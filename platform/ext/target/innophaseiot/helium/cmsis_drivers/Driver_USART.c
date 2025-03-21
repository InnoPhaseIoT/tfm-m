/*
 * Copyright (c) 2013-2023 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Driver_USART_CMSDK.h"
#include "cmsis_driver_config.h"
#include "RTE_Device.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")

#if (defined (RTE_USART0_S) && (RTE_USART0_S == 1)) || \
    (defined (RTE_USART1_S) && (RTE_USART1_S == 1)) || \
    (defined (RTE_USART2_S) && (RTE_USART2_S == 1))

#if (defined (RTE_USART0_S) && (RTE_USART0_S == 1))

ARM_DRIVER_USART_CMSDK(UART0_CMSDK_DEV, Driver_USART0);

#endif /* RTE_USART0 */

#if (defined (RTE_USART1) && (RTE_USART1 == 1))

ARM_DRIVER_USART_CMSDK(UART1_CMSDK_DEV, Driver_USART1);

#endif /* RTE_USART1 */

#if (defined (RTE_USART2) && (RTE_USART2 == 1))

ARM_DRIVER_USART_CMSDK(UART2_CMSDK_DEV, Driver_USART2);

#endif /* RTE_USART2 */

#endif

#pragma GCC pop_options
