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

#ifdef __cplusplus
extern "C" {
#endif

#include "inph_xspi_flash_dev.h"

inph_xspi_t xspi_obj;

const inph_stc_xspi_mem_config_t* const inphXSPIMemConfigs1[] = {
   &GD25Q64E_3byteaddr_SlaveSlot_0,
   NULL
};

void flash_config_io(void)
{
    uint32_t val;
    volatile uint32_t *alt_fn_sel_port_b_lower = (uint32_t*)GPIO_PORTB_BASE;
    volatile uint32_t *alt_fn_sel_port_b_upper = (uint32_t*)(GPIO_PORTB_BASE + 4);

    /* Select flash signals as the alternate function for Port B, Pins 2-3 */
    val = *alt_fn_sel_port_b_lower;
    val &= ~0xff00;
    val |= 0x1100;
    *alt_fn_sel_port_b_lower = val;

    /* Select flash signals as the alternate function for Port B, Pins 4-7 */
    *alt_fn_sel_port_b_upper = 0x1111;

    /* Enable alternate function on Port B, Pins 2-7 */
    *((volatile uint32_t*)(GPIO_ARM_CNTRL0 + 0x18)) = 0xfc00;
}


inph_en_xspi_status_t Inph_XSPI_MemCmdReadID(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint8_t *deviceID, uint8_t command, inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint32_t deviceIDLen = 0;
    uint32_t dummyCycles = 0;

    /* Wait for completion of current transfer before starting new command */
    while (context->transferStatus != INPH_XSPI_READY)
        ;

    if (command == INPH_XSPI_RD_JEDEC_ID_CMD) {
        /* 0x9F - no dummy no addr, returns 3 bytes */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, command, false, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, NULL, 0, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, INPH_XSPI_ADDR_MASK_BYTE,
            memConfig->chipSelect, INPH_XSPI_TX_NOT_LAST_BYTE, context);

        deviceIDLen = 3;
        dummyCycles = 0;
    }
    else if (command == INPH_XSPI_RD_MANU_DEV_ID_CMD) {
        /* 0x90 - 2 dummy - 1 addr (0x00) , returns 2 byte data
         * 0x90 - (00-00-00) - MID-DID
         */
        uint8_t addr[3];
        addr[0] = 0;
        addr[1] = 0;
        addr[2] = 0;

        result = Inph_XSPI_TransmitCommand_Ext(
            base, command, false, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, addr, 1, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, INPH_XSPI_ADDR_MASK_BYTE,
            memConfig->chipSelect, INPH_XSPI_TX_NOT_LAST_BYTE, context);

        deviceIDLen = 2;
        dummyCycles = 16;
    }
    else if (command == INPH_XSPI_RD_DEV_ID_CMD) {
        /* 0xAB - 3 dummy, returns 1 byte data */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, command, false, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, NULL, 0, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, INPH_XSPI_ADDR_MASK_BYTE,
            memConfig->chipSelect, INPH_XSPI_TX_NOT_LAST_BYTE, context);

        deviceIDLen = 1;
        dummyCycles = 24;
    }

    if (result == INPH_XSPI_SUCCESS) {
        result = Inph_XSPI_SendDummyCycles(base, dummyCycles);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_ReceiveDataBlocking_Ext(
                base, deviceID, deviceIDLen, INPH_XSPI_WIDTH_SINGLE,
                INPH_XSPI_DATA_RATE_SDR, context);
        }
    }

    return result;
}

inph_en_xspi_status_t Inph_XSPI_SerialFlashReadID(
    const inph_stc_xspi_mem_config_t *qspi_flash_mem_config)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR;
    uint8_t deviceID[3];

    for (int i = 0; i < 3; i++) {
        deviceID[i] = 0;
    }

    result =
        Inph_XSPI_MemCmdReadID(xspi_obj.base, qspi_flash_mem_config, deviceID,
                               INPH_XSPI_RD_JEDEC_ID_CMD, &xspi_obj.context);
    if (result == INPH_XSPI_SUCCESS) {
        result = INPH_XSPI_ERROR;

        result = Inph_XSPI_MemCmdReadID(
            xspi_obj.base, qspi_flash_mem_config, deviceID,
            INPH_XSPI_RD_MANU_DEV_ID_CMD, &xspi_obj.context);

        if (result != INPH_XSPI_SUCCESS) {
            return INPH_XSPI_ERROR;
        }

        result = Inph_XSPI_MemCmdReadID(
        xspi_obj.base, qspi_flash_mem_config, deviceID,
        INPH_XSPI_RD_DEV_ID_CMD, &xspi_obj.context);

        if (result != INPH_XSPI_SUCCESS) {
            return INPH_XSPI_ERROR;
        }

        return INPH_XSPI_SUCCESS;
    }

    return result;
}

inph_en_xspi_status_t Inph_XSPI_SerialFlashInit(
    const inph_stc_xspi_mem_config_t *qspi_flash_mem_config)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    bool isQuadEnabled = false;

    if ((xspi_obj.base != NULL) && (qspi_flash_mem_config != NULL) &&
        (qspi_flash_mem_config->deviceCfg != NULL)) {
        result = INPH_XSPI_SUCCESS;

        INPH_ASSERT(
            INPH_XSPI_CHIP_SEL_VALID(qspi_flash_mem_config->chipSelect));

        /* Set the active CS to the CS where the NOR flash is connected to */
        xspi_obj.slave_select = qspi_flash_mem_config->chipSelect;

        /* Check if you can talk to the attached flash device */
        result = Inph_XSPI_SerialFlashReadID(qspi_flash_mem_config);
        if (result == INPH_XSPI_SUCCESS)
        {
            /* Enable Quad mode */
            if (qspi_flash_mem_config->deviceCfg->readCmd->dataWidth ==
                INPH_XSPI_WIDTH_QUAD) {
                result = Inph_XSPI_MemIsQuadEnabled(xspi_obj.base,
                                                    qspi_flash_mem_config,
                                                    &isQuadEnabled,
                                                    &xspi_obj.context);
                if ((result == INPH_XSPI_SUCCESS) && !isQuadEnabled) {
                    result = Inph_XSPI_MemEnableQuadMode(
                        xspi_obj.base, qspi_flash_mem_config,
                        INPH_XSPI_FLASH_QUAD_ENABLE_TIMEOUT_US, &xspi_obj.context);
                }
            }
        }
    }

    return result;
}

#ifdef __cplusplus
}
#endif
