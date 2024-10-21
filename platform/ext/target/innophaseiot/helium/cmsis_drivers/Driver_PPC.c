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
 * @file    Driver_PPC.c
 * @author  InnophaseIOT Firmware Team
 * @brief   Provides functions for Peripheral Protection
 */

#include "Driver_PPC.h"

#include "RTE_Device.h"
#include "platform_retarget_dev.h"
#include "platform_retarget.h"
#include "inph_ppc_drv.h"

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_DRIVER_VERSION_MAJOR_MINOR(1,0),
    ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)
};

static ARM_DRIVER_VERSION INPH_PPC_GetVersion(void)
{
    return DriverVersion;
}

//#if (INPH_HELIUM_A0)

/* PPC control for BASE0 peripherals */

static int32_t APB_PPCBASE0_Initialize(void)
{
    inph_ppc_init(&APB_PPCBASE0_DEV_S, APB_PPC_BASE0);

    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE0_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE0_ConfigPeriph(uint8_t periph,
                                         ARM_PPC_SecAttr sec_attr,
                                         ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCBASE0_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t APB_PPCBASE0_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&APB_PPCBASE0_DEV_S, periph);
}

static uint32_t APB_PPCBASE0_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&APB_PPCBASE0_DEV_S, periph);
}

static int32_t APB_PPCBASE0_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCBASE0_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;
}

static void APB_PPCBASE0_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&APB_PPCBASE0_DEV_S);
}

static void APB_PPCBASE0_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&APB_PPCBASE0_DEV_S);
}

static uint32_t APB_PPCBASE0_InterruptState(void)
{
    return inph_ppc_irq_state(&APB_PPCBASE0_DEV_S);
}

//Helium A0 driver structure
ARM_DRIVER_PPC Driver_APB_PPCBASE0 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = APB_PPCBASE0_Initialize,
    .Uninitialize      = APB_PPCBASE0_Uninitialize,
    .ConfigPeriph      = APB_PPCBASE0_ConfigPeriph,
    .IsPeriphSecure    = APB_PPCBASE0_IsPeriphSecure,
    .IsPeriphPrivOnly  = APB_PPCBASE0_IsPeriphPrivOnly,
    .EnableInterrupt   = APB_PPCBASE0_EnableInterrupt,
    .DisableInterrupt  = APB_PPCBASE0_DisableInterrupt,
    .ClearInterrupt    = APB_PPCBASE0_ClearInterrupt,
    .InterruptState    = APB_PPCBASE0_InterruptState
};

static int32_t APB_PPCBASE1_Initialize(void)
{
    inph_ppc_init(&APB_PPCBASE1_DEV_S, APB_PPC_BASE1);

    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE1_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE1_ConfigPeriph(uint8_t periph,
                                         ARM_PPC_SecAttr sec_attr,
                                         ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCBASE1_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_sec_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t APB_PPCBASE1_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&APB_PPCBASE1_DEV_S, periph);
}

static uint32_t APB_PPCBASE1_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&APB_PPCBASE1_DEV_S, periph);
}

static int32_t APB_PPCBASE1_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCBASE1_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;
}

static void APB_PPCBASE1_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&APB_PPCBASE1_DEV_S);
}

static void APB_PPCBASE1_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&APB_PPCBASE1_DEV_S);
}

static uint32_t APB_PPCBASE1_InterruptState(void)
{
    return inph_ppc_irq_state(&APB_PPCBASE1_DEV_S);
}

//Helium A0 driver structure
ARM_DRIVER_PPC Driver_APB_PPCBASE1 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = APB_PPCBASE1_Initialize,
    .Uninitialize      = APB_PPCBASE1_Uninitialize,
    .ConfigPeriph      = APB_PPCBASE1_ConfigPeriph,
    .IsPeriphSecure    = APB_PPCBASE1_IsPeriphSecure,
    .IsPeriphPrivOnly  = APB_PPCBASE1_IsPeriphPrivOnly,
    .EnableInterrupt   = APB_PPCBASE1_EnableInterrupt,
    .DisableInterrupt  = APB_PPCBASE1_DisableInterrupt,
    .ClearInterrupt    = APB_PPCBASE1_ClearInterrupt,
    .InterruptState    = APB_PPCBASE1_InterruptState
};

static int32_t APB_PPCBASE2_Initialize(void)
{
    inph_ppc_init(&APB_PPCBASE2_DEV_S, APB_PPC_BASE2);

    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE2_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE2_ConfigPeriph(uint8_t periph,
                                         ARM_PPC_SecAttr sec_attr,
                                         ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCBASE2_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t APB_PPCBASE2_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&APB_PPCBASE2_DEV_S, periph);
}

static uint32_t APB_PPCBASE2_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&APB_PPCBASE2_DEV_S, periph);
}

static int32_t APB_PPCBASE2_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCBASE2_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;
}

static void APB_PPCBASE2_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&APB_PPCBASE2_DEV_S);
}

static void APB_PPCBASE2_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&APB_PPCBASE2_DEV_S);
}

static uint32_t APB_PPCBASE2_InterruptState(void)
{
    return inph_ppc_irq_state(&APB_PPCBASE2_DEV_S);
}

//Helium A0 driver structure
ARM_DRIVER_PPC Driver_APB_PPCBASE2 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = APB_PPCBASE2_Initialize,
    .Uninitialize      = APB_PPCBASE2_Uninitialize,
    .ConfigPeriph      = APB_PPCBASE2_ConfigPeriph,
    .IsPeriphSecure    = APB_PPCBASE2_IsPeriphSecure,
    .IsPeriphPrivOnly  = APB_PPCBASE2_IsPeriphPrivOnly,
    .EnableInterrupt   = APB_PPCBASE2_EnableInterrupt,
    .DisableInterrupt  = APB_PPCBASE2_DisableInterrupt,
    .ClearInterrupt    = APB_PPCBASE2_ClearInterrupt,
    .InterruptState    = APB_PPCBASE2_InterruptState
};


/* PPC controller for Peripheral APB System Control */

static int32_t APB_SYSCNTRL_Initialize(void)
{
    inph_ppc_init(&APB_PPCSYSTEM_DEV_S, APB_PPC_SYSTEM);

    return ARM_DRIVER_OK;
}

static int32_t APB_SYSCNTRL_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_SYSCNTRL_ConfigPeriph(uint8_t periph,
                                         ARM_PPC_SecAttr sec_attr,
                                         ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCSYSTEM_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t APB_SYSCNTRL_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&APB_PPCSYSTEM_DEV_S, periph);
}

static uint32_t APB_SYSCNTRL_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&APB_PPCSYSTEM_DEV_S, periph);
}

static int32_t APB_SYSCNTRL_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCSYSTEM_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void APB_SYSCNTRL_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&APB_PPCSYSTEM_DEV_S);
}

static void APB_SYSCNTRL_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&APB_PPCSYSTEM_DEV_S);
}

static uint32_t APB_SYSCNTRL_InterruptState(void)
{
    return inph_ppc_irq_state(&APB_PPCSYSTEM_DEV_S);
}

ARM_DRIVER_PPC Driver_APB_SYSCNTRL = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = APB_SYSCNTRL_Initialize,
    .Uninitialize      = APB_SYSCNTRL_Uninitialize,
    .ConfigPeriph      = APB_SYSCNTRL_ConfigPeriph,
    .IsPeriphSecure    = APB_SYSCNTRL_IsPeriphSecure,
    .IsPeriphPrivOnly  = APB_SYSCNTRL_IsPeriphPrivOnly,
    .EnableInterrupt   = APB_SYSCNTRL_EnableInterrupt,
    .DisableInterrupt  = APB_SYSCNTRL_DisableInterrupt,
    .ClearInterrupt    = APB_SYSCNTRL_ClearInterrupt,
    .InterruptState    = APB_SYSCNTRL_InterruptState
};

/* PPC controller for Peripheral AHB System Control */

static int32_t AHB_SYSCNTRL_Initialize(void)
{
    inph_ppc_init(&AHB_PPCSYSTEM_DEV_S, AHB_PPC_SYSTEM);

    return ARM_DRIVER_OK;
}

static int32_t AHB_SYSCNTRL_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t AHB_SYSCNTRL_ConfigPeriph(uint8_t periph,
                                         ARM_PPC_SecAttr sec_attr,
                                         ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&AHB_PPCSYSTEM_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t AHB_SYSCNTRL_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&AHB_PPCSYSTEM_DEV_S, periph);
}

static uint32_t AHB_SYSCNTRL_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&AHB_PPCSYSTEM_DEV_S, periph);
}

static int32_t AHB_SYSCNTRL_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&AHB_PPCSYSTEM_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void AHB_SYSCNTRL_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&AHB_PPCSYSTEM_DEV_S);
}

static void AHB_SYSCNTRL_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&AHB_PPCSYSTEM_DEV_S);
}

static uint32_t AHB_SYSCNTRL_InterruptState(void)
{
    return inph_ppc_irq_state(&AHB_PPCSYSTEM_DEV_S);
}

ARM_DRIVER_PPC Driver_AHB_SYSCNTRL = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = AHB_SYSCNTRL_Initialize,
    .Uninitialize      = AHB_SYSCNTRL_Uninitialize,
    .ConfigPeriph      = AHB_SYSCNTRL_ConfigPeriph,
    .IsPeriphSecure    = AHB_SYSCNTRL_IsPeriphSecure,
    .IsPeriphPrivOnly  = AHB_SYSCNTRL_IsPeriphPrivOnly,
    .EnableInterrupt   = AHB_SYSCNTRL_EnableInterrupt,
    .DisableInterrupt  = AHB_SYSCNTRL_DisableInterrupt,
    .ClearInterrupt    = AHB_SYSCNTRL_ClearInterrupt,
    .InterruptState    = AHB_SYSCNTRL_InterruptState
};

/* PPC controller for Peripheral0 */

static int32_t AHB_PERIPHERAL0_Initialize(void)
{
    inph_ppc_init(&AHB_PPCPERIPH0_DEV_S, AHB_PPC_PERIPH0);

    return ARM_DRIVER_OK;
}

static int32_t AHB_PERIPHERAL0_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t AHB_PERIPHERAL0_ConfigPeriph(uint8_t periph,
                                      ARM_PPC_SecAttr sec_attr,
                                      ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&AHB_PPCPERIPH0_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t AHB_PERIPHERAL0_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&AHB_PPCPERIPH0_DEV_S, periph);
}

static uint32_t AHB_PERIPHERAL0_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&AHB_PPCPERIPH0_DEV_S, periph);
}

static int32_t AHB_PERIPHERAL0_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&AHB_PPCPERIPH0_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void AHB_PERIPHERAL0_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&AHB_PPCPERIPH0_DEV_S);
}

static void AHB_PERIPHERAL0_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&AHB_PPCPERIPH0_DEV_S);
}

static uint32_t AHB_PERIPHERAL0_InterruptState(void)
{
    return inph_ppc_irq_state(&AHB_PPCPERIPH0_DEV_S);
}

ARM_DRIVER_PPC Driver_AHB_PERIPHERAL0 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = AHB_PERIPHERAL0_Initialize,
    .Uninitialize      = AHB_PERIPHERAL0_Uninitialize,
    .ConfigPeriph      = AHB_PERIPHERAL0_ConfigPeriph,
    .IsPeriphSecure    = AHB_PERIPHERAL0_IsPeriphSecure,
    .IsPeriphPrivOnly  = AHB_PERIPHERAL0_IsPeriphPrivOnly,
    .EnableInterrupt   = AHB_PERIPHERAL0_EnableInterrupt,
    .DisableInterrupt  = AHB_PERIPHERAL0_DisableInterrupt,
    .ClearInterrupt    = AHB_PERIPHERAL0_ClearInterrupt,
    .InterruptState    = AHB_PERIPHERAL0_InterruptState
};

/* PPC controller for Peripheral1 */

static int32_t AHB_PERIPHERAL1_Initialize(void)
{
    inph_ppc_init(&AHB_PPCPERIPH1_DEV_S, AHB_PPC_PERIPH1);

    return ARM_DRIVER_OK;
}

static int32_t AHB_PERIPHERAL1_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t AHB_PERIPHERAL1_ConfigPeriph(uint8_t periph,
                                      ARM_PPC_SecAttr sec_attr,
                                      ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&AHB_PPCPERIPH1_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t AHB_PERIPHERAL1_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&AHB_PPCPERIPH1_DEV_S, periph);
}

static uint32_t AHB_PERIPHERAL1_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&AHB_PPCPERIPH1_DEV_S, periph);
}

static int32_t AHB_PERIPHERAL1_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&AHB_PPCPERIPH1_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void AHB_PERIPHERAL1_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&AHB_PPCPERIPH1_DEV_S);
}

static void AHB_PERIPHERAL1_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&AHB_PPCPERIPH1_DEV_S);
}

static uint32_t AHB_PERIPHERAL1_InterruptState(void)
{
    return inph_ppc_irq_state(&AHB_PPCPERIPH1_DEV_S);
}

ARM_DRIVER_PPC Driver_AHB_PERIPHERAL1 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = AHB_PERIPHERAL1_Initialize,
    .Uninitialize      = AHB_PERIPHERAL1_Uninitialize,
    .ConfigPeriph      = AHB_PERIPHERAL1_ConfigPeriph,
    .IsPeriphSecure    = AHB_PERIPHERAL1_IsPeriphSecure,
    .IsPeriphPrivOnly  = AHB_PERIPHERAL1_IsPeriphPrivOnly,
    .EnableInterrupt   = AHB_PERIPHERAL1_EnableInterrupt,
    .DisableInterrupt  = AHB_PERIPHERAL1_DisableInterrupt,
    .ClearInterrupt    = AHB_PERIPHERAL1_ClearInterrupt,
    .InterruptState    = AHB_PERIPHERAL1_InterruptState
};

/* PPC controller for SDIO */

static int32_t AHB_SDIO_Initialize(void)
{
    inph_ppc_init(&AHB_PPCSDIO_DEV_S, AHB_PPC_SDIO);

    return ARM_DRIVER_OK;
}

static int32_t AHB_SDIO_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t AHB_SDIO_ConfigPeriph(uint8_t periph,
                                     ARM_PPC_SecAttr sec_attr,
                                     ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&AHB_PPCSDIO_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t AHB_SDIO_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&AHB_PPCSDIO_DEV_S, periph);
}

static uint32_t AHB_SDIO_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&AHB_PPCSDIO_DEV_S, periph);
}

static int32_t AHB_SDIO_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&AHB_PPCSDIO_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void AHB_SDIO_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&AHB_PPCSDIO_DEV_S);
}

static void AHB_SDIO_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&AHB_PPCSDIO_DEV_S);
}

static uint32_t AHB_SDIO_InterruptState(void)
{
    return inph_ppc_irq_state(&AHB_PPCSDIO_DEV_S);
}

ARM_DRIVER_PPC Driver_AHB_SDIO = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = AHB_SDIO_Initialize,
    .Uninitialize      = AHB_SDIO_Uninitialize,
    .ConfigPeriph      = AHB_SDIO_ConfigPeriph,
    .IsPeriphSecure    = AHB_SDIO_IsPeriphSecure,
    .IsPeriphPrivOnly  = AHB_SDIO_IsPeriphPrivOnly,
    .EnableInterrupt   = AHB_SDIO_EnableInterrupt,
    .DisableInterrupt  = AHB_SDIO_DisableInterrupt,
    .ClearInterrupt    = AHB_SDIO_ClearInterrupt,
    .InterruptState    = AHB_SDIO_InterruptState
};

/* PPC controller for XIP1 */

static int32_t AHB_XIP1_Initialize(void)
{
    inph_ppc_init(&AHB_PPCCXIP1_DEV_S, AHB_PPC_XIP1);

    return ARM_DRIVER_OK;
}

static int32_t AHB_XIP1_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t AHB_XIP1_ConfigPeriph(uint8_t periph,
                                     ARM_PPC_SecAttr sec_attr,
                                     ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&AHB_PPCCXIP1_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t AHB_XIP1_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&AHB_PPCCXIP1_DEV_S, periph);
}

static uint32_t AHB_XIP1_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&AHB_PPCCXIP1_DEV_S, periph);
}

static int32_t AHB_XIP1_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&AHB_PPCCXIP1_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void AHB_XIP1_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&AHB_PPCCXIP1_DEV_S);
}

static void AHB_XIP1_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&AHB_PPCCXIP1_DEV_S);
}

static uint32_t AHB_XIP1_InterruptState(void)
{
    return inph_ppc_irq_state(&AHB_PPCCXIP1_DEV_S);
}

ARM_DRIVER_PPC Driver_AHB_XIP1 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = AHB_XIP1_Initialize,
    .Uninitialize      = AHB_XIP1_Uninitialize,
    .ConfigPeriph      = AHB_XIP1_ConfigPeriph,
    .IsPeriphSecure    = AHB_XIP1_IsPeriphSecure,
    .IsPeriphPrivOnly  = AHB_XIP1_IsPeriphPrivOnly,
    .EnableInterrupt   = AHB_XIP1_EnableInterrupt,
    .DisableInterrupt  = AHB_XIP1_DisableInterrupt,
    .ClearInterrupt    = AHB_XIP1_ClearInterrupt,
    .InterruptState    = AHB_XIP1_InterruptState
};

/* PPC controller for XIP2 */

static int32_t AHB_XIP2_Initialize(void)
{
    inph_ppc_init(&AHB_PPCCXIP2_DEV_S, AHB_PPC_XIP2);

    return ARM_DRIVER_OK;
}

static int32_t AHB_XIP2_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t AHB_XIP2_ConfigPeriph(uint8_t periph,
                                     ARM_PPC_SecAttr sec_attr,
                                     ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&AHB_PPCCXIP2_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t AHB_XIP2_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&AHB_PPCCXIP2_DEV_S, periph);
}

static uint32_t AHB_XIP2_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&AHB_PPCCXIP2_DEV_S, periph);
}

static int32_t AHB_XIP2_EnableInterrupt(void)
{
    enum inph_ppc_error_t ret;

    ret = inph_ppc_irq_enable(&AHB_PPCCXIP2_DEV_S);

    if( ret != INPH_PPC_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

return ARM_DRIVER_OK;
}

static void AHB_XIP2_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&AHB_PPCCXIP2_DEV_S);
}

static void AHB_XIP2_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&AHB_PPCCXIP2_DEV_S);
}

static uint32_t AHB_XIP2_InterruptState(void)
{
    return inph_ppc_irq_state(&AHB_PPCCXIP2_DEV_S);
}

ARM_DRIVER_PPC Driver_AHB_XIP2 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = AHB_XIP2_Initialize,
    .Uninitialize      = AHB_XIP2_Uninitialize,
    .ConfigPeriph      = AHB_XIP2_ConfigPeriph,
    .IsPeriphSecure    = AHB_XIP2_IsPeriphSecure,
    .IsPeriphPrivOnly  = AHB_XIP2_IsPeriphPrivOnly,
    .EnableInterrupt   = AHB_XIP2_EnableInterrupt,
    .DisableInterrupt  = AHB_XIP2_DisableInterrupt,
    .ClearInterrupt    = AHB_XIP2_ClearInterrupt,
    .InterruptState    = AHB_XIP2_InterruptState
};

