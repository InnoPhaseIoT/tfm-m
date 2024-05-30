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
 * @file    Driver_MPC.c
 * @author  InnophaseIOT Firmware Team
 * @brief   MPC top driver
 */

#include "Driver_MPC.h"

#include "tfm_hal_device_header.h"
//#include "platform_retarget_dev.h"
#include "inph_device.h"
#include "RTE_Device.h"

/* driver version */
#define INPH_MPC_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)
#define INPH_MPC_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    INPH_MPC_API_VERSION,
    INPH_MPC_DRV_VERSION
};

static ARM_DRIVER_VERSION INPH_MPC_GetVersion(void)
{
    return DriverVersion;
}

/*
 * \brief Translates error codes from native API to CMSIS API.
 *
 * \param[in] err  Error code to translate (\ref inph_mpc_sie200_error_t).
 *
 * \return Returns CMSIS error code.
 */
static int32_t inph_error_codes(enum inph_mpc_sie200_error_t err)
{
    switch(err) {
    case INPH_MPC_SIE200_ERR_NONE:
        return ARM_DRIVER_OK;
    case INPH_MPC_SIE200_INVALID_ARG:
        return ARM_DRIVER_ERROR_PARAMETER;
    case INPH_MPC_SIE200_NOT_INIT:
        return ARM_MPC_ERR_NOT_INIT;
    case INPH_MPC_SIE200_ERR_NOT_IN_RANGE:
        return ARM_MPC_ERR_NOT_IN_RANGE;
    case INPH_MPC_SIE200_ERR_NOT_ALIGNED:
        return ARM_MPC_ERR_NOT_ALIGNED;
    case INPH_MPC_SIE200_ERR_INVALID_RANGE:
        return ARM_MPC_ERR_INVALID_RANGE;
    case INPH_MPC_SIE200_ERR_RANGE_SEC_ATTR_NON_COMPATIBLE:
        return ARM_MPC_ERR_RANGE_SEC_ATTR_NON_COMPATIBLE;
    /* default:  The default is not defined intentionally to force the
     *           compiler to check that all the enumeration values are
     *           covered in the switch.
	 */
    }
}

//#if (INPH_MPC_SRAM1_S)
/* Ranges controlled by this SRAM1_MPC */
static struct inph_mpc_sie200_memory_range_t INPH_MPC_SRAM1_RANGE_S = {
    .base  = INPH_MPC_SRAM1_RANGE_BASE_S,
    .limit = INPH_MPC_SRAM1_RANGE_LIMIT_S,
    .attr  = INPH_MPC_SIE200_SEC_ATTR_SECURE
};

static struct inph_mpc_sie200_memory_range_t INPH_MPC_SRAM1_RANGE_NS = {
    .base  = INPH_MPC_SRAM1_RANGE_BASE_NS,
    .limit = INPH_MPC_SRAM1_RANGE_LIMIT_NS,
    .attr  = INPH_MPC_SIE200_SEC_ATTR_NONSECURE
};

#define INPH_MPC_SRAM1_RANGE_LIST_LEN  2u
static const struct  inph_mpc_sie200_memory_range_t* INPH_MPC_SRAM1_RANGE_LIST[INPH_MPC_SRAM1_RANGE_LIST_LEN]=
    {&INPH_MPC_SRAM1_RANGE_S, &INPH_MPC_SRAM1_RANGE_NS};

/* SRAM1_MPC Driver wrapper functions */
static int32_t INPH_MPC_SRAM1_Initialize(void)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_init(&INPH_MPC_SRAM1_DEV_S,
                          INPH_MPC_SRAM1_RANGE_LIST,
                          INPH_MPC_SRAM1_RANGE_LIST_LEN);

    return inph_error_codes(ret);
}

static int32_t INPH_MPC_SRAM1_Uninitialize(void)
{
    /* Nothing to be done */
    return ARM_DRIVER_OK;
}

static int32_t INPH_MPC_SRAM1_GetBlockSize(uint32_t* blk_size)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_get_block_size(&INPH_MPC_SRAM1_DEV_S, blk_size);

    return inph_error_codes(ret);
}

static int32_t INPH_MPC_SRAM1_GetCtrlConfig(uint32_t* ctrl_val)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_get_ctrl(&INPH_MPC_SRAM1_DEV_S, ctrl_val);

    return inph_error_codes(ret);
}

static int32_t INPH_MPC_SRAM1_SetCtrlConfig(uint32_t ctrl)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_set_ctrl(&INPH_MPC_SRAM1_DEV_S, ctrl);

    return inph_error_codes(ret);
}

static int32_t INPH_MPC_SRAM1_GetRegionConfig(uintptr_t base,
                                         uintptr_t limit,
                                         ARM_MPC_SEC_ATTR* attr)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_get_region_config(&INPH_MPC_SRAM1_DEV_S, base, limit,
                                       (enum inph_mpc_sie200_sec_attr_t*)attr);

    return inph_error_codes(ret);
}

static int32_t INPH_MPC_SRAM1_ConfigRegion(uintptr_t base,
                                      uintptr_t limit,
                                      ARM_MPC_SEC_ATTR attr)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_config_region(&INPH_MPC_SRAM1_DEV_S, base, limit,
                                   (enum inph_mpc_sie200_sec_attr_t)attr);

    return inph_error_codes(ret);
}

static int32_t INPH_MPC_SRAM1_EnableInterrupt(void)
{
    enum inph_mpc_sie200_error_t ret;

    ret = inph_mpc_sie200_irq_enable(&INPH_MPC_SRAM1_DEV_S);

    return inph_error_codes(ret);
}

static void INPH_MPC_SRAM1_DisableInterrupt(void)
{
    inph_mpc_sie200_irq_disable(&INPH_MPC_SRAM1_DEV_S);
}


static void INPH_MPC_SRAM1_ClearInterrupt(void)
{
    inph_mpc_sie200_clear_irq(&INPH_MPC_SRAM1_DEV_S);
}

static uint32_t INPH_MPC_SRAM1_InterruptState(void)
{
    return inph_mpc_sie200_irq_state(&INPH_MPC_SRAM1_DEV_S);
}

static int32_t INPH_MPC_SRAM1_LockDown(void)
{
    return inph_mpc_sie200_lock_down(&INPH_MPC_SRAM1_DEV_S);
}

/* SRAM1_MPC Driver CMSIS access structure */
extern ARM_DRIVER_MPC INPH_DRIVER_MPC_SRAM1;
ARM_DRIVER_MPC INPH_DRIVER_MPC_SRAM1 = {
    .GetVersion       = INPH_MPC_GetVersion,
    .Initialize       = INPH_MPC_SRAM1_Initialize,
    .Uninitialize     = INPH_MPC_SRAM1_Uninitialize,
    .GetBlockSize     = INPH_MPC_SRAM1_GetBlockSize,
    .GetCtrlConfig    = INPH_MPC_SRAM1_GetCtrlConfig,
    .SetCtrlConfig    = INPH_MPC_SRAM1_SetCtrlConfig,
    .ConfigRegion     = INPH_MPC_SRAM1_ConfigRegion,
    .GetRegionConfig  = INPH_MPC_SRAM1_GetRegionConfig,
    .EnableInterrupt  = INPH_MPC_SRAM1_EnableInterrupt,
    .DisableInterrupt = INPH_MPC_SRAM1_DisableInterrupt,
    .ClearInterrupt   = INPH_MPC_SRAM1_ClearInterrupt,
    .InterruptState   = INPH_MPC_SRAM1_InterruptState,
    .LockDown         = INPH_MPC_SRAM1_LockDown,
};
//#endif /* INPH_MPC_SRAM1_S */

