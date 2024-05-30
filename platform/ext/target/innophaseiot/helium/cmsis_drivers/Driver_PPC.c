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

/* APB PPCEXP2 Driver wrapper functions */
static int32_t APB_PPCHLMA0_Initialize(void)
{
    inph_ppc_init(&APB_PPCHLMA0_DEV_S, APB_PPC_EXP2);//APB_PPCEXP2_DEV_S

    return ARM_DRIVER_OK;
}

static int32_t APB_PPCHLMA0_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t APB_PPCHLMA0_ConfigPeriph(uint8_t periph,
                                        ARM_PPC_SecAttr sec_attr,
                                        ARM_PPC_PrivAttr priv_attr)
{
    inph_ppc_config_peripheral(&APB_PPCHLMA0_DEV_S, periph,
                                 (enum ppc_sse200_sec_attr_t)sec_attr,
                                 (enum ppc_sse200_priv_attr_t)priv_attr);

    return ARM_DRIVER_OK;
}

static uint32_t APB_PPCHLMA0_IsPeriphSecure(uint8_t periph)
{
    return inph_ppc_is_periph_secure(&APB_PPCHLMA0_DEV_S, periph);
}

static uint32_t APB_PPCHLMA0_IsPeriphPrivOnly(uint8_t periph)
{
    return inph_ppc_is_periph_priv_only(&APB_PPCHLMA0_DEV_S, periph);
}

static int32_t APB_PPCHLMA0_EnableInterrupt(void)
{
    enum ppc_sse200_error_t ret;

    ret = inph_ppc_irq_enable(&APB_PPCHLMA0_DEV_S);

    if( ret != PPC_SSE200_ERR_NONE) {
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;
}

static void APB_PPCHLMA0_DisableInterrupt(void)
{
    inph_ppc_irq_disable(&APB_PPCHLMA0_DEV_S);
}

static void APB_PPCHLMA0_ClearInterrupt(void)
{
    inph_ppc_clear_irq(&APB_PPCHLMA0_DEV_S);
}

static uint32_t APB_PPCHLMA0_InterruptState(void)
{
    return inph_ppc_irq_state(&APB_PPCHLMA0_DEV_S);
}

//Helium A0 driver structure
ARM_DRIVER_PPC Driver_APB_PPCHLMA0 = {
    .GetVersion        = INPH_PPC_GetVersion,
    .Initialize        = APB_PPCHLMA0_Initialize,
    .Uninitialize      = APB_PPCHLMA0_Uninitialize,
    .ConfigPeriph      = APB_PPCHLMA0_ConfigPeriph,
    .IsPeriphSecure    = APB_PPCHLMA0_IsPeriphSecure,
    .IsPeriphPrivOnly  = APB_PPCHLMA0_IsPeriphPrivOnly,
    .EnableInterrupt   = APB_PPCHLMA0_EnableInterrupt,
    .DisableInterrupt  = APB_PPCHLMA0_DisableInterrupt,
    .ClearInterrupt    = APB_PPCHLMA0_ClearInterrupt,
    .InterruptState    = APB_PPCHLMA0_InterruptState
};
//#endif /* INPH_HELIUM_A0 */

