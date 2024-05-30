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
 * @brief   InnophaseIOT driver for ARM SEE 200 Peripheral Protection Controllers
 */

#ifndef __INPH_PPC_DRV_H
#define __INPH_PPC_DRV_H

/* SPCTRL PPCs control memory mapped registers access structure */
struct inph_spctrl_ppc_sse200_t {
    volatile uint32_t spcsecctrl;       /* configuration control register */
    volatile uint32_t buswait;          /* bus access wait control */
    volatile uint32_t secrespcfg;       /* security  violation response config register */
    volatile uint32_t nsccfg;           /* non secure callable config for IDAU */
    //MPC
    volatile uint32_t secmpcintstatus;  /* memory protection controller interrupt status */                                         
    volatile uint32_t secmpcinten;      /* MPC interrupt enable */
    
    //PPC
    volatile uint32_t secppcintstatus;  /* PPC controller interrupt status */
    volatile uint32_t secppcintclr;     /* ppc interrupt clear */
    volatile uint32_t secppcinten;      /* ppc interrupt enable */

    // Master security controller
    volatile uint32_t secmscintstatus;  /* master security interrupt status */
    volatile uint32_t secmscintclr;     /* master security interrupt clear */
    volatile uint32_t secmscintent;     /* master security interrupt enable */
    
    //TrustZone GPIO secure interrupt
    volatile uint32_t secgpiointen;     /* TrustZone GPIO security interrupt enable */

    //Base0 Base1 Base2
    volatile uint32_t apnnsppcbase0;    /* APB slave PPC Base0 */
    volatile uint32_t apnnsppcbase1;    /* APB slave PPC Base1 */
    volatile uint32_t apnnsppcbase2;    /* APB slave PPC Base2 */

    //system control PPC
    volatile uint32_t apbnsppcsys;      /* system control PPC */
    
    //system control peripheral ppc
    volatile uint32_t apbnsppcperiph0;  /* system control ppc peripheral0 */
    volatile uint32_t apbnsppcperiph1;  /* system control ppc peripheral1 */
    
    //SDIO xip
    volatile uint32_t ahbnsppcsdio;     /* sdio ppc */
    volatile uint32_t ahbnsppccxip;     /* xip ppc */
    
    //privileged access
    volatile uint32_t apbsprvppcbase0;  /* privileged access base0 peripherals */
    volatile uint32_t apbsprvppcbase1;  /* privileged access base0 peripherals */
    volatile uint32_t apbsprvppcbase2;  /* privileged access base0 peripherals */

    volatile uint32_t apbsprvppcsys;    /* privileged access system controller */
    
    volatile uint32_t apbsprvppcperiph0;   /* privileged access peripheral0 */
    volatile uint32_t apbsprvppcperiph1;   /* privileged access peripheral1 */
    
    volatile uint32_t apbsprvppcsdio;   /* privileged access sdio */
    volatile uint32_t apbsprvppccxip;   /* privileged access xip */

    volatile uint32_t nsmsc;            /* master security controller non-secure access */

    volatile uint32_t nsgpio     ;      /* gpio non-secure access */
};


/* Secure Privilege Control Block aka SPCTRL */
/* Non-Secure Privilege Control Block aka NSPCTRL */


/* ARM TrustZone PPC device configuration structure */
struct inph_ppc_dev_cfg_t {
    uint32_t const spctrl_base;  /*!< SPCTRL base address */
    uint32_t const nspctrl_base; /*!< NSPCTRL base address */
};

/* ARM TrustZone PPC device data structure */
struct inph_ppc_dev_data_t {
    volatile uint32_t* p_ns_ppc;  /*!< Pointer to non-secure register */
    volatile uint32_t* p_sp_ppc;  /*!< Pointer to secure unprivileged
                                       register */
    volatile uint32_t* p_nsp_ppc; /*!< Pointer to non-secure unprivileged
                                       register */
    uint32_t int_bit_mask;        /*!< Interrupt bit mask */
    uint8_t state;                /*!< Indicates if the PPC driver
                                      is initialized */
    uint8_t reserved[3];          /*!< 32 bits alignment */
};

/* ARM PPC device structure */
struct inph_ppc_dev_t {
    const struct inph_ppc_dev_cfg_t* const cfg;  /*!< PPC configuration */
    struct inph_ppc_dev_data_t* const data;      /*!< PPC data */
};

/* Security attribute used to configure the peripheral */
enum inph_ppc_sec_attr_t {
    INPH_PPC_SECURE_ONLY,    /*! Secure access */
    INPH_PPC_NONSECURE_ONLY, /*! Non-secure access */
};

/* Privilege attribute used to configure the peripheral */
enum inph_ppc_priv_attr_t {
    INPH_PPC_PRIV_AND_NONPRIV, /*! Privilege and non-Privilege access */
    INPH_PPC_PRIV_ONLY,        /*! Privilege only access */
};

/* ARM PPC error codes */
enum inph_ppc_error_t {
    INPH_PPC_ERR_NONE = 0,  /*!< No error */
    INPH_PPC_NOT_INIT,      /*!< PPC not initialized */
};

/* ARM PPC names */
enum inph_ppc_name_t {
    AHB_PPC_XIP = 0,  /*!< AHB XIP */
    AHB_PPC_SDIO,     /*!< AHB PPC SDIO*/
    APB_PPC_PERIPH0,  /*!< PERIPHERAL0 PPC */
    AHB_PPC_PERIPH1,  /*!< PERIPHERAL1 PPC */
    AHB_PPC_SYSTEM,   /*!< AHB SYSTEM CONTROLLER PPC */
    APB_PPC_BASE0,    /*!< APB BASE0 PPC */
    APB_PPC_BASE1,    /*!< APB BASE1 PPC */
    APB_PPC_BASE2    /*!< APB BASE2 PPC */
};

/**
 * \brief Initialize the PPC device.
 *
 * \param[in] dev       PPC device \ref inph_ppc_dev_t
 * \param[in] ppc_name  PPC name \ref inph_ppc_name_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_ppc_init(struct inph_ppc_dev_t* dev,
                     enum inph_ppc_name_t ppc_name);

/**
 * \brief Configures the PPC device.
 *
 * \param[in] dev        PPC device \ref inph_ppc_dev_t
 * \param[in] periph     Peripheral position in the PPC.
 * \param[in] sec_attr   Secure attribute value.
 * \param[in] priv_attr  Privilege attribute value.
 *
 * \return Returns error code as specified in \ref inph_ppc_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_ppc_error_t inph_ppc_config_peripheral(
                                         struct inph_ppc_dev_t* dev,
                                         uint8_t periph,
                                         enum inph_ppc_sec_attr_t sec_attr,
                                         enum inph_ppc_priv_attr_t priv_attr);
/**
 * \brief Checks if the peripheral is configured as secure or non-secure.
 *
 * \param[in] dev     PPC device \ref inph_ppc_dev_t
 * \param[in] periph  Peripheral position in the PPC.
 *
 * \return Returns 1 for secure and 0 for non-secure.
 *         If the driver is not initalized the return value is 1 (secure) as
 *         it is the default system configuration.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t inph_ppc_is_periph_secure(struct inph_ppc_dev_t* dev,
                                     uint8_t periph);

/**
 * \brief Checks if the peripheral is configured as Privilege only or
 *        Privilege and non-Privilege access mode.
 *
 * \param[in] dev     PPC device \ref inph_ppc_dev_t
 * \param[in] periph  Peripheral position in the PPC.
 *
 * \return Returns 1 for Privilege only configuration and 0 for Privilege and
 *         non-Privilege access.
 *         If the driver is not initalized the return of this function is
 *         1 (Privilege only) as it is the default system configuration.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t inph_ppc_is_periph_priv_only(struct inph_ppc_dev_t* dev,
                                        uint8_t periph);
/**
 * \brief Enables PPC interrupt.
 *
 * \param[in] dev  PPC device \ref inph_ppc_dev_t
 *
 * \return Returns error code as specified in \ref inph_ppc_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum inph_ppc_error_t inph_ppc_irq_enable(struct inph_ppc_dev_t* dev);

/**
 * \brief Disables PPC interrupt.
 *
 * \param[in] dev  PPC device \ref inph_ppc_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_ppc_irq_disable(struct inph_ppc_dev_t* dev);

/**
 * \brief Clears PPC interrupt.
 *
 * \param[in] dev  PPC device \ref inph_ppc_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void inph_ppc_clear_irq(struct inph_ppc_dev_t* dev);

/**
 * \brief Returns the PPC interrupt state.
 *
 * \param[in] dev  PPC device \ref inph_ppc_dev_t
 *
 * \return Returns 1 if the interrupt is active and otherwise 0.
 *         If the driver is not initalized the return of this function is
 *         0 (not active) as it is the default system configuration.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t inph_ppc_irq_state(struct inph_ppc_dev_t* dev);

#endif /* __INPH_PPC_DRV_H__ */
