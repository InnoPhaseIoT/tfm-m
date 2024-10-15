/*
 * Copyright (c) 2016-2018 ARM Limited
 *
 * Licensed under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * \file platform_retarget_dev.h
 * \brief The structure definitions in this file are exported based on the peripheral
 * definitions from device_cfg.h.
 * This retarget file is meant to be used as a helper for baremetal
 * applications and/or as an example of how to configure the generic
 * driver structures.
 */

#ifndef __INPH_RETARGET_DEV_H__
#define __INPH_RETARGET_DEV_H__

/* ======= Includes generic driver headers ======= */
#include "RTE_Device.h"

/* ======= Defines peripheral configuration structures ======= */
/* ARM UART driver structures */
#ifdef ARM_UART0_S
extern struct arm_uart_dev_t ARM_UART0_DEV_S;
#endif
#ifdef ARM_UART0_NS
extern struct arm_uart_dev_t ARM_UART0_DEV_NS;
#endif


/* ARM PPC driver structures */
#ifdef RTE_APB_PPC_BASE0
extern struct inph_ppc_dev_t APB_PPCBASE0_DEV_S;
#endif

#ifdef RTE_APB_PPC_BASE1
extern struct inph_ppc_dev_t APB_PPCBASE1_DEV_S;
#endif

#ifdef RTE_APB_PPC_BASE2
extern struct inph_ppc_dev_t APB_PPCBASE2_DEV_S;
#endif

#ifdef RTE_AHB_PPC_PERIPH0
extern struct inph_ppc_dev_t AHB_PPCPERIPH0_DEV_S;
#endif

#ifdef RTE_AHB_PPC_PERIPH1
extern struct inph_ppc_dev_t AHB_PPCPERIPH1_DEV_S;
#endif

#ifdef RTE_AHB_PPC_XIP1
extern struct inph_ppc_dev_t AHB_PPCCXIP1_DEV_S;
#endif

#ifdef RTE_AHB_PPC_XIP2
extern struct inph_ppc_dev_t AHB_PPCCXIP2_DEV_S;
#endif

#ifdef RTE_AHB_PPC_SDIO
extern struct inph_ppc_dev_t AHB_PPCSDIO_DEV_S;
#endif

#ifdef RTE_APB_PPC_SYSTEM
extern struct inph_ppc_dev_t APB_PPCSYSTEM_DEV_S;
#endif

#ifdef RTE_AHB_PPC_SYSTEM
extern struct inph_ppc_dev_t AHB_PPCSYSTEM_DEV_S;
#endif

/* ARM MPC SSE 200 driver structures */
#ifdef MPC_SRAM0_S
extern struct inph_mpc_sie200_dev_t INPH_MPC_SRAM0_DEV_S;
#endif


#endif  /* __INPH_RETARGET_DEV_H__ */
