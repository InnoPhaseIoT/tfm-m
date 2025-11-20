/*
 * Copyright (c) 2018 ARM Limited
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

#ifndef __CMSIS_DRIVER_CONFIG_H__
#define __CMSIS_DRIVER_CONFIG_H__

#include "platform_retarget_dev.h"
#include "RTE_Device.h"
#include "target_cfg.h"

#ifdef RTE_USART0_S
#define UART_DEV            USART0_DEV_S
#define UART0_CMSDK_DEV     UART0_CMSDK_DEV_S
#endif

#ifdef RTE_USART1_S
#define UART_DEV            USART1_DEV_S
#define UART1_CMSDK_DEV     UART1_CMSDK_DEV_S
#endif

#ifdef RTE_USART2_S
#define UART_DEV            USART2_DEV_S
#define UART2_CMSDK_DEV     UART2_CMSDK_DEV_S
#endif

//Shalini: FYI
#ifdef RTE_FLASH0
#define FLASH_DEV           FLASH0_DEV_S
#define FLASH0_CMSDK_DEV    FLASH0_CMSDK_DEV_S
#endif

#ifdef RTE_SRAM0_MPC
#define MPC_SRAM0_DEV     MPC_SRAM0_DEV_S
#endif

#ifdef RTE_SRAM1_MPC
#define MPC_SRAM1_DEV     MPC_SRAM1_DEV_S
#endif

#ifdef RTE_SRAM2_MPC
#define MPC_SRAM2_DEV     MPC_SRAM2_DEV_S
#endif

#ifdef RTE_SRAM3_MPC
#define MPC_SRAM3_DEV     MPC_SRAM3_DEV_S
#endif

#ifdef RTE_SRAM4_MPC
#define MPC_SRAM4_DEV     MPC_SRAM4_DEV_S
#endif

#ifdef RTE_SRAM5_MPC
#define MPC_SRAM5_DEV     MPC_SRAM5_DEV_S
#endif

#ifdef RTE_SRAM6_MPC
#define MPC_SRAM6_DEV     MPC_SRAM6_DEV_S
#endif

#ifdef RTE_SRAM7_MPC
#define MPC_SRAM7_DEV     MPC_SRAM7_DEV_S
#endif

#ifdef RTE_SRAM8_MPC
#define MPC_SRAM8_DEV     MPC_SRAM8_DEV_S
#endif

#ifdef RTE_SRAM9_MPC
#define MPC_SRAM9_DEV     MPC_SRAM9_DEV_S
#endif

#if 0
#ifdef RTE_SRAM10_MPC
#define MPC_SRAM10_DEV     MPC_SRAM10_DEV_S
#endif

#ifdef RTE_SRAM11_MPC
#define MPC_SRAM11_DEV     MPC_SRAM11_DEV_S
#endif

#ifdef RTE_SRAM12_MPC
#define MPC_SRAM12_DEV     MPC_SRAM12_DEV_S
#endif

#ifdef RTE_SRAM13_MPC
#define MPC_SRAM13_DEV     MPC_SRAM13_DEV_S
#endif

#ifdef RTE_SRAM14_MPC
#define MPC_SRAM14_DEV     MPC_SRAM14_DEV_S
#endif

#ifdef RTE_SRAM15_MPC
#define MPC_SRAM15_DEV     MPC_SRAM15_DEV_S
#endif
#endif


#ifdef RTE_ROM_MPC
#define MPC_ROM_DEV        MPC_ROM_DEV_S
#endif

#ifdef RTE_XSPI1_MPC
#define MPC_XSPI1_DEV        MPC_XSPI1_DEV_S
#endif

#ifdef RTE_XSPI2_MPC
#define MPC_XSPI2_DEV        MPC_XSPI2_DEV_S
#endif




#endif  /* __CMSIS_DRIVER_CONFIG_H__ */
