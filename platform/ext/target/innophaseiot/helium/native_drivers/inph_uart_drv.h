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
 * @file    inph_uart_drv.h
 * @author  InnophaseIOT Firmware Team
 * @brief   UART top driver header file
 */

#ifndef __INPH_UART_DRV_H
#define __INPH_UART_DRV_H

#include <stdint.h>
#include "inph_uart_registers.h"
#include "Driver_USART.h"
#include "helium_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum inph_en_uart_data_width {
    INPH_UART_5_BITS = 0U,
    INPH_UART_6_BITS,
    INPH_UART_7_BITS,
    INPH_UART_8_BITS,
} inph_en_uart_data_width_t;

typedef enum inph_en_uart_stop_bits {
    INPH_UART_STOP_BITS_1 = 0U,   /* 1 Stop Bit    */
    INPH_UART_STOP_BITS_1_5 = 1U, /* 1.5 Stop Bits */
    INPH_UART_STOP_BITS_2 = 2U,   /* 2 Stop Bits   */
} inph_en_uart_stop_bits_t;

typedef enum inph_en_uart_parity {
    INPH_UART_PARITY_NONE = 0U, /* no parity check   */
    INPH_UART_PARITY_EVEN,
    INPH_UART_PARITY_ODD, /* odd parity check */
} inph_en_uart_parity_t;

/* UART Polarity */
typedef enum inph_en_uart_polarity {
    INPH_UART_ACTIVE_LOW = 0U,  /* signal active low */
    INPH_UART_ACTIVE_HIGH = 1U, /* signal active high */
} inph_en_uart_polarity_t;

typedef inph_uart_t USART_Type;

typedef struct usart_config {
/* Width of UART data (valid range is 5 to 8) */
inph_en_uart_data_width_t dataWidth;
bool_t enableMsbFirst; // not supported
/* stop bits */
inph_en_uart_stop_bits_t stopBits;
/* Configures the UART parity */
inph_en_uart_parity_t parity;

/* enables the usage of the CTS input signal for the transmitter. The
 * transmitter waits for CTS to be active before sending data
 */
bool_t enableCts;

/* Sets the CTS Polarity */
inph_en_uart_polarity_t ctsPolarity;

/* When the RX FIFO has fewer entries than rtsRxFifoLevel, the
 * RTS signal is active (note to disable RTS, set this field to zero)
 */
uint32_t rtsRxFifoLevel;

/* Specifies the number of bits to detect a break condition */
uint32_t breakWidth;
bool_t breaklevel;

/* When there are more entries in the RX FIFO than this level
 * the RX trigger output goes high. This output can be connected
 * to a DMA channel through a trigger transfer.
 */
uint32_t rxFifoTriggerLevel;

/* The bits set in this mask allow the event to cause an interrupt */
uint32_t rxFifoIntEnableMask;

/*
 * When there are fewer entries in the TX FIFO then this level
 * the TX trigger output goes high. This output can be connected
 * to a DMA channel through a trigger mux.
 */
uint32_t txFifoTriggerLevel;

/* Bits set in this mask allows the event to cause an interrupt */
uint32_t txFifoIntEnableMask;

uint32_t baudRate;
uint32_t clockRate;

} usart_config_t;

typedef struct {
    USART_Type      *base;          /* USART base */
    usart_config_t  config;         /* USART configuration structure */
    uint32_t        tx_nbr_bytes;   /* Number of bytes transfered */
    uint32_t        rx_nbr_bytes;   /* Number of bytes recevied */
    bool            is_initialized; /* true if initialized */
    ARM_USART_SignalEvent_t cb_event;
} UARTx_Resources;

/* UART device configuration structure */
struct inph_uart_dev_cfg_t {
    const uint32_t base;              /*!< UART base address */
    const uint32_t default_baudrate;  /*!< Default baudrate */
};

/* UART device data structure */
struct inph_uart_dev_data_t {
    uint32_t state;       /*!< Indicates if the uart driver
                               is initialized and enabled */
    uint32_t system_clk;  /*!< System clock */
    uint32_t baudrate;    /*!< Baudrate */
};

/*  UART device structure */
struct inph_uart_dev_t {
    const struct arm_uart_dev_cfg_t* const cfg;  /*!< UART configuration */
    struct arm_uart_dev_data_t* const data;      /*!< UART data */
};

/*  UART enumeration types */
enum inph_uart_error_t {
    INPH_UART_ERR_NONE = 0,      /*!< No error */
    INPH_UART_ERR_INVALID_ARG,   /*!< Error invalid input argument */
    INPH_UART_ERR_INVALID_BAUD,  /*!< Invalid baudrate */
    INPH_UART_ERR_NOT_INIT,      /*!< Error UART not initialized */
    INPH_UART_ERR_NOT_READY,     /*!< Error UART not ready */
};

enum inph_uart_irq_t {
    INPH_UART_IRQ_RX,       /*!< RX interrupt source */
    INPH_UART_IRQ_TX,       /*!< TX interrupt source */
    INPH_UART_IRQ_COMBINED  /*!< RX-TX combined interrupt source */
};

enum inph_en_uart_rx_trigger {
    INPH_UART_1_BYTE = 0U, /* 1 byte in RX */
    INPH_UART_4_BYTES,     /* 1/4 full     */
    INPH_UART_8_BYTES,     /* 1/2 full     */
    INPH_UART_14_BYTES,    /* 7/8 full     */
};

#define INPH_UART_FIFO_SIZE               (16UL)
#define INPH_UART_FCR_XMIT_F_RST          (0x4)
#define INPH_UART_FCR_RCVR_F_RST          (0x02)
#define INPH_UART_LCR_PARITY_EN           (0x8)
#define INPH_UART_IIR_INT_ID_SHIFT        (0x01)
#define INPH_UART_IIR_INT_ID_MASK         (0x07)
//#define INPH_UART_LCR_DLAB                (0x80)
#define INPH_UART_FCR_RCVR_TRIG_LSB_SHIFT (0x06)
#define INPH_UART_INITIALIZED             (0x01)


void inph_uart_uninit(USART_Type *base);
enum inph_uart_error_t inph_uart_init(UARTx_Resources *dev);
enum inph_uart_error_t inph_uart_set_baudrate(UARTx_Resources *dev);
uint32_t inph_uart_get_baudrate(UARTx_Resources* dev);
enum inph_uart_error_t inph_uart_set_clock(UARTx_Resources* dev,
                                         uint32_t system_clk);
enum inph_uart_error_t inph_uart_read(USART_Type *dev, uint8_t* byte);
enum inph_uart_error_t inph_uart_write(USART_Type *base, uint8_t byte);
uint32_t inph_uart_tx_ready(UARTx_Resources *dev);
uint32_t inph_uart_rx_ready(UARTx_Resources *dev);


/*******************************************************************************
 * Function Name: Inph_UART_ReadRxFifo
 ****************************************************************************//**
*
* @brief Read a byte from receive buffer
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    byte          returns the single byte read from receive buffer
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_ReadRxFifo(USART_Type *base)
{
    return (INPH_UART_RBR(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetLatchBit
 ****************************************************************************//**
*
* @brief return the latch bit
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    latch value   Returns the value of the latch bit
*
*******************************************************************************/
__STATIC_INLINE uint8_t Inph_UART_GetLatchBit(USART_Type *base)
{
    return (INPH_UART_LCR_DLAB(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_Get
 ****************************************************************************//**
*
* @brief Read a byte from receiver buffer
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    numRead       how many bytes read 0 or 1
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_Get(USART_Type *base)
{
    return Inph_UART_ReadRxFifo(base);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetNumInTxFifo
 ****************************************************************************//**
*
* @brief Get numbe of bytes in the TX buffer
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    numBytes      number of bytes available in the buffer
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetNumInTxFifo(USART_Type *base)
{
    return (INPH_UART_TXLVL(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetNumInRxFifo
 ****************************************************************************//**
*
* @brief Get number of bytes in the receiver byte
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    numBytes      number of bytes in the receiver buffer not read
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetNumInRxFifo(USART_Type *base)
{
    return (INPH_UART_RXLVL(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_WriteTxFifo
 ****************************************************************************//**
*
* @brief Write a byte to TX buffer
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_WriteTxFifo(USART_Type *base, uint32_t data)
{
    INPH_UART_THR(base) = data;
}

/*******************************************************************************
 * Function Name: Inph_UART_ClearTxFifo
 ****************************************************************************//**
*
* @brief resets the TX buffer and clears it
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_ClearTxFifo(USART_Type *base)
{
    INPH_UART_FCR(base) |= INPH_UART_FCR_XMIT_F_RST;
}

/*******************************************************************************
 * Function Name: Inph_UART_ClearRxFifo
 ****************************************************************************//**
*
* @brief reset the RX buffer and clear it
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_ClearRxFifo(USART_Type *base)
{
    INPH_UART_FCR(base) |= INPH_UART_FCR_RCVR_F_RST;
}

/*******************************************************************************
 * Function Name: Inph_UART_DataReady
 ****************************************************************************//**
*
* @brief if there is data available to be read
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    valid         0 or 1 for return value
*
*******************************************************************************/
__STATIC_INLINE uint8_t Inph_UART_DataReady(USART_Type *base)
{
    return (INPH_UART_LSR_DR(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_IsTxComplete
 ****************************************************************************//**
*
* @brief if TX has completed and TX buffer is empty
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return   True or False 
*
*******************************************************************************/
__STATIC_INLINE bool_t Inph_UART_IsTxComplete(USART_Type *base)
{
    return (INPH_UART_LSR_TEMT(base) == 1 ? TRUE : FALSE);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetDataWidth
 ****************************************************************************//**
*
* @brief return data width value - number of bits per char
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    width         Data field width value
*
*******************************************************************************/
__STATIC_INLINE uint32_t inph_uart_GetDataWidth(USART_Type *base)
{
    return (INPH_UART_LCR_DLS(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableDataWidth
 ****************************************************************************//**
*
* @brief Sets the data width value
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableDataWidth(USART_Type *base,
                                               uint32_t dataWidth)
{
    INPH_UART_LCR_DLS(base) = dataWidth;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetParity
 ****************************************************************************//**
*
* @brief Check if parity is set
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    parity field value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetParity(USART_Type *base)
{
    return (INPH_UART_LCR_PEN(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableParity
 ****************************************************************************//**
*
* @brief Set parity field with parity value
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_DisnableParity(USART_Type *base)
{
    INPH_UART_LCR_PEN(base) = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableParity
 ****************************************************************************//**
*
* @brief Set parity field with parity value
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableParity(USART_Type *base)
{
    INPH_UART_LCR_PEN(base) = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_SetParity
 ****************************************************************************//**
*
* @brief Set parity field with parity value
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_SetParity(USART_Type *base,
                                         inph_en_uart_parity_t parity)
{
    INPH_UART_LCR_EPS(base) = parity;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetStopBits
 ****************************************************************************//**
*
* @brief return number of stop bits set in LCR register
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return                  number of stop bits
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetStopBits(USART_Type *base)
{
    return (INPH_UART_LCR_STOP(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableStopBits
 ****************************************************************************//**
*
* @brief set number of stop bits in LCR register
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableStopBits(USART_Type *base,
                                              inph_en_uart_stop_bits_t stopBits)
{
    INPH_UART_LCR_STOP(base) = stopBits;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableXmitInt
 ****************************************************************************//**
*
* @brief Enable transmit interrupts - when TX buffer is empty, interrupt is generated
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableXmitInt(USART_Type *base)
{
    INPH_UART_IER_ETBEI(base) = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableLsrInt
 ****************************************************************************//**
*
* @brief Generate interrupt if there is change in LSR register
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableLsrInt(USART_Type *base)
{
    INPH_UART_IER_ELSI(base) = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetOverRunErr
 ****************************************************************************//**
*
* @brief Find out if and over run error has happened
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    over-run      return over-run field value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetOverRunErr(USART_Type *base)
{
    return (INPH_UART_LSR_OE(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetParityErr
 ****************************************************************************//**
*
* @brief Find out if a parity error has happened
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    parity        parity error field value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetParityErr(USART_Type *base)
{
    return (INPH_UART_LSR_PE(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetFramingErr
 ****************************************************************************//**
*
* @brief Find out if framing error has happened
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    framing       returns framing error field value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetFramingErr(USART_Type *base)
{
    return (INPH_UART_LSR_FE(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetBreakInt
 ****************************************************************************//**
*
* @brief check if break interrupt has happend
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    break         break interrupt field value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetBreakInt(USART_Type *base)
{
    return (INPH_UART_LSR_BI(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableRcvrInt
 ****************************************************************************//**
*
* @brief Enable receive interrupt to read data 
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableRcvrInt(USART_Type *base)
{
    INPH_UART_IER_ERBFI(base) = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_DisableRcvrInt
 ****************************************************************************//**
*
* @brief Disables receive interrupt to read data 
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_DisableRcvrInt(USART_Type *base)
{
    INPH_UART_IER_ERBFI(base) = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetRcvrInt
 ****************************************************************************//**
*
* @brief Check if receiver interrupt has happend
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    receive int   returns receive interrupt field value 
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetRcvrInt(USART_Type *base)
{
    return (INPH_UART_IER_ERBFI(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetXmitInt
 ****************************************************************************//**
*
* @brief Check if tramsmit interrupt occured
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    transmit int  returns transmit interrupt field value
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetXmitInt(USART_Type *base)
{
    return (INPH_UART_IER_ETBEI(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetLsrInt
 ****************************************************************************//**
*
* @brief if there is LSR interrupt
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    LSR int       Field value of LSR interrupt
*
*******************************************************************************/
__STATIC_INLINE uint32_t Inph_UART_GetLsrInt(USART_Type *base)
{
    return (INPH_UART_IER_ELSI(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_DisableAllInt
 ****************************************************************************//**
*
* @brief Disable all interrupts for UART
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_DisableAllInt(USART_Type *base)
{
    INPH_UART_IER(base) = 0x0;
}

/*******************************************************************************
 * Function Name: Inph_UART_ClearBrk
 ****************************************************************************//**
*
* @brief Clear line break enable
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_ClearBrk(USART_Type *base)
{
    INPH_UART_LCR_BC(base) = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableBrk
 ****************************************************************************//**
*
* @brief enables sending line break
*
* @param[in] base       The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableBrk(USART_Type *base)
{
    INPH_UART_LCR_BC(base) = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableFifo
 ****************************************************************************//**
*
* @brief enables uart FIFO
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_EnableFifo(USART_Type *base)
{
    INPH_UART_FCR_FIFOE(base) = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_DisableLsrInt
 ****************************************************************************//**
*
* @brief disable LSR interrupts from being asserted
*
* @param[in] base          The pointer to the UART base instance.
* 
* @return    none
*
*******************************************************************************/
__STATIC_INLINE void Inph_UART_DisableLsrInt(USART_Type *base)
{
    INPH_UART_IER_ELSI(base) = 0;
}

#ifdef __cplusplus
}
#endif
#endif /* __INPH_UART_DRV_H */
