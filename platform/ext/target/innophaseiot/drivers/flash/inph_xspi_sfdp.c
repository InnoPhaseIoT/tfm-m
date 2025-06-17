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
 * @file    inph_xspi_sfdp.c
 * @author  Innophase Firmware Team
 * @brief   Provides APIs for SFDP enumeration in xSPI driver
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "inph_xspi_memslot.h"

/* Private typedef -----------------------------------------------------------*/

typedef struct {
    uint8_t  idLsb;
    uint8_t  minorRev;
    uint8_t  majorRev;
    uint8_t  paramLen;
    uint8_t  paramTablePtr[3];
    uint8_t  idMsb;
}inph_stc_xspi_sfdp_parameter_hdr_t;

typedef struct {
    uint32_t signature;
    uint8_t  minorRev;
    uint8_t  majorRev;
    uint8_t  numParamHeader;
    uint8_t  acessProtocol;

    /* JEDEC defined parameter header */
    inph_stc_xspi_sfdp_parameter_hdr_t parameter_hdr[];
}inph_stc_xspi_sfdp_header_t;

typedef union {
    struct {
        uint32_t dWord1;
        uint32_t dWord2;
        uint32_t dWord3;
        uint32_t dWord4;
        uint32_t dWord5;
        uint32_t dWord6;
        uint32_t dWord7;
        uint32_t dWord8;
        uint32_t dWord9;
        uint32_t dWord10;
        uint32_t dWord11;
        uint32_t dWord12;
        uint32_t dWord13;
        uint32_t dWord14;
        uint32_t dWord15;
        uint32_t dWord16;
    }bfptParam;
    uint32_t bfptDWords[16];
}inph_stc_xspi_sfdp_bfpt_table_t;

/**
* This internal structure is used to store data for erase types.
*/
typedef struct
{
    uint8_t eraseCmd;      /**< The instruction used for erase transaction */
    uint32_t eraseSize;    /**< The number of bytes to be erased at one erase transaction */
    uint32_t eraseTime;    /**< The maximum erase time for one erase transaction */
} inph_stc_xspi_sfdp_erase_type_t;

typedef struct
{
    uint16_t dummyClks : 5;
    uint16_t modeClks : 3;
    uint16_t opCode : 8;
} inph_stc_xspi_sfdp_read_param_t;

/** Specifies protocol mode. */
typedef enum
{
    READ_MODE_1S_1S_1S        = 1U,     /**< One DQ signal used during command transfer,
                                             * address transfer, and data transfer. All phases are SDR.
                                             */
    READ_MODE_1S_1S_2S        = 2U,     /**< One DQ signal used during command transfer, and address transfer,
                                             *  two DQ signals used during data transfer. All phases are SDR.
                                             */
    READ_MODE_1S_2S_2S        = 3U,     /**< One DQ signal used during command transfer, two DQ signals used
                                             *  during address transfer, and data transfer. All phases are SDR.
                                             */
    READ_MODE_1S_1S_4S        = 4U,     /**< One DQ signal used during command and address transfer,
                                             * four DQ signals used during data transfer. All phases are SDR.
                                             */
    READ_MODE_1S_4S_4S        = 5U,     /**< One DQ signal used during command transfer, four DQ signals used
                                            * during address transfer, and data transfer. All phases are SDR.
                                            */
    READ_MODE_WRONG           = 0xFFU   /**< Unknown or unsupported mode */
} inph_en_xspi_sfdp_read_mode_t;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define INPH_XSPI_DWORD_SIZE_IN_BYTES           4
#define INPH_XSPI_SFDP_BASIC_PARAM_TABLE_LEN    16
#define INPH_XSPI_SFDP_LENGTH                   (INPH_XSPI_SFDP_BASIC_PARAM_TABLE_LEN * INPH_XSPI_DWORD_SIZE_IN_BYTES)
#define INPH_XSPI_SFDP_SIGNATURE                0x50444653
#define INPH_XSPI_SFDP_MINOR_REV_216G           0x0B
#define INPH_XSPI_XFDP_ACCESS_PROTOCOL          0xFF // backward compatibe with 216B

/* SFDP basic parameter time in units */
#define INPH_XSPI_SFDP_UNIT_0                         (0U)                    /**< Units of Basic Flash Parameter Table Time Parameters */
#define INPH_XSPI_SFDP_UNIT_1                         (1U)                    /**< Units of Basic Flash Parameter Table Time Parameters */
#define INPH_XSPI_SFDP_UNIT_2                         (2U)                    /**< Units of Basic Flash Parameter Table Time Parameters */
#define INPH_XSPI_SFDP_UNIT_3                         (3U)                    /**< Units of Basic Flash Parameter Table Time Parameters */

#define INPH_XSPI_SFDP_ERASE_TIME_1MS                 (1U)                    /**< Units of Erase Typical Time in ms */
#define INPH_XSPI_SFDP_ERASE_TIME_16MS                (16U)                   /**< Units of Erase Typical Time in ms */
#define INPH_XSPI_SFDP_ERASE_TIME_128MS               (128U)                  /**< Units of Erase Typical Time in ms */
#define INPH_XSPI_SFDP_ERASE_TIME_256MS               (256U)                  /**< Units of Erase Typical Time in ms */
#define INPH_XSPI_SFDP_ERASE_TIME_1S                  (1000U)                 /**< Units of Erase Typical Time in ms */
#define INPH_XSPI_SFDP_ERASE_TIME_4S                  (4000U)                 /**< Units of Erase Typical Time in ms */
#define INPH_XSPI_SFDP_ERASE_TIME_64S                 (64000U)                /**< Units of Erase Typical Time in ms */

#define INPH_XSPI_SFDP_PAGE_PRGM_TIME_8US             (8U)                    /**< Units of Page Program Typical Time in us */
#define INPH_XSPI_SFDP_PAGE_PRGM_TIME_64US            (64U)                   /**< Units of Page Program Typical Time in us */

#define INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_128NS          (128U)              /**< Units of Erase Suspend Time in ns */
#define INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_1US            (1000U)             /**< Units of Erase Suspend Time in ns */
#define INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_8US            (8000U)             /**< Units of Erase Suspend Time in ns */
#define INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_64US           (64000U)            /**< Units of Erase Suspend Time in ns */

#define INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos        (8U)
#define INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Msk                              \
                            (0xFFU << INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos          (5U)
#define INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Msk                                \
                            (0x7U << INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos         (0U)
#define INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Msk                               \
                            (0x1FU << INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos)

// Byte 0 of 1st DWORD in BFPT
#define INPH_XSPI_SFDP_BFPT_DWORD1_BYTE_0_Pos            (0x0U)

#define INPH_XSPI_SFDP_BFPT_4K_ERASE_SUPPORT_Pos         (0U)
#define INPH_XSPI_SFDP_BFPT_4K_ERASE_SUPPORT_Msk                               \
        (0x3U << INPH_XSPI_SFDP_BFPT_4K_ERASE_SUPPORT_Pos)
#define INPH_XSPI_SFDP_BFPT_4K_ERASE_SUPPORT             (1U)

#define INPH_XSPI_SFDP_BFPT_READ_1S_1S_2S_SUPPORT_Pos    (16UL)
#define INPH_XSPI_SFDP_BFPT_READ_1S_1S_2S_SUPPORT_Msk                          \
                                    (1 << INPH_XSPI_SFDP_BFPT_READ_1S_1S_2S_SUPPORT_Pos)

#define INPH_XSPI_SFDP_BFPT_ADDR_BYTES_SUPPORTED_Pos     (17U)
#define INPH_XSPI_SFDP_BFPT_ADDR_BYTES_SUPPORTED_Msk                           \
        (0x3U << INPH_XSPI_SFDP_BFPT_ADDR_BYTES_SUPPORTED_Pos) /*!< 0x01 default */

#define INPH_XSPI_SFDP_BFPT_3BYTE_ADDRESSING             (0U)
#define INPH_XSPI_SFDP_BFPT_3BYTE_OR_4BYTE_ADDRESSING    (1U)
#define INPH_XSPI_NUM_ADDR_BYTES                         (3U) // TODO: move it to memslot header

#define INPH_XSPI_SFDP_BFPT_DTR_SUPPORT_Pos              (19UL)
#define INPH_XSPI_SFDP_BFPT_DTR_SUPPORT_Msk                                    \
                                    (1 << INPH_XSPI_SFDP_BFPT_DTR_SUPPORT_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_1S_2S_2S_SUPPORT_Pos    (20UL)
#define INPH_XSPI_SFDP_BFPT_READ_1S_2S_2S_SUPPORT_Msk                          \
                           (1 << INPH_XSPI_SFDP_BFPT_READ_1S_2S_2S_SUPPORT_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_1S_4S_4S_SUPPORT_Pos    (21UL)
#define INPH_XSPI_SFDP_BFPT_READ_1S_4S_4S_SUPPORT_Msk                          \
                          (1 << INPH_XSPI_SFDP_BFPT_READ_1S_4S_4S_SUPPORT_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_1S_1S_4S_SUPPORT_Pos    (22UL)
#define INPH_XSPI_SFDP_BFPT_READ_1S_1S_4S_SUPPORT_Msk                          \
                            (1 << INPH_XSPI_SFDP_BFPT_READ_1S_1S_4S_SUPPORT_Pos)

/* DWord - 2 */
#define INPH_XSPI_SFDP_BFPT_DWORD2_BYTE_0_Pos            (0x04U)
#define INPH_XSPI_SFDP_BFPT_SIZE_ABOVE_4GB               (0x80000000UL)          /**< Flash memory density bit define if it >= 4 Gbit  or <= 2Gbit */
#define INPH_XSPI_SFDP_BFPT_SIZE_16Mb                    (0x7FFFFFFUL)          /**< Flash memory density of 16Mbits */

/* DWord - 3 */
#define INPH_XSPI_SFDP_BFPT_DWORD3_BYTE_0_Pos            (0x8U)

#define INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos        (8U)
#define INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Msk                              \
                            (0xFFU << INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos          (5U)
#define INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Msk                                \
                            (0x7U << INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos)

#define INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos         (0U)
#define INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Msk                               \
                            (0x1FU << INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos)

/* DWord - 4 */
#define INPH_XSPI_SFDP_BFPT_DWORD4_BYTE_0_Pos            (0x0CU)

/* DWord - 5 */
#define INPH_XSPI_SFDP_BFPT_DWORD5_BYTE_0_Pos            (0x10U)

/* DWord - 6 */
#define INPH_XSPI_SFDP_BFPT_DWORD6_BYTE_0_Pos            (0x14U)

/* DWord - 7 */
#define INPH_XSPI_SFDP_BFPT_DWORD7_BYTE_0_Pos            (0x18U)

/* DWord - 8 */
#define INPH_XSPI_SFDP_BFPT_DWORD8_BYTE0_Pos             (0x1C)
#define INPH_XSPI_SFDP_ERASE_TYPE_CNT                    (4U)

/* DWord - 9 */
#define INPH_XSPI_SFDP_BFPT_DWORD9_BYTE0_Pos             (0x20)
#define INPH_XSPI_SFDP_ERASE_TYPE_CNT                    (4U)

/* DWord - 10 */
#define INPH_XSPI_SFDP_BFPT_DWORD10_BYTE_0_Pos           (0x24U)
#define INPH_XSPI_SFDP_BFPT_ERASE_TYP_TIME_Pos           (4U)

#define INPH_XSPI_SFDP_BFPT_MAX_TIME_MULT_Msk    (0x0FU)
#define INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_Msk          (0x7FU) /* 7 bits */
#define INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_COUNT_Msk    (0x1FU) /* 5 bits */
#define INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_UNIT_Pos     (0x5U)  /* 2 bits*/

/* DWord - 11 */
#define INPH_XSPI_SFDP_BFPT_DWORD11_BYTE_0_Pos           (0x28U)

#define INPH_XSPI_SFDP_BFPT_PAGE_SIZE_Pos                (4U)
#define INPH_XSPI_SFDP_BFPT_PAGE_SIZE_Msk                                      \
                                    (0xFU << INPH_XSPI_SFDP_BFPT_PAGE_SIZE_Pos)

#define INPH_XSPI_SFDP_BFPT_PAGE_PRGM_TIME_Pos           (8U)
#define INPH_XSPI_SFDP_BFPT_PAGE_PRGM_TIME_Msk                                \
                               (0x3FU << INPH_XSPI_SFDP_BFPT_PAGE_PRGM_TIME_Pos)
#define INPH_XSPI_SFDP_BFPT_PAGE_PRGM_MAX_TIME_MULT_Msk  (0x0FU)

#define INPH_XSPI_SFDP_BFPT_CHIP_ERASE_TIME_Pos          (24U)
#define INPH_XSPI_SFDP_BFPT_CHIP_ERASE_TIME_Msk                                \
                              (0x7FU << INPH_XSPI_SFDP_BFPT_CHIP_ERASE_TIME_Pos)

/* DWord - 12 */
#define INPH_XSPI_SFDP_BFPT_DWORD12_BYTE_0_Pos           (0x2CU)
#define INPH_XSPI_SFDP_SUSRES_SUPPORT_Pos                (31U)
#define INPH_XSPI_SFDP_SUSRES_Msk                                              \
                              (0x1U << INPH_XSPI_SFDP_SUSRES_SUPPORT_Pos)
#define INPH_XSPI_SFDP_SUSPEND_ERASE_TIME_Pos            (24U)
#define INPH_XSPI_SFDP_SUSPEND_ERASE_TIME_Msk                                  \
                              (0x7FU << INPH_XSPI_SFDP_SUSPEND_ERASE_TIME_Pos)
#define INPH_XSPI_SFDP_ERASE_RES_TO_SUS_TIME_Pos         (20U)
#define INPH_XSPI_SFDP_ERASE_RES_TO_SUS_TIME_Msk                               \
                              (0xFU << INPH_XSPI_SFDP_ERASE_RES_TO_SUS_TIME_Pos)
#define INPH_XSPI_SFDP_SUSPEND_PRGM_TIME_Pos             (13U)
#define INPH_XSPI_SFDP_SUSPEND_PRGM_TIME_Msk                                   \
                              (0x7FU << INPH_XSPI_SFDP_SUSPEND_PRGM_TIME_Pos)
#define INPH_XSPI_SFDP_PRGM_RES_TO_SUS_TIME_Pos          (9U)
#define INPH_XSPI_SFDP_PRGM_RES_TO_SUS_TIME_Msk                                \
                              (0xFU << INPH_XSPI_SFDP_PRGM_RES_TO_SUS_TIME_Pos)

/* DWord - 13 */
#define INPH_XSPI_SFDP_BFPT_DWORD13_BYTE_0_Pos           (0x30U)
#define INPH_XSPI_SFDP_SUSPEND_CMD_Pos                   (24U)
#define INPH_XSPI_SFDP_SUSPEND_CMD_Msk                                         \
                                       (0xFFU << INPH_XSPI_SFDP_SUSPEND_CMD_Pos)
#define INPH_XSPI_SFDP_RESUME_CMD_Pos                    (24U)
#define INPH_XSPI_SFDP_RESUME_CMD_Msk                                          \
                                        (0xFFU << INPH_XSPI_SFDP_RESUME_CMD_Pos)

/* DWord - 15 */
#define INPH_XSPI_SFDP_BFPT_DWORD15_BYTE_0_Pos           (0x38U)

#define INPH_XSPI_SFDP_BFPT_QUAD_EN_REQ_Pos              (20U)
#define INPH_XSPI_SFDP_BFPT_QUAD_EN_REQ_Msk                                    \
                                   (0x7U << INPH_XSPI_SFDP_BFPT_QUAD_EN_REQ_Pos)

/* DWord - 16 */
#define INPH_XSPI_SFDP_BFPT_DWORD16_BYTE_0_Pos           (0x3CU)
#define INPH_XSPI_SFDP_BFPT_RESET_CMD_Pos                (8U)
#define INPH_XSPI_SFDP_BFPT_RESET_CMD_Msk                                      \
                                    (0x3FU << INPH_XSPI_SFDP_BFPT_RESET_CMD_Pos)

/* Private variables ---------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/
/**
 * Resets the memory command structure to default values.
 *
 * @param[in] *memCmd         Pointer to the memory command structure.
 * @return                    none.
 */
static void setMemCmdToDefault(inph_stc_xspi_mem_cmd_t *memCmd)
{
    /* default to spi mode, SDR, no mode, no dummy, no address phase */
    memCmd->command = INPH_XSPI_NO_COMMAND_OR_MODE;
    memCmd->cmdWidth = INPH_XSPI_WIDTH_SINGLE;
    memCmd->cmdRate = INPH_XSPI_DATA_RATE_SDR,
    memCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

    memCmd->addrWidth = INPH_XSPI_WIDTH_SINGLE;
    memCmd->addrRate = INPH_XSPI_DATA_RATE_SDR;
    memCmd->addrPresence = INPH_XSPI_PHASE_SKIP;

    memCmd->modeBits = 0U;
    memCmd->modeWidth = INPH_XSPI_WIDTH_SINGLE;
    memCmd->modeRate = INPH_XSPI_DATA_RATE_SDR;
    memCmd->modePresence = INPH_XSPI_PHASE_SKIP;

    memCmd->dummyCycles = INPH_XSPI_DUMMY_NONE;
    memCmd->dummyCyclesPresence = INPH_XSPI_PHASE_SKIP;

    memCmd->dataWidth = INPH_XSPI_WIDTH_SINGLE;
    memCmd->dataRate = INPH_XSPI_DATA_RATE_SDR;
}

/**
 * This function un-packs 32-bit value into byte array.
 *
 * @param[in]  data           4 bytes byte which needs to be unpacked.
 * @param[out] byteArray      Holds the unpacked 8-bit bytes.
 * @param[in]  data_len       Size of the byte
 * @return                    None.
 */
void wordToByteArray(uint32_t data, uint8_t byteArray[], uint32_t data_len)
{
    if (data_len == INPH_XSPI_4_BYTES) {
        byteArray[3] = (uint8_t)((data >> 24) & 0xFF);
        byteArray[2] = (uint8_t)((data >> 16) & 0xFF);
        byteArray[1] = (uint8_t)((data >> 8) & 0xFF);
        byteArray[0] = (uint8_t)(data & 0xFF);
    }
}

/**
 * This function reads the SFDP data from the flash device.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memCfg        Pointer to command structure used to store the
 *                           command configuration.
 * @param[in] sfdpAddress    Address array holding SFDP header address.
 * @param[in] chipSelect     The chip select line for connected memory device.
 * @param[in] size           Size of the SFDP data
 * @param[out] sfdpBuffer    Array holding the SFDP data read from flash.
 * @param[in] *context       Pointer to the context structure
 * @return                   Status.
 */
static inph_en_xspi_status_t sfdpReadBuffer(XSPI_Type *base,
                                        inph_stc_xspi_mem_cmd_t const *cmdSfdp,
                                        uint8_t const sfdpAddress[],
                                        inph_en_xspi_chip_select_t  chipSelect,
                                        uint32_t size,
                                        uint8_t sfdpBuffer[],
                                        inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_NO_SFDP_SUPPORT;

    result = Inph_XSPI_TransmitCommand_Ext(base, cmdSfdp->command, false,
                                        cmdSfdp->cmdWidth,
                                        cmdSfdp->cmdRate, sfdpAddress,
                                        3,
                                        cmdSfdp->addrWidth,
                                        cmdSfdp->addrRate,
                                        INPH_XSPI_ADDR_MASK_WORD, chipSelect,
                                        INPH_XSPI_TX_NOT_LAST_BYTE, context);
    if (result == INPH_XSPI_SUCCESS) {
        result = Inph_XSPI_SendDummyCycles(
            base, cmdSfdp->dummyCycles);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_ReceiveDataBlocking_Ext(
                base, sfdpBuffer, size,
                cmdSfdp->dataWidth,
                cmdSfdp->dataRate, context);
            }
        }

    return result;
}

/**
 * Gets the number of address bytes supported from Basic Flash Parameter Table.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] numAddrBytes   Number of address bytes supported.
 * @return                    Success if number of address bytes are supported,
 *                            failure otherwise.
 */
static inph_en_xspi_status_t getNumAddressBytes(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                                                uint32_t *numAddrBytes)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t dWord1 = (uint32_t) bfptTable->bfptParam.dWord1;

    uint32_t addrMode = (dWord1 &
                         INPH_XSPI_SFDP_BFPT_ADDR_BYTES_SUPPORTED_Msk) >>
                         INPH_XSPI_SFDP_BFPT_ADDR_BYTES_SUPPORTED_Pos;

    /* We do not support memories beyond 16MB or 4-byte addressing */
    if ((addrMode != INPH_XSPI_SFDP_BFPT_3BYTE_ADDRESSING) &&
        (addrMode != INPH_XSPI_SFDP_BFPT_3BYTE_OR_4BYTE_ADDRESSING))
    {
        result = INPH_XSPI_SFDP_ADDRMODE_UNSUPPORTED;
    }
    else
    {
        *numAddrBytes = INPH_XSPI_NUM_ADDR_BYTES;
    }
    return result;
}

/**
 * Gets the memory density from Basic Flash Parameter Table.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] memoryDenisty  Memory density in bytes.
 * @return                    Success if memory denisty is supported, failure
 *                            otherwise.
 */
static inph_en_xspi_status_t getMemoryDensity(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                                              uint32_t *memoryDenisty)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    uint32_t memSize  = bfptTable->bfptParam.dWord2;

    /* We do not support memory greater than 16MB */
    if (((memSize & INPH_XSPI_SFDP_BFPT_SIZE_ABOVE_4GB) != 0) ||
          (memSize > INPH_XSPI_SFDP_BFPT_SIZE_16Mb))
    {
        result = INPH_XSPI_SFDP_MEMSIZE_UNSUPPORTED;
    }
    else
    {
        /* Get size in bytes */
        *memoryDenisty = ((memSize + 1) / 8);
    }
    return result;
}

/**
 * Gets the erase size and commands supported from Basic Flash Parameter Table.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] eraseType      Structure filled with all erase type's info.
 * @return                    none.
 */
static void getEraseSizeandCmd(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                               inph_stc_xspi_sfdp_erase_type_t eraseType[])
{
    uint32_t idx = 0;
    uint32_t type = 0;
    uint8_t eraseInfo[8];

    wordToByteArray(bfptTable->bfptParam.dWord8, &eraseInfo[0], INPH_XSPI_4_BYTES);
    wordToByteArray(bfptTable->bfptParam.dWord9, &eraseInfo[4], INPH_XSPI_4_BYTES);

    /* Get erase size & cmd for all the erase types from 8th and 9th DWords */
    for (type = 0; type < INPH_XSPI_SFDP_ERASE_TYPE_CNT; type++)
    {
        /* Field specifies n, erase size is 2^n */
        eraseType[type].eraseSize = (1UL << eraseInfo[idx++]);
        eraseType[type].eraseCmd = eraseInfo[idx++];
    }
}

/**
 * Gets the typical time taken by each of the erase types from Basic Flash
 * Parameter Table and calculates the max time taken by each of them.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] eraseType      Structure holds max time taken in milliseconds by
 *                            each of the erase command types.
 * @return                    none.
 */
static void getEraseTime(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                         inph_stc_xspi_sfdp_erase_type_t eraseType[])
{
    uint32_t dWord10 = bfptTable->bfptParam.dWord10;
    uint32_t count = 0;
    uint32_t units = 0;
    uint32_t unitsMs = 0;
    uint32_t maxTimeMultiplier = dWord10 & INPH_XSPI_SFDP_BFPT_MAX_TIME_MULT_Msk;

    uint32_t type = 0;
    uint32_t typicalTime = 0;
    uint32_t timeBitsLen = 7;
    uint32_t timeBitsOffset = 4;
    for (type = 0; type < INPH_XSPI_SFDP_ERASE_TYPE_CNT; type++)
    {
        typicalTime = (dWord10 >> timeBitsOffset) & INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_Msk;
        count = typicalTime & INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_COUNT_Msk;
        units = typicalTime >> INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_UNIT_Pos;

        switch (units)
        {
            case INPH_XSPI_SFDP_UNIT_0:
                unitsMs = INPH_XSPI_SFDP_ERASE_TIME_1MS;
                break;
            case INPH_XSPI_SFDP_UNIT_1:
                unitsMs = INPH_XSPI_SFDP_ERASE_TIME_16MS;
                break;
            case INPH_XSPI_SFDP_UNIT_2:
                unitsMs = INPH_XSPI_SFDP_ERASE_TIME_128MS;
                break;
            case INPH_XSPI_SFDP_UNIT_3:
                unitsMs = INPH_XSPI_SFDP_ERASE_TIME_1S;
                break;
        }

        /* Calculate max erase time(in ms) with typical erase time & multiplier */
        eraseType[type].eraseTime =  ((count + 1) * unitsMs) * (2 * (maxTimeMultiplier + 1));

        // 4+7=11, 11+7=18, 18+7=25
        timeBitsOffset += timeBitsLen;
    }
}

/**
 * Gets the Page size from Basic Flash Parameter Table.
 *
 * @param[in] bfptHeader      Basic Function Parameter Table header structure.
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] pageSize       Page Size supported.
 * @return                    none.
 */
void getPageSize(inph_stc_xspi_sfdp_parameter_hdr_t *bfptHeader,
                 inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                 uint32_t *pageSize)
{
    /* JEDS216 does not have page size information, the # of DWords is 9 */
    if (bfptHeader->paramLen < 11)
    {
        *pageSize = 256;
    }
    else
    {
        uint32_t dWord11 = bfptTable->bfptParam.dWord11;
        uint32_t size = (dWord11 & INPH_XSPI_SFDP_BFPT_PAGE_SIZE_Msk) >>
                        INPH_XSPI_SFDP_BFPT_PAGE_SIZE_Pos;
        *pageSize = 1 << size; // 2^N
    }
}

/**
 * Gets the typical time taken by chip erase from Basic Flash Parameter Table.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] chipEraseTime  Typical chip erase time in milliseconds.
 * @return                    none.
 */
void getChipEraseTime(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable, uint32_t *chipEraseTime)
{
    uint32_t count = 0;
    uint32_t units = 0;
    uint32_t unitsMs = 0;
    uint32_t dWord11 = bfptTable->bfptParam.dWord11;

    uint32_t typicalTime = (dWord11 & INPH_XSPI_SFDP_BFPT_CHIP_ERASE_TIME_Msk)
                            >> INPH_XSPI_SFDP_BFPT_CHIP_ERASE_TIME_Pos;

    count = typicalTime & INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_COUNT_Msk;
    units = typicalTime >> INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_UNIT_Pos;

    switch (units)
    {
        case INPH_XSPI_SFDP_UNIT_0:
            unitsMs = INPH_XSPI_SFDP_ERASE_TIME_16MS;
            break;
        case INPH_XSPI_SFDP_UNIT_1:
            unitsMs = INPH_XSPI_SFDP_ERASE_TIME_256MS;
            break;
        case INPH_XSPI_SFDP_UNIT_2:
            unitsMs = INPH_XSPI_SFDP_ERASE_TIME_4S;
            break;
        case INPH_XSPI_SFDP_UNIT_3:
            unitsMs = INPH_XSPI_SFDP_ERASE_TIME_64S;
            break;
    }

    *chipEraseTime = (count + 1) * unitsMs;

}

/**
 * Gets the typical time taken by page program from Basic Flash Parameter Table
 * and calculates the max time taken for page programming.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] pagePrgmTime   Max time taken for page progam in microseconds.
 * @return                    none.
 */
void getPageProgramTime(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable, uint32_t *pagePrgmTime)
{
    uint32_t count = 0;
    uint32_t units = 0;
    uint32_t unitsUs = 0;
    uint32_t dWord11 = bfptTable->bfptParam.dWord11;

    uint32_t typicalTime = (dWord11 & INPH_XSPI_SFDP_BFPT_PAGE_PRGM_TIME_Msk)
                            >> INPH_XSPI_SFDP_BFPT_PAGE_PRGM_TIME_Pos;

    count = typicalTime & INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_COUNT_Msk;
    units = typicalTime >> INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_UNIT_Pos;

    switch (units)
    {
        case INPH_XSPI_SFDP_UNIT_0:
            unitsUs = INPH_XSPI_SFDP_PAGE_PRGM_TIME_8US;
            break;
        case INPH_XSPI_SFDP_UNIT_1:
            unitsUs = INPH_XSPI_SFDP_PAGE_PRGM_TIME_64US;
            break;
    }

    uint32_t maxTimeMultiplier = dWord11 & INPH_XSPI_SFDP_BFPT_MAX_TIME_MULT_Msk;

    *pagePrgmTime = ((count + 1) * unitsUs) * (2 * (maxTimeMultiplier + 1));
}

/**
 * Gets the quad enable parameters from Basic Flash Parameter Table.
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] *deviceCfg     Pointer to config. structure of memory device
 *                            used to store device-specific parameters.
 * @param[out] qer_id         Quad. enable requirement ID.
 * @return                    none.
 */
void getQuadEnableParameters(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                             inph_stc_xspi_mem_device_cfg_t *deviceCfg,
                             inph_en_xspi_qer_t qer_id)
{
    uint32_t dWord15 = bfptTable->bfptParam.dWord15;

    setMemCmdToDefault(deviceCfg->writeStsRegQeCmd);
    setMemCmdToDefault(deviceCfg->readStsRegQeCmd);

    qer_id =
    (inph_en_xspi_qer_t)((dWord15 & INPH_XSPI_SFDP_BFPT_QUAD_EN_REQ_Msk) >>
                                    INPH_XSPI_SFDP_BFPT_QUAD_EN_REQ_Pos);

    switch (qer_id)
    {
        case INPH_XSPI_SFDP_QER_0:
            deviceCfg->stsRegQuadEnableMask = INPH_XSPI_NO_COMMAND_OR_MODE;
            deviceCfg->writeStsRegQeCmd->command = INPH_XSPI_NO_COMMAND_OR_MODE;
            deviceCfg->writeStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_SKIP;
            deviceCfg->readStsRegQeCmd->command = INPH_XSPI_NO_COMMAND_OR_MODE;
            deviceCfg->readStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_SKIP;
            break;
        case INPH_XSPI_SFDP_QER_1:
        case INPH_XSPI_SFDP_QER_4:
        case INPH_XSPI_SFDP_QER_5:
            deviceCfg->stsRegQuadEnableMask = INPH_XSPI_QE_BIT_1_OF_SR_2;
            deviceCfg->writeStsRegQeCmd->command = INPH_XSPI_WRITE_STATUS_REG1_CMD; //0x01, writes 2 bytes to SR1
            deviceCfg->writeStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
            deviceCfg->readStsRegQeCmd->command = INPH_XSPI_READ_STATUS_REG2_CMD; //0x35
            deviceCfg->readStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

            break;
        case INPH_XSPI_SFDP_QER_2:
            //memCfg->deviceCfg->stsRegQuadEnableMask = INPH_XSPI_QE_BIT_6_OF_SR_1_Msk; // TODO: Do we need this?
            deviceCfg->writeStsRegQeCmd->command = INPH_XSPI_WRITE_STATUS_REG1_CMD;
            deviceCfg->writeStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
            deviceCfg->readStsRegQeCmd->command = INPH_XSPI_READ_STATUS_REG1_CMD;
            deviceCfg->readStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

            break;
        case INPH_XSPI_SFDP_QER_3:
            //memCfg->deviceCfg->stsRegQuadEnableMask = INPH_XSPI_QE_BIT_7_OF_SR_2_Msk; // TODO: do we need this?
            deviceCfg->writeStsRegQeCmd->command = INPH_XSPI_WRITE_STATUS_REG1_CMD;
            deviceCfg->writeStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
            deviceCfg->readStsRegQeCmd->command = INPH_XSPI_READ_STATUS_REG1_CMD;
            deviceCfg->readStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

            break;

        case INPH_XSPI_SFDP_QER_6:
            deviceCfg->stsRegQuadEnableMask = INPH_XSPI_QE_BIT_1_OF_SR_2;
            deviceCfg->writeStsRegQeCmd->command = INPH_XSPI_WRITE_STATUS_REG2_CMD; //0x31, writes 1 byte SR2
            deviceCfg->writeStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
            deviceCfg->readStsRegQeCmd->command = INPH_XSPI_READ_STATUS_REG2_CMD; //0x35
            deviceCfg->readStsRegQeCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
            break;

            break;
        default:
            break;
    };
}

/**
 * Gets the soft reset and reset enable command from Basic Flash Parameter Table
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] *deviceCfg     Pointer to config. structure of memory device
 *                            used to store device-specific parameters.
 * @return                    none.
 */
void getResetCmd(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                inph_stc_xspi_mem_device_cfg_t *deviceCfg)
{
    uint32_t dWord16 = bfptTable->bfptParam.dWord16;
    uint32_t softReset = (dWord16 & INPH_XSPI_SFDP_BFPT_RESET_CMD_Msk) >>
                            INPH_XSPI_SFDP_BFPT_RESET_CMD_Pos;

    setMemCmdToDefault(deviceCfg->resetEnCmd);
    setMemCmdToDefault(deviceCfg->resetCmd);

    /* If chip has a reset command, update the relevant fields */
    if (softReset == 0x10)
    {
        /* Reset Enable cmd is 0x66, Reset cmd is 0x99 */
        /* Update command field */
        deviceCfg->resetEnCmd->command = INPH_XSPI_RESET_ENABLE_CMD;
        deviceCfg->resetCmd->command = INPH_XSPI_RESET_CMD;
    }
}

/**
 * Gets the suspend/resume commands and timing information from the Basic Flash
 * Parameter Table
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] *deviceCfg     Pointer to config. structure of memory device
 *                            used to store device-specific parameters.
 * @return                    none.
 */
void getSusResCmd(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                  inph_stc_xspi_mem_device_cfg_t *deviceCfg)
{
    uint32_t dWord12 = bfptTable->bfptParam.dWord12;
    uint32_t susResSupport = (dWord12 & INPH_XSPI_SFDP_SUSRES_Msk) >>
                                            INPH_XSPI_SFDP_SUSRES_SUPPORT_Pos;

    setMemCmdToDefault(deviceCfg->suspendCmd);
    setMemCmdToDefault(deviceCfg->resumeCmd);

    deviceCfg->susResSupport = susResSupport;
    if (susResSupport)
    {
        uint32_t dWord13 = bfptTable->bfptParam.dWord13;

        deviceCfg->suspendCmd->command =
                                (dWord13 & INPH_XSPI_SFDP_SUSPEND_CMD_Msk) >>
                                                INPH_XSPI_SFDP_SUSPEND_CMD_Pos;

        deviceCfg->resumeCmd->command =
                                (dWord13 & INPH_XSPI_SFDP_RESUME_CMD_Msk) >>
                                                INPH_XSPI_SFDP_RESUME_CMD_Pos;

        /* Max latency to suspend in-progress erase */
        uint32_t latency = (dWord12 & INPH_XSPI_SFDP_SUSPEND_ERASE_TIME_Msk) >>
                            INPH_XSPI_SFDP_SUSPEND_ERASE_TIME_Pos;

        uint32_t count = latency & INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_COUNT_Msk;
        uint32_t units = latency >> INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_UNIT_Pos;
        uint32_t unitsNs = 0;

        switch (units)
        {
            case INPH_XSPI_SFDP_UNIT_0:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_128NS;
                break;
            case INPH_XSPI_SFDP_UNIT_1:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_1US;
                break;
            case INPH_XSPI_SFDP_UNIT_2:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_8US;
                break;
            case INPH_XSPI_SFDP_UNIT_3:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_64US;
                break;
        }

        // eg. units = 1, count = 19 latency = (19+1)*(1000) = 20us
        /* The range is 128 ns to 2048 µs in four groups: 128 ns to 4. 096 µs,
         * 1 µs to 32 µs, 8 µs to 256 µs, 64 µs to 2048 µs
         * */
        uint32_t susEraseLatency = (count + 1) * unitsNs;


        /* Max latency to suspend in-progress program */
        latency = (dWord12 & INPH_XSPI_SFDP_SUSPEND_PRGM_TIME_Msk) >>
                            INPH_XSPI_SFDP_SUSPEND_PRGM_TIME_Pos;
        count = latency & INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_COUNT_Msk;
        units = (latency >> INPH_XSPI_SFDP_BFPT_TYPICAL_TIME_UNIT_Pos);
        unitsNs = 0;

        switch (units)
        {
            case INPH_XSPI_SFDP_UNIT_0:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_128NS;
                break;
            case INPH_XSPI_SFDP_UNIT_1:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_1US;
                break;
            case INPH_XSPI_SFDP_UNIT_2:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_8US;
                break;
            case INPH_XSPI_SFDP_UNIT_3:
                unitsNs = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_64US;
                break;
        }

        uint32_t susPrgmLatency = (count + 1) * unitsNs; // (4+1) * 1000 = 5us

        /* Erase Resume to Suspend Time - Time required to make progress on the
         * erase before allowing another suspend.
         * */
        count = (dWord12 & INPH_XSPI_SFDP_ERASE_RES_TO_SUS_TIME_Msk) >>
                            INPH_XSPI_SFDP_ERASE_RES_TO_SUS_TIME_Pos;
        units = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_64US;

        /* Ranage is between 64us to 1024us */
        uint32_t eraseResToSusTime = (count + 1) * units; // (7+1)*64 = 512us

        /* Program Resume to Suspend Time - Time required to make progress on the
         * erase before allowing another suspend.
         * */
        count = (dWord12 & INPH_XSPI_SFDP_PRGM_RES_TO_SUS_TIME_Msk) >>
                            INPH_XSPI_SFDP_PRGM_RES_TO_SUS_TIME_Pos;
        units = INPH_XSPI_SFDP_ERASE_SUSPEND_TIME_64US;

        /* Ranage is between 64us to 1024us */
        uint32_t prgmResToSusTime = (count + 1) * units; // (15+1)*64 = 1024us

        /* Get the time taken to suspend in-progress erase and time taken to
         * suspend in-progress program . Set the suspendTime to the greater
         * value of both.
         * */
        deviceCfg->suspendTime = (susEraseLatency > susPrgmLatency)
                                            ? susEraseLatency : susPrgmLatency;

        // TODO: check this??
        deviceCfg->resumeTime = 0; //SUS bit cleard and WIP set 10 1 eithing 200ns.
        deviceCfg->susToResTime = 0; // ??

        deviceCfg->resToSusTime = (eraseResToSusTime > prgmResToSusTime)
                                        ? eraseResToSusTime : prgmResToSusTime;
    }
}

/**
 * Gets the fast read 1S-4S-4S command and parameters from the Basic Flash
 * Parameter Table
 *
 * @param[in] readCmdParam    Structure holding the command parameter info.
 * @param[out] *readCmd       Pointer to memory command structure.
 * @return                    none.
 */
void getReadCmd_1S_4S_4S(uint16_t readCmdParam,
                         inph_stc_xspi_mem_cmd_t *readCmd)
{
    readCmd->command =
                 (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Msk) >>
                                 INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos;

    readCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

    readCmd->addrWidth = INPH_XSPI_WIDTH_QUAD;
    readCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
    readCmd->addrMask = INPH_XSPI_ADDR_MASK_BYTE;

    uint16_t modeClks=
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos;
    if (modeClks != 0)
    {
        readCmd->modeBits = modeClks;
        readCmd->modeDuration = 2U;// quad mode (2clocks-1)
        readCmd->modeWidth = INPH_XSPI_WIDTH_QUAD;
        readCmd->modePresence = INPH_XSPI_PHASE_PRESENT;
    }

    uint16_t dummyClks =
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos;
    if (dummyClks != 0)
    {
        readCmd->dummyCycles = dummyClks;
        readCmd->dummyCyclesPresence = INPH_XSPI_PHASE_PRESENT;
    }

    readCmd->dataWidth = INPH_XSPI_WIDTH_QUAD;
}

/**
 * Gets the fast read 1S-1S-4S command and parameters from the Basic Flash
 * Parameter Table
 *
 * @param[in] readCmdParam    Structure holding the command parameter info.
 * @param[out] *readCmd       Pointer to memory command structure.
 * @return                    none.
 */
void getReadCmd_1S_1S_4S(uint16_t readCmdParam,
                         inph_stc_xspi_mem_cmd_t *readCmd)
{

    readCmd->command =
             (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Msk) >>
                             INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos;
    readCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

    readCmd->addrWidth = INPH_XSPI_WIDTH_SINGLE;
    readCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
    readCmd->addrMask = INPH_XSPI_ADDR_MASK_BYTE;

    uint16_t modeClks=
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos;
    if (modeClks != 0)
    {
        readCmd->modeBits = modeClks;
        readCmd->modeDuration = 0U;
        readCmd->modeWidth = INPH_XSPI_WIDTH_SINGLE;
        readCmd->modePresence = INPH_XSPI_PHASE_SKIP;
    }

    uint16_t dummyClks =
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos;
    if (dummyClks != 0)
    {
        readCmd->dummyCycles = dummyClks;
        readCmd->dummyCyclesPresence = INPH_XSPI_PHASE_PRESENT;
    }

    readCmd->dataWidth = INPH_XSPI_WIDTH_QUAD;
}

/**
 * Gets the fast read 1S-2S-2S command and parameters from the Basic Flash
 * Parameter Table
 *
 * @param[in] readCmdParam    Structure holding the command parameter info.
 * @param[out] *readCmd       Pointer to memory command structure.
 * @return                    none.
 */
void getReadCmd_1S_2S_2S(uint16_t readCmdParam,
                         inph_stc_xspi_mem_cmd_t *readCmd)
{
    readCmd->command =
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Msk) >>
                                     INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos;
    readCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

    readCmd->addrWidth = INPH_XSPI_WIDTH_DUAL;
    readCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
     readCmd->addrMask = INPH_XSPI_ADDR_MASK_BYTE;

    uint16_t modeClks=
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos;
    if (modeClks != 0)
    {
        readCmd->modeBits = modeClks;
        readCmd->modeDuration = 0U;
        readCmd->modeWidth = INPH_XSPI_WIDTH_DUAL;
        readCmd->modePresence = INPH_XSPI_PHASE_SKIP;
    }

    uint16_t dummyClks =
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos;
    if (dummyClks != 0)
    {
        readCmd->dummyCycles = dummyClks;
        readCmd->dummyCyclesPresence = INPH_XSPI_PHASE_PRESENT;
    }

    readCmd->dataWidth = INPH_XSPI_WIDTH_DUAL;
}

/**
 * Gets the fast read 1S-1S-2S command and parameters from the Basic Flash
 * Parameter Table
 *
 * @param[in] readCmdParam    Structure holding the command parameter info.
 * @param[out] *readCmd       Pointer to memory command structure.
 * @return                    none.
 */
void getReadCmd_1S_1S_2S(uint16_t readCmdParam,
                         inph_stc_xspi_mem_cmd_t *readCmd)
{
    readCmd->command =
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Msk) >>
                                     INPH_XSPI_SFDP_BFPT_READ_PARAM_OPCODE_Pos;
    readCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

    readCmd->addrWidth = INPH_XSPI_WIDTH_SINGLE;
    readCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
     readCmd->addrMask = INPH_XSPI_ADDR_MASK_BYTE;

    uint16_t modeClks=
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_MODE_Pos;
    if (modeClks != 0)
    {
        readCmd->modeBits = modeClks;
        readCmd->modeDuration = 0U;
        readCmd->modeWidth = INPH_XSPI_WIDTH_SINGLE;
        readCmd->modePresence = INPH_XSPI_PHASE_SKIP;
    }

    uint16_t dummyClks =
                (readCmdParam & INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Msk) >>
                                INPH_XSPI_SFDP_BFPT_READ_PARAM_DUMMY_Pos;
    if (dummyClks != 0)
    {
        readCmd->dummyCycles = dummyClks;
        readCmd->dummyCyclesPresence = INPH_XSPI_PHASE_PRESENT;
    }

    readCmd->dataWidth = INPH_XSPI_WIDTH_DUAL;
}

/**
 * Sets the read 1S-1S-1S command and parameters from the Basic Flash
 * Parameter Table
 *
 * @param[out] *readCmd       Pointer to memory command structure.
 * @return                    none.
 */
void setReadCmd_1S_1S_1S(inph_stc_xspi_mem_cmd_t *readCmd)
{
    readCmd->command = INPH_XSPI_SINGLE_READ_CMD;
    readCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;

    readCmd->addrWidth = INPH_XSPI_WIDTH_SINGLE;
    readCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
    readCmd->addrMask = INPH_XSPI_ADDR_MASK_BYTE;

    readCmd->dataWidth = INPH_XSPI_WIDTH_SINGLE;
}

/**
 * Gets the fast read command and parameters from the Basic Flash
 * Parameter Table
 *
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] *readCmd       Pointer to memory command structure.
 * @param[in] maxdataWidth    Maximum data width supported by xSPI interface.
 * @return                    The supported read mode.
 */
inph_en_xspi_sfdp_read_mode_t getReadCommand(inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                    inph_stc_xspi_mem_cmd_t *readCmd,
                    inph_en_xspi_transfer_width_t maxdataWidth)
{
    bool quadEnabled = (maxdataWidth == INPH_XSPI_WIDTH_QUAD);
    uint32_t dWord1 = bfptTable->bfptParam.dWord1;
    uint32_t dWord3 = bfptTable->bfptParam.dWord3;
    uint32_t dWord4 = bfptTable->bfptParam.dWord4;
    uint32_t instrInfoSize = 16;
    uint32_t instrInfoMsk = 0xFFFF;
    uint16_t readParam;

    inph_en_xspi_sfdp_read_mode_t read_mode = READ_MODE_WRONG;

    /* We do not support DTR, so set only SDR mode */
    setMemCmdToDefault(readCmd);
    if (quadEnabled == true)
    {
       /* if (dWord1 & INPH_XSPI_SFDP_BFPT_READ_1S_4S_4S_SUPPORT_Msk >>
                    INPH_XSPI_SFDP_BFPT_READ_1S_4S_4S_SUPPORT_Pos)
        {
            readParam = (uint16_t)(dWord3 & instrInfoMsk);
            getReadCmd_1S_4S_4S(readParam, readCmd);
            read_mode = READ_MODE_1S_4S_4S;

        }
        else*/ if (dWord1 & INPH_XSPI_SFDP_BFPT_READ_1S_1S_4S_SUPPORT_Msk >>
                    INPH_XSPI_SFDP_BFPT_READ_1S_1S_4S_SUPPORT_Pos)
        {
            readParam = ((dWord3 >> instrInfoSize) & instrInfoMsk);
            getReadCmd_1S_1S_4S(readParam, readCmd);
            read_mode = READ_MODE_1S_1S_4S;
        }
        else
        {
            /* User chose quad mode, but device does not support quad mode */
            read_mode = READ_MODE_WRONG;
        }
    }

    /* Quad mode is not supported */
    if (read_mode == READ_MODE_WRONG)
    {
        /* Check if 1S-2S-2S is supported */
        if ((dWord1 & INPH_XSPI_SFDP_BFPT_READ_1S_2S_2S_SUPPORT_Msk) >>
                    INPH_XSPI_SFDP_BFPT_READ_1S_2S_2S_SUPPORT_Pos)
        {
            readParam = ((dWord4 >> instrInfoSize) & instrInfoMsk);
            getReadCmd_1S_2S_2S(readParam, readCmd);
            read_mode = READ_MODE_1S_2S_2S;
        }
        else
        {
            /* Check if dual data rate and 1S-1S-2S are both supported */
            if ((maxdataWidth >= INPH_XSPI_WIDTH_DUAL) &&
                 ((dWord1 & INPH_XSPI_SFDP_BFPT_READ_1S_1S_2S_SUPPORT_Msk) >>
                        INPH_XSPI_SFDP_BFPT_READ_1S_1S_2S_SUPPORT_Pos))
            {
                readParam = (dWord4 & instrInfoMsk);
                getReadCmd_1S_1S_2S(readParam, readCmd);
                read_mode = READ_MODE_1S_1S_2S;
            }
            else
            {
                /* Fall back read mode */
                setReadCmd_1S_1S_1S(readCmd);
                read_mode = READ_MODE_1S_1S_1S;
            }
       }
    }
    return read_mode;
}

/**
 * Sets the page program command.
 *
 * @param[out] *programCmd    Pointer to memory command structure.
 * @param[in] maxdataWidth    Maximum data width supported by xSPI interface.
 * @return                    None.
 */
void setProgramCommand(inph_stc_xspi_mem_cmd_t *programCmd,
                       inph_en_xspi_transfer_width_t maxdataWidth)
{
    setMemCmdToDefault(programCmd);
    bool quadEnabled = (maxdataWidth == INPH_XSPI_WIDTH_QUAD);

    if (quadEnabled == true)
    {
        programCmd->command = INPH_XSPI_QUAD_INPUT_PAGE_PGM_CMD;
        programCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
        programCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
        programCmd->dataWidth = INPH_XSPI_WIDTH_QUAD;
    }
    else
    {
        programCmd->command = INPH_XSPI_QUAD_INPUT_PAGE_PGM_CMD;
        programCmd->cmdPresence = INPH_XSPI_PHASE_PRESENT;
        programCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
        programCmd->dataWidth = INPH_XSPI_WIDTH_SINGLE;
    }
}

/**
 * Parses the SFDP table and gets the relevant configuration of the connected
 * memory chip and fills the memory configuration structure.
 *
 * @param[in] bfptHeader      Basic Function Parameter Table header structure.
 * @param[in] *bfptTable      Pointer to Basic Flash Parameter Table.
 * @param[out] *memCfg        Pointer to memory config. structure where the
 *                            parsed parameter information is stored.
 * @param[in] maxdataWidth    Transfer width options.
 * @param[out] qer_id         Quad enable requirement ID.
 * @return                    none.
 */
static inph_en_xspi_status_t parseSfdpTable(
                                    inph_stc_xspi_sfdp_header_t *bfptHeader,
                                    inph_stc_xspi_sfdp_bfpt_table_t *bfptTable,
                                    const inph_stc_xspi_mem_config_t *memCfg,
                                    inph_en_xspi_transfer_width_t maxdataWidth,
                                    inph_en_xspi_qer_t qer_id)
{
    /*
     * DOWRD - BFPT - DWORD1 - 4 bytes - 0-31 bits
     * 1. Uniform 4KB Sectors, Write Buffer Size, Volatile Status Register,
     *    Fast Read Supportc(1S-1S-2S) (1S-2S-2S) (1S-4S-4S)(1S-1S-4S),
     *    Number of Address Bytes, DTR Support
       2. Memory Density -DONE
       3. Fast Read (1S-4S-4S) (1S-1S-4S): Wait States, Mode Bit Clocks, Instruction
       4. Fast Read (1S-1S-2S) (1S-2S-2S): Wait States, Mode Bit Clocks, Instruction
       5. Fast Read (2S-2S-2S) (4S-4S-4S) Support
       6. Fast Read (2S-2S-2S): Wait States, Mode Bit Clocks, Instruction
       7. Fast Read (4S-4S-4S): Wait States, Mode Bit Clocks, Instruction
       8. Erase Type 1 and 2 Size and Instruction - DONE
       9. Erase Type 3 and 4 Size and Instruction - DONE
       10. Erase Type (1:4) Typical Erase Times and Multiplier Used To Derive Max Erase Times
       11. Chip Erase Typical Time, Byte Program and Page Program Typical Times, Page Size
       12. Erase/Program Suspend/Resume Support, Intervals, Latency, Keep Out Area Size - DONE
       13. Program/Erase Suspend/Resume Instructions - DONE
       14. Deep Powerdown and Status Register Polling Device Busy - SKIP
       15. Hold and WP Disable Function, Quad Enable Requirements, 4S-4S-4S Mode Enable/Disable
           Sequences, 0-4-4 Entry/Exit Methods and Support
       16. 32-bit Address Entry/Exit Methods and Support, Soft Reset and Rescue Sequences, Volatile and
        Nonvolatile Status Register Support - DONE (only soft reset)
    */

    /*
     * 1. Uniform 4KB Sectors, Write Buffer Size, Volatile Status Register,
     *    Fast Read Supportc(1S-1S-2S) (1S-2S-2S) (1S-4S-4S)(1S-1S-4S),
     *    Number of Address Bytes, DTR Support
     */
    // 1:0 Block/Sector Erase sizes
    // device support 4k erse 00 -rsvd, 01 4K yes, 2- rsvd, 3 4k no

    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    inph_stc_xspi_sfdp_erase_type_t eraseType[INPH_XSPI_SFDP_ERASE_TYPE_CNT];
    inph_stc_xspi_mem_device_cfg_t *device = memCfg->deviceCfg;

    // DWord-1
    result = getNumAddressBytes(bfptTable, &device->numOfAddrBytes);

    //DWord-2
    if (result == INPH_XSPI_SUCCESS)
    {
        result = getMemoryDensity(bfptTable, &device->memSize);
    }

    /* Get Erase command, size and time taken */
    if (result == INPH_XSPI_SUCCESS)
    {
        // TODO: confirm - erase time is not required in memCfg structure??no
        // skip write granularity, volatile SR BP bits, WE instruction to volatile SR writes
        // skip 4k erase instruction as 0x1C has all details
        // TODO: check if we need to check support of DTR, 1S-2S-2S, 1S-4S-4S, 1S-1S-4S

        /* Get erase size and command for all the 4 types of erase */
        getEraseSizeandCmd(bfptTable, eraseType);

        /* Get the corresponding erase times for the 4 types */
        getEraseTime(bfptTable, eraseType);

        /* We have parsed the sector erase commands, find a valid the erase
         * command and assign it to user structure.
         * */
        setMemCmdToDefault(device->eraseCmd);
        for (uint32_t type = 0; type < INPH_XSPI_SFDP_ERASE_TYPE_CNT; type++)
        {
            if (eraseType[type].eraseCmd != 0xFF) // supported
            {
                device->eraseCmd->command = eraseType[type].eraseCmd;
                device->eraseCmd->addrPresence = INPH_XSPI_PHASE_PRESENT;
                device->eraseSize = eraseType[type].eraseSize;
                device->eraseTime = eraseType[type].eraseTime;
                break;
            }
            else
            {
                device->eraseCmd->command = INPH_XSPI_NO_COMMAND_OR_MODE;
                device->eraseCmd->cmdWidth = INPH_XSPI_WIDTH_NA;
                device->eraseSize = 0;
                device->eraseTime = 0;
            }
        }
    }

    if (result == INPH_XSPI_SUCCESS)
    {
        /* Set write enable cmd */
        setMemCmdToDefault(device->writeEnCmd);
        device->writeEnCmd->command = INPH_XSPI_WRITE_ENABLE_CMD;

        /* Set write disable cmd */
        setMemCmdToDefault(device->writeDisCmd);
        device->writeDisCmd->command = INPH_XSPI_WRITE_DISABLE_CMD;

        /* Set busy bit mask in status register */
        device->stsRegBusyMask = INPH_XSPI_BUSY_BIT_0_OF_SR_1_Msk;

        /* Set Read Status Register1 cmd */
        setMemCmdToDefault(device->readStsRegWipCmd);
        device->readStsRegWipCmd->command  = INPH_XSPI_READ_STATUS_REG1_CMD;

        /* Get QUAD parameters */
        if (maxdataWidth == INPH_XSPI_WIDTH_QUAD)
        {
            // TODO: there is also a 38H when minor version is not 0??
            getQuadEnableParameters(bfptTable, device, qer_id);
        }

        /* Gte page size */
        getPageSize(bfptHeader->parameter_hdr, bfptTable, &device->programSize);

        /* Get page program time */
        getPageProgramTime(bfptTable, &device->programTime);

        /* Set Chip Erase cmd */
        setMemCmdToDefault(device->chipEraseCmd);
        device->chipEraseCmd->command = INPH_XSPI_CHIP_ERASE_CMD;

        /* Get Chip Erase time */
        getChipEraseTime(bfptTable, &device->chipEraseTime);

        /* DW16 - skip 4-byte addressing mode, but get the soft reset and
         * reset enable details
         * */
        getResetCmd(bfptTable, device);

        /* DW12 - Suspend/Resume Support
         * DW13 - Suspend/Resume instructions
         * */
        getSusResCmd(bfptTable, device);

        /* Sets the page program command */
        setProgramCommand(device->programCmd, maxdataWidth);

        /* Get read commands */
        getReadCommand(bfptTable, device->readCmd, maxdataWidth);
    }

    return result;
}

/**
 * This function reads the SFDP parameters from the flash device, parses the
 * SFDP table, gets the instructions for the chosen data width from the table,
 * and fills the user provided memory configuration structure with the info.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[out] *memCfg       Pointer to memory config. structure where the
 *                           parsed parameter information is stored.
 * @param[in] maxdataWidth   Maximum data width supported by xSPI interface.
 * @param[out] qer_id        Quad enable requirement ID.
 * @param[in] *context       Pointer to the context structure
 * @return                   Status.
 */
inph_en_xspi_status_t Inph_XSPI_MemInitSfdpMode(XSPI_Type *base,
                                    const inph_stc_xspi_mem_config_t *memCfg,
                                    inph_en_xspi_transfer_width_t maxdataWidth,
                                    inph_en_xspi_qer_t qer_id,
                                    inph_stc_xspi_context_t const *context)
{
    INPH_ASSERT(NULL != memCfg);
    INPH_ASSERT(NULL != memCfg->deviceCfg);

    volatile uint32_t sfdpBufferSize = sizeof(inph_stc_xspi_sfdp_header_t) +
                                     sizeof(inph_stc_xspi_sfdp_parameter_hdr_t);
    uint8_t sfdpBuffer[sfdpBufferSize];
    uint8_t sfdpAddress[3];
    inph_stc_xspi_sfdp_header_t *header = (inph_stc_xspi_sfdp_header_t*) sfdpBuffer;
    inph_en_xspi_status_t result = INPH_XSPI_NO_SFDP_SUPPORT;
    inph_stc_xspi_mem_device_cfg_t *device = memCfg->deviceCfg;

    for (uint8_t i = 0U; i < 3; i++)
    {
        sfdpAddress[i] = 0U;
    }

    if (device->readSfdpCmd != NULL)
    {
        /* Read sfdp header and basic parameter header defined by JEDEC */
        result = sfdpReadBuffer(base, device->readSfdpCmd, sfdpAddress,
                                memCfg->chipSelect, sfdpBufferSize, sfdpBuffer,
                                context);
    }
    else
    {
        result = INPH_XSPI_NO_SFDP_SUPPORT;
    }

    if (result == INPH_XSPI_SUCCESS)
    {
        /* Check if SFDP header validity wuch that it is backward compatible
         * with JESD216B
         * */
        /* majorRev - 01h for devices which implement the JESD216F revision
         * (unchanged from JESD216D revision). Major rev change indicate that
         * the table structure has changed and may not be backwards compatible
         * with software written for an earlier revision of SFDP. Let's stick
         * with revision 1 as we need backward compatibility.
         * acessProtocol - FFh still indicates that the SFDP command structure
         * is backwards compatible with the description given in JESD216B.
         * The device will in this case respond to one or more of the SFDP
         * command options as described in JESD216B. Any other value indicates
         * that the SFDP command will behave differently in one or more aspects
         * numParamHeader - should have atleast the basic parameter table
         */
        if ((header->signature == INPH_XSPI_SFDP_SIGNATURE) &&
            (header->majorRev == 1) && (header->acessProtocol == 0xFF) &&
            ((header->numParamHeader + 1) > 0))
        {
            // 2. verify if the first header is basic flash paramater header defined bye jedec
            // 2a. basic parameter table ID should be equal to 0
            // 2b. basic parmater header major revision should be 1
            /* The Parameter ID LSB value of 00h is reserved for the SPI Basic
             * Parameter Table defined by this standard. For backwards
             * compatibility the MSB is FFh when the LSB is 00h and LSB 00h
             * shall not be used when the MSB is any value other than FFh.
            */
            if ((header->parameter_hdr->idLsb == 0x00) &&
                (header->parameter_hdr->idMsb == 0xFF) &&
                (header->parameter_hdr->majorRev == 1))
            {
                /* We do not support octal flash, hence only one JEDEC defined
                 * basic parameter table will be present and the length will not
                 * exceed 16 words. If octal mode is supported the 17th DWord
                 * will have octal commands.
                 */
                if (header->parameter_hdr->paramLen >
                                INPH_XSPI_SFDP_BASIC_PARAM_TABLE_LEN)
               {
                   result = INPH_XSPI_NO_SFDP_SUPPORT;
               }
            }

            if (result == INPH_XSPI_SUCCESS)
            {
                /* Now read the parameter table */
                sfdpAddress[2] = header->parameter_hdr->paramTablePtr[0];
                sfdpAddress[1] = header->parameter_hdr->paramTablePtr[1];
                sfdpAddress[0] = header->parameter_hdr->paramTablePtr[2];

                uint32_t paramTableLen =
                            header->parameter_hdr->paramLen * sizeof(uint32_t);

                if (paramTableLen > 0U)
                {
                    uint8_t bfptBuffer[paramTableLen];

                    /* Initialize the BFPT buffer */
                    for (uint32_t i = 0U; i < paramTableLen; i++)
                    {
                        bfptBuffer[i] = 0U;
                    }

                    inph_stc_xspi_sfdp_bfpt_table_t *bfptTable = (inph_stc_xspi_sfdp_bfpt_table_t *)bfptBuffer;

                    /* Read the parameter table */
                    result = sfdpReadBuffer(base, device->readSfdpCmd, sfdpAddress,
                                            memCfg->chipSelect, paramTableLen,
                                            (uint8_t*)bfptTable->bfptDWords,
                                            context);
                    if (result == INPH_XSPI_SUCCESS)
                    {
                        result = parseSfdpTable(header, bfptTable, memCfg, maxdataWidth, qer_id);
                    }
                }
                else
                {
                    result = INPH_XSPI_NO_SFDP_SUPPORT;
                }
            }
        }
        else
        {
            result = INPH_XSPI_NO_SFDP_SUPPORT;
        }


    }

    return result;
}

/**
 * This function queries the external device for parameters, parses and
 * populates the relevant memory structure @ref inph_stc_xspi_mem_device_cfg_t
 * with the data obtained from the memory device.
 * Refer to SFDP spec (JESD216B) for details.
 *
 * @note This function uses low-level @ref Inph_XSPI_TransmitCommand_Ext()
 * API which works in a blocking mode. If the device does not support SFDP
 * it returns and error.
 * @pre - XSPI should be initialized and enabled to work in SPI mode, the
 * readSfdpCmd field in @ref inph_stc_xspi_mem_device_cfg_t should be filled.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *device        Pointer to the memory device config structure.
 * @param[in] chipSelect     The chip select line for connected memory device.
 * @param[in] *context       Pointer to the context structure that holds the
 *                           transfer parameters.
 * @return                   Memory slot initialization status which can be
 *                           INPH_XSPI_SUCCESS or INPH_XSPI_NO_SFDP_SUPPORT.
 */
inph_en_xspi_status_t Inph_XSPI_MemSfdpDetect(XSPI_Type *base,
                                    inph_stc_xspi_mem_device_cfg_t *device,
                                    inph_en_xspi_chip_select_t chipSelect,
                                    inph_stc_xspi_context_t *context)
{
    INPH_ASSERT(NULL != device);

    inph_stc_xspi_mem_config_t memSfdpDetect =
    {
        .chipSelect = chipSelect,
        .flags = 0,
        .baseAddress = 0U,
        .memMappedSize = 0U,
        .dualQuadSlots = 0,
        .deviceCfg = device,
    };

    return Inph_XSPI_MemInitSfdpMode(base, &memSfdpDetect, INPH_XSPI_WIDTH_QUAD, INPH_XSPI_SFDP_QER_0, context);

}

#if defined(__cplusplus)
}
#endif
