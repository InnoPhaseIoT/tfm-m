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
 * @file    platform_retarget_dev.h
 * @author  InnophaseIOT Firmware Team
 * @brief   device structure references
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

/* Values for hardware version in PIDR0 reg */
#define SIE200      0x60
#define SIE300      0x65

/* ARM UART driver structures */
#ifdef RTE_USART0_S
extern struct inph_uart_dev_t UART0_CMSDK_DEV_S;
#endif

#ifdef RTE_FLASH0
extern struct inph_flash_dev_t FLASH0_CMSDK_DEV_S;
#endif

#ifdef RTE_TZM_S
extern struct inph_tzm_dev_t TZM_DEV_S;
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
#ifdef RTE_SRAM0_MPC
extern struct mpc_sie_dev_t MPC_SRAM0_DEV_S;
#endif

#ifdef RTE_SRAM1_MPC
extern struct mpc_sie_dev_t MPC_SRAM1_DEV_S;
#endif

#ifdef RTE_SRAM2_MPC
extern struct mpc_sie_dev_t MPC_SRAM2_DEV_S;
#endif

#ifdef RTE_SRAM3_MPC
extern struct mpc_sie_dev_t MPC_SRAM3_DEV_S;
#endif

#ifdef RTE_SRAM4_MPC
extern struct mpc_sie_dev_t MPC_SRAM4_DEV_S;
#endif

#ifdef RTE_SRAM5_MPC
extern struct mpc_sie_dev_t MPC_SRAM5_DEV_S;
#endif

#ifdef RTE_SRAM6_MPC
extern struct mpc_sie_dev_t MPC_SRAM6_DEV_S;
#endif

#ifdef RTE_SRAM7_MPC
extern struct mpc_sie_dev_t MPC_SRAM7_DEV_S;
#endif

#ifdef RTE_SRAM8_MPC
extern struct mpc_sie_dev_t MPC_SRAM8_DEV_S;
#endif

#ifdef RTE_SRAM9_MPC
extern struct mpc_sie_dev_t MPC_SRAM9_DEV_S;
#endif

#if 0
#ifdef RTE_SRAM10_MPC
extern struct mpc_sie_dev_t MPC_SRAM10_DEV_S;
#endif

#ifdef RTE_SRAM11_MPC
extern struct mpc_sie_dev_t MPC_SRAM11_DEV_S;
#endif

#ifdef RTE_SRAM12_MPC
extern struct mpc_sie_dev_t MPC_SRAM12_DEV_S;
#endif

#ifdef RTE_SRAM13_MPC
extern struct mpc_sie_dev_t MPC_SRAM13_DEV_S;
#endif

#ifdef RTE_SRAM14_MPC
extern struct mpc_sie_dev_t MPC_SRAM14_DEV_S;
#endif

#ifdef RTE_SRAM15_MPC
extern struct mpc_sie_dev_t MPC_SRAM15_DEV_S;
#endif
#endif

#ifdef RTE_ROM_MPC
extern struct mpc_sie_dev_t MPC_ROM_DEV_S;
#endif

#ifdef RTE_XSPI1_MPC
extern struct mpc_sie_dev_t MPC_XSPI1_DEV_S;
#endif

#ifdef RTE_XSPI2_MPC
extern struct mpc_sie_dev_t MPC_XSPI2_DEV_S;
#endif


#endif  /* __INPH_RETARGET_DEV_H__ */
