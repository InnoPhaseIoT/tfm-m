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
 ******************************************************************************
 * @file   memdev_cfg.h
 *
 * @brief  Provides definitions for XSPI driver memory configurations for the
 *         connected slave device.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INPH_XSPI_MEMDEV_CFG_H
#define INPH_XSPI_MEMDEV_CFG_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "inph_xspi_memslot.h"

#define INPH_XSPI_DEVICE_NUM       2

/* NOR Flash Memory default command opcodes */
#define INPH_XSPI_WRITE_ENABLE_CMD (0x06U) /**< Write Enable command */
#define INPH_XSPI_VOL_SR_WRITE_ENABLE_CMD                                      \
    (0x50U) /**< Write Enable command for volatile status register */
#define INPH_XSPI_WRITE_DISABLE_CMD (0x04U) /**< Write Disable command */

#define INPH_XSPI_RELEASE_PWR_DWN_CMD                                          \
    (0xABU)                             /**< Release Power Down command        \
                                         */
#define INPH_XSPI_RD_DEV_ID_CMD (0xABU) /**< Read Device ID command */
#define INPH_XSPI_RD_MANU_DEV_ID_CMD                                           \
    (0x90U) /**< Read Manufacturer and Device ID command */
#define INPH_XSPI_RD_JEDEC_ID_CMD (0x9FU) /**< Read JEDEC ID command */
#define INPH_XSPI_RD_UNIQUE_ID_CMD                                             \
    (0x4BU) /**< Read device unique ID command                                 \
             */

#define INPH_XSPI_RD_CMD       (0x03U) /**< Read data command */
#define INPH_XSPI_FAST_RD_CMD  (0x0BU) /**< Read data command */

#define INPH_XSPI_PAGE_PGM_CMD (0x02U) /**< Read data command */

#define INPH_XSPI_SECTOR_4K_ERASE_CMD                                          \
    (0x20U) /**< Sector Erase(4KB) command                                     \
             */
#define INPH_XSPI_BLOCK_32K_ERASE_CMD                                          \
    (0x52U) /**< Block Erase(32KB) command                                     \
             */
#define INPH_XSPI_BLOCK_64K_ERASE_CMD                                          \
    (0xD8U)                              /**< Block Erase(32KB) command        \
                                          */
#define INPH_XSPI_CHIP_ERASE_CMD (0xC7U) /**< Chip Erase command */

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

#define INPH_XSPI_READ_SFDP_REG_CMD (0x5AU) /**< Read SFDP Register command */
#define INPH_XSPI_ERASE_SEC_REG_CMD                                            \
    (0x44U) /**< Erase Security Register command */
#define INPH_XSPI_PGM_SEC_REG_CMD                                              \
    (0x42U) /**< Program Security Register command */
#define INPH_XSPI_RD_SEC_REG_CMD                                               \
    (0x48U) /**< Read Security Register command                                \
             */

#define INPH_XSPI_GLB_BLK_LOCK_CMD   (0x7EU) /**< Global Block Lock command */
#define INPH_XSPI_GLB_BLK_UNLOCK_CMD (0x98U) /**< Global Block Lock command */
#define INPH_XSPI_RD_BLK_LOCK_CMD    (0x3DU) /**< Read Block Lock command */
#define INPH_XSPI_INDIVIDUAL_BLK_LOCK_CMD                                      \
    (0x36U) /**< Individual Block Lock command */
#define INPH_XSPI_INDIVIDUAL_BLK_UNLOCK_CMD                                    \
    (0x39U) /**< Individual Block Unlock command */

#define INPH_XSPI_ERASE_PGM_SUSPEND_CMD                                        \
    (0x75U) /**< Erase/Program Suspend command */
#define INPH_XSPI_ERASE_PGM_RESUME_CMD                                         \
    (0x7AU)                                /**< Erase/Program Suspend command */
#define INPH_XSPI_PWR_DWN_CMD      (0xB9U) /**< Power Down command */

#define INPH_XSPI_RESET_ENABLE_CMD (0x66U) /**< Reset Enable command */
#define INPH_XSPI_RESET_DEVICE_CMD (0x99U) /**< Reset Device command */

#define INPH_XSPI_FAST_READ_DUAL_OUTPUT_1_1_2_CMD                              \
    (0x3BU) /**< Fast Read Dual Output command */

#define INPH_XSPI_FAST_READ_DUAL_IO_CMD                                        \
    (0xBBU) /**< Fast Read Dual IO command */
#define INPH_XSPI_READ_MANU_DEV_ID_DUAL_IO_CMD                                 \
    (0x92U) /**< Read Manufacturer, device ID Dual IO command */

#define INPH_XSPI_QUAD_INPUT_PAGE_PGM_CMD                                      \
    (0x32U) /**< Quad Input page Program command */
#define INPH_XSPI_FAST_RD_QUAD_OUTPUT_CMD                                      \
    (0x6BU) /**< Fast Read Quad Output command */

#define INPH_XSPI_READ_MANU_DEV_ID_QUAD_IO_CMD                                 \
    (0x94U) /**< Read Manufacturer, device ID Quad IO command */
#define INPH_XSPI_FAST_RD_QUAD_IO_CMD                                          \
    (0xEBU) /**< Fast Read Quad Output command */

#define INPH_XSPI_SET_BURST_WITH_WRAP_CMD                                      \
    (0x77U) /**< Set Burst with Wrap command */

#define INPH_XSPI_BUSY_BIT_0_OF_SR_1_Msk                                       \
    (0x01U) /**< The BUSY/WIP is bit 0 of the status register 1 mask */
#define INPH_XSPI_BUSY_BIT_0_OF_SR_1_Pos                                       \
    (0x00U) /**< The BUSY/WIP is bit 0 of the status register 1 position */

#define INPH_XSPI_QE_BIT_1_OF_SR_2_Msk                                         \
    (0x02U) /**< The QE is bit 1 of the status register 2 mask */
#define INPH_XSPI_QE_BIT_1_OF_SR_2_Pos                                         \
    (0x01U) /**< The QE is bit 1 of the status register 2 position */

#define INPH_XSPI_PAGE_SIZE (256U) /**< Page Size */
#define INPH_XSPI_PROG_TIME_TYPICAL_1MS                                        \
    (1U) /**< Units of Page Program Typical Time in .8 ms */
#define INPH_XSPI_PROG_TIME_MAX_3MS                                            \
    (3U) /**< Units of Page Program Max Time in ms */
#define INPH_XSPI_PROG_TIME_MAX_3000US                                         \
    (3000U) /**< Units of Page Program Max Time in us */
#define INPH_XSPI_SECTOR_4K_SIZE (4096U) /**< Sector Size */
#define INPH_XSPI_CHIP_ERASE_TYPICAL_TIME_20S                                  \
    (20000U) /**< Units of Chip Erase Typical Time in ms */
#define INPH_XSPI_CHIP_ERASE_MAX_TIME_100S                                     \
    (100000U) /**< Units of Chip Erase Maximum Time in ms */
#define INPH_XSPI_SECTOR_4K_ERASE_TYPICAL_TIME_45MS                            \
    (45U) /**< Units of 4k Sector Erase Typical Time in ms */
#define INPH_XSPI_SECTOR_4K_ERASE_MAX_TIME_400MS                               \
    (400U) /**< Units of 4k Sector Erase Maximum Time in ms */
#define INPH_XSPI_BLOCK_64K_ERASE_TYPICAL_TIME_150MS                           \
    (150U) /**< Units of 64k Block Erase Typical Time in ms */
#define INPH_XSPI_BLOCK_64K_ERASE_MAX_TIME_2000MS                              \
    (2000U) /**< Units of 64k Block Erase Maximum Time in ms */

/* PSRAM Memory default command opcodes */
#define INPH_XSPI_PSRAM_RD_CMD      (0x03U) /**< Read data command */
#define INPH_XSPI_PSRAM_FAST_RD_CMD (0x0BU) /**< Fast Read data command */
#define INPH_XSPI_PSRAM_FAST_RD_QUAD_CMD                                       \
    (0xEBU) /**< Quad Fast Read data command */

#define INPH_XSPI_PSRAM_WRITE_CMD      (0x02U) /**< Write command */
#define INPH_XSPI_PSRAM_QUAD_WRITE_CMD (0x38U) /**< Quad write command */

#define INPH_XSPI_PSRAM_ENTER_QUAD_MODE_CMD                                    \
    (0x35U) /**< Enter Quad Mode command */
#define INPH_XSPI_PSRAM_EXIT_QUAD_MODE_CMD                                     \
    (0xF5U)                                      /**< Exit Quad Mode command */
#define INPH_XSPI_PSRAM_RESET_ENABLE_CMD (0x66U) /**< Reset Enable command */
#define INPH_XSPI_PSRAM_RESET_CMD        (0x99U) /**< Reset command */

#define INPH_XSPI_PSRAM_WRAP_BOUNDARY_TOGGLE_CMD                               \
    (0xC0U)                               /**< Wrap Boundary Toggle command */
#define INPH_XSPI_PSRAM_RD_ID_CMD (0x9FU) /**< Read ID command */

extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_readCmd;
extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_writeEnCmd;
extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_writeDisCmd;
extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_eraseCmd;
extern const inph_stc_xspi_mem_cmd_t
    GD25Q64E_3byteaddr_SlaveSlot_0_chipEraseCmd;
extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_programCmd;
extern const inph_stc_xspi_mem_cmd_t
    GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegQeCmd;
extern const inph_stc_xspi_mem_cmd_t
    GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegWipCmd;
extern const inph_stc_xspi_mem_cmd_t
    GD25Q64E_3byteaddr_SlaveSlot_0_writeStsRegQeCmd;

extern const inph_stc_xspi_mem_device_cfg_t
    deviceCfg_GD25Q64E_3byteaddr_SlaveSlot_0;

extern const inph_stc_xspi_mem_config_t GD25Q64E_3byteaddr_SlaveSlot_0;
extern const inph_stc_xspi_mem_device_cfg_t deviceCfg_GD25LQ64E_3byteaddr_SlaveSlot_0;

extern const inph_stc_xspi_mem_config_t
    *const inphXSPIMemConfigs[INPH_XSPI_DEVICE_NUM];

extern const inph_stc_xspi_block_config_t xspiBlockConfig;

/* For testing 1x, 2x, and 4x modes */
extern const inph_stc_xspi_mem_device_cfg_t
    deviceCfg_GD25Q64E_3byteaddr_SlaveSlot_0_test;
extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_1x_readCmd;
extern const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_2x_readCmd;

#if defined(__cplusplus)
}
#endif

#endif /* INPH_XSPI_MEMDEV_CFG_H */
