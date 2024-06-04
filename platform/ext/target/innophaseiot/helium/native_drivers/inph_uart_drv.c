/*
 * Copyright (c) 2016-2022 ARM Limited
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

#include "inph_uart_drv.h"


/* CTRL Register */
#define ARM_UART_TX_EN       (1ul << 0)
#define ARM_UART_RX_EN       (1ul << 1)
#define ARM_UART_TX_INTR_EN  (1ul << 2)
#define ARM_UART_RX_INTR_EN  (1ul << 3)

/* STATE Register */
#define ARM_UART_TX_BF  (1ul << 0)
#define ARM_UART_RX_BF  (1ul << 1)

/* INTSTATUS Register */
#define ARM_UART_TX_INTR  (1ul << 0)
#define ARM_UART_RX_INTR  (1ul << 1)

/* UART state definitions */
#define ARM_UART_INITIALIZED  (1ul << 0)

#define INPH_UART_LCR_DLAB (0x80)

void arm_uart_uninit(USART_Type *base)
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

enum arm_uart_error_t arm_uart_init(UARTx_Resources *dev)
{

    if ((dev->base == NULL) || (dev->config == NULL)) {
        return (ARM_UART_ERR_INVALID_ARG);
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
    
    dev->is_initialized = ARM_UART_INITIALIZED;

    return (ARM_UART_ERR_NONE);
}

enum arm_uart_error_t arm_uart_set_baudrate(UARTx_Resources *dev)
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
    
    return ARM_UART_ERR_NONE;
}

uint32_t arm_uart_get_baudrate(UARTx_Resources* dev)
{
    return dev->config.baudRate;
}

enum arm_uart_error_t arm_uart_set_clock(UARTx_Resources* dev,
                                         uint32_t system_clk)
{
    if(system_clk == 0) {
        return ARM_UART_ERR_INVALID_ARG;
    }

    if(!(dev->is_initialized & ARM_UART_INITIALIZED)) {
        return ARM_UART_ERR_NOT_INIT;
    }

    /* Sets system clock */
    dev->config.clockRate = system_clk;

    /* Enables receiver and transmitter */
    return ARM_UART_ERR_NONE;
}

enum arm_uart_error_t arm_uart_read(UARTx_Resources *dev, uint8_t* byte)
{
    /* Reads data */

    *byte = (uint8_t)Inph_UART_ReadRxFifo(dev->base);

    return ARM_UART_ERR_NONE;
}

enum arm_uart_error_t arm_uart_write(UARTx_Resources *dev, uint8_t byte)
{
    /* Sends data */
    Inph_UART_WriteTxFifo(dev->base, data);

    return ARM_UART_ERR_NONE;
}

uint32_t arm_uart_tx_ready(UARTx_Resources *dev)
{

    if(!(dev->is_initialized & ARM_UART_INITIALIZED)) {
        return 0;
    }

    return Inph_UART_GetNumInTxFifo(dev->base);
}

uint32_t arm_uart_rx_ready(UARTx_Resources *dev)
{

    if(!(dev->is_initialized & ARM_UART_INITIALIZED)) {
        return 0;
    }

    return (Inph_UART_GetNumInRxFifo(dev->base));
}

