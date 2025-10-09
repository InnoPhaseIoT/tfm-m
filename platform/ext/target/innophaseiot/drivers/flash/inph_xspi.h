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
 ***************************************************************************/
/**
 * @file    inph_xspi.h
 * @author  Innophase Firmware Team
 * @brief   Provides low level APIs for xSPI driver
 */

/**
 * @addtogroup INPH_PDL_XSPI xSPI (Expanded SPI)
 * @{
 * The SPI-based communication interface to the external quad SPI (QSPI)
 * high-speed memory devices.
 *
 * The functions and other declarations used in this driver are in inph_xspi.h
 * and inph_xspi_memslot.h (if used).
 *
 * **xSPI Memory Controller Interface**: This IP block implements an SPI-based
 * communication interface for interfacing external memory devices to Helium.
 * The xSPI MC supports SPI, dual SPI (DSPI), quad SPI (QSPI).
 *
 * Features
 *   - Standard SPI Master interface
 *   - Supports single/dual/quad SPI memory devices
 *   - eXecute-In-Place (XIP) operation mode for flash devices for read access
 *   - Access-In-pace (AIP) operation mode for PSRAM devices for read access
 *     and write accesses
 *   - Supports external serial memory initialization via Serial Flash
 *     Discoverable Paramaters (SFDP) standard.
 *
 * The primary usage model for the xSPI is that of an external memory interface.
 * The driver is capable of interfacing with different types of memory, such as
 * NOR flash and PSRAM devices.
 *
 * @b xSPI driver is divided into three layers
 *   - inph_xspi.h API
 *   - inph_xspi_memslot.h API
 *   - XSPI memory configuration structures
 *
 * The XSPI API is divided into the low-level functions and memory-slot
 * functions. Use the low level API for the xSPI block initialization and for
 * implementing a generic SPI communication interface using the XSPI block.
 *
 * The memory slot API has functions to implement the basic memory operations
 * such as program, read, erase etc. These functions are implemented using the
 * memory parameters in the memory device configuration data structure. The
 * Inph_XSPI_MemInit() API initializes all the memory slots based on the
 * settings in the array.
 *
 * @image html xspi_pdl_layers.png
 *
 * @warning You cannot edit a buffer during the Read/Write operations.
 *
 * Before any new operation, check that the xSPI driver has completed the
 * previous operation by calling Inph_XSPI_BusyCheck(). Also, check that the
 * memory is available before proceeding.
 *
 * Simple example of external flash memory programming using low level xSPI API.
 * All steps mentioned in example below are incorporated in
 * @ref Inph_XSPI_MemCmdWriteEnable(), @ref Inph_XSPI_MemCmdProgram(), and
 * @ref Inph_XSPI_MemIsBusy() of the
 * @ref group_xspi_mem_slot_functions "memory slot level API".
 * @warning Example is simplified, without checks of error conditions.
 * @note Flash memories need erase operation before programming. Refer to
 * external memory datasheet for specific memory commands.
 * @note PSRAM devices need to be Reset before starting memory operations
 * @ref Inph_XSPI_MemReset().
 *
 * @snippet xspi_snippets.c XSPI_Write_Example
 *
 * For the Read operation, before accessing the read buffer, check that it is
 * ready by calling the Inph_XSPI_BusyCheck().
 *
 * Simple example of external flash memory read using low level XSPI API. All
 * steps mentioned in example below are incorporated in
 * @ref Inph_XSPI_MemCmdRead() of the
 * @ref group_xspi_mem_slot_functions "memory slot level API".
 * @warning Example is simplified, without checks of error conditions.
 * @note Refer to external memory datasheet for specific memory commands.
 *
 * @snippet xspi_snippets.c XSPI_Read_Example
 *
 * @section group_xspi_configuration Configuration Considerations
 *
 * PDL API has common parameters: base, context, config structures.
 *
 * See Inph_XSPI_Init() for the required configuration structures and other
 * initialization settings.
 *
 * See the documentation for Inph_XSPI_Init() and Inph_XSPI_MemInit() for
 * details on the required configuration structures and other initialization
 * topics.
 *
 * The normal/command mode is used for implementing a generic SPI/DSPI/QSPI
 * communication interface using the xSPI block. This interface can be used
 * to implement special commands like Program/Erase of flash, memory device
 * configuration, and other special commands specific to the memory device.
 * The transfer width (SPI/DSPI/QSPI) of a transmission is a parameter set for
 * each transmit/receive operation. So these can be changed at run time.
 *
 * In a typical memory interface with flash memory, the xSPI is used in the
 * XIP mode when reading from the memory and it switches to the normal mode
 * when writing to flash memory.
 * In a typical memory interface with PSRAM device, the xSPI is used in XIP
 * mode when reading from memory and AIP mode while writing to memory. It can
 * also switch to normal command mode to read and write to the memory device.
 *
 * A typical memory device has multiple types of commands.
 *
 * The xSPI interface can be used to transmit different types of commands. Each
 * command has different phases: command, address, dummy cycles, and transmit
 * and receive data which require separate APIs.
 *
 * @subsection group_xspi_init XSPI Initialization
 * Create interrupt function and allocate memory for XSPI context structure
 * @snippet xspi_snippets.c XSPI_INIT_context_and_interrupt
 *
 * XSPI driver initialization for low level API usage (inph_xspi.h)
 * @snippet xspi_snippets.c XSPI_INIT_low_level
 *
 * Additional steps to initialize XSPI driver for memory slot level API usage
 * (inph_xspi_memslot.h).
 * @snippet xspi_snippets.c XSPI_memslot_level
 *
 * @note Example does not include initialization of all needed configuration
 * structures (@ref inph_stc_xspi_mem_device_cfg_t,
 * @ref inph_stc_xspi_mem_cmd_t)
 *
 * @subsection group_xspi_xip_init XSPI XIP Initialization
 * The eXecute In Place (XIP) is a mode of operation where read or write
 * commands to the memory device are directed through the xSPI without any use
 * of API function calls. In this mode the xSPI block maps the AHB bus-accesses
 * to external memory device addresses to make it behave similar to internal
 * memory. This allows the CPU to execute code directly from external memory.
 * This mode is not limited to code and is suitable also for data read and
 * write accesses. The memory regions available for XIP addresses allocation
 * are defined in a linker script file (.ld).
 *
 * With XSPI IP, normal/command mode transactions are also allowed when the
 * device is set to XIP mode. However, only blocking XSPI API's are expected
 * to be used for erase or program operations.
 *
 * When the external flash is busy with erase or write operation, it may not be
 * available for XIP at that moment. Blocking API's will ensure the transaction
 * is complete and then switch back to XIP.
 *
 * Read-while-write is a feature which when enabled, suspends the write which is
 * in progress when a read arrives on the AIP interface. Once the AIP read is
 * serviced, the suspended write is resumed, thus the AIP read is not blocked.
 * This feature can be enabled in XIP configurations.
 *
 * @snippet xspi_snippets.c XSPI_XIP
 * @note Example of input parameters initialization is in @ref group_xspi_init
 * section.
 *
 *@subsection group_xspi_usage_rules Rules for Helium QSPI/XSPI Block Usage
 * 1. All operations may use one or more dummy cycles between the Command
 * and Address phase and the device's Response phase. Bus contention may
 * occur if no (zero) dummy cycles are used.
 * 2. Any transfer that does not allow dummy cycles (such as Register Status
 * Reads) must use the single-bit transfer mode. In single-bit mode, Helium
 * drives the Command on the Data0 line and the device responds on the Data1
 * line, so bus contention cannot occur.
 *
 * @defgroup group_xspi_macros Macros
 * @{
 * @defgroup group_xspi_macros_status Status Macros
 * @defgroup group_xspi_macros_cmd Command Macros
 * @defgroup group_xspi_macros_flags External Memory Flags
 * @}
 * @defgroup group_xspi_functions Functions
 * @{
 * @defgroup group_xspi_low_level_functions Low Level Functions
 * @{
 * The XSPI interface can be used to transmit different types of commands.
 * Each command has different phases: command, dummy cycles, and transmit and
 * receive data which require separate APIs.
 *
 * During the time that Chip Select line is active (LOW) the clock signal (CLK)
 * is toggled while command information is first transferred on the data (IO)
 * signals from the master to the slave. The clock continues to toggle during
 * any period required for information access in the slave. The clock continues
 * to toggle during the transfer of read data from the slave to the master
 * or write data from the master to the slave. When the master has transferred
 * the desired amount of data, the master drives the Chip Select line
 * inactive (HIGH).
 * Basic flow for read/write commands using
 * @ref Inph_XSPI_TransmitCommand,
 * @ref Inph_XSPI_TransmitData,
 * @ref Inph_XSPI_ReceiveData and
 * @ref Inph_XSPI_SendDummyCycles with a Quad SPI interface.
 *
 * The sequence of the PDL functions required in a read or write transaction is:
 * @ref Inph_XSPI_TransmitCommand() ->
 * @ref Inph_XSPI_SendDummyCycles() ->
 * @ref Inph_XSPI_ReceiveData() / @ref Inph_XSPI_TransmitData() ->
 * @ref Inph_XSPI_BusyCheck().
 * The address is sent as part of the Inph_XSPI_TransmitCommand() function.
 * No separate function call is required.
 *
 * @}
 * @defgroup group_xspi_mem_slot_functions Memory Slot Functions
 * @{
 * Memory slot API
 * @}
 * @}
 * @defgroup group_xspi_data_structures Data Structures
 * @{
 * @defgroup group_xspi_data_structures_memslot XSPI Memory Description Structure
 *
 * Top structure is @ref inph_stc_xspi_block_config_t, which could have links
 * to  @ref inph_stc_xspi_mem_config_t which describes the device connected
 * to the XSPI external memory.
 *
 * @}
 * @defgroup group_xspi_enums Enumerated Types
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INPH_XSPI_H
#define INPH_XSPI_H

#if defined(__cplusplus)
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "inph_assert.h"
#include "inph_status_codes.h"
#include "inph_utils.h"
#include "xspi_registers.h"
//--- #include "inph_timers.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup group_xspi_macros
 * @{
 */

#define INPH_XSPI_DRV_VERSION_MAJOR   1 /**< The driver major version */

#define INPH_XSPI_DRV_VERSION_MINOR   0 /**< The driver minor version */

#define INPH_XSPI_WAIT_1_US           (1U)

/** \cond INTERNAL */

#define INPH_XSPI_MAX_FIFO_FILL_LEVEL (7U)

#define INPH_XSPI_TX_FIFO_DEPTH       (4U)
#define INPH_XSPI_RX_FIFO_DEPTH       (4U)

#define INPH_XSPI_1_BYTE              (1U)
#define INPH_XSPI_2_BYTES             (2U)
#define INPH_XSPI_3_BYTES             (3U)
#define INPH_XSPI_4_BYTES             (4U)

/* Modes supported */
#define INPH_XSPI_ATTR_SPI_MODE       (1U) /**< single (x1, 1-bit) */
#define INPH_XSPI_ATTR_DUAL_MODE      (2U) /**< dual (x2, 2-bit)   */
#define INPH_XSPI_ATTR_QUAD_MODE      (4U) /**< quad (x4, 4-bit)   */
#define INPH_XSPI_ATTR_OCTA_MODE      (8U) /**< octa (x8, 8-bit)   */
#define INPH_XSPI_ATTR_x16_MODE       (9U) /**< 16-bit (x16, 16-bit)   */

/* length of the command phase of the SPI transaction in SPI (clock cycles - 1)
 */
// single
#define INPH_XSPI_SPICMDATTR_STRx1_MODE_DURATION                               \
    (7U) /**< 8-bit command in STR x1 mode (8 clocks - 1) */
#define INPH_XSPI_SPICMDATTR_DDRx1_MODE_DURATION                               \
    (3U) /**< 8-bit command in DDR x1 mode (4 clocks - 1) */
// Dual
#define INPH_XSPI_SPICMDATTR_STRx2_MODE_DURATION                               \
    (3U) /**< 8-bit command in STR x2 mode (4 clocks - 1) */
#define INPH_XSPI_SPICMDATTR_DDRx2_MODE_DURATION                               \
    (1U) /**< 8-bit command in DDR x2 mode (2 clocks - 1) */
// Quad
#define INPH_XSPI_SPICMDATTR_STRx4_MODE_DURATION                               \
    (1U) /**< 8-bit command in STR x4 mode (2 clocks - 1) */
#define INPH_XSPI_SPICMDATTR_DDRx4_MODE_DURATION                               \
    (0U) /**< 8-bit command in DDR x4 mode (1 clocks - 1) */
// Octa
#define INPH_XSPI_SPICMDATTR_STRx8_MODE_DURATION                               \
    (0U) /**< 8-bit command in STR x8 mode (1 clocks - 1) */
#define INPH_XSPI_SPICMDATTR_DDRx8_MODE_DURATION                               \
    (0U) /**< 8-bit command in DDRR x8 mode (1 clocks - 1) */

/* length of the addr phase of the SPI transaction in SPI (clock cycles - 1) */
// single
#define INPH_XSPI_SPIADDRATTR_STRx1_MODE_DURATION                              \
    (23U) /**< 24-bit address in STR x1 mode (24 clocks-1)*/
#define INPH_XSPI_SPIADDRATTR_DDRx1_MODE_DURATION                              \
    (11U) /**< 24-bit address in DDR x1 mode (12 clocks-1)*/
// dual
#define INPH_XSPI_SPIADDRATTR_STRx2_MODE_DURATION                              \
    (11U) /**< 24-bit address in STR x2 mode (12 clocks-1)*/
#define INPH_XSPI_SPIADDRATTR_DDRx2_MODE_DURATION                              \
    (5U) /**< 24-bit address in DDR x2 mode (6 clocks-1)*/
// quad
#define INPH_XSPI_SPIADDRATTR_STRx4_MODE_DURATION                              \
    (5U) /**< 24-bit address in STR x4 mode (6 clocks-1)*/
#define INPH_XSPI_SPIADDRATTR_DDRx4_MODE_DURATION                              \
    (2U) /**< 24-bit address in DDR x4 mode (3 clocks-1)*/
// octa
#define INPH_XSPI_SPIADDRATTR_STRx8_MODE_DURATION                              \
    (2U) /**< 24-bit address in STR x8 mode (3 clocks-1)*/
#define INPH_XSPI_SPIADDRATTR_DDRx8_MODE_DURATION                              \
    (1U) /**< 24-bit address in STR x8 mode (2 clocks-1)*/

// data direction
#define INPH_XSPI_SPIDATAATTR_DIRECTION_WR                                     \
    (0U) /**< data is output - spi memory is written */
#define INPH_XSPI_SPIDATAATTR_DIRECTION_RD                                     \
    (1U) /**< data is input - spi memory is read */

#define INPH_XSPI_SPICMD_8_BIT_OFFSET                                          \
    (8U) /**< offset to align 8-bit command's most significant bit to bit [15] \
          */

#define INPH_XSPI_PSRAM_AIP_WRITE_SUPPORT_EN                                   \
    (1U) /**< AIP write is supported on attached memory chip for PSRAMs */

#define INPH_XSPI_DISABLED      (0U) /**< Disable feature */
#define INPH_XSPI_ENABLED       (1U) /**< Enable feature */
#define INPH_XSPI_NOT_SUPPORTED (0U) /**< Unsupported feature */
#define INPH_XSPI_PAGE_READ_DISABLED                                           \
    (0U) /**< Page read mode disabled for NOR flash */
#define INPH_XSPI_PAGE_READ_ENABLED                                            \
    (0U) /**< Page read mode enabled for NAND flash */
#define INPH_XSPI_AIP_SINGLE_DIE_ADDR_BITS                                     \
    (0x1F) /**< Number of address bits on a single die */
#define INPH_XSPI_AIP_ACCESS_BOUNDARY_NOT_SUPPORTED                            \
    (0x1F) /**< Max value when not supported (for NOR flash) */
#define INPH_XSPI_AIP_WINDOW0       (0x0) /**< AIP Windows 0 for NOR flash */
#define INPH_XSPI_AIP_WINDOW1       (0x1) /**< AIP Windows 0 for PSRAM flash */

#define INPH_XSPI_ADDR_FIELD_24BITS (0U) /**< 24- bit address field */
#define INPH_XSPI_ADDR_FIELD_32BITS (1U) /**< 32- bit address field */
#define INPH_XSPI_ADDR_FIELD_16BITS (2U) /**< 16- bit address field */
#define INPH_XSPI_ADDR_FIELD_8BITS  (3U) /**< 8- bit address field */

#define INPH_XSPI_DUMMY_NO_WRITE_LATENCY                                       \
    (1U) /**< 8- No write latency to be inserted */

/* DMA constants. */
#define INPH_XSPI_DMA_NOP                                                      \
    (0x0UL) /**< Does not execute the current line and go to next line. */
#define INPH_XSPI_DMA_RSV (0x2UL) /**< Reserved. */
#define INPH_XSPI_DMA_TRAN                                                     \
    (0x4UL) /**< Transfers data of one descriptor line. */
#define INPH_XSPI_DMA_LINK         (0x6UL) /**< The link to another descriptor. */
#define INPH_XSPI_DMA3_CMD         (0x1UL) /**< The Command descriptor. */
#define INPH_XSPI_DMA3_INTERGRATED (0x7UL) /**< The Integrated descriptor. */
#define INPH_XSPI_DMA2_DESCR_SIZE  (0x2UL) /**< The ADMA2 descriptor size. */

#define INPH_XSPI_DMA_TYPE_LINK                                                \
    (0x1UL)                             /**< The link to another descriptor.   \
                                         */
#define INPH_XSPI_DMA_TYPE_DATA (0x2UL) /**< Points to start of mem block */
#define INPH_XSPI_DMA_TYPE_INVALID1                                            \
    (0x0UL) /**< Invalid, causes DMA stop with error */
#define INPH_XSPI_DMA_TYPE_INVALID2                                            \
    (0x3UL) /**< Invalid, causes DMA stop with error */

/* DMA descriptor table positions for First word */
#define INPH_XSPI_DMA_ATTR_VALID_POS (0U) /**< The DMA Attr Valid position. */
#define INPH_XSPI_DMA_ATTR_END_POS   (1U) /**< The DMA Attr End position. */
#define INPH_XSPI_DMA_ATTR_INT_POS                                             \
    (2U)                               /**< The DMA Attr Interrupt position.   \
                                        */
#define INPH_XSPI_DMA_RSVD1_POS   (3U) /**< The DMA Reserved1 position. */
#define INPH_XSPI_DMA_TYPE_POS    (4U) /**< The DMA Type position. */
#define INPH_XSPI_DMA_RSV2_POS    (6U) /**< The DMA Reserved2 position. */
/* Size of mem block in 4 byte words. Size in bytes = 4 * Size */
#define INPH_XSPI_DMA_SIZE_POS    (16U) /**< The DMA Size position. */

/* DMA descriptor table positions for Second word */
/* Pointer to start of data block (data descriptor) or link descriptor */
#define INPH_XSPI_DMA_ADDR_POS    (2U) /**< The DMA Address position. */

#define INPH_XSPI_BUFFER_SIZE_MAX (65536UL)



/* SFDP related */
#define INPH_XSPI_SFDP_FAIL       (0x08U)

/* To validate input parameters */
#define INPH_XSPI_MODE_VALID(mode)                                             \
    ((INPH_XSPI_MODE_NORMAL == (inph_en_xspi_mode_t)(mode)) ||                 \
     (INPH_XSPI_MODE_NORMAL == (inph_en_xspi_mode_t)(mode)))

#define INPH_XSPI_TXFR_WIDTH_VALID(width)                                      \
    ((INPH_XSPI_WIDTH_SINGLE == (width)) ||                                    \
     (INPH_XSPI_WIDTH_DUAL == (width)) || (INPH_XSPI_WIDTH_QUAD == (width)))

#define INPH_XSPI_DATA_RATE_VALID(rate)                                        \
    ((INPH_XSPI_DATA_RATE_SDR == (rate)) || (INPH_XSPI_DATA_RATE_DDR == (rate)))

#define INPH_XSPI_CHIP_SEL_VALID(cs) (INPH_XSPI_CHIP_SELECT_0 == (cs))

#define INPH_XSPI_CMD_PARAM_VALID(param, paramSize)                            \
    (((paramSize) > 0U) ? (NULL != (param)) : (true))

#define INPH_XSPI_WIDTH_NA_VALID(paramWidth, paramSize)                        \
    (((paramSize) > 0U) ? ((paramWidth) <= INPH_XSPI_WIDTH_QUAD) : (true))

#define INPH_XSPI_CMD_DATA_RATE_VALID(rate)                                    \
    ((INPH_XSPI_DATA_RATE_SDR == (rate)) || (INPH_XSPI_DATA_RATE_DDR == (rate)))

#define INPH_XSPI_CMD_PARAM_DATA_RATE_VALID(rate)                              \
    ((INPH_XSPI_DATA_RATE_SDR == (rate)) || (INPH_XSPI_DATA_RATE_DDR == (rate)))

#define INPH_XSPI_DATA_DATA_RATE_VALID(rate)                                   \
    ((INPH_XSPI_DATA_RATE_SDR == (rate)) || (INPH_XSPI_DATA_RATE_DDR == (rate)))

#define INPH_XSPI_BUF_SIZE_VALID(size)                                         \
    (((INPH_XSPI_BUFFER_SIZE_MAX) >= (size)) && ((0UL) < (size)))

#define INPH_XSPI_BUF_PTR_VALID(buffer) (((NULL) != (buffer)))

/** \endcond */

/**
 * @} group_xspi_macros
 */

/* Exported typedef ----------------------------------------------------------*/

/** @addtogroup group_xspi_enums
 * @{
 */

/** The Transfer width options for the command, data, the address and the mode.
 */
typedef enum {
    INPH_XSPI_WIDTH_SINGLE = 0U, /**< Normal SPI mode. */
    INPH_XSPI_WIDTH_DUAL = 1U,   /**< Dual SPI mode. */
    INPH_XSPI_WIDTH_QUAD = 2U,   /**< Quad SPI mode. */
    INPH_XSPI_WIDTH_NA = 0xFFU   /**< The specific width parameter is not
                                    applicable for this memory command. */
} inph_en_xspi_transfer_width_t;

/** The xSPI error-event selection. */
typedef enum {
    /**< Generates a bus error. */
    INPH_XSPI_BUS_ERROR = 0UL,
    /** Stalls the bus with the wait states. This option will increase the
     * interrupt latency.
     */
    INPH_XSPI_WAIT_STATES = 1UL
} inph_en_xspi_error_event_t;

/** Placeholder to align with PDL requirements, not supported setup */
typedef enum {
    /**
     * xspi.spi_data[0] = DATA0, xspi.spi_data[1] = DATA1, ...,
     * xspi.spi_data[3] = DATA3. This value is allowed for the SPI, DSPI, QSPI,
     * dual QSPI SPI modes.
     */
    INPH_XSPI_DATA_SEL0 = 1,
    INPH_XSPI_DATA_SEL1 = 2
} inph_en_xspi_data_select_t;

/** The xSPI modes to work with an external memory. */
typedef enum {
    INPH_XSPI_MODE_NORMAL, /**< Command mode (MMIO mode). */
    INPH_XSPI_MODE_MEMORY  /**< XIP (eXecute In Place) mode. */
} inph_en_xspi_mode_t;

/** The xSPI transfer status return values. */
typedef enum {
    INPH_XSPI_READY,     /**< The XSPI is ready for transaction. */
    INPH_XSPI_TX_CMPLT,  /**< The data transmission is complete. */
    INPH_XSPI_TX_BUSY,   /**< The data transmission is in progress. */
    INPH_XSPI_RX_CMPLT,  /**< The data reception is completed. */
    INPH_XSPI_RX_BUSY,   /**< The data reception is in progress. */
    INPH_XSPI_XIP_ERROR, /**< An XIP alignment error. */
    INPH_XSPI_CMD_ERROR, /**< A TX CMD FIFO overflow. */
    INPH_XSPI_TX_ERROR,  /**< A TX DATA FIFO overflow. */
    INPH_XSPI_RX_ERROR   /**< An RX DATA FIFO underflow. */
} inph_en_xspi_transfer_state_t;

/* The chip select enum represents the corresponding bits in the chip select
 * register
 * */
typedef enum {
    INPH_XSPI_CHIP_SELECT_0 = 1U, /**< Chip select 0 for memory device */
} inph_en_xspi_chip_select_t;

/** Specifies the clock source for the receiver clock. */
typedef enum {
    INPH_XSPI_INTERNAL_CLK = 0U,     /**< The xSPI internal clock */
    INPH_XSPI_INV_INTERNAL_CLK = 1U, /**< The xSPI internal inverted clock */
    INPH_XSPI_FEEDBACK_CLK = 2U,     /**< The xSPI feedback clock */
    INPH_XSPI_INV_FEEDBACK_CLK = 3U  /**< The xSPI feedback inverted clock */
} inph_en_xspi_clk_select_t;

typedef enum {
    INPH_XSPI_DATA_RATE_SDR = 0, /**< The XSPI Single Data Rate (SDR) */
    INPH_XSPI_DATA_RATE_DDR = 1, /**< The XSPI Double Data Rate (DDR) */
} inph_en_xspi_data_rate_t;

typedef enum {
    INPH_XSPI_PHASE_PRESENT = 0, /**< Command phase is present */
    INPH_XSPI_PHASE_SKIP = 1,    /**< Command phase is skipped */
} inph_en_xspi_phase_presence_t;

/* Specifies the number of dummy bytes to be sent in dummy phase
 * of the SPI transaction
 * */
typedef enum {
    INPH_XSPI_DUMMY_NONE = 0,  /**< No dummy cycles */
    INPH_XSPI_DUMMY_1BYTE = 1, /**< 1 dummy byte - 8 cycles */
    INPH_XSPI_DUMMY_2BYTE = 2, /**< 2 dummy byte - 16 cycles */
    INPH_XSPI_DUMMY_3BYTE = 3, /**< 3 dummy byte - 24 cycles */
    INPH_XSPI_DUMMY_4BYTE = 4, /**< 4 dummy byte - 32 cycles */
} inph_en_xspi_dummybytes_t;

/* For memory chips (notably x16 ones) which support reading from and writing
 * to aligned addresses, the controller can mask the address (data transfered
 * in the address phase) such that it always carries the correct alignment.
*/
typedef enum {
    INPH_XSPI_ADDR_MASK_WORD = 0,     /**< Word address, minimal transfer width
                                        * is 32 bits, lower 2 bits are masked.
                                        * Address aligned to 4-byte boundary */
    INPH_XSPI_ADDR_MASK_HALFWORD = 2, /**< Half word, minimal transfer is
                                        * 16-bits, addr bit 0 is masked.
                                        * Address aligned to 2-byte boundary */
    INPH_XSPI_ADDR_MASK_BYTE = 3,     /**< Byte, nos restrictions
                                        * Address aligned to 1-byte boundary */
} inph_en_xspi_address_mask_t;


/** Specifies the quad enable requirement case.
 * JEDEC Basic Flash Parameter Table: 15th DWORD
**/
typedef enum
{
    INPH_XSPI_SFDP_QER_0   = 0, /**< No QE Bit */
    INPH_XSPI_SFDP_QER_1   = 1, /**< Bit 1 of Status Register 2 - Write uses 2 bytes using 01h */
    INPH_XSPI_SFDP_QER_2   = 2, /**< Bit 6 of Status Register 1 - Write uses 1 byte */
    INPH_XSPI_SFDP_QER_3   = 3, /**< Bit 7 of Status Register 2- Write uses 1 byte */
    INPH_XSPI_SFDP_QER_4   = 4, /**< Bit 1 of Status Register 2 - Write uses 1 or 2 bytes */
    INPH_XSPI_SFDP_QER_5   = 5, /**< Bit 1 of Status Register 2 - Write status uses 01h */
    INPH_XSPI_SFDP_QER_6   = 6, /**< Bit 1 of Status Register 2 - Write uses 1 byte using 31h */
} inph_en_xspi_qer_t;

/**
 * @} group_xspi_enums
 */

/** @addtogroup group_xspi_data_structures
 * @{
 */

/**
 * xSPI user callback function type called at the end if a transfer.
 *
 * @param[in] event          The event which caused the callback call.
 *
 */
typedef void (*inph_xspi_event_cb_t)(uint32_t event);

/** The xSPI configuration structure. */
typedef struct {
    uint32_t
        mode; /**<  Specifies the mode of operation \ref inph_en_xspi_mode_t. */
    uint32_t deselectDelay; /**<  Also called the Chip Select High Time
                             * Specifies the minimum duration of SPI
                             * de-selection between SPI transfers:
                             *   - "0": 1 clock cycle.
                             *   - "1": 2 clock cycles.
                             *   - "2": 3 clock cycles.
                             *   - "3": 4 clock cycles.
                             *   - "4": 5 clock cycles.
                             *   - "5": 6 clock cycles.
                             *   - "6": 7 clock cycles.
                             *   - "7": 8 clock cycles. */
    uint32_t rxClockSel;    /**< Specifies the clock source for the receiver
                             *  clock @ref inph_en_xspi_clk_select_t. */
    uint32_t blockEvent;    /**< Specifies what happens when there is a Read
                             * from an empty RX FIFO or a Write to a full
                             * TX FIFO. @ref inph_en_xspi_error_event_t. */
} inph_stc_xspi_config_t;

/**
 * The QSPI internal context data. The driver may require memory to perform
 * operations and it defines this structure. The application must not modify
 * it, instead allocate the required memory for the drive to work with.
 */
typedef struct {
    uint8_t const volatile
        *volatile txBufferAddr; /**<  The pointer to the data to transfer */
    uint32_t txBufferSize; /**<  The size of the data to transmit in bytes */
    uint32_t volatile txBufferCount; /**< The transfer counter. The number of
                                        the transmitted bytes = txBufferSize -
                                        txBufferCount */
    uint8_t volatile
        *volatile rxBufferAddr; /**<  The pointer to the variable where the
                                   received data is stored */
    uint32_t rxBufferSize; /**<  The size of the data to be received in bytes */
    uint32_t volatile rxBufferCount; /**< The transfer counter. The number of
                                        the received bytes = rxBufferSize -
                                        rxBufferCounter */
    volatile inph_en_xspi_transfer_state_t
        transferStatus; /**< Holds the current transfer status */
    inph_xspi_event_cb_t volatile txCmpltCb; /**< The user-defined callback
                                                executed at the completion of a
                                                transmission */
    inph_xspi_event_cb_t volatile rxCmpltCb; /**< The user-defined callback
                                                executed at the completion of a
                                                reception */

    uint8_t command; /**< The current SPI command which needs to be executed */

    uint32_t
        timeout; /**< The timeout in microseconds for the blocking functions.
                    This timeout value applies to all blocking APIs. */
    uint16_t memReadyPollDelay; /**< The timeout in microseconds for polling
                                   memory device on its readiness. */

    inph_en_xspi_data_rate_t preCmdDataRate; /**< preferred command data rate */
    inph_en_xspi_transfer_width_t
        preCmdWidth;                         /**< preferred command data rate */
    inph_en_xspi_data_rate_t preXIPDataRate; /**< preferred XIP data rate */

    uint32_t dummyCycles; /**< preferred dummy cycles per transaction */
    uint32_t flags; /**< device is memory-mapped, enables the Autodetect using
                       the SFDP, enables the write capability */

} inph_stc_xspi_context_t;

/**
 *  @brief DMA descriptor structure type definition
 */
typedef struct {
    uint32_t attribute; /*!< DMA descriptor attribute */
    uint32_t *address;  /*!< DMA descriptor address pointer */
} inph_xspi_dma_desc_t;

/**
 * @} group_xspi_data_structures
 */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup group_xspi_low_level_functions
 * @{
 */

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
                                     inph_stc_xspi_context_t *context);

/**
 * De-initialize the XSPI memory controller to default values.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    None.
 */
void Inph_XSPI_DeInit(XSPI_Type *base);

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
void Inph_XSPI_SetMode(XSPI_Type *base, inph_en_xspi_mode_t mode);

/**
 * Reads the mode of operation for xSPI MC, which can be XIP or normal mode.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    Current mode of operation which can be
 *                            @ref INPH_XSPI_MODE_NORMAL or
 *                            @ref INPH_XSPI_MODE_MEMORY.
 */
inph_en_xspi_mode_t Inph_XSPI_GetMode(XSPI_Type const *base);

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
                             inph_en_xspi_data_select_t dataSelect);

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
    inph_stc_xspi_context_t const *context);

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
                       inph_stc_xspi_context_t *context);

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
                               inph_stc_xspi_context_t const *context);

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
                      inph_stc_xspi_context_t *context);

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
                              inph_stc_xspi_context_t const *context);

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
                                                uint32_t cycles);

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
                                     inph_stc_xspi_context_t const *context);

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
void Inph_XSPI_Enable(XSPI_Type *base, inph_stc_xspi_context_t *context);

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
                                  uint32_t *device_idx);

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
void Inph_XSPI_Interrupt(XSPI_Type *base, inph_stc_xspi_context_t *context);

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
    uint32_t cmpltTxfr, inph_stc_xspi_context_t const *context);

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
    inph_stc_xspi_context_t *context);

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
                                   inph_stc_xspi_context_t const *context);

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
                          inph_stc_xspi_context_t *context);

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
    inph_en_xspi_data_rate_t dataRate, inph_stc_xspi_context_t const *context);

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
    inph_en_xspi_data_rate_t dataRate, uint32_t cycles);

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
    inph_stc_xspi_context_t *context);

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
                         inph_stc_xspi_context_t *context);

__STATIC_INLINE void Inph_XSPI_Disable(XSPI_Type *base);
__STATIC_INLINE void Inph_XSPI_SetInterruptMask(XSPI_Type *base,
                                                uint32_t interrupt);
__STATIC_INLINE uint32_t Inph_XSPI_GetInterruptMask(XSPI_Type const *base);
__STATIC_INLINE uint32_t Inph_XSPI_GetInterruptStatusMasked(
                                                        XSPI_Type const *base);
__STATIC_INLINE uint32_t Inph_XSPI_GetInterruptStatus(XSPI_Type const *base);
__STATIC_INLINE void Inph_XSPI_SetInterrupt(XSPI_Type *base,
                                            uint32_t interrupt);
__STATIC_INLINE void Inph_XSPI_ClearInterrupt(XSPI_Type *base,
                                              uint32_t interrupt);
__STATIC_INLINE void Inph_XSPI_SetTxFifoTriggerLevel(XSPI_Type *base,
                                                     uint32_t level);
__STATIC_INLINE void Inph_XSPI_SetRxFifoTriggerLevel(XSPI_Type *base,
                                                     uint32_t level);
__STATIC_INLINE uint32_t Inph_XSPI_GetCmdFifoStatus(XSPI_Type const *base);
__STATIC_INLINE uint32_t Inph_XSPI_GetTxFifoStatus(XSPI_Type const *base);
__STATIC_INLINE uint32_t Inph_XSPI_GetRxFifoStatus(XSPI_Type const *base);
__STATIC_INLINE bool Inph_XSPI_BusyCheck(XSPI_Type const *base);

/** \cond INTERNAL */

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
void Inph_XSPI_PushTxFifo(XSPI_Type *base, inph_stc_xspi_context_t *context);

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
void Inph_XSPI_PopRxFifo(XSPI_Type *base, inph_stc_xspi_context_t *context);

__STATIC_INLINE void Inph_XSPI_ConvertCmdTxfrWidth(
                                        inph_en_xspi_transfer_width_t txfrWidth,
                                        uint8_t *duration, uint8_t *mode);
__STATIC_INLINE void Inph_XSPI_ConvertAddrTxfrWidth(
                                        inph_en_xspi_transfer_width_t txfrWidth,
                                        uint8_t *duration, uint8_t *mode);
__STATIC_INLINE void Inph_XSPI_ConvertTransferWidthToMode(
                                        inph_en_xspi_transfer_width_t txfrWidth,
                                        uint8_t *mode);
__STATIC_INLINE void Inph_XSPI_StartTransfer(XSPI_Type *base,
                                             inph_stc_xspi_context_t *context);
__STATIC_INLINE uint32_t Inph_XSPI_PackBytes(uint8_t const buff[],
                                             uint8_t size);
__STATIC_INLINE void Inph_XSPI_UnPackBytes(uint32_t data, uint8_t byteArray[],
                                           uint32_t data_len);
__STATIC_INLINE inph_en_xspi_status_t Inph_XSPI_Timeout(uint32_t *timeoutUnits);

__STATIC_INLINE XSPI_DEVICE_Type volatile * Inph_XSPI_GetDeviceBySlot(
                                        XSPI_Type *base,
                                        inph_en_xspi_chip_select_t chipSelect);
/** \endcond */

/**
 * @} group_xspi_low_level_functions
 */

/** @addtogroup group_xspi_low_level_functions
 * @{
 */

/**
 * Disables the xSPI IP block. The XSPI block can be disabled
 * only when it is not in the active state. Use the Inph_XSPI_BusyCheck() API
 * to check it before calling this API.
 *
 * @note There is no xSPI IP specific enable/disable feature.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_Disable(XSPI_Type *base)
{
    UNUSED(base);
}

/**
 * This function sets interrupt mask for the XSPI Interrupt.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *interrupt      Mask for different source options that can be
 *                            masked.
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_SetInterruptMask(XSPI_Type *base,
                                                uint32_t interrupt)
{
    base->IRQCTRL.dw = interrupt;
}

/**
 * This function reads an interrupt mask for the XSPI Interrupt.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    Mask set for the xSPI Interrupt.
 */
__STATIC_INLINE uint32_t Inph_XSPI_GetInterruptMask(XSPI_Type const *base)
{
    return base->IRQCTRL.dw;
}

/**
 * This function is used to returns event that triggered the interrupt. This
 * function can be used in the interrupt service-routine to find which source
 * triggered the interrupt.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    Interrupt status register with with bits set at
 *                            positions corresponding to the interrupts
 *                            triggered in the system.
 */
__STATIC_INLINE uint32_t Inph_XSPI_GetInterruptStatusMasked(
                                                        XSPI_Type const *base)
{
    return base->SPISTS.dw;
}

/**
 * This function is used to read an active interrupt. This status is the
 * unmasked result, so will also show interrupts that will not generate active
 * interrupts.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    return the Interrupt status register with bit
 *                            positions corresponding to the interrupts
 *                            triggered in the system.
 */
__STATIC_INLINE uint32_t Inph_XSPI_GetInterruptStatus(XSPI_Type const *base)
{
    return base->SPISTS.dw;
}

/**
 * This function is used to set an interrupt source. This function can be used
 * to activate interrupts through the software.
 *
 * @note Interrupt sources set using this interrupt will generate interrupts
 * only if they are not masked.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] interrupt       An encoded integer with a bit set corresponding
 *                            to the interrupt to be triggered.
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_SetInterrupt(XSPI_Type *base, uint32_t interrupt)
{
    base->IRQCTRL.dw = interrupt;
}

/**
 * This function is used to clear an interrupt source. This function can be
 * used in the user code to clear all pending interrupts.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] interrupt       An encoded integer with a bit set corresponding
 *                            to the interrupt that must be cleared.
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_ClearInterrupt(XSPI_Type *base,
                                              uint32_t interrupt)
{
    base->SPISTS.dw = interrupt;
}

/**
 * This function is used to set fill level for the TX FIFO. This value must
 * be an integer between 0 and 7. For the normal SPI mode only.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] level           Fill level to set between (0-7).
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_SetTxFifoTriggerLevel(XSPI_Type *base,
                                                     uint32_t level)
{
    INPH_ASSERT(level <= INPH_XSPI_MAX_FIFO_FILL_LEVEL);
    base->IRQCTRL.bf.FIFOBoundary = level;
}

/**
 * This function is used to set fill level for the RX FIFO. This value must
 * be an integer between 0 and 7. For the normal mode only.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] level           Fill level to set between (0-7).
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_SetRxFifoTriggerLevel(XSPI_Type *base,
                                                     uint32_t level)
{
    INPH_ASSERT(level <= INPH_XSPI_MAX_FIFO_FILL_LEVEL);
    base->IRQCTRL.bf.FIFOBoundary = level;
}

/**
 * This function gets FIFO Status.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    FIFO status.
 */
__STATIC_INLINE uint32_t Inph_XSPI_GetCmdFifoStatus(XSPI_Type const *base)
{
    return base->FIFOSTS.dw;
}

/**
 * This function gets the Tx FIFO status
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    Tx FIFO status.
 */
__STATIC_INLINE uint32_t Inph_XSPI_GetTxFifoStatus(XSPI_Type const *base)
{
    return base->SPISTS.bf.WriteFIFOStatus;
}

/**
 * This function gets the Rx FIFO status
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    Rx FIFO status.
 */
__STATIC_INLINE uint32_t Inph_XSPI_GetRxFifoStatus(XSPI_Type const *base)
{
    return base->SPISTS.bf.ReadFIFOStatus;
}

/**
 * This function gets the busy status of SPI transaction
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @return                    SPI busy status.
 */
__STATIC_INLINE bool Inph_XSPI_BusyCheck(XSPI_Type const *base)
{
    return base->SPISTS.bf.Busy;
}

/** \cond INTERNAL */

/**
 * This function gets the duration and mode based on cmd transfer bus width.
 *
 * @param[in] txfrWidth       Transfer width for command phase.
 * @param[out] *duration      Pointer to transfer duration.
 * @param[out] *mode          Pointer to transfer mode.
 * @return                    None.
 */

__STATIC_INLINE void Inph_XSPI_ConvertCmdTxfrWidth(
                                        inph_en_xspi_transfer_width_t txfrWidth,
                                        uint8_t *duration, uint8_t *mode)
{
    if (txfrWidth == INPH_XSPI_WIDTH_SINGLE) {
        *duration = INPH_XSPI_SPICMDATTR_STRx1_MODE_DURATION;
        *mode = INPH_XSPI_ATTR_SPI_MODE;
    }
    else if (txfrWidth == INPH_XSPI_WIDTH_DUAL) {
        *duration = INPH_XSPI_SPICMDATTR_STRx2_MODE_DURATION;
        *mode = INPH_XSPI_ATTR_DUAL_MODE;
    }
    else if (txfrWidth == INPH_XSPI_WIDTH_QUAD) {
        *duration = INPH_XSPI_SPICMDATTR_STRx4_MODE_DURATION;
        *mode = INPH_XSPI_ATTR_QUAD_MODE;
    }
}

/**
 * This function gets the duration and mode based on address transfer bus width.
 *
 * @param[in] txfrWidth       Transfer width for address phases.
 * @param[out] *duration      Pointer to transfer duration.
 * @param[out] *mode          Pointer to transfer mode.
 * @return                    None.
 */

__STATIC_INLINE void Inph_XSPI_ConvertAddrTxfrWidth(
                                        inph_en_xspi_transfer_width_t txfrWidth,
                                        uint8_t *duration, uint8_t *mode)
{
    if (txfrWidth == INPH_XSPI_WIDTH_SINGLE) {
        *duration = INPH_XSPI_SPIADDRATTR_STRx1_MODE_DURATION;
        *mode = INPH_XSPI_ATTR_SPI_MODE;
    }
    else if (txfrWidth == INPH_XSPI_WIDTH_DUAL) {
        *duration = INPH_XSPI_SPIADDRATTR_STRx2_MODE_DURATION;
        *mode = INPH_XSPI_ATTR_DUAL_MODE;
    }
    else if (txfrWidth == INPH_XSPI_WIDTH_QUAD) {
        *duration = INPH_XSPI_SPIADDRATTR_STRx4_MODE_DURATION;
        *mode = INPH_XSPI_ATTR_QUAD_MODE;
    }
}

/**
 * This function gets the mode based on transfer bus width.
 *
 * @param[in] txfrWidth       Transfer width for command, data & address phases.
 * @param[out] *mode          Pointer to transfer mode.
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_ConvertTransferWidthToMode(
                                        inph_en_xspi_transfer_width_t txfrWidth,
                                        uint8_t *mode)
{
    if (txfrWidth == INPH_XSPI_WIDTH_SINGLE) {
        *mode = INPH_XSPI_ATTR_SPI_MODE;
    }
    else if (txfrWidth == INPH_XSPI_WIDTH_DUAL) {
        *mode = INPH_XSPI_ATTR_DUAL_MODE;
    }
    else if (txfrWidth == INPH_XSPI_WIDTH_QUAD) {
        *mode = INPH_XSPI_ATTR_QUAD_MODE;
    }
}

/**
 * This function starts the transfer by writing the command into the
 * SPI Command register. Writing to this register start executing the written
 * command on the SPI bus.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *context        Pointer to the context structure that holds the
 *                            transfer parameters.
 * @return                    None.
 * @pre                       All other command parameters should be configured
 *                            before writing into this register. This is
 *                            required even if the command is skipped.
 */
__STATIC_INLINE void Inph_XSPI_StartTransfer(XSPI_Type *base,
                                             inph_stc_xspi_context_t *context)
{
    /* For commands less than 16 bits wide, align command's most significant
     * bit to bit [15]. Writing this registers executes the command.
     */
    base->SPICMD.bf.Command = (context->command)
                              << INPH_XSPI_SPICMD_8_BIT_OFFSET;
}

/**
 * This function packs bytes in the buff byte array into a 4-byte value.
 *
 * For data bytes less than 32-bits or the last word of the transaction is not
 * a multiple of 32-bits the most significant data bits must be aligned to
 * bit[31].
 *
 * @param[in]  buff           The byte array to pack.
 * @param[in]  size           Size of the byte array to pack.
 * @return                    The 4-byte value packed from the byte array.
 */
__STATIC_INLINE uint32_t Inph_XSPI_PackBytes(uint8_t const buff[], uint8_t size)
{
    uint32_t data = 0UL;

    if (size == INPH_XSPI_4_BYTES) {
        data = (((uint32_t)buff[0UL] << 24UL) | ((uint32_t)buff[1UL] << 16UL) |
                ((uint32_t)buff[2UL] << 8) | (uint32_t)buff[3]);
    }
    else if (size == INPH_XSPI_3_BYTES) {
        /* align byte 3 to MSB */
        data = (((uint32_t)buff[0UL] << 24UL) | ((uint32_t)buff[1UL] << 16UL) |
                ((uint32_t)buff[2UL] << 8));
    }
    else if (size == INPH_XSPI_2_BYTES) {
        /* align byte 2 to MSB */
        data = (((uint32_t)buff[0UL] << 24UL) | ((uint32_t)buff[1UL] << 16UL));
    }
    else if (size == INPH_XSPI_1_BYTE) {
        /* align byte 1 to MSB */
        data = (uint32_t)buff[0UL] << 24UL;
    }

    return data;
}

/**
 * This function un-packs 32-bit value into byte array.
 *
 * @param[in]  data           4 bytes byte which needs to be unpacked.
 * @param[out] byteArray      Holds the unpacked 8-bit bytes.
 * @param[in]  data_len       Size of the byte.
 * @return                    None.
 */
__STATIC_INLINE void Inph_XSPI_UnPackBytes(uint32_t data, uint8_t byteArray[],
                                           uint32_t data_len)
{
    if (data_len == INPH_XSPI_4_BYTES) {
        byteArray[0] = (uint8_t)((data >> 24) & 0xFF);
        byteArray[1] = (uint8_t)((data >> 16) & 0xFF);
        byteArray[2] = (uint8_t)((data >> 8) & 0xFF);
        byteArray[3] = (uint8_t)(data & 0xFF);
    }
    else if (data_len == INPH_XSPI_3_BYTES) {
        byteArray[0] = (uint8_t)((data >> 16) & 0xFF);
        byteArray[1] = (uint8_t)((data >> 8) & 0xFF);
        byteArray[2] = (uint8_t)(data & 0xFF);
    }
    else if (data_len == INPH_XSPI_2_BYTES) {
        byteArray[0] = (uint8_t)((data >> 8) & 0xFF);
        byteArray[1] = (uint8_t)(data & 0xFF);
    }
    else if (data_len == INPH_XSPI_1_BYTE) {
        byteArray[0] = (uint8_t)(data & 0xFF);
    }
}

/**
 * This function checks if timeout has expired. It uses Inph_TIMER_MicroSec()
 * function for delay.
 *
 * @param[in]  timeoutUnits   Pointer to timeout.
 * @return                    Timeout status which can be
 *                            @ref INPH_XSPI_ERROR_TIMEOUT when timeout
 *                            expires, @ref INPH_XSPI_SUCCESS otherwise.
 */
__STATIC_INLINE inph_en_xspi_status_t Inph_XSPI_Timeout(uint32_t *timeoutUnits)
{
    inph_en_xspi_status_t result = INPH_XSPI_SUCCESS;
    volatile int delay = 0xFF;

    if (*timeoutUnits > 0u) {
        //---Inph_TIMER_MicroSec(INPH_XSPI_WAIT_1_US);
        while (delay > 0) {
            delay--;
        }
        --(*timeoutUnits);
        result = (0u == (*timeoutUnits)) ? INPH_XSPI_ERROR_TIMEOUT
                                         : INPH_XSPI_SUCCESS;
    }
    return result;
}

/**
 * This function returns the address of xSPI memory device register structures
 * using the chip select number.
 *
 * @param[in] *base           Pointer to xSPI mem controller register structure.
 * @param[in] *chipSelect     Holds the chip select line to be used during
 *                            transmission.
 * @return                    Address of memory device structure.
 *
 */
__STATIC_INLINE XSPI_DEVICE_Type volatile *
Inph_XSPI_GetDeviceBySlot(XSPI_Type *base,
                          inph_en_xspi_chip_select_t chipSelect)
{
    XSPI_DEVICE_Type volatile *device;

    switch (chipSelect) {
    case INPH_XSPI_CHIP_SELECT_0:
        device = (XSPI_DEVICE_Type *)&(base->AIPwindow0.s);
        break;
    default:
        /* A user error */
        device = NULL;
        break;
    }

    return device;
}
/** \endcond */

/**
 * @} group_xspi_low_level_functions
 */

#if defined(__cplusplus)
}
#endif

#endif /* INPH_XSPI_H */

/**
 * @} INPH_PDL_XSPI
 */
