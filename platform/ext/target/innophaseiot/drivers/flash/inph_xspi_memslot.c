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
 * @file    inph_xspi_memslot.c
 * @author  Innophase Firmware Team
 * @brief   Provides memory slot level APIs for xSPI driver
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "inph_xspi_memslot.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TIMEOUT_SLICE_MAX (1000000UL)    /* The maximum timeout slice (in us)
                                          * while polling the memory */
#define TIMEOUT_SLICE_DIV (4U)           /* The division factor to use for
                                          * slicing the timeout while polling
                                          * the memory */

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/**
 * This function returns the XIP address width field based on number of bytes
 * in the address.
 *
 * @param[in] numOfAddrBytes Number of bytes in address
 * @return                   XIP address width field
 */
static inph_en_xspi_xip_addr_width_t getXIPAddrWidth(uint32_t numOfAddrBytes)
{
    inph_en_xspi_xip_addr_width_t addrWidth = 0;

    if (numOfAddrBytes == 1) {
        addrWidth = INPH_XSPI_XIP_ADDR_WIDTH_8BITS;
    }
    else if (numOfAddrBytes == 2) {
        addrWidth = INPH_XSPI_XIP_ADDR_WIDTH_16BITS;
    }
    else if (numOfAddrBytes == 3) {
        addrWidth = INPH_XSPI_XIP_ADDR_WIDTH_24BITS;
    }
    else if (numOfAddrBytes == 4) {
        addrWidth = INPH_XSPI_XIP_ADDR_WIDTH_32BITS;
    }

    return addrWidth;
}

/**
 * This function configures the connected memory device's XIP registers and
 * enables the XIP mode for the corresponding device.
 *
 * @param[in] *device        XSPI memory device's register structure.
 * @param[in] *memCfg        Pointer to the memory device's config structure
 *                           that configures and maps the device to Helium's
 *                           memory map.
 * @return                   None
 */
static void AIPWindowInit(XSPI_DEVICE_Type volatile *device,
                          inph_stc_xspi_mem_config_t *memCfg)
{
    uint32_t regVal = 0;
    uint8_t mode = 0;
    uint8_t duration = 0;
    uint8_t aipWriteSupport = 0;

    /* For NOR Flash set this register to page size. Some PSRAM chips have
     * boundary limitations too. The value written here is the bit number on
     * which the boundary is on, eg., for 512 byte boundary set value to 9.
     * */
    device->AIPACCB.dw = INPH_XSPI_AIP_ACCESS_BOUNDARY_NOT_SUPPORTED;

    /* Set the size of this AIP window. The size must a power of two. If the
     * size is 2^N, the size is given by setting the low N bits to 1 in this
     * register and the rest to 0. Eg 8MB memory (2^23) low 23 bits should be
     * set to 1.*/
    device->AIPSIZE.bf.AIPsize = memCfg->memMappedSize - 1;

    /* The base address the memory slave is mapped to in memory map, which will
     * be the window address as given on the AHB/AXI interface. The window
     * address should be set ot multiples of window size. For example, if the
     * New AIP Size register is set to 17 (128KB window), the window base
     * address is set to any multiple of 128KB, e.g. 128KB, 256KB, 384KB, etc.
     * */
    device->AIPWINADDR.bf.AIPwindowaddress = memCfg->baseAddress;

    /* SPI cmd to use for AIP reads */
    device->AIPCMD.bf.RCommand = memCfg->deviceCfg->readCmd->command
                                 << INPH_XSPI_SPICMD_8_BIT_OFFSET;

    /* SPI cmd to use for AIP writes in case of PSRAM chips.
     * For NOR flash this setting can be ignored.
     * */
    device->AIPCMD.bf.WCommand = memCfg->deviceCfg->programCmd->command
                                 << INPH_XSPI_SPICMD_8_BIT_OFFSET;

    /* Get command duration and mode */
    mode = getModeAttribute(memCfg->deviceCfg->readCmd->cmdWidth);
    duration = getDurationAttribute(memCfg->deviceCfg->readCmd->cmdWidth,
                                    memCfg->deviceCfg->readCmd->cmdRate);

    /* Only PSRAM support AIP write, does not apply for NOR flash. */
    if ((memCfg->flags & INPH_XSPI_FLAG_AIP_WRITE_ENABLE) != 0) {
        aipWriteSupport = 1;
    }

    /* Set AIP Command Attribute register */
    regVal = 0;
    regVal =
        (duration << XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_OFFSET) |
        (mode << XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_OFFSET) |
        (memCfg->deviceCfg->readCmd->cmdRate
         << XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_OFFSET) |
        (aipWriteSupport << XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_OFFSET) |
        (memCfg->deviceCfg->readCmd->cmdPresence
         << XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_OFFSET);
    device->AIPCMDATTR.dw = regVal;

    /* Number of address bits on a single die. Only a single die is supported,
     * hence set to 0x1F. Ignoring the die select command as stacked die is not
     * supported and the chosen flash part does not have a die select command
     * */
    device->AIPDIECMD.bf.Addrbitsindie = INPH_XSPI_AIP_SINGLE_DIE_ADDR_BITS;

    /* Skipping the Die SelectAttribute (device->AIPDIEATTR) setting as
     * die select command is not supported by the chosen flash part
     * */

    /* Memory address to which the controller maps address 0 on the AIP slave
     * interface. Here, the address 0 in the external device is mapped to the
     * AIP window address.
     * */
    device->AIPADRBASE.bf.BaseAddress = 0;

    /* Set the AIP address attribute register */
    mode = getModeAttribute(memCfg->deviceCfg->readCmd->addrWidth);
    inph_en_xspi_xip_addr_width_t addrWidth =
        getXIPAddrWidth(memCfg->deviceCfg->numOfAddrBytes);
    regVal = 0;
    regVal = ((mode << XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_OFFSET) |
              (memCfg->deviceCfg->readCmd->addrRate
               << XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_OFFSET) |
              (addrWidth << XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_OFFSET) |
              (memCfg->deviceCfg->readCmd->addrMask
               << XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_OFFSET)) &
             XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_INV_MASK;
    device->AIPADRATTR.dw = regVal;

    /* Set the Chip Select line to use for AIP mode reads */
    device->AIPCS.bf.ChipSelect = memCfg->chipSelect;

    /* Skipping AIP State register as stacked die is not supported */

    /* Set the AIP Dummy Attribute register */
    regVal = 0;
    regVal = ((memCfg->deviceCfg->readCmd->dummyCycles - 1)
              << XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_OFFSET) |
             (memCfg->deviceCfg->readCmd->dummyCyclesPresence
              << XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_OFFSET) |
             (INPH_XSPI_DUMMY_NO_WRITE_LATENCY
              << XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_OFFSET);
    device->AIPDUMMYATTR.dw = regVal;

    /* If write capability is enabled in XIP mode, the suspend/resume
     * commands and attributes need to be setup, ignore otherwise.
     * */
    if ((memCfg->flags & INPH_XSPI_FLAG_WRITE_ENABLE) == 1) {
        /* Suspend resume commands */
        device->AIPSUSRESCMD.bf.SusCommand =
            memCfg->deviceCfg->suspendCmd->command
            << INPH_XSPI_SPICMD_8_BIT_OFFSET;
        device->AIPSUSRESCMD.bf.ResCommand =
            memCfg->deviceCfg->resumeCmd->command
            << INPH_XSPI_SPICMD_8_BIT_OFFSET;

        /* Get command duration and mode */
        mode = getModeAttribute(memCfg->deviceCfg->suspendCmd->cmdWidth);
        duration = getDurationAttribute(memCfg->deviceCfg->suspendCmd->cmdWidth,
                                        memCfg->deviceCfg->suspendCmd->cmdRate);
        /* Set Suspend resume attribute register */
        regVal = 0;
        regVal =
            ((duration << XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_OFFSET) |
             (mode << XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_OFFSET) |
             (memCfg->deviceCfg->suspendCmd->cmdRate
              << XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_OFFSET)) &
            XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_INV_MASK;
        device->AIPSUSRESATTR.dw = regVal;

        /* Setup timing values for suspend and resume operations */
        device->AIPSUSTIME.bf.Suspendtime = memCfg->deviceCfg->suspendTime;
        device->AIPRESTIME.bf.Resumetime = memCfg->deviceCfg->resumeTime;
        device->AIPSUSRESTIME.bf.Sustorestime = memCfg->deviceCfg->susToResTime;
        device->AIPRESSUSTIME.bf.Restosustime = memCfg->deviceCfg->resToSusTime;
    }

    /* Set Data attribute register */
    mode = getModeAttribute(memCfg->deviceCfg->readCmd->dataWidth);
    regVal = ((mode << XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_OFFSET) |
              (memCfg->deviceCfg->readCmd->dataRate
               << XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_OFFSET)) &
             XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_INV_MASK &
             XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_INV_MASK &
             XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_INV_MASK;
    device->AIPDATATTR.dw = regVal;

    /* Set Mode Bits */
    device->AIPMODEBITS.bf.Bits = memCfg->deviceCfg->readCmd->modeBits;

    /* Mode Attributes */
    mode = getModeAttribute(memCfg->deviceCfg->readCmd->modeWidth);
    duration = getDurationAttribute(memCfg->deviceCfg->readCmd->modeWidth,
                                    memCfg->deviceCfg->readCmd->modeRate);
    /* Set Mode Attributes */
    regVal = 0;
    regVal = ((duration << XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_OFFSET) |
              (mode << XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_OFFSET) |
              (memCfg->deviceCfg->readCmd->modeRate
               << XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_OFFSET) |
              (memCfg->deviceCfg->readCmd->modePresence
               << XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_OFFSET)) &
             XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_INV_MASK;

    device->AIPMODEBITSATTR.dw = regVal;

    /* Page read command attributes used only for NAND flash support
     * Set the Page Enable bit to 0 ,to disable page read mode for NOR chips
     * */
    mode = getModeAttribute(memCfg->deviceCfg->readCmd->cmdWidth);
    duration = getDurationAttribute(memCfg->deviceCfg->readCmd->cmdWidth,
                                    memCfg->deviceCfg->readCmd->cmdRate);
    regVal = 0;
    regVal = ((duration << XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_OFFSET) |
              (mode << XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_OFFSET) |
              (memCfg->deviceCfg->readCmd->modeRate
               << XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_OFFSET)) &
             XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_INV_MASK &
             XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_INV_MASK &
             XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_INV_MASK;
    device->AIPPRCMDATTR.dw = regVal;

    /* Skipping page read time setting(AIPPAGETIME), NAND flash not supported*/

    /* Enable support for suspend/resume, if supported.
     * Enable update bit to apply the new AIP registers settings.
     * Enable AIP/XIP mode for windows0.
     * */
    regVal = 0;
    regVal =
        (INPH_XSPI_ENABLED << XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_OFFSET) |
        (INPH_XSPI_ENABLED << XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_OFFSET);

    /* If write capability is enabled in XIP mode, enable suspend/resume */
    if ((memCfg->flags & INPH_XSPI_FLAG_WRITE_ENABLE) == 1) {
        regVal |=
            (INPH_XSPI_ENABLED << XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_OFFSET);
    }

    /* Write the settings to the AIP Control register */
    device->AIPCTRL.dw = regVal;
}

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
                  inph_stc_xspi_context_t *context)
{
    XSPI_DEVICE_Type volatile *device;
    inph_stc_xspi_mem_config_t *memCfg;
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    inph_en_xspi_status_t sfdpResult =(uint32_t)INPH_XSPI_SUCCESS;


    if ((base != NULL) && (blockConfig != NULL) &&
        (blockConfig->memConfig != NULL) && (context != NULL) &&
        (blockConfig->memCount != 0)) {
        inph_stc_xspi_mem_config_t **extMemCfg = blockConfig->memConfig;
        uint32_t size = blockConfig->memCount;

        for (uint32_t idx = 0UL; idx < size; idx++) {
            memCfg = extMemCfg[idx];

            if ((memCfg != NULL) && (memCfg->deviceCfg != NULL)) {
                INPH_ASSERT(INPH_XSPI_CHIP_SEL_VALID(memCfg->chipSelect));

                context->flags = memCfg->flags;

                /* We have two external devices connected, get the correct
                 * device which needs to be configured from chipSelect
                 * */
                device = Inph_XSPI_GetDeviceBySlot(base, memCfg->chipSelect);

                if (device != NULL) {
                    result = INPH_XSPI_SUCCESS;
                    sfdpResult = INPH_XSPI_SUCCESS;
                    if ((memCfg->flags & INPH_XSPI_FLAG_DETECT_SFDP) != 0U)
                    {
                        sfdpResult = Inph_XSPI_MemSfdpDetect(base,
                                                             memCfg->deviceCfg,
                                                             memCfg->chipSelect,
                                                             context);
                        if(sfdpResult != INPH_XSPI_SUCCESS)
                        {
                            sfdpResult |= INPH_XSPI_SFDP_FAIL << idx;
                        }
                    }

                    /* Check validity of parameters for XIP */
                    INPH_ASSERT(INPH_XSPI_MEM_ADDR_SIZE_VALID(
                                        memCfg->deviceCfg->numOfAddrBytes));
                    INPH_ASSERT(INPH_XSPI_MEM_MAPPED_SIZE_VALID(
                                        memCfg->memMappedSize));
                    INPH_ASSERT(INPH_XSPI_MEM_ADDR_VALID(
                                memCfg->baseAddress, memCfg->memMappedSize));

                    if ((sfdpResult == INPH_XSPI_SUCCESS) &&
                        (memCfg->flags & INPH_XSPI_FLAG_MEMORY_MAPPED) != 0) {
                        /* Configure XIP registers for window0 */
                        AIPWindowInit(device, memCfg);
                    }
                }
            }

            if (result == INPH_XSPI_ERROR_INVALID_PARAMETER) {
                break;
            }
        }
    }

    if (sfdpResult != INPH_XSPI_SUCCESS)
    {
        result = (INPH_XSPI_ID | INPH_PDL_STATUS_ERROR | sfdpResult);
    }

    return result;
}

/**
 * De-initialize the XSPI memory device slots to it's default values.
 *
 * @param[in] *base          Pointer to xSPI mem. controller register structure.
 * @return                   None.
 */
void Inph_XSPI_MemDeInit(XSPI_Type *base)
{
    XSPI_DEVICE_Type volatile *device;

    /* Configure the XSPI device slots to the default values */
    for (uint32_t idx = 0UL; idx < (uint32_t)INPH_XSPI_NO_OF_DEVICE; idx++) {
        device = Inph_XSPI_GetDeviceBySlot(base, (idx + 1));
        device->AIPCTRL.dw = 0;
        device->AIPACCB.dw = 0U;
        device->AIPSIZE.dw = 0U;
        device->AIPWINADDR.dw = 0U;
        device->AIPCMD.dw = 0U;
        device->AIPCMDATTR.dw = 0U;
        device->AIPDIECMD.dw = 0U;
        device->AIPDIEATTR.dw = 0U;
        device->AIPADRBASE.dw = 0U;
        device->AIPADRATTR.dw = 0U;
        device->AIPCS.dw = 0U;
        device->AIPDIEPAGESTATE.dw = 0U;
        device->AIPDUMMYATTR.dw = 0U;
        device->AIPSUSRESCMD.dw = 0U;
        device->AIPSUSRESATTR.dw = 0U;
        device->AIPSUSTIME.dw = 0U;
        device->AIPDATATTR.dw = 0U;
        device->AIPRESTIME.dw = 0U;
        device->AIPSUSRESTIME.dw = 0U;
        device->AIPRESSUSTIME.dw = 0U;
        device->AIPMODEBITS.dw = 0U;
        device->AIPMODEBITSATTR.dw = 0U;
        device->AIPPRCMDATTR.dw = 0U;
        device->AIPPAGETIME.dw = 0U;
    }
}

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
                            inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    /* Check if there is a current transfer in progress */
    if (context->transferStatus != INPH_XSPI_READY)
        return INPH_XSPI_OPERATION_INPROGRESS;

    /* Get the Write Enable command */
    inph_stc_xspi_mem_cmd_t *writeEn = memConfig->deviceCfg->writeEnCmd;
    if (writeEn != NULL) {
        result = Inph_XSPI_TransmitCommand_Ext(
            base, (uint8_t)writeEn->command, false, writeEn->cmdWidth,
            writeEn->cmdRate, NULL, 0, writeEn->addrWidth, writeEn->addrRate,
            INPH_XSPI_ADDR_MASK_BYTE, memConfig->chipSelect,
            INPH_XSPI_TX_LAST_BYTE, context);

        if (result == INPH_XSPI_SUCCESS) {
            uint8_t welStatus = 1;
            uint32_t timeout = context->timeout;
            /* Read the status register to check if the WEL is set */
            if (memConfig->deviceCfg->readStsRegWipCmd != NULL) {
                do {
                    result = Inph_XSPI_MemCmdReadStatus(
                        base, memConfig, &welStatus,
                        memConfig->deviceCfg->readStsRegWipCmd->command,
                        context);
                    if (result == INPH_XSPI_SUCCESS) {
                        /* Retrieve Write Enable latch bit */
                        welStatus = (welStatus & 0x02) >> 1;
                    }
                    result = Inph_XSPI_Timeout(&timeout);
                } while ((welStatus != 1) && (result != INPH_XSPI_ERROR_TIMEOUT));
            }
        }
    }

    return result;
}

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
                             inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    /* Check if there is a current transfer in progress */
    if (context->transferStatus != INPH_XSPI_READY)
        return INPH_XSPI_OPERATION_INPROGRESS;

    /* Get the Write Enable command */
    inph_stc_xspi_mem_cmd_t *writeDis = memConfig->deviceCfg->writeDisCmd;
    if (writeDis != NULL) {
        /* Write enable has only command phase, hence cmdParam is NULL */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, (uint8_t)writeDis->command, false, writeDis->cmdWidth,
            writeDis->cmdRate, NULL, 0, writeDis->addrWidth, writeDis->addrRate,
            INPH_XSPI_ADDR_MASK_BYTE, memConfig->chipSelect,
            INPH_XSPI_TX_LAST_BYTE, context);
    }

    return result;
}

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
                         inph_stc_xspi_context_t const *context)
{
    uint8_t busyStatus = 1;
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if (memConfig->deviceCfg->readStsRegWipCmd != NULL) {
        result = Inph_XSPI_MemCmdReadStatus(
            base, memConfig, &busyStatus,
            memConfig->deviceCfg->readStsRegWipCmd->command, context);

        if (result == INPH_XSPI_SUCCESS) {
            /* Retrieve WIP/Busy bits from the received status data */
            busyStatus &= memConfig->deviceCfg->stsRegBusyMask;
        }
    }
    return busyStatus;
}

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
                        inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint8_t statusReg[2] = {0U};

    if ((memConfig->deviceCfg->readStsRegQeCmd != NULL) &&
        (memConfig->deviceCfg->writeStsRegQeCmd != NULL) &&
        (memConfig->deviceCfg->readStsRegWipCmd != NULL)) {

        uint8_t writeStsRegQeCmd =
            (uint8_t)memConfig->deviceCfg->writeStsRegQeCmd->command;
        /* Read the status register 1 */
        result = Inph_XSPI_MemCmdReadStatus(
                    base, memConfig, &statusReg[0],
                    memConfig->deviceCfg->readStsRegWipCmd->command, context);

        if (result == INPH_XSPI_SUCCESS) {
            /* Read the status register 2 */
            result = Inph_XSPI_MemCmdReadStatus(
                base, memConfig, &statusReg[1],
                memConfig->deviceCfg->readStsRegQeCmd->command, context);

            if (result == INPH_XSPI_SUCCESS) {
                /* Set the QE bit, mostly bit 1 of SR2 */
                statusReg[1] |= memConfig->deviceCfg->stsRegQuadEnableMask;

                if (writeStsRegQeCmd == INPH_XSPI_WRSR_REG1_CMD) {
                    /* WRSR - 01h - writes SR1 and SR2 */
                    result = Inph_XSPI_MemCmdWriteStatus(
                        base, memConfig, statusReg,
                        writeStsRegQeCmd, context);
                }
                else {
                    /* WRSR - 31h - writes SR2 only*/
                    result = Inph_XSPI_MemCmdWriteStatus(
                        base, memConfig, &statusReg[1],
                        writeStsRegQeCmd, context);
                }
            }
        }
    }

    if (result == INPH_XSPI_SUCCESS) {
        /* Remove this, if it is a overkill, if required, add timeout  */
        uint8_t qeStatus = 1;
        uint32_t timeout = context->timeout;
        /* Read the status register to check if the QE bit is set */
        if (memConfig->deviceCfg->readStsRegQeCmd != NULL) {
            do {
                result = Inph_XSPI_MemCmdReadStatus(
                    base, memConfig, &qeStatus,
                    memConfig->deviceCfg->readStsRegQeCmd->command, context);

                if (result == INPH_XSPI_SUCCESS) {
                    /* Retrieve Quad Enable bit */
                    qeStatus = (qeStatus & 0x02) >> 1;
                }
                result = Inph_XSPI_Timeout(&timeout);
            } while ((qeStatus != 1) && (result != INPH_XSPI_ERROR_TIMEOUT));
        }
    }

    return result;
}

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
    uint8_t *status, uint8_t command, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    result = Inph_XSPI_TransmitCommand_Ext(
        base, command, false, INPH_XSPI_WIDTH_SINGLE, INPH_XSPI_DATA_RATE_SDR,
        NULL, 0, INPH_XSPI_WIDTH_SINGLE, INPH_XSPI_DATA_RATE_SDR,
        INPH_XSPI_ADDR_MASK_BYTE, memConfig->chipSelect,
        INPH_XSPI_TX_NOT_LAST_BYTE, context);

    if (result == INPH_XSPI_SUCCESS) {
        result = Inph_XSPI_SendDummyCycles(
            base, memConfig->deviceCfg->readStsRegQeCmd->dummyCycles);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_ReceiveDataBlocking_Ext(
                base, status, INPH_XSPI_READ_ONE_BYTE, INPH_XSPI_WIDTH_SINGLE,
                INPH_XSPI_DATA_RATE_SDR, context);
        }
    }

    return result;
}

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
inph_en_xspi_status_t Inph_XSPI_MemCmdWriteStatus(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    void const *status, uint8_t command, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    /* Check if there is a current transfer in progress */
    if (context->transferStatus != INPH_XSPI_READY)
        return INPH_XSPI_OPERATION_INPROGRESS;

    /* Each model has different write status command as shown below:
     * WRSR-31h-skip addr-skip dummy-Status data, 1 byte, set mask bit.
     * WRSR-01h-skip addr-skip dummy-Status data, 2 bytes, set mask bit.
     * */

    /* Send the write enable command before any write operation */
    result = Inph_XSPI_MemCmdWriteEnable(base, memConfig, context);

    if (result == INPH_XSPI_SUCCESS) {
        uint32_t size = (command == INPH_XSPI_WRSR_REG1_CMD) ?
                        INPH_XSPI_WRITE_TWO_BYTES:INPH_XSPI_WRITE_ONE_BYTE;
        result = Inph_XSPI_TransmitCommand_Ext(
            base, command, false, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, NULL, 0, INPH_XSPI_WIDTH_SINGLE,
            INPH_XSPI_DATA_RATE_SDR, INPH_XSPI_ADDR_MASK_BYTE,
            memConfig->chipSelect, INPH_XSPI_TX_NOT_LAST_BYTE, context);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_SendDummyCycles(
                base, memConfig->deviceCfg->writeStsRegQeCmd->dummyCycles);

            if (result == INPH_XSPI_SUCCESS) {
                result = Inph_XSPI_TransmitDataBlocking_Ext(
                    base, status, size,
                    memConfig->deviceCfg->writeStsRegQeCmd->dataWidth,
                    memConfig->deviceCfg->writeStsRegQeCmd->dataRate, context);

                if (result == INPH_XSPI_SUCCESS) {
                    /* Since it is blocking transmit call, keep polling to
                     * check if the page program is complete before initiating
                     * another write.*/
                    result = Inph_XSPI_MemIsReady(
                        base, memConfig, memConfig->deviceCfg->programTime,
                        context);
                }
            }
        }
    }

    return result;
}

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
                          inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if (memConfig->deviceCfg->chipEraseCmd != NULL) {
        /* Send the write enable command before any erase operation */
        result = Inph_XSPI_MemCmdWriteEnable(base, memConfig, context);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_TransmitCommand_Ext(
                base, memConfig->deviceCfg->chipEraseCmd->command, false,
                memConfig->deviceCfg->chipEraseCmd->cmdWidth,
                memConfig->deviceCfg->chipEraseCmd->cmdRate, NULL, 0,
                memConfig->deviceCfg->chipEraseCmd->addrWidth,
                memConfig->deviceCfg->chipEraseCmd->addrRate,
                INPH_XSPI_ADDR_MASK_WORD, memConfig->chipSelect,
                INPH_XSPI_TX_LAST_BYTE, context);
        }
    }

    return result;
}

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
    uint8_t const *sectorAddr, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((memConfig->deviceCfg->eraseCmd != NULL) && (sectorAddr != NULL)) {
        /* Send the write enable command before any erase operation */
        result = Inph_XSPI_MemCmdWriteEnable(base, memConfig, context);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_TransmitCommand_Ext(
                base, memConfig->deviceCfg->eraseCmd->command, false,
                memConfig->deviceCfg->eraseCmd->cmdWidth,
                memConfig->deviceCfg->eraseCmd->cmdRate, sectorAddr,
                memConfig->deviceCfg->numOfAddrBytes,
                memConfig->deviceCfg->eraseCmd->addrWidth,
                memConfig->deviceCfg->eraseCmd->addrRate,
                INPH_XSPI_ADDR_MASK_WORD, memConfig->chipSelect,
                INPH_XSPI_TX_LAST_BYTE, context);
        }
    }

    return result;
}

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
    uint8_t const *prgmAddr, uint8_t const *writeBuff, uint32_t size,
    inph_xspi_event_cb_t cmdCompleteCb, inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((memConfig == NULL) || (memConfig->deviceCfg->programCmd == NULL) ||
        (prgmAddr == NULL) || (size > memConfig->deviceCfg->programSize)) {
        return result;
    }

    /* Send the write enable command before any write operation */
    result = Inph_XSPI_MemCmdWriteEnable(base, memConfig, context);

    if (result == INPH_XSPI_SUCCESS) {
        /* Send page program command and memory addr to start programming */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, memConfig->deviceCfg->programCmd->command, false,
            memConfig->deviceCfg->programCmd->cmdWidth,
            memConfig->deviceCfg->programCmd->cmdRate, prgmAddr,
            memConfig->deviceCfg->numOfAddrBytes,
            memConfig->deviceCfg->programCmd->addrWidth,
            memConfig->deviceCfg->programCmd->addrRate,
            INPH_XSPI_ADDR_MASK_WORD, memConfig->chipSelect,
            INPH_XSPI_TX_NOT_LAST_BYTE, context);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_SendDummyCycles(
                base, memConfig->deviceCfg->programCmd->dummyCycles);

            if (result == INPH_XSPI_SUCCESS) {
                result = Inph_XSPI_TransmitData_Ext(
                    base, writeBuff, size,
                    memConfig->deviceCfg->programCmd->dataWidth,
                    memConfig->deviceCfg->programCmd->dataRate, cmdCompleteCb,
                    context);
            }
        }
    }

    return result;
}

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
    uint8_t const *readAddr, uint8_t *readBuff, uint32_t size,
    inph_xspi_event_cb_t cmdCompleteCb, inph_stc_xspi_context_t *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((memConfig == NULL) || (memConfig->deviceCfg->readCmd == NULL) ||
        (readAddr == NULL)) {
        return result;
    }

    /* Check if there is a current transfer in progress */
    if (context->transferStatus != INPH_XSPI_READY)
        return INPH_XSPI_OPERATION_INPROGRESS;

    /* Send read command */
    result = Inph_XSPI_TransmitCommand_Ext(
        base, memConfig->deviceCfg->readCmd->command, false,
        memConfig->deviceCfg->readCmd->cmdWidth,
        memConfig->deviceCfg->readCmd->cmdRate, readAddr,
        memConfig->deviceCfg->numOfAddrBytes,
        memConfig->deviceCfg->readCmd->addrWidth,
        memConfig->deviceCfg->readCmd->addrRate, INPH_XSPI_ADDR_MASK_WORD,
        memConfig->chipSelect, INPH_XSPI_TX_NOT_LAST_BYTE, context);

    if (result == INPH_XSPI_SUCCESS) {
        result = Inph_XSPI_SendDummyCycles(
            base, memConfig->deviceCfg->readCmd->dummyCycles);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_ReceiveData_Ext(
                base, readBuff, size,
                memConfig->deviceCfg->programCmd->dataWidth,
                memConfig->deviceCfg->programCmd->dataRate, cmdCompleteCb,
                context);
        }
    }

    return result;
}

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
                                    inph_stc_xspi_context_t *context)
{
    if (context != NULL) {
        context->memReadyPollDelay = pollTimeoutUs;
    }
}

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
inph_en_xspi_status_t
Inph_XSPI_MemIsReady(XSPI_Type *base,
                     inph_stc_xspi_mem_config_t const *memConfig,
                     uint32_t timeoutUs, inph_stc_xspi_context_t const *context)
{
    bool isBusy = Inph_XSPI_MemIsBusy(base, memConfig, context);
    uint32_t pollingDelayUs = 0;

#if 1
    UNUSED(pollingDelayUs);
    UNUSED(timeoutUs);

    /* Loop forever until timeout is implemented */
    while (isBusy) {
        isBusy = Inph_XSPI_MemIsBusy(base, memConfig, context);
    }

    return INPH_XSPI_SUCCESS;
#else

    /* Get the delay between polling */
    if (context->memReadyPollDelay > 0) {
        if (isBusy) {
            pollingDelayUs = (timeoutUs > context->memReadyPollDelay) ?
                              context->memReadyPollDelay : (uint16_t)timeoutUs;

            do {
                Inph_TIMER_MicroSec(pollingDelayUs);

                isBusy = Inph_XSPI_MemIsBusy(base, memConfig, context);
                timeoutUs = (timeoutUs > pollingDelayUs) ?
                                            (timeoutUs - pollingDelayUs) : 0;
            } while(isBusy && (timeoutUs > 0L));
        }
    }
    else {
        if (isBusy) {

            uint32_t delayMs = 0;
            uint32_t timeoutSlice = 0;
            uint32_t delayUs = 0;

            timeoutSlice = timeoutUs / TIMEOUT_SLICE_DIV;
            if (timeoutSlice > TIMEOUT_SLICE_MAX)
            {
                timeoutSlice = TIMEOUT_SLICE_MAX;
            }
            if (timeoutSlice == 0)
            {
                timeoutSlice = 1;
            }

            do {
                delayMs = timeoutSlice/1000;
                delayUs = timeoutSlice % 1000;

                Inph_TIMER_MilliSec(delayMs);
                Inph_TIMER_MicroSec(delayUs);

                isBusy = Inph_XSPI_MemIsBusy(base, memConfig, context);
                timeoutUs = (timeoutUs > timeoutSlice) ?
                                            (timeoutUs - timeoutSlice) : 0;
            } while(isBusy && (timeoutUs > 0L));
        }
    }

    return (isBusy ? INPH_XSPI_ERROR_TIMEOUT : INPH_XSPI_SUCCESS);
#endif
}

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
    bool *isQuadEnabled, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint8_t readStatus = 0U;

    if (memConfig != NULL) {
        result = Inph_XSPI_MemCmdReadStatus(
            base, memConfig, &readStatus,
            memConfig->deviceCfg->readStsRegQeCmd->command, context);

        if (result == INPH_XSPI_SUCCESS) {
            uint8_t qeMask = memConfig->deviceCfg->stsRegQuadEnableMask;
            *isQuadEnabled = (qeMask == (readStatus & qeMask));
        }
    }

    return result;
}

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
    uint32_t timeoutUs, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if (memConfig != NULL) {
        result = Inph_XSPI_MemQuadEnable(base, memConfig, context);

        if (result == INPH_XSPI_SUCCESS) {
            result = Inph_XSPI_MemIsReady(base, memConfig, timeoutUs, context);
        }
    }

    return result;
}

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
                  inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint8_t addrArray[4] = {0U};
    uint32_t readLen = 0;

    if ((memConfig == NULL) || (memConfig->deviceCfg->readCmd == NULL)) {
        return result;
    }

    /* Check if there is a current transfer in progress */
    if (context->transferStatus != INPH_XSPI_READY)
        return INPH_XSPI_OPERATION_INPROGRESS;

    /* Check if read address exceeds memory size */
    if ((readAddr + length) <= memConfig->deviceCfg->memSize) {
        while (length > 0) {
            /* Set the max # of bytes which can be read in one read operation */
            readLen = (length > INPH_XSPI_MAX_RX_COUNT)
                          ? (INPH_XSPI_MAX_RX_COUNT)
                          : length;

            /* Convert the addr to a byte array*/
            Inph_XSPI_UnPackBytes(readAddr, addrArray,
                                  memConfig->deviceCfg->numOfAddrBytes);

            /* Send read command */
            result = Inph_XSPI_TransmitCommand_Ext(
                base, memConfig->deviceCfg->readCmd->command, false,
                memConfig->deviceCfg->readCmd->cmdWidth,
                memConfig->deviceCfg->readCmd->cmdRate, addrArray,
                memConfig->deviceCfg->numOfAddrBytes,
                memConfig->deviceCfg->readCmd->addrWidth,
                memConfig->deviceCfg->readCmd->addrRate,
                INPH_XSPI_ADDR_MASK_WORD, memConfig->chipSelect,
                INPH_XSPI_TX_NOT_LAST_BYTE, context);

            if (result == INPH_XSPI_SUCCESS) {
                result = Inph_XSPI_SendDummyCycles(
                    base, memConfig->deviceCfg->readCmd->dummyCycles);

                if (result == INPH_XSPI_SUCCESS) {
                    result = Inph_XSPI_ReceiveDataBlocking_Ext(
                        base, rxBuffer, readLen,
                        memConfig->deviceCfg->readCmd->dataWidth,
                        memConfig->deviceCfg->readCmd->dataRate, context);

                    /* Prep for next read cycle */
                    length -= readLen; // remaining bytes to be read
                    readAddr += readLen;
                    rxBuffer = (uint8_t *)rxBuffer + readLen;
                }
            }

            /* If any of the operations above fails the break the read loop */
            if (result != INPH_XSPI_SUCCESS) {
                break;
            }
        }
    }

    return result;
}

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
                   uint32_t length, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint8_t addrArray[4] = {0U};
    uint32_t writeLen = 0;
    uint32_t offset = 0;
    uint32_t pageSize;

    if ((memConfig == NULL) || (memConfig->deviceCfg->programCmd == NULL)) {
        return result;
    }

    /* Get the page size of the external memory device */
    pageSize = memConfig->deviceCfg->programSize;

    /* Check if write address exceeds memory size */
    if ((writeAddr + length) <= memConfig->deviceCfg->memSize) {

        /* The address might not be aligned with start of page, calculate
         * offset from start of page */

        /* Write length might not be page size aligned, calculate offset
         * */
        offset = writeAddr % pageSize; // if 8194 % 256 = 2, length =150
        // (2+150) < 256 --> write entire length or length = 500-> (2+502) >
        // 256, write (256 - 2)
        writeLen =
            (offset + length) < pageSize ? length : (pageSize - offset); //

        while (length > 0) {
            result = INPH_XSPI_SUCCESS;
            /* The address might not be aligned with start of page, calculate
             * offset from start of page boundary to start writing from.
             * */
            offset = writeAddr % pageSize;

            /* calculate bytes to be written in each cycle, the write length
             * should be pageSize or less and should fall within page boundary
             * for each write cycle
             */
            writeLen =
                ((offset + length) < pageSize) ? length : (pageSize - offset);

            /* Convert the addr to a byte array*/
            Inph_XSPI_UnPackBytes(writeAddr, addrArray,
                                  memConfig->deviceCfg->numOfAddrBytes);

            /* If the connected device does not require write enable, skip it */
            if (memConfig->deviceCfg->writeEnCmd != NULL) {
                /* Send the write enable command before any write operation */
                result = Inph_XSPI_MemCmdWriteEnable(base, memConfig, context);
            }

            if (result == INPH_XSPI_SUCCESS) {
                /* Send page program cmd and memory addr to start programming */
                result = Inph_XSPI_TransmitCommand_Ext(
                    base, memConfig->deviceCfg->programCmd->command, false,
                    memConfig->deviceCfg->programCmd->cmdWidth,
                    memConfig->deviceCfg->programCmd->cmdRate, addrArray,
                    memConfig->deviceCfg->numOfAddrBytes,
                    memConfig->deviceCfg->programCmd->addrWidth,
                    memConfig->deviceCfg->programCmd->addrRate,
                    INPH_XSPI_ADDR_MASK_WORD, memConfig->chipSelect,
                    INPH_XSPI_TX_NOT_LAST_BYTE, context);

                if (result == INPH_XSPI_SUCCESS) {
                    result = Inph_XSPI_SendDummyCycles(
                        base, memConfig->deviceCfg->programCmd->dummyCycles);

                    if (result == INPH_XSPI_SUCCESS) {
                        result = Inph_XSPI_TransmitDataBlocking_Ext(
                            base, txBuffer, writeLen,
                            memConfig->deviceCfg->programCmd->dataWidth,
                            memConfig->deviceCfg->programCmd->dataRate,
                            context);
                    }

                    if (result == INPH_XSPI_SUCCESS) {
                        /* If the connected device does not have a read status
                         * command, then skip it.
                         * */
                        if (memConfig->deviceCfg->readStsRegWipCmd != NULL) {
                            /* Since it is blocking transmit call, keep polling
                             * to check if the page program is complete before
                             * initiating another write.*/
                            result = Inph_XSPI_MemIsReady(
                                base, memConfig,
                                memConfig->deviceCfg->programTime, context);
                        }
                    }
                    /* Prep for next write cycle */
                    length -= writeLen; // remaining bytes to be written
                    writeAddr += writeLen;
                    txBuffer = (uint8_t *)txBuffer + writeLen;
                }
            }

            /* If any of the operations above fails the break the read loop */
            if (result != INPH_XSPI_SUCCESS) {
                break;
            }
        }
    }

    return result;
}

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
inph_en_xspi_status_t Inph_XSPI_MemEraseSector(
    XSPI_Type *base, inph_stc_xspi_mem_config_t const *memConfig,
    uint32_t eraseAddr, uint32_t length, inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;
    uint8_t addrArray[4] = {0U};
    uint32_t eraseSectorSize = 0;
    uint32_t eraseStartAddr = eraseAddr;
    uint32_t eraseEndAddr = eraseAddr + length;

    if ((memConfig->deviceCfg->eraseCmd != NULL)) {
        /* Check if the address exceeds the memory size */
        if (eraseEndAddr <= memConfig->deviceCfg->memSize) {
            /* Get the erase sector size */
            eraseSectorSize = memConfig->deviceCfg->eraseSize;

            /* If the erase start address is in the middle of the sector/block,
             * align the address to the beginning of the sector
             */
            if ((eraseStartAddr % eraseSectorSize) != 0) {
                eraseStartAddr =
                    (eraseStartAddr / eraseSectorSize) * eraseSectorSize;
            }

            while (eraseStartAddr <= eraseEndAddr) {
                /* Convert the addr to a byte array*/
                Inph_XSPI_UnPackBytes(eraseStartAddr, addrArray,
                                      memConfig->deviceCfg->numOfAddrBytes);

                result = Inph_XSPI_MemCmdSectorErase(base, memConfig, addrArray,
                                                     context);

                if (result == INPH_XSPI_SUCCESS) {
                    /* Keep polling until the erase is complete or the
                     * operation exceeds timeout */
                    result = Inph_XSPI_MemIsReady(
                        base, memConfig, memConfig->deviceCfg->eraseTime,
                        context);
                }

                /* If any of the operations above fails the break the loop */
                if (result != INPH_XSPI_SUCCESS) {
                    break;
                }

                eraseStartAddr += memConfig->deviceCfg->eraseSize;
            }
        }
    }

    return result;
}

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
                       inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if (memConfig != NULL) {
        result = Inph_XSPI_MemCmdChipErase(base, memConfig, context);

        if (result == INPH_XSPI_SUCCESS) {
            /* Keep polling until the chip erase is complete or the
             * operation exceeds timeout */
            result = Inph_XSPI_MemIsReady(
                base, memConfig, memConfig->deviceCfg->chipEraseTime, context);
        }
    }

    return result;
}

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
                   inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((memConfig != NULL) && (memConfig->deviceCfg->resetEnCmd != NULL) &&
        (memConfig->deviceCfg->resetCmd != NULL)) {
        /* Get the Reset Enable command */
        inph_stc_xspi_mem_cmd_t *resetEn = memConfig->deviceCfg->resetEnCmd;

        /* Reset enable has only command phase, hence cmdParam is NULL */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, (uint8_t)resetEn->command, false, resetEn->cmdWidth,
            resetEn->cmdRate, NULL, 0, resetEn->addrWidth, resetEn->addrRate,
            INPH_XSPI_ADDR_MASK_BYTE, memConfig->chipSelect,
            INPH_XSPI_TX_LAST_BYTE, context);

        if (result == INPH_XSPI_SUCCESS) {
            /* Get the Reset Command */
            inph_stc_xspi_mem_cmd_t *reset = memConfig->deviceCfg->resetCmd;

            /* Reset has only command phase, hence cmdParam is NULL */
            result = Inph_XSPI_TransmitCommand_Ext(
                base, (uint8_t)reset->command, false, resetEn->cmdWidth,
                resetEn->cmdRate, NULL, 0, resetEn->addrWidth,
                resetEn->addrRate, INPH_XSPI_ADDR_MASK_BYTE,
                memConfig->chipSelect, INPH_XSPI_TX_LAST_BYTE, context);
        }
    }
    return result;
}

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
                           inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((memConfig != NULL) && (memConfig->deviceCfg->quadEnterCmd != NULL)) {
        /* Get Enter Quad Mode command */
        inph_stc_xspi_mem_cmd_t *quadEnter = memConfig->deviceCfg->quadEnterCmd;

        /* Enter Quad Mode has only command phase, hence cmdParam is NULL */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, (uint8_t)quadEnter->command, false, quadEnter->cmdWidth,
            quadEnter->cmdRate, NULL, 0, quadEnter->addrWidth,
            quadEnter->addrRate, INPH_XSPI_ADDR_MASK_BYTE,
            memConfig->chipSelect, INPH_XSPI_TX_LAST_BYTE, context);
    }
    return result;
}

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
                          inph_stc_xspi_context_t const *context)
{
    inph_en_xspi_status_t result = INPH_XSPI_ERROR_INVALID_PARAMETER;

    if ((memConfig != NULL) && (memConfig->deviceCfg->quadExitCmd != NULL)) {
        /* Get Exit Quad Mode command */
        inph_stc_xspi_mem_cmd_t *quadExit = memConfig->deviceCfg->quadExitCmd;

        /* Exit Quad Mode has only command phase, hence cmdParam is NULL */
        result = Inph_XSPI_TransmitCommand_Ext(
            base, (uint8_t)quadExit->command, false, quadExit->cmdWidth,
            quadExit->cmdRate, NULL, 0, quadExit->addrWidth, quadExit->addrRate,
            INPH_XSPI_ADDR_MASK_BYTE, memConfig->chipSelect,
            INPH_XSPI_TX_LAST_BYTE, context);
    }
    return result;
}

#if defined(__cplusplus)
}
#endif
