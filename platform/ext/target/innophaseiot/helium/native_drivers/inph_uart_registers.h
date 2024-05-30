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
 * @file    inph_uart.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Provides UART header functions for UART functions
 */

#ifndef INPH_UART_REGISTERS_H
#define INPH_UART_REGISTERS_H

/* Private headers ----------------------------------------------------------*/
#include "inph_utils.h"

/*  RBRTHR DESCRIPTION :Receiver Buffer Register (R when DLAB=0)
Transmitter Holding Register (W when DLAB=0) */
typedef union {
    struct {
        __IOM uint32_t RBRTHR : 8; /*0:7 SW=rw HW=ro 0x0 */
    } bf;
    __IOM uint32_t dw;

} uart_RBRTHR_t;

/*  IER DESCRIPTION :Interrupt Enable Register (R/W when DLAB=0) */
typedef union {
    struct {
        __IOM uint32_t ENRCVRDAI : 1; /*0 SW=rw HW=ro 0x0 */
        __IOM uint32_t ENXMITHEI : 1; /*1 SW=rw HW=ro 0x0 */
        __IOM uint32_t ENRCVRLSI : 1; /*2 SW=rw HW=ro 0x0 */
        __IOM uint32_t resv3 : 5;
    } bf;
    __IOM uint32_t dw;

} uart_IER_t;

/*  IIRFCR DESCRIPTION :Interrupt Identification Register (R)
FIFO Control Register (W) */
typedef union {
    struct {
        __IOM uint32_t INTPENDFIFOEN : 1;  /*0 SW=rw HW=ro 0x0 */
        __IOM uint32_t INTID0RCVRFRST : 1; /*1 SW=rw HW=ro 0x0 */
        __IOM uint32_t INTID1XMITFRST : 1; /*2 SW=rw HW=ro 0x0 */
        __IOM uint32_t INTID2 : 1;         /*3 SW=ro HW=ro 0x0 */

        __IOM uint32_t resv4 : 2;
        __IOM uint32_t FIFOENRCVRTRIGLSB : 1; /*6 SW=rw HW=ro 0x0 */
        __IOM uint32_t FIFOENRCVRTRIGMSB : 1; /*7 SW=rw HW=ro 0x0 */
    } bf;
    __IOM uint32_t dw;

} uart_IIRFCR_t;

/*  LCR DESCRIPTION :Line control Register */
typedef union {
    struct {
        __IOM uint32_t WLEN : 2;     /*0:1 SW=rw HW=ro 0x0 */
        __IOM uint32_t NUMSTOP : 1;  /*2 SW=rw HW=ro 0x0 */
        __IOM uint32_t PARITYEN : 1; /*3 SW=rw HW=ro 0x0 */
        __IOM uint32_t EVEN : 1;     /*4 SW=rw HW=ro 0x0 */
        __IOM uint32_t STICK : 1;    /*5 SW=rw HW=ro 0x0 */
        __IOM uint32_t SETBR : 1;    /*6 SW=rw HW=ro 0x0 */
        __IOM uint32_t DLAB : 1;     /*7 SW=rw HW=ro 0x0 */
    } bf;
    __IOM uint32_t dw;

} uart_LCR_t;

/*  MCR DESCRIPTION :Modem control Register */
typedef union {
    struct {
        __OM uint32_t DTR : 1;  /*0 SW=wo HW=ro 0x0 */
        __OM uint32_t RTS : 1;  /*1 SW=wo HW=ro 0x0 */
        __OM uint32_t OUT1 : 1; /*2 SW=wo HW=ro 0x0 */
        __OM uint32_t OUT2 : 1; /*3 SW=wo HW=ro 0x0 */
        __OM uint32_t LOOP : 1; /*4 SW=wo HW=ro 0x0 */
        __OM uint32_t resv5 : 3;
    } bf;
    __OM uint32_t dw;

} uart_MCR_t;

/*  LSR DESCRIPTION :Line Status Register */
typedef union {
    struct {
        __IM uint32_t DRDY : 1;     /*0 SW=ro HW=ro 0x0 */
        __IM uint32_t OERR : 1;     /*1 SW=ro HW=ro 0x0 */
        __IM uint32_t PERR : 1;     /*2 SW=ro HW=ro 0x0 */
        __IM uint32_t FERR : 1;     /*3 SW=ro HW=ro 0x0 */
        __IM uint32_t BINT : 1;     /*4 SW=ro HW=ro 0x0 */
        __IM uint32_t XMITHRE : 1;  /*5 SW=ro HW=ro 0x1 */
        __IM uint32_t XMITE : 1;    /*6 SW=ro HW=ro 0x1 */
        __IM uint32_t ERRRCVRF : 1; /*7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_LSR_t;

/*  MSR DESCRIPTION :Modem Status Register */
typedef union {
    struct {
        __IM uint32_t DCTS : 1; /*0 SW=ro HW=ro 0x0 */
        __IM uint32_t DDSR : 1; /*1 SW=ro HW=ro 0x0 */
        __IM uint32_t TERI : 1; /*2 SW=ro HW=ro 0x0 */
        __IM uint32_t DDCD : 1; /*3 SW=ro HW=ro 0x0 */
        __IM uint32_t CTS : 1;  /*4 SW=ro HW=ro 0x0 */
        __IM uint32_t DSR : 1;  /*5 SW=ro HW=ro 0x0 */
        __IM uint32_t RI : 1;   /*6 SW=ro HW=ro 0x0 */
        __IM uint32_t DCD : 1;  /*7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_MSR_t;

/*  SCR DESCRIPTION :Scratch Register */
typedef union {
    struct {
        __IOM uint32_t SCR : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IOM uint32_t dw;

} uart_SCR_t;

/*  LSBDL DESCRIPTION :LSB of Divisor Latch */
typedef union {
    struct {
        __IM uint32_t LSBDL : 8; /*0:7 SW=rw HW=ro 0x1 */
    } bf;
    __IM uint32_t dw;

} uart_LSBDL_t;

/*  MSBDL DESCRIPTION :MSB of Divisor Latch */
typedef union {
    struct {
        __IM uint32_t MSBDL : 8; /*0:7 SW=rw HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_MSBDL_t;

/*  TXFFL DESCRIPTION :Tx Fifo Fill Level */
typedef union {
    struct {
        __IM uint32_t TXFFL : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_TxFFL_t;

/*  RXFFL DESCRIPTION :Rx Fifo Fill Level */
typedef union {
    struct {
        __IM uint32_t RXFFL : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_RxFFL_t;

/*  REV0 DESCRIPTION :Revision register 0 */
typedef union {
    struct {
        __IM uint32_t REV0 : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_REV0_t;

/*  REV1 DESCRIPTION :Revision register 1 */
typedef union {
    struct {
        __IM uint32_t REV1 : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_REV1_t;

/*  REV2 DESCRIPTION :Revision register 2 */
typedef union {
    struct {
        __IM uint32_t REV2 : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_REV2_t;

/*  REV3 DESCRIPTION :Revision register 3 */
typedef union {
    struct {
        __IM uint32_t REV3 : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IM uint32_t dw;

} uart_REV3_t;

/*  CLKDIVP0 DESCRIPTION :Clock divider P value 0 */
typedef union {
    struct {
        __IOM uint32_t CLKDIVP0 : 8; /*0:7 SW=ro HW=ro 0x1 */
    } bf;
    __IOM uint32_t dw;

} uart_CLKDIVP0_t;

/*  CLKDIVP1 DESCRIPTION :Clock divider P value 1 */
typedef union {
    struct {
        __IOM uint32_t CLKDIVP1 : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IOM uint32_t dw;

} uart_CLKDIVP1_t;

/*  CLKDIVQ0 DESCRIPTION :Clock divider Q value 0 */
typedef union {
    struct {
        __IOM uint32_t CLKDIVQ0 : 8; /*0:7 SW=ro HW=ro 0x1 */
    } bf;
    __IOM uint32_t dw;

} uart_CLKDIVQ0_t;

/*  CLKDIVQ1 DESCRIPTION :Clock divider Q value 1 */
typedef union {
    struct {
        __IOM uint32_t CLKDIVQ1 : 8; /*0:7 SW=ro HW=ro 0x0 */
    } bf;
    __IOM uint32_t dw;

} uart_CLKDIVQ1_t;

/*  AXISTCONTROL DESCRIPTION :AXI ST control */
typedef union {
    struct {
        __IOM uint32_t AXISIEN : 1; /*0 SW=rw HW=ro 0x0 */
        __IOM uint32_t AXISOEN : 1; /*1 SW=rw HW=ro 0x0 */
        __IOM uint32_t resv2 : 6;
    } bf;
    __IOM uint32_t dw;

} uart_AXISTcontrol_t;

typedef struct inph_uart_base {
    uart_RBRTHR_t RBRTHR;

    uart_IER_t IER;

    uart_IIRFCR_t IIRFCR;

    uart_LCR_t LCR;

    uart_MCR_t MCR;

    uart_LSR_t LSR;

    uart_MSR_t MSR;

    uart_SCR_t SCR;

    uart_LSBDL_t LSBDL;

    uart_MSBDL_t MSBDL;

    uart_TxFFL_t TxFFL;

    uart_RxFFL_t RxFFL;

    uart_REV0_t REV0;

    uart_REV1_t REV1;

    uart_REV2_t REV2;

    uart_REV3_t REV3;

    uart_CLKDIVP0_t CLKDIVP0;

    uart_CLKDIVP1_t CLKDIVP1;

    uart_CLKDIVQ0_t CLKDIVQ0;

    uart_CLKDIVQ1_t CLKDIVQ1;

    uart_AXISTcontrol_t AXISTcontrol;

} inph_uart_t;

#endif /* INPH_UART_REGISTERS_H */
