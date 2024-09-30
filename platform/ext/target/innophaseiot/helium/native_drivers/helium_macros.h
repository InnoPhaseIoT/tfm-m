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
 * @file    helium_macros.h
 * @author  Innophase Firmware Team
 * @brief   Helium helper macros header
 */

#ifndef __INPH_HELIUM_MACROS_H
#define __INPH_HELIUM_MACROS_H

/*******************************************************************************
*  Register Access Helper Macros
*******************************************************************************/



/*******************************************************************************
*               UART
********************************************************************************/

/**
 * \addtogroup group_uart_macros_uart
 * \{
 */

#define INPH_UART_BASE(uart)          ((USART_Type *)(uart))

#define INPH_UART_RBR(base)           (((USART_Type *)(base))->RBRTHRDLL.RBR.dw)
#define INPH_UART_THR(base)           (((USART_Type *)(base))->RBRTHRDLL.THR.dw)
#define INPH_UART_DLL(base)           (((USART_Type *)(base))->RBRTHRDLL.DLL.dw)

#define INPH_UART_IER(base)           (((USART_Type *)(base))->IERDLH.IER.dw)
#define INPH_UART_DLH(base)           (((USART_Type *)(base))->IERDLH.DLH.dw)

#define INPH_UART_FCR(base)           (((USART_Type *)(base))->IIRFCR.FCR.dw)
#define INPH_UART_IIR(base)           (((USART_Type *)(base))->IIRFCR.IIR.dw)

#define INPH_UART_LCR(base)           (((USART_Type *)(base))->LCR.dw)
#define INPH_UART_MCR(base)           (((USART_Type *)(base))->MCR.dw)
#define INPH_UART_LSR(base)           (((USART_Type *)(base))->LSR.dw)

#define INPH_UART_TXLVL(base)         (((USART_Type *)(base))->TxFFL.dw)
#define INPH_UART_RXLVL(base)         (((USART_Type *)(base))->RxFFL.dw)
#define INPH_UART_DLF(base)           (((USART_Type *)(base))->DLF.dw)

#define INPH_UART_LCR_DLAB(base)      (((USART_Type *)(base))->LCR.bf.DLAB)
#define INPH_UART_LCR_STOP(base)      (((USART_Type *)(base))->LCR.bf.STOP)
#define INPH_UART_LCR_EPS(base)       (((USART_Type *)(base))->LCR.bf.EPS)
#define INPH_UART_LCR_PEN(base)       (((USART_Type *)(base))->LCR.bf.PEN)
#define INPH_UART_LCR_DLS(base)       (((USART_Type *)(base))->LCR.bf.DLS)
#define INPH_UART_LCR_BC(base)        (((USART_Type *)(base))->LCR.bf.BC)
#define INPH_UART_LSR_DR(base)        (((USART_Type *)(base))->LSR.bf.DR)
#define INPH_UART_LSR_TEMT(base)      (((USART_Type *)(base))->LSR.bf.TEMT)
#define INPH_UART_LSR_BI(base)        (((USART_Type *)(base))->LSR.bf.BI)
#define INPH_UART_LSR_FE(base)        (((USART_Type *)(base))->LSR.bf.FE)
#define INPH_UART_LSR_PE(base)        (((USART_Type *)(base))->LSR.bf.PE)
#define INPH_UART_LSR_OE(base)        (((USART_Type *)(base))->LSR.bf.OE)
#define INPH_UART_USR_BUSY(base)      (((USART_Type *)(base))->USR.bf.BUSY)
#define INPH_UART_IER_ELSI(base)      (((USART_Type *)(base))->IERDLH.IER.bf.ELSI)
#define INPH_UART_IER_ETBEI(base)     (((USART_Type *)(base))->IERDLH.IER.bf.ETBEI)
#define INPH_UART_IER_ERBFI(base)     (((USART_Type *)(base))->IERDLH.IER.bf.ERBFI)
#define INPH_UART_FCR_XFIFOR(base)    (((USART_Type *)(base))->IIRFCR.FCR.bf.XFIFOR)
#define INPH_UART_FCR_RFIFOR(base)    (((USART_Type *)(base))->IIRFCR.FCR.bf.RFIFOR)
#define INPH_UART_FCR_FIFOE(base)     (((USART_Type *)(base))->IIRFCR.FCR.bf.FIFOE)
#define INPH_UART_FCR_RT(base)        (((USART_Type *)(base))->IIRFCR.FCR.bf.RT)
#define INPH_UART_MCR_LPBACK(base)    (((USART_Type *)(base))->MCR.bf.LoopBack)

/*******************************************************************************
*               DMAC
********************************************************************************/


#endif /* __INPH_HELIUM_MACROS_H */
