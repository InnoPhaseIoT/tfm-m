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

#include "cmsis_driver_config.h"
#include "RTE_Device.h"
#include "Driver_MPC_Sie.h"

#if 0    
    (defined (RTE_SRAM10_MPC) && (RTE_SRAM10_MPC == 1)) ||           \
    (defined (RTE_SRAM11_MPC) && (RTE_SRAM11_MPC == 1)) ||           \
    (defined (RTE_SRAM12_MPC) && (RTE_SRAM12_MPC == 1)) ||           \
    (defined (RTE_SRAM13_MPC) && (RTE_SRAM13_MPC == 1)) ||           \
    (defined (RTE_SRAM14_MPC) && (RTE_SRAM14_MPC == 1)) ||           \
    (defined (RTE_SRAM15_MPC) && (RTE_SRAM15_MPC == 1)) ||           
#endif

#if (defined (RTE_SRAM0_MPC) && (RTE_SRAM0_MPC == 1)) ||             \
    (defined (RTE_SRAM1_MPC) && (RTE_SRAM1_MPC == 1)) ||             \
    (defined (RTE_SRAM2_MPC) && (RTE_SRAM2_MPC == 1)) ||             \
    (defined (RTE_SRAM3_MPC) && (RTE_SRAM3_MPC == 1)) ||             \
    (defined (RTE_SRAM4_MPC) && (RTE_SRAM4_MPC == 1)) ||             \
    (defined (RTE_SRAM5_MPC) && (RTE_SRAM5_MPC == 1)) ||             \
    (defined (RTE_SRAM6_MPC) && (RTE_SRAM6_MPC == 1)) ||             \
    (defined (RTE_SRAM7_MPC) && (RTE_SRAM7_MPC == 1)) ||             \
    (defined (RTE_SRAM8_MPC) && (RTE_SRAM8_MPC == 1)) ||             \
    (defined (RTE_SRAM9_MPC) && (RTE_SRAM9_MPC == 1)) ||             \
    (defined (RTE_ROM_MPC) && (RTE_ROM_MPC == 1)) ||                 \
    (defined (RTE_XSPI1_MPC) && (RTE_XSPI1_MPC == 1)) ||             \
    (defined (RTE_XSPI2_MPC) && (RTE_XSPI2_MPC == 1))


#if (defined (RTE_SRAM0_MPC) && (RTE_SRAM0_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM0_DEV, Driver_SRAM0_MPC);
#endif /* RTE_SRAM0_MPC */

#if (defined (RTE_SRAM1_MPC) && (RTE_SRAM1_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM1_DEV, Driver_SRAM1_MPC);
#endif /* RTE_SRAM1_MPC */

#if (defined (RTE_SRAM2_MPC) && (RTE_SRAM2_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM2_DEV, Driver_SRAM2_MPC);
#endif /* RTE_SRAM2_MPC */

#if (defined (RTE_SRAM3_MPC) && (RTE_SRAM3_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM3_DEV, Driver_SRAM3_MPC);
#endif /* RTE_SRAM3_MPC */

#if (defined (RTE_SRAM4_MPC) && (RTE_SRAM4_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM4_DEV, Driver_SRAM4_MPC);
#endif /* RTE_SRAM4_MPC */

#if (defined (RTE_SRAM5_MPC) && (RTE_SRAM5_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM5_DEV, Driver_SRAM5_MPC);
#endif /* RTE_SRAM5_MPC */

#if (defined (RTE_SRAM6_MPC) && (RTE_SRAM6_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM6_DEV, Driver_SRAM6_MPC);
#endif /* RTE_SRAM6_MPC */

#if (defined (RTE_SRAM7_MPC) && (RTE_SRAM7_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM7_DEV, Driver_SRAM7_MPC);
#endif /* RTE_SRAM7_MPC */

#if (defined (RTE_SRAM8_MPC) && (RTE_SRAM8_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM8_DEV, Driver_SRAM8_MPC);
#endif /* RTE_SRAM8_MPC */

#if (defined (RTE_SRAM9_MPC) && (RTE_SRAM9_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM9_DEV, Driver_SRAM9_MPC);
#endif /* RTE_SRAM9_MPC */

#if 0
#if (defined (RTE_SRAM10_MPC) && (RTE_SRAM10_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM10_DEV, Driver_SRAM10_MPC);
#endif /* RTE_SRAM10_MPC */

#if (defined (RTE_SRAM11_MPC) && (RTE_SRAM11_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM11_DEV, Driver_SRAM11_MPC);
#endif /* RTE_SRAM11_MPC */

#if (defined (RTE_SRAM12_MPC) && (RTE_SRAM12_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM12_DEV, Driver_SRAM12_MPC);
#endif /* RTE_SRAM10_MPC */

#if (defined (RTE_SRAM13_MPC) && (RTE_SRAM13_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM13_DEV, Driver_SRAM13_MPC);
#endif /* RTE_SRAM13_MPC */

#if (defined (RTE_SRAM14_MPC) && (RTE_SRAM14_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM14_DEV, Driver_SRAM14_MPC);
#endif /* RTE_SRAM14_MPC */

#if (defined (RTE_SRAM15_MPC) && (RTE_SRAM15_MPC == 1))
ARM_DRIVER_MPC(MPC_SRAM15_DEV, Driver_SRAM15_MPC);
#endif /* RTE_SRAM13_MPC */
#endif

#if (defined (RTE_ROM_MPC) && (RTE_ROM_MPC == 1))
ARM_DRIVER_MPC(MPC_ROM_DEV, Driver_ROM_MPC);
#endif /* RTE_ROM_MPC */

#if (defined (RTE_XSPI1_MPC) && (RTE_XSPI1_MPC == 1))
ARM_DRIVER_MPC(MPC_XSPI1_DEV, Driver_XSPI1_MPC);
#endif /* RTE_XSPI1_MPC */

#if (defined (RTE_XSPI2_MPC) && (RTE_XSPI2_MPC == 1))
ARM_DRIVER_MPC(MPC_XSPI2_DEV, Driver_XSPI2_MPC);
#endif /* RTE_XSPI2_MPC */

#endif
