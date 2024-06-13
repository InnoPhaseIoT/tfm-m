/****************************************************************************
 * @attention
 *
 * Copyright (c) 2024, InnoPhase IoT, Inc.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
/**
 * @file    inph_mpc_drv.c
 * @author  InnophaseIOT Firmware Team
 * @brief   InnophaseIOT MPC driver
 */

#include "inph_mpc_drv.h"
#include "tfm_utils.h"

//#include "tfm_hal_device_header.h"

#define INPH_MPC_SIE200_BLK_CFG_OFFSET  5U

#define INPH_MPC_SIE200_CTRL_SEC_RESP      (1UL << 4UL)  /* MPC fault triggers a
                                                     * bus error */
#define INPH_MPC_SIE200_CTRL_AUTOINCREMENT (1UL << 8UL)  /* BLK_IDX auto increment */
#define INPH_MPC_SIE200_CTRL_SEC_LOCK_DOWN (1UL << 31UL) /* MPC Security lock down */

/* ARM MPC interrupt */
#define INPH_MPC_SIE200_INT_EN    1UL
#define INPH_MPC_SIE200_INT_STAT  1UL

/* ARM MPC state definitions */
#define INPH_MPC_SIE200_INITIALIZED  (1 << 0)


/* Error code returned by the internal driver functions */
enum inph_mpc_sie200_intern_error_t{
    INPH_MPC_SIE200_INTERN_ERR_NONE =  INPH_MPC_SIE200_ERR_NONE,
    INPH_MPC_SIE200_INTERN_ERR_NOT_IN_RANGE = INPH_MPC_SIE200_ERR_NOT_IN_RANGE,
    INPH_MPC_SIE200_INTERN_ERR_NOT_ALIGNED  = INPH_MPC_SIE200_ERR_NOT_ALIGNED,
    INPH_MPC_SIE200_INTERN_ERR_INVALID_RANGE = INPH_MPC_SIE200_ERR_INVALID_RANGE,
    MPC_INTERN_ERR_RANGE_SEC_ATTR_NON_COMPATIBLE =
                                   INPH_MPC_SIE200_ERR_RANGE_SEC_ATTR_NON_COMPATIBLE,
    /* Calculated block index
       is higher than the maximum allowed by the MPC. It should never
       happen unless the controlled ranges of the MPC are misconfigured
       in the driver or if the IP has not enough LUTs to cover the
       range, due to wrong reported block size for example.
    */
    INPH_MPC_SIE200_INTERN_ERR_BLK_IDX_TOO_HIGH = -1,

};

/* ARM MPC memory mapped register access structure */
struct inph_mpc_sie200_reg_map_t {
    volatile uint32_t ctrl;       /* (R/W) MPC Control */
    volatile uint32_t reserved[3];/* Reserved */
    volatile uint32_t blk_max;    /* (R/ ) Maximum value of block based index */
    volatile uint32_t blk_cfg;    /* (R/ ) Block configuration */
    volatile uint32_t blk_idx;    /* (R/W) Index value for accessing block
                                   *       based look up table */
    volatile uint32_t blk_lutn;   /* (R/W) Block based gating
                                   *       Look Up Table (LUT) */
    volatile uint32_t int_stat;   /* (R/ ) Interrupt state */
    volatile uint32_t int_clear;  /* ( /W) Interrupt clear */
    volatile uint32_t int_en;     /* (R/W) Interrupt enable */
    volatile uint32_t int_info1;  /* (R/ ) Interrupt information 1 */
    volatile uint32_t int_info2;  /* (R/ ) Interrupt information 2 */
    volatile uint32_t int_set;    /* ( /W) Interrupt set. Debug purpose only */
    volatile uint32_t reserved2[997]; /* Reserved */
    volatile uint32_t pidr4;      /* (R/ ) Peripheral ID 4 */
    volatile uint32_t pidr5;      /* (R/ ) Peripheral ID 5 */
    volatile uint32_t pidr6;      /* (R/ ) Peripheral ID 6 */
    volatile uint32_t pidr7;      /* (R/ ) Peripheral ID 7 */
    volatile uint32_t pidr0;      /* (R/ ) Peripheral ID 0 */
    volatile uint32_t pidr1;      /* (R/ ) Peripheral ID 1 */
    volatile uint32_t pidr2;      /* (R/ ) Peripheral ID 2 */
    volatile uint32_t pidr3;      /* (R/ ) Peripheral ID 3 */
    volatile uint32_t cidr0;      /* (R/ ) Component ID 0 */
    volatile uint32_t cidr1;      /* (R/ ) Component ID 1 */
    volatile uint32_t cidr2;      /* (R/ ) Component ID 2 */
    volatile uint32_t cidr3;      /* (R/ ) Component ID 3 */
};

/*
 * Checks if the address is controlled by the MPC and returns
 * the range index in which it is contained.
 *
 * \param[in]  dev         MPC device to initalize \ref inph_mpc_sie200_dev_t
 * \param[in]  addr        Address to check if it is controlled by MPC.
 * \param[out] addr_range  Range index in which it is contained.
 *
 * \return True if the base is controller by the range list, false otherwise.
 */
static uint32_t inph_mpc_range_list(struct inph_mpc_sie200_dev_t* dev, uint32_t addr,
                            const struct inph_mpc_sie200_memory_range_t** addr_range)
{
    uint32_t i;
    const struct inph_mpc_sie200_memory_range_t* range;

    for(i = 0; i < dev->data->nbr_of_ranges; i++) {
        range = dev->data->range_list[i];
        if(addr >= range->base && addr <= range->limit) {
            *addr_range = range;
            return 1;
        }
    }
    return 0;
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_init(struct inph_mpc_sie200_dev_t* dev,
                            const struct inph_mpc_sie200_memory_range_t** range_list,
                            uint8_t nbr_of_ranges)
{
    if((range_list == NULL) || (nbr_of_ranges == 0)) {
        return INPH_MPC_SIE200_INVALID_ARG;
    }

    dev->data->range_list = range_list;
    dev->data->nbr_of_ranges = nbr_of_ranges;
    dev->data->state = INPH_MPC_SIE200_INITIALIZED;

    return INPH_MPC_SIE200_ERR_NONE;
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_get_block_size(struct inph_mpc_sie200_dev_t* dev,
                                                  uint32_t* blk_size)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    if(blk_size == 0) {
        return INPH_MPC_SIE200_INVALID_ARG;
    }

    /* Calculate the block size in byte according to the manual */
    *blk_size = (1 << (p_mpc->blk_cfg + INPH_MPC_SIE200_BLK_CFG_OFFSET));

    return INPH_MPC_SIE200_ERR_NONE;
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_config_region(struct inph_mpc_sie200_dev_t* dev,
                                                const uint32_t base,
                                                const uint32_t limit,
                                                enum inph_mpc_sie200_sec_attr_t attr)
{
    uint32_t base_word_mask, base_word;
    uint32_t block_size, norm_base, base_block_idx;
    const struct inph_mpc_sie200_memory_range_t* range;
    const struct inph_mpc_sie200_memory_range_t* base_range;
    const struct inph_mpc_sie200_memory_range_t* limit_range;
    uint32_t word_value;
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    /* Sanity check to make sure the given range is within this MPCs range */
    if ((dev->data->range_list[attr]->base > base) ||
                    (dev->data->range_list[attr]->limit < limit) ) {
        return INPH_MPC_SIE200_ERR_NOT_IN_RANGE;
    }
    /*
     * Check that the addresses are within the controlled regions
     * of this MPC
     */
     if(!inph_mpc_range_list(dev, base, &base_range) ||
        !inph_mpc_range_list(dev, limit, &limit_range)) {
         return INPH_MPC_SIE200_INTERN_ERR_NOT_IN_RANGE;
     }

     /* Base and limit should be part of the same range */
     if(base_range != limit_range) {
        return INPH_MPC_SIE200_INTERN_ERR_INVALID_RANGE;
     }
     range = base_range;
     
     block_size = (1 << (p_mpc->blk_cfg + INPH_MPC_SIE200_BLK_CFG_OFFSET));

     /* Base and limit+1 addresses must be aligned on the MPC block size */
     if(base % block_size || (limit+1) % block_size) {
        return INPH_MPC_SIE200_INTERN_ERR_NOT_ALIGNED;
     }
  
    /*
     * The memory range should allow accesses in with the wanted security
     * attribute if it requires special attribute for successfull accesses
     */
    if(range->attr != attr) {
        return INPH_MPC_SIE200_ERR_RANGE_SEC_ATTR_NON_COMPATIBLE;
    }

    /*
     * Starts changing actual configuration so issue DMB to ensure every
     * transaction has completed by now
     */
//    __DMB();

    if (range->attr == INPH_MPC_SIE200_SEC_ATTR_SECURE)
    {
        norm_base = base - INPH_MPC_MEM_BASE_ADDR_S;
    }
    else
    {
        norm_base = base - INPH_MPC_MEM_BASE_ADDR_NS;
    }
    base_block_idx = norm_base/block_size;
    base_word_mask = (1 << (base_block_idx % 32));
    base_word = base_block_idx / 32;
    
    /* choose the word in LUT */
    p_mpc->blk_idx = base_word;

    /* If only one word needs to be touched in the LUT */
    word_value = p_mpc->blk_lutn;
    if(attr == INPH_MPC_SIE200_SEC_ATTR_NONSECURE) {
       word_value |= base_word_mask;
    } else {
       word_value &= ~base_word_mask;
    }

    /*
     * Set the index again because full word read or write could have
     * incremented it
     */
    p_mpc->blk_idx = base_word;
    p_mpc->blk_lutn = word_value;

    /* Commit the configuration change */
//    __DSB();
//    __ISB();

    return INPH_MPC_SIE200_ERR_NONE;
 
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_get_region_config(
                                               struct inph_mpc_sie200_dev_t* dev,
                                               uint32_t base, uint32_t limit,
                                               enum inph_mpc_sie200_sec_attr_t* attr)
{
    uint32_t block_size, base_word_mask;
    uint32_t block_size_mask, base_word;
    uint32_t norm_base, base_block_idx;
    const struct inph_mpc_sie200_memory_range_t* base_range;
    const struct inph_mpc_sie200_memory_range_t* limit_range;    
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;
    const struct inph_mpc_sie200_memory_range_t* range;
    uint32_t word_value;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    if(attr == 0) {
        return INPH_MPC_SIE200_INVALID_ARG;
    }

    /*
     * Initialize the security attribute to mixed in case of early
     * termination of this function. A caller that does not check the
     * returned error will act as if it does not know anything about the
     * region queried, which is the safest bet
     */
    *attr = INPH_MPC_SIE200_SEC_ATTR_MIXED;

    /*
     * If the base and limit are not aligned, align them and make sure
     * that the resulting region fully includes the original region
     */
    block_size = (1 << (p_mpc->blk_cfg + INPH_MPC_SIE200_BLK_CFG_OFFSET));

    block_size_mask = block_size - 1;
    base &= ~(block_size_mask);
    limit &= ~(block_size_mask);
    limit += block_size - 1; /* Round to the upper block address,
                              * and then remove one to get the preceding
                              * address. */
    
    if(!inph_mpc_range_list(dev, base, &base_range) ||
       !inph_mpc_range_list(dev, limit, &limit_range)) {
        return INPH_MPC_SIE200_INTERN_ERR_NOT_IN_RANGE;
    }    

    /* Set the block index to the first word that will be updated */
    if (range->attr == INPH_MPC_SIE200_SEC_ATTR_SECURE)
    {
        norm_base = base - INPH_MPC_MEM_BASE_ADDR_S;
    }
    else
    {
        norm_base = base - INPH_MPC_MEM_BASE_ADDR_NS;
    }
    
   base_block_idx = norm_base/block_size;
   base_word_mask = (1 << (base_block_idx % 32));
   base_word = base_block_idx / 32;
        
   /* choose the word in LUT */
   p_mpc->blk_idx = base_word;

    /* If only one word needs to be touched in the LUT */
    word_value = p_mpc->blk_lutn;
    word_value &= base_word_mask;
    if(word_value == 0) {
       *attr = INPH_MPC_SIE200_SEC_ATTR_SECURE;
    }
    else {
           *attr = INPH_MPC_SIE200_SEC_ATTR_NONSECURE;
        }
    
    return INPH_MPC_SIE200_ERR_NONE;

}

enum inph_mpc_sie200_error_t inph_mpc_sie200_get_ctrl(struct inph_mpc_sie200_dev_t* dev,
                                            uint32_t* ctrl_val)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    if(ctrl_val == 0) {
        return INPH_MPC_SIE200_INVALID_ARG;
    }

    *ctrl_val = p_mpc->ctrl;

    return INPH_MPC_SIE200_ERR_NONE;
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_set_ctrl(struct inph_mpc_sie200_dev_t* dev,
                                            uint32_t mpc_ctrl)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    p_mpc->ctrl = mpc_ctrl;

    return INPH_MPC_SIE200_ERR_NONE;
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_get_sec_resp(struct inph_mpc_sie200_dev_t* dev,
                                            enum inph_mpc_sie200_sec_resp_t* sec_rep)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    if(sec_rep == 0) {
        return INPH_MPC_SIE200_INVALID_ARG;
    }

    if(p_mpc->ctrl & INPH_MPC_SIE200_CTRL_SEC_RESP) {
        *sec_rep = INPH_MPC_SIE200_RESP_BUS_ERROR;
        return INPH_MPC_SIE200_ERR_NONE;
    }

    *sec_rep = INPH_MPC_SIE200_RESP_RAZ_WI;

    return INPH_MPC_SIE200_ERR_NONE;
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_irq_enable(struct inph_mpc_sie200_dev_t* dev)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    p_mpc->int_en |= INPH_MPC_SIE200_INT_EN;

    return INPH_MPC_SIE200_ERR_NONE;
}

void inph_mpc_sie200_irq_disable(struct inph_mpc_sie200_dev_t* dev)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    p_mpc->int_en &= ~INPH_MPC_SIE200_INT_EN;
}

void inph_mpc_sie200_clear_irq(struct inph_mpc_sie200_dev_t* dev)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    p_mpc->int_clear = INPH_MPC_SIE200_INT_EN;
}

uint32_t inph_mpc_sie200_irq_state(struct inph_mpc_sie200_dev_t* dev)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    return (p_mpc->int_stat & INPH_MPC_SIE200_INT_STAT);
}

enum inph_mpc_sie200_error_t inph_mpc_sie200_lock_down(struct inph_mpc_sie200_dev_t* dev)
{
    struct inph_mpc_sie200_reg_map_t* p_mpc =
                                   (struct inph_mpc_sie200_reg_map_t*)dev->cfg->base;

    if(!(dev->data->state & INPH_MPC_SIE200_INITIALIZED)) {
        return INPH_MPC_SIE200_NOT_INIT;
    }

    p_mpc->ctrl |= (INPH_MPC_SIE200_CTRL_AUTOINCREMENT
                    | INPH_MPC_SIE200_CTRL_SEC_LOCK_DOWN);

    return INPH_MPC_SIE200_ERR_NONE;
}
