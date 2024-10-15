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
 * @file    Driver_USART.c
 * @author  InnophaseIOT Firmware Team
 * @brief   UART top driver
 */

#include "Driver_USART.h"
#include "platform_retarget.h"
#include "inph_uart_drv.h"
#include "RTE_Device.h"

#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  (void)arg
#endif

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_DRIVER_VERSION_MAJOR_MINOR(1,1),
    ARM_DRIVER_VERSION_MAJOR_MINOR(1,1)
};

/* Driver Capabilities */
static const ARM_USART_CAPABILITIES DriverCapabilities = {
    1, /* supports UART (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports UART Single-wire mode */
    0, /* supports UART IrDA mode */
    0, /* supports UART Smart Card mode */
    0, /* Smart Card Clock generator available */
    0, /* RTS Flow Control available */
    0, /* CTS Flow Control available */
    0, /* Transmit completed event: \ref ARM_USARTx_EVENT_TX_COMPLETE */
    0, /* Signal receive character timeout event: \ref ARM_USARTx_EVENT_RX_TIMEOUT */
    0, /* RTS Line: 0=not available, 1=available */
    0, /* CTS Line: 0=not available, 1=available */
    0, /* DTR Line: 0=not available, 1=available */
    0, /* DSR Line: 0=not available, 1=available */
    0, /* DCD Line: 0=not available, 1=available */
    0, /* RI Line: 0=not available, 1=available */
    0, /* Signal CTS change event: \ref ARM_USARTx_EVENT_CTS */
    0, /* Signal DSR change event: \ref ARM_USARTx_EVENT_DSR */
    0, /* Signal DCD change event: \ref ARM_USARTx_EVENT_DCD */
    0, /* Signal RI change event: \ref ARM_USARTx_EVENT_RI */
    0  /* Reserved */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* USART0 Driver wrapper functions */
static UARTx_Resources USART0_DEV = { //((UART_Type *)(uart))
    .base = (struct inph_uart_base *)UART0_BASE_S,
    .tx_nbr_bytes = 0,
    .rx_nbr_bytes = 0,
    .is_initialized = 0
};

static ARM_DRIVER_VERSION GetVersion(void)
{
    return DriverVersion;
}

static ARM_USART_CAPABILITIES GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t Initialize(ARM_USART_SignalEvent_t cb_event)
{
    enum inph_uart_error_t ret;
    
    /* Initializes generic UART driver */
    USART0_DEV.config.stopBits = INPH_UART_STOP_BITS_1;
    USART0_DEV.config.parity = INPH_UART_PARITY_NONE;
    USART0_DEV.config.dataWidth = INPH_UART_8_BITS;
    USART0_DEV.config.rxFifoTriggerLevel = INPH_UART_1_BYTE;
    USART0_DEV.cb_event = cb_event;
    
    ret = inph_uart_init(&USART0_DEV);
    if (ret == INPH_UART_ERR_NONE)
        return INPH_DRIVER_OK;
    else
        return INPH_DRIVER_ERROR;
}

static int32_t Uninitialize(void)
{
    inph_uart_uninit(USART0_DEV.base);
    return INPH_DRIVER_OK;
}

static int32_t INPH_USARTx_PowerControl(UARTx_Resources* USART0_DEV,
                                       ARM_POWER_STATE state)
{
    ARG_UNUSED(USART0_DEV);

    switch (state) {
    case INPH_POWER_OFF:
    case INPH_POWER_LOW:
        return INPH_DRIVER_ERROR_UNSUPPORTED;
    case INPH_POWER_FULL:
        /* Nothing to be done */
        return INPH_DRIVER_OK;
    /* default:  The default is not defined intentionally to force the
     *           compiler to check that all the enumeration values are
     *           covered in the switch.*/
    }
    return INPH_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t INPH_USARTx_Send(UARTx_Resources* USART0_DEV, const void *data,
                               uint32_t num)
{
    const uint8_t* p_data = (const uint8_t*)data;

    if ((data == NULL) || (num == 0U)) {
        /* Invalid parameters */
        return INPH_DRIVER_ERROR_PARAMETER;
    }

    /* Resets previous TX counter */
    USART0_DEV->tx_nbr_bytes = 0;

    while(USART0_DEV->tx_nbr_bytes != num) {
        /* Waits until UART is ready to transmit */
        while(inph_uart_tx_ready(USART0_DEV)) {};

        /* As UART is ready to transmit at this point, the write function can
         * not return any transmit error */
        inph_uart_write(USART0_DEV->base, *p_data);

        USART0_DEV->tx_nbr_bytes++;
        p_data++;
    }

    /* Waits until character is transmited */
    while (inph_uart_tx_ready(USART0_DEV)){};

    return INPH_DRIVER_OK;
}

static int32_t INPH_USARTx_Receive(UARTx_Resources* USART0_DEV,
                                  void *data, uint32_t num)
{
    uint8_t* p_data = (uint8_t*)data;

    if ((data == NULL) || (num == 0U)) {
        // Invalid parameters
        return INPH_DRIVER_ERROR_PARAMETER;
    }

    /* Resets previous RX counter */
    USART0_DEV->rx_nbr_bytes = 0;

    while(USART0_DEV->rx_nbr_bytes != num) {
        /* Waits until one character is received */
        while (!inph_uart_rx_ready(USART0_DEV)){};

        /* As UART has received one byte, the read can not
         * return any receive error at this point */
        inph_uart_read(USART0_DEV->base, p_data);

        USART0_DEV->rx_nbr_bytes++;
        p_data++;
    }

    return INPH_DRIVER_OK;
}

static uint32_t GetTxCount(void)
{
    return USART0_DEV.tx_nbr_bytes;
}

static uint32_t GetRxCount(void)
{
    return USART0_DEV.rx_nbr_bytes;
}

static int32_t PowerControl(ARM_POWER_STATE state)
{
    return INPH_USARTx_PowerControl(&USART0_DEV, state);
}

static int32_t Send(const void *data, uint32_t num)
{
    return INPH_USARTx_Send(&USART0_DEV, data, num);
}

static int32_t Receive(void *data, uint32_t num)
{
    return INPH_USARTx_Receive(&USART0_DEV, data, num);
}

static int32_t Transfer(const void *data_out, void *data_in,
                                   uint32_t num)
{
    ARG_UNUSED(data_out);
    ARG_UNUSED(data_in);
    ARG_UNUSED(num);

    return INPH_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t Control(uint32_t control, uint32_t arg)
{
    return INPH_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_STATUS GetStatus(void)
{
    ARM_USART_STATUS status = {0, 0, 0, 0, 0, 0, 0, 0};
    return status;
}

static int32_t SetModemControl(ARM_USART_MODEM_CONTROL control)
{
    ARG_UNUSED(control);
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_MODEM_STATUS GetModemStatus(void)
{
    ARM_USART_MODEM_STATUS modem_status = {0, 0, 0, 0, 0};
    return modem_status;
}

extern ARM_DRIVER_USART Driver_USART0;
ARM_DRIVER_USART Driver_USART0 = {
    .GetVersion = GetVersion,
    .GetCapabilities = GetCapabilities,
    .Initialize = Initialize,
    .Uninitialize = Uninitialize,
    .PowerControl = PowerControl,
    .Send = Send,
    .Receive = Receive,
    .Transfer = Transfer,
    .GetTxCount = GetTxCount,
    .GetRxCount = GetRxCount,
    .Control = Control,
    .GetStatus = GetStatus,
    .SetModemControl = SetModemControl,
    .GetModemStatus = GetModemStatus
};

