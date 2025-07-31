/*
 * Copyright (c) 2017-2024, Arm Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tfm_hal_device_header.h"
#include "fih.h"
#include "target_cfg.h"
#include "Driver_MPC.h"
#include "Driver_PPC.h"
#include "platform_retarget_dev.h"
#include "region_defs.h"
#include "tfm_plat_defs.h"
#include "region.h"
#include "platform_regs.h"
#include "utilities.h"

#ifdef PSA_API_TEST_IPC
#endif

#pragma GCC push_options
#pragma GCC optimize ("O0")

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/* The section names come from the scatter file */
REGION_DECLARE(Load$$LR$$, LR_NS_PARTITION, $$Base);
REGION_DECLARE(Image$$, ER_VENEER, $$Base);
REGION_DECLARE(Image$$, VENEER_ALIGN, $$Limit);

#ifdef BL2
REGION_DECLARE(Load$$LR$$, LR_SECONDARY_PARTITION, $$Base);
#endif /* BL2 */

const struct memory_region_limits memory_regions = {
    .non_secure_code_start =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base) +
        BL2_HEADER_SIZE,

    .non_secure_partition_base =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base),

    .non_secure_partition_limit =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base) +
        NS_PARTITION_SIZE - 1,

    .veneer_base = (uint32_t)&REGION_NAME(Image$$, ER_VENEER, $$Base),
    .veneer_limit = (uint32_t)&REGION_NAME(Image$$, VENEER_ALIGN, $$Limit),

#ifdef BL2
    .secondary_partition_base =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_SECONDARY_PARTITION, $$Base),

    .secondary_partition_limit =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_SECONDARY_PARTITION, $$Base) +
        SECONDARY_PARTITION_SIZE - 1,
#endif /* BL2 */
};

/* Allows software, via SAU, to define the code region as a NSC */
#define NSCCFG_CODENSC  1

/* Import MPC driver */
extern ARM_DRIVER_MPC Driver_SRAM0_MPC;
extern ARM_DRIVER_MPC Driver_SRAM1_MPC;
extern ARM_DRIVER_MPC Driver_SRAM2_MPC;
#if 1
extern ARM_DRIVER_MPC Driver_SRAM3_MPC;
extern ARM_DRIVER_MPC Driver_SRAM4_MPC;
extern ARM_DRIVER_MPC Driver_SRAM5_MPC;
extern ARM_DRIVER_MPC Driver_SRAM6_MPC;
extern ARM_DRIVER_MPC Driver_SRAM7_MPC;
extern ARM_DRIVER_MPC Driver_SRAM8_MPC;
extern ARM_DRIVER_MPC Driver_SRAM9_MPC;
extern ARM_DRIVER_MPC Driver_SRAM10_MPC;
extern ARM_DRIVER_MPC Driver_SRAM11_MPC;
extern ARM_DRIVER_MPC Driver_SRAM12_MPC;
extern ARM_DRIVER_MPC Driver_SRAM13_MPC;
extern ARM_DRIVER_MPC Driver_SRAM14_MPC;
extern ARM_DRIVER_MPC Driver_SRAM15_MPC;
#endif
extern ARM_DRIVER_MPC Driver_XSPI1_MPC;
extern ARM_DRIVER_MPC Driver_XSPI2_MPC;
extern ARM_DRIVER_MPC Driver_ROM_MPC;

/* Import PPC drivers */
extern ARM_DRIVER_PPC Driver_APB_PPCBASE0;
extern ARM_DRIVER_PPC Driver_APB_PPCBASE1;
extern ARM_DRIVER_PPC Driver_APB_PPCBASE2;
extern ARM_DRIVER_PPC Driver_APB_SYSCNTRL;
extern ARM_DRIVER_PPC Driver_AHB_SYSCNTRL;
extern ARM_DRIVER_PPC Driver_AHB_PERIPHERAL0;
extern ARM_DRIVER_PPC Driver_AHB_PERIPHERAL1;
extern ARM_DRIVER_PPC Driver_AHB_SDIO;
extern ARM_DRIVER_PPC Driver_AHB_XIP1;
extern ARM_DRIVER_PPC Driver_AHB_XIP2;

/* Define Peripherals NS address range for the platform */
#define PERIPHERALS_BASE_NS_START (0x40000000)
#define PERIPHERALS_BASE_NS_END   (0x4FFFFFFF)

static ARM_DRIVER_PPC *const ppc_bank_drivers[] = {
    &Driver_APB_PPCBASE0,
    &Driver_APB_PPCBASE1,
    &Driver_APB_PPCBASE2,
    &Driver_APB_SYSCNTRL,
    &Driver_AHB_SYSCNTRL,
    &Driver_AHB_PERIPHERAL0,
    &Driver_AHB_PERIPHERAL1,
    &Driver_AHB_SDIO,
    &Driver_AHB_XIP1,
    &Driver_AHB_XIP2,
};

#define PPC_BANK_COUNT (sizeof(ppc_bank_drivers)/sizeof(ppc_bank_drivers[0]))


/* To write into AIRCR register, 0x5FA value must be write to the VECTKEY field,
 * otherwise the processor ignores the write.
 */
#define SCB_AIRCR_WRITE_MASK ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos))

struct platform_data_t tfm_peripheral_std_uart = {
        INPH_UART0_BASE_NS,
        INPH_UART0_BASE_NS + 0xFFF,
        PPC_SP_DO_NOT_CONFIGURE,
        -1
};

struct platform_data_t tfm_peripheral_uart1 = {
        INPH_UART1_BASE_S,
        INPH_UART1_BASE_S + 0xFFF,
        AHB_PPC_PERIPH0,
        SPCNTL_PERIPH0_UART1_POS
};

struct platform_data_t tfm_peripheral_uart2 = {
        INPH_UART2_BASE_S,
        INPH_UART2_BASE_S + 0xFFF,
        AHB_PPC_PERIPH0,
        SPCNTL_PERIPH0_UART2_POS
};

#if 0
struct platform_data_t tfm_peripheral_timer0 = {
        CMSDK_TIMER0_BASE_S,
        CMSDK_TIMER1_BASE_S - 1,
        PPC_SP_APB_PPC0,
        CMSDK_TIMER0_APB_PPC_POS
};
#endif

#ifdef PSA_API_TEST_IPC

/* Below data structure are only used for PSA FF tests, and this pattern is
 * definitely not to be followed for real life use cases, as it can break
 * security.
 */


#endif

enum tfm_plat_err_t enable_fault_handlers(void)
{
    /* Explicitly set secure fault priority to the highest */
    NVIC_SetPriority(SecureFault_IRQn, 0);

    /* Enables BUS, MEM, USG and Secure faults */
    SCB->SHCSR    |= SCB_SHCSR_USGFAULTENA_Msk
                  | SCB_SHCSR_BUSFAULTENA_Msk
                  | SCB_SHCSR_MEMFAULTENA_Msk
                  | SCB_SHCSR_SECUREFAULTENA_Msk;
    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t system_reset_cfg(void)
{
    uint32_t reg_value = SCB->AIRCR;

    /* Clear SCB_AIRCR_VECTKEY value */
    reg_value &= ~(uint32_t)(SCB_AIRCR_VECTKEY_Msk);

    /* Enable system reset request only to the secure world */
    reg_value |= (uint32_t)(SCB_AIRCR_WRITE_MASK | SCB_AIRCR_SYSRESETREQS_Msk);

    SCB->AIRCR = reg_value;

    return TFM_PLAT_ERR_SUCCESS;
}

FIH_RET_TYPE(enum tfm_plat_err_t) init_debug(void)
{

    /*  fix me : not implemented yet (EIP)*/
    FIH_RET(fih_int_encode(TFM_PLAT_ERR_SUCCESS));
}

/*----------------- NVIC interrupt target state to NS configuration ----------*/
enum tfm_plat_err_t nvic_interrupt_target_state_cfg(void)
{
    /* Target every interrupt to NS; unimplemented interrupts will be WI */
    for (uint8_t i=0; i<sizeof(NVIC->ITNS)/sizeof(NVIC->ITNS[0]); i++) {
        NVIC->ITNS[i] = 0xFFFFFFFF;
    }

    /* Make sure that MPC and PPC are targeted to S state */
    NVIC_ClearTargetState(MPC_IRQn);
    NVIC_ClearTargetState(PPC_IRQn);

#ifdef SECURE_UART1
    /* UART1 is a secure peripheral, so its IRQs have to target S state */
    NVIC_ClearTargetState(UART_1_IRQn);
#endif

    return TFM_PLAT_ERR_SUCCESS;
}

/*----------------- NVIC interrupt enabling for S peripherals ----------------*/
enum tfm_plat_err_t nvic_interrupt_enable(void)
{
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    int32_t ret = ARM_DRIVER_OK;

    //ret = Driver_SRAM0_MPC.EnableInterrupt();
    //if (ret != ARM_DRIVER_OK) {
    //    return TFM_PLAT_ERR_SYSTEM_ERR;
    //} // MHK

    /* MPC interrupt enabling */
    ret = Driver_SRAM1_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM2_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM3_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM4_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    ret = Driver_SRAM5_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM6_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM7_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM8_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM9_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM10_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM11_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM12_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    ret = Driver_SRAM13_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM14_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_SRAM15_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_XSPI1_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_XSPI2_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    ret = Driver_ROM_MPC.EnableInterrupt();
    if (ret != ARM_DRIVER_OK) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    
    NVIC_EnableIRQ(MPC_IRQn);

    /* PPC interrupt enabling */
    /* Clear pending PPC interrupts */
 
    spctrl->SECPPCINTCLR.dw |= SPCNTL_BASE0_INT_POS_MASK |
                           SPCNTL_BASE1_INT_POS_MASK |
                           SPCNTL_BASE2_INT_POS_MASK |
                           SPCNTL_SYSAHB_INT_POS_MASK |
                           SPCNTL_SYSAPB_INT_POS_MASK |
                           SPCNTL_PERIPH0_INT_POS_MASK |
                           SPCNTL_PERIPH1_INT_POS_MASK |
                           SPCNTL_SDIO_INT_POS_MASK |
                           SPCNTL_CXIP1_INT_POS_MASK |
                           SPCNTL_CXIP2_INT_POS_MASK;

    /* Enable PPC interrupts for APB PPC */
    spctrl->SECPPCINTEN.dw |= SPCNTL_BASE0_INT_POS_MASK |
                           SPCNTL_BASE1_INT_POS_MASK |
                           SPCNTL_BASE2_INT_POS_MASK |
                           SPCNTL_SYSAHB_INT_POS_MASK |
                           SPCNTL_SYSAPB_INT_POS_MASK |
                           SPCNTL_PERIPH0_INT_POS_MASK |
                           SPCNTL_PERIPH1_INT_POS_MASK |
                           SPCNTL_SDIO_INT_POS_MASK |
                           SPCNTL_CXIP1_INT_POS_MASK |
                           SPCNTL_CXIP2_INT_POS_MASK;
                           

    NVIC_EnableIRQ(PPC_IRQn);

#ifdef PSA_FF_TEST_SECURE_UART2

#endif

    return TFM_PLAT_ERR_SUCCESS;
}

/*------------------- SAU/IDAU configuration functions -----------------------*/
#if defined(PSA_API_TEST_NS) && !defined(PSA_API_TEST_IPC)
#define DEV_APIS_TEST_NVMEM_REGION_START (NS_DATA_LIMIT + 1)
#define DEV_APIS_TEST_NVMEM_REGION_LIMIT \
    (DEV_APIS_TEST_NVMEM_REGION_START + DEV_APIS_TEST_NVMEM_REGION_SIZE - 1)
#endif

struct sau_cfg_t {
    uint32_t RBAR;
    uint32_t RLAR;
    bool nsc;
};

const struct sau_cfg_t sau_cfg[] = {
    {
        ((uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base)),
        ((uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base) +
        NS_PARTITION_SIZE - 1),
        false,
    },
#if 1
	{
        0x20050000,
        0x2009ffff,
        false,
    },
#endif
	{
        (uint32_t)&REGION_NAME(Image$$, ER_VENEER, $$Base),
        (uint32_t)&REGION_NAME(Image$$, VENEER_ALIGN, $$Limit) - 1,
        true,
    },
    {
        PERIPHERALS_BASE_NS_START,
#ifdef SECURE_UART1        
        (INPH_UART1_BASE_NS - 1),
        false,
    },
    {
        INPH_UART1_BASE_NS,
#endif
        PERIPHERALS_BASE_NS_END,
        false,
    },
#ifdef BL2
    {
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_SECONDARY_PARTITION, $$Base),
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_SECONDARY_PARTITION, $$Base) +
        SECONDARY_PARTITION_SIZE - 1,
        false,
    },
#endif
};

#define NR_SAU_INIT_STEP                 3

FIH_RET_TYPE(int32_t) sau_and_idau_cfg(void)
{
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    uint32_t i;

    /* Ensure all memory accesses are completed */
    __DMB();

    /* Enables SAU */
    TZ_SAU_Enable();

    for (i = 0; i < ARRAY_SIZE(sau_cfg); i++) {
        SAU->RNR = i;
        SAU->RBAR = sau_cfg[i].RBAR & SAU_RBAR_BADDR_Msk;
        SAU->RLAR = (sau_cfg[i].RLAR & SAU_RLAR_LADDR_Msk) |
                    (sau_cfg[i].nsc ? SAU_RLAR_NSC_Msk : 0U) |
                    SAU_RLAR_ENABLE_Msk;
    }

    /* Allows SAU to define the code region as a NSC */
    spctrl->NSCCFG.bf.CODENSC |= NSCCFG_CODENSC;

    /* Ensure the write is completed and flush pipeline */
    __DSB();
    __ISB();

    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}

#ifdef TFM_FIH_PROFILE_ON
fih_int fih_verify_sau_and_idau_cfg(void)
{
    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}
#endif /* TFM_FIH_PROFILE_ON */

/*------------------- Memory configuration functions -------------------------*/
#ifdef BL2
#define NR_MPC_INIT_STEP                 7
#else
#define NR_MPC_INIT_STEP                 6
#endif

FIH_RET_TYPE(int32_t) mpc_init_cfg(void)
{
    int32_t ret = ARM_DRIVER_OK;
    
    /* Configuring primary non-secure partition.
     * It is ensured in flash_layout.h that this memory region is located in
     * QSPI device. */
    ret = Driver_XSPI1_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        ERROR_MSG("Failed to Initialize MPC for QSPI1!");
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    ret = Driver_XSPI1_MPC.ConfigRegion( XSPI1_RANGE_BASE_NS, XSPI1_RANGE_LIMIT_NS,
                                      ARM_MPC_ATTR_NONSECURE);
    if (ret != ARM_DRIVER_OK) {
        ERROR_MSG("Failed to Configure MPC for QSPI1!");
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_XSPI1_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

//xSPI2
    ret = Driver_XSPI2_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        ERROR_MSG("Failed to Initialize MPC for QSPI2!");
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    ret = Driver_XSPI2_MPC.ConfigRegion( XSPI2_RANGE_BASE_NS, XSPI2_RANGE_LIMIT_NS,
                                      ARM_MPC_ATTR_NONSECURE);
    if (ret != ARM_DRIVER_OK) {
        ERROR_MSG("Failed to Configure MPC for QSPI2!");
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_XSPI2_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

//ROM
    ret = Driver_ROM_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        ERROR_MSG("Failed to Initialize MPC for ROM!");
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    ret = Driver_ROM_MPC.ConfigRegion( ROM_RANGE_BASE_NS, ROM_RANGE_LIMIT_NS,
                                         ARM_MPC_ATTR_NONSECURE);
    if (ret != ARM_DRIVER_OK) {
        ERROR_MSG("Failed to Configure MPC for ROM!");
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }

    ret = Driver_ROM_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    


#ifdef BL2
    /* Secondary image region */
    ret = Driver_XSPI1_MPC.ConfigRegion(memory_regions.secondary_partition_base,
                                  memory_regions.secondary_partition_limit,
                                  ARM_MPC_ATTR_NONSECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
#endif /* BL2 */    

#if 0     // MHK
    //SRAM0
    ret = Driver_SRAM0_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
        }

    ret = Driver_SRAM0_MPC.ConfigRegion(SRAM0_RANGE_BASE_NS, SRAM0_RANGE_LIMIT_NS,
                                        ARM_MPC_ATTR_NONSECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM0_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
#endif
    //SRAM1
    ret = Driver_SRAM1_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    ret = Driver_SRAM1_MPC.ConfigRegion(SRAM1_RANGE_BASE_NS, SRAM1_RANGE_LIMIT_NS,
                                        ARM_MPC_ATTR_NONSECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM1_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM2
    ret = Driver_SRAM2_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM2_MPC.ConfigRegion(SRAM2_RANGE_BASE_S, SRAM2_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM2_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM3
    ret = Driver_SRAM3_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM3_MPC.ConfigRegion(SRAM3_RANGE_BASE_S, SRAM3_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM3_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM4
    ret = Driver_SRAM4_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM4_MPC.ConfigRegion(SRAM4_RANGE_BASE_S, SRAM4_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM4_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM5
    ret = Driver_SRAM5_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM5_MPC.ConfigRegion(SRAM5_RANGE_BASE_S, SRAM5_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM5_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM6
    ret = Driver_SRAM6_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM6_MPC.ConfigRegion(SRAM6_RANGE_BASE_S, SRAM6_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM6_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM7
    ret = Driver_SRAM7_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM7_MPC.ConfigRegion(SRAM7_RANGE_BASE_S, SRAM7_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM7_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM8
    ret = Driver_SRAM8_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM5_MPC.ConfigRegion(SRAM5_RANGE_BASE_S, SRAM5_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM5_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM9
    ret = Driver_SRAM9_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM9_MPC.ConfigRegion(SRAM9_RANGE_BASE_S, SRAM9_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM9_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM10
    ret = Driver_SRAM10_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM10_MPC.ConfigRegion(SRAM10_RANGE_BASE_S, SRAM10_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM10_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    //SRAM11
    ret = Driver_SRAM11_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM11_MPC.ConfigRegion(SRAM11_RANGE_BASE_S, SRAM11_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM11_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM12
    ret = Driver_SRAM12_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM12_MPC.ConfigRegion(SRAM12_RANGE_BASE_S, SRAM12_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM12_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM13
    ret = Driver_SRAM13_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM13_MPC.ConfigRegion(SRAM13_RANGE_BASE_S, SRAM13_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM13_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM14
    ret = Driver_SRAM14_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM14_MPC.ConfigRegion(SRAM14_RANGE_BASE_S, SRAM14_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM14_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    //SRAM15
    ret = Driver_SRAM15_MPC.Initialize();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    ret = Driver_SRAM15_MPC.ConfigRegion(SRAM15_RANGE_BASE_S, SRAM15_RANGE_LIMIT_S,
                                        ARM_MPC_ATTR_SECURE);
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }
    
    ret = Driver_SRAM15_MPC.LockDown();
    if (ret != ARM_DRIVER_OK) {
        FIH_RET(fih_int_encode(ret));
    }

    /* Add barriers to assure the MPC configuration is done before continue
     * the execution.
     */
    __DSB();
    __ISB();

    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}

#ifdef TFM_FIH_PROFILE_ON
fih_int fih_verify_mpc_cfg(void)
{  
    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}
#endif /* TFM_FIH_PROFILE_ON */

/*---------------------- PPC configuration functions -------------------------*/
#define NR_PPC_INIT_STEP                 4

FIH_RET_TYPE(int32_t) ppc_init_cfg(void)
{
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    inph_nspriv_security_t* nsppctrl = PPC_NSPPCTRL;
    
    int err = ARM_DRIVER_OK;

    /* Initialize not used PPC drivers */
    err |= Driver_APB_PPCBASE0.Initialize();
    err |= Driver_APB_PPCBASE1.Initialize();
    err |= Driver_APB_PPCBASE2.Initialize();
    err |= Driver_APB_SYSCNTRL.Initialize();
    err |= Driver_AHB_SYSCNTRL.Initialize();
    err |= Driver_AHB_PERIPHERAL0.Initialize();
    err |= Driver_AHB_PERIPHERAL1.Initialize();
    err |= Driver_AHB_SDIO.Initialize();
    err |= Driver_AHB_XIP1.Initialize();
    err |= Driver_AHB_XIP2.Initialize();

    /* in NS, grant un-privileged for UART0 */
    nsppctrl->APBNSPRVPPCPERIPH0.bf.PPC_PERIPH_0_NS_PRV_N |=
                                 (1U << NSPPCNTL_PERIPH0_UART0_POS);

    /* Configure the response to a security violation as a
     * bus error instead of RAZ/WI
     */
    spctrl->SECRESPCFG.bf.SECRESPCFG |= 1U;

    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}

#ifdef TFM_FIH_PROFILE_ON
fih_int fih_verify_ppc_cfg(void)
{    
 
    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}
#endif /* TFM_FIH_PROFILE_ON */

void ppc_configure_to_non_secure(enum ppc_bank_e bank, uint16_t pos)
{
    /* Setting NS flag for peripheral to enable NS access */
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    ((uint32_t*)&(spctrl->APBNSPPCBASE0))[bank] |= (1U << pos);
}

FIH_RET_TYPE(int32_t) ppc_configure_to_secure(enum ppc_bank_e bank, uint16_t pos)
{
    /* Clear NS flag for peripheral to prevent NS access */
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    ((uint32_t*)&(spctrl->APBNSPPCBASE0))[bank] &= ~(1U << pos);

    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}

FIH_RET_TYPE(int32_t) ppc_en_secure_unpriv(enum ppc_bank_e bank, uint16_t pos)
{
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    ((uint32_t*)&(spctrl->APBNSPPCBASE0))[bank] |= (1U << pos);

    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}

FIH_RET_TYPE(int32_t) ppc_clr_secure_unpriv(enum ppc_bank_e bank, uint16_t pos)
{
    inph_security_cntrl_t* spctrl = PPC_SPCTRL;
    ((uint32_t*)&(spctrl->APBNSPPCBASE0))[bank] &= ~(1U << pos);

    FIH_RET(fih_int_encode(ARM_DRIVER_OK));
}

void ppc_clear_irq(void)
{
    int32_t i = 0;

    for (i = 0; i < PPC_BANK_COUNT; i++) {
        ppc_bank_drivers[i]->ClearInterrupt();
    }
}

void mpc_clear_irq(void)
{
/* Clear MPC interrupt flag and pending MPC IRQ */
    Driver_SRAM0_MPC.ClearInterrupt();
    Driver_SRAM1_MPC.ClearInterrupt();
    Driver_SRAM2_MPC.ClearInterrupt();
    Driver_SRAM3_MPC.ClearInterrupt();
    Driver_SRAM4_MPC.ClearInterrupt();
    Driver_SRAM5_MPC.ClearInterrupt();
    Driver_SRAM6_MPC.ClearInterrupt();
    Driver_SRAM7_MPC.ClearInterrupt();
    Driver_SRAM8_MPC.ClearInterrupt();
    Driver_SRAM9_MPC.ClearInterrupt();
    Driver_SRAM10_MPC.ClearInterrupt();
    Driver_SRAM11_MPC.ClearInterrupt();
    Driver_SRAM12_MPC.ClearInterrupt();
    Driver_SRAM13_MPC.ClearInterrupt();
    Driver_SRAM14_MPC.ClearInterrupt();
    Driver_SRAM15_MPC.ClearInterrupt();
    Driver_XSPI1_MPC.ClearInterrupt();
    Driver_XSPI2_MPC.ClearInterrupt();
    Driver_ROM_MPC.ClearInterrupt();
}

#pragma GCC pop_options
