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
 * @file    inph_mpc_drv.h
 * @author  InnophaseIOT Firmware Team
 * @brief   InnophaseIOT driver for ARM SEE 200 Memory Protection controller
 */

#ifndef __INPH_MPC_DRV_H
#define __INPH_MPC_DRV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


struct inph_sse200_mpc_t {

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


/* Error code returned by the driver functions */
enum inph_mpc_sie200_error_t {
    INPH_MPC_SIE200_ERR_NONE,          /*!< No error */
    INPH_MPC_SIE200_INVALID_ARG,       /*!< MPC invalid input arguments */
    INPH_MPC_SIE200_NOT_INIT,          /*!< MPC not initialized */
    INPH_MPC_SIE200_ERR_NOT_IN_RANGE,  /*!< Address does not belong to a range
                                   *   controlled by the MPC */
    INPH_MPC_SIE200_ERR_NOT_ALIGNED,   /*!< Address is not aligned on the block size
                                   *   of this MPC */
    INPH_MPC_SIE200_ERR_INVALID_RANGE, /*!< The given address range to configure
                                   *   is invalid. This could be because:
                                   *   - The base and limit swapped
                                   *   - The base and limit addresses
                                   *     are in different ranges */
    INPH_MPC_SIE200_ERR_RANGE_SEC_ATTR_NON_COMPATIBLE, /*!< The given range cannot be
                                                   *   accessed with the wanted
                                                   *   security attributes */
};

/* Security attribute used in various place of the API */
enum inph_mpc_sie200_sec_attr_t {
    INPH_MPC_SIE200_SEC_ATTR_SECURE,     /*!< Secure attribute */
    INPH_MPC_SIE200_SEC_ATTR_NONSECURE,  /*!< Non-secure attribute */
    /*!< Used when getting the configuration of a memory range and some blocks
     *   are secure whereas some other are non secure */
    INPH_MPC_SIE200_SEC_ATTR_MIXED,
};

/* What can happen when trying to do an illegal memory access */
enum inph_mpc_sie200_sec_resp_t {
    INPH_MPC_SIE200_RESP_RAZ_WI,    /*!< Read As Zero, Write Ignored */
    INPH_MPC_SIE200_RESP_BUS_ERROR  /*!< Bus error */
};

/* Description of a memory range controlled by the MPC */
struct inph_mpc_sie200_memory_range_t {
    const uint32_t base;   /*!< Base address (included in the range) */
    const uint32_t limit;  /*!< Limit address (excluded in the range) */
    const enum inph_mpc_sie200_sec_attr_t attr; /*!< Optional security attribute
                                                needed to be matched when
                                                accessing this range.
                                                For example, the non-secure
                                                alias of a memory region can not
                                                be accessed using secure access,
                                                and configuring the MPC to
                                                secure using that range will not
                                                be permitted by the driver. */
};

/* ARM MPC SIE 200 device configuration structure */
struct inph_mpc_sie200_dev_cfg_t {
    const uint32_t base;  /*!< MPC base address */
};

/* ARM MPC SIE 200 device data structure */
struct inph_mpc_sie200_dev_data_t {
    const struct inph_mpc_sie200_memory_range_t** range_list;  /*!< Array of pointers
                                                               to memory ranges
                                                               controlled by
                                                               the MPC */
    uint8_t nbr_of_ranges;  /*!< Number of memory ranges in the list */
    uint8_t state;          /*!< Indicates if the MPC driver
                                 is initialized and enabled */
    uint16_t reserved;      /*!< 32 bits alignment */
};

/* ARM MPC SIE 200 device structure */
struct inph_mpc_sie200_dev_t {
    const struct inph_mpc_sie200_dev_cfg_t* const cfg;  /*!< MPC configuration */
    struct inph_mpc_sie200_dev_data_t* const data;      /*!< MPC data */
};

/**
 * \brief Initializes a MPC device.
 *
 * \param[in] dev            MPC device \ref inph_mpc_sie200_dev_t
 * \param[in] range_list     List of memory ranges controller by the MPC
 *                           (\ref inph_mpc_sie200_memory_range_t). This list can not
 *                           freed after the initializations.
 * \param[in] nbr_of_ranges  Number of memory ranges
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_init(struct inph_mpc_sie200_dev_t* dev,
                            const struct inph_mpc_sie200_memory_range_t** range_list,
                            uint8_t nbr_of_ranges);

/**
 * \brief Gets MPC block size. All regions must be aligned on this block
 *        size (base address and limit+1 address).
 *
 * \param[in]  dev       MPC device \ref inph_mpc_sie200_dev_t
 * \param[out] blk_size  MPC block size
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_get_block_size(struct inph_mpc_sie200_dev_t* dev,
                                                  uint32_t* blk_size);

/**
 * \brief Configures a memory region (base and limit included).
 *
 * \param[in] dev    MPC device \ref inph_mpc_sie200_dev_t
 * \param[in] base   Base address of the region to poll. This bound is
 *                   included. It does not need to be aligned in any way.
 *
 * \param[in] limit  Limit address of the region to poll. This bound is
 *                   included. (limit+1) does not need to be aligned
 *                   in any way.
 * \param[in] attr   Security attribute of the region. If the region has mixed
 *                   secure/non-secure, a special value is returned
 *                   (\ref inph_mpc_sie200_sec_attr_t).
 *
 *            In case base and limit+1 addresses are not aligned on
 *            the block size, the enclosing region with base and
 *            limit+1 aligned on block size will be queried.
 *            In case of early termination of the function (error), the
 *            security attribute will be set to INPH_MPC_SIE200_ATTR_MIXED.
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_config_region(struct inph_mpc_sie200_dev_t* dev,
                                               const uint32_t base,
                                               const uint32_t limit,
                                               enum inph_mpc_sie200_sec_attr_t attr);

/**
 * \brief Gets a memory region configuration(base and limit included).
 *
 * \param[in]  dev    MPC device \ref inph_mpc_sie200_dev_t
 * \param[in]  base   Base address of the region to get the configuration.
 * \param[in]  limit  Limit address of the region to get the configuration.
 * \param[out] attr   Security attribute of the region
 *                    \ref inph_mpc_sie200_sec_attr_t
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_get_region_config(
                                              struct inph_mpc_sie200_dev_t* dev,
                                              uint32_t base,
                                              uint32_t limit,
                                              enum inph_mpc_sie200_sec_attr_t* attr);

/**
 * \brief Gets the MPC control value.
 *
 * \param[in]  dev       MPC device \ref inph_mpc_sie200_dev_t
 * \param[out] ctrl_val  Current MPC control value.
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_get_ctrl(struct inph_mpc_sie200_dev_t* dev,
                                            uint32_t* ctrl_val);

/**
 * \brief Sets the MPC control value.
 *
 * \param[in] dev       MPC device \ref inph_mpc_sie200_dev_t
 * \param[in] mpc_ctrl  New MPC control value
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_set_ctrl(struct inph_mpc_sie200_dev_t* dev,
                                            uint32_t mpc_ctrl);

/**
 * \brief Gets the configured secure response.
 *
 * \param[in]  dev      MPC device \ref inph_mpc_sie200_dev_t
 * \param[out] sec_rep  Configured secure response (\ref inph_mpc_sie200_sec_resp_t).
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_get_sec_resp(struct inph_mpc_sie200_dev_t* dev,
                                           enum inph_mpc_sie200_sec_resp_t* sec_rep);

/**
 * \brief Enables MPC interrupt.
 *
 * \param[in] dev  MPC device \ref inph_mpc_sie200_dev_t
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_irq_enable(struct inph_mpc_sie200_dev_t* dev);

/**
 * \brief Disables MPC interrupt
 *
 * \param[in] dev  MPC device \ref inph_mpc_sie200_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_mpc_sie200_irq_disable(struct inph_mpc_sie200_dev_t* dev);

/**
 * \brief Clears MPC interrupt.
 *
 * \param[in] dev  MPC device \ref inph_mpc_sie200_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_mpc_sie200_clear_irq(struct inph_mpc_sie200_dev_t* dev);

/**
 * \brief Returns the MPC interrupt state.
 *
 * \param[in] dev  MPC device \ref inph_mpc_sie200_dev_t
 *
 * \return Returns 1 if the interrupt is active, 0 otherwise.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t inph_mpc_sie200_irq_state(struct inph_mpc_sie200_dev_t* dev);

/**
 * \brief Locks down the MPC configuration.
 *
 * \param[in] dev  MPC device \ref inph_mpc_sie200_dev_t
 *
 * \return Returns error code as specified in \ref inph_mpc_sie200_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_mpc_sie200_error_t inph_mpc_sie200_lock_down(struct inph_mpc_sie200_dev_t* dev);

#ifdef __cplusplus
}
#endif
#endif /* __INPH_MPC_DRV_H */
