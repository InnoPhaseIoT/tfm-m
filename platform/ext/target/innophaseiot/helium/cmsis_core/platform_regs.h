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
 * @file    platform_regs
 * @author  InnophaseIOT Firmware Team
 * @brief   Register file
 */

#ifndef __INPH_HELIUM_REGS_H__
#define __INPH_HELIUM_REGS_H__

#include <stdint.h>
#include "inph_nspriv_registers.h"
#include "inph_security_registers.h"
//#include "tfm_utils.h"

#define PPC_SPCTRL (inph_security_cntrl_t*)(INPH_SPCTRL_BASE_S)
#define PPC_NSPPCTRL (inph_nspriv_security_t*)(INPH_NSPRIV_BASE_NS)

/* ARM AHB PPC peripherals definition */

#define SPCNTL_XIP1_CXIP1_POS  0U
#define SPCNTL_XIP2_CXIP2_POS  0U

#define SPCNTL_SYS_SMU_POS   0U
#define SPCNTL_SYS_AON_POS   1U
#define SPCNTL_SYS_RTC_POS   2U
#define SPCNTL_SYS_LPT_POS   3U
#define SPCNTL_SYS_WDT_POS   4U
#define SPCNTL_SYS_MISC_POS  5U
#define SPCNTL_SYS_MISC2_POS 6U
#define SPCNTL_SYS_PMU_POS   7U
#define SPCNTL_SYS_RFA_POS   8U
#define SPCNTL_SYS_DFA_POS   9U
#define SPCNTL_SYS_HKADC_POS 10U

#define SPCNTL_BASE0_SEC_POS   0U
#define SPCNTL_BASE0_DT0_POS   1U
#define SPCNTL_BASE0_DT1_POS   2U
#define SPCNTL_BASE0_DT2_POS   3U
#define SPCNTL_BASE0_DT3_POS   4U
#define SPCNTL_BASE0_OTP_POS   5U
#define SPCNTL_BASE0_RESV_POS  6U
#define SPCNTL_BASE0_NPU_POS   7U
#define SPCNTL_BASE0_NSP_POS   8U

#define SPCNTL_BASE1_SRAM0_POS   0U
#define SPCNTL_BASE1_SRAM1_POS   1U
#define SPCNTL_BASE1_SRAM2_POS   2U
#define SPCNTL_BASE1_SRAM3_POS   3U
#define SPCNTL_BASE1_SRAM4_POS   4U
#define SPCNTL_BASE1_SRAM5_POS   5U
#define SPCNTL_BASE1_SRAM6_POS   6U
#define SPCNTL_BASE1_SRAM7_POS   7U
#define SPCNTL_BASE1_SRAM8_POS   8U
#define SPCNTL_BASE1_SRAM9_POS   9U
#define SPCNTL_BASE1_SRAM10_POS  10U
#define SPCNTL_BASE1_SRAM11_POS  11U
#define SPCNTL_BASE1_SRAM12_POS  12U
#define SPCNTL_BASE1_SRAM13_POS  13U
#define SPCNTL_BASE1_SRAM14_POS  14U
#define SPCNTL_BASE1_SRAM15_POS  15U

#define SPCNTL_BASE2_ROMMPC_POS     0U
#define SPCNTL_BASE2_XSPI1MPC_POS   1U
#define SPCNTL_BASE2_XSPI1CFG_POS   2U
#define SPCNTL_BASE2_UDMA_POS       3U
#define SPCNTL_BASE2_XSPI1CRYP_POS  4U
#define SPCNTL_BASE2_XSPI2CFG_POS   5U
#define SPCNTL_BASE2_XIP2MPC_POS    6U
#define SPCNTL_BASE2_XSPI2CRYP_POS  7U

#define SPCNTL_PERIPH0_UART0_POS   0U
#define SPCNTL_PERIPH0_UART1_POS   1U
#define SPCNTL_PERIPH0_UART2_POS   2U
#define SPCNTL_PERIPH0_SPI0_POS    3U
#define SPCNTL_PERIPH0_SPI1_POS    4U
#define SPCNTL_PERIPH0_I2S_POS     5U
#define SPCNTL_PERIPH0_I2C0_POS    6U
#define SPCNTL_PERIPH0_I2C1_POS    7U
#define SPCNTL_PERIPH0_PDM_POS     8U
#define SPCNTL_PERIPH0_HKADC_POS   9U

#define SPCNTL_PERIPH1_GPIO0_POS   0U
#define SPCNTL_PERIPH1_GPIO1_POS   1U
#define SPCNTL_PERIPH1_TCPWM0_POS  2U
#define SPCNTL_PERIPH1_TCPWM1_POS  3U
#define SPCNTL_PERIPH1_TCPWM2_POS  4U
#define SPCNTL_PERIPH1_TCPWM3_POS  5U
#define SPCNTL_PERIPH1_TCPWM4_POS  6U
#define SPCNTL_PERIPH1_TCPWM5_POS  7U
#define SPCNTL_PERIPH1_TRIG_POS    8U

#define SPCNTL_SDIO_CNTRL_POS   0U
#define SPCNTL_SDIO_DPRAM_POS   1U

#define NSPPCNTL_PERIPH0_UART0_POS   1U

/* PPC interrupt position mask */
#define SPCNTL_BASE0_INT_POS_MASK     (1UL << 0)
#define SPCNTL_BASE1_INT_POS_MASK     (1UL << 1)
#define SPCNTL_BASE2_INT_POS_MASK     (1UL << 2)
#define SPCNTL_SYSAHB_INT_POS_MASK    (1UL << 3)
#define SPCNTL_SYSAPB_INT_POS_MASK    (1UL << 4)
#define SPCNTL_PERIPH0_INT_POS_MASK   (1UL << 5)
#define SPCNTL_PERIPH1_INT_POS_MASK   (1UL << 6)
#define SPCNTL_SDIO_INT_POS_MASK      (1UL << 7)
#define SPCNTL_CXIP1_INT_POS_MASK     (1UL << 8)
#define SPCNTL_CXIP2_INT_POS_MASK     (1UL << 9)

#if 0 //MHK remove it do not need the blow code
/*  SPCSECCTRL DESCRIPTION :TBD if needed: Secure Privilege Controller Secure Configuration Control register */
typedef union {
    struct {
        uint32_t Reserved : 32;               /*31:0 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;


}security_ctrl_regs_SPCSECCTRL;

/*  BUSWAIT DESCRIPTION :TBD if needed: Bus Access wait control after reset */
typedef union {
    struct {
        uint32_t Reserved : 32;               /*31:0 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;


}security_ctrl_regs_BUSWAIT;

/*  SECRESPCFG DESCRIPTION :Security Violation Response Configuration register */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 31;               /*31:1 SW=rw HW=ro 0x0 */
            uint32_t SECRESPCFG : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t SECRESPCFG : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 31;               /*1:31 SW=rw HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECRESPCFG;

/*  NSCCFG DESCRIPTION :TBD. Non Secure Callable Configuration for IDAU */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 30;               /*31:2 SW=ro HW=ro 0x0 */
            uint32_t RAMNSC : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t CODENSC : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t CODENSC : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t RAMNSC : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 30;               /*2:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_NSCCFG;

/*  SECMPCINTSTATUS DESCRIPTION :Memory Protection Controller Interrupt Status */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 13;               /*31:19 SW=ro HW=ro 0x0 */
            uint32_t S_MPCXSPI2_STATUS : 1;               /*18 SW=ro HW=wo 0x0 */
            uint32_t S_MPCXSPI1_STATUS : 1;               /*17 SW=ro HW=wo 0x0 */
            uint32_t S_MPCROM_STATUS : 1;               /*16 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM15_STATUS : 1;               /*15 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM14_STATUS : 1;               /*14 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM13_STATUS : 1;               /*13 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM12_STATUS : 1;               /*12 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM11_STATUS : 1;               /*11 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM10_STATUS : 1;               /*10 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM9_STATUS : 1;               /*9 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM8_STATUS : 1;               /*8 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM7_STATUS : 1;               /*7 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM6_STATUS : 1;               /*6 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM5_STATUS : 1;               /*5 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM4_STATUS : 1;               /*4 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM3_STATUS : 1;               /*3 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM2_STATUS : 1;               /*2 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM1_STATUS : 1;               /*1 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM0_STATUS : 1;               /*0 SW=ro HW=wo 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t S_MPCSRAM0_STATUS : 1;               /*0 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM1_STATUS : 1;               /*1 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM2_STATUS : 1;               /*2 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM3_STATUS : 1;               /*3 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM4_STATUS : 1;               /*4 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM5_STATUS : 1;               /*5 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM6_STATUS : 1;               /*6 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM7_STATUS : 1;               /*7 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM8_STATUS : 1;               /*8 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM9_STATUS : 1;               /*9 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM10_STATUS : 1;               /*10 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM11_STATUS : 1;               /*11 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM12_STATUS : 1;               /*12 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM13_STATUS : 1;               /*13 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM14_STATUS : 1;               /*14 SW=ro HW=wo 0x0 */
            uint32_t S_MPCSRAM15_STATUS : 1;               /*15 SW=ro HW=wo 0x0 */
            uint32_t S_MPCROM_STATUS : 1;               /*16 SW=ro HW=wo 0x0 */
            uint32_t S_MPCXSPI1_STATUS : 1;               /*17 SW=ro HW=wo 0x0 */
            uint32_t S_MPCXSPI2_STATUS : 1;               /*18 SW=ro HW=wo 0x0 */
            uint32_t Reserved : 13;               /*19:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECMPCINTSTATUS;

/*  SECMPCINTEN DESCRIPTION :Peripheral Protection Controller Interrupt Enable */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 13;               /*31:19 SW=rw HW=ro 0x0 */
            uint32_t S_MPCXSPI2_INT_EN : 1;               /*18 SW=rw HW=ro 0x0 */
            uint32_t S_MPCXSPI1_INT_EN : 1;               /*17 SW=rw HW=ro 0x0 */
            uint32_t S_MPCROM_INT_EN : 1;               /*16 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM15_INT_EN : 1;               /*15 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM14_INT_EN : 1;               /*14 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM13_INT_EN : 1;               /*13 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM12_INT_EN : 1;               /*12 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM11_INT_EN : 1;               /*11 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM10_INT_EN : 1;               /*10 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM9_INT_EN : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM8_INT_EN : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM7_INT_EN : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM6_INT_EN : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM5_INT_EN : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM4_INT_EN : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM3_INT_EN : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM2_INT_EN : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM1_INT_EN : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM0_INT_EN : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t S_MPCSRAM0_INT_EN : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM1_INT_EN : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM2_INT_EN : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM3_INT_EN : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM4_INT_EN : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM5_INT_EN : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM6_INT_EN : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM7_INT_EN : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM8_INT_EN : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM9_INT_EN : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM10_INT_EN : 1;               /*10 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM11_INT_EN : 1;               /*11 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM12_INT_EN : 1;               /*12 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM13_INT_EN : 1;               /*13 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM14_INT_EN : 1;               /*14 SW=rw HW=ro 0x0 */
            uint32_t S_MPCSRAM15_INT_EN : 1;               /*15 SW=rw HW=ro 0x0 */
            uint32_t S_MPCROM_INT_EN : 1;               /*16 SW=rw HW=ro 0x0 */
            uint32_t S_MPCXSPI1_INT_EN : 1;               /*17 SW=rw HW=ro 0x0 */
            uint32_t S_MPCXSPI2_INT_EN : 1;               /*18 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 13;               /*19:31 SW=rw HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECMPCINTEN;

/*  SECPPCINTSTATUS DESCRIPTION :Peripheral Protection Controller Interrupt Status */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 22;               /*31:10 SW=ro HW=ro 0x0 */
            uint32_t PPC_CXIP2_STS : 1;               /*9 SW=ro HW=wo 0x0 */
            uint32_t PPC_CXIP1_STS : 1;               /*8 SW=ro HW=wo 0x0 */
            uint32_t PPC_PERIPH_SDIO_STS : 1;               /*7 SW=ro HW=wo 0x0 */
            uint32_t PPC_PERIPH_1_STS : 1;               /*6 SW=ro HW=wo 0x0 */
            uint32_t PPC_PERIPH_0_STS : 1;               /*5 SW=ro HW=wo 0x0 */
            uint32_t PPC_SYS_AHB_STS : 1;               /*4 SW=ro HW=wo 0x0 */
            uint32_t PPC_SYS_APB_STS : 1;               /*3 SW=ro HW=wo 0x0 */
            uint32_t PPC_BASE_2_STS : 1;               /*2 SW=ro HW=wo 0x0 */
            uint32_t PPC_BASE_1_STS : 1;               /*1 SW=ro HW=wo 0x0 */
            uint32_t PPC_BASE_0_STS : 1;               /*0 SW=ro HW=wo 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_STS : 1;               /*0 SW=ro HW=wo 0x0 */
            uint32_t PPC_BASE_1_STS : 1;               /*1 SW=ro HW=wo 0x0 */
            uint32_t PPC_BASE_2_STS : 1;               /*2 SW=ro HW=wo 0x0 */
            uint32_t PPC_SYS_APB_STS : 1;               /*3 SW=ro HW=wo 0x0 */
            uint32_t PPC_SYS_AHB_STS : 1;               /*4 SW=ro HW=wo 0x0 */
            uint32_t PPC_PERIPH_0_STS : 1;               /*5 SW=ro HW=wo 0x0 */
            uint32_t PPC_PERIPH_1_STS : 1;               /*6 SW=ro HW=wo 0x0 */
            uint32_t PPC_PERIPH_SDIO_STS : 1;               /*7 SW=ro HW=wo 0x0 */
            uint32_t PPC_CXIP1_STS : 1;               /*8 SW=ro HW=wo 0x0 */
            uint32_t PPC_CXIP2_STS : 1;               /*9 SW=ro HW=wo 0x0 */
            uint32_t Reserved : 22;               /*10:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECPPCINTSTATUS;

/*  SECPPCINTCLR DESCRIPTION :
Peripheral Protection Controller Interrupt Clear */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 22;               /*31:10 SW=ro HW=ro 0x0 */
            uint32_t PPC_CXIP2_CLR : 1;               /*9 SW=w1s HW=rw 0x0 */
            uint32_t PPC_CXIP1_CLR : 1;               /*8 SW=w1s HW=rw 0x0 */
            uint32_t PPC_PERIPH_SDIO_CLR : 1;               /*7 SW=w1s HW=rw 0x0 */
            uint32_t PPC_PERIPH_1_CLR : 1;               /*6 SW=w1s HW=rw 0x0 */
            uint32_t PPC_PERIPH_0_CLR : 1;               /*5 SW=w1s HW=rw 0x0 */
            uint32_t PPC_SYS_AHB_CLR : 1;               /*4 SW=w1s HW=rw 0x0 */
            uint32_t PPC_SYS_APB_CLR : 1;               /*3 SW=w1s HW=rw 0x0 */
            uint32_t PPC_BASE_2_CLR : 1;               /*2 SW=w1s HW=rw 0x0 */
            uint32_t PPC_BASE_1_CLR : 1;               /*1 SW=w1s HW=rw 0x0 */
            uint32_t PPC_BASE_0_CLR : 1;               /*0 SW=w1s HW=rw 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_CLR : 1;               /*0 SW=w1s HW=rw 0x0 */
            uint32_t PPC_BASE_1_CLR : 1;               /*1 SW=w1s HW=rw 0x0 */
            uint32_t PPC_BASE_2_CLR : 1;               /*2 SW=w1s HW=rw 0x0 */
            uint32_t PPC_SYS_APB_CLR : 1;               /*3 SW=w1s HW=rw 0x0 */
            uint32_t PPC_SYS_AHB_CLR : 1;               /*4 SW=w1s HW=rw 0x0 */
            uint32_t PPC_PERIPH_0_CLR : 1;               /*5 SW=w1s HW=rw 0x0 */
            uint32_t PPC_PERIPH_1_CLR : 1;               /*6 SW=w1s HW=rw 0x0 */
            uint32_t PPC_PERIPH_SDIO_CLR : 1;               /*7 SW=w1s HW=rw 0x0 */
            uint32_t PPC_CXIP1_CLR : 1;               /*8 SW=w1s HW=rw 0x0 */
            uint32_t PPC_CXIP2_CLR : 1;               /*9 SW=w1s HW=rw 0x0 */
            uint32_t Reserved : 22;               /*10:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECPPCINTCLR;

/*  SECPPCINTEN DESCRIPTION :Peripheral Protection Controller Interrupt Enable */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 22;               /*31:10 SW=ro HW=ro 0x0 */
            uint32_t PPC_CXIP2_EN : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t PPC_CXIP1_EN : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t PPC_PERIPH_SDIO_EN : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t PPC_PERIPH_1_EN : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t PPC_PERIPH_0_EN : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t PPC_SYS_AHB_EN : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t PPC_SYS_APB_EN : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t PPC_BASE_2_EN : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t PPC_BASE_1_EN : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t PPC_BASE_0_EN : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_EN : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t PPC_BASE_1_EN : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t PPC_BASE_2_EN : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t PPC_SYS_APB_EN : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t PPC_SYS_AHB_EN : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t PPC_PERIPH_0_EN : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t PPC_PERIPH_1_EN : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t PPC_PERIPH_SDIO_EN : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t PPC_CXIP1_EN : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t PPC_CXIP2_EN : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 22;               /*10:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECPPCINTEN;

/*  SECMSCINTSTATUS DESCRIPTION :Master Security Controller Interrupt Status */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 9;               /*31:23 SW=ro HW=ro 0x0 */
            uint32_t TZM_HKADC_DMA_STS : 1;               /*22 SW=ro HW=wo 0x0 */
            uint32_t TZM_PDM_DMA_STS : 1;               /*21 SW=ro HW=wo 0x0 */
            uint32_t TZM_I2C_DMA_1_STS : 1;               /*20 SW=ro HW=wo 0x0 */
            uint32_t TZM_I2C_DMA_0_STS : 1;               /*19 SW=ro HW=wo 0x0 */
            uint32_t TZM_I2S_DMA_STS : 1;               /*18 SW=ro HW=wo 0x0 */
            uint32_t TZM_SPI_DMA_1_STS : 1;               /*17 SW=ro HW=wo 0x0 */
            uint32_t TZM_SPI_DMA_0_STS : 1;               /*16 SW=ro HW=wo 0x0 */
            uint32_t TZM_UART_DMA_2_STS : 1;               /*15 SW=ro HW=wo 0x0 */
            uint32_t TZM_UART_DMA_1_STS : 1;               /*14 SW=ro HW=wo 0x0 */
            uint32_t TZM_UART_DMA_0_STS : 1;               /*13 SW=ro HW=wo 0x0 */
            uint32_t TZM_SDIO_DMA_STS : 1;               /*12 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_MEM_STS : 1;               /*11 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_CODE_STS : 1;               /*10 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_STS : 1;               /*9 SW=ro HW=wo 0x0 */
            uint32_t TZM_XSPI2_DMA_STS : 1;               /*8 SW=ro HW=wo 0x0 */
            uint32_t TZM_CRYPTO_XIP2_STS : 1;               /*7 SW=ro HW=wo 0x0 */
            uint32_t TZM_XSPI1_DMA_STS : 1;               /*6 SW=ro HW=wo 0x0 */
            uint32_t TZM_CRYPTO_SUB_STS : 1;               /*5 SW=ro HW=wo 0x0 */
            uint32_t TZM_CRYPTO_XIP1_STS : 1;               /*4 SW=ro HW=wo 0x0 */
            uint32_t TZM_DEBUG_STS : 1;               /*3 SW=ro HW=wo 0x0 */
            uint32_t TZM_UDMA_BASE_STS : 1;               /*2 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_TX_STS : 1;               /*1 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_RX_STS : 1;               /*0 SW=ro HW=wo 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t TZM_NPU_RX_STS : 1;               /*0 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_TX_STS : 1;               /*1 SW=ro HW=wo 0x0 */
            uint32_t TZM_UDMA_BASE_STS : 1;               /*2 SW=ro HW=wo 0x0 */
            uint32_t TZM_DEBUG_STS : 1;               /*3 SW=ro HW=wo 0x0 */
            uint32_t TZM_CRYPTO_XIP1_STS : 1;               /*4 SW=ro HW=wo 0x0 */
            uint32_t TZM_CRYPTO_SUB_STS : 1;               /*5 SW=ro HW=wo 0x0 */
            uint32_t TZM_XSPI1_DMA_STS : 1;               /*6 SW=ro HW=wo 0x0 */
            uint32_t TZM_CRYPTO_XIP2_STS : 1;               /*7 SW=ro HW=wo 0x0 */
            uint32_t TZM_XSPI2_DMA_STS : 1;               /*8 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_STS : 1;               /*9 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_CODE_STS : 1;               /*10 SW=ro HW=wo 0x0 */
            uint32_t TZM_NPU_MEM_STS : 1;               /*11 SW=ro HW=wo 0x0 */
            uint32_t TZM_SDIO_DMA_STS : 1;               /*12 SW=ro HW=wo 0x0 */
            uint32_t TZM_UART_DMA_0_STS : 1;               /*13 SW=ro HW=wo 0x0 */
            uint32_t TZM_UART_DMA_1_STS : 1;               /*14 SW=ro HW=wo 0x0 */
            uint32_t TZM_UART_DMA_2_STS : 1;               /*15 SW=ro HW=wo 0x0 */
            uint32_t TZM_SPI_DMA_0_STS : 1;               /*16 SW=ro HW=wo 0x0 */
            uint32_t TZM_SPI_DMA_1_STS : 1;               /*17 SW=ro HW=wo 0x0 */
            uint32_t TZM_I2S_DMA_STS : 1;               /*18 SW=ro HW=wo 0x0 */
            uint32_t TZM_I2C_DMA_0_STS : 1;               /*19 SW=ro HW=wo 0x0 */
            uint32_t TZM_I2C_DMA_1_STS : 1;               /*20 SW=ro HW=wo 0x0 */
            uint32_t TZM_PDM_DMA_STS : 1;               /*21 SW=ro HW=wo 0x0 */
            uint32_t TZM_HKADC_DMA_STS : 1;               /*22 SW=ro HW=wo 0x0 */
            uint32_t Reserved : 9;               /*23:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECMSCINTSTATUS;

/*  SECMSCINTCLR DESCRIPTION :
Master Security Controller Interrupt Clear */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 9;               /*31:23 SW=ro HW=ro 0x0 */
            uint32_t TZM_HKADC_DMA_CLR : 1;               /*22 SW=w1s HW=rw 0x0 */
            uint32_t TZM_PDM_DMA_CLR : 1;               /*21 SW=w1s HW=rw 0x0 */
            uint32_t TZM_I2C_DMA_1_CLR : 1;               /*20 SW=w1s HW=rw 0x0 */
            uint32_t TZM_I2C_DMA_0_CLR : 1;               /*19 SW=w1s HW=rw 0x0 */
            uint32_t TZM_I2S_DMA_CLR : 1;               /*18 SW=w1s HW=rw 0x0 */
            uint32_t TZM_SPI_DMA_1_CLR : 1;               /*17 SW=w1s HW=rw 0x0 */
            uint32_t TZM_SPI_DMA_0_CLR : 1;               /*16 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UART_DMA_2_CLR : 1;               /*15 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UART_DMA_1_CLR : 1;               /*14 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UART_DMA_0_CLR : 1;               /*13 SW=w1s HW=rw 0x0 */
            uint32_t TZM_SDIO_DMA_CLR : 1;               /*12 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_MEM_CLR : 1;               /*11 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_CODE_CLR : 1;               /*10 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_CLR : 1;               /*9 SW=w1s HW=rw 0x0 */
            uint32_t TZM_XSPI2_DMA_CLR : 1;               /*8 SW=w1s HW=rw 0x0 */
            uint32_t TZM_CRYPTO_XIP2_CLR : 1;               /*7 SW=w1s HW=rw 0x0 */
            uint32_t TZM_XSPI1_DMA_CLR : 1;               /*6 SW=w1s HW=rw 0x0 */
            uint32_t TZM_CRYPTO_SUB_CLR : 1;               /*5 SW=w1s HW=rw 0x0 */
            uint32_t TZM_CRYPTO_XIP1_CLR : 1;               /*4 SW=w1s HW=rw 0x0 */
            uint32_t TZM_DEBUG_CLR : 1;               /*3 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UDMA_BASE_CLR : 1;               /*2 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_TX_CLR : 1;               /*1 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_RX_CLR : 1;               /*0 SW=w1s HW=rw 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t TZM_NPU_RX_CLR : 1;               /*0 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_TX_CLR : 1;               /*1 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UDMA_BASE_CLR : 1;               /*2 SW=w1s HW=rw 0x0 */
            uint32_t TZM_DEBUG_CLR : 1;               /*3 SW=w1s HW=rw 0x0 */
            uint32_t TZM_CRYPTO_XIP1_CLR : 1;               /*4 SW=w1s HW=rw 0x0 */
            uint32_t TZM_CRYPTO_SUB_CLR : 1;               /*5 SW=w1s HW=rw 0x0 */
            uint32_t TZM_XSPI1_DMA_CLR : 1;               /*6 SW=w1s HW=rw 0x0 */
            uint32_t TZM_CRYPTO_XIP2_CLR : 1;               /*7 SW=w1s HW=rw 0x0 */
            uint32_t TZM_XSPI2_DMA_CLR : 1;               /*8 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_CLR : 1;               /*9 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_CODE_CLR : 1;               /*10 SW=w1s HW=rw 0x0 */
            uint32_t TZM_NPU_MEM_CLR : 1;               /*11 SW=w1s HW=rw 0x0 */
            uint32_t TZM_SDIO_DMA_CLR : 1;               /*12 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UART_DMA_0_CLR : 1;               /*13 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UART_DMA_1_CLR : 1;               /*14 SW=w1s HW=rw 0x0 */
            uint32_t TZM_UART_DMA_2_CLR : 1;               /*15 SW=w1s HW=rw 0x0 */
            uint32_t TZM_SPI_DMA_0_CLR : 1;               /*16 SW=w1s HW=rw 0x0 */
            uint32_t TZM_SPI_DMA_1_CLR : 1;               /*17 SW=w1s HW=rw 0x0 */
            uint32_t TZM_I2S_DMA_CLR : 1;               /*18 SW=w1s HW=rw 0x0 */
            uint32_t TZM_I2C_DMA_0_CLR : 1;               /*19 SW=w1s HW=rw 0x0 */
            uint32_t TZM_I2C_DMA_1_CLR : 1;               /*20 SW=w1s HW=rw 0x0 */
            uint32_t TZM_PDM_DMA_CLR : 1;               /*21 SW=w1s HW=rw 0x0 */
            uint32_t TZM_HKADC_DMA_CLR : 1;               /*22 SW=w1s HW=rw 0x0 */
            uint32_t Reserved : 9;               /*23:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECMSCINTCLR;

/*  SECMSCINTEN DESCRIPTION :Master Security Controller Interrupt Enable */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 9;               /*31:23 SW=ro HW=ro 0x0 */
            uint32_t TZM_HKADC_DMA_EN : 1;               /*22 SW=rw HW=ro 0x0 */
            uint32_t TZM_PDM_DMA_EN : 1;               /*21 SW=rw HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_1_EN : 1;               /*20 SW=rw HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_0_EN : 1;               /*19 SW=rw HW=ro 0x0 */
            uint32_t TZM_I2S_DMA_EN : 1;               /*18 SW=rw HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_1_EN : 1;               /*17 SW=rw HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_0_EN : 1;               /*16 SW=rw HW=ro 0x0 */
            uint32_t TZM_UART_DMA_2_EN : 1;               /*15 SW=rw HW=ro 0x0 */
            uint32_t TZM_UART_DMA_1_EN : 1;               /*14 SW=rw HW=ro 0x0 */
            uint32_t TZM_UART_DMA_0_EN : 1;               /*13 SW=rw HW=ro 0x0 */
            uint32_t TZM_SDIO_DMA_EN : 1;               /*12 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_MEM_EN : 1;               /*11 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_CODE_EN : 1;               /*10 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_EN : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI2_DMA_EN : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP2_EN : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI1_DMA_EN : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_SUB_EN : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP1_EN : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t TZM_DEBUG_EN : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t TZM_UDMA_BASE_EN : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_TX_EN : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_RX_EN : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t TZM_NPU_RX_EN : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_TX_EN : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t TZM_UDMA_BASE_EN : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t TZM_DEBUG_EN : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP1_EN : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_SUB_EN : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI1_DMA_EN : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP2_EN : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI2_DMA_EN : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_EN : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_CODE_EN : 1;               /*10 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_MEM_EN : 1;               /*11 SW=rw HW=ro 0x0 */
            uint32_t TZM_SDIO_DMA_EN : 1;               /*12 SW=rw HW=ro 0x0 */
            uint32_t TZM_UART_DMA_0_EN : 1;               /*13 SW=rw HW=ro 0x0 */
            uint32_t TZM_UART_DMA_1_EN : 1;               /*14 SW=rw HW=ro 0x0 */
            uint32_t TZM_UART_DMA_2_EN : 1;               /*15 SW=rw HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_0_EN : 1;               /*16 SW=rw HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_1_EN : 1;               /*17 SW=rw HW=ro 0x0 */
            uint32_t TZM_I2S_DMA_EN : 1;               /*18 SW=rw HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_0_EN : 1;               /*19 SW=rw HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_1_EN : 1;               /*20 SW=rw HW=ro 0x0 */
            uint32_t TZM_PDM_DMA_EN : 1;               /*21 SW=rw HW=ro 0x0 */
            uint32_t TZM_HKADC_DMA_EN : 1;               /*22 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 9;               /*23:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECMSCINTEN;

/*  SECGPIOINTEN DESCRIPTION :TrustZone GPIO Secure Interrupt Enable */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 31;               /*31:1 SW=ro HW=ro 0x0 */
            uint32_t GPIO_SEC_IRQ_EN : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t GPIO_SEC_IRQ_EN : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 31;               /*1:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_SECGPIOINTEN;

/*  APBNSPPCBASE0 DESCRIPTION :Base 0 Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_0_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBNSPPCBASE0;

/*  APBNSPPCBASE1 DESCRIPTION :Base 1 (MPCs) Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_1_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_1_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBNSPPCBASE1;

/*  APBNSPPCBASE2 DESCRIPTION :Base 1 (Misc) Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_2_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_2_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBNSPPCBASE2;

/*  APBNSPPCSYS DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_SYS_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_SYS_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBNSPPCSYS;

/*  AHBNSPPCSYS DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_SYS_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_SYS_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_AHBNSPPCSYS;

/*  APBNSPPCPERIPH0 DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_0_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_0_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBNSPPCPERIPH0;

/*  APBNSPPCPERIPH1 DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_1_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_1_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBNSPPCPERIPH1;

/*  AHBNSPPCSDIO DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_SDIO_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_SDIO_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_AHBNSPPCSDIO;

/*  AHBNSPPCCXIP DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t PPC_CRYPTO_XIP2_NS_N : 16;               /*31:16 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP1_NS_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_CRYPTO_XIP1_NS_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP2_NS_N : 16;               /*16:31 SW=rw HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_AHBNSPPCCXIP;

/*  APBSPRVPPCBASE0 DESCRIPTION :Base 0 Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_0_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBSPRVPPCBASE0;

/*  APBSPRVPPCBASE1 DESCRIPTION :Base 1 (MPCs) Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_1_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_1_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBSPRVPPCBASE1;

/*  APBSPRVPPCBASE2 DESCRIPTION :Base 1 (Misc) Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_2_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_2_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBSPRVPPCBASE2;

/*  APBSPRVPPCSYS DESCRIPTION :System Control Sub Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_APB_SYS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_APB_SYS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBSPRVPPCSYS;

/*  AHBSPRVPPCSYS DESCRIPTION :System Control Sub Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_AHB_SYS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_AHB_SYS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_AHBSPRVPPCSYS;

/*  APBSPRVPPCPERIPH0 DESCRIPTION :System Control Sub Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_0_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_0_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBSPRVPPCPERIPH0;

/*  APBSPRVPPCPERIPH1 DESCRIPTION :System Control Sub Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_1_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_1_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_APBSPRVPPCPERIPH1;

/*  AHBSPRVPPCSDIO DESCRIPTION :System Control Sub Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_SDIO_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_SDIO_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_AHBSPRVPPCSDIO;

/*  AHBSPRVPPCCXIP DESCRIPTION :System Control Sub Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t PPC_CRYPTO_XIP2_PRV_N : 16;               /*31:16 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP1_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_CRYPTO_XIP1_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP2_PRV_N : 16;               /*16:31 SW=rw HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_AHBSPRVPPCCXIP;

/*  NSMSC DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 9;               /*31:23 SW=ro HW=ro 0x0 */
            uint32_t TZM_HKADC_DMA_NS : 1;               /*22 SW=ro HW=ro 0x0 */
            uint32_t TZM_PDM_DMA_NS : 1;               /*21 SW=ro HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_1_NS : 1;               /*20 SW=ro HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_0_NS : 1;               /*19 SW=ro HW=ro 0x0 */
            uint32_t TZM_I2S_DMA_NS : 1;               /*18 SW=ro HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_1_NS : 1;               /*17 SW=ro HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_0_NS : 1;               /*16 SW=ro HW=ro 0x0 */
            uint32_t TZM_UART_DMA_2_NS : 1;               /*15 SW=ro HW=ro 0x0 */
            uint32_t TZM_UART_DMA_1_NS : 1;               /*14 SW=ro HW=ro 0x0 */
            uint32_t TZM_UART_DMA_0_NS : 1;               /*13 SW=ro HW=ro 0x0 */
            uint32_t TZM_SDIO_DMA_NS : 1;               /*12 SW=ro HW=ro 0x0 */
            uint32_t TZM_NPU_MEM_NS : 1;               /*11 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_CODE_NS : 1;               /*10 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_NS : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI2_DMA_NS : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP2_NS : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI1_DMA_NS : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_SUB_NS : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP1_NS : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t TZM_DEBUG_NS : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t TZM_UDMA_BASE_NS : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_TX_NS : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_RX_NS : 1;               /*0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t TZM_NPU_RX_NS : 1;               /*0 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_TX_NS : 1;               /*1 SW=rw HW=ro 0x0 */
            uint32_t TZM_UDMA_BASE_NS : 1;               /*2 SW=rw HW=ro 0x0 */
            uint32_t TZM_DEBUG_NS : 1;               /*3 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP1_NS : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_SUB_NS : 1;               /*5 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI1_DMA_NS : 1;               /*6 SW=rw HW=ro 0x0 */
            uint32_t TZM_CRYPTO_XIP2_NS : 1;               /*7 SW=rw HW=ro 0x0 */
            uint32_t TZM_XSPI2_DMA_NS : 1;               /*8 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_SYS_CTRL_NS : 1;               /*9 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_CODE_NS : 1;               /*10 SW=rw HW=ro 0x0 */
            uint32_t TZM_NPU_MEM_NS : 1;               /*11 SW=rw HW=ro 0x0 */
            uint32_t TZM_SDIO_DMA_NS : 1;               /*12 SW=ro HW=ro 0x0 */
            uint32_t TZM_UART_DMA_0_NS : 1;               /*13 SW=ro HW=ro 0x0 */
            uint32_t TZM_UART_DMA_1_NS : 1;               /*14 SW=ro HW=ro 0x0 */
            uint32_t TZM_UART_DMA_2_NS : 1;               /*15 SW=ro HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_0_NS : 1;               /*16 SW=ro HW=ro 0x0 */
            uint32_t TZM_SPI_DMA_1_NS : 1;               /*17 SW=ro HW=ro 0x0 */
            uint32_t TZM_I2S_DMA_NS : 1;               /*18 SW=ro HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_0_NS : 1;               /*19 SW=ro HW=ro 0x0 */
            uint32_t TZM_I2C_DMA_1_NS : 1;               /*20 SW=ro HW=ro 0x0 */
            uint32_t TZM_PDM_DMA_NS : 1;               /*21 SW=ro HW=ro 0x0 */
            uint32_t TZM_HKADC_DMA_NS : 1;               /*22 SW=ro HW=ro 0x0 */
            uint32_t Reserved : 9;               /*23:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}security_ctrl_regs_NSMSC;

/*  NSGPIO DESCRIPTION :System Control Sub Non-Secure Access APB slave Peripheral Protection Control. Each field defines the Non-secure settings for an associated peripheral:

1: Allow Non-secure access
0: Disallow Non-secure access
Resets to 0 */
typedef union {
    struct {
        uint32_t GPIO_NS_PIN_N : 32;               /*31:0 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;


}security_ctrl_regs_NSGPIO;

typedef volatile struct inph_security_cntrl_base{

    security_ctrl_regs_SPCSECCTRL  SPCSECCTRL;
    security_ctrl_regs_BUSWAIT  BUSWAIT;
    security_ctrl_regs_SECRESPCFG  SECRESPCFG;
    security_ctrl_regs_NSCCFG  NSCCFG;
    /* MPC */
    security_ctrl_regs_SECMPCINTSTATUS  SECMPCINTSTATUS;
    security_ctrl_regs_SECMPCINTEN  SECMPCINTEN;
    /* ppc */
    security_ctrl_regs_SECPPCINTSTATUS  SECPPCINTSTATUS;
    security_ctrl_regs_SECPPCINTCLR  SECPPCINTCLR;
    security_ctrl_regs_SECPPCINTEN  SECPPCINTEN;
    /* Master Security controller */
    security_ctrl_regs_SECMSCINTSTATUS  SECMSCINTSTATUS;
    security_ctrl_regs_SECMSCINTCLR  SECMSCINTCLR;
    security_ctrl_regs_SECMSCINTEN  SECMSCINTEN;
    /* TrustZone GPIO secure interrupt */
    security_ctrl_regs_SECGPIOINTEN  SECGPIOINTEN;
    /* base0, base1, base2 */
    security_ctrl_regs_APBNSPPCBASE0  APBNSPPCBASE0;
    security_ctrl_regs_APBNSPPCBASE1  APBNSPPCBASE1;
    security_ctrl_regs_APBNSPPCBASE2  APBNSPPCBASE2;
    /* system control PPC */
    security_ctrl_regs_APBNSPPCSYS  APBNSPPCSYS;
    security_ctrl_regs_AHBNSPPCSYS  AHBNSPPCSYS;
    /* system control peripheral PPC */
    security_ctrl_regs_APBNSPPCPERIPH0  APBNSPPCPERIPH0;
    security_ctrl_regs_APBNSPPCPERIPH1  APBNSPPCPERIPH1;
    /* SDIO and XIP */
    security_ctrl_regs_AHBNSPPCSDIO  AHBNSPPCSDIO;
    security_ctrl_regs_AHBNSPPCCXIP  AHBNSPPCCXIP;
    /* privileged access */
    security_ctrl_regs_APBSPRVPPCBASE0  APBSPRVPPCBASE0;
    security_ctrl_regs_APBSPRVPPCBASE1  APBSPRVPPCBASE1;
    security_ctrl_regs_APBSPRVPPCBASE2  APBSPRVPPCBASE2;

    security_ctrl_regs_APBSPRVPPCSYS  APBSPRVPPCSYS;
    security_ctrl_regs_AHBSPRVPPCSYS  AHBSPRVPPCSYS;

    security_ctrl_regs_APBSPRVPPCPERIPH0  APBSPRVPPCPERIPH0;
    security_ctrl_regs_APBSPRVPPCPERIPH1  APBSPRVPPCPERIPH1;

    security_ctrl_regs_AHBSPRVPPCSDIO  AHBSPRVPPCSDIO;
    security_ctrl_regs_AHBSPRVPPCCXIP  AHBSPRVPPCCXIP;

    security_ctrl_regs_NSMSC  NSMSC;

    security_ctrl_regs_NSGPIO  NSGPIO;

    uint8_t filler34[0x1F7C];


} inph_security_cntrl_t;

/*  APBNSPRVPPCBASE0 DESCRIPTION :Base 0 Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_0_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_APBNSPRVPPCBASE0;

/*  APBNSPRVPPCBASE1 DESCRIPTION :Base 1 (MPCs) Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_1_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_1_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_APBNSPRVPPCBASE1;

/*  APBNSPRVPPCBASE2 DESCRIPTION :Base 1 (Misc) Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_2_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_2_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_APBNSPRVPPCBASE2;

/*  APBNSPRVPPCSYS DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_APB_SYS_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_APB_SYS_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_APBNSPRVPPCSYS;

/*  AHBNSPRVPPCSYS DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_AHB_SYS_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_AHB_SYS_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_AHBNSPRVPPCSYS;

/*  APBNSPRVPPCPERIPH0 DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_0_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_0_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_APBNSPRVPPCPERIPH0;

/*  APBNSPRVPPCPERIPH1 DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_1_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_1_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_APBNSPRVPPCPERIPH1;

/*  AHBNSPRVPPCSDIO DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_SDIO_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_SDIO_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_AHBNSPRVPPCSDIO;

/*  AHBNSPRVPPCCXIP DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t PPC_CRYPTO_XIP2_NS_PRV_N : 16;               /*31:16 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP1_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;

    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_CRYPTO_XIP1_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP2_NS_PRV_N : 16;               /*16:31 SW=rw HW=ro 0x0 */
        } bf;

    #endif
    uint32_t  dw;


}ns_privilege_regs_AHBNSPRVPPCCXIP;

typedef volatile struct inph_nspriv_security_base{
    ns_privilege_regs_APBNSPRVPPCBASE0  APBNSPRVPPCBASE0;
    ns_privilege_regs_APBNSPRVPPCBASE1  APBNSPRVPPCBASE1;
    ns_privilege_regs_APBNSPRVPPCBASE2  APBNSPRVPPCBASE2;
    ns_privilege_regs_APBNSPRVPPCSYS  APBNSPRVPPCSYS;
    ns_privilege_regs_AHBNSPRVPPCSYS  AHBNSPRVPPCSYS;
    ns_privilege_regs_APBNSPRVPPCPERIPH0  APBNSPRVPPCPERIPH0;
    ns_privilege_regs_APBNSPRVPPCPERIPH1  APBNSPRVPPCPERIPH1;
    ns_privilege_regs_AHBNSPRVPPCSDIO  AHBNSPRVPPCSDIO;
    ns_privilege_regs_AHBNSPRVPPCCXIP  AHBNSPRVPPCCXIP;

    uint8_t filler10[0x1FDC];


} inph_nspriv_security_t;

#endif

#endif /* __INPH_HELIUM_REGS_H__ */
