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

#ifndef __INPH_UART_REGISTERS_H
#define __INPH_UART_REGISTERS_H

/* Private headers ----------------------------------------------------------*/
#include "tfm_utils.h"

/*  DLL DESCRIPTION :Divisor Latch (Low).
If UART_16550_COMPATIBLE = No, then this register can be accessed only when the DLAB bit (LCR[7]) is set and the UART is not busy - that is, USR[0] is 0; otherwise this register can be accessed only when the DLAB bit (LCR[7]) is set. */
typedef union {
    struct {
         uint32_t DLL : 8;               /*0:7 SW=rw HW=ro 0x0 */
         uint32_t RSVDDLL31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_DLL;

/*  THR DESCRIPTION :Transmit Holding Register.
This register can be accessed only when the DLAB bit (LCR[7]) is cleared. */
typedef union {
    struct {
         uint32_t THR : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDTHR : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_THR;

/*  DLH DESCRIPTION :Divisor Latch High (DLH) Register.
If UART_16550_COMPATIBLE = No, then this register can be accessed only when the DLAB bit (LCR[7]) is set and the UART is not busy, that is, USR[0] is 0; otherwise this register can be accessed only when the DLAB bit (LCR[7]) is set. */
typedef union {
    struct {
         uint32_t dlh : 8;               /*0:7 SW=rw HW=ro 0x0 */
         uint32_t RSVDDLH : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_DLH;

/*  FCR DESCRIPTION :This register is only valid when the DW_apb_uart is configured to have FIFO's implemented (FIFO_MODE != NONE). If FIFO's are not implemented, this register does not exist and writing to this register address will have no effect. */
typedef union {
    struct {
         uint32_t FIFOE : 1;               /*0 SW=wo HW=ro 0x0 */
         uint32_t RFIFOR : 1;               /*1 SW=wo HW=ro 0x0 */
         uint32_t XFIFOR : 1;               /*2 SW=wo HW=ro 0x0 */
         uint32_t DMAM : 1;               /*3 SW=wo HW=ro 0x0 */
         uint32_t TET : 2;               /*4:5 SW=wo HW=ro 0x0 */
         uint32_t RT : 2;               /*6:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDFCR31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_FCR;

/*  STHR0 DESCRIPTION :Shadow Transmit Holding Register. This register is valid only when the DW_apb_uart is configured to have additional shadow registers
implemented (SHADOW = YES). If shadow registers are not implemented, this register does not exist, and
reading from this register address returns 0.

This register can be accessed only when the DLAB bit (LCR[7]) is cleared. */
typedef union {
    struct {
         uint32_t STHRn : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHRn : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR0;

/*  STHR1 DESCRIPTION :Shadow Transmit Holding Register 1 */
typedef union {
    struct {
         uint32_t STHR1 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR1 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR1;

/*  STHR2 DESCRIPTION :Shadow Transmit Holding Register 2 */
typedef union {
    struct {
         uint32_t sthr2 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR2 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR2;

/*  STHR3 DESCRIPTION :Shadow Transmit Holding Register 3 */
typedef union {
    struct {
         uint32_t sthr3 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR3 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR3;

/*  STHR4 DESCRIPTION :Shadow Transmit Holding Register 4 */
typedef union {
    struct {
         uint32_t sthr4 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR4 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR4;

/*  STHR5 DESCRIPTION :Shadow Transmit Holding Register 5 */
typedef union {
    struct {
         uint32_t sthr5 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR5 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR5;

/*  STHR6 DESCRIPTION :Shadow Transmit Holding Register 6 */
typedef union {
    struct {
         uint32_t sthr6 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR6 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR6;

/*  STHR7 DESCRIPTION :Shadow Transmit Holding Register 7 */
typedef union {
    struct {
         uint32_t sthr7 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR7 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR7;

/*  STHR8 DESCRIPTION :Shadow Transmit Holding Register 8 */
typedef union {
    struct {
         uint32_t sthr8 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR8;

/*  STHR9 DESCRIPTION :Shadow Transmit Holding Register 9 */
typedef union {
    struct {
         uint32_t sthr9 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR9 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR9;

/*  STHR10 DESCRIPTION :Shadow Transmit Holding Register 10 */
typedef union {
    struct {
         uint32_t sthr10 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR10 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR10;

/*  STHR11 DESCRIPTION :Shadow Transmit Holding Register 11 */
typedef union {
    struct {
         uint32_t sthr11 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR11 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR11;

/*  STHR12 DESCRIPTION :Shadow Transmit Holding Register 12 */
typedef union {
    struct {
         uint32_t sthr12 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR12 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR12;

/*  STHR13 DESCRIPTION :Shadow Transmit Holding Register 13 */
typedef union {
    struct {
         uint32_t sthr13 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR13 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR13;

/*  STHR14 DESCRIPTION :Shadow Transmit Holding Register 14 */
typedef union {
    struct {
         uint32_t sthr14 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR14 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR14;

/*  STHR15 DESCRIPTION :Shadow Transmit Holding Register 15 */
typedef union {
    struct {
         uint32_t STHR15 : 8;               /*0:7 SW=wo HW=ro 0x0 */
         uint32_t RSVDSTHR15 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STHR15;

/*  RBR DESCRIPTION :Receive Buffer Register.
This register can be accessed only when the DLAB bit (LCR[7]) is cleared. */
typedef union {
    struct {
         uint32_t RBR : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDRBR : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_RBR;

/*  IER DESCRIPTION :Interrupt Enable Register.
This register can be accessed only when the DLAB bit (LCR[7]) is cleared. */
typedef union {
    struct {
         uint32_t ERBFI : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t ETBEI : 1;               /*1 SW=rw HW=ro 0x0 */
         uint32_t ELSI : 1;               /*2 SW=rw HW=ro 0x0 */
         uint32_t EDSSI : 1;               /*3 SW=rw HW=ro 0x0 */
         uint32_t ELCOLR : 1;               /*4 SW=ro HW=ro 0x0 */
         uint32_t RSVDIER6to5 : 2;               /*5:6 SW=ro HW=ro 0x0 */
         uint32_t PTIME : 1;               /*7 SW=rw HW=ro 0x0 */
         uint32_t RSVDIER31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_IER;

/*  IIR DESCRIPTION :Interrupt Identification Register */
typedef union {
    struct {
         uint32_t IID : 4;               /*0:3 SW=ro HW=ro 0x1 */
         uint32_t RSVDIIR5to4 : 2;               /*4:5 SW=ro HW=ro 0x0 */
         uint32_t FIFOSE : 2;               /*6:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDIIR31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_IIR;

/*  LCR DESCRIPTION :Line Control Register */
typedef union {
    struct {
         uint32_t DLS : 2;               /*0:1 SW=rw HW=ro 0x0 */
         uint32_t STOP : 1;               /*2 SW=rw HW=ro 0x0 */
         uint32_t PEN : 1;               /*3 SW=rw HW=ro 0x0 */
         uint32_t EPS : 1;               /*4 SW=rw HW=ro 0x0 */
         uint32_t SP : 1;               /*5 SW=rw HW=ro 0x0 */
         uint32_t BC : 1;               /*6 SW=rw HW=ro 0x0 */
         uint32_t DLAB : 1;               /*7 SW=rw HW=ro 0x0 */
         uint32_t RSVDLCR31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_LCR;

/*  MCR DESCRIPTION :Modem Control Register */
typedef union {
    struct {
         uint32_t DTR : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RTS : 1;               /*1 SW=rw HW=ro 0x0 */
         uint32_t OUT1 : 1;               /*2 SW=rw HW=ro 0x0 */
         uint32_t OUT2 : 1;               /*3 SW=rw HW=ro 0x0 */
         uint32_t LoopBack : 1;               /*4 SW=rw HW=ro 0x0 */
         uint32_t AFCE : 1;               /*5 SW=rw HW=ro 0x0 */
         uint32_t SIRE : 1;               /*6 SW=rw HW=ro 0x0 */
         uint32_t RSVDMCR31to7 : 25;               /*7:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_MCR;

/*  LSR DESCRIPTION :Line Status Register */
typedef union {
    struct {
         uint32_t DR : 1;               /*0 SW=ro HW=ro 0x0 */
         uint32_t OE : 1;               /*1 SW=ro HW=ro 0x0 */
         uint32_t PE : 1;               /*2 SW=ro HW=ro 0x0 */
         uint32_t FE : 1;               /*3 SW=ro HW=ro 0x0 */
         uint32_t BI : 1;               /*4 SW=ro HW=ro 0x0 */
         uint32_t THRE : 1;               /*5 SW=ro HW=ro 0x1 */
         uint32_t TEMT : 1;               /*6 SW=ro HW=ro 0x1 */
         uint32_t RFE : 1;               /*7 SW=ro HW=ro 0x0 */
         uint32_t RSVDADDRRCVD : 1;               /*8 SW=ro HW=ro 0x0 */
         uint32_t RSVDLSR31to9 : 23;               /*9:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_LSR;

/*  MSR DESCRIPTION :Whenever bits 0, 1, 2 or 3 is set to logic one, to indicate
a change on the modem control inputs, a modem status interrupt will be generated
if enabled via the IER regardless of when the change occurred. The bits
(bits 0, 1, 3) can be set after a reset-even though their respective modem signals are
inactive-because the synchronized version of the modem signals have a reset value of 0 and change to value 1 after reset. To
prevent unwanted interrupts due to this change, a read of the MSR register can be performed after reset. */
typedef union {
    struct {
         uint32_t DCTS : 1;               /*0 SW=ro HW=ro 0x0 */
         uint32_t DDSR : 1;               /*1 SW=ro HW=ro 0x0 */
         uint32_t TERI : 1;               /*2 SW=ro HW=ro 0x0 */
         uint32_t DDCD : 1;               /*3 SW=ro HW=ro 0x0 */
         uint32_t CTS : 1;               /*4 SW=ro HW=ro 0x0 */
         uint32_t DSR : 1;               /*5 SW=ro HW=ro 0x0 */
         uint32_t RI : 1;               /*6 SW=ro HW=ro 0x0 */
         uint32_t DCD : 1;               /*7 SW=ro HW=ro 0x0 */
         uint32_t RSVDMSR31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_MSR;

/*  SCR DESCRIPTION :Scratchpad Register */
typedef union {
    struct {
         uint32_t SCR : 8;               /*0:7 SW=rw HW=ro 0x0 */
         uint32_t RSVDSCR31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SCR;

/*  LPDLL DESCRIPTION :Low Power Divisor Latch Low Register.

This register is only valid when the DW_apb_uart is configured to have SIR low-power reception
capabilities implemented (SIR_LP_RX = Yes). If SIR low-power reception capabilities are not implemented,
this register does not exist and reading from this register address returns 0.

If UART_16550_COMPATIBLE = No, then this register can be accessed only when the DLAB bit (LCR[7]) is
set and the UART is not busy, that is, USR[0] is 0; otherwise this register can be accessed only when the
DLAB bit (LCR[7]) is set. */
typedef union {
    struct {
         uint32_t LPDLL : 8;               /*0:7 SW=rw HW=ro 0x0 */
         uint32_t RSVDLPDLL31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_LPDLL;

/*  LPDLH DESCRIPTION :Low Power Divisor Latch High Register.

This register is valid only when the DW_apb_uart is configured to have SIR low-power reception
capabilities implemented (SIR_LP_RX = Yes). If SIR low-power reception capabilities are not implemented,
this register does not exist and reading from this register address returns 0.

If UART_16550_COMPATIBLE = No, then this register can be accessed only when the DLAB bit (LCR[7]) is
set and the UART is not busy that is, USR[0] is 0; otherwise this register can be accessed only when the
DLAB bit (LCR[7]) is set. */
typedef union {
    struct {
         uint32_t LPDLH : 8;               /*0:7 SW=rw HW=ro 0x0 */
         uint32_t RSVDLPDLH31to8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_LPDLH;

/*  SRBR0 DESCRIPTION :This register is valid only when the DW_apb_uart is configured to have additional shadow registers
implemented (SHADOW = YES). If shadow registers are not implemented, this register does not exist and
reading from this register address returns 0.

This register can be accessed only when the DLAB bit (LCR[7]) is cleared. */
typedef union {
    struct {
         uint32_t SRBRn : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBRn : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR0;

/*  SRBR1 DESCRIPTION :Shadow Receive Buffer Register 1 */
typedef union {
    struct {
         uint32_t SRBR1 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR1 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR1;

/*  SRBR2 DESCRIPTION :Shadow Receive Buffer Register 2 */
typedef union {
    struct {
         uint32_t SRBR2 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR2 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR2;

/*  SRBR3 DESCRIPTION :Shadow Receive Buffer Register 3 */
typedef union {
    struct {
         uint32_t SRBR3 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR3 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR3;

/*  SRBR4 DESCRIPTION :Shadow Receive Buffer Register 4 */
typedef union {
    struct {
         uint32_t SRBR4 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR4 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR4;

/*  SRBR5 DESCRIPTION :Shadow Receive Buffer Register 5 */
typedef union {
    struct {
         uint32_t SRBR5 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR5 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR5;

/*  SRBR6 DESCRIPTION :Shadow Receive Buffer Register 6 */
typedef union {
    struct {
         uint32_t SRBR6 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR6 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR6;

/*  SRBR7 DESCRIPTION :Shadow Receive Buffer Register 7 */
typedef union {
    struct {
         uint32_t SRBR7 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR7 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR7;

/*  SRBR8 DESCRIPTION :Shadow Receive Buffer Register 8 */
typedef union {
    struct {
         uint32_t SRBR8 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR8 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR8;

/*  SRBR9 DESCRIPTION :Shadow Receive Buffer Register 9 */
typedef union {
    struct {
         uint32_t SRBR9 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR9 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR9;

/*  SRBR10 DESCRIPTION :Shadow Receive Buffer Register 10 */
typedef union {
    struct {
         uint32_t SRBR10 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR10 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR10;

/*  SRBR11 DESCRIPTION :Shadow Receive Buffer Register 11 */
typedef union {
    struct {
         uint32_t SRBR11 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR11 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR11;

/*  SRBR12 DESCRIPTION :Shadow Receive Buffer Register 12 */
typedef union {
    struct {
         uint32_t SRBR12 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR12 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR12;

/*  SRBR13 DESCRIPTION :Shadow Receive Buffer Register 13 */
typedef union {
    struct {
         uint32_t SRBR13 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR13 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR13;

/*  SRBR14 DESCRIPTION :Shadow Receive Buffer Register 14 */
typedef union {
    struct {
         uint32_t SRBR14 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR14 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR14;

/*  SRBR15 DESCRIPTION :Shadow Receive Buffer Register 15 */
typedef union {
    struct {
         uint32_t SRBR15 : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDSRBR15 : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRBR15;

/*  FAR DESCRIPTION :FIFO Access Register */
typedef union {
    struct {
         uint32_t FAR : 1;               /*0 SW=ro HW=ro 0x0 */
         uint32_t RSVDFAR31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_FAR;

/*  USR DESCRIPTION :UART Status register. */
typedef union {
    struct {
         uint32_t BUSY : 1;               /*0 SW=ro HW=rw 0x0 */
         uint32_t TFNF : 1;               /*1 SW=ro HW=rw 0x1 */
         uint32_t TFE : 1;               /*2 SW=ro HW=rw 0x1 */
         uint32_t RFNE : 1;               /*3 SW=ro HW=rw 0x0 */
         uint32_t RFF : 1;               /*4 SW=ro HW=rw 0x0 */
         uint32_t RSVDUSR31to5 : 27;               /*5:31 SW=ro HW=rw 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_USR;

/*  TFL DESCRIPTION :TFL register is valid only when the DW_apb_uart is configured to have additional FIFO status registers
implemented (FIFO_STAT = YES). If status registers are not implemented, this register does not exist and
reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t tfl : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDTFL31toADDRWIDTH : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_TFL;

/*  RFL DESCRIPTION :RFL register is valid only when the DW_apb_uart is configured to have additional FIFO status registers
implemented (FIFO_STAT = YES). If status registers are not implemented, this register does not exist and
reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t rfl : 8;               /*0:7 SW=ro HW=ro 0x0 */
         uint32_t RSVDRFL31toADDRWIDTH : 24;               /*8:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_RFL;

/*  SRR DESCRIPTION :This register is valid only when the DW_apb_uart is configured to have additional shadow registers
implemented (SHADOW = YES). If shadow registers are not implemented, this register does not exist and
reading from this register address returns 0.

For more information on the amount of time that serial clock modules need in order to see new register
values and reset their respective state machines, refer to the 'Clock Support' subsection in the data book. */
typedef union {
    struct {
         uint32_t UR : 1;               /*0 SW=wo HW=ro 0x0 */
         uint32_t RFR : 1;               /*1 SW=wo HW=ro 0x0 */
         uint32_t XFR : 1;               /*2 SW=wo HW=ro 0x0 */
         uint32_t RSVDSRR31to3 : 29;               /*3:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRR;

/*  SRTS DESCRIPTION :SRTS register is valid only when the DW_apb_uart is configured to have additional shadow registers
implemented (SHADOW = YES). If shadow registers are not implemented, this register does not exist and
reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t SRTS : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDSRTS31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRTS;

/*  SBCR DESCRIPTION :SBCR register is valid only when the DW_apb_uart is configured to have additional shadow registers
implemented (SHADOW = YES). If shadow registers are not implemented, this register does not exist and
reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t SBCB : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDSBCR31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SBCR;

/*  SDMAM DESCRIPTION :This register is valid only when the DW_apb_uart is configured to have additional FIFO registers implemented (FIFO_MODE != None) and additional shadow registers implemented (SHADOW = YES). If these registers are not implemented, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t SDMAM : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDSDMAM31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SDMAM;

/*  SFE DESCRIPTION :SFE register is valid only when the DW_apb_uart is configured to have additional FIFO registers
implemented (FIFO_MODE != None) and additional shadow registers implemented (SHADOW = YES). If these registers are not implemented, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t SFE : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDSFE31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SFE;

/*  SRT DESCRIPTION :SRT register is valid only when the DW_apb_uart is configured to have additional FIFO registers
implemented (FIFO_MODE != None) and additional shadow registers implemented (SHADOW = YES). If these registers are not implemented, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t SRT : 2;               /*0:1 SW=rw HW=ro 0x0 */
         uint32_t RSVDSRT31to2 : 30;               /*2:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_SRT;

/*  STET DESCRIPTION :This register is valid only when the DW_apb_uart is configured to have FIFOs implemented
(FIFO_MODE != NONE) and THRE interrupt support implemented (THRE_MODE_USER = Enabled) and
additional shadow registers implemented (SHADOW = YES). If FIFOs are not implemented or THRE interrupt support is not implemented or shadow registers are not implemented, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t STET : 2;               /*0:1 SW=rw HW=ro 0x0 */
         uint32_t RSVDSTET31to2 : 30;               /*2:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_STET;

/*  HTX DESCRIPTION :Halt TX */
typedef union {
    struct {
         uint32_t HTX : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDHTX31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_HTX;

/*  DMASA DESCRIPTION :DMA Software Acknowledge Register */
typedef union {
    struct {
         uint32_t DMASA : 1;               /*0 SW=wo HW=ro 0x0 */
         uint32_t RSVDDMASA31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_DMASA;

/*  TCR DESCRIPTION :This register is used to enable or disable RS485 mode and also control the polarity values for Driven enable
(de) and Receiver Enable (re) signals.

This register is only valid when the DW_apb_uart is configured to have RS485 interface implemented
(UART_RS485_INTERFACE_EN = ENABLED). If RS485 interface is not implemented, this register does not
exist and reading from this register address returns zero. */
typedef union {
    struct {
         uint32_t RS485EN : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t REPOL : 1;               /*1 SW=rw HW=ro 0x1 */
         uint32_t DEPOL : 1;               /*2 SW=rw HW=ro 0x1 */
         uint32_t XFERMODE : 2;               /*3:4 SW=rw HW=ro 0x0 */
         uint32_t RSVDTCR31to5 : 27;               /*5:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_TCR;

/*  DEEN DESCRIPTION :The Driver Output Enable Register (DE_EN) is used to control the assertion and de-assertion of the DE
signal.

This register is only valid when the DW_apb_uart is configured to have RS485 interface implemented
(UART_RS485_INTERFACE_EN = ENABLED). If RS485 interface is not implemented, this register does not
exist and reading from this register address will return zero. */
typedef union {
    struct {
         uint32_t DEEnable : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDDEEN31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_DEEN;

/*  REEN DESCRIPTION :The Receiver Output Enable Register (RE_EN) is used to control the assertion and de-assertion of the RE signal.

This register is only valid when the DW_apb_uart is configured to have RS485 interface implemented
(UART_RS485_INTERFACE_EN = ENABLED). If the RS485 interface is not implemented, this register does
not exist and reading from this register address will return zero. */
typedef union {
    struct {
         uint32_t REEnable : 1;               /*0 SW=rw HW=ro 0x0 */
         uint32_t RSVDREEN31to1 : 31;               /*1:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_REEN;

/*  DET DESCRIPTION :The Driver Output Enable Timing Register (DET) is used to control the DE assertion and de-assertion timings of 'de' signal.
This register is only valid when the DW_apb_uart is configured to have RS485 interface implemented (UART_RS485_INTERFACE = ENABLED). If RS485 interface is not implemented, this register does not exist and reading from this register address will return zero. */
typedef union {
    struct {
         uint32_t DEAssertionTime : 8;               /*0:7 SW=rw HW=ro 0x0 */
         uint32_t RSVDDEAT15to8 : 8;               /*8:15 SW=ro HW=ro 0x0 */
         uint32_t DEDeassertionTime : 8;               /*16:23 SW=rw HW=ro 0x0 */
         uint32_t RSVDDEDEAT31to24 : 8;               /*24:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_DET;

/*  TAT DESCRIPTION :The Turn Around Timing Register (TAT) is used to hold the turnaround time between switching of 're' and
'de' signals.

This register is only valid when the DW_apb_uart is configured to have the RS485 interface implemented
(UART_RS485_INTERFACE_EN = ENABLED). If RS485 interface is not implemented, this register does not
exist and reading from this register address will return zero. */
typedef union {
    struct {
         uint32_t DEtoRE : 16;               /*0:15 SW=rw HW=ro 0x0 */
         uint32_t REtoDE : 16;               /*16:31 SW=rw HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_TAT;

/*  DLF DESCRIPTION :This register is only valid when the DW_apb_uart is configured to have Fractional Baud rate Divisor implemented (FRACTIONAL_BAUD_DIVISOR_EN = ENABLED). If Fractional Baud rate divisor is not implemented, this register does not exist and reading from this register address will return zero. */
typedef union {
    struct {
         uint32_t DLF : 6;               /*0:5 SW=rw HW=ro 0x0 */
         uint32_t RSVDDLF : 26;               /*6:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_DLF;

/*  LCREXT DESCRIPTION :Line Extended Control Register */
typedef union {
    struct {
         uint32_t RSVDDLSE : 1;               /*0 SW=ro HW=rw 0x0 */
         uint32_t RSVDADDRMATCH : 1;               /*1 SW=ro HW=rw 0x0 */
         uint32_t RSVDSENDADDR : 1;               /*2 SW=ro HW=rw 0x0 */
         uint32_t RSVDTRANSMITMODE : 1;               /*3 SW=ro HW=rw 0x0 */
         uint32_t CGEN : 1;               /*4 SW=rw HW=rw 0x1 */
         uint32_t RSVDLCREXT : 27;               /*5:31 SW=ro HW=rw 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_LCREXT;

/*  UARTPROTLEVEL DESCRIPTION :UART Protection level register */
typedef union {
    struct {
         uint32_t UARTPROTLEVEL : 3;               /*0:2 SW=rw HW=ro 0x2 */
         uint32_t RSVDUARTPROTLEVEL : 29;               /*3:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_UARTPROTLEVEL;

/*  REGTIMEOUTRST DESCRIPTION :Name: Register timeout counter reset register
This register keeps the reset value of reg_timer counter register.
The reset value of the register is REG_TIMEOUT_DEFAULT
The default reset value can be further modified if HC_REG_TIMEOUT_VALUE = 0.
The final programmed value (or the default reset value if not programmed)
determines what value the reg_timeout counter register starts counting down
from. A zero on the counter will break the hung transaction with PSLVERR high */
typedef union {
    struct {
         uint32_t REGTIMEOUTRST : 4;               /*0:3 SW=rw HW=rw 0x8 */
         uint32_t RSVDREGTIMEOUTRST : 28;               /*4:31 SW=ro HW=rw 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_REGTIMEOUTRST;

/*  CPR DESCRIPTION :Component Parameter Register.This register is valid only when UART_ADD_ENCODED_PARAMS = 1. If the UART_ADD_ENCODED_PARAMS parameter is not set, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t APBDATAWIDTH : 2;               /*0:1 SW=ro HW=ro 0x2 */
         uint32_t RSVDCPR3to2 : 2;               /*2:3 SW=ro HW=ro 0x0 */
         uint32_t AFCEMODE : 1;               /*4 SW=ro HW=ro 0x1 */
         uint32_t THREMODE : 1;               /*5 SW=ro HW=ro 0x1 */
         uint32_t SIRMODE : 1;               /*6 SW=ro HW=ro 0x1 */
         uint32_t SIRLPMODE : 1;               /*7 SW=ro HW=ro 0x1 */
         uint32_t ADDITIONALFEAT : 1;               /*8 SW=ro HW=ro 0x1 */
         uint32_t FIFOACCESS : 1;               /*9 SW=ro HW=ro 0x0 */
         uint32_t FIFOSTAT : 1;               /*10 SW=ro HW=ro 0x1 */
         uint32_t SHADOW : 1;               /*11 SW=ro HW=ro 0x1 */
         uint32_t UARTADDENCODEDPARAMS : 1;               /*12 SW=ro HW=ro 0x1 */
         uint32_t DMAEXTRA : 1;               /*13 SW=ro HW=ro 0x1 */
         uint32_t RSVDCPR15to14 : 2;               /*14:15 SW=ro HW=ro 0x0 */
         uint32_t FIFOMODE : 8;               /*16:23 SW=ro HW=ro 0x8 */
         uint32_t RSVDCPR31to24 : 8;               /*24:31 SW=ro HW=ro 0x0 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_CPR;

/*  UCV DESCRIPTION :UCV register is valid only when the DW_apb_uart is configured to have additional features implemented (ADDITIONAL_FEATURES = YES). If additional features are not implemented, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t UARTComponentVersion : 32;               /*0:31 SW=ro HW=ro 0x3430342A */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_UCV;

/*  CTR DESCRIPTION :CTR is register is valid only when the DW_apb_uart is configured to have additional features implemented (ADDITIONAL_FEATURES = YES). If additional features are not implemented, this register does not exist and reading from this register address returns 0. */
typedef union {
    struct {
         uint32_t PeripheralID : 32;               /*0:31 SW=ro HW=ro 0x44570110 */
    } bf;
     uint32_t  dw;
    
    
}DWapbuart_CTR;

/* uar registers structure */

typedef __IOM struct inph_uart_base{
    union {
        DWapbuart_RBR  RBR;
        DWapbuart_DLL  DLL;
        DWapbuart_THR  THR;
    } RBRTHRDLL;
    
    union {
        DWapbuart_IER  IER;
        DWapbuart_DLH  DLH;
    } IERDLH;
    
    union {
        DWapbuart_IIR  IIR;
        DWapbuart_FCR  FCR;
    } IIRFCR;
    
    DWapbuart_LCR  LCR;
    DWapbuart_MCR  MCR;
    DWapbuart_LSR  LSR;
    DWapbuart_MSR  MSR;
    DWapbuart_SCR  SCR;
    DWapbuart_LPDLL  LSBDL;
    DWapbuart_LPDLH  MSBDL;
    
    uint8_t filler10[0x8];
    
    union {
        DWapbuart_SRBR0  SRBR0;
        DWapbuart_STHR0  STHR0;
    } alternate_DWapbuart_SRBR0;
    
    union {
        DWapbuart_SRBR1  SRBR1;
        DWapbuart_STHR1  STHR1;
    } alternate_DWapbuart_SRBR1;
    
    union {
        DWapbuart_SRBR2  SRBR2;
        DWapbuart_STHR2  STHR2;
    } alternate_DWapbuart_SRBR2;
    
    union {
        DWapbuart_SRBR3  SRBR3;
        DWapbuart_STHR3  STHR3;
    } alternate_DWapbuart_SRBR3;
    
    union {
        DWapbuart_SRBR4  SRBR4;
        DWapbuart_STHR4  STHR4;
    } alternate_DWapbuart_SRBR4;
    
    union {
        DWapbuart_SRBR5  SRBR5;
        DWapbuart_STHR5  STHR5;
    } alternate_DWapbuart_SRBR5;
    
    union {
        DWapbuart_SRBR6  SRBR6;
        DWapbuart_STHR6  STHR6;
    } alternate_DWapbuart_SRBR6;
    
    union {
        DWapbuart_SRBR7  SRBR7;
        DWapbuart_STHR7  STHR7;
    } alternate_DWapbuart_SRBR7;
    
    union {
        DWapbuart_SRBR8  SRBR8;
        DWapbuart_STHR8  STHR8;
    } alternate_DWapbuart_SRBR8;
    
    union {
        DWapbuart_SRBR9  SRBR9;
        DWapbuart_STHR9  STHR9;
    } alternate_DWapbuart_SRBR9;
    
    union {
        DWapbuart_SRBR10  SRBR10;
        DWapbuart_STHR10  STHR10;
    } alternate_DWapbuart_SRBR10;
    
    union {
        DWapbuart_SRBR11  SRBR11;
        DWapbuart_STHR11  STHR11;
    } alternate_DWapbuart_SRBR11;
    
    union {
        DWapbuart_SRBR12  SRBR12;
        DWapbuart_STHR12  STHR12;
    } alternate_DWapbuart_SRBR12;
    
    union {
        DWapbuart_SRBR13  SRBR13;
        DWapbuart_STHR13  STHR13;
    } alternate_DWapbuart_SRBR13;
    
    union {
        DWapbuart_SRBR14  SRBR14;
        DWapbuart_STHR14  STHR14;
    } alternate_DWapbuart_SRBR14;
    
    union {
        DWapbuart_SRBR15  SRBR15;
        DWapbuart_STHR15  STHR15;
    } alternate_DWapbuart_SRBR15;
    
    DWapbuart_FAR  FAR;
    
    uint8_t filler27[0x8];
    
    DWapbuart_USR  USR;
    DWapbuart_TFL  TxFFL;
    DWapbuart_RFL  RxFFL;
    DWapbuart_SRR  SRR;
    DWapbuart_SRTS  SRTS;
    DWapbuart_SBCR  SBCR;
    DWapbuart_SDMAM  SDMAM;
    DWapbuart_SFE  SFE;
    DWapbuart_SRT  SRT;
    DWapbuart_STET  STET;
    DWapbuart_HTX  HTX;
    DWapbuart_DMASA  DMASA;
    DWapbuart_TCR  TCR;
    DWapbuart_DEEN  DEEN;
    DWapbuart_REEN  REEN;
    DWapbuart_DET  DET;
    DWapbuart_TAT  TAT;
    DWapbuart_DLF  DLF;
    
    uint8_t filler45[0x8];
    
    DWapbuart_LCREXT  LCREXT;
    DWapbuart_UARTPROTLEVEL  UARTPROTLEVEL;
    DWapbuart_REGTIMEOUTRST  REGTIMEOUTRST;
    
    uint8_t filler48[0x1C];
    
    DWapbuart_CPR  CPR;
    DWapbuart_UCV  UCV;
    DWapbuart_CTR  CTR;
    
    uint8_t filler0[0x300];
    
    
} inph_uart_t;


#endif /* __INPH_UART_REGISTERS_H */


