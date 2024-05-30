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

#include "tfm_hal_device_header.h"
#include "cmsis_driver_config.h"
#include "RTE_Device.h"

#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  (void)arg
#endif

/* driver version */
#define INPH_USART_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,2)
#define INPH_USART_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2,2)

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    INPH_USART_API_VERSION,
    INPH_USART_DRV_VERSION
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

typedef struct {
struct inph_uart_base  *base;       /* USART base */
    usart_config_t  config;         /* USART configuration structure */
    uint32_t        tx_nbr_bytes;   /* Number of bytes transfered */
    uint32_t        rx_nbr_bytes;   /* Number of bytes recevied */
    bool            is_initialized; /* true if initialized */
} UARTx_Resources;

/* USART0 Driver wrapper functions */
static UARTx_Resources USART0_DEV = { //((UART_Type *)(uart))
    .base = (struct inph_uart_base *)UART0_BASE,
    .tx_nbr_bytes = 0,
    .rx_nbr_bytes = 0,
    .is_initialized = 0
}

static ARM_DRIVER_VERSION ARM_USART_GetVersion(void)
{
    return DriverVersion;
}

static ARM_USART_CAPABILITIES ARM_USART_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t ARM_USART_Initialize(UARTx_Resources* USART0_DEV)
{
    /* Initializes generic UART driver */
    USART0_DEV->config.stopBits = INPH_UART_STOP_BITS_1;
    USART0_DEV->config.parity = INPH_UART_PARITY_NONE;
    USART0_DEV->config.dataWidth = INPH_UART_8_BITS;
    USART0_DEV->config.rxFifoTriggerLevel = INPH_UART_1_BYTE;
    
    arm_uart_init(&USART0_DEV);

    return ARM_DRIVER_OK;
}

static int32_t ARM_USART_Uninitialize(UARTx_Resources* USART0_DEV)
{
    return arm_uart_uninit(&USART0_DEV->base);
}

static int32_t ARM_USARTx_PowerControl(UARTx_Resources* USART0_DEV,
                                       ARM_POWER_STATE state)
{
    ARG_UNUSED(USART0_DEV);

    switch (state) {
    case ARM_POWER_OFF:
    case ARM_POWER_LOW:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    case ARM_POWER_FULL:
        /* Nothing to be done */
        return ARM_DRIVER_OK;
    /* default:  The default is not defined intentionally to force the
     *           compiler to check that all the enumeration values are
     *           covered in the switch.*/
    }
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_USARTx_Send(UARTx_Resources* USART0_DEV, const void *data,
                               uint32_t num)
{
    const uint8_t* p_data = (const uint8_t*)data;

    if ((data == NULL) || (num == 0U)) {
        /* Invalid parameters */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Resets previous TX counter */
    USART0_DEV->tx_nbr_bytes = 0;

    while(USART0_DEV->tx_nbr_bytes != num) {
        /* Waits until UART is ready to transmit */
        while(arm_uart_tx_ready(&USART0_DEV)) {};

        /* As UART is ready to transmit at this point, the write function can
         * not return any transmit error */
        (void)arm_uart_write(USART0_DEV->base, *p_data);

        USART0_DEV->tx_nbr_bytes++;
        p_data++;
    }

    /* Waits until character is transmited */
    while (arm_uart_tx_ready(&USART0_DEV)){};

    return ARM_DRIVER_OK;
}

static int32_t ARM_USARTx_Receive(UARTx_Resources* USART0_DEV,
                                  void *data, uint32_t num)
{
    uint8_t* p_data = (uint8_t*)data;

    if ((data == NULL) || (num == 0U)) {
        // Invalid parameters
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Resets previous RX counter */
    USART0_DEV->rx_nbr_bytes = 0;

    while(USART0_DEV->rx_nbr_bytes != num) {
        /* Waits until one character is received */
        while (!arm_uart_rx_ready(USART0_DEV->base)){};

        /* As UART has received one byte, the read can not
         * return any receive error at this point */
        (void)arm_uart_read(USART0_DEV->base, p_data);

        USART0_DEV->rx_nbr_bytes++;
        p_data++;
    }

    return ARM_DRIVER_OK;
}

static uint32_t ARM_USART_GetTxCount(UARTx_Resources* USART0_DEV)
{
    return USART0_DEV->tx_nbr_bytes;
}

static uint32_t ARM_USART_GetRxCount(UARTx_Resources* USART0_DEV)
{
    return USART0_DEV->rx_nbr_bytes;
}

static int32_t ARM_USARTx_Control(UARTx_Resources* USART0_DEV, uint32_t control,
                                  uint32_t arg)
{
    switch (control & ARM_USART_CONTROL_Msk) {
#ifdef UART_TX_RX_CONTROL_ENABLED
        case ARM_USART_CONTROL_TX:
            if (arg == 0) {
                arm_uart_tx_disable(uart_dev->dev);
            } else if (arg == 1) {
                if (arm_uart_tx_enable(uart_dev->dev) != ARM_UART_ERR_NONE) {
                    return ARM_DRIVER_ERROR;
                }
            } else {
                return ARM_DRIVER_ERROR_PARAMETER;
            }
            break;
        case ARM_USART_CONTROL_RX:
            if (arg == 0) {
                arm_uart_rx_disable(uart_dev->dev);
            } else if (arg == 1) {
                if (arm_uart_rx_enable(uart_dev->dev) != ARM_UART_ERR_NONE) {
                    return ARM_DRIVER_ERROR;
                }
            } else {
                return ARM_DRIVER_ERROR_PARAMETER;
            }
            break;
#endif
        case ARM_USART_MODE_ASYNCHRONOUS:
            if(arm_uart_set_baudrate(USART0_DEV->base, arg) != ARM_UART_ERR_NONE) {
                return ARM_USART_ERROR_BAUDRATE;
            }
            break;
        /* Unsupported command */
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* UART Data bits */
    if(control & ARM_USART_DATA_BITS_Msk) {
        /* Data bit is not configurable */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* UART Parity */
    if(control & ARM_USART_PARITY_Msk) {
        /* Parity is not configurable */
        return ARM_USART_ERROR_PARITY;
    }

    /* USART Stop bits */
    if(control & ARM_USART_STOP_BITS_Msk) {
        /* Stop bit is not configurable */
        return ARM_USART_ERROR_STOP_BITS;
    }

    return ARM_DRIVER_OK;
}

static int32_t ARM_USART_PowerControl(ARM_POWER_STATE state)
{
    return ARM_USARTx_PowerControl(&USART0_DEV, state);
}

static int32_t ARM_USART_Send(const void *data, uint32_t num)
{
    return ARM_USARTx_Send(&USART0_DEV, data, num);
}

static int32_t ARM_USART_Receive(void *data, uint32_t num)
{
    return ARM_USARTx_Receive(&USART0_DEV, data, num);
}

static int32_t ARM_USART_Transfer(const void *data_out, void *data_in,
                                   uint32_t num)
{
    ARG_UNUSED(data_out);
    ARG_UNUSED(data_in);
    ARG_UNUSED(num);

    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_USART_Control(uint32_t control, uint32_t arg)
{
    return ARM_USARTx_Control(&USART0_DEV, control, arg);
}

static ARM_USART_STATUS ARM_USART_GetStatus(void)
{
    ARM_USART_STATUS status = {0, 0, 0, 0, 0, 0, 0, 0};
    return status;
}

static int32_t ARM_USART_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
    ARG_UNUSED(control);
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_MODEM_STATUS ARM_USART_GetModemStatus(void)
{
    ARM_USART_MODEM_STATUS modem_status = {0, 0, 0, 0, 0};
    return modem_status;
}

extern ARM_DRIVER_USART Driver_USART;
ARM_DRIVER_USART Driver_USART = {
    .GetVersion = ARM_USART_GetVersion,
    .GetCapabilities = ARM_USART_GetCapabilities,
    .Initialize = ARM_USART_Initialize,
    .Uninitialize = ARM_USART_Uninitialize,
    .PowerControl = ARM_USART_PowerControl,
    .Send = ARM_USART_Send,
    .Receive = ARM_USART_Receive,
    .Transfer = ARM_USART_Transfer,
    .GetTxCount = ARM_USART_GetTxCount,
    .GetRxCount = ARM_USART_GetRxCount,
    .Control = ARM_USART_Control,
    .GetStatus = ARM_USART_GetStatus,
    .SetModemControl = ARM_USART_SetModemControl,
    .GetModemStatus = ARM_USART_GetModemStatus
};

