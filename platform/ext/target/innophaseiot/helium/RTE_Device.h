/*
 * Copyright (c) 2016-2018 ARM Limited
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

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

#include "tfm_utils.h"

#define INPH_DRIVER_VERSION_MAJOR_MINOR(major,minor) (((major) << 8) | (minor))

/**
\brief Driver Version
*/
typedef struct INPH_DRIVER_VERSION {
  uint16_t api;                         ///< API version
  uint16_t drv;                         ///< Driver version
} INPH_DRIVER_VERSION;

/* General return codes */
#define INPH_DRIVER_OK                 0 ///< Operation succeeded
#define INPH_DRIVER_ERROR             -1 ///< Unspecified error
#define INPH_DRIVER_ERROR_BUSY        -2 ///< Driver is busy
#define INPH_DRIVER_ERROR_TIMEOUT     -3 ///< Timeout occurred
#define INPH_DRIVER_ERROR_UNSUPPORTED -4 ///< Operation not supported
#define INPH_DRIVER_ERROR_PARAMETER   -5 ///< Parameter error
#define INPH_DRIVER_ERROR_SPECIFIC    -6 ///< Start of driver specific errors

/**
\brief General power states
*/
typedef enum _INPH_POWER_STATE {
  INPH_POWER_OFF,                        ///< Power off: no operation possible
  INPH_POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
  INPH_POWER_FULL                        ///< Power on: full operation at maximum performance
} INPH_POWER_STATE;

#define MPC_SRAM0_S
#define AHB_PPC_BASE0_S
#define AHB_PPC_BASE1_S
#define AHB_PPC_BASE2_S

#endif  /* __RTE_DEVICE_H */
