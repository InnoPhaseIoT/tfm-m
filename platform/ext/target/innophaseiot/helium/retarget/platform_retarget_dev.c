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
 * @file    platform_retarget_dev.c
 * @author  InnophaseIOT Firmware Team
 * @brief   security structures
 */

#include "platform_retarget_dev.h"
#include "platform_retarget.h"
#include "mpc_sie_drv.h"
#include "inph_ppc_drv.h"
#include "inph_uart_drv.h"
#include "inph_tzm_drv.h"
#include "device_cfg.h"

/* UART definitions */

/* USART0 Driver wrapper functions */
/* UART CMSDK driver structures */
static const struct inph_uart_dev_cfg_t UART0_CMSDK_DEV_CFG_S = {
    .base = INPH_UART0_BASE_S,
    .default_baudrate = DEFAULT_UART_BAUDRATE
};
static struct inph_uart_dev_data_t UART0_CMSDK_DEV_DATA_S = {
    .state = 0,
    .system_clk = 0,
    .baudrate = 0
};
struct inph_uart_dev_t UART0_CMSDK_DEV_S = {
    &(UART0_CMSDK_DEV_CFG_S),
    &(UART0_CMSDK_DEV_DATA_S)
};

/* TZM definitions */
struct inph_tzm_dev_t TZM_DEV_S = {
    .spctrl_base = INPH_SPCTRL_BASE_S,
    .state = INPH_TZM_INITIALIZED
};
/* PPC definitions */

static struct inph_ppc_dev_cfg_t APB_PPCBASE0_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCBASE0_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCBASE0_DEV_S = {
    &APB_PPCBASE0_DEV_CFG, &APB_PPCBASE0_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCBASE1_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCBASE1_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCBASE1_DEV_S = {
    &APB_PPCBASE1_DEV_CFG, &APB_PPCBASE1_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCBASE2_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCBASE2_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCBASE2_DEV_S = {
    &APB_PPCBASE2_DEV_CFG, &APB_PPCBASE2_DEV_DATA_S };

/* Peripheral0 */
static struct inph_ppc_dev_cfg_t AHB_PPCPERIPH0_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCPERIPH0_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCPERIPH0_DEV_S = {
    &AHB_PPCPERIPH0_DEV_CFG, &AHB_PPCPERIPH0_DEV_DATA_S };

/* Peripheral1 */
static struct inph_ppc_dev_cfg_t AHB_PPCPERIPH1_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCPERIPH1_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCPERIPH1_DEV_S = {
    &AHB_PPCPERIPH1_DEV_CFG, &AHB_PPCPERIPH1_DEV_DATA_S };

/* XIP1 */
static struct inph_ppc_dev_cfg_t AHB_PPCCXIP1_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCCXIP1_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCCXIP1_DEV_S = {
    &AHB_PPCCXIP1_DEV_CFG, &AHB_PPCCXIP1_DEV_DATA_S };

/* XIP2 */
static struct inph_ppc_dev_cfg_t AHB_PPCCXIP2_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCCXIP2_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCCXIP2_DEV_S = {
    &AHB_PPCCXIP2_DEV_CFG, &AHB_PPCCXIP2_DEV_DATA_S };

/* SDIO */
static struct inph_ppc_dev_cfg_t AHB_PPCSDIO_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCSDIO_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCSDIO_DEV_S = {
    &AHB_PPCSDIO_DEV_CFG, &AHB_PPCSDIO_DEV_DATA_S };

/* system control APB */
static struct inph_ppc_dev_cfg_t APB_PPCSYSTEM_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCSYSTEM_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCSYSTEM_DEV_S = {
    &APB_PPCSYSTEM_DEV_CFG, &APB_PPCSYSTEM_DEV_DATA_S };

/* system control AHB */
static struct inph_ppc_dev_cfg_t AHB_PPCSYSTEM_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_SPCTRL_BASE_NS,
    .snspriv_base = INPH_NSPRIV_BASE_S,
    .nnspriv_base = INPH_NSPRIV_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCSYSTEM_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCSYSTEM_DEV_S = {
    &AHB_PPCSYSTEM_DEV_CFG, &AHB_PPCSYSTEM_DEV_DATA_S };


/* MPC definitions */

#define MPC_SRAM_RANGE_LIST_LEN  2u

/* SRAM0 */
static const struct mpc_sie_memory_range_t MPC_SRAM0_RANGE_S = {
    .base         = SRAM0_RANGE_BASE_S,
    .limit        = SRAM0_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM0_RANGE_NS = {
    .base         = SRAM0_RANGE_BASE_NS,
    .limit        = SRAM0_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM0_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM0_RANGE_S,
        &MPC_SRAM0_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM0_DEV_CFG_S = {
    .base = INPH_SRAM0_BASE_S,
    .range_list = MPC_SRAM0_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM0_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM0_DEV_S = {
    &(MPC_SRAM0_DEV_CFG_S),
    &(MPC_SRAM0_DEV_DATA_S)};

/* SRAM1 */
static const struct mpc_sie_memory_range_t MPC_SRAM1_RANGE_S = {
    .base         = SRAM1_RANGE_BASE_S,
    .limit        = SRAM1_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM1_RANGE_NS = {
    .base         = SRAM1_RANGE_BASE_NS,
    .limit        = SRAM1_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM1_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM1_RANGE_S,
        &MPC_SRAM1_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM1_DEV_CFG_S = {
    .base = INPH_SRAM1_BASE_S,
    .range_list = MPC_SRAM1_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM1_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM1_DEV_S = {
    &(MPC_SRAM1_DEV_CFG_S),
    &(MPC_SRAM1_DEV_DATA_S)};

/* SRAM2 */
static const struct mpc_sie_memory_range_t MPC_SRAM2_RANGE_S = {
    .base         = SRAM2_RANGE_BASE_S,
    .limit        = SRAM2_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM2_RANGE_NS = {
    .base         = SRAM2_RANGE_BASE_NS,
    .limit        = SRAM2_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM2_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM2_RANGE_S,
        &MPC_SRAM2_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM2_DEV_CFG_S = {
    .base = INPH_SRAM2_BASE_S,
    .range_list = MPC_SRAM2_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM2_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM2_DEV_S = {
    &(MPC_SRAM2_DEV_CFG_S),
    &(MPC_SRAM2_DEV_DATA_S)};

/* SRAM3 */
static const struct mpc_sie_memory_range_t MPC_SRAM3_RANGE_S = {
    .base         = SRAM3_RANGE_BASE_S,
    .limit        = SRAM3_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM3_RANGE_NS = {
    .base         = SRAM3_RANGE_BASE_NS,
    .limit        = SRAM3_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM3_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM3_RANGE_S,
        &MPC_SRAM3_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM3_DEV_CFG_S = {
    .base = INPH_SRAM3_BASE_S,
    .range_list = MPC_SRAM3_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM3_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM3_DEV_S = {
    &(MPC_SRAM3_DEV_CFG_S),
    &(MPC_SRAM3_DEV_DATA_S)};

/* SRAM4 */
static const struct mpc_sie_memory_range_t MPC_SRAM4_RANGE_S = {
    .base         = SRAM4_RANGE_BASE_S,
    .limit        = SRAM4_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM4_RANGE_NS = {
    .base         = SRAM4_RANGE_BASE_NS,
    .limit        = SRAM4_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM4_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM4_RANGE_S,
        &MPC_SRAM4_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM4_DEV_CFG_S = {
    .base = INPH_SRAM4_BASE_S,
    .range_list = MPC_SRAM4_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM4_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM4_DEV_S = {
    &(MPC_SRAM4_DEV_CFG_S),
    &(MPC_SRAM4_DEV_DATA_S)};

/* SRAM5 */
static const struct mpc_sie_memory_range_t MPC_SRAM5_RANGE_S = {
    .base         = SRAM5_RANGE_BASE_S,
    .limit        = SRAM5_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM5_RANGE_NS = {
    .base         = SRAM5_RANGE_BASE_NS,
    .limit        = SRAM5_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM5_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM5_RANGE_S,
        &MPC_SRAM5_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM5_DEV_CFG_S = {
    .base = INPH_SRAM5_BASE_S,
    .range_list = MPC_SRAM5_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM5_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM5_DEV_S = {
    &(MPC_SRAM5_DEV_CFG_S),
    &(MPC_SRAM5_DEV_DATA_S)};

/* SRAM6 */
static const struct mpc_sie_memory_range_t MPC_SRAM6_RANGE_S = {
    .base         = SRAM6_RANGE_BASE_S,
    .limit        = SRAM6_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM6_RANGE_NS = {
    .base         = SRAM6_RANGE_BASE_NS,
    .limit        = SRAM6_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM6_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM6_RANGE_S,
        &MPC_SRAM6_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM6_DEV_CFG_S = {
    .base = INPH_SRAM6_BASE_S,
    .range_list = MPC_SRAM6_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM6_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM6_DEV_S = {
    &(MPC_SRAM6_DEV_CFG_S),
    &(MPC_SRAM6_DEV_DATA_S)};

/* SRAM7 */
static const struct mpc_sie_memory_range_t MPC_SRAM7_RANGE_S = {
    .base         = SRAM7_RANGE_BASE_S,
    .limit        = SRAM7_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM7_RANGE_NS = {
    .base         = SRAM7_RANGE_BASE_NS,
    .limit        = SRAM7_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM7_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM7_RANGE_S,
        &MPC_SRAM7_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM7_DEV_CFG_S = {
    .base = INPH_SRAM7_BASE_S,
    .range_list = MPC_SRAM7_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM7_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM7_DEV_S = {
    &(MPC_SRAM7_DEV_CFG_S),
    &(MPC_SRAM7_DEV_DATA_S)};

/* SRAM8 */
static const struct mpc_sie_memory_range_t MPC_SRAM8_RANGE_S = {
    .base         = SRAM8_RANGE_BASE_S,
    .limit        = SRAM8_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM8_RANGE_NS = {
    .base         = SRAM8_RANGE_BASE_NS,
    .limit        = SRAM8_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM8_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM8_RANGE_S,
        &MPC_SRAM8_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM8_DEV_CFG_S = {
    .base = INPH_SRAM8_BASE_S,
    .range_list = MPC_SRAM8_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM8_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM8_DEV_S = {
    &(MPC_SRAM8_DEV_CFG_S),
    &(MPC_SRAM8_DEV_DATA_S)};

/* SRAM9 */
static const struct mpc_sie_memory_range_t MPC_SRAM9_RANGE_S = {
    .base         = SRAM9_RANGE_BASE_S,
    .limit        = SRAM9_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM9_RANGE_NS = {
    .base         = SRAM9_RANGE_BASE_NS,
    .limit        = SRAM9_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM9_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM9_RANGE_S,
        &MPC_SRAM9_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM9_DEV_CFG_S = {
    .base = INPH_SRAM9_BASE_S,
    .range_list = MPC_SRAM9_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM9_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM9_DEV_S = {
    &(MPC_SRAM9_DEV_CFG_S),
    &(MPC_SRAM9_DEV_DATA_S)};

/* SRAM10 */
static const struct mpc_sie_memory_range_t MPC_SRAM10_RANGE_S = {
    .base         = SRAM10_RANGE_BASE_S,
    .limit        = SRAM10_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM10_RANGE_NS = {
    .base         = SRAM10_RANGE_BASE_NS,
    .limit        = SRAM10_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM10_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM10_RANGE_S,
        &MPC_SRAM10_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM10_DEV_CFG_S = {
    .base = INPH_SRAM10_BASE_S,
    .range_list = MPC_SRAM10_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM10_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM10_DEV_S = {
    &(MPC_SRAM10_DEV_CFG_S),
    &(MPC_SRAM10_DEV_DATA_S)};

/* SRAM11 */
static const struct mpc_sie_memory_range_t MPC_SRAM11_RANGE_S = {
    .base         = SRAM11_RANGE_BASE_S,
    .limit        = SRAM11_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM11_RANGE_NS = {
    .base         = SRAM11_RANGE_BASE_NS,
    .limit        = SRAM11_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM11_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM11_RANGE_S,
        &MPC_SRAM11_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM11_DEV_CFG_S = {
    .base = INPH_SRAM11_BASE_S,
    .range_list = MPC_SRAM11_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM11_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM11_DEV_S = {
    &(MPC_SRAM11_DEV_CFG_S),
    &(MPC_SRAM11_DEV_DATA_S)};

/* SRAM12 */
static const struct mpc_sie_memory_range_t MPC_SRAM12_RANGE_S = {
    .base         = SRAM12_RANGE_BASE_S,
    .limit        = SRAM12_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM12_RANGE_NS = {
    .base         = SRAM12_RANGE_BASE_NS,
    .limit        = SRAM12_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM12_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM12_RANGE_S,
        &MPC_SRAM12_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM12_DEV_CFG_S = {
    .base = INPH_SRAM12_BASE_S,
    .range_list = MPC_SRAM12_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM12_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM12_DEV_S = {
    &(MPC_SRAM12_DEV_CFG_S),
    &(MPC_SRAM12_DEV_DATA_S)};

/* SRAM14 */
static const struct mpc_sie_memory_range_t MPC_SRAM14_RANGE_S = {
    .base         = SRAM14_RANGE_BASE_S,
    .limit        = SRAM14_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM14_RANGE_NS = {
    .base         = SRAM14_RANGE_BASE_NS,
    .limit        = SRAM14_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM14_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM14_RANGE_S,
        &MPC_SRAM14_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM14_DEV_CFG_S = {
    .base = INPH_SRAM14_BASE_S,
    .range_list = MPC_SRAM14_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM14_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM14_DEV_S = {
    &(MPC_SRAM14_DEV_CFG_S),
    &(MPC_SRAM14_DEV_DATA_S)};

/* SRAM15 */
static const struct mpc_sie_memory_range_t MPC_SRAM15_RANGE_S = {
    .base         = SRAM15_RANGE_BASE_S,
    .limit        = SRAM15_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_SRAM15_RANGE_NS = {
    .base         = SRAM15_RANGE_BASE_NS,
    .limit        = SRAM15_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_SRAM15_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_SRAM15_RANGE_S,
        &MPC_SRAM15_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_SRAM15_DEV_CFG_S = {
    .base = INPH_SRAM15_BASE_S,
    .range_list = MPC_SRAM15_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_SRAM15_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_SRAM15_DEV_S = {
    &(MPC_SRAM15_DEV_CFG_S),
    &(MPC_SRAM15_DEV_DATA_S)};

/* ROM */
static const struct mpc_sie_memory_range_t MPC_ROM_RANGE_S = {
    .base         = ROM_RANGE_BASE_S,
    .limit        = ROM_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_ROM_RANGE_NS = {
    .base         = ROM_RANGE_BASE_NS,
    .limit        = ROM_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_ROM_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_ROM_RANGE_S,
        &MPC_ROM_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_ROM_DEV_CFG_S = {
    .base = INPH_ROM_BASE_S,
    .range_list = MPC_ROM_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_ROM_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_ROM_DEV_S = {
    &(MPC_ROM_DEV_CFG_S),
    &(MPC_ROM_DEV_DATA_S)};

/* XSPI1 */
static const struct mpc_sie_memory_range_t MPC_XSPI1_RANGE_S = {
    .base         = XSPI1_RANGE_BASE_S,
    .limit        = XSPI1_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_XSPI1_RANGE_NS = {
    .base         = XSPI1_RANGE_BASE_NS,
    .limit        = XSPI1_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_XSPI1_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_XSPI1_RANGE_S,
        &MPC_XSPI1_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_XSPI1_DEV_CFG_S = {
    .base = INPH_XSPI1_BASE_S,
    .range_list = MPC_XSPI1_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_XSPI1_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_XSPI1_DEV_S = {
    &(MPC_XSPI1_DEV_CFG_S),
    &(MPC_XSPI1_DEV_DATA_S)};

/* XSPI2 */
static const struct mpc_sie_memory_range_t MPC_XSPI2_RANGE_S = {
    .base         = XSPI2_RANGE_BASE_S,
    .limit        = XSPI2_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_SECURE
};
static const struct mpc_sie_memory_range_t MPC_XSPI2_RANGE_NS = {
    .base         = XSPI2_RANGE_BASE_NS,
    .limit        = XSPI2_RANGE_LIMIT_NS,
    .range_offset = 0,
    .attr         = MPC_SIE_SEC_ATTR_NONSECURE
};
static const struct mpc_sie_memory_range_t*
    MPC_XSPI2_RANGE_LIST[MPC_SRAM_RANGE_LIST_LEN] = {
        &MPC_XSPI2_RANGE_S,
        &MPC_XSPI2_RANGE_NS
    };
static struct mpc_sie_dev_cfg_t MPC_XSPI2_DEV_CFG_S = {
    .base = INPH_XSPI2_BASE_S,
    .range_list = MPC_XSPI2_RANGE_LIST,
    .nbr_of_ranges = MPC_SRAM_RANGE_LIST_LEN};
static struct mpc_sie_dev_data_t MPC_XSPI2_DEV_DATA_S = {
    .is_initialized = false};
struct mpc_sie_dev_t MPC_XSPI2_DEV_S = {
    &(MPC_XSPI2_DEV_CFG_S),
    &(MPC_XSPI2_DEV_DATA_S)};


//#endif //INPH_HELIUM_A0

