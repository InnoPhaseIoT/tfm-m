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

#include "memdev_cfg.h"

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_readCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_FAST_RD_QUAD_OUTPUT_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_PRESENT,
     /* Presence of address phase. */
    .addrMask = INPH_XSPI_ADDR_MASK_BYTE,
    /* There are no mode bits, as the phase is skipped. */
    .modeBits = 0U,
    /* There are no mode duration, as the phase is skipped. */
    .modeDuration = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    /* Requires 8 dummy clocks i.e., 1 dummy byte sent in quad mode. */
    .dummyCycles = 8,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_QUAD,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_programCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_QUAD_INPUT_PAGE_PGM_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_PRESENT,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_QUAD,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_1x_readCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_RD_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_PRESENT,
    /* There is no mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    /* Requires 4 dummy clocks i.e., 2 dummy bytes sent in quad mode. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_2x_readCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_FAST_READ_DUAL_OUTPUT_1_1_2_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_PRESENT,
    /* There is no mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    /* Requires 8 dummy clocks i.e., 1 dummy byte sent in dual mode. */
    .dummyCycles = 8,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_DUAL,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_1x_programCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_PAGE_PGM_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_PRESENT,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_suspendCmd =
{
    /* The 8-bit command doe Suspend command. */
    .command = INPH_XSPI_ERASE_PGM_SUSPEND_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* There is no address transferred, its just placeholder. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
     /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* There is no data transferred, its just placeholder. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_resumeCmd =
{
    /* The 8-bit command doe Suspend command. */
    .command = INPH_XSPI_ERASE_PGM_RESUME_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* There is no address transferred, its just placeholder. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
     /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* There is no data transferred, its just placeholder. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_writeEnCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_WRITE_ENABLE_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* There is no address transferred, its just placeholder. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
     /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* There is no data transferred, its just placeholder. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_writeDisCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_WRITE_DISABLE_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* There is no address transferred, its just placeholder. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* There is no data transferred, its just placeholder. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_eraseCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_SECTOR_4K_ERASE_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_PRESENT,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
    /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /*  There is no data transferred, its just placeholder. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_chipEraseCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_CHIP_ERASE_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegQeCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_READ_STATUS_REG2_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegWipCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_READ_STATUS_REG1_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

/* For the Flash model in FPGA daughter card */
const inph_stc_xspi_mem_cmd_t GD25Q64E_3byteaddr_SlaveSlot_0_writeStsRegQeCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_WRITE_STATUS_REG2_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

/* For the Flash model in HeLite ASIC */
const inph_stc_xspi_mem_cmd_t GD25LQ64E_3byteaddr_SlaveSlot_0_writeStsRegQeCmd =
{
    /* The 8-bit command. 1 x I/O read command. */
    .command = INPH_XSPI_WRITE_STATUS_REG1_REG2_CMD,
    /* The width of the command transfer. */
    .cmdWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of Command. */
    .cmdRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of command phase. */
    .cmdPresence = INPH_XSPI_PHASE_PRESENT,
    /* The width of the address transfer. */
    .addrWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the address. */
    .addrRate = INPH_XSPI_DATA_RATE_SDR,
    /* Presence of address phase. */
    .addrPresence = INPH_XSPI_PHASE_SKIP,
    /* No mode present. */
    .modeBits = 0U,
    /* The width of the mode command transfer. */
    .modeWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the mode. */
    .modeRate = INPH_XSPI_DATA_RATE_SDR,
    /* presence of Mode phase */
    .modePresence = INPH_XSPI_PHASE_SKIP,
    /* The number of dummy cycles. A zero value suggests no dummy cycles. */
    .dummyCycles = INPH_XSPI_DUMMY_NONE,
     /* Presence of dummy phase */
    .dummyCyclesPresence = INPH_XSPI_PHASE_SKIP,
    /* The width of the data transfer. */
    .dataWidth = INPH_XSPI_WIDTH_SINGLE,
    /* Data rate of the data */
    .dataRate = INPH_XSPI_DATA_RATE_SDR
};

/* GD25Q64E (used in FPGA setup) and GD25LQ64E (used in Helium ASIC) have
 * different WRSR commands, rest of the commands configurations match.
 * */
const inph_stc_xspi_mem_device_cfg_t deviceCfg_GD25Q64E_3byteaddr_SlaveSlot_0 =
{
    /* Specifies the number of address bytes used by the memory slave device. */
    .numOfAddrBytes = 0x03U,
    /* The size of the memory. */
    .memSize = 0x800000U,
    /* Specifies the Read command. */
    .readCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_readCmd,
    /* Specifies if there is page boundary limitations for reads. NOR flash
     * has no such limitations, so set to 0 */
     .pageReadBoundary = false,
    /* Specifies the Suspend command. */
    .suspendCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_suspendCmd,
    /* Specifies the Resume command. */
    .resumeCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_resumeCmd,
    /* Specifies the Write Enable command. */
    .writeEnCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_writeEnCmd,
    /* Specifies the Write Disable command. */
    .writeDisCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_writeDisCmd,
    /* Specifies the Erase command. */
    /* Corresponds to 4K sector erase command */
    .eraseCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_eraseCmd,
    /* Specifies the sector size of each erase. */
    /* 64KB block erase */
    .eraseSize = 0x1000,/*0x00010000U */
    /* Specifies the Chip Erase command. */
    .chipEraseCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_chipEraseCmd,
    /* Specifies the Program command. */
    .programCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_programCmd,
    /* Specifies the page size for programming. */
    .programSize = 0x00000100U,
    /* Specifies the command to read the QE-containing status register. */
    .readStsRegQeCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegQeCmd,
    /* Specifies the command to read the WIP-containing status register. */
    .readStsRegWipCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegWipCmd,
    /* Specifies the command to write into the QE-containing status register. */
    .writeStsRegQeCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_writeStsRegQeCmd,
    /* Specifies the Enter Quad command. */
    .quadEnterCmd = NULL,
    /* Specifies the Exit Quad command. */
    .quadExitCmd = NULL,
    /* Specifies the Reset Enable command */
    .resetEnCmd = NULL,
    /* Specifies the Reset command */
    .resetCmd = NULL,
    /* The mask for the status register. */
    .stsRegBusyMask = INPH_XSPI_BUSY_BIT_0_OF_SR_1_Msk,
    /* The mask for the status register. */
    .stsRegQuadEnableMask = INPH_XSPI_QE_BIT_1_OF_SR_2_Msk,
    /* The typical time for the erase type-1 cycle-time in ms. */
    /* 4K block erase is chosen, typical is 40ms and max time is 300ms-500ms*/
    .eraseTime = INPH_XSPI_SECTOR_4K_ERASE_TYPICAL_TIME_45MS,
    /* The time for the chip-erase cycle-time in ms.(16s-80s) */
    .chipEraseTime = INPH_XSPI_CHIP_ERASE_TYPICAL_TIME_20S,
    /* The time for the page-program cycle-time in us (400us - 4000us) */
    .programTime = INPH_XSPI_PROG_TIME_MAX_3000US
};

/* GD25Q64E (used in FPGA setup) and GD25LQ64E (used in Helium ASIC) have
 * different WRSR commands, rest of the commands configurations match.
 * */
const inph_stc_xspi_mem_device_cfg_t deviceCfg_GD25LQ64E_3byteaddr_SlaveSlot_0 =
{
    /* Specifies the number of address bytes used by the memory slave device. */
    .numOfAddrBytes = 0x03U,
    /* The size of the memory. */
    .memSize = 0x800000U,
    /* Specifies the Read command. */
    .readCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_readCmd,
    /* Specifies if there is page boundary limitations for reads. NOR flash
     * has no such limitations, so set to 0 */
     .pageReadBoundary = false,
    /* Specifies the Suspend command. */
    .suspendCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_suspendCmd,
    /* Specifies the Resume command. */
    .resumeCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_resumeCmd,
    /* Specifies the Write Enable command. */
    .writeEnCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_writeEnCmd,
    /* Specifies the Write Disable command. */
    .writeDisCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_writeDisCmd,
    /* Specifies the Erase command. */
    /* Corresponds to 4K sector erase command */
    .eraseCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_eraseCmd,
    /* Specifies the sector size of each erase. */
    /* 64KB block erase */
    .eraseSize = 0x1000,/*0x00010000U */
    /* Specifies the Chip Erase command. */
    .chipEraseCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_chipEraseCmd,
    /* Specifies the Program command. */
    .programCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_programCmd,
    /* Specifies the page size for programming. */
    .programSize = 0x00000100U,
    /* Specifies the command to read the QE-containing status register. */
    .readStsRegQeCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegQeCmd,
    /* Specifies the command to read the WIP-containing status register. */
    .readStsRegWipCmd = (inph_stc_xspi_mem_cmd_t*)&GD25Q64E_3byteaddr_SlaveSlot_0_readStsRegWipCmd,
    /* Specifies the command to write into the QE-containing status register. */
    .writeStsRegQeCmd = (inph_stc_xspi_mem_cmd_t*)&GD25LQ64E_3byteaddr_SlaveSlot_0_writeStsRegQeCmd,
    /* Specifies the Enter Quad command. */
    .quadEnterCmd = NULL,
    /* Specifies the Exit Quad command. */
    .quadExitCmd = NULL,
    /* Specifies the Reset Enable command */
    .resetEnCmd = NULL,
    /* Specifies the Reset command */
    .resetCmd = NULL,
    /* The mask for the status register. */
    .stsRegBusyMask = INPH_XSPI_BUSY_BIT_0_OF_SR_1_Msk,
    /* The mask for the status register. */
    .stsRegQuadEnableMask = INPH_XSPI_QE_BIT_1_OF_SR_2_Msk,
    /* The typical time for the erase type-1 cycle-time in ms. */
    /* 4K block erase is chosen, typical is 40ms and max time is 300ms-500ms*/
    .eraseTime = INPH_XSPI_SECTOR_4K_ERASE_TYPICAL_TIME_45MS,
    /* The time for the chip-erase cycle-time in ms.(16s-80s) */
    .chipEraseTime = INPH_XSPI_CHIP_ERASE_TYPICAL_TIME_20S,
    /* The time for the page-program cycle-time in us (400us - 4000us) */
    .programTime = INPH_XSPI_PROG_TIME_MAX_3000US
};

const inph_stc_xspi_mem_config_t GD25Q64E_3byteaddr_SlaveSlot_0 =
{
    /* Determines the slot number where the memory device is placed. */
#ifdef xSPI1_PSRAM
    .chipSelect = INPH_XSPI_CHIP_SELECT_1,
#else
    .chipSelect = INPH_XSPI_CHIP_SELECT_0,
#endif
    /* Flags. */
    .flags = INPH_XSPI_FLAG_MEMORY_MAPPED | INPH_XSPI_FLAG_WRITE_ENABLE,
    /* The data-line selection options for a slave device. */
    .dataSelect = INPH_XSPI_DATA_SEL0,
    /* The base address the memory device is mapped to in the T3 memory map.
    Valid when the memory-mapped mode is enabled. */
    .baseAddress = 0x0000000U,
    /* The size allocated in the memory map, for the memory slave device.
    The size is allocated from the base address.
    Valid when the memory mapped mode is enabled. */
    /* Half for XIP and the other half for user space */
    .memMappedSize = 0x400000U,
    /* If this memory device is one of the devices in the dual quad SPI configuration.
    Valid when the memory mapped mode is enabled. */
    .dualQuadSlots = 0,
    /* The configuration of the device. */
    .deviceCfg = (inph_stc_xspi_mem_device_cfg_t*)&deviceCfg_GD25LQ64E_3byteaddr_SlaveSlot_0
};
