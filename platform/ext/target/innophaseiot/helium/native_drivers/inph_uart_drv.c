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
 * @file    inph_uart_drv.c
 * @author  InnophaseIOT Firmware Team
 * @brief   UART top driver
 */

#include "inph_uart_drv.h"

#define INPH_UART_LCR_DLAB (0x80)

void inph_uart_uninit(USART_Type *base)
{
    base->RBRTHR.dw = 0UL;
    base->IER.dw = 0UL;
    base->IIRFCR.dw = 0UL;
    base->LCR.dw = 0UL;
    base->MCR.dw = 0UL;
    base->CLKDIVP0 = 1UL;
    base->CLKDIVP1 = 0UL;
    base->CLKDIVQ0 = 1UL;
    base->CLKDIVQ1 = 0UL;
    base->AXISTcontrol.dw = 0UL;
}

enum inph_uart_error_t inph_uart_init(UARTx_Resources *dev)
{

    if ((dev->base == NULL) || (dev->config == NULL)) {
        return (INPH_UART_ERR_INVALID_ARG);
    }    

    /* de-initialize UART to default reset values */
    Inph_UART_Deinit(dev->base);

    /* Enable FIFO */
    Inph_UART_EnableFifo(dev->base);

    /* set the stop bits and data length */
    Inph_UART_EnableStopBits(dev->base, dev->config->stopBits);
    Inph_UART_EnableDataWidth(dev->base, dev->config->dataWidth);

    /* set the parity */
    if (dev->config->parity != 0) {
        Inph_UART_EnableParity(dev->base);
        Inph_UART_SetParity(dev->base, dev->config->parity);
    }
    else {
        Inph_UART_DisnableParity(dev->base);
    }

    /* set the trigger level */
    switch (dev->config->rxFifoTriggerLevel) {
    default:
    case INPH_UART_1_BYTE:
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGLSB = 0;
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGMSB = 0;
        break;
    case INPH_UART_4_BYTES:
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGLSB = 1;
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGMSB = 0;
        break;
    case INPH_UART_8_BYTES:
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGLSB = 0;
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGMSB = 1;
        break;
    case INPH_UART_14_BYTES:
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGLSB = 1;
        dev->base->IIRFCR.bf.FIFOENRCVRTRIGMSB = 1;
        break;
    }
    
    dev->is_initialized = INPH_UART_INITIALIZED;

    return (INPH_UART_ERR_NONE);
}

enum inph_uart_error_t inph_uart_set_baudrate(UARTx_Resources *dev)
{
    uint8_t temp;

    /* set the DLAB bit */
    temp = dev->base->LCR.dw;
    dev->base->LCR.dw = INPH_UART_LCR_DLAB | temp;

    dev->base->CLKDIVP0.dw = dev->config.clockP0;
    dev->base->CLKDIVQ0.dw = dev->config.clockQ0;

    /* set the latch values now */
    dev->base->RBRTHR.dw = dev->config.deviceLatch & 0xFF;
    dev->base->IER.dw = (dev->config.deviceLatch >> 0x08) & 0xFF;
    dev->base->LCR.dw = temp;
    
    return INPH_UART_ERR_NONE;
}

uint32_t inph_uart_get_baudrate(UARTx_Resources* dev)
{
    return dev->config.baudRate;
}

enum inph_uart_error_t inph_uart_set_clock(UARTx_Resources* dev,
                                         uint32_t system_clk)
{
    if(system_clk == 0) {
        return INPH_UART_ERR_INVALID_ARG;
    }

    if(!(dev->is_initialized & INPH_UART_INITIALIZED)) {
        return INPH_UART_ERR_NOT_INIT;
    }

    /* Sets system clock */
    dev->config.clockRate = system_clk;

    /* Enables receiver and transmitter */
    return INPH_UART_ERR_NONE;
}

enum inph_uart_error_t inph_uart_read(USART_Type *base, uint8_t* byte)
{
    /* Reads data */

    *byte = (uint8_t)Inph_UART_ReadRxFifo(base);

    return INPH_UART_ERR_NONE;
}

enum inph_uart_error_t inph_uart_write(USART_Type *base, uint8_t byte)
{
    /* Sends data */
    Inph_UART_WriteTxFifo(base, data);

    return INPH_UART_ERR_NONE;
}

uint32_t inph_uart_tx_ready(UARTx_Resources *dev)
{

    if(!(dev->is_initialized & INPH_UART_INITIALIZED)) {
        return 0;
    }

    return Inph_UART_GetNumInTxFifo(dev->base);
}

uint32_t inph_uart_rx_ready(UARTx_Resources *dev)
{

    if(!(dev->is_initialized & INPH_UART_INITIALIZED)) {
        return 0;
    }

    return (Inph_UART_GetNumInRxFifo(dev->base));
}

