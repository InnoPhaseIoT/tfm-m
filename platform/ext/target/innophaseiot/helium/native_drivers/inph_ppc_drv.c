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
 * @file    inph_ppc_drv.h
 * @author  InnophaseIOT Firmware Team
 * @brief   PPC functions
 */

#include "inph_ppc_drv.h"

#define AHB_PPC_XIP_INT_POS_MASK     (1UL << 7)
#define AHB_PPC_SDIO_INT_POS_MASK    (1UL << 6)
#define AHB_PPC_PERIPH1_INT_POS_MASK (1UL << 5)
#define AHB_PPC_PERIPH0_INT_POS_MASK (1UL << 4)
#define AHB_PPC_SYSCTRL_INT_POS_MASK (1UL << 3)
#define AHB_PPC_BASE2_INT_POS_MASK   (1UL << 2)
#define AHB_PPC_BASE1_INT_POS_MASK   (1UL << 1)
#define AHB_PPC_BASE0_INT_POS_MASK   (1UL << 0)

#define AHB_PPC_GPIO_INT_POS_MASK    (1UL << 0)


/* ARM PPC state definitions */
#define INPH_PPC_INITIALIZED  (1 << 0)

/* Default peripheral states */
#define SECURE_AS_DEFAULT_PERIPHERAL_STATE  1
#define PRIVILEGE_ONLY_AS_DEFAULT_PERIPHERAL_STATE  1

void inph_ppc_init(struct inph_ppc_dev_t* dev,
                     enum inph_ppc_name_t ppc_name)
{
    struct inph_spctrl_ppc_sse200_t* p_spctrl = 
                         (struct inph_spctrl_ppc_sse200_t *)dev->cfg->spctrl_base;

    switch(ppc_name) {
        case AHB_PPC_XIP:
            dev->data->p_ns_ppc  = &p_spctrl->ahbnsppccxip;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppccxip;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppccxip;
            dev->data->int_bit_mask = AHB_PPC_XIP_INT_POS_MASK;
            break;
            
        case AHB_PPC_SDIO:
            dev->data->p_ns_ppc  = &p_spctrl->ahbnsppcsdio;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcsdio;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcsdio;
            dev->data->int_bit_mask = AHB_PPC_SDIO_INT_POS_MASK;
            break;
        case AHB_PPC_PERIPH1:
            dev->data->p_ns_ppc  = &p_spctrl->apbnsppcperiph1;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcperiph1;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcperiph1;
            dev->data->int_bit_mask = AHB_PPC_PERIPH1_INT_POS_MASK;
            break;
        case APB_PPC_PERIPH0:
            dev->data->p_ns_ppc  = &p_spctrl->apbnsppcperiph0;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcperiph0;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcperiph0;
            dev->data->int_bit_mask = AHB_PPC_PERIPH0_INT_POS_MASK;
            break;
        case AHB_PPC_SYSTEM:
            dev->data->p_ns_ppc  = &p_spctrl->apbnsppcsys;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcsys;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcsys;
            dev->data->int_bit_mask = AHB_PPC_SYSCTRL_INT_POS_MASK;
            break;
        case APB_PPC_BASE2:
            dev->data->p_ns_ppc  = &p_spctrl->apnnsppcbase2;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcbase2;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcbase2;
            dev->data->int_bit_mask = AHB_PPC_BASE2_INT_POS_MASK;
            break;
        case APB_PPC_BASE1:
            dev->data->p_ns_ppc  = &p_spctrl->apnnsppcbase1;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcbase1;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcbase1;
            dev->data->int_bit_mask = AHB_PPC_BASE1_INT_POS_MASK;
            break;
        case APB_PPC_BASE0:
            dev->data->p_ns_ppc  = &p_spctrl->apnnsppcbase0;
            dev->data->p_sp_ppc  = &p_spctrl->apbsprvppcbase0;
            dev->data->p_nsp_ppc = &p_spctrl->apbsprvppcbase0;
            dev->data->int_bit_mask = AHB_PPC_BASE0_INT_POS_MASK;
            break;
        
        /* default:  The default is not defined intentionally to force the
         *           compiler to check that all enumeration values are
         *           covered in the switch.*/
    }

    dev->data->state = INPH_PPC_INITIALIZED;
}

enum inph_ppc_error_t inph_ppc_config_peripheral(
                                          struct inph_ppc_dev_t* dev,
                                          uint8_t periph,
                                          enum inph_ppc_sec_attr_t sec_attr,
                                          enum inph_ppc_priv_attr_t priv_attr)
{
    if(dev->data->state != INPH_PPC_INITIALIZED) {
        return INPH_PPC_NOT_INIT;
    }

    if(sec_attr == INPH_PPC_SECURE_ONLY) {
        /* Sets secure attribute */
        *(dev->data->p_ns_ppc) &= ~(1U << periph);

        /* Uses secure unprivileged access address (SPCTRL) to set privilege
         * attribute */
        if(priv_attr == INPH_PPC_PRIV_ONLY) {
            *(dev->data->p_sp_ppc) &= ~(1U << periph);
        } else {
            *(dev->data->p_sp_ppc) |= (1U << periph);
        }
    } else {
        /* Sets non-secure attribute */
        *(dev->data->p_ns_ppc) |= (1U << periph);

        /* Uses non-secure unprivileged access address (NSPCTRL) to set
         * privilege attribute */
        if(priv_attr == INPH_PPC_PRIV_ONLY) {
            *(dev->data->p_nsp_ppc) &= ~(1U << periph);
        } else {
            *(dev->data->p_nsp_ppc) |= (1U << periph);
        }
    }

    return INPH_PPC_ERR_NONE;
}

uint32_t inph_ppc_is_periph_secure(struct inph_ppc_dev_t* dev,
                                     uint8_t periph)
{
    if(dev->data->state != INPH_PPC_INITIALIZED) {
        return SECURE_AS_DEFAULT_PERIPHERAL_STATE;
    }

    return ((*(dev->data->p_ns_ppc) & (1U << periph)) == 0);
}

uint32_t inph_ppc_is_periph_priv_only(struct inph_ppc_dev_t* dev,
                                        uint8_t periph)
{
    if(dev->data->state != INPH_PPC_INITIALIZED) {
        return PRIVILEGE_ONLY_AS_DEFAULT_PERIPHERAL_STATE;
    }

    if ((*(dev->data->p_ns_ppc) & (1U << periph)) == 0) {
        /* Returns secure unprivileged access address (SPCTRL) */
        return ((*(dev->data->p_sp_ppc) & (1U << periph)) == 1);
    } else {
        /* Returns non-secure unprivileged access address (NSPCTRL) */
        return ((*(dev->data->p_nsp_ppc) & (1U << periph)) == 0);
    }
}

enum inph_ppc_error_t inph_ppc_irq_enable(struct inph_ppc_dev_t* dev)
{
    struct inph_spctrl_ppc_sse200_t* p_spctrl =
                         (struct inph_spctrl_ppc_sse200_t*)dev->cfg->spctrl_base;

    if(dev->data->state != INPH_PPC_INITIALIZED) {
        return INPH_PPC_NOT_INIT;
    }

    p_spctrl->secppcinten |= dev->data->int_bit_mask;

    return INPH_PPC_ERR_NONE;
}

void inph_ppc_irq_disable(struct inph_ppc_dev_t* dev)
{
    struct inph_spctrl_ppc_sse200_t* p_spctrl =
                         (struct inph_spctrl_ppc_sse200_t*)dev->cfg->spctrl_base;

    if(dev->data->state == INPH_PPC_INITIALIZED) {
        p_spctrl->secppcinten &= ~(dev->data->int_bit_mask);
    }
}

void inph_ppc_clear_irq(struct inph_ppc_dev_t* dev)
{
    struct inph_spctrl_ppc_sse200_t* p_spctrl =
                         (struct inph_spctrl_ppc_sse200_t*)dev->cfg->spctrl_base;

    if(dev->data->state == INPH_PPC_INITIALIZED) {
        p_spctrl->secppcintclr = dev->data->int_bit_mask;
    }
}

uint32_t inph_ppc_irq_state(struct inph_ppc_dev_t* dev)
{
    struct inph_spctrl_ppc_sse200_t* p_spctrl =
                         (struct inph_spctrl_ppc_sse200_t*)dev->cfg->spctrl_base;

    if(dev->data->state != INPH_PPC_INITIALIZED) {
        return 0;
    }

    return ((p_spctrl->secppcintstatus & dev->data->int_bit_mask) != 0);
}
