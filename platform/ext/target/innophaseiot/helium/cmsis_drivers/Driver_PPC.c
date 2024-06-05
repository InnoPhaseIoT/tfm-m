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

#include "tfm_hal_device_header.h"
#include "platform_retarget_dev.h"
#include "inph_device.h"

/* Driver version */
#define INPH_PPC_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)
#define INPH_PPC_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)
#define INPH_DRIVER_VERSION ARM_DRIVER_VERSION

/* Driver Version */
static const INPH_DRIVER_VERSION DriverVersion = {
    INPH_PPC_API_VERSION,
    INPH_PPC_DRV_VERSION
};

static INPH_DRIVER_VERSION INPH_PPC_GetVersion(void)
{
    return DriverVersion;
}

//#if (INPH_HELIUM_A0)

/* APB Hellium A0 Driver wrapper functions */
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
                                         enum inph_ppc_sec_attr_t sec_attr,
                                         enum inph_ppc_sec_attr_t priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCBASE0_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_sec_attr_t)priv_attr);

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
    enum ppc_sse200_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCBASE0_DEV_S);

    if( ret != PPC_SSE200_ERR_NONE) {
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
    inph_ppc_init(&APB_PPCBASE0_DEV_S, APB_PPC_BASE0);

    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE1_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE1_ConfigPeriph(uint8_t periph,
                                         enum inph_ppc_sec_attr_t sec_attr,
                                         enum inph_ppc_sec_attr_t priv_attr)
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
    enum ppc_sse200_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCBASE1_DEV_S);

    if( ret != PPC_SSE200_ERR_NONE) {
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
    inph_ppc_init(&APB_PPCBASE0_DEV_S, APB_PPC_BASE0);

    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE2_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_PPCBASE2_ConfigPeriph(uint8_t periph,
                                         enum inph_ppc_sec_attr_t sec_attr,
                                         enum inph_ppc_sec_attr_t priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCBASE2_DEV_S, periph,
                                 (enum inph_ppc_sec_attr_t)sec_attr,
                                 (enum inph_ppc_sec_attr_t)priv_attr);

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
    enum ppc_sse200_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCBASE2_DEV_S);

    if( ret != PPC_SSE200_ERR_NONE) {
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
//#endif /* INPH_HELIUM_A0 */

