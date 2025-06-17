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
 * @file    inph_xspi_memslot.h
 * @author  Innophase Firmware Team
 * @brief   Provides memory slot level APIs for xSPI driver
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INPH_XSPI_MEMORYSLOT_H
#define INPH_XSPI_MEMORYSLOT_H

#if defined(__cplusplus)
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "inph_assert.h"
#include "inph_xspi.h"

/* Exported macro ------------------------------------------------------------*/

/** @addtogroup group_xspi_macros_status
 * @{
 */

#define INPH_XSPI_DEVICE_BUSY  (1U) /**< The external memory is busy */
#define INPH_XSPI_DEVICE_READY (0U) /**< The external memory is ready */

/**
 * @} group_xspi_macros_status
 */

/** @addtogroup group_xspi_macros_cmd
 * @{
 */

/* Indicates if is the last byte in the command transmission */
/* Command without parameter and parameter width */
#define INPH_XSPI_CMD_NO_PARAM (0U) /**< No parameter */
#define INPH_XSPI_TX_LAST_BYTE               (1U) /**< The last byte in the
              * command transmission (CS is set high after the transmission) */
#define INPH_XSPI_TX_NOT_LAST_BYTE           (0U) /**< Not the last byte in the
              * command transmission (CS remains low after the transmission) */
#define INPH_XSPI_READ_ONE_BYTE              (1U) /**< Read 1 byte */
#define INPH_XSPI_WRITE_ONE_BYTE             (1U) /**< Write 1 byte */
#define INPH_XSPI_WRITE_TWO_BYTES            (2U) /**< Write 2 bytes */
#define INPH_XSPI_ONE_WORD                   (4U) /**< 4 bytes */

#define INPH_XSPI_QE_BIT_1_OF_SR_2           (0x02UL) /**< The QE is bit 1 of the SR 2 */
#define INPH_XSPI_QE_BIT_6_OF_SR_1           (0x40UL) /**< The QE is bit 6 of the SR 1 */
#define INPH_XSPI_QE_BIT_7_OF_SR_2           (0x80UL) /**< The QE is bit 7 of the SR 2 */

#define INPH_XSPI_WRSR_REG1_CMD              (0x01U) /**< The write status register 1 */
#define INPH_XSPI_WRSR_REG2_CMD              (0x31U) /**< The write status register 2 */

/**
 * @} group_xspi_macros_cmd
 */

/** \cond INTERNAL */
/* This address must be a multiple of XSPI XIP memory size */
#define INPH_XSPI_MEM_ADDR_VALID(addr, size) (0U == ((addr) % (size)))
/* Size should be a power of 2 */
#define INPH_XSPI_MEM_MAPPED_SIZE_VALID(size)                                  \
    (((size) >= 0x10000U) && (0U == ((size) & ((size) - 1U))))
#define INPH_XSPI_MEM_ADDR_SIZE_VALID(addrSize)                                \
    ((0U < (addrSize)) && ((addrSize) <= INPH_XSPI_THREE_BYTES_ADDR))
/** \endcond */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup group_xspi_macros_flags
 * @{
 */

#define INPH_XSPI_FLAG_ALL_DISABLED     (0U) /**< All memory configuration flags are disabled */

#define INPH_XSPI_FLAG_WRITE_ENABLE     (1U) /**< Enables the SPI/command based
                                 * write capability for the memory slave in the
          * memory-mapped mode. Valid when the memory-mapped mode is enabled */


#define INPH_XSPI_FLAG_MEMORY_MAPPED    (2U) /**< Determines if the device is
* memory-mapped. If enabled, this memory slot will be initialized in System init */

#define INPH_XSPI_FLAG_DETECT_SFDP      (4U) /**< Enables the Autodetect using
                                              * the SFDP */

#define INPH_XSPI_FLAG_AIP_WRITE_ENABLE (8U) /**< Enables AIP write capability for the memory slave like PSRAM in the
 * memory-mapped mode. Valid when the memory-mapped mode is enabled */


/**
 * @} group_xspi_macros_flags
 */

/** \cond INTERNAL */
/* Address is 3-byte */
#define INPH_XSPI_THREE_BYTES_ADDR      (03U)

/* Maximum bytes to read */
#define INPH_XSPI_MAX_RX_COUNT          (65536UL)

/**< Max suspend time is 20 micro seconds */
#define INPH_XSPI_SUSPEND_TIME_MAX      (1U)
/**< Max suspend time is 30 micro seconds */
#define INPH_XSPI_RESUME_TIME_MAX       (1U)

#define INPH_XSPI_NO_OF_DEVICE          (1U)
/** \endcond */


/* SFDP macros */
#define INPH_XSPI_NO_COMMAND_OR_MODE (0xFFFFFFFFUL) /**< No cmd or mode present */


#define INPH_XSPI_READ_STATUS_REG1_CMD                                         \
    (0x05U) /**< Read Status Register-1 command */
#define INPH_XSPI_WRITE_STATUS_REG1_CMD                                        \
    (0x01U) /**< Write Status Register-1 command */
#define INPH_XSPI_READ_STATUS_REG2_CMD                                         \
    (0x35U) /**< Read Status Register-2 command */
#define INPH_XSPI_WRITE_STATUS_REG2_CMD                                        \
    (0x31U) /**< Write Status Register-2 command */
#define INPH_XSPI_READ_STATUS_REG3_CMD                                         \
    (0x15U) /**< Read Status Register-3 command */
#define INPH_XSPI_WRITE_STATUS_REG3_CMD                                        \
    (0x11U) /**< Write Status Register-3 command */
#define INPH_XSPI_WRITE_STATUS_REG1_REG2_CMD                                   \
    (0x01U) /**< Write Status Register 1&2 command */
#define INPH_XSPI_BUSY_BIT_0_OF_SR_1_Msk                                       \
    (0x01U) /**< The BUSY/WIP is bit 0 of the status register 1 mask */
#define INPH_XSPI_BUSY_BIT_0_OF_SR_1_Pos                                       \
    (0x00U) /**< The BUSY/WIP is bit 0 of the status register 1 position */


#define INPH_XSPI_RESET_ENABLE_CMD        (0x66U) /**< Reset Enable command */
#define INPH_XSPI_RESET_CMD               (0x99U) /**< Reset command */
#define INPH_XSPI_SINGLE_READ_CMD         (0x03U) /**< Read data command */
#define INPH_XSPI_WRITE_ENABLE_CMD        (0x06U) /**< Write Enable command */
#define INPH_XSPI_WRITE_DISABLE_CMD       (0x04U) /**< Write Disable command */
#define INPH_XSPI_CHIP_ERASE_CMD          (0xC7U) /**< Chip Erase command */
#define INPH_XSPI_PAGE_PGM_CMD            (0x02U) /**< page program command */
#define INPH_XSPI_QUAD_INPUT_PAGE_PGM_CMD (0x32U) /**< Quad Input page Program command */


/* Exported typedef ----------------------------------------------------------*/

/** @addtogroup group_xspi_enums
 * @{
 */

/** Specifies the the XIP device address width field */
typedef enum {
    INPH_XSPI_XIP_ADDR_WIDTH_24BITS = 0, /**< 24-bit addr width */
    INPH_XSPI_XIP_ADDR_WIDTH_32BITS = 1, /**< 32-bit addr width */
    INPH_XSPI_XIP_ADDR_WIDTH_16BITS = 2, /**< 16-bit addr width */
    INPH_XSPI_XIP_ADDR_WIDTH_8BITS = 3,  /**< 8-bit addr width */
} inph_en_xspi_xip_addr_width_t;

/**
 * @} group_inph_xspi_enums
 */

/** @addtogroup group_xspi_data_structures_memslot
 * @{
 */

/** This command structure is used to store the Read/Write command
 * configuration. */
typedef struct {
    uint32_t command; /**< The 8-bit command */
    inph_en_xspi_transfer_width_t
        cmdWidth;                     /**< The width of the command transfer */
    inph_en_xspi_data_rate_t cmdRate; /**< The Data rate of command */
    inph_en_xspi_phase_presence_t
        cmdPresence; /**< This specifies the presence of the command phase */

    inph_en_xspi_transfer_width_t
        addrWidth;                     /**< The width of the address transfer */
    inph_en_xspi_data_rate_t addrRate; /**< The Data rate of address */
    inph_en_xspi_phase_presence_t
        addrPresence; /**< This specifies the presence of the address phase */
    inph_en_xspi_address_mask_t
        addrMask; /**< Address type, byte, half-word, word */

    uint32_t modeBits;     /**< The 8-bit mode byte */
    uint32_t modeDuration; /**< The length of mode phase */
    inph_en_xspi_transfer_width_t
        modeWidth;                     /**< The width of the mode transfer */
    inph_en_xspi_data_rate_t modeRate; /**< The Data rate of mode */
    inph_en_xspi_phase_presence_t
        modePresence; /**< This specifies the presence of the mode field */

    uint32_t dummyCycles; /**< The number of the dummy cycles. A zero value
                             suggests no dummy cycles */
    inph_en_xspi_phase_presence_t
        dummyCyclesPresence; /**< This specifies the presence of the dummy field
                              */

    inph_en_xspi_transfer_width_t
        dataWidth;                     /**< The width of the data transfer */
    inph_en_xspi_data_rate_t dataRate; /**< The Data rate of data */


    uint32_t modeH; /**< The 8-bit command. This value is 0x0 when there is no
                       higher byte mode present */
    uint32_t commandH; /**< The 8-bit command. This value is 0x0 when there is
                          no higher byte command present */

} inph_stc_xspi_mem_cmd_t;

/**
 *
 * This configuration structure of the XSPI memory device is used to store
 * device-specific parameters.
 * These parameters are used to set up the memory mode initialization and the
 * memory API.
 */
typedef struct {
    uint32_t
        numOfAddrBytes; /**< This specifies the number of address bytes
                         * used by the memory slave device, valid values 1-4 */
    uint32_t memSize; /**< The memory size: For densities of 2 gigabits or less
                       * - the size in bytes; For densities 4 gigabits and above
                       * - bit-31 is set to 1b to define that this memory is 4
                       * gigabits and above; and other 30:0 bits define N where
                       * the density is computed as 2^N bytes. For example,
                       * 0x80000021 corresponds to 2^30 = 1 gigabyte.
                       */
    inph_stc_xspi_mem_cmd_t *readCmd; /**< This specifies the Read command */
    bool pageReadBoundary; /**< This specifies if external devce has read size
                            * limitations. For example, page reads for NAND
                            * flash, no limitations for NOR flash,some PSRAM
                            * devices have boundary limitations too
                            * */
    inph_stc_xspi_mem_cmd_t
        *suspendCmd; /**< This specifies the Suspend command */
    inph_stc_xspi_mem_cmd_t
        *resumeCmd; /**< This specifies the Resume command */
    inph_stc_xspi_mem_cmd_t
        *writeEnCmd; /**< This specifies the Write Enable command */
    inph_stc_xspi_mem_cmd_t
        *writeDisCmd; /**< This specifies the Write Disable command */
    inph_stc_xspi_mem_cmd_t *eraseCmd; /**< This specifies the Erase command */
    uint32_t eraseSize; /**< This specifies the sector size of each Erase */
    inph_stc_xspi_mem_cmd_t
        *chipEraseCmd; /**< This specifies the Chip Erase command */
    inph_stc_xspi_mem_cmd_t
        *programCmd;      /**< This specifies the Program command */
    uint32_t programSize; /**< This specifies the page size for programming */
    inph_stc_xspi_mem_cmd_t
        *readStsRegWipCmd; /**< This specifies the command to read the
                              WIP-containing status register  */
    inph_stc_xspi_mem_cmd_t
        *readStsRegQeCmd; /**< This specifies the command to read the
                             QE-containing status register */
    inph_stc_xspi_mem_cmd_t
        *writeStsRegQeCmd; /**< This specifies the command to write into the
                              QE-containing status register */
    inph_stc_xspi_mem_cmd_t
        *readSfdpCmd; /**< This specifies the read SFDP command */
    inph_stc_xspi_mem_cmd_t
        *quadEnterCmd; /**< This specifies the Enter Quad Mode command */
    inph_stc_xspi_mem_cmd_t
        *quadExitCmd; /**< This specifies the Exit Quad Mode command */
    inph_stc_xspi_mem_cmd_t
        *resetEnCmd; /**< This specifies the Reset Enable command */
    inph_stc_xspi_mem_cmd_t *resetCmd; /**< This specifies the Reset command */

    uint32_t stsRegBusyMask; /**< The Busy mask for the status registers */
    uint32_t stsRegQuadEnableMask; /**< The QE mask for the status registers */
    uint32_t eraseTime;     /**< Max time for erase type 1 cycle time in ms */
    uint32_t chipEraseTime; /**< Max time for chip erase cycle time in ms */
    uint32_t programTime;   /**< Max time for page program cycle time in us */

    bool susResSupport; /**< This specifies if suspend/resume cmds are supported */
    uint32_t suspendTime; /**< Time taken to suspend a program/erase operation
    (Max time taken between CS going high to next cmd after Suspend) */
    uint32_t resumeTime; /**< Max time for chip erase cycle time in ms */
    uint32_t susToResTime;
    uint32_t resToSusTime; /**< Latency between Resume and next Suspend */

} inph_stc_xspi_mem_device_cfg_t;

/**
 *
 * This xSPI memory configuration structure is used to store the memory
 * configuration for the memory mode of operation.This data structure is
 * required for the initialization of the xSPI MC.
 */
typedef struct {
    /* Determines the chip select where the memory device is placed */
    inph_en_xspi_chip_select_t chipSelect;

    /* Determines if the device is memory-mapped, write enabled, SFDP etc */
    uint32_t flags;

    /* The data-line selection options for a slave device */
    inph_en_xspi_data_select_t dataSelect;

    /* The base address the memory slave is mapped to in memory map, which will
     * be the window address as given on the AHB/AXI interface. The window
     * address should be set to multiples of window size. For example, if the
     * New AIP Size register is set to 17 (128KB window), the window base
     * address is set to any multiple of 128KB, e.g. 128KB, 256KB, 384KB, etc.
     * */
    uint32_t baseAddress;

    /* The size allocated in the memory map for the memory slave, which is the
     * size of this AIP window. The capacity is allocated from the base address.
     * The size must a power of two.
     * */
    uint32_t memMappedSize;

    /* Is the memory device in the dual quad SPI configuration. */
    uint32_t dualQuadSlots;

    /* The configuration of the device */
    inph_stc_xspi_mem_device_cfg_t *deviceCfg;
} inph_stc_xspi_mem_config_t;

/**
 *
 * This XSPI memory configuration structure is used to store the memory
 * configuration for the memory mode of operation. This data structure is stored
 * in a fixed location in the flash. The data structure is required for the
 * initialization of the XSPI in the SystemInit.
 */
typedef struct {
    uint32_t memCount; /**< The number of XSPI memory defined  */
    inph_stc_xspi_mem_config_t *
        *memConfig; /**< The pointer to the array of the memory configuration
                       structures of size Memory_count */
    uint32_t majorVersion; /**< The version of the XSPI driver */
    uint32_t minorVersion; /**< The version of the XSPI Driver */
} inph_stc_xspi_block_config_t;

/**
 * @} group_xspi_data_structures_memslot
 */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup group_xspi_mem_slot_functions
 * @{
 */

/**
 * Initialize the XSPI memory device. This function should be caled when the
 * memory device is required to be used in XIP mode. This function performs
 * SFDP on the external memories connected. This function configures
 * the XSPI device slot registers with the with the configuration from
 * @ref inph_stc_xspi_mem_config_t structure which is a member of
 * @ref inph_stc_xspi_block_config_t structure.
 *
 * @ref Inph_XSPI_Init should be called before calling this function. The
 * @ref inph_stc_xspi_context_t returned by the Inph_XSPI_Init is passed as a
 * parameter to this function.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *blockConfig   Pointer to the memory device config structure.
 * @param[in] *context       Pointer to the context structure that holds the
 *                           transfer parameters.
 * @return                   Memory slot initialization status which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_NO_SFDP_SUPPORT
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_SFDP_ADDRMODE_UNSUPPORTED or
 *                           @ref INPH_XSPI_SFDP_MEMSIZE_UNSUPPORTED or
 *                           @ref INPH_XSPI_SFDP_4K_ERASE_UNSUPPORTED.
 */
inph_en_xspi_status_t
Inph_XSPI_MemInit(XSPI_Type *base,
                  inph_stc_xspi_block_config_t const *blockConfig,
                  inph_stc_xspi_context_t *context);

/**
 * De-initialize the XSPI memory device slots to it's default values.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @return                   None.
 */
void Inph_XSPI_MemDeInit(XSPI_Type *base);

/**
 * This function sends Write Enable command to the memory device.
 * This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which works
 * in a blocking mode. If the read status command is available, this functions
 * will read the status register to verify if the WEL bit is set.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Pointer to the memory configuration structure.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status which can be @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS.
 */
inph_en_xspi_status_t
Inph_XSPI_MemCmdWriteEnable(XSPI_Type *base,
                            inph_stc_xspi_mem_config_t const *memConfig,
                            inph_stc_xspi_context_t const *context);

/**
 * This function sends Write Disable command to the memory device.
 * This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which works
 * in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status which can be @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemCmdWriteDisable(XSPI_Type *base,
                             inph_stc_xspi_mem_config_t const *memConfig,
                             inph_stc_xspi_context_t const *context);

/**
 * This function checks if the memory device is busy executing a page progam or
 * erase or write status register commands. When the device is busy it ignores
 * any commands except read status register or suspend command. This function
 * is a blocking function until the status register from the memory is read.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Return True if busy and False if not busy.
 */
bool Inph_XSPI_MemIsBusy(XSPI_Type *base,
                         inph_stc_xspi_mem_config_t const *memConfig,
                         inph_stc_xspi_context_t const *context);

/**
 * This function sets the quad enable bit in the stauts register to let the
 * memory device operate in quad mode. The QE bit is non-volatile read/write
 * bit which is set to 0 as factory default. This command must be executed
 * before sending quad SPI commands to the memory device. This function
 * will read the status register to verify if the QE bit is set.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemQuadEnable(XSPI_Type *base,
                        inph_stc_xspi_mem_config_t const *memConfig,
                        inph_stc_xspi_context_t const *context);

/**
 * This function reads the status register. This function is a blocking
 * function, it will block until the status register is read. This function can
 * be used anytime, even while in Program, Erase or Write Status Register
 * operations are in progress.
 *
 * @note This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which
 * works in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] status         Holds the status value read from the memory device.
 * @param[in] command        Holds the read status command.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t Inph_XSPI_MemCmdReadStatus(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint8_t *status, uint8_t command, inph_stc_xspi_context_t const *context);

/**
 * This function writes to the status register. Before writing into a
 * non-volatile status register bits, a write enable command will be executed.
 * While write status register is in progress, the read status register command
 * can still be executed to check the status of busy bit. Once the write is
 * complete the busy bit will be cleared and the Write Enable Latch(WEL) bit
 * will be cleared. This function is a blocking function, it will block until
 * the cmd is transmitted.
 *
 * @note This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which
 * works in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] status         Holds the status value to be written.
 * @param[in] command        Holds the write status command.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS.
 */
inph_en_xspi_status_t
Inph_XSPI_MemCmdWriteStatus(XSPI_Type *base,
                            inph_stc_xspi_mem_config_t const *memConfig,
                            void const *status, uint8_t command,
                            inph_stc_xspi_context_t const *context);

/**
 * This function erases the entire chip memory (erase state is all 1s).
 * A write enable command will be executed before sending a chip erase command.
 * While chip erase is in progress, a read status register instruction can be
 * send to check the status of busy bit. Once the erase is complete the busy
 * bit will be cleared and the Write Enable Latch(WEL) bit will be cleared.
 * This function is a blocking function.
 * NOTE: Chip erase will not be executed if the memory region is protected by
 * Block Protect.
 *
 * @note This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which
 * works in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS.
 */
inph_en_xspi_status_t
Inph_XSPI_MemCmdChipErase(XSPI_Type *base,
                          inph_stc_xspi_mem_config_t const *memConfig,
                          inph_stc_xspi_context_t const *context);

/**
 * This function performs block erase (erase state is all 1s). A write enable
 * command will be executed before sending a block erase command.
 * While block erase is in progress, a read status register instruction can be
 * send to check the status of busy bit. Once the erase is complete the busy
 * bit will be cleared and the Write Enable Latch(WEL) bit will be cleared.
 * This function is a blocking function.
 * NOTE: Block erase will not be executed if the addressed page is protected by
 * Block Protect bits.
 *
 * @note This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which
 * works in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] sectorAddr     Holds the sector erase to be erased.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS.
 */
inph_en_xspi_status_t Inph_XSPI_MemCmdSectorErase(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint8_t const *sectorAddr, inph_stc_xspi_context_t const *context);

/**
 * This function performs page program operation at a previously erased
 * memory location. If QUAD page program is to be performed then the Quad
 * Enable bit in status register must be enabled. A write enable command will
 * be executed before sending page program command. While page program is in
 * progress, the read status register command can still be executed to check
 * the status of busy bit. Once page program is complete the busy bit will be
 * cleared and the Write Enable Latch(WEL) bit will be cleared. The Page
 * program will not be executed if the addressed page is protected by
 * Block Protect bits.
 *
 * @note This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which
 * works in a blocking mode and Inph_XSPI_TransmitData_Ext to write in
 * non-blocking mode, which uses interrupts to transfer.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] *prgmAddr      memory address to be programmed.
 * @param[in] *writeBuff     pointer to buffer holding data to be programmed.
 * @param[in] size           size of the data to be programmed.
 * @param[in] cmdCompleteCb  the callback function to be called once the
 *                           programming is complete.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_FIFO_FULL.
 */
inph_en_xspi_status_t Inph_XSPI_MemCmdProgram(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint8_t const *addr, uint8_t const *writeBuff, uint32_t size,
    inph_xspi_event_cb_t cmdCompleteCb, inph_stc_xspi_context_t *context);

/**
 * This function performs the read operation. For QUAD read, the Quad Enable
 * bit in status register must be enabled. If a read data instruction is issued
 * when a program or erase cycle is in progress, the instruction will be
 * ignored.
 *
 * @note This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which
 * works in a blocking mode and Inph_XSPI_ReceiveData_Ext in non-blocking mode,
 * which uses interrupts to read from FIFO.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Device to which command is sent.
 * @param[in] *readAddr      memory address to be read from.
 * @param[in] *readBuff      pointer to buffer where the read data will be
 *                           stored.
 * @param[in] size           size of the data to be read.
 * @param[in] cmdCompleteCb  the callback function to be called once the
 *                           read is complete.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS.
 */
inph_en_xspi_status_t Inph_XSPI_MemCmdRead(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint8_t const *addr, uint8_t *readBuff, uint32_t size,
    inph_xspi_event_cb_t cmdCompleteCb, inph_stc_xspi_context_t *context);


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
 * @param[in] *context       Pointer to the context structure that holds the
 *                           transfer parameters.
 * @param[in] chipSelect     The chip select line for connected memory device.
 * @param[in] *context       Pointer to the context structure that holds the
 *                           transfer parameters.
 * @return                   Memory slot initialization status which can be
 *                           INPH_XSPI_SUCCESS or INPH_XSPI_NO_SFDP_SUPPORT.
 */
inph_en_xspi_status_t Inph_XSPI_MemSfdpDetect(XSPI_Type *base,
                                    inph_stc_xspi_mem_device_cfg_t *device,
                                    inph_en_xspi_chip_select_t chipSelect,
                                    inph_stc_xspi_context_t *context);

/**
 * This function sets the polling delay in micro seconds.
 *
 * @param[in] pollTimeoutUs  Holds the timeout polling value in micro seconds.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   None.
 */
void Inph_XSPI_SetReadyPollingDelay(uint16_t pollTimeoutUs,
                                    inph_stc_xspi_context_t *context);

/**
 * This function polls the memory device to check whether it has completed the
 * current operation and is ready to accept new commands. It polls until the
 * device is ready or the timeout expires, whichever is earlier. This is a
 * blocking function, it will block the execution flow until the command
 * transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory configuration of the conencted device.
 * @param[in] timeoutUs      Timeout value in microseconds.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t Inph_XSPI_MemIsReady(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint32_t timeoutUs, inph_stc_xspi_context_t const *context);

/**
 * This function checks if the Quad Enable(QE) bit is set in status register.
 * This is a blocking function, it will block the execution flow until
 * the command transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory configuration of the conencted device.
 * @param[in] *isQuadEnabled This holds the status of QE bit, if enabled, set
 *                           to true, if disabled, set to false.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t Inph_XSPI_MemIsQuadEnabled(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    bool *isQuadEnabled, inph_stc_xspi_context_t const *context);

/**
 * This function sets the Quad Enable(QE) bit in the external memory
 * status register to enable QUAD SPI mode.
 * This is a blocking function, it will block the execution flow until
 * the command transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory configuration of the conencted device.
 * @param[in] timeoutUs      Timeout value in microseconds to apply while
 *                           polling the memory.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t Inph_XSPI_MemEnableQuadMode(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint32_t timeoutUs, inph_stc_xspi_context_t const *context);

/**
 * This function reads from external memory until read transfer is complete or
 * a timeout occurs.
 * This is a blocking function, it will block the execution flow until the
 * command transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory device configuration.
 * @param[in] *readAddr      memory address to be read from.
 * @param[in] *rxBuffer      pointer to buffer where the read data will be
 *                           stored.
 * @param[in] length         size of the data to be read.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemRead(XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
                  uint32_t readAddr, uint8_t rxBuffer[], uint32_t length,
                  inph_stc_xspi_context_t const *context);

/**
 * This function writes data to the external memory.
 * This is a blocking function, it will block the execution flow until the
 * command transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory device configuration.
 * @param[in] *writeAddr     memory address to be written to.
 * @param[in] *txBuffer      Pointer to buffer holding data to be written into
 *                           the external memory.
 * @param[in] length         size of the data to be written.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_FIFO_FULL or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemWrite(XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
                   uint32_t writeAddr, uint8_t const txBuffer[],
                   uint32_t length, inph_stc_xspi_context_t const *context);

/**
 * This function erases blocks or sector of external memory.
 * This is a blocking function, it will block the execution flow until the
 * command transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory device configuration.
 * @param[in] *eraseAddr     memory address of the block to be erased.
 * @param[in] length         length data to be erased.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemEraseSector(XSPI_Type *base,
                         inph_stc_xspi_mem_config_t const *memConfig,
                         uint32_t eraseAddr, uint32_t length,
                         inph_stc_xspi_context_t const *context);

/**
 * This function erases entire chip. This is a blocking function.
 * This is a blocking function, it will block the execution flow until the
 * command transmission is completed.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memConfig     Memory device configuration.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status of the operation which can be
 *                           @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_INVALID_PARAMETER or
 *                           @ref INPH_XSPI_OPERATION_INPROGRESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemEraseChip(XSPI_Type *base,
                       inph_stc_xspi_mem_config_t const *memConfig,
                       inph_stc_xspi_context_t const *context);

/**
 * This function sends Reset Enable command to the memory device, followed by
 * a reset command. This command puts the device in SPI standby mode which is
 * the default mode after power up.
 *
 * This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which works
 * in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Pointer to the memory configuration structure.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status which can be @ref INPH_XSPI_SUCCESS or
 *                           @ref INPH_XSPI_ERROR_TIMEOUT.
 */
inph_en_xspi_status_t
Inph_XSPI_MemReset(XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
                   inph_stc_xspi_context_t const *context);

/**
 * This function sends Enter Quad Mode Command to the PSRAM.
 * This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which works
 * in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Pointer to the memory configuration structure.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status
 */
inph_en_xspi_status_t
Inph_XSPI_MemEnterQuadMode(XSPI_Type *base,
                           inph_stc_xspi_mem_config_t const *memConfig,
                           inph_stc_xspi_context_t const *context);

/**
 * This function sends Exit Quad Mode Command to the PSRAM.
 * This function uses low-level Inph_XSPI_TransmitCommand_Ext() API which works
 * in a blocking mode.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @param[in] *memDevice     Pointer to the memory configuration structure.
 * @param[in] *context       Pointer to the context structure
 *                           @ref inph_stc_xspi_context_t allocated by the user.
 *                           The structure is used during the XSPI operation for
 *                           internal configuration and transfers. The user
 *                           must not modify anything in this structure.
 * @return                   Status
 */
inph_en_xspi_status_t
Inph_XSPI_MemExitQuadMode(XSPI_Type *base,
                          inph_stc_xspi_mem_config_t const *memConfig,
                          inph_stc_xspi_context_t const *context);

/**
 * @} group_xspi_mem_slot_functions
 */

__STATIC_INLINE uint8_t
getDurationAttribute(inph_en_xspi_transfer_width_t transferWidth,
                     inph_en_xspi_data_rate_t dataRate);

__STATIC_INLINE uint8_t
getModeAttribute(inph_en_xspi_transfer_width_t transferWidth);

/**
 * This function returns duration in (clock cycles - 1) taken by the command
 * given the command transfer width and data rate.
 *
 * @param[in] transfer_width   Specifies single, dual or quad mode width.
 * @param[in] data_rate        Specifies single or double data rate.
 * @return                     Duration in (clock cycles - 1)
 */
__STATIC_INLINE uint8_t
getDurationAttribute(inph_en_xspi_transfer_width_t transferWidth,
                     inph_en_xspi_data_rate_t dataRate)
{
    uint8_t duration = 0;

    if ((transferWidth == INPH_XSPI_WIDTH_SINGLE) &&
        (dataRate == INPH_XSPI_DATA_RATE_SDR)) {
        duration = INPH_XSPI_SPICMDATTR_STRx1_MODE_DURATION;
    }
    else if ((transferWidth == INPH_XSPI_WIDTH_DUAL) &&
             (dataRate == INPH_XSPI_DATA_RATE_SDR)) {
        duration = INPH_XSPI_SPICMDATTR_STRx2_MODE_DURATION;
    }
    else if ((transferWidth == INPH_XSPI_WIDTH_QUAD) &&
             (dataRate == INPH_XSPI_DATA_RATE_SDR)) {
        duration = INPH_XSPI_SPICMDATTR_STRx4_MODE_DURATION;
    }
    else if ((transferWidth == INPH_XSPI_WIDTH_SINGLE) &&
             (dataRate == INPH_XSPI_DATA_RATE_DDR)) {
        duration = INPH_XSPI_SPICMDATTR_DDRx1_MODE_DURATION;
    }
    else if ((transferWidth == INPH_XSPI_WIDTH_DUAL) &&
             (dataRate == INPH_XSPI_DATA_RATE_DDR)) {
        duration = INPH_XSPI_SPICMDATTR_DDRx2_MODE_DURATION;
    }
    else if ((transferWidth == INPH_XSPI_WIDTH_QUAD) &
             (dataRate == INPH_XSPI_DATA_RATE_DDR)) {
        duration = INPH_XSPI_SPICMDATTR_DDRx4_MODE_DURATION;
    }

    return duration;
}

/**
 * This function returns mode setting given the transfer width
 *
 * @param[in] transfer_width   Specifies single, dual or quad mode width.
 * @return                     Mode setting.
 */
__STATIC_INLINE uint8_t
getModeAttribute(inph_en_xspi_transfer_width_t transferWidth)
{
    uint8_t mode = 0;

    if (transferWidth == INPH_XSPI_WIDTH_SINGLE) {
        mode = INPH_XSPI_ATTR_SPI_MODE;
    }
    else if (transferWidth == INPH_XSPI_WIDTH_DUAL) {
        mode = INPH_XSPI_ATTR_DUAL_MODE;
    }
    else if (transferWidth == INPH_XSPI_WIDTH_QUAD) {
        mode = INPH_XSPI_ATTR_QUAD_MODE;
    }

    return mode;
}

#if defined(__cplusplus)
}
#endif

#endif /* INPH_XSPI_MEMORYSLOT_H */
