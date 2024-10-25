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
 * @file    inph_tzm_drv.h
 * @author  InnophaseIOT Firmware Team
 * @brief   InnophaseIOT driver for ARM Trust Zone Master controller
 */

#ifndef __INPH_TZM_DRV_H
#define __INPH_TZM_DRV_H

#include <stdint.h>
#include "inph_security_registers.h"

/* Secure Privilege Control Block aka SPCTRL */

#define AHB_TZM_NPU_RX_NS_POS_MASK      (1UL << 0)
#define AHB_TZM_NPU_TX_NS_POS_MASK      (1UL << 1)
#define AHB_TZM_UDMA_BASE_NS_POS_MASK   (1UL << 2)
#define AHB_TZM_DEBUG_NS_POS_MASK       (1UL << 3)
#define AHB_TZM_CRYPTO_SUB_NS_POS_MASK  (1UL << 5)
#define AHB_TZM_XSPI1_DMA_POS_MASK      (1UL << 6)
#define AHB_TZM_XSPI2_DMA_POS_MASK      (1UL << 8)
#define AHB_TZM_NPU_SYS_CTRL_NS_POS_MASK (1UL << 10)
#define AHB_TZM_NPU_CODE_NS_POS_MASK    (1UL << 11)
#define AHB_TZM_NPU_MEM_NS_POS_MASK     (1UL << 12)

/* ARM TZM state definitions */
#define INPH_TZM_INITIALIZED  (1 << 0)

/* Security attribute used to configure the peripheral */
enum inph_tzm_sec_attr_t {
    INPH_TZM_SECURE_ONLY = 0,    /*! Secure access */
    INPH_TZM_NONSECURE_ONLY, /*! Non-secure access */
};

/* ARM TZM error codes */
enum inph_tzm_error_t {
    INPH_TZM_ERR_NONE = 0,  /*!< No error */
    INPH_TZM_ERROR,      /*!< TZM error */
};

/* ARM TZM device structure */
struct inph_tzm_dev_t {
    uint32_t const spctrl_base;  /*!< SPCTRL base address */
    uint8_t state;               /*!< Indicates if the TZM driver is set */
};

/**
 * \brief Enables secure or non-secure for TZM.
 *
 * \param[in] dev  TZM device \ref inph_tzm_dev_t
 *
 * \return Returns error code as specified in \ref inph_tzm_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_tzm_error_t inph_tzm_config(struct inph_tzm_dev_t* dev,
                                          uint8_t tzm,
                                          enum inph_tzm_sec_attr_t sec_attr);

/**
 * \brief Enables interrupt for tzm.
 *
 * \param[in] dev  TZM device \ref inph_tzm_dev_t
 *
 * \return Returns error code as specified in \ref inph_tzm_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_tzm_error_t inph_tzm_irq_enable(struct inph_tzm_dev_t* dev,
                                          uint8_t tzm);

/**
 * \brief Disables tzm interrupt.
 *
 * \param[in] dev  tzm device \ref inph_tzm_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_tzm_irq_disable(struct inph_tzm_dev_t* dev, uint8_t tzm);

/**
 * \brief Clears tzm interrupt.
 *
 * \param[in] dev  tzm device \ref inph_tzm_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_tzm_clear_irq(struct inph_tzm_dev_t* dev, uint8_t tzm);


#endif /* __INPH_TZM_DRV_H__ */
