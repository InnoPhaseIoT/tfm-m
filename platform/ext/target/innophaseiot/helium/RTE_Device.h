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
 * @file    RTE_Device.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Run Time Environment definitions
 */

#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

#include "tfm_utils.h"

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

/*****************************************************************************/
/* TZM RUN TIME ENVIRONMENT DECLARATIONS                                     */
/*****************************************************************************/
// <e> TZM (Trust Zone Control Master) [RTE_TZM_S]
// <i> Configuration settings for Driver_USART0 in component ::Drivers:USART
#define   RTE_TZM_S                       1
// </e> TZM (Trust Zone Control Master) [RTE_TZM_S]

/*****************************************************************************/
/* UART RUN TIME ENVIRONMENT DECLARATIONS                                     */
/*****************************************************************************/
// <e> USART (Universal synchronous - asynchronous receiver transmitter) [Driver_USART0]
// <i> Configuration settings for Driver_USART0 in component ::Drivers:USART
#define   RTE_USART0_S                    1
// </e> USART (Universal synchronous - asynchronous receiver transmitter) [Driver_USART0]

// <e> USART (Universal synchronous - asynchronous receiver transmitter) [Driver_USART0]
// <i> Configuration settings for Driver_USART0 in component ::Drivers:USART
#define   RTE_USART0_NS                    0
// </e> USART (Universal synchronous - asynchronous receiver transmitter) [Driver_USART0]

/*****************************************************************************/
/* FLASH RUN TIME ENVIRONMENT DECLARATIONS                                     */
/*****************************************************************************/
// <e> FLASH (Flash Memory) [Driver_FLASH0]
// <i> Configuration settings for Driver_FLASH0 in component ::Drivers:FLASH
#define   RTE_FLASH0                     1
// </e> FLASH (Flash Memory) [Driver_FLASH0]

/*****************************************************************************/
/* MPC RUN TIME ENVIRONMENT DECLARATIONS                                     */
/*****************************************************************************/

// <e> MPC (Memory Protection Controller) [Driver_SRAM0_MPC]
// <i> Configuration settings for Driver_SRAM0_MPC in component ::Drivers:MPC
#define   RTE_SRAM0_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM0_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM1_MPC]
// <i> Configuration settings for Driver_SRAM1_MPC in component ::Drivers:MPC
#define   RTE_SRAM1_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM1_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM2_MPC]
// <i> Configuration settings for Driver_SRAM2_MPC in component ::Drivers:MPC
#define   RTE_SRAM2_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM2_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM3_MPC]
// <i> Configuration settings for Driver_SRAM3_MPC in component ::Drivers:MPC
#define   RTE_SRAM3_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM3_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM4_MPC]
// <i> Configuration settings for Driver_SRAM4_MPC in component ::Drivers:MPC
#define   RTE_SRAM4_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM4_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM5_MPC]
// <i> Configuration settings for Driver_SRAM5_MPC in component ::Drivers:MPC
#define   RTE_SRAM5_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM5_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM6_MPC]
// <i> Configuration settings for Driver_SRAM6_MPC in component ::Drivers:MPC
#define   RTE_SRAM6_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM6_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM7_MPC]
// <i> Configuration settings for Driver_SRAM7_MPC in component ::Drivers:MPC
#define   RTE_SRAM7_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM7_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM8_MPC]
// <i> Configuration settings for Driver_SRAM8_MPC in component ::Drivers:MPC
#define   RTE_SRAM8_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM8_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM9_MPC]
// <i> Configuration settings for Driver_SRAM9_MPC in component ::Drivers:MPC
#define   RTE_SRAM9_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_SRAM9_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM10_MPC]
// <i> Configuration settings for Driver_SRAM10_MPC in component ::Drivers:MPC
#define   RTE_SRAM10_MPC                 1
// </e> MPC (Memory Protection Controller) [Driver_SRAM10_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM11_MPC]
// <i> Configuration settings for Driver_SRAM11_MPC in component ::Drivers:MPC
#define   RTE_SRAM11_MPC                 1
// </e> MPC (Memory Protection Controller) [Driver_SRAM11_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM12_MPC]
// <i> Configuration settings for Driver_SRAM12_MPC in component ::Drivers:MPC
#define   RTE_SRAM12_MPC                 1
// </e> MPC (Memory Protection Controller) [Driver_SRAM12_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM13_MPC]
// <i> Configuration settings for Driver_SRAM13_MPC in component ::Drivers:MPC
#define   RTE_SRAM13_MPC                 1
// </e> MPC (Memory Protection Controller) [Driver_SRAM13_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM14_MPC]
// <i> Configuration settings for Driver_SRAM14_MPC in component ::Drivers:MPC
#define   RTE_SRAM14_MPC                 1
// </e> MPC (Memory Protection Controller) [Driver_SRAM14_MPC]

// <e> MPC (Memory Protection Controller) [Driver_SRAM15_MPC]
// <i> Configuration settings for Driver_SRAM15_MPC in component ::Drivers:MPC
#define   RTE_SRAM15_MPC                 1
// </e> MPC (Memory Protection Controller) [Driver_SRAM15_MPC]

// <e> MPC (Memory Protection Controller) [Driver_ROM_MPC]
// <i> Configuration settings for Driver_ROM_MPC in component ::Drivers:MPC
#define   RTE_ROM_MPC                    1
// </e> MPC (Memory Protection Controller) [Driver_ROM_MPC]

// <e> MPC (Memory Protection Controller) [Driver_XSPI1_MPC]
// <i> Configuration settings for Driver_XSPI1_MPC in component ::Drivers:MPC
#define   RTE_XSPI1_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_XSPI1_MPC]

// <e> MPC (Memory Protection Controller) [Driver_XSPI2_MPC]
// <i> Configuration settings for Driver_XSPI2_MPC in component ::Drivers:MPC
#define   RTE_XSPI2_MPC                  1
// </e> MPC (Memory Protection Controller) [Driver_XSPI2_MPC]

/*****************************************************************************/
/* PPC RUN TIME ENVIRONMENT DECLARATIONS                                     */
/*****************************************************************************/

// <e> PPC (Peripheral Protection Controller) [Driver_APB_PPCBASE0]
// <i> Configuration settings for Driver_APB_PPCBASE0in component ::Drivers:PPC
#define   RTE_APB_PPC_BASE0               1
// </e> PPC (Peripheral Protection Controller) [Driver_APB_PPCBASE0]

// <e> PPC (Peripheral Protection Controller) [Driver_APB_PPCBASE1]
// <i> Configuration settings for Driver_APB_PPCBASE1 in component ::Drivers:PPC
#define   RTE_APB_PPC_BASE1               1
// </e> PPC (Peripheral Protection Controller) [Driver_APB_PPCBASE1]

// <e> PPC (Peripheral Protection Controller) [Driver_APB_PPCBASE2]
// <i> Configuration settings for Driver_APB_PPCBASE2 in component ::Drivers:PPC
#define   RTE_APB_PPC_BASE2               1
// </e> PPC (Peripheral Protection Controller) [Driver_APB_PPCBASE2]

// <e> PPC (Peripheral Protection Controller) [Driver_AHB_PERIPHERAL0]
// <i> Configuration settings for Driver_AHB_PERIPHERAL0 in component ::Drivers:PPC
#define   RTE_AHB_PPC_PERIPH0             1
// </e> PPC (Peripheral Protection Controller) [Driver_AHB_PERIPHERAL0]

// <e> PPC (Peripheral Protection Controller) [Driver_AHB_PERIPHERAL1]
// <i> Configuration settings for Driver_AHB_PERIPHERAL1 in component ::Drivers:PPC
#define   RTE_AHB_PPC_PERIPH1             1
// </e> PPC (Peripheral Protection Controller) [Driver_AHB_PERIPHERAL1]

// <e> PPC (Peripheral Protection Controller) [Driver_AHB_XIP1]
// <i> Configuration settings for Driver_AHB_XIP1 in component ::Drivers:PPC
#define   RTE_AHB_PPC_XIP1                1
// </e> PPC (Peripheral Protection Controller) [Driver_AHB_XIP1]

// <e> PPC (Peripheral Protection Controller) [Driver_AHB_XIP2]
// <i> Configuration settings for Driver_AHB_XIP2 in component ::Drivers:PPC
#define   RTE_AHB_PPC_XIP2                1
// </e> PPC (Peripheral Protection Controller) [Driver_AHB_XIP2]

// <e> PPC (Peripheral Protection Controller) [Driver_AHB_SDIO]
// <i> Configuration settings for Driver_AHB_SDIO in component ::Drivers:PPC
#define   RTE_AHB_PPC_SDIO                1
// </e> PPC (Peripheral Protection Controller) [Driver_AHB_SDIO]

// <e> PPC (Peripheral Protection Controller) [Driver_APB_SYSCNTRL]
// <i> Configuration settings for Driver_APB_SYSCNTRL in component ::Drivers:PPC
#define   RTE_APB_PPC_SYSTEM              1
// </e> PPC (Peripheral Protection Controller) [Driver_APB_SYSCNTRL]

// <e> PPC (Peripheral Protection Controller) [Driver_AHB_SYSCNTRL]
// <i> Configuration settings for Driver_AHB_SYSCNTRL in component ::Drivers:PPC
#define   RTE_AHB_PPC_SYSTEM              1
// </e> PPC (Peripheral Protection Controller) [Driver_AHB_SYSCNTRL]


#endif  /* __RTE_DEVICE_H */
