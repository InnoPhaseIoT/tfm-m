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

#include "platform_retarget_dev.h"
#include "Driver_Flash_CMSDK.h"
#include "cmsis_driver_config.h"
#include "RTE_Device.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")


#if (defined (RTE_FLASH0) && (RTE_FLASH0 == 1))

ARM_DRIVER_FLASH_CMSDK(FLASH0_CMSDK_DEV, Driver_FLASH0); //shalini: adjust

#endif /* RTE_USART0 */


#pragma GCC pop_options
