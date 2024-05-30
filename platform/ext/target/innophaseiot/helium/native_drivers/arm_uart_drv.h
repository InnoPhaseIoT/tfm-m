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

/**
 * \file arm_uart_drv.h
 * \brief Generic driver for ARM UART.
 */

#ifndef __ARM_UART_DRV_H__
#define __ARM_UART_DRV_H__

#include <stdint.h>
#include "inph_uart_registers.h"

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

typedef inph_uart_t USART_Type;

typedef struct usart_config {
    /* Width of UART data (valid range is 5 to 8) */
    inph_en_uart_data_width_t dataWidth;
    bool enableMsbFirst; // not supported
    /* stop bits */
    inph_en_uart_stop_bits_t stopBits;
    /* Configures the UART parity */
    inph_en_uart_parity_t parity;

    /* enables the usage of the CTS input signal for the transmitter. The
     * transmitter waits for CTS to be active before sending data
     */
    bool enableCts;

    /* When the RX FIFO has fewer entries than rtsRxFifoLevel, the
     * RTS signal is active (note to disable RTS, set this field to zero)
     */
    uint32_t rtsRxFifoLevel;

    /* Specifies the number of bits to detect a break condition */
    uint32_t breakWidth;
    bool breaklevel;

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
    uint8_t clockP0;
    uint8_t clockP1;
    uint8_t clockQ0;
    uint8_t clickQ1;
    uint32_t deviceLatch;    
} usart_config_t;

typedef struct inph_uart_baudrate_config {
    uint32_t baudRate;
    uint32_t clockRate;
    uint8_t clockP0;
    uint8_t clockP1;
    uint8_t clockQ0;
    uint8_t clickQ1;
    uint32_t deviceLatch;

};

typedef struct {
    USART_Type      *base;          /* USART base */
    usart_config_t  config;         /* USART configuration structure */
    uint32_t        tx_nbr_bytes;   /* Number of bytes transfered */
    uint32_t        rx_nbr_bytes;   /* Number of bytes recevied */
    bool            is_initialized; /* true if initialized */
} UARTx_Resources;

/* ARM UART device configuration structure */
struct arm_uart_dev_cfg_t {
    const uint32_t base;              /*!< UART base address */
    const uint32_t default_baudrate;  /*!< Default baudrate */
};

/* ARM UART device data structure */
struct arm_uart_dev_data_t {
    uint32_t state;       /*!< Indicates if the uart driver
                               is initialized and enabled */
    uint32_t system_clk;  /*!< System clock */
    uint32_t baudrate;    /*!< Baudrate */
};

/* ARM UART device structure */
struct arm_uart_dev_t {
    const struct arm_uart_dev_cfg_t* const cfg;  /*!< UART configuration */
    struct arm_uart_dev_data_t* const data;      /*!< UART data */
};

/* ARM UART enumeration types */
enum arm_uart_error_t {
    ARM_UART_ERR_NONE = 0,      /*!< No error */
    ARM_UART_ERR_INVALID_ARG,   /*!< Error invalid input argument */
    ARM_UART_ERR_INVALID_BAUD,  /*!< Invalid baudrate */
    ARM_UART_ERR_NOT_INIT,      /*!< Error UART not initialized */
    ARM_UART_ERR_NOT_READY,     /*!< Error UART not ready */
};

enum arm_uart_irq_t {
    ARM_UART_IRQ_RX,       /*!< RX interrupt source */
    ARM_UART_IRQ_TX,       /*!< TX interrupt source */
    ARM_UART_IRQ_COMBINED  /*!< RX-TX combined interrupt source */
};

enum inph_en_uart_rx_trigger {
    INPH_UART_1_BYTE = 0U, /* 1 byte in RX */
    INPH_UART_4_BYTES,     /* 1/4 full     */
    INPH_UART_8_BYTES,     /* 1/2 full     */
    INPH_UART_14_BYTES,    /* 7/8 full     */
};

/*******************************************************************************
 * Function Name: Inph_UART_ReadRxFifo
 ****************************************************************************//**
*
*  Read a byte from receive buffer
*
* param[in] base          The pointer to the UART base instance.
* 
* return    byte          returns the single byte read from receive buffer
*
*******************************************************************************/
static inline uint32_t Inph_UART_ReadRxFifo(USART_Type *base)
{
    return (INPH_UART_RBR(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetLatchBit
 ****************************************************************************//**
*
*  return the latch bit
*
* param[in] base          The pointer to the UART base instance.
* 
* return    latch value   Returns the value of the latch bit
*
*******************************************************************************/
static inline uint8_t Inph_UART_GetLatchBit(USART_Type *base)
{
    return (base->LCR.bf.DLAB);
}

/*******************************************************************************
 * Function Name: Inph_UART_Put
 ****************************************************************************//**
*
* Writes a byte onto transmit buffer
*
* param[in] base          The pointer to the UART base instance.
* 
* return    numByte       Number of bytes written 0 or 1
*
*******************************************************************************/
static inline uint32_t Inph_UART_Put(USART_Type *base, uint32_t data)
{
    INPH_ASSERT_FALSE(Inph_UART_GetLatchBit(base));
    return Inph_UART_Write(base, data);
}

/*******************************************************************************
 * Function Name: Inph_UART_PutString
 ****************************************************************************//**
*
*  write a string of bytes onto uart tx buffer
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_PutString(USART_Type *base, char const string[])
{
    INPH_ASSERT(INPH_UART_IS_BUFFER_VALID(string, 1UL));
    INPH_ASSERT_FALSE(Inph_UART_GetLatchBit(base));
    /* write the string now */
    Inph_UART_WriteString(base, string);
}

/*******************************************************************************
 * Function Name: Inph_UART_Get
 ****************************************************************************//**
*
*  Read a byte from receiver buffer
*
* param[in] base          The pointer to the UART base instance.
* 
* return    numRead       how many bytes read 0 or 1
*
*******************************************************************************/
static inline uint32_t Inph_UART_Get(USART_Type *base)
{
    INPH_ASSERT_FALSE(Inph_UART_GetLatchBit(base));

    return Inph_UART_ReadRxFifo(base);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetNumInTxFifo
 ****************************************************************************//**
*
*  Get numbe of bytes in the TX buffer
*
* param[in] base          The pointer to the UART base instance.
* 
* return    numBytes      number of bytes available in the buffer
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetNumInTxFifo(USART_Type *base)
{
    return (INPH_UART_TXLVL(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_GetNumInRxFifo
 ****************************************************************************//**
*
*  Get number of bytes in the receiver byte
*
* param[in] base          The pointer to the UART base instance.
* 
* return    numBytes      number of bytes in the receiver buffer not read
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetNumInRxFifo(USART_Type *base)
{
    return (INPH_UART_RXLVL(base));
}

/*******************************************************************************
 * Function Name: Inph_UART_WriteTxFifo
 ****************************************************************************//**
*
*  Write a byte to TX buffer
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_WriteTxFifo(USART_Type *base, uint32_t data)
{
    INPH_UART_RBR(base) = data;
}

/*******************************************************************************
 * Function Name: Inph_UART_ClearTxFifo
 ****************************************************************************//**
*
*  resets the TX buffer and clears it
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_ClearTxFifo(USART_Type *base)
{
    INPH_UART_FCR_IIR(base) |= INPH_UART_FCR_XMIT_F_RST;
}

/*******************************************************************************
 * Function Name: Inph_UART_ClearRxFifo
 ****************************************************************************//**
*
*  reset the RX buffer and clear it
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_ClearRxFifo(USART_Type *base)
{
    INPH_UART_FCR_IIR(base) |= INPH_UART_FCR_RCVR_F_RST;
}

/*******************************************************************************
 * Function Name: Inph_UART_DataReady
 ****************************************************************************//**
*
*  if there is data available to be read
*
* param[in] base          The pointer to the UART base instance.
* 
* return    valid         0 or 1 for return value
*
*******************************************************************************/
static inline uint8_t Inph_UART_DataReady(USART_Type *base)
{
    return (base->LSR.bf.DRDY);
}

/*******************************************************************************
 * Function Name: Inph_UART_IsTxComplete
 ****************************************************************************//**
*
*  if TX has completed and TX buffer is empty
*
* param[in] base          The pointer to the UART base instance.
* 
* return   True or False 
*
*******************************************************************************/
static inline bool_t Inph_UART_IsTxComplete(USART_Type *base)
{
    return (base->LSR.bf.XMITHRE == 1 ? TRUE : FALSE);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetDataWidth
 ****************************************************************************//**
*
*  return data width value - number of bits per char
*
* param[in] base          The pointer to the UART base instance.
* 
* return    width         Data field width value
*
*******************************************************************************/
static inline uint32_t inph_uart_GetDataWidth(USART_Type *base)
{
    return (base->LCR.bf.WLEN);
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableDataWidth
 ****************************************************************************//**
*
*  Sets the data width value
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableDataWidth(USART_Type *base,
                                               uint32_t dataWidth)
{
    base->LCR.bf.WLEN = dataWidth;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetParity
 ****************************************************************************//**
*
*  Check if parity is set
*
* param[in] base          The pointer to the UART base instance.
* 
* return    parity field value
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetParity(USART_Type *base)
{
    return (base->LCR.bf.PARITYEN);
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableParity
 ****************************************************************************//**
*
*  Set parity field with parity value
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_DisnableParity(USART_Type *base)
{
    base->LCR.bf.PARITYEN = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableParity
 ****************************************************************************//**
*
*  Set parity field with parity value
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableParity(USART_Type *base)
{
    base->LCR.bf.PARITYEN = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_SetParity
 ****************************************************************************//**
*
*  Set parity field with parity value
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_SetParity(USART_Type *base,
                                         inph_en_uart_parity_t parity)
{
    base->LCR.bf.EVEN = parity;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetStopBits
 ****************************************************************************//**
*
*  return number of stop bits set in LCR register
*
* param[in] base          The pointer to the UART base instance.
* 
* return                  number of stop bits
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetStopBits(USART_Type *base)
{
    return (base->LCR.bf.NUMSTOP);
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableStopBits
 ****************************************************************************//**
*
*  set number of stop bits in LCR register
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableStopBits(USART_Type *base,
                                              inph_en_uart_stop_bits_t stopBits)
{
    base->LCR.bf.NUMSTOP = stopBits;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableXmitInt
 ****************************************************************************//**
*
*  Enable transmit interrupts - when TX buffer is empty, interrupt is generated
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableXmitInt(USART_Type *base)
{
    base->IER.bf.ENXMITHEI = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableLsrInt
 ****************************************************************************//**
*
*  Generate interrupt if there is change in LSR register
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableLsrInt(USART_Type *base)
{
    base->IER.bf.ENRCVRLSI = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetOverRunErr
 ****************************************************************************//**
*
*  Find out if and over run error has happened
*
* param[in] base          The pointer to the UART base instance.
* 
* return    over-run      return over-run field value
*
*******************************************************************************/
static inline int32_t Inph_UART_GetOverRunErr(USART_Type *base)
{
    return (base->LSR.bf.OERR);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetParityErr
 ****************************************************************************//**
*
*  Find out if a parity error has happened
*
* param[in] base          The pointer to the UART base instance.
* 
* return    parity        parity error field value
*
*******************************************************************************/
static inline int32_t Inph_UART_GetParityErr(USART_Type *base)
{
    return (base->LSR.bf.PERR);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetFramingErr
 ****************************************************************************//**
*
*  Find out if framing error has happened
*
* param[in] base          The pointer to the UART base instance.
* 
* return    framing       returns framing error field value
*
*******************************************************************************/
static inline int32_t Inph_UART_GetFramingErr(USART_Type *base)
{
    return (base->LSR.bf.FERR);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetBreakInt
 ****************************************************************************//**
*
*  check if break interrupt has happend
*
* param[in] base          The pointer to the UART base instance.
* 
* return    break         break interrupt field value
*
*******************************************************************************/
static inline int32_t Inph_UART_GetBreakInt(USART_Type *base)
{
    return (base->LSR.bf.BINT);
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableRcvrInt
 ****************************************************************************//**
*
*  Enable receive interrupt to read data 
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableRcvrInt(USART_Type *base)
{
    base->IER.bf.ENRCVRDAI = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_DisableRcvrInt
 ****************************************************************************//**
*
*  Disables receive interrupt to read data 
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_DisableRcvrInt(USART_Type *base)
{
    base->IER.bf.ENRCVRDAI = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetRcvrInt
 ****************************************************************************//**
*
*  Check if receiver interrupt has happend
*
* param[in] base          The pointer to the UART base instance.
* 
* return    receive int   returns receive interrupt field value 
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetRcvrInt(USART_Type *base)
{
    return (base->IER.bf.ENRCVRDAI);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetXmitInt
 ****************************************************************************//**
*
*  Check if tramsmit interrupt occured
*
* param[in] base          The pointer to the UART base instance.
* 
* return    transmit int  returns transmit interrupt field value
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetXmitInt(USART_Type *base)
{
    return (base->IER.bf.ENXMITHEI);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetLsrInt
 ****************************************************************************//**
*
*  if there is LSR interrupt
*
* param[in] base          The pointer to the UART base instance.
* 
* return    LSR int       Field value of LSR interrupt
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetLsrInt(USART_Type *base)
{
    return (base->IER.bf.ENRCVRLSI);
}

/*******************************************************************************
 * Function Name: Inph_UART_GetIntId
 ****************************************************************************//**
*
*  Return the interrupt ID
*
* param[in] base          The pointer to the UART base instance.
* 
* return    ID            Interrupt ID
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetIntId(USART_Type *base)
{
    uint32_t field = INPH_UART_FCR_IIR(base);
    field >>= INPH_UART_IIR_INT_ID_SHIFT;
    field &= INPH_UART_IIR_INT_ID_MASK;
    return field;
}

/*******************************************************************************
 * Function Name: Inph_UART_DisableAllInt
 ****************************************************************************//**
*
*  Disable all interrupts for UART
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_DisableAllInt(USART_Type *base)
{
    INPH_UART_IER(base) = 0x0;
}

/*******************************************************************************
 * Function Name: Inph_UART_GetIntPending
 ****************************************************************************//**
*
*  If an interrupt is pending
*
* param[in] base          The pointer to the UART base instance.
* 
* return    int pending   0 for pending, 1 for not pending
*
*******************************************************************************/
static inline uint32_t Inph_UART_GetIntPending(USART_Type *base)
{
    return (base->IIRFCR.bf.INTPENDFIFOEN);
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableAxiCtrl
 ****************************************************************************//**
*
*  Enables TX or RX streaming with UART DMA
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableAxiCtrl(USART_Type *base, bool_t tx,
                                             bool_t rx)
{
    base->AXISTcontrol.bf.AXISIEN = rx;
    base->AXISTcontrol.bf.AXISOEN = tx;
}

/*******************************************************************************
 * Function Name: Inph_UART_ClearBrk
 ****************************************************************************//**
*
*  Clear line break enable
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_ClearBrk(USART_Type *base)
{
    base->LCR.bf.SETBR = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableBrk
 ****************************************************************************//**
*
*  enables sending line break
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableBrk(USART_Type *base)
{
    base->LCR.bf.SETBR = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_EnableFifo
 ****************************************************************************//**
*
*  enables uart FIFO
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_EnableFifo(USART_Type *base)
{
    base->IIRFCR.bf.INTPENDFIFOEN = 1;
}

/*******************************************************************************
 * Function Name: Inph_UART_DisableLsrInt
 ****************************************************************************//**
*
*  disable LSR interrupts from being asserted
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_DisableLsrInt(USART_Type *base)
{
    base->IER.bf.ENRCVRLSI = 0;
}

/*******************************************************************************
 * Function Name: Inph_UART_ResetPQclocks
 ****************************************************************************//**
*
*  resets P and Q clocks to their initial reset values
*
* param[in] base          The pointer to the UART base instance.
* 
* return    none
*
*******************************************************************************/
static inline void Inph_UART_ResetPQclocks(USART_Type *base)
{
    INPH_UART_CLKP0((USART_Type *)(base)) = 1;
    INPH_UART_CLKP1((USART_Type *)(base)) = 0;
    INPH_UART_CLKQ0((USART_Type *)(base)) = 1;
    INPH_UART_CLKQ1((USART_Type *)(base)) = 0;
}

/**
 * \brief Initializes UART. It uses the default baudrate to configure
 * the peripheral at this point.
 *
 * \param[in] dev         UART device struct \ref arm_uart_dev_t
 * \param[in] system_clk  System clock used by the device.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t Inph_UART_Init(USART_Type *base, usart_config_t config)

/**
 * \brief Sets the UART baudrate.
 *
 * \param[in] dev       UART device struct \ref arm_uart_dev_t
 * \param[in] baudrate  New baudrate.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_set_baudrate(struct arm_uart_dev_t* dev,
                                            uint32_t baudrate);

/**
 * \brief Gets the UART baudrate.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns the UART baudrate.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t arm_uart_get_baudrate(struct arm_uart_dev_t* dev);

/**
 * \brief Sets system clock.
 *
 * \param[in] dev         UART device struct \ref arm_uart_dev_t
 * \param[in] system_clk  System clock used by the device.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_set_clock(struct arm_uart_dev_t* dev,
                                         uint32_t system_clk);
/**
 * \brief Reads one byte from UART dev.
 *
 * \param[in] dev   UART device struct \ref arm_uart_dev_t
 * \param[in] byte  Pointer to byte.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note For better performance, this function doesn't check if dev and byte
 * pointer are NULL, and if the driver is initialized.
 */
enum arm_uart_error_t arm_uart_read(struct arm_uart_dev_t* dev, uint8_t* byte);

/**
 * \brief Writes a byte to UART dev.
 *
 * \param[in] dev   UART device struct \ref arm_uart_dev_t
 * \param[in] byte  Byte to write.
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note For better performance, this function doesn't check if dev is NULL and
 * if the driver is initialized to have better performance.
 */
enum arm_uart_error_t arm_uart_write(struct arm_uart_dev_t* dev, uint8_t byte);

/**
 * \brief Enables TX interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_irq_tx_enable(struct arm_uart_dev_t* dev);

/**
 * \brief Disables TX interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_irq_tx_disable(struct arm_uart_dev_t* dev);

/**
 * \brief  Verifies if Tx is ready to send more data.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return  1 if TX is ready, 0 otherwise.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t arm_uart_tx_ready(struct arm_uart_dev_t* dev);

/**
 * \brief Enables RX interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_irq_rx_enable(struct arm_uart_dev_t* dev);

/**
 * \brief Disables RX interrupt
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_irq_rx_disable(struct arm_uart_dev_t* dev);

/**
 * \brief Verifies if Rx has data.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return 1 if RX has data, 0 otherwise.
 *
 * \note This function doesn't check if dev is NULL.
 */
uint32_t arm_uart_rx_ready(struct arm_uart_dev_t* dev);

/**
 * \brief Clears UART interrupt.
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 * \param[in] irq  IRQ source to clean \ref arm_uart_irq_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_clear_interrupt(struct arm_uart_dev_t* dev,
                              enum arm_uart_irq_t irq);

/**
 * \brief Enables TX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_tx_enable(struct arm_uart_dev_t* dev);

/**
 * \brief Disables TX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_tx_disable(struct arm_uart_dev_t* dev);

/**
 * \brief Enables RX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \return Returns error code as specified in \ref arm_uart_error_t
 *
 * \note This function doesn't check if dev is NULL.
 */
enum arm_uart_error_t arm_uart_rx_enable(struct arm_uart_dev_t* dev);

/**
 * \brief Disables RX
 *
 * \param[in] dev  UART device struct \ref arm_uart_dev_t
 *
 * \note This function doesn't check if dev is NULL.
 */
void arm_uart_rx_disable(struct arm_uart_dev_t* dev);

#ifdef __cplusplus
}
#endif
#endif /* __ARM_UART_DRV_H__ */
