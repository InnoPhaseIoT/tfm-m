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
#include "helium_macros.h"

void inph_uart_uninit(struct inph_uart_dev_t *dev)
{
    /* reset the FIFOs */
    INPH_UART_FCR_XFIFOR((USART_Type *)dev->cfg->base) = 1UL;
    INPH_UART_FCR_RFIFOR((USART_Type *)dev->cfg->base) = 1UL;

    INPH_UART_FCR((USART_Type *)dev->cfg->base) = 0UL;
    INPH_UART_IER((USART_Type *)dev->cfg->base) = 0UL;
    INPH_UART_LCR((USART_Type *)dev->cfg->base) = 0UL;
    INPH_UART_MCR((USART_Type *)dev->cfg->base) = 0UL;
}

enum inph_uart_error_t inph_uart_init(struct inph_uart_dev_t *dev,
                                      uint32_t system_clk)
{
    if (dev->cfg->base == 0) {
        return (INPH_UART_ERR_INVALID_ARG);
    }    

    /* de-initialize UART to default reset values */
    inph_uart_uninit(dev);
    
    /* Enable FIFO */
    Inph_UART_EnableFifo((USART_Type *)dev->cfg->base);
    
    /*set the system clock and baud rate */
    dev->data->system_clk = system_clk;
    dev->data->baudrate = dev->cfg->default_baudrate;

    dev->data->state = INPH_UART_INITIALIZED;

    return (INPH_UART_ERR_NONE);
}

enum inph_uart_error_t inph_uart_set_baudrate(struct inph_uart_dev_t *dev)
{
    uint8_t temp;
    uint32_t dli, tf;
    float dlf;
    
    if (dev->data->state != INPH_UART_INITIALIZED)
    {
        return INPH_UART_ERR_NOT_INIT;
    }

    dli = (uint32_t)(dev->data->system_clk / (16 * dev->data->baudrate));
    dlf = ((float)(dev->data->system_clk)) / (float)((16 * dev->data->baudrate) - dli);
    /* adjust to upper integer value */
    tf = (uint32_t)((INPH_UART_DLF_SIZE_ADJUSTED * dlf) + 0.5);

    /* set the DLAB bit */
    temp = INPH_UART_LCR(dev->cfg->base);
    INPH_UART_LCR(dev->cfg->base) = INPH_UART_LCR_DLAB_MASK | temp;

    /* set the latch values now */
    INPH_UART_DLL(dev->cfg->base) = (dli & 0xFF);
    INPH_UART_DLH(dev->cfg->base) = (dli >> 0x08) & 0xFF;
    /* device latch fractional size is 6 */
    INPH_UART_DLF(dev->cfg->base) = (tf & 0x3F);
    INPH_UART_LCR(dev->cfg->base) = temp;

    return INPH_UART_ERR_NONE;
}

uint32_t inph_uart_get_baudrate(struct inph_uart_dev_t  *dev)
{
    return dev->data->baudrate;
}

enum inph_uart_error_t inph_uart_set_clock(struct inph_uart_dev_t *dev,
                                         uint32_t system_clk)
{
    if(system_clk == 0) {
        return INPH_UART_ERR_INVALID_ARG;
    }

    if(!(dev->data->state & INPH_UART_INITIALIZED)) {
        return INPH_UART_ERR_NOT_INIT;
    }

    /* Sets system clock */
    dev->data->system_clk = system_clk;

    /* Enables receiver and transmitter */
    return INPH_UART_ERR_NONE;
}

enum inph_uart_error_t inph_uart_read(struct inph_uart_dev_t *dev, uint8_t* byte)
{
    /* Reads data */

    *byte = (uint8_t)Inph_UART_ReadRxFifo((USART_Type *)dev->cfg->base);

    return INPH_UART_ERR_NONE;
}

enum inph_uart_error_t inph_uart_write(struct inph_uart_dev_t *dev, uint8_t byte)
{
    /* Sends data */
    Inph_UART_WriteTxFifo((USART_Type *)dev->cfg->base, byte);

    return INPH_UART_ERR_NONE;
}

uint32_t inph_uart_tx_ready(struct inph_uart_dev_t *dev)
{

    if(!(dev->data->state & INPH_UART_INITIALIZED)) {
        return 0;
    }

    return Inph_UART_GetNumInTxFifo((USART_Type *)dev->cfg->base);
}

uint32_t inph_uart_rx_ready(struct inph_uart_dev_t *dev)
{

    if(!(dev->data->state & INPH_UART_INITIALIZED)) {
        return 0;
    }

    return (Inph_UART_GetNumInRxFifo((USART_Type *)dev->cfg->base));
}

