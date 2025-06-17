/****************************************************************************
 * Copyright [2025] [InnoPhase IoT Inc.]
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
 ****************************************************************************/
/**
 * @file    inph_xspi.c
 * @author  Innophase Firmware Team
 * @brief   Provides low level APIs for xSPI driver
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "inph_xspi.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/**
 * Initialize the XSPI memory controller for communication. The user must
 * ensure that the XSPI interrupt is disabled while this function is called.
 * Enabling the interrupts can lead to triggering in the middle of the
 * initialization operation, which can lead to erroneous initialization.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *config         Pointer to the configuration structure.
 * @param[in] timeout         Timeout in microseconds for blocking APIs in use.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER.
 */
inph_en_xspi_status_t Inph_XSPI_Init(XSPI_Type *base,
                                     inph_stc_xspi_config_t const *config,
                                     uint32_t timeout,
                                     inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((NULL != base) && (NULL != config) && (NULL != context)) {

        context->timeout = timeout;
        context->memReadyPollDelay = 0U;
        context->preXIPDataRate = INPH_XSPI_DATA_RATE_SDR;

        /* Disable all interrupts. In XIP mode the write FIFO fill level and
         * read FIFO fill level interrupts are unconditionally disabled,
         * irrespective of the bit being enabled in IRQCTRL register.
         * */
        base->IRQCTRL.dw = xspimc_IRQCTRL_DEFAULT;

        /* clock phase - clock output starts low and ends low */
        base->SPICLKCFG.bf.Clockpolarity = 0;

        /* change output on negative edge */
        base->SPICLKCFG.bf.Transmitdataon = 0;

        /* Time between CS going active and first clock edge, and
         * the time from last clock edge to CS going inactive, time is
         * given in # of input clock cycles (Min. CS low + 1)*/
        base->SPICLKCFG.bf.MinCSLow = 0x0;

        /* SPI controller waits for the (min CS high + 1) clock cycles
         * before driving the CS active again. (duration between transactions)
         * */
        base->MINCSHIGH.bf.MinCSHigh = config->deselectDelay;

        /* At the end of transaction or beginning of dummy phase or
         * data phase for reads, the SPI memory controller will tristate its
         * outputs at the tie programmed in the Hold time register.
         * hold time = (half of clock period setting for divide by 4) - 1
         * if clock period is 16, so hold time = (16/2 -1) = 7,
         * if clock period is 2, set hold time to at least 1
         * */
        base->HOLDTIME.bf.Holdtime = 0x01;

        /* There are no GPIO output pin */
        base->GPIO.bf.GPIO = 0;
        base->GPIOOE.bf.GPIOOE = 0;

        /* Disable auto configuration */
        base->ACFGCTRL.bf.EnableAutoConfigurationaftersoftwarereset = 0;

        result = INPH_XSPI_SUCCESS;
    }

    return result;
}

/**
 * De-initialize the XSPI memory controller to default values.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    None.
 */
void Inph_XSPI_DeInit(XSPI_Type *base)
{
    /* Disable the AIP Window */
    base->AIPwindow0.s.AIPCTRL.bf.AIPModeEnable = 0;
    base->IRQCTRL.dw = xspimc_IRQCTRL_DEFAULT;
}

/**
 * Sets the mode which can be XIP mode or normal mode. When set to XIP mode,
 * the external memory device is mapped to microcontrollers memory space which
 * allows direct access enabling code execution. In normal/command mode the
 * xSPI controller acts as a simple SPI engine.
 *
 * @note In XIP mode, the write FIFO fill and read FIFO fill level interrupts
 * are unconditionally disabled
 *
 * @note The read-while-write access is not enabled, hence the XIP mode and
 * Command mode are mutually exclusive.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] mode            Holds the mode of operation to be set to.
 * @return                    None.
 */
void Inph_XSPI_SetMode(XSPI_Type *base, inph_en_xspi_mode_t mode)
{
    if (mode == INPH_XSPI_MODE_NORMAL) {
        base->AIPwindow0.s.AIPCTRL.bf.AIPModeEnable = 0;
    }
    else {
        base->AIPwindow0.s.AIPCTRL.bf.AIPModeEnable = 1;
    }
}

/**
 * Reads the mode of operation for xSPI MC, which can be XIP or normal mode.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    Current mode of operation which can be
 *                            @ref INPH_XSPI_MODE_NORMAL or
 *                            @ref INPH_XSPI_MODE_MEMORY.
 */
inph_en_xspi_mode_t Inph_XSPI_GetMode(XSPI_Type const *base)
{
    inph_en_xspi_mode_t mode = INPH_XSPI_MODE_NORMAL;

    if (base->AIPwindow0.s.AIPCTRL.bf.AIPModeEnable == 1) {
        mode = INPH_XSPI_MODE_MEMORY;
    }

    return mode;
}

/**
 * This function configures the data select option for a specific slave.
 * @note This function is not supported.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] chipSelect      The slave device to which setting is made.
 * @param[in] dataSelect      Selects the data select opion.
 * @return                    None.
 */
void Inph_XSPI_SetDataSelect(XSPI_Type *base,
                             inph_en_xspi_chip_select_t chipSelect,
                             inph_en_xspi_data_select_t dataSelect)
{
    UNUSED(base);
    UNUSED(chipSelect);
    UNUSED(dataSelect);

    /* Not supported, do nothing */
}

/**
 * This function packs bytes in the buff byte array into a 4-byte value and
 * transmits data. Once complete the application callback is triggered to
 * indicate the completion of transfer. This function can be called from
 * interrupt handler for non-blocking.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    None.
 */
void Inph_XSPI_PushTxFifo(XSPI_Type *base, inph_stc_xspi_context_t *context)
{
    uint32_t data = 0;
    uint32_t bytesToWrite = 0;
    uint32_t fifoFull = 0;
    uint32_t buffCounter = context->txBufferCount;
    uint8_t *buff = (uint8_t *)context->txBufferAddr;

    fifoFull = base->FIFOSTS.bf.FULL;
    while (fifoFull != 1) {
        /* smaller of the two: min bytes to write to FIFO or buffCounter */
        bytesToWrite =
            (INPH_XSPI_4_BYTES > buffCounter) ? buffCounter : INPH_XSPI_4_BYTES;

        /* Pack in the buff bytes to create 4 byte value */
        data = Inph_XSPI_PackBytes(&buff[0], bytesToWrite);

        /* Set the SPI Transmit Data register - Writing this register pushes one
         * 32-bit word into custom command data FIFO.
         */
        base->SPITXDATA.bf.Data = data;

        /* prepare buffer pointer and counter to reflect remaining bytes */
        buff = &buff[bytesToWrite];
        buffCounter -= bytesToWrite;
        if (buffCounter == 0) {
            break;
        }

        fifoFull = base->FIFOSTS.bf.FULL;
    }

    /* Save changes in the context */
    context->txBufferAddr = buff;
    context->txBufferCount = buffCounter;

    /* Check if all the data bytes are sent */
    if (buffCounter == 0) {
        /* If write interrupts are enabled, disable them */
        if (base->IRQCTRL.bf.WriteFIFOFillIRQEnable == 1) {
            /* Disable the Write FIFO Fill IRQ enable interrupt */
            base->IRQCTRL.bf.WriteFIFOFillIRQEnable = 0;

            /* Disable the Write FIFO Error IRQ enable interrupt */
            base->IRQCTRL.bf.WriteFIFOErrorIRQEnable = 0;

            /* When receive is complete, enable the SPI not busy IRQ,
             * to make sure the command execution is complete before
             * application starting another transaction.
             * */
            base->IRQCTRL.bf.NotBusyIRQEnable = 1;
        }

        /* Update the transfer status */
        context->transferStatus = (uint32_t)INPH_XSPI_TX_CMPLT;

        /* Notify the caller that the transfer is complete */
        if (context->txCmpltCb != NULL) {
            context->txCmpltCb(INPH_XSPI_TX_CMPLT);
        }
    }
}

/**
 * This function unpacks the read 4-byte value into byte array and copies to
 * receive buffer. Once complete the application callback is triggered to
 * indicate the receive is complete. This function can be called from interrupt
 * handler for non-blocking.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    None.
 */
void Inph_XSPI_PopRxFifo(XSPI_Type *base, inph_stc_xspi_context_t *context)
{
    uint32_t data = 0;
    uint32_t bytesToRead = 0;
    uint32_t fifoFillLevel = 0;
    uint32_t fifoEmpty = 0;
    uint32_t fifoStatus = 0;
    uint32_t buffCounter = context->rxBufferCount;
    uint8_t *buff = (uint8_t *)context->rxBufferAddr;

    /* Check if there is data in FIFO */
    fifoStatus = base->FIFOSTS.dw;
    fifoFillLevel = fifoStatus & 0xFFFF;
    fifoEmpty = (fifoStatus >> 16) & 1;
    while (fifoFillLevel != 0) {
        if (fifoEmpty == 1) {
            break;
        }

        /* Smaller of the two: min bytes to read from FIFO or buffCounter*/
        bytesToRead =
            (INPH_XSPI_4_BYTES > buffCounter) ? buffCounter : INPH_XSPI_4_BYTES;

        /* Read the SPI Receive Data register - Reading this register pops
         * one 32-bit word from SPI custom command data FIFO.
         */
        data = base->SPIRXDATA.bf.Data;

        /* Un-pack the data word into byte array */
        Inph_XSPI_UnPackBytes(data, &buff[0], bytesToRead);

        buffCounter -= bytesToRead;
        if (buffCounter == 0) {
            break;
        }

        /* prepare buffer pointer and counter for next read */
        buff = &buff[bytesToRead];

        /* Check if fifo has new data */
        fifoStatus = base->FIFOSTS.dw;
        fifoFillLevel = fifoStatus & 0xFFFF;
        fifoEmpty = (fifoStatus >> 16) & 1;
    }

    /* Save changes in the context */
    context->rxBufferAddr = buff;
    context->rxBufferCount = buffCounter; /* remaining bytes to read */

    /* Check if all the data bytes are received */
    if (buffCounter == 0)
    {
        /* If read interrupts is enabled, then disable them */
        if (base->IRQCTRL.bf.ReadFIFOFillIRQEnable == 1) {
            /* Disable the Read FIFO Fill interrupt */
            base->IRQCTRL.bf.ReadFIFOFillIRQEnable = 0;

            /* Disable the Read FIFO Error IRQ enable interrupt */
            base->IRQCTRL.bf.ReadFIFOErrorIRQEnable = 0;

            /* When receive is complete, enable the SPI not busy IRQ, to make
             * sure the command execution is complete before application
             * starting another transaction.
             * */
            base->IRQCTRL.bf.NotBusyIRQEnable = 1;
        }

        /* At this point all the data are read, update the receipt status */
        context->transferStatus = (uint32_t)INPH_XSPI_RX_CMPLT;

        /* Notify the caller that the receipt is complete */
        if (context->rxCmpltCb != NULL) {
            context->rxCmpltCb(INPH_XSPI_RX_CMPLT);
        }
    }
}

/**
 * Configures the command parameters followed by address byte and other
 * attribues. This function sets up chip select line for the rest of the
 * transaction. The @ref Inph_XSPI_TransmitCommand is called before @ref
 * Inph_XSPI_TransmitData or @ref Inph_XSPI_ReceiveData incase of
 * transmitting or receiving data respectively.
 *
 * Commands are 1-byte and address's are 24-bit.
 * Single, dual and quad modes are supported.
 *
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] cmd             Holds the command byte to be transmitted.
 * @param[in] isCommand2byte  Is command a 2-byte command.
 * @param[in] cmdTxfrWidth    Holds the width of the command byte
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] cmdParam        Array that holds the bytes to be transmitted after
 *                            command bytes, which will be address bytes.
 * @param[in] paramSize       Size of he parameter array.
 * @param[in] paramTxfrWidth  Holds the width of the transfer parameter
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] chipSelect      The slave device to which transfer is made
 * @param[in] cmpltTxfr       Specifies if the chip select line must be
 *                            de-asserted after transferring last byte. If this
 *                            value is set to 1, the command is transmitted
 *                            immediately.This value is set to 0, when this
 *                            function is succeeded by
 *                            @ref Inph_XSPI_TransmitData_Ext or
 *                            @ref Inph_XSPI_ReceiveData_Ext, which would
 *                            prepare the FIFO and then starts the transfer.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    Command transfer status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t Inph_XSPI_TransmitCommand(
    XSPI_Type *base, uint8_t cmd, inph_en_xspi_transfer_width_t cmdTxfrWidth,
    uint8_t const cmdParam[], uint32_t paramSize,
    inph_en_xspi_transfer_width_t paramTxfrWidth,
    inph_en_xspi_chip_select_t chipSelect, uint32_t cmpltTxfr,
    inph_stc_xspi_context_t const *context)
{
    return Inph_XSPI_TransmitCommand_Ext(
        base, (uint16_t)cmd, false, cmdTxfrWidth, INPH_XSPI_DATA_RATE_SDR,
        cmdParam, paramSize, paramTxfrWidth, INPH_XSPI_DATA_RATE_SDR,
        INPH_XSPI_ADDR_MASK_WORD, chipSelect, cmpltTxfr, context);
}

/**
 * This function is used to transmit data using the normal xspi interface.
 * This function uses the TX Data FIFO to implement the transmit functionality.
 * The function sets up an interrupt to trigger the TX Data FIFO and uses that
 * interrupt to fill the TX Data FIFO until all the data is transmitted. At the
 * end of the transmission, the TxCmpltCb is executed.  The chip select is
 * de-asserted at the end of transmit.
 *
 * @note The function triggers the transfer and the transfer itself utilizes
 * the interrupt for FIFO operations in the background. Thus, frequent
 * interrupts will be executed after this function is triggered.
 * Since this API is non-blocking and sets up the interrupt to act on the data
 * FIFO, ensure there will be no another instance of the function called
 * before the current instance has completed execution.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] txBuffer        Pointer to the data to be transferred.
 * @param[in] size            Size of txBuffer.
 * @param[in] transferWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] TxCmpltCb       Callback to be executed at the end of a transfer.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                            @ref INPH_XSPI_ERROR_FIFO_FULL.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand where the chip
 *                            select is asserted. The chip select is
 *                            de-asserted at the end of a transmit.
 */
inph_en_xspi_status_t
Inph_XSPI_TransmitData(XSPI_Type *base, uint8_t const *txBuffer, uint32_t size,
                       inph_en_xspi_transfer_width_t transferWidth,
                       inph_xspi_event_cb_t TxCmpltCb,
                       inph_stc_xspi_context_t *context)
{
    return Inph_XSPI_TransmitData_Ext(base, txBuffer, size, transferWidth,
                                      INPH_XSPI_DATA_RATE_SDR, TxCmpltCb,
                                      context);
}

/**
 * This function is used to transmit data using the normal xspi interface.
 * This function transmits data using the TX Data FIFO and txBufferCount to
 * keep track of the transfer count.
 *
 * @note This function does not use interrupt and blocks until completion, the
 * CPU will constantly monitor FIFO status and move data accordingly. The
 * function returns only on completion.
 * @note Ensure that the other transfers are finished before calling this
 * function and it should not be called during non-blocking transfers.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] txBuffer        Pointer to the data to be transferred.
 * @param[in] size            Size of txBuffer.
 * @param[in] transferWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                            @ref INPH_XSPI_ERROR_FIFO_FULL or
 *                            @ref INPH_XSPI_ERROR_TIMEOUT.
 * @pre                       This function is to be preceded by @ref
 *                            Inph_XSPI_TransmitCommand where the chip
 *                            select is asserted.
 */
inph_en_xspi_status_t
Inph_XSPI_TransmitDataBlocking(XSPI_Type *base, uint8_t const *txBuffer,
                               uint32_t size,
                               inph_en_xspi_transfer_width_t transferWidth,
                               inph_stc_xspi_context_t const *context)
{
    return Inph_XSPI_TransmitDataBlocking_Ext(
        base, txBuffer, size, transferWidth, INPH_XSPI_DATA_RATE_SDR, context);
}

/**
 * This function is used to receive data using the normal xspi interface. The
 * chip select is de-asserted at the end of the receive. The data is received
 * into the RX Data FIFO. The function sets up an interrupt to trigger on the
 * RX Data FIFO level and data is read from the RX Data FIFO to the rxBuffer as
 * it gets filled. This function does not block until completion. At the end of
 * the receive complete, the RxCmpltCb is executed.
 *
 * @note The function triggers the receive transaction and the receive operation
 * itself utilizes the interrupt for FIFO operations in the background. Thus,
 * frequent interrupts will be executed after this function is triggered.
 * So ensure there will be no another instance of the function called
 * before the current instance has completed execution.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] rxBuffer        Pointer to the buffer where the received data
 *                            will be stored.
 * @param[in] size            Size of data to be received.
 * @param[in] dataTxfrWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] RxCmpltCb       Callback to be executed at the end of reception.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand where the chip
 *                            select is asserted. The chip select is
 *                            de-asserted at the end of the receive.
 */
inph_en_xspi_status_t
Inph_XSPI_ReceiveData(XSPI_Type *base, uint8_t *rxBuffer, uint32_t size,
                      inph_en_xspi_transfer_width_t dataTxfrWidth,
                      inph_xspi_event_cb_t RxCmpltCb,
                      inph_stc_xspi_context_t *context)
{
    return Inph_XSPI_ReceiveData_Ext(base, rxBuffer, size, dataTxfrWidth,
                                     INPH_XSPI_DATA_RATE_SDR, RxCmpltCb,
                                     context);
}

/**
 * This function is used to receive data using the normal xspi interface.
 * The data is received into the RX Data FIFO.
 *
 * @note This function does not use interrupt and blocks until completion. the
 * caller will have to monitor FIFO status and move data accordingly.
 * The function returns only on completion. Ensure that the other transfers are
 * finished before calling this function and it should not be called during
 * non-blocking transfers.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] rxBuffer        Pointer to the buffer where the received data
 *                            will be stored.
 * @param[in] size            Size of data to be received.
 * @param[in] dataTxfrWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                            @ref INPH_XSPI_ERROR_TIMEOUT.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand where the chip
 *                            select is asserted. The chip select is
 *                            de-asserted at the end of the receive.
 */
inph_en_xspi_status_t
Inph_XSPI_ReceiveDataBlocking(XSPI_Type *base, uint8_t *rxBuffer, uint32_t size,
                              inph_en_xspi_transfer_width_t dataTxfrWidth,
                              inph_stc_xspi_context_t const *context)
{
    return Inph_XSPI_ReceiveDataBlocking_Ext(
        base, rxBuffer, size, dataTxfrWidth, INPH_XSPI_DATA_RATE_SDR, context);
}

/**
 * This function configures the dummy clock cycles.
 *
 * @note This function configures the dummy cycles, the settings are transmitted
 * in the receive or transmit data functions which succeed this call.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] cycles          Holds the number of dummy cycles to be sent.
 * @return                    PDL status @ref INPH_XSPI_SUCCESS.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand where the chip
 *                            select is asserted.
 */
inph_en_xspi_status_t Inph_XSPI_SendDummyCycles(XSPI_Type *base,
                                                uint32_t cycles)
{
    return Inph_XSPI_SendDummyCycles_Ext(base, INPH_XSPI_WIDTH_SINGLE,
                                         INPH_XSPI_DATA_RATE_SDR, cycles);
}

/**
 * This function gets the transfer status. This function is used to poll for
 * the status of the TransmitData or ReceiveData function
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    Current status of the transfer
 *                            @ref inph_en_xspi_transfer_state_t
 */
uint32_t Inph_XSPI_GetTransferStatus(XSPI_Type *base,
                                     inph_stc_xspi_context_t const *context)
{
    UNUSED(base);
    return (context->transferStatus);
}

/**
 * Sets the global context structure to default values.
 *
 * @note There is no xSPI IP specific enable/disable feature.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    None.
 */
void Inph_XSPI_Enable(XSPI_Type *base, inph_stc_xspi_context_t *context)
{
    UNUSED(base);

    /* Global variables initialization */
    context->txBufferAddr = NULL;
    context->txBufferSize = 0U;
    context->txBufferCount = 0U;
    context->rxBufferAddr = NULL;
    context->rxBufferSize = 0U;
    context->rxBufferCount = 0U;
    context->transferStatus = (uint32_t)INPH_XSPI_READY;
}

/**
 * Converted the Chip select enum to corresponding device index.
 *
 * @param[in] chipSelect      The slave device to which transfer is made.
 * @param[out] device_idx     A pointer to device index to be returned.
 * @return                    @ref INPH_XSPI_SUCCESS status if the device exist,
 *                            otherwise @ref INPH_XSPI_ERROR_INVALID_PARAMETER.
 */
inph_en_xspi_status_t
Inph_XSPI_ConvertSlaveSlotToIndex(inph_en_xspi_chip_select_t cs,
                                  uint32_t *device_idx)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    switch (cs) {
    case INPH_XSPI_CHIP_SELECT_0:
        *device_idx = 0U;
        result = INPH_XSPI_SUCCESS;
        break;
    default:
        result = INPH_XSPI_ERROR_INVALID_PARAMETER;
        break;
    }
    return result;
}

/**
 * The Interrupt Service Routine for the XSPI. The interrupt code will be
 * responsible for the FIFO operations on FIFO interrupts during ongoing
 * transfers. The user must place a call to this interrupt function in the
 * interrupt routine corresponding to the interrupt attached to the XSPI. If
 * the user does not do this, it will break the functionality of all the API
 * functions in the XSPI driver that use XSPI interrupts for transfers.
 *
 * @param[in] *base          Pointer to xSPI mem controller register structure.
 * @param[in] *config        Pointer to the configuration structure.
 * @return                   None.
 */
void Inph_XSPI_Interrupt(XSPI_Type *base, inph_stc_xspi_context_t *context)
{
    uint32_t status = 0;
    uint32_t irqEn = 0;
    uint32_t dmaStatus = 0;

    /* Read the Interrupt status and enable registers */
    status = base->SPISTS.dw;
    irqEn = base->IRQCTRL.dw;
    dmaStatus = base->DMASTS.dw;

    /* Check which interrupt has occurred */
    if (((irqEn &
          XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_MASK) != 0) &&
        ((status & XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_MASK) != 0)) {
        /* Read FIFO errors occurs when reading when write operation has been
         * requested or reading FIFO while its empty.
         * */
        context->transferStatus = (uint32_t)INPH_XSPI_RX_ERROR;

        /* Clear the interrupt */
        base->SPISTS.bf.ReadFIFOError = 1;
    }
    else if (((irqEn &
               XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_MASK) != 0) &&
             ((status & XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_MASK) != 0)) {
        /* Write FIFO errors occurs when writing the FIFO when read operation
         * is requested. The application should check if INPH_XSPI_READY before
         * starting any new read or write transaction.
         * */
        context->transferStatus = (uint32_t)INPH_XSPI_TX_ERROR;

        /* Clear the interrupt */
        base->SPISTS.bf.WriteFIFOError = 1;
    }
    else if (((irqEn &
               XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_MASK) != 0) &&
             ((status & XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_MASK) != 0)) {
        /* Read FIFO fill level is greater that the FIFO boundary level set in
         * IRQ control register's FIFO boundary bits [10:8], so start reading
         * from FIFO */
        /* NOTE: This value is left to default, so it gets activated when
         * Read FIFO is at least 1/8th full during or after read command
         * */
        Inph_XSPI_PopRxFifo(base, context);
    }
    else if (((irqEn &
               XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_MASK) != 0) &&
             ((status & XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_MASK) != 0)) {
        /* Write FIFO fill level is less than or equal to the FIFO boundary
         * level set in IRQ control register's FIFO boundary bits [10:8], so
         * start writing data to the FIFO */
        Inph_XSPI_PushTxFifo(base, context);
    }
    else if (((irqEn &
               XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_MASK) != 0) &&
             ((status & XSPI_MC_REGISTERS_SPISTS_BUSY_MASK) == 0)) {
        /* SPI is ready for new transaction */
        context->transferStatus = (uint32_t)INPH_XSPI_READY;

        /* Disable the SPI not busy IRQ */
        base->IRQCTRL.bf.NotBusyIRQEnable = 0;
    }
    else if (((irqEn &
               XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_MASK) != 0) &&
             ((dmaStatus & XSPI_MC_REGISTERS_DMASTS_DMAIDLE_MASK) != 0)) {

        context->transferStatus = (uint32_t)INPH_XSPI_READY;
        /* Disable the DMA idle interrupt */
        base->IRQCTRL.bf.DMAIdleIRQEnable = 0;
    }
    else if (((irqEn & XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_MASK) != 0) &&
             ((dmaStatus & XSPI_MC_REGISTERS_DMASTS_DMAIRQ_MASK) != 0)) {
        /* DMA successfully transferred one or more buffer descriptors. */
        if (context->transferStatus == INPH_XSPI_RX_BUSY) {
            context->transferStatus = INPH_XSPI_RX_CMPLT;
            /* Notify the caller that the receipt is complete */
            if (context->rxCmpltCb != NULL) {
                context->rxCmpltCb(context->transferStatus);
            }
        }
        else // TX_BUSY
        {
            context->transferStatus = INPH_XSPI_TX_CMPLT;
            /* Notify the caller that the transmit is complete */
            if (context->txCmpltCb != NULL) {
                context->txCmpltCb(context->transferStatus);
            }
        }

        /* Disable DMA IRQ Enable and DMA Error IRQ Enable */
        base->IRQCTRL.bf.DMAIRQEnable = 0;
        base->IRQCTRL.bf.DMAErrorIRQEnable = 0;

        /* DMA transaction completed, disable DMA mode */
        base->GLBLCTRL.bf.DMAEnable = 0;

        /* Clear the interrupt */
        base->DMASTS.bf.DMAIRQ = 1;

        base->IRQCTRL.bf.NotBusyIRQEnable = 1;
    }
    else if (((irqEn &
               XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_MASK) != 0) &&
             ((dmaStatus & XSPI_MC_REGISTERS_DMASTS_DMAERROR_MASK) != 0)) {
        /* Can happen when the size programmed in data size register is not the
         *  sum of sizes in the transaction list
         * */

        if (context->transferStatus == INPH_XSPI_TX_BUSY) {
            context->transferStatus = (uint32_t)INPH_XSPI_TX_ERROR;
        }
        else if (context->transferStatus == INPH_XSPI_RX_BUSY) {
            context->transferStatus = (uint32_t)INPH_XSPI_RX_ERROR;
        }

        /* Disable DMA IRQ Enable and DMA Error IRQ Enable */
        base->IRQCTRL.bf.DMAIRQEnable = 0;
        base->IRQCTRL.bf.DMAErrorIRQEnable = 0;

        /* DMA transaction resulted in error, disable DMA mode */
        base->GLBLCTRL.bf.DMAEnable = 0;
    }
    else {
        /* Do nothing */
    }
}

/**
 * Configures the command parameters followed by address byte and other
 * attribues. This function sets up chip select line for the rest of the
 * transaction. The @ref Inph_XSPI_TransmitCommand_Ext is called before @ref
 * Inph_XSPI_TransmitData_Ext or @ref Inph_XSPI_ReceiveData_Ext incase of
 * transmitting or receiving data respectively.
 *
 * Commands are 1-byte and address's are 24-bit.
 * Single, dual and quad modes are supported.
 *
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] cmd             Holds the command byte to be transmitted.
 * @param[in] isCommand2byte  Is command a 2-byte command.
 * @param[in] cmdTxfrWidth    Holds the width of the command byte
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] cmdDataRate     Holds data rate of the command phase
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] cmdParam        Array that holds the bytes to be transmitted after
 *                            command bytes, which will be address bytes.
 * @param[in] paramSize       Size of he parameter array.
 * @param[in] paramTxfrWidth  Holds the width of the transfer parameter
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] paramDataRate   Holds data rate of the transfer parameter
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] addrMask        Address Mask to be used.
 *                            @ref inph_en_xspi_address_mask_t
 * @param[in] chipSelect      The slave device to which transfer is made.
 * @param[in] cmpltTxfr       Specifies if the chip select line must be
 *                            de-asserted after transferring last byte. If this
 *                            value is set to 1, the command is transmitted
 *                            immediately.This value is set to 0, when this
 *                            function is succeeded by
 *                            @ref Inph_XSPI_TransmitData_Ext or
 *                            @ref Inph_XSPI_ReceiveData_Ext, which would
 *                            prepare the FIFO and then starts the transfer.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    Command transfer status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t Inph_XSPI_TransmitCommand_Ext(
    XSPI_Type *base, uint16_t cmd, bool isCommand2byte,
    inph_en_xspi_transfer_width_t cmdTxfrWidth,
    inph_en_xspi_data_rate_t cmdDataRate, uint8_t const cmdParam[],
    uint32_t paramSize, inph_en_xspi_transfer_width_t paramTxfrWidth,
    inph_en_xspi_data_rate_t paramDataRate,
    inph_en_xspi_address_mask_t addrMask, inph_en_xspi_chip_select_t chipSelect,
    uint32_t cmpltTxfr, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t timeout = 0;
    XSPI_DEVICE_Type volatile *device;
    uint32_t regData = 0;
    uint8_t duration = 0;
    uint8_t mode = 0;

    UNUSED(isCommand2byte);

    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(cmdTxfrWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(cmdDataRate));
    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(paramTxfrWidth));
    INPH_ASSERT(INPH_XSPI_CHIP_SEL_VALID(chipSelect));
    INPH_ASSERT(INPH_XSPI_CMD_PARAM_VALID(cmdParam, paramSize));
    INPH_ASSERT(INPH_XSPI_WIDTH_NA_VALID(paramTxfrWidth, paramSize));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(paramDataRate));

    timeout = context->timeout;

    Inph_XSPI_ConvertCmdTxfrWidth(cmdTxfrWidth, &duration, &mode);

    regData = 0;
    regData =
        (regData | (duration << XSPI_MC_REGISTERS_SPICMDATTR_DURATION_OFFSET) |
         (mode << XSPI_MC_REGISTERS_SPICMDATTR_MODE_OFFSET) |
         (cmdDataRate << XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_OFFSET)) &
        XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_INV_MASK &
        XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_INV_MASK &
        XSPI_MC_REGISTERS_SPICMDATTR_SKIP_INV_MASK &
        XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_INV_MASK;

    device = (XSPI_DEVICE_Type *)Inph_XSPI_GetDeviceBySlot(base, chipSelect);

    /* If AIP mode is enabled and suspend resume mode is enabled, then set
     * read while write bit to 1, and configure hold timing
     * */
    if ((device->AIPCTRL.bf.AIPModeEnable == 1) &&
        (device->AIPCTRL.bf.SusRes == 1)) {
        regData |= XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_MASK;

        /* The maximum duration of the operation (write or erase) must be
         * set in the hold time register settings. Setting it to 0, to never
         * deny XIP reads.
         * */
        base->AIPHOLDOFFTIME.bf.AIPholdofftime = 0;

        /* Set the Chip Select corresponding to the windows which is affected
         * by this operation.
         * */
        base->AIPHOLDOFFSEL.bf.AIPwindows = chipSelect;
    }

    /* Set the command attributes*/
    base->SPICMDATTR.dw = regData;

    /* The param array holds configurations for address phase */
    if (paramSize == 0) {
        /* Skip address phase, set address mask bit even when it is skipped */
        regData = base->SPIADDRATTR.dw;
        regData = (regData | (INPH_XSPI_ENABLED
                              << XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_OFFSET)) &
                  (XSPI_MC_REGISTERS_SPIADDRATTR_MASK_INV_MASK);
        regData |= (addrMask << XSPI_MC_REGISTERS_SPIADDRATTR_MASK_OFFSET);

        base->SPIADDRATTR.dw = regData;
        base->SPIADDR.bf.Address = 0;
    }
    else {
        /* Get the address from command parameters, convert it to 32-bit value,
         * For addresses less than 32-bit align MSB to 31st bit.
         * */
        uint32_t addr = 0;
        addr = Inph_XSPI_PackBytes(&cmdParam[0], paramSize);

        /* Set address for SPI transaction */
        base->SPIADDR.bf.Address = addr;

        Inph_XSPI_ConvertAddrTxfrWidth(paramTxfrWidth, &duration, &mode);

        regData = 0;
        regData =
            (regData |
             (duration << XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_OFFSET) |
             (mode << XSPI_MC_REGISTERS_SPIADDRATTR_MODE_OFFSET) |
             (paramDataRate << XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_OFFSET) |
             (addrMask << XSPI_MC_REGISTERS_SPIADDRATTR_MASK_OFFSET)) &
            XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_INV_MASK &
            XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_INV_MASK;

        base->SPIADDRATTR.dw = regData;
    }

    base->SPICS.bf.ChipSelect = chipSelect;

    /* Skip mode phase in the next SPI transaction */
    base->SPIMODEBITS.bf.Bits = 0;
    base->SPIMODEBITSATTR.bf.Skip = INPH_XSPI_ENABLED;

    /* Writing command to the SPI command register executes the written command
     * on the SPI bus. However, there could be additional parameters which
     * need to be configured before executing the command. To accommodate that,
     * save the command to global context to be sent at a later point when all
     * the other command, address and data parameters are configured in their
     * corresponding registers.
     */
    inph_stc_xspi_context_t *context_st = (inph_stc_xspi_context_t *)context;
    context_st->command = cmd;

    /* If this is the last byte then start the transfer immediately */
    if (cmpltTxfr) {
        /* If this is the last byte, then the transfer starts immediately after
         * sending the command. So skip the dummy phase and ensure that the
         * "no write latency" bit is set to 1 in the dummy attribute.
         */
        regData = base->SPIDUMMYATTR.dw;
        regData |=
            (INPH_XSPI_ENABLED << XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_OFFSET) |
            (INPH_XSPI_ENABLED << XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_OFFSET);
        base->SPIDUMMYATTR.dw = regData;

        /* There is no data phase too. Do not set direction,set only skip bit */
        regData =
            (INPH_XSPI_ENABLED << XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_OFFSET);
        base->SPIDATAATTR.dw = regData;

        /* Start Command Transfer */
        Inph_XSPI_StartTransfer(base, context_st);

        /* Wait for busy bit to be cleared to ensure the command execution is
         * complete before sending another command.
         * */
        bool busyStatus = (bool)Inph_XSPI_BusyCheck(base);
        while (busyStatus && (result != INPH_XSPI_ERROR_TIMEOUT)) {
            busyStatus = (bool)Inph_XSPI_BusyCheck(base);
            result = Inph_XSPI_Timeout(&timeout);
        }
    }
    return result;
}

/**
 * This function is used to transmit data using the normal xspi interface.
 * This function uses the TX Data FIFO to implement the transmit functionality.
 * The function sets up an interrupt to trigger the TX Data FIFO and uses that
 * interrupt to fill the TX Data FIFO until all the data is transmitted. At the
 * end of the transmission, the TxCmpltCb is executed.  The chip select is
 * de-asserted at the end of transmit.
 *
 * @note The function triggers the transfer and the transfer itself utilizes
 * the interrupt for FIFO operations in the background. Thus, frequent
 * interrupts will be executed after this function is triggered.
 * Since this API is non-blocking and sets up the interrupt to act on the data
 * FIFO, ensure there will be no another instance of the function called
 * before the current instance has completed execution.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] txBuffer        Pointer to the data to be transferred.
 * @param[in] size            Size of txBuffer.
 * @param[in] transferWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds transfer data rate of data being sent
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] TxCmpltCb       Callback to be executed at the end of a transfer.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                            @ref INPH_XSPI_ERROR_FIFO_FULL.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted. The chip select is
 *                            de-asserted at the end of a transmit.
 */
inph_en_xspi_status_t Inph_XSPI_TransmitData_Ext(
    XSPI_Type *base, uint8_t const *txBuffer, uint32_t size,
    inph_en_xspi_transfer_width_t transferWidth,
    inph_en_xspi_data_rate_t dataRate, inph_xspi_event_cb_t TxCmpltCb,
    inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint32_t fifoStatusFull = 0;
    uint32_t regData = 0;
    uint8_t mode = 0;

    /* Check input values */
    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(transferWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(dataRate));
    INPH_ASSERT(INPH_XSPI_BUF_SIZE_VALID(size));

    if (txBuffer == NULL) {
        return result;
    }

    /* Check if there is an ongoing transaction before starting one */
    if (context->transferStatus != INPH_XSPI_READY) {
        return INPH_XSPI_OPERATION_INPROGRESS;
    }

    /* Check if fifo has space to write new data */
    fifoStatusFull = base->FIFOSTS.bf.FULL;
    if (fifoStatusFull != 1) {
        /* reset error code */
        result = INPH_XSPI_SUCCESS;

        Inph_XSPI_ConvertTransferWidthToMode(transferWidth, &mode);

        uint8_t direction = INPH_XSPI_SPIDATAATTR_DIRECTION_WR;
        regData =
            (regData | (mode << XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET) |
            (dataRate << XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET) |
            (direction << XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET)) &
            XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK &
            XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK &
            XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK &
            XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK;

        /* Set the SPI data attribute register */
        base->SPIDATAATTR.dw = regData;

        /* Set the SPI data size register to (# of bits to be transferred - 1)*/
        base->SPIDATASIZE.bf.Size = (size * 8) - 1;

        /* Initialize parameters for Inph_XSPI_PushTxFifo */
        context->txBufferAddr = (uint8_t *)txBuffer;
        context->txBufferSize = size;
        context->txBufferCount = size;
        context->txCmpltCb = TxCmpltCb;
        context->transferStatus = (uint32_t)INPH_XSPI_TX_BUSY;

        /* It is a non-blocking call, enable the transfer tx request interrupt
         * Inph_XSPI_PushTxFifo method will be called from the interrupt
         * and once completed triggers the callback to application
         */
        /* Enable the Write FIFO Fill IRQ enable interrupt */
        base->IRQCTRL.bf.WriteFIFOFillIRQEnable = 1;

        /* Enable the Write FIFO Error IRQ enable interrupt */
        base->IRQCTRL.bf.WriteFIFOErrorIRQEnable = 1;

        /* All the configurations for transmit data are complete, start the
         * execution of the command on the SPI bus, once completed, it will
         * be followed by writing data to the FIFO.
         */
        Inph_XSPI_StartTransfer(base, context);
    }
    else {
        result = INPH_XSPI_ERROR_FIFO_FULL;
    }

    return result;
}

/**
 * This function is used to transmit data using the normal xspi interface.
 * This function transmits data using the TX Data FIFO and txBufferCount to
 * keep track of the transfer count.
 *
 * @note This function does not use interrupt and blocks until completion, the
 * CPU will constantly monitor FIFO status and move data accordingly. The
 * function returns only on completion.
 * @note Ensure that the other transfers are finished before calling this
 * function and it should not be called during non-blocking transfers.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] txBuffer        Pointer to the data to be transferred.
 * @param[in] size            Size of txBuffer.
 * @param[in] transferWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds transfer data rate of data being sent.
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                            @ref INPH_XSPI_ERROR_FIFO_FULL or
 *                            @ref INPH_XSPI_ERROR_TIMEOUT.
 * @pre                       This function is to be preceded by @ref
 *                            Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted.
 */
inph_en_xspi_status_t
Inph_XSPI_TransmitDataBlocking_Ext(XSPI_Type *base, uint8_t const *txBuffer,
                                   uint32_t size,
                                   inph_en_xspi_transfer_width_t transferWidth,
                                   inph_en_xspi_data_rate_t dataRate,
                                   inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_FIFO_FULL;
    uint32_t fifoStatusFull = 0;
    uint32_t regData = 0;
    uint8_t mode = 0;

    /* Check input values */
    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(transferWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(dataRate));
    INPH_ASSERT(INPH_XSPI_BUF_SIZE_VALID(size));

    if (txBuffer == NULL) {
        return INPH_XSPI_ERROR_INVALID_PARAMETER;
    }

    /* Check if there is an ongoing transaction before starting one */
    if (context->transferStatus != INPH_XSPI_READY) {
        return INPH_XSPI_OPERATION_INPROGRESS;
    }

    /* Check if fifo has space to write new data */
    fifoStatusFull = base->FIFOSTS.bf.FULL;
    if (fifoStatusFull != 1) {
        /* reset error code */
        result = INPH_XSPI_SUCCESS;

        Inph_XSPI_ConvertTransferWidthToMode(transferWidth, &mode);

        regData = 0;
        uint8_t direction = INPH_XSPI_SPIDATAATTR_DIRECTION_WR;
        regData =
            (regData | (mode << XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET) |
             (dataRate << XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET) |
             (direction << XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET)) &
            XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK &
            XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK &
            XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK &
            XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK;

        /* Set the SPI data attribute register */
        base->SPIDATAATTR.dw = regData;

        /* Set the SPI data size register to (# of bits to be transferred - 1)*/
        base->SPIDATASIZE.bf.Size = (size * 8) - 1;

        uint32_t timeout = context->timeout;
        inph_stc_xspi_context_t context_st = *context;

        /* Initialize parameters for Inph_XSPI_PushTxFifo */
        context_st.txBufferAddr = (uint8_t *)txBuffer;
        context_st.txBufferSize = size;
        context_st.txBufferCount = size;
        context_st.txCmpltCb = NULL;
        context_st.transferStatus = (uint32_t)INPH_XSPI_TX_BUSY;

        /* All the configurations for transmit data are complete, start the
         * execution of the command on the SPI bus, once completed, it will
         * be followed by writing data to the FIFO.
         */
        Inph_XSPI_StartTransfer(base, &context_st);

        while ((context_st.transferStatus == INPH_XSPI_TX_BUSY) &&
               (result != INPH_XSPI_ERROR_TIMEOUT)) {
            /* Push data into Tx fifo and start transmitting data */
            Inph_XSPI_PushTxFifo(base, &context_st);

            /* Since it's blocking, check if it exceeds timeout value */
            result = Inph_XSPI_Timeout(&timeout);
        }

        if (result == INPH_XSPI_SUCCESS)
        {
            /* Wait for busy bit to be cleared to ensure the command execution
             * is complete before sending another command.
             * */
            timeout = context->timeout;
            bool busyStatus = Inph_XSPI_BusyCheck(base);
            while (busyStatus && (result != INPH_XSPI_ERROR_TIMEOUT)) {
                busyStatus = Inph_XSPI_BusyCheck(base);
                result = Inph_XSPI_Timeout(&timeout);
            }
        }

        if (result == INPH_XSPI_SUCCESS) {
            context_st.transferStatus = (uint32_t)INPH_XSPI_READY;
        }
    }

    return result;
}

/**
 * This function is used to receive data using the normal xspi interface. The
 * chip select is de-asserted at the end of the receive. The data is received
 * into the RX Data FIFO. The function sets up an interrupt to trigger on the
 * RX Data FIFO level and data is read from the RX Data FIFO to the rxBuffer as
 * it gets filled. This function does not block until completion. At the end of
 * the receive complete, the RxCmpltCb is executed.
 *
 * @note The function triggers the receive transaction and the receive operation
 * itself utilizes the interrupt for FIFO operations in the background. Thus,
 * frequent interrupts will be executed after this function is triggered.
 * So ensure there will be no another instance of the function called
 * before the current instance has completed execution.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] rxBuffer        Pointer to the buffer where the received data
 *                            will be stored.
 * @param[in] size            Size of data to be received.
 * @param[in] dataTxfrWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds receive data rate
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] RxCmpltCb       Callback to be executed at the end of reception.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted. The chip select is
 *                            de-asserted at the end of the receive.
 */
inph_en_xspi_status_t
Inph_XSPI_ReceiveData_Ext(XSPI_Type *base, uint8_t *rxBuffer, uint32_t size,
                          inph_en_xspi_transfer_width_t dataTxfrWidth,
                          inph_en_xspi_data_rate_t dataRate,
                          inph_xspi_event_cb_t RxCmpltCb,
                          inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t regData = 0;
    uint8_t mode = 0;

    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(dataTxfrWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(dataRate));
    INPH_ASSERT(INPH_XSPI_BUF_SIZE_VALID(size));

    if (rxBuffer == NULL) {
        return INPH_XSPI_ERROR_INVALID_PARAMETER;
    }

    /* Check if there is an ongoing transaction before starting one */
    if (context->transferStatus != INPH_XSPI_READY) {
        return INPH_XSPI_OPERATION_INPROGRESS;
    }

    Inph_XSPI_ConvertTransferWidthToMode(dataTxfrWidth, &mode);

    regData = 0;
    uint8_t direction = INPH_XSPI_SPIDATAATTR_DIRECTION_RD;
    regData = (regData | (mode << XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET) |
               (dataRate << XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET) |
               (direction << XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET)) &
              XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK;

    /* Set the SPI data attribute register */
    base->SPIDATAATTR.dw = regData;

    /* Set the SPI data size register to (# of bits to be received - 1) */
    base->SPIDATASIZE.bf.Size = (size * 8) - 1;

    /* Initialize parameters for Inph_XSPI_PopRxFifo */
    context->rxBufferAddr = (uint8_t *)rxBuffer;
    context->rxBufferSize = size;
    context->rxBufferCount = size;
    context->rxCmpltCb = RxCmpltCb;
    context->transferStatus = (uint32_t)INPH_XSPI_RX_BUSY;

    /* It is a non-blocking call, enable the transfer Rx request interrupt
     * Inph_XSPI_PopRxFifo method will be called from the interrupt
     * and once completed triggers the callback to application
     */
    /* Enable the Read FIFO Fill IRQ enable interrupt */
    base->IRQCTRL.bf.ReadFIFOFillIRQEnable = 1;

    /* Enable the Read FIFO Error IRQ enable interrupt */
    base->IRQCTRL.bf.ReadFIFOErrorIRQEnable = 1;

    /* All the configurations for receiving data are complete, start the
     * execution of the command on the SPI bus, once completed, it will be
     * followed by reading data to the Rx FIFO.
     */
    Inph_XSPI_StartTransfer(base, context);

    return result;
}

/**
 * This function is used to receive data using the normal xspi interface.
 * The data is received into the RX Data FIFO.
 *
 * @note This function does not use interrupt and blocks until completion. the
 * CPU will constantly monitor FIFO status and move data accordingly. The
 * function returns only on completion.
 * @note Ensure that the other transfers are finished before calling this
 * function and it should not be called during non-blocking transfers.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] rxBuffer        Pointer to the buffer where the received data
 *                            will be stored.
 * @param[in] size            Size of data to be received.
 * @param[in] dataTxfrWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds receive data rate
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                            @ref INPH_XSPI_ERROR_TIMEOUT.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted. The chip select is
 *                            de-asserted at the end of the receive.
 */
inph_en_xspi_status_t Inph_XSPI_ReceiveDataBlocking_Ext(
                            XSPI_Type *base, uint8_t *rxBuffer, uint32_t size,
                            inph_en_xspi_transfer_width_t dataTxfrWidth,
                            inph_en_xspi_data_rate_t dataRate,
                            inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t regData = 0;
    uint8_t mode = 0;

    /* Check input values */
    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(dataTxfrWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(dataRate));
    INPH_ASSERT(INPH_XSPI_BUF_SIZE_VALID(size));

    if (rxBuffer == NULL) {
        return INPH_XSPI_ERROR_INVALID_PARAMETER;
    }

    /* Check if there is an ongoing transaction before starting one */
    if (context->transferStatus != INPH_XSPI_READY) {
        return INPH_XSPI_OPERATION_INPROGRESS;
    }

    Inph_XSPI_ConvertTransferWidthToMode(dataTxfrWidth, &mode);

    regData = 0;
    uint8_t direction = INPH_XSPI_SPIDATAATTR_DIRECTION_RD;
    regData = (regData | (mode << XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET) |
               (dataRate << XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET) |
               (direction << XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET)) &
              XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK;

    /* Set the SPI data attribute register */
    base->SPIDATAATTR.dw = regData;

    /* Set the SPI data size register to (# of bits to be received - 1) */
    base->SPIDATASIZE.dw = (size * 8) - 1;

    uint32_t timeout = context->timeout;
    inph_stc_xspi_context_t context_st = *context;

    /* Initialize parameters for Inph_XSPI_PopRxFifo */
    context_st.rxBufferAddr = (uint8_t *)rxBuffer;
    context_st.rxBufferSize = size;
    context_st.rxBufferCount = size;
    context_st.rxCmpltCb = NULL;
    context_st.transferStatus = (uint32_t)INPH_XSPI_RX_BUSY;

    /* All the configurations for receiving data are complete, start the
     * execution of the command on the SPI bus, once completed, it will be
     * followed by reading data to the Rx FIFO.
     */
    Inph_XSPI_StartTransfer(base, &context_st);

    while ((context_st.transferStatus == INPH_XSPI_RX_BUSY) &&
           (result != INPH_XSPI_ERROR_TIMEOUT)) {
        /* Pop data from Rx fifo and start reading data */
        Inph_XSPI_PopRxFifo(base, &context_st);

        /* Since it's blocking, check if it exceeds timeout value */
        result = Inph_XSPI_Timeout(&timeout);
    }

    if (result == INPH_XSPI_SUCCESS)
    {
        /* Wait for busy bit to be cleared to ensure the command execution
         * is complete before sending another command.
         * */
        timeout = context->timeout;
        bool busyStatus = Inph_XSPI_BusyCheck(base);
        while (busyStatus && (result != INPH_XSPI_ERROR_TIMEOUT)) {
            busyStatus = Inph_XSPI_BusyCheck(base);
            result = Inph_XSPI_Timeout(&timeout);
        }
    }

    if (result == INPH_XSPI_SUCCESS) {
        context_st.transferStatus = (uint32_t)INPH_XSPI_READY;
    }

    return result;
}

/**
 * This function configures the dummy clock cycles.
 *
 * @note This function configures the dummy cycles, the settings are transmitted
 * in the receive or transmit data functions which succeed this call.
 * @note Supports SPI mode and single data rate only.
 * @note If there is no dummy cycle, set cycles to 0 in-order to skip the phase.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] cycles          Holds the number of dummy cycles to be sent.
 * @param[in] transferWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds receive data rate
 *                            @ref inph_en_xspi_data_rate_t
 * @return                    PDL status @ref INPH_XSPI_SUCCESS.
 * @pre                       This function is to be preceded by
 *                            @ref Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted.
 */
inph_en_xspi_status_t Inph_XSPI_SendDummyCycles_Ext(
    XSPI_Type *base, inph_en_xspi_transfer_width_t dataTxfrWidth,
    inph_en_xspi_data_rate_t dataRate, uint32_t cycles)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t regData = 0;

    UNUSED(dataTxfrWidth);
    UNUSED(dataRate);

    if (cycles == 0) {
        /* Skip the dummy phase and ensure that the "no write latency" bit is
         *  set to 1 in the dummy attribute.
         */
        regData = base->SPIDUMMYATTR.dw;
        regData |=
            (INPH_XSPI_ENABLED << XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_OFFSET) |
            (INPH_XSPI_ENABLED << XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_OFFSET);
    }
    else {
        uint8_t duration = 0;

        /* Set duration to (length of dummy phase in SPI cock cycle - 1) */
        duration = cycles - 1;
        regData =
            ((duration << XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_OFFSET) |
             (INPH_XSPI_ENABLED
              << XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_OFFSET)) &
            XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_INV_MASK;
    }

    /* Set the SPI data attribute register */
    base->SPIDUMMYATTR.dw = regData;

    return result;
}

/**
 * This function is used to transmit data using the normal xspi interface.
 * This function initiates the data transfer via DMA. It sets up an interrupt
 * to trigger when the DMA has successfully transferred one or more buffers.
 * At the end of the transmission, the TxCmpltCb is executed and the chip select
 * is de-asserted.
 *
 * @note The function triggers the transfer and the transfer itself utilizes
 * the interrupt for DMA operations in the background. Since this API is
 * non-blocking, ensure there will be no another instance of the function
 * called before the current instance has completed execution.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] txBuffer        Pointer to the data to be transferred.
 * @param[in] size            Size of txBuffer (in bytes).
 * @param[in] dataTxfrWidth   Holds the width of the transfer
 *                            @inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds transfer data rate of data being sent
 *                            @inph_en_xspi_data_rate_t
 * @param[in] TxCmpltCb       Callback to be executed at the end of a transfer.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be
 *                            @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS.
 * @pre                       This function is to be preceded by @ref
 *                            Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted.
 */
inph_en_xspi_status_t Inph_XSPI_TransmitDataDMA(
    XSPI_Type *base, uint32_t const *txBuffer, uint32_t size,
    inph_en_xspi_transfer_width_t dataTxfrWidth,
    inph_en_xspi_data_rate_t dataRate, inph_xspi_event_cb_t TxCmpltCb,
    inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t regData = 0;
    uint8_t mode = 0;

    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(dataTxfrWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(dataRate));
    INPH_ASSERT(INPH_XSPI_BUF_SIZE_VALID(size));

    if (txBuffer == NULL) {
        return INPH_XSPI_ERROR_INVALID_PARAMETER;
    }

    /* Check if there is an ongoing transaction before starting one */
    if (context->transferStatus != INPH_XSPI_READY) {
        return INPH_XSPI_OPERATION_INPROGRESS;
    }

    Inph_XSPI_ConvertTransferWidthToMode(dataTxfrWidth, &mode);

    uint8_t direction = INPH_XSPI_SPIDATAATTR_DIRECTION_WR;
    regData = (regData | (mode << XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET) |
               (dataRate << XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET) |
               (direction << XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET)) &
              XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK;

    /* Set the SPI data attribute register */
    base->SPIDATAATTR.dw = regData;

    /* Size of allocated memory blocks in 4 byte word */
    uint32_t size_in_words = (txBuffer[0] >> INPH_XSPI_DMA_SIZE_POS) & 0xFFFF;
    base->SPIDATASIZE.bf.Size = (size_in_words * 32) - 1; /* size in bits */

    /* Set the start address of the first DMA descriptor.
     * Can be changed only when DMA is idle. The DMA engine updates this
     * register to the address of current buffer descriptor being processed.
     * */
    base->DMASTARTADR.dw = (uint32_t)&txBuffer[0];

    /* Set to 4 byte burst */
    base->DMAFXDBL.bf.FixedBL = 1;

    /* Enable DMA, at this point the requests are issues to both system
     * memory and SPI memory
     * */
    base->GLBLCTRL.bf.DMAEnable = 1;

    /* Set busy status */
    context->transferStatus = (uint32_t)INPH_XSPI_TX_BUSY;
    context->txCmpltCb = TxCmpltCb;

    /* If the IRQ bit is set in the buffer descriptor, then indicate successful
     * DMA transfer through interrupts
     * */
    uint8_t irqEn = (txBuffer[0] >> INPH_XSPI_DMA_ATTR_INT_POS) & 1;
    if (irqEn == 1) {
        /* Enable DMA transfer complete interrupt */
        base->IRQCTRL.bf.DMAIRQEnable = 1;
        base->IRQCTRL.bf.DMAErrorIRQEnable = 1;
    }

    /* All the configurations for transmit data are complete, start the
     * execution of the command on the SPI bus, once completed, it will
     * be followed by writing data to the FIFO.
     */
    Inph_XSPI_StartTransfer(base, context);

    return result;
}

/**
 * This function is used to receive data using the normal xspi interface.
 * This function initiates the data receive operation via DMA. It sets up an
 * interrupt to trigger when the DMA has successfully transferred one or more
 * buffers. At the end of the transmission, the RxCmpltCb is executed and the
 * chip select is de-asserted.
 *
 * @note The function triggers the transaction and utilizes the interrupt
 * for DMA operations in the background. Since this API is non-blocking, ensure
 * there will be no another instance of the function called before the current
 * instance has completed execution.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] rxBuffer        Pointer to the buffer where the received data
 *                            will be stored.
 * @param[in] size            Size of data to be received (in bytes).
 * @param[in] dataTxfrWidth   Holds the width of the transfer
 *                            @ref inph_en_xspi_transfer_width_t
 * @param[in] dataRate        Holds receive data rate
 *                            @ref inph_en_xspi_data_rate_t
 * @param[in] RxCmpltCb       Callback to be executed at the end of reception.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    PDL status which can be @ref INPH_XSPI_SUCCESS or
 *                            @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                            @ref INPH_XSPI_OPERATION_INPROGRESS
 * @pre                       This function is to be preceded by @ref
 *                            Inph_XSPI_TransmitCommand_Ext where the chip
 *                            select is asserted.
 */
inph_en_xspi_status_t
Inph_XSPI_ReceiveDataDMA(XSPI_Type *base, uint32_t *rxBuffer, uint32_t size,
                         inph_en_xspi_transfer_width_t dataTxfrWidth,
                         inph_en_xspi_data_rate_t dataRate,
                         inph_xspi_event_cb_t RxCmpltCb,
                         inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t regData = 0;
    uint8_t mode = 0;

    /* Check input values */
    INPH_ASSERT(INPH_XSPI_TXFR_WIDTH_VALID(dataTxfrWidth));
    INPH_ASSERT(INPH_XSPI_DATA_RATE_VALID(dataRate));
    INPH_ASSERT(INPH_XSPI_BUF_SIZE_VALID(size));

    if (rxBuffer == NULL) {
        return INPH_XSPI_ERROR_INVALID_PARAMETER;
    }

    /* Check if there is an ongoing transaction before starting one */
    if (context->transferStatus != INPH_XSPI_READY) {
        return INPH_XSPI_OPERATION_INPROGRESS;
    }

    Inph_XSPI_ConvertTransferWidthToMode(dataTxfrWidth, &mode);

    regData = 0;
    uint8_t direction = INPH_XSPI_SPIDATAATTR_DIRECTION_RD;
    regData = (regData | (mode << XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET) |
               (dataRate << XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET) |
               (direction << XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET)) &
              XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK &
              XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK;

    /* Set the SPI data attribute register */
    base->SPIDATAATTR.dw = regData;

    /* Size of allocated memory blocks in 4 byte word */
    uint32_t size_in_words = (rxBuffer[0] >> INPH_XSPI_DMA_SIZE_POS) & 0xFFFF;
    base->SPIDATASIZE.bf.Size = (size_in_words * 32) - 1; /* size in bits */

    /* Set the start address of the first DMA descriptor.
     * Can be changed only when DMA is idle. The DMA engine updates this
     * register to the address of current buffer descriptor being processed.
     * */
    base->DMASTARTADR.dw = (uint32_t)&rxBuffer[0];

    /* Set to 4 byte burst */
    base->DMAFXDBL.dw = 1;

    /* Enable DMA, at this point the requests are issues to both system
     * memory and SPI memory
     * */
    base->GLBLCTRL.bf.DMAEnable = 1;

    /* Set busy status */
    context->transferStatus = (uint32_t)INPH_XSPI_RX_BUSY;
    context->rxCmpltCb = RxCmpltCb;

    /* If the IRQ bit is set in the buffer descriptor, then indicate successful
     * DMA transfer through interrupts
     * */
    uint8_t irqEn = (rxBuffer[0] >> INPH_XSPI_DMA_ATTR_INT_POS) & 1;
    if (irqEn == 1) {
        /* Enable DMA transfer complete interrupt */
        base->IRQCTRL.bf.DMAIRQEnable = 1;
        base->IRQCTRL.bf.DMAErrorIRQEnable = 1;
    }

    /* All the configurations for receiving data are complete, start the
     * execution of the command on the SPI bus. Command execution completed,
     * is signaled by busy field in spi status register.
     */
    Inph_XSPI_StartTransfer(base, context);

    return result;
}

#if defined(__cplusplus)
}
#endif
