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

#ifndef INPH_XSPI_REGS_H
#define INPH_XSPI_REGS_H

#include "inph_utils.h"

/* parameter macros  */
#define CDC_TYPE 0
#define SRAM_IMPL 0
#define AIP_IMPL 0
#define AIR_TYPE 0
#define AIP_AW 2
#define ADDR_DEC_N 1
#define AIP_ID_W 1
#define ACFG_IMPL 0
#define ACFG_ROM_AW 2
#define DMA_IMPL 0
#define DMA_TYPE 0
#define DMA_AW 2
#define DMA_ID_W 1
#define DQ_WIDTH 4
#define SPI_CS_W 1
#define WR_FIFO_AW 2
#define RD_FIFO_AW 2
#define CFG_FIFO_AW 2
#define GPIO_DW 1

/*block : xspi_mc */

/*section : CSR */

/*section : registers */

/*  GLBLCTRL DESCRIPTION :Global Control */
typedef union {
    struct {
        uint32_t AutoCfgRestart : 1;               /*0 SW=rw HW=ro 0x0 */

        uint32_t resv1 : 15;
        uint32_t DMAEnable : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;


}xspimc_GLBLCTRL;

/*  SPICLKCFG DESCRIPTION :SPI Clock Configuration */
typedef union {
    struct {
        uint32_t Clockperiod : 8;               /*0:7 SW=rw HW=ro 0xF */
        uint32_t MinCSLow : 8;               /*8:15 SW=rw HW=ro 0x7 */
        uint32_t Transmitdataon : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t Clockpolarity : 1;               /*17 SW=rw HW=ro 0x0 */
        
        uint32_t resv18 : 6;
        uint32_t Samplepoint : 8;               /*24:31 SW=rw HW=ro 0xF */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPICLKCFG;

/*  MINCSHIGH DESCRIPTION :Minimum CS High */
typedef union {
    struct {
        uint32_t MinCSHigh : 8;               /*0:7 SW=rw HW=ro 0x0 */
        uint32_t resv8 : 24;
    } bf;
    uint32_t  dw;
    
    
}xspimc_MINCSHIGH;

/*  FIFOSTS DESCRIPTION :FIFO Status */
typedef union {
    struct {
        uint32_t FIFOFIll : 16;               /*0:15 SW=ro HW=ro 0x0 */
        uint32_t EMPTY : 1;               /*16 SW=ro HW=ro 0x1 */
        uint32_t FULL : 1;               /*17 SW=ro HW=ro 0x0 */
        uint32_t resv18 : 14;
    } bf;
    uint32_t  dw;
    
    
}xspimc_FIFOSTS;

/*  SPISTS DESCRIPTION :FIFO Status */
typedef union {
    struct {
        uint32_t Enabled : 1;               /*0 SW=ro HW=ro 0x1 */
        
        uint32_t resv1 : 15;
        uint32_t Busy : 1;               /*16 SW=ro HW=ro 0x0 */
        uint32_t ReadFIFOStatus : 1;               /*17 SW=ro HW=ro 0x0 */
        uint32_t WriteFIFOStatus : 1;               /*18 SW=ro HW=ro 0x1 */
        uint32_t ReadFIFOError : 1;               /*19 SW=rw HW=ro 0x0 */
        uint32_t WriteFIFOError : 1;               /*20 SW=rw HW=ro 0x0 */
        uint32_t resv21 : 11;
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPISTS;

/*  IRQCTRL DESCRIPTION :IRQ Control */
typedef union {
    struct {
        uint32_t NotBusyIRQEnable : 1;               /*0 SW=rw HW=ro 0x0 */
        uint32_t ReadFIFOFillIRQEnable : 1;               /*1 SW=rw HW=ro 0x0 */
        uint32_t WriteFIFOFillIRQEnable : 1;               /*2 SW=rw HW=ro 0x0 */
        uint32_t ReadFIFOErrorIRQEnable : 1;               /*3 SW=rw HW=ro 0x0 */
        uint32_t WriteFIFOErrorIRQEnable : 1;               /*4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t FIFOBoundary : 3;               /*8:10 SW=rw HW=ro 0x0 */
        
        uint32_t resv11 : 5;
        uint32_t DMAIdleIRQEnable : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t DMAIRQEnable : 1;               /*17 SW=rw HW=ro 0x0 */
        uint32_t DMAErrorIRQEnable : 1;               /*18 SW=rw HW=ro 0x0 */
        uint32_t resv19 : 13;
    } bf;
    uint32_t  dw;
    
    
}xspimc_IRQCTRL;

/*  SPICMD DESCRIPTION :SPI Command */
typedef union {
    struct {
        uint32_t Command : 16;               /*0:15 SW=rw HW=ro 0x0 */
        uint32_t resv16 : 16;
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPICMD;

/*  SPICMDATTR DESCRIPTION :SPI Command Attributes */
typedef union {
    struct {
        uint32_t Duration : 4;               /*0:3 SW=rw HW=ro 0x7 */
        
        uint32_t resv4 : 4;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 1;
        uint32_t HyperRAM : 1;               /*15 SW=rw HW=ro 0x0 */
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x0 */
        
        uint32_t resv17 : 14;
        uint32_t WriteErase : 1;               /*31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPICMDATTR;

/*  SPIADDR DESCRIPTION :SPI Address */
typedef union {
    struct {
        uint32_t Address : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIADDR;

/*  SPIADDRATTR DESCRIPTION :SPI Address Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x17 */
        
        uint32_t resv5 : 3;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 2;
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t Mask : 2;               /*17:18 SW=rw HW=ro 0x3 */
        uint32_t resv19 : 13;
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIADDRATTR;

/*  SPICS DESCRIPTION :SPI Chip Select */
typedef union {
    struct {
        uint32_t ChipSelect : 32;               /*0:31 SW=rw HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPICS;

/*  SPIDUMMYATTR DESCRIPTION :SPI Dummy Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t Skip : 1;               /*8 SW=rw HW=ro 0x0 */
        
        uint32_t resv9 : 7;
        uint32_t WL : 5;               /*16:20 SW=rw HW=ro 0x0 */
        
        uint32_t resv21 : 3;
        uint32_t NoWL : 1;               /*24 SW=rw HW=ro 0x1 */
        uint32_t DynWL : 1;               /*25 SW=rw HW=ro 0x0 */
        uint32_t resv26 : 6;
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIDUMMYATTR;

/*  AIPHOLDOFFTIME DESCRIPTION :AIP hold off time */
typedef union {
    struct {
        uint32_t AIPholdofftime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPHOLDOFFTIME;

/*  AIPHOLDOFFSEL DESCRIPTION :AIP hold off select */
typedef union {
    struct {
        uint32_t AIPwindows : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPHOLDOFFSEL;

/*  AIPHOLDOFFCTRL DESCRIPTION :AIP hold off control */
typedef union {
    struct {
        uint32_t AIPholdoffcontrol : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPHOLDOFFCTRL;

/*  SPIDATASIZE DESCRIPTION :SPI Data Size */
typedef union {
    struct {
        uint32_t Size : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIDATASIZE;

/*  SPIDATAATTR DESCRIPTION :SPI Data Attributes */
typedef union {
    struct {
        uint32_t Mode : 4;               /*0:3 SW=rw HW=ro 0x0 */
        uint32_t DDRMode : 1;               /*4 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*5 SW=rw HW=ro 0x0 */
        uint32_t DQS : 1;               /*6 SW=rw HW=ro 0x0 */
        uint32_t FlipBytes : 1;               /*7 SW=rw HW=ro 0x0 */
        uint32_t Skip : 1;               /*8 SW=rw HW=ro 0x0 */
        
        uint32_t resv9 : 7;
        uint32_t Direction : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIDATAATTR;

/*  SPITXDATA DESCRIPTION :SPI Transmit Data */
typedef union {
    struct {
        uint32_t Data : 32;               /*0:31 SW=wo HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPITXDATA;

/*  SPIRXDATA DESCRIPTION :SPI Receive Data */
typedef union {
    struct {
        uint32_t Data : 32;               /*0:31 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIRXDATA;

/*  SPIMODEBITS DESCRIPTION :SPI Mode Bits */
typedef union {
    struct {
        uint32_t Bits : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIMODEBITS;

/*  SPIMODEBITSATTR DESCRIPTION :SPI Mode Bits Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x0 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 2;
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x1 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;
    
    
}xspimc_SPIMODEBITSATTR;

/*section : AIPwindow0 */
/*  AIPWINDOW0 DESCRIPTION :*/

/*  AIPCTRL DESCRIPTION :AIP Control */
typedef union {
    struct {
        uint32_t AIPModeEnable : 1;               /*0 SW=rw HW=ro 0x1 */
        uint32_t Busy : 1;               /*1 SW=ro HW=ro 0x0 */
        
        uint32_t resv2 : 6;
        uint32_t SusRes : 1;               /*8 SW=rw HW=ro 0x0 */
        uint32_t Update : 1;               /*9 SW=rw HW=ro 0x0 */
        uint32_t resv10 : 22;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPCTRL;

/*  AIPACCB DESCRIPTION :New AIP access boundary */
typedef union {
    struct {
        uint32_t AIPaccessboundary : 5;               /*0:4 SW=rw HW=ro 0x1F */
        uint32_t resv5 : 27;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPACCB;

/*  AIPSIZE DESCRIPTION :New AIP Size */
typedef union {
    struct {
        uint32_t AIPsize : 32;               /*0:31 SW=rw HW=ro 0x1FFFFF */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPSIZE;

/*  AIPWINADDR DESCRIPTION :New AIP window address */
typedef union {
    struct {
        uint32_t AIPwindowaddress : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPWINADDR;

/*  AIPCMD DESCRIPTION :New AIP Command */
typedef union {
    struct {
        uint32_t RCommand : 16;               /*0:15 SW=rw HW=ro 0xB00 */
        uint32_t WCommand : 16;               /*16:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPCMD;

/*  AIPCMDATTR DESCRIPTION :New AIP Command Attributes */
typedef union {
    struct {
        uint32_t Duration : 3;               /*0:2 SW=rw HW=ro 0x7 */
        
        uint32_t resv3 : 5;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t Writesupport : 1;               /*14 SW=rw HW=ro 0x0 */
        uint32_t HypeRAMcommand : 1;               /*15 SW=rw HW=ro 0x0 */
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPCMDATTR;

/*  AIPDIECMD DESCRIPTION :New AIP Die Select Command */
typedef union {
    struct {
        uint32_t Dieselectcmd : 16;               /*0:15 SW=rw HW=ro 0x0 */
        uint32_t Addrbitsindie : 5;               /*16:20 SW=rw HW=ro 0x0 */
        uint32_t resv21 : 11;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPDIECMD;

/*  AIPDIEATTR DESCRIPTION :New AIP Die Select Attributes */
typedef union {
    struct {
        uint32_t Commandduration : 4;               /*0:3 SW=rw HW=ro 0x7 */
        
        uint32_t resv4 : 4;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t Dieenable : 1;               /*14 SW=rw HW=ro 0x0 */
        
        uint32_t resv15 : 1;
        uint32_t Addresswidth : 2;               /*16:17 SW=rw HW=ro 0x3 */
        uint32_t resv18 : 14;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPDIEATTR;

/*  AIPADRBASE DESCRIPTION :New AIP Base_Address */
typedef union {
    struct {
        uint32_t BaseAddress : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPADRBASE;

/*  AIPADRATTR DESCRIPTION :New AIP Address Attributes */
typedef union {
    struct {
        
        uint32_t resv0 : 8;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 2;
        uint32_t Width : 2;               /*16:17 SW=rw HW=ro 0x0 */
        uint32_t Mask : 2;               /*18:19 SW=rw HW=ro 0x3 */
        uint32_t resv20 : 12;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPADRATTR;

/*  AIPCS DESCRIPTION :New AIP Chip Select */
typedef union {
    struct {
        uint32_t ChipSelect : 32;               /*0:31 SW=rw HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPCS;

/*  AIPDIEPAGESTATE DESCRIPTION :AIP State */
typedef union {
    struct {
        uint32_t SelectedPage : 23;               /*0:22 SW=rw HW=ro 0x0 */
        uint32_t Pageselected : 1;               /*23 SW=rw HW=ro 0x0 */
        uint32_t SelectedDie : 7;               /*24:30 SW=rw HW=ro 0x0 */
        uint32_t DieSelected : 1;               /*31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPDIEPAGESTATE;

/*  AIPDUMMYATTR DESCRIPTION :New AIP Dummy Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x7 */
        
        uint32_t resv5 : 3;
        uint32_t Skip : 1;               /*8 SW=rw HW=ro 0x0 */
        
        uint32_t resv9 : 7;
        uint32_t WriteLatency : 5;               /*16:20 SW=rw HW=ro 0x0 */
        
        uint32_t resv21 : 3;
        uint32_t Nowritelatency : 1;               /*24 SW=rw HW=ro 0x1 */
        uint32_t Dynwritelatency : 1;               /*25 SW=rw HW=ro 0x0 */
        uint32_t resv26 : 6;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPDUMMYATTR;

/*  AIPSUSRESCMD DESCRIPTION :New AIP Suspend/resume commands */
typedef union {
    struct {
        uint32_t SusCommand : 16;               /*0:15 SW=rw HW=ro 0x0 */
        uint32_t ResCommand : 16;               /*16:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPSUSRESCMD;

/*  AIPSUSRESATTR DESCRIPTION :New AIP Suspend/Resume attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x0 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t resv14 : 18;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPSUSRESATTR;

/*  AIPSUSTIME DESCRIPTION :New AIP Suspend Time */
typedef union {
    struct {
        uint32_t Suspendtime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPSUSTIME;

/*  AIPDATATTR DESCRIPTION :New AIP Data attributes */
typedef union {
    struct {
        uint32_t Mode : 4;               /*0:3 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*4 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*5 SW=rw HW=ro 0x0 */
        uint32_t DQS : 1;               /*6 SW=rw HW=ro 0x0 */
        uint32_t FlipBytes : 1;               /*7 SW=rw HW=ro 0x0 */
        uint32_t resv8 : 24;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPDATATTR;

/*  AIPRESTIME DESCRIPTION :New AIP Resume Time */
typedef union {
    struct {
        uint32_t Resumetime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPRESTIME;

/*  AIPSUSRESTIME DESCRIPTION :New AIP Suspend to Resume Time */
typedef union {
    struct {
        uint32_t Sustorestime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPSUSRESTIME;

/*  AIPRESSUSTIME DESCRIPTION :New AIP Resume to Suspend Time */
typedef union {
    struct {
        uint32_t Restosustime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPRESSUSTIME;

/*  AIPMODEBITS DESCRIPTION :New AIP Mode Bits */
typedef union {
    struct {
        uint32_t Bits : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPMODEBITS;

/*  AIPMODEBITSATTR DESCRIPTION :New AIP Mode Bits Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x0 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 2;
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x1 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPMODEBITSATTR;

/*  AIPPRCMDATTR DESCRIPTION :New AIP Page Read command attributes */
typedef union {
    struct {
        uint32_t Duration : 4;               /*0:3 SW=rw HW=ro 0x7 */
        
        uint32_t resv4 : 4;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t PageEnable : 1;               /*14 SW=rw HW=ro 0x0 */
        
        uint32_t resv15 : 2;
        uint32_t Addresswidth : 2;               /*17:18 SW=rw HW=ro 0x0 */
        uint32_t resv19 : 13;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPPRCMDATTR;

/*  AIPPAGETIME DESCRIPTION :New AIP Page Read Time */
typedef union {
    struct {
        uint32_t Bits : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow0_AIPPAGETIME;

typedef struct {
    xspimc_AIPwindow0_AIPCTRL  AIPCTRL;
    xspimc_AIPwindow0_AIPACCB  AIPACCB;
    xspimc_AIPwindow0_AIPSIZE  AIPSIZE;
    xspimc_AIPwindow0_AIPWINADDR  AIPWINADDR;
    xspimc_AIPwindow0_AIPCMD  AIPCMD;
    xspimc_AIPwindow0_AIPCMDATTR  AIPCMDATTR;
    xspimc_AIPwindow0_AIPDIECMD  AIPDIECMD;
    xspimc_AIPwindow0_AIPDIEATTR  AIPDIEATTR;
    xspimc_AIPwindow0_AIPADRBASE  AIPADRBASE;
    xspimc_AIPwindow0_AIPADRATTR  AIPADRATTR;
    xspimc_AIPwindow0_AIPCS  AIPCS;
    xspimc_AIPwindow0_AIPDIEPAGESTATE  AIPDIEPAGESTATE;
    xspimc_AIPwindow0_AIPDUMMYATTR  AIPDUMMYATTR;
    xspimc_AIPwindow0_AIPSUSRESCMD  AIPSUSRESCMD;
    xspimc_AIPwindow0_AIPSUSRESATTR  AIPSUSRESATTR;
    xspimc_AIPwindow0_AIPSUSTIME  AIPSUSTIME;
    xspimc_AIPwindow0_AIPDATATTR  AIPDATATTR;
    xspimc_AIPwindow0_AIPRESTIME  AIPRESTIME;
    xspimc_AIPwindow0_AIPSUSRESTIME  AIPSUSRESTIME;
    xspimc_AIPwindow0_AIPRESSUSTIME  AIPRESSUSTIME;
    xspimc_AIPwindow0_AIPMODEBITS  AIPMODEBITS;
    xspimc_AIPwindow0_AIPMODEBITSATTR  AIPMODEBITSATTR;
    xspimc_AIPwindow0_AIPPRCMDATTR  AIPPRCMDATTR;
    xspimc_AIPwindow0_AIPPAGETIME  AIPPAGETIME;
    
    
} xspimc_AIPwindow0;


typedef xspimc_AIPwindow0 XSPI_DEVICE_Type;


/*  DMASTARTADR DESCRIPTION :DMA Start Address */
typedef union {
    struct {
        
        uint32_t resv0 : 2;
        uint32_t Address : 30;               /*2:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_DMASTARTADR;

/*  DMAFXDBL DESCRIPTION :DMA Master Fixed Burst Length Select */
typedef union {
    struct {
        uint32_t FixedBL : 2;               /*0:1 SW=rw HW=ro 0x0 */
        
        uint32_t resv2 : 6;
        uint32_t AXIBL : 16;               /*8:23 SW=rw HW=ro 0xF */
        uint32_t resv24 : 8;
    } bf;
    uint32_t  dw;
    
    
}xspimc_DMAFXDBL;

/*  DMASTS DESCRIPTION :DMA Status */
typedef union {
    struct {
        uint32_t DMAIdle : 1;               /*0 SW=ro HW=ro 0x1 */
        uint32_t DMAIRQ : 1;               /*1 SW=rw HW=ro 0x0 */
        uint32_t DMAError : 1;               /*2 SW=rw HW=ro 0x0 */
        uint32_t resv3 : 29;
    } bf;
    uint32_t  dw;
    
    
}xspimc_DMASTS;

/*  DMABDCNT DESCRIPTION :DMA Buffer Descriptor Count */
typedef union {
    struct {
        uint32_t Count : 32;               /*0:31 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_DMABDCNT;

/*  GPIO DESCRIPTION :GPIO Output */
typedef union {
    struct {
        uint32_t GPIO : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_GPIO;

/*  GPIOOE DESCRIPTION :GPIO Output Enable */
typedef union {
    struct {
        uint32_t GPIOOE : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_GPIOOE;

/*  WPCTRL DESCRIPTION :Write protect control */
typedef union {
    struct {
        uint32_t WP : 1;               /*0 SW=rw HW=ro 0x1 */
        uint32_t WPZ : 1;               /*1 SW=rw HW=ro 0x0 */
        uint32_t resv2 : 30;
    } bf;
    uint32_t  dw;
    
    
}xspimc_WPCTRL;

/*  HOLDTIME DESCRIPTION :SPI Hold time */
typedef union {
    struct {
        uint32_t Holdtime : 8;               /*0:7 SW=rw HW=ro 0x7 */
        uint32_t resv8 : 24;
    } bf;
    uint32_t  dw;
    
    
}xspimc_HOLDTIME;

/*  ACFGCTRL DESCRIPTION :Auto-Configuration Control */
typedef union {
    struct {
        uint32_t EnableAutoConfigurationaftersoftwarereset : 1;               /*0 SW=rw HW=ro 0x0 */
        
        uint32_t resv1 : 23;
        uint32_t CSNumber : 5;               /*24:28 SW=rw HW=ro 0x1 */
        uint32_t resv29 : 3;
    } bf;
    uint32_t  dw;
    
    
}xspimc_ACFGCTRL;

/*  VERSION DESCRIPTION :Version */
typedef union {
    struct {
        uint32_t Revision : 8;               /*0:7 SW=ro HW=ro 0x3 */
        uint32_t Minorversion : 8;               /*8:15 SW=ro HW=ro 0x3 */
        uint32_t Majorversion : 16;               /*16:31 SW=ro HW=ro 0x4 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_VERSION;

/*  AIPIMPFEAT DESCRIPTION :Implemented Features */
typedef union {
    struct {
        uint32_t AIPImpl : 1;               /*0 SW=ro HW=ro 0x0 */
        
        uint32_t resv1 : 3;
        uint32_t DMAImpl : 1;               /*4 SW=ro HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t ACFGImpl : 1;               /*8 SW=ro HW=ro 0x0 */
        
        uint32_t resv9 : 3;
        uint32_t SRAMImpl : 1;               /*12 SW=ro HW=ro 0x0 */
        uint32_t resv13 : 19;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPFEAT;

/*  AIPIMPCSW DESCRIPTION :Implemented number of CS lines */
typedef union {
    struct {
        uint32_t CSlines : 32;               /*0:31 SW=ro HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPCSW;

/*  AIPIMPGPIOW DESCRIPTION :Implemented number of GPIO lines */
typedef union {
    struct {
        uint32_t GPIOlines : 32;               /*0:31 SW=ro HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPGPIOW;

/*  AIPIMPDQWIDTH DESCRIPTION :Implemented number of data lines */
typedef union {
    struct {
        uint32_t Datalines : 32;               /*0:31 SW=ro HW=ro 0x4 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPDQWIDTH;

/*  GPIOIMPCDC DESCRIPTION :Implemented Clocking option */
typedef union {
    struct {
        uint32_t CDC : 32;               /*0:31 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_GPIOIMPCDC;

/*  AIPIMPTYPE DESCRIPTION :Implemented AIP type */
typedef union {
    struct {
        uint32_t AIPType : 32;               /*0:31 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPTYPE;

/*  AIPIMPAW DESCRIPTION :Implemented AIP address width */
typedef union {
    struct {
        uint32_t AIPAW : 32;               /*0:31 SW=ro HW=ro 0x2 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPAW;

/*  AIPIMPIDW DESCRIPTION :Implemented AIP ID width */
typedef union {
    struct {
        uint32_t AIPIDW : 32;               /*0:31 SW=ro HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPIMPIDW;

/*  CFGFIFOAW DESCRIPTION :Implemented custom command FIFO depth */
typedef union {
    struct {
        uint32_t CFGFIFOlen : 32;               /*0:31 SW=ro HW=ro 0x2 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_CFGFIFOAW;

/*  IMPWRFIFOAW DESCRIPTION :Implemented write FIFO depth */
typedef union {
    struct {
        uint32_t WRFIFO : 32;               /*0:31 SW=ro HW=ro 0x2 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_IMPWRFIFOAW;

/*  IMPRDFIFOAW DESCRIPTION :Implemented read FIFO depth */
typedef union {
    struct {
        uint32_t RDFIFOlen : 32;               /*0:31 SW=ro HW=ro 0x2 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_IMPRDFIFOAW;

/*  ACFGROMAW DESCRIPTION :Implemented Auto Configuratioon data size */
typedef union {
    struct {
        uint32_t ACFGlen : 32;               /*0:31 SW=ro HW=ro 0x2 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_ACFGROMAW;

/*  IMPDMAAW DESCRIPTION :Implemented DMA Address_width */
typedef union {
    struct {
        uint32_t DMAAW : 32;               /*0:31 SW=ro HW=ro 0x2 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_IMPDMAAW;

/*  ADDRDECN DESCRIPTION :Implemented number of available AIP windows */
typedef union {
    struct {
        uint32_t AIPwindows : 32;               /*0:31 SW=ro HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_ADDRDECN;

/*section : AIPwindow1 */
/*  AIPWINDOW1 DESCRIPTION :*/

/*  AIPCTRL DESCRIPTION :AIP Control */
typedef union {
    struct {
        uint32_t AIPModeEnable : 1;               /*0 SW=rw HW=ro 0x1 */
        uint32_t Busy : 1;               /*1 SW=ro HW=ro 0x0 */
        
        uint32_t resv2 : 6;
        uint32_t SusRes : 1;               /*8 SW=rw HW=ro 0x0 */
        uint32_t Update : 1;               /*9 SW=rw HW=ro 0x0 */
        uint32_t resv10 : 22;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPCTRL;

/*  AIPACCB DESCRIPTION :New AIP access boundary */
typedef union {
    struct {
        uint32_t AIPaccessboundary : 5;               /*0:4 SW=rw HW=ro 0x1F */
        uint32_t resv5 : 27;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPACCB;

/*  AIPSIZE DESCRIPTION :New AIP Size */
typedef union {
    struct {
        uint32_t AIPsize : 32;               /*0:31 SW=rw HW=ro 0x1FFFFF */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPSIZE;

/*  AIPWINADDR DESCRIPTION :New AIP window address */
typedef union {
    struct {
        uint32_t AIPwindowaddress : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPWINADDR;

/*  AIPCMD DESCRIPTION :New AIP Command */
typedef union {
    struct {
        uint32_t RCommand : 16;               /*0:15 SW=rw HW=ro 0xB00 */
        uint32_t WCommand : 16;               /*16:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPCMD;

/*  AIPCMDATTR DESCRIPTION :New AIP Command Attributes */
typedef union {
    struct {
        uint32_t Duration : 3;               /*0:2 SW=rw HW=ro 0x7 */
        
        uint32_t resv3 : 5;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t Writesupport : 1;               /*14 SW=rw HW=ro 0x0 */
        uint32_t HypeRAMcommand : 1;               /*15 SW=rw HW=ro 0x0 */
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x0 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPCMDATTR;

/*  AIPDIECMD DESCRIPTION :New AIP Die Select Command */
typedef union {
    struct {
        uint32_t Dieselectcmd : 16;               /*0:15 SW=rw HW=ro 0x0 */
        uint32_t Addrbitsindie : 5;               /*16:20 SW=rw HW=ro 0x0 */
        uint32_t resv21 : 11;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPDIECMD;

/*  AIPDIEATTR DESCRIPTION :New AIP Die Select Attributes */
typedef union {
    struct {
        uint32_t Commandduration : 4;               /*0:3 SW=rw HW=ro 0x7 */
        
        uint32_t resv4 : 4;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t Dieenable : 1;               /*14 SW=rw HW=ro 0x0 */
        
        uint32_t resv15 : 1;
        uint32_t Addresswidth : 2;               /*16:17 SW=rw HW=ro 0x3 */
        uint32_t resv18 : 14;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPDIEATTR;

/*  AIPADRBASE DESCRIPTION :New AIP Base_Address */
typedef union {
    struct {
        uint32_t BaseAddress : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPADRBASE;

/*  AIPADRATTR DESCRIPTION :New AIP Address Attributes */
typedef union {
    struct {
        
        uint32_t resv0 : 8;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 2;
        uint32_t Width : 2;               /*16:17 SW=rw HW=ro 0x0 */
        uint32_t Mask : 2;               /*18:19 SW=rw HW=ro 0x3 */
        uint32_t resv20 : 12;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPADRATTR;

/*  AIPCS DESCRIPTION :New AIP Chip Select */
typedef union {
    struct {
        uint32_t ChipSelect : 32;               /*0:31 SW=rw HW=ro 0x1 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPCS;

/*  AIPDIEPAGESTATE DESCRIPTION :AIP State */
typedef union {
    struct {
        uint32_t SelectedPage : 23;               /*0:22 SW=rw HW=ro 0x0 */
        uint32_t Pageselected : 1;               /*23 SW=rw HW=ro 0x0 */
        uint32_t SelectedDie : 7;               /*24:30 SW=rw HW=ro 0x0 */
        uint32_t DieSelected : 1;               /*31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPDIEPAGESTATE;

/*  AIPDUMMYATTR DESCRIPTION :New AIP Dummy Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x7 */
        
        uint32_t resv5 : 3;
        uint32_t Skip : 1;               /*8 SW=rw HW=ro 0x0 */
        
        uint32_t resv9 : 7;
        uint32_t WriteLatency : 5;               /*16:20 SW=rw HW=ro 0x0 */
        
        uint32_t resv21 : 3;
        uint32_t Nowritelatency : 1;               /*24 SW=rw HW=ro 0x1 */
        uint32_t Dynwritelatency : 1;               /*25 SW=rw HW=ro 0x0 */
        uint32_t resv26 : 6;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPDUMMYATTR;

/*  AIPSUSRESCMD DESCRIPTION :New AIP Suspend/resume commands */
typedef union {
    struct {
        uint32_t SusCommand : 16;               /*0:15 SW=rw HW=ro 0x0 */
        uint32_t ResCommand : 16;               /*16:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPSUSRESCMD;

/*  AIPSUSRESATTR DESCRIPTION :New AIP Suspend/Resume attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x0 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t resv14 : 18;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPSUSRESATTR;

/*  AIPSUSTIME DESCRIPTION :New AIP Suspend Time */
typedef union {
    struct {
        uint32_t Suspendtime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPSUSTIME;

/*  AIPDATATTR DESCRIPTION :New AIP Data attributes */
typedef union {
    struct {
        uint32_t Mode : 4;               /*0:3 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*4 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*5 SW=rw HW=ro 0x0 */
        uint32_t DQS : 1;               /*6 SW=rw HW=ro 0x0 */
        uint32_t FlipBytes : 1;               /*7 SW=rw HW=ro 0x0 */
        uint32_t resv8 : 24;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPDATATTR;

/*  AIPRESTIME DESCRIPTION :New AIP Resume Time */
typedef union {
    struct {
        uint32_t Resumetime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPRESTIME;

/*  AIPSUSRESTIME DESCRIPTION :New AIP Suspend to Resume Time */
typedef union {
    struct {
        uint32_t Sustorestime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPSUSRESTIME;

/*  AIPRESSUSTIME DESCRIPTION :New AIP Resume to Suspend Time */
typedef union {
    struct {
        uint32_t Restosustime : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPRESSUSTIME;

/*  AIPMODEBITS DESCRIPTION :New AIP Mode Bits */
typedef union {
    struct {
        uint32_t Bits : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPMODEBITS;

/*  AIPMODEBITSATTR DESCRIPTION :New AIP Mode Bits Attributes */
typedef union {
    struct {
        uint32_t Duration : 5;               /*0:4 SW=rw HW=ro 0x0 */
        
        uint32_t resv5 : 3;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x0 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        
        uint32_t resv14 : 2;
        uint32_t Skip : 1;               /*16 SW=rw HW=ro 0x1 */
        uint32_t resv17 : 15;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPMODEBITSATTR;

/*  AIPPRCMDATTR DESCRIPTION :New AIP Page Read command attributes */
typedef union {
    struct {
        uint32_t Duration : 4;               /*0:3 SW=rw HW=ro 0x7 */
        
        uint32_t resv4 : 4;
        uint32_t Mode : 4;               /*8:11 SW=rw HW=ro 0x1 */
        uint32_t DDRMode : 1;               /*12 SW=rw HW=ro 0x0 */
        uint32_t Stackeddie : 1;               /*13 SW=rw HW=ro 0x0 */
        uint32_t PageEnable : 1;               /*14 SW=rw HW=ro 0x0 */
        
        uint32_t resv15 : 2;
        uint32_t Addresswidth : 2;               /*17:18 SW=rw HW=ro 0x0 */
        uint32_t resv19 : 13;
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPPRCMDATTR;

/*  AIPPAGETIME DESCRIPTION :New AIP Page Read Time */
typedef union {
    struct {
        uint32_t Bits : 32;               /*0:31 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}xspimc_AIPwindow1_AIPPAGETIME;

typedef struct {
    xspimc_AIPwindow1_AIPCTRL  AIPCTRL;
    xspimc_AIPwindow1_AIPACCB  AIPACCB;
    xspimc_AIPwindow1_AIPSIZE  AIPSIZE;
    xspimc_AIPwindow1_AIPWINADDR  AIPWINADDR;
    xspimc_AIPwindow1_AIPCMD  AIPCMD;
    xspimc_AIPwindow1_AIPCMDATTR  AIPCMDATTR;
    xspimc_AIPwindow1_AIPDIECMD  AIPDIECMD;
    xspimc_AIPwindow1_AIPDIEATTR  AIPDIEATTR;
    xspimc_AIPwindow1_AIPADRBASE  AIPADRBASE;
    xspimc_AIPwindow1_AIPADRATTR  AIPADRATTR;
    xspimc_AIPwindow1_AIPCS  AIPCS;
    xspimc_AIPwindow1_AIPDIEPAGESTATE  AIPDIEPAGESTATE;
    xspimc_AIPwindow1_AIPDUMMYATTR  AIPDUMMYATTR;
    xspimc_AIPwindow1_AIPSUSRESCMD  AIPSUSRESCMD;
    xspimc_AIPwindow1_AIPSUSRESATTR  AIPSUSRESATTR;
    xspimc_AIPwindow1_AIPSUSTIME  AIPSUSTIME;
    xspimc_AIPwindow1_AIPDATATTR  AIPDATATTR;
    xspimc_AIPwindow1_AIPRESTIME  AIPRESTIME;
    xspimc_AIPwindow1_AIPSUSRESTIME  AIPSUSRESTIME;
    xspimc_AIPwindow1_AIPRESSUSTIME  AIPRESSUSTIME;
    xspimc_AIPwindow1_AIPMODEBITS  AIPMODEBITS;
    xspimc_AIPwindow1_AIPMODEBITSATTR  AIPMODEBITSATTR;
    xspimc_AIPwindow1_AIPPRCMDATTR  AIPPRCMDATTR;
    xspimc_AIPwindow1_AIPPAGETIME  AIPPAGETIME;
    
    
} xspimc_AIPwindow1;

typedef struct {
    __IOM xspimc_GLBLCTRL  GLBLCTRL;
    __IOM xspimc_SPICLKCFG  SPICLKCFG;
    __IOM xspimc_MINCSHIGH  MINCSHIGH;
    
    __IOM uint8_t filler3[0x4];
    
    __IOM xspimc_FIFOSTS  FIFOSTS;
    __IOM xspimc_SPISTS  SPISTS;
    __IOM xspimc_IRQCTRL  IRQCTRL;
    
    __IOM uint8_t filler6[0x4];
    
    __IOM xspimc_SPICMD  SPICMD;
    __IOM xspimc_SPICMDATTR  SPICMDATTR;
    
    __IOM uint8_t filler8[0x8];
    
    __IOM xspimc_SPIADDR  SPIADDR;
    __IOM xspimc_SPIADDRATTR  SPIADDRATTR;
    __IOM xspimc_SPICS  SPICS;
    
    __IOM uint8_t filler11[0x4];
    
    __IOM xspimc_SPIDUMMYATTR  SPIDUMMYATTR;
    __IOM xspimc_AIPHOLDOFFTIME  AIPHOLDOFFTIME;
    __IOM xspimc_AIPHOLDOFFSEL  AIPHOLDOFFSEL;
    __IOM xspimc_AIPHOLDOFFCTRL  AIPHOLDOFFCTRL;
    __IOM xspimc_SPIDATASIZE  SPIDATASIZE;
    __IOM xspimc_SPIDATAATTR  SPIDATAATTR;
    __IOM xspimc_SPITXDATA  SPITXDATA;
    __IOM xspimc_SPIRXDATA  SPIRXDATA;
    
    __IOM uint8_t filler19[0x8];
    
    __IOM xspimc_SPIMODEBITS  SPIMODEBITS;
    __IOM xspimc_SPIMODEBITSATTR  SPIMODEBITSATTR;
    
    __IOM uint8_t filler21[0x10];
    
    
    union {
        __IOM xspimc_AIPwindow0 s;
        __IOM uint8_t filler[0x60];
    } AIPwindow0;
    __IOM xspimc_DMASTARTADR  DMASTARTADR;
    __IOM xspimc_DMAFXDBL  DMAFXDBL;
    __IOM xspimc_DMASTS  DMASTS;
    __IOM xspimc_DMABDCNT  DMABDCNT;
    __IOM xspimc_GPIO  GPIO;
    __IOM xspimc_GPIOOE  GPIOOE;
    __IOM xspimc_WPCTRL  WPCTRL;
    __IOM xspimc_HOLDTIME  HOLDTIME;
    __IOM xspimc_ACFGCTRL  ACFGCTRL;
    
    __IOM uint8_t filler31[0x30];
    
    __IOM xspimc_VERSION  VERSION;
    
    __IOM uint8_t filler32[0x48];
    
    __IOM xspimc_AIPIMPFEAT  AIPIMPFEAT;
    __IOM xspimc_AIPIMPCSW  AIPIMPCSW;
    __IOM xspimc_AIPIMPGPIOW  AIPIMPGPIOW;
    __IOM xspimc_AIPIMPDQWIDTH  AIPIMPDQWIDTH;
    __IOM xspimc_GPIOIMPCDC  GPIOIMPCDC;
    __IOM xspimc_AIPIMPTYPE  AIPIMPTYPE;
    __IOM xspimc_AIPIMPAW  AIPIMPAW;
    __IOM xspimc_AIPIMPIDW  AIPIMPIDW;
    __IOM xspimc_CFGFIFOAW  CFGFIFOAW;
    
    __IOM uint8_t filler41[0x4];
    
    __IOM xspimc_IMPWRFIFOAW  IMPWRFIFOAW;
    
    __IOM uint8_t filler42[0x4];
    
    __IOM xspimc_IMPRDFIFOAW  IMPRDFIFOAW;
    
    __IOM uint8_t filler43[0x4];
    
    __IOM xspimc_ACFGROMAW  ACFGROMAW;
    __IOM xspimc_IMPDMAAW  IMPDMAAW;
    __IOM xspimc_ADDRDECN  ADDRDECN;
    
    __IOM uint8_t filler46[0xBC];
    
    
    union {
        __IOM xspimc_AIPwindow1 s;
        __IOM uint8_t filler[0x60];
    } AIPwindow1;
    
    
} xspimc_s;


typedef xspimc_s XSPI_Type;


#if 0
typedef struct {
    
    union {
        xspimc_s s;
        uint8_t filler[0x2E0];
    } s;
    
    
} xspimc_CSR;

typedef struct {
    
    union {
        xspimc_CSR s;
        uint8_t filler[0x2E0];
    } CSR;
    
    
} xspimc_s;
#endif

#define xspimc_GLBLCTRL_READMASK 0x10001U
#define xspimc_GLBLCTRL_WRITEMASK 0x10001U
#define xspimc_GLBLCTRL_VOLATILEMASK 0x0U
#define xspimc_GLBLCTRL_RESETMASK 0x10001U
#define xspimc_GLBLCTRL_DEFAULT 0x00000000U

#define xspimc_SPICLKCFG_READMASK 0xFF03FFFFU
#define xspimc_SPICLKCFG_WRITEMASK 0xFF03FFFFU
#define xspimc_SPICLKCFG_VOLATILEMASK 0x0U
#define xspimc_SPICLKCFG_RESETMASK 0xFF03FFFFU
#define xspimc_SPICLKCFG_DEFAULT 0x0F00070FU

#define xspimc_MINCSHIGH_READMASK 0xFFU
#define xspimc_MINCSHIGH_WRITEMASK 0xFFU
#define xspimc_MINCSHIGH_VOLATILEMASK 0x0U
#define xspimc_MINCSHIGH_RESETMASK 0xFFU
#define xspimc_MINCSHIGH_DEFAULT 0x00000000U

#define xspimc_FIFOSTS_READMASK 0x3FFFFU
#define xspimc_FIFOSTS_WRITEMASK 0x0U
#define xspimc_FIFOSTS_VOLATILEMASK 0x0U
#define xspimc_FIFOSTS_RESETMASK 0x3FFFFU
#define xspimc_FIFOSTS_DEFAULT 0x00010000U

#define xspimc_SPISTS_READMASK 0x1F0001U
#define xspimc_SPISTS_WRITEMASK 0x180000U
#define xspimc_SPISTS_VOLATILEMASK 0x0U
#define xspimc_SPISTS_RESETMASK 0x1F0001U
#define xspimc_SPISTS_DEFAULT 0x00040001U

#define xspimc_IRQCTRL_READMASK 0x7071FU
#define xspimc_IRQCTRL_WRITEMASK 0x7071FU
#define xspimc_IRQCTRL_VOLATILEMASK 0x0U
#define xspimc_IRQCTRL_RESETMASK 0x7071FU
#define xspimc_IRQCTRL_DEFAULT 0x00000000U

#define xspimc_SPICMD_READMASK 0xFFFFU
#define xspimc_SPICMD_WRITEMASK 0xFFFFU
#define xspimc_SPICMD_VOLATILEMASK 0x0U
#define xspimc_SPICMD_RESETMASK 0xFFFFU
#define xspimc_SPICMD_DEFAULT 0x00000000U

#define xspimc_SPICMDATTR_READMASK 0x8001BF0FU
#define xspimc_SPICMDATTR_WRITEMASK 0x8001BF0FU
#define xspimc_SPICMDATTR_VOLATILEMASK 0x0U
#define xspimc_SPICMDATTR_RESETMASK 0x8001BF0FU
#define xspimc_SPICMDATTR_DEFAULT 0x00000107U

#define xspimc_SPIADDR_READMASK 0xFFFFFFFFU
#define xspimc_SPIADDR_WRITEMASK 0xFFFFFFFFU
#define xspimc_SPIADDR_VOLATILEMASK 0x0U
#define xspimc_SPIADDR_RESETMASK 0xFFFFFFFFU
#define xspimc_SPIADDR_DEFAULT 0x00000000U

#define xspimc_SPIADDRATTR_READMASK 0x73F1FU
#define xspimc_SPIADDRATTR_WRITEMASK 0x73F1FU
#define xspimc_SPIADDRATTR_VOLATILEMASK 0x0U
#define xspimc_SPIADDRATTR_RESETMASK 0x73F1FU
#define xspimc_SPIADDRATTR_DEFAULT 0x00060117U

#define xspimc_SPICS_READMASK 0xFFFFFFFFU
#define xspimc_SPICS_WRITEMASK 0xFFFFFFFFU
#define xspimc_SPICS_VOLATILEMASK 0x0U
#define xspimc_SPICS_RESETMASK 0xFFFFFFFFU
#define xspimc_SPICS_DEFAULT 0x00000001U

#define xspimc_SPIDUMMYATTR_READMASK 0x31F011FU
#define xspimc_SPIDUMMYATTR_WRITEMASK 0x31F011FU
#define xspimc_SPIDUMMYATTR_VOLATILEMASK 0x0U
#define xspimc_SPIDUMMYATTR_RESETMASK 0x31F011FU
#define xspimc_SPIDUMMYATTR_DEFAULT 0x01000000U

#define xspimc_AIPHOLDOFFTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFTIME_VOLATILEMASK 0x0U
#define xspimc_AIPHOLDOFFTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFTIME_DEFAULT 0x00000000U

#define xspimc_AIPHOLDOFFSEL_READMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFSEL_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFSEL_VOLATILEMASK 0x0U
#define xspimc_AIPHOLDOFFSEL_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFSEL_DEFAULT 0x00000000U

#define xspimc_AIPHOLDOFFCTRL_READMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFCTRL_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFCTRL_VOLATILEMASK 0x0U
#define xspimc_AIPHOLDOFFCTRL_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPHOLDOFFCTRL_DEFAULT 0x00000000U

#define xspimc_SPIDATASIZE_READMASK 0xFFFFFFFFU
#define xspimc_SPIDATASIZE_WRITEMASK 0xFFFFFFFFU
#define xspimc_SPIDATASIZE_VOLATILEMASK 0x0U
#define xspimc_SPIDATASIZE_RESETMASK 0xFFFFFFFFU
#define xspimc_SPIDATASIZE_DEFAULT 0x00000000U

#define xspimc_SPIDATAATTR_READMASK 0x101FFU
#define xspimc_SPIDATAATTR_WRITEMASK 0x101FFU
#define xspimc_SPIDATAATTR_VOLATILEMASK 0x0U
#define xspimc_SPIDATAATTR_RESETMASK 0x101FFU
#define xspimc_SPIDATAATTR_DEFAULT 0x00000000U

#define xspimc_SPITXDATA_READMASK 0x0U
#define xspimc_SPITXDATA_WRITEMASK 0xFFFFFFFFU
#define xspimc_SPITXDATA_VOLATILEMASK 0x0U
#define xspimc_SPITXDATA_RESETMASK 0xFFFFFFFFU
#define xspimc_SPITXDATA_DEFAULT 0x00000000U

#define xspimc_SPIRXDATA_READMASK 0xFFFFFFFFU
#define xspimc_SPIRXDATA_WRITEMASK 0x0U
#define xspimc_SPIRXDATA_VOLATILEMASK 0x0U
#define xspimc_SPIRXDATA_RESETMASK 0xFFFFFFFFU
#define xspimc_SPIRXDATA_DEFAULT 0x00000000U

#define xspimc_SPIMODEBITS_READMASK 0xFFFFFFFFU
#define xspimc_SPIMODEBITS_WRITEMASK 0xFFFFFFFFU
#define xspimc_SPIMODEBITS_VOLATILEMASK 0x0U
#define xspimc_SPIMODEBITS_RESETMASK 0xFFFFFFFFU
#define xspimc_SPIMODEBITS_DEFAULT 0x00000000U

#define xspimc_SPIMODEBITSATTR_READMASK 0x13F1FU
#define xspimc_SPIMODEBITSATTR_WRITEMASK 0x13F1FU
#define xspimc_SPIMODEBITSATTR_VOLATILEMASK 0x0U
#define xspimc_SPIMODEBITSATTR_RESETMASK 0x13F1FU
#define xspimc_SPIMODEBITSATTR_DEFAULT 0x00010000U

#define xspimc_AIPwindow0_AIPCTRL_READMASK 0x303U
#define xspimc_AIPwindow0_AIPCTRL_WRITEMASK 0x301U
#define xspimc_AIPwindow0_AIPCTRL_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPCTRL_RESETMASK 0x303U
#define xspimc_AIPwindow0_AIPCTRL_DEFAULT 0x00000001U

#define xspimc_AIPwindow0_AIPACCB_READMASK 0x1FU
#define xspimc_AIPwindow0_AIPACCB_WRITEMASK 0x1FU
#define xspimc_AIPwindow0_AIPACCB_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPACCB_RESETMASK 0x1FU
#define xspimc_AIPwindow0_AIPACCB_DEFAULT 0x0000001FU

#define xspimc_AIPwindow0_AIPSIZE_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSIZE_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSIZE_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPSIZE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSIZE_DEFAULT 0x001FFFFFU

#define xspimc_AIPwindow0_AIPWINADDR_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPWINADDR_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPWINADDR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPWINADDR_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPWINADDR_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPCMD_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPCMD_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPCMD_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPCMD_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPCMD_DEFAULT 0x00000B00U

#define xspimc_AIPwindow0_AIPCMDATTR_READMASK 0x1FF07U
#define xspimc_AIPwindow0_AIPCMDATTR_WRITEMASK 0x1FF07U
#define xspimc_AIPwindow0_AIPCMDATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPCMDATTR_RESETMASK 0x1FF07U
#define xspimc_AIPwindow0_AIPCMDATTR_DEFAULT 0x00000107U

#define xspimc_AIPwindow0_AIPDIECMD_READMASK 0x1FFFFFU
#define xspimc_AIPwindow0_AIPDIECMD_WRITEMASK 0x1FFFFFU
#define xspimc_AIPwindow0_AIPDIECMD_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPDIECMD_RESETMASK 0x1FFFFFU
#define xspimc_AIPwindow0_AIPDIECMD_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPDIEATTR_READMASK 0x37F0FU
#define xspimc_AIPwindow0_AIPDIEATTR_WRITEMASK 0x37F0FU
#define xspimc_AIPwindow0_AIPDIEATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPDIEATTR_RESETMASK 0x37F0FU
#define xspimc_AIPwindow0_AIPDIEATTR_DEFAULT 0x00030107U

#define xspimc_AIPwindow0_AIPADRBASE_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPADRBASE_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPADRBASE_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPADRBASE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPADRBASE_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPADRATTR_READMASK 0xF3F00U
#define xspimc_AIPwindow0_AIPADRATTR_WRITEMASK 0xF3F00U
#define xspimc_AIPwindow0_AIPADRATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPADRATTR_RESETMASK 0xF3F00U
#define xspimc_AIPwindow0_AIPADRATTR_DEFAULT 0x000C0100U

#define xspimc_AIPwindow0_AIPCS_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPCS_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPCS_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPCS_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPCS_DEFAULT 0x00000001U

#define xspimc_AIPwindow0_AIPDIEPAGESTATE_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPDIEPAGESTATE_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPDIEPAGESTATE_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPDIEPAGESTATE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPDIEPAGESTATE_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPDUMMYATTR_READMASK 0x31F011FU
#define xspimc_AIPwindow0_AIPDUMMYATTR_WRITEMASK 0x31F011FU
#define xspimc_AIPwindow0_AIPDUMMYATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPDUMMYATTR_RESETMASK 0x31F011FU
#define xspimc_AIPwindow0_AIPDUMMYATTR_DEFAULT 0x01000007U

#define xspimc_AIPwindow0_AIPSUSRESCMD_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSRESCMD_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSRESCMD_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPSUSRESCMD_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSRESCMD_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPSUSRESATTR_READMASK 0x3F1FU
#define xspimc_AIPwindow0_AIPSUSRESATTR_WRITEMASK 0x3F1FU
#define xspimc_AIPwindow0_AIPSUSRESATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPSUSRESATTR_RESETMASK 0x3F1FU
#define xspimc_AIPwindow0_AIPSUSRESATTR_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPSUSTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPSUSTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPDATATTR_READMASK 0xFFU
#define xspimc_AIPwindow0_AIPDATATTR_WRITEMASK 0xFFU
#define xspimc_AIPwindow0_AIPDATATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPDATATTR_RESETMASK 0xFFU
#define xspimc_AIPwindow0_AIPDATATTR_DEFAULT 0x00000001U

#define xspimc_AIPwindow0_AIPRESTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPRESTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPRESTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPRESTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPRESTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPSUSRESTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSRESTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSRESTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPSUSRESTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPSUSRESTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPRESSUSTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPRESSUSTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPRESSUSTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPRESSUSTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPRESSUSTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPMODEBITS_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPMODEBITS_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPMODEBITS_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPMODEBITS_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPMODEBITS_DEFAULT 0x00000000U

#define xspimc_AIPwindow0_AIPMODEBITSATTR_READMASK 0x13F1FU
#define xspimc_AIPwindow0_AIPMODEBITSATTR_WRITEMASK 0x13F1FU
#define xspimc_AIPwindow0_AIPMODEBITSATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPMODEBITSATTR_RESETMASK 0x13F1FU
#define xspimc_AIPwindow0_AIPMODEBITSATTR_DEFAULT 0x00010000U

#define xspimc_AIPwindow0_AIPPRCMDATTR_READMASK 0x67F0FU
#define xspimc_AIPwindow0_AIPPRCMDATTR_WRITEMASK 0x67F0FU
#define xspimc_AIPwindow0_AIPPRCMDATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPPRCMDATTR_RESETMASK 0x67F0FU
#define xspimc_AIPwindow0_AIPPRCMDATTR_DEFAULT 0x00000107U

#define xspimc_AIPwindow0_AIPPAGETIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPPAGETIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPPAGETIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow0_AIPPAGETIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow0_AIPPAGETIME_DEFAULT 0x00000000U

#define xspimc_DMASTARTADR_READMASK 0xFFFFFFFCU
#define xspimc_DMASTARTADR_WRITEMASK 0xFFFFFFFCU
#define xspimc_DMASTARTADR_VOLATILEMASK 0x0U
#define xspimc_DMASTARTADR_RESETMASK 0xFFFFFFFCU
#define xspimc_DMASTARTADR_DEFAULT 0x00000000U

#define xspimc_DMAFXDBL_READMASK 0xFFFF03U
#define xspimc_DMAFXDBL_WRITEMASK 0xFFFF03U
#define xspimc_DMAFXDBL_VOLATILEMASK 0x0U
#define xspimc_DMAFXDBL_RESETMASK 0xFFFF03U
#define xspimc_DMAFXDBL_DEFAULT 0x00000F00U

#define xspimc_DMASTS_READMASK 0x7U
#define xspimc_DMASTS_WRITEMASK 0x6U
#define xspimc_DMASTS_VOLATILEMASK 0x0U
#define xspimc_DMASTS_RESETMASK 0x7U
#define xspimc_DMASTS_DEFAULT 0x00000001U

#define xspimc_DMABDCNT_READMASK 0xFFFFFFFFU
#define xspimc_DMABDCNT_WRITEMASK 0x0U
#define xspimc_DMABDCNT_VOLATILEMASK 0x0U
#define xspimc_DMABDCNT_RESETMASK 0xFFFFFFFFU
#define xspimc_DMABDCNT_DEFAULT 0x00000000U

#define xspimc_GPIO_READMASK 0xFFFFFFFFU
#define xspimc_GPIO_WRITEMASK 0xFFFFFFFFU
#define xspimc_GPIO_VOLATILEMASK 0x0U
#define xspimc_GPIO_RESETMASK 0xFFFFFFFFU
#define xspimc_GPIO_DEFAULT 0x00000000U

#define xspimc_GPIOOE_READMASK 0xFFFFFFFFU
#define xspimc_GPIOOE_WRITEMASK 0xFFFFFFFFU
#define xspimc_GPIOOE_VOLATILEMASK 0x0U
#define xspimc_GPIOOE_RESETMASK 0xFFFFFFFFU
#define xspimc_GPIOOE_DEFAULT 0x00000000U

#define xspimc_WPCTRL_READMASK 0x3U
#define xspimc_WPCTRL_WRITEMASK 0x3U
#define xspimc_WPCTRL_VOLATILEMASK 0x0U
#define xspimc_WPCTRL_RESETMASK 0x3U
#define xspimc_WPCTRL_DEFAULT 0x00000001U

#define xspimc_HOLDTIME_READMASK 0xFFU
#define xspimc_HOLDTIME_WRITEMASK 0xFFU
#define xspimc_HOLDTIME_VOLATILEMASK 0x0U
#define xspimc_HOLDTIME_RESETMASK 0xFFU
#define xspimc_HOLDTIME_DEFAULT 0x00000007U

#define xspimc_ACFGCTRL_READMASK 0x1F000001U
#define xspimc_ACFGCTRL_WRITEMASK 0x1F000001U
#define xspimc_ACFGCTRL_VOLATILEMASK 0x0U
#define xspimc_ACFGCTRL_RESETMASK 0x1F000001U
#define xspimc_ACFGCTRL_DEFAULT 0x01000000U

#define xspimc_VERSION_READMASK 0xFFFFFFFFU
#define xspimc_VERSION_WRITEMASK 0x0U
#define xspimc_VERSION_VOLATILEMASK 0x0U
#define xspimc_VERSION_RESETMASK 0xFFFFFFFFU
#define xspimc_VERSION_DEFAULT 0x00040303U

#define xspimc_AIPIMPFEAT_READMASK 0x1111U
#define xspimc_AIPIMPFEAT_WRITEMASK 0x0U
#define xspimc_AIPIMPFEAT_VOLATILEMASK 0x0U
#define xspimc_AIPIMPFEAT_RESETMASK 0x1111U
#define xspimc_AIPIMPFEAT_DEFAULT 0x00000000U

#define xspimc_AIPIMPCSW_READMASK 0xFFFFFFFFU
#define xspimc_AIPIMPCSW_WRITEMASK 0x0U
#define xspimc_AIPIMPCSW_VOLATILEMASK 0x0U
#define xspimc_AIPIMPCSW_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPIMPCSW_DEFAULT 0x00000001U

#define xspimc_AIPIMPGPIOW_READMASK 0xFFFFFFFFU
#define xspimc_AIPIMPGPIOW_WRITEMASK 0x0U
#define xspimc_AIPIMPGPIOW_VOLATILEMASK 0x0U
#define xspimc_AIPIMPGPIOW_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPIMPGPIOW_DEFAULT 0x00000001U

#define xspimc_AIPIMPDQWIDTH_READMASK 0xFFFFFFFFU
#define xspimc_AIPIMPDQWIDTH_WRITEMASK 0x0U
#define xspimc_AIPIMPDQWIDTH_VOLATILEMASK 0x0U
#define xspimc_AIPIMPDQWIDTH_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPIMPDQWIDTH_DEFAULT 0x00000004U

#define xspimc_GPIOIMPCDC_READMASK 0xFFFFFFFFU
#define xspimc_GPIOIMPCDC_WRITEMASK 0x0U
#define xspimc_GPIOIMPCDC_VOLATILEMASK 0x0U
#define xspimc_GPIOIMPCDC_RESETMASK 0xFFFFFFFFU
#define xspimc_GPIOIMPCDC_DEFAULT 0x00000000U

#define xspimc_AIPIMPTYPE_READMASK 0xFFFFFFFFU
#define xspimc_AIPIMPTYPE_WRITEMASK 0x0U
#define xspimc_AIPIMPTYPE_VOLATILEMASK 0x0U
#define xspimc_AIPIMPTYPE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPIMPTYPE_DEFAULT 0x00000000U

#define xspimc_AIPIMPAW_READMASK 0xFFFFFFFFU
#define xspimc_AIPIMPAW_WRITEMASK 0x0U
#define xspimc_AIPIMPAW_VOLATILEMASK 0x0U
#define xspimc_AIPIMPAW_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPIMPAW_DEFAULT 0x00000002U

#define xspimc_AIPIMPIDW_READMASK 0xFFFFFFFFU
#define xspimc_AIPIMPIDW_WRITEMASK 0x0U
#define xspimc_AIPIMPIDW_VOLATILEMASK 0x0U
#define xspimc_AIPIMPIDW_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPIMPIDW_DEFAULT 0x00000001U

#define xspimc_CFGFIFOAW_READMASK 0xFFFFFFFFU
#define xspimc_CFGFIFOAW_WRITEMASK 0x0U
#define xspimc_CFGFIFOAW_VOLATILEMASK 0x0U
#define xspimc_CFGFIFOAW_RESETMASK 0xFFFFFFFFU
#define xspimc_CFGFIFOAW_DEFAULT 0x00000002U

#define xspimc_IMPWRFIFOAW_READMASK 0xFFFFFFFFU
#define xspimc_IMPWRFIFOAW_WRITEMASK 0x0U
#define xspimc_IMPWRFIFOAW_VOLATILEMASK 0x0U
#define xspimc_IMPWRFIFOAW_RESETMASK 0xFFFFFFFFU
#define xspimc_IMPWRFIFOAW_DEFAULT 0x00000002U

#define xspimc_IMPRDFIFOAW_READMASK 0xFFFFFFFFU
#define xspimc_IMPRDFIFOAW_WRITEMASK 0x0U
#define xspimc_IMPRDFIFOAW_VOLATILEMASK 0x0U
#define xspimc_IMPRDFIFOAW_RESETMASK 0xFFFFFFFFU
#define xspimc_IMPRDFIFOAW_DEFAULT 0x00000002U

#define xspimc_ACFGROMAW_READMASK 0xFFFFFFFFU
#define xspimc_ACFGROMAW_WRITEMASK 0x0U
#define xspimc_ACFGROMAW_VOLATILEMASK 0x0U
#define xspimc_ACFGROMAW_RESETMASK 0xFFFFFFFFU
#define xspimc_ACFGROMAW_DEFAULT 0x00000002U

#define xspimc_IMPDMAAW_READMASK 0xFFFFFFFFU
#define xspimc_IMPDMAAW_WRITEMASK 0x0U
#define xspimc_IMPDMAAW_VOLATILEMASK 0x0U
#define xspimc_IMPDMAAW_RESETMASK 0xFFFFFFFFU
#define xspimc_IMPDMAAW_DEFAULT 0x00000002U

#define xspimc_ADDRDECN_READMASK 0xFFFFFFFFU
#define xspimc_ADDRDECN_WRITEMASK 0x0U
#define xspimc_ADDRDECN_VOLATILEMASK 0x0U
#define xspimc_ADDRDECN_RESETMASK 0xFFFFFFFFU
#define xspimc_ADDRDECN_DEFAULT 0x00000001U

#define xspimc_AIPwindow1_AIPCTRL_READMASK 0x303U
#define xspimc_AIPwindow1_AIPCTRL_WRITEMASK 0x301U
#define xspimc_AIPwindow1_AIPCTRL_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPCTRL_RESETMASK 0x303U
#define xspimc_AIPwindow1_AIPCTRL_DEFAULT 0x00000001U

#define xspimc_AIPwindow1_AIPACCB_READMASK 0x1FU
#define xspimc_AIPwindow1_AIPACCB_WRITEMASK 0x1FU
#define xspimc_AIPwindow1_AIPACCB_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPACCB_RESETMASK 0x1FU
#define xspimc_AIPwindow1_AIPACCB_DEFAULT 0x0000001FU

#define xspimc_AIPwindow1_AIPSIZE_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSIZE_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSIZE_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPSIZE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSIZE_DEFAULT 0x001FFFFFU

#define xspimc_AIPwindow1_AIPWINADDR_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPWINADDR_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPWINADDR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPWINADDR_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPWINADDR_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPCMD_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPCMD_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPCMD_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPCMD_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPCMD_DEFAULT 0x00000B00U

#define xspimc_AIPwindow1_AIPCMDATTR_READMASK 0x1FF07U
#define xspimc_AIPwindow1_AIPCMDATTR_WRITEMASK 0x1FF07U
#define xspimc_AIPwindow1_AIPCMDATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPCMDATTR_RESETMASK 0x1FF07U
#define xspimc_AIPwindow1_AIPCMDATTR_DEFAULT 0x00000107U

#define xspimc_AIPwindow1_AIPDIECMD_READMASK 0x1FFFFFU
#define xspimc_AIPwindow1_AIPDIECMD_WRITEMASK 0x1FFFFFU
#define xspimc_AIPwindow1_AIPDIECMD_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPDIECMD_RESETMASK 0x1FFFFFU
#define xspimc_AIPwindow1_AIPDIECMD_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPDIEATTR_READMASK 0x37F0FU
#define xspimc_AIPwindow1_AIPDIEATTR_WRITEMASK 0x37F0FU
#define xspimc_AIPwindow1_AIPDIEATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPDIEATTR_RESETMASK 0x37F0FU
#define xspimc_AIPwindow1_AIPDIEATTR_DEFAULT 0x00030107U

#define xspimc_AIPwindow1_AIPADRBASE_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPADRBASE_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPADRBASE_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPADRBASE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPADRBASE_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPADRATTR_READMASK 0xF3F00U
#define xspimc_AIPwindow1_AIPADRATTR_WRITEMASK 0xF3F00U
#define xspimc_AIPwindow1_AIPADRATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPADRATTR_RESETMASK 0xF3F00U
#define xspimc_AIPwindow1_AIPADRATTR_DEFAULT 0x000C0100U

#define xspimc_AIPwindow1_AIPCS_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPCS_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPCS_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPCS_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPCS_DEFAULT 0x00000001U

#define xspimc_AIPwindow1_AIPDIEPAGESTATE_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPDIEPAGESTATE_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPDIEPAGESTATE_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPDIEPAGESTATE_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPDIEPAGESTATE_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPDUMMYATTR_READMASK 0x31F011FU
#define xspimc_AIPwindow1_AIPDUMMYATTR_WRITEMASK 0x31F011FU
#define xspimc_AIPwindow1_AIPDUMMYATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPDUMMYATTR_RESETMASK 0x31F011FU
#define xspimc_AIPwindow1_AIPDUMMYATTR_DEFAULT 0x01000007U

#define xspimc_AIPwindow1_AIPSUSRESCMD_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSRESCMD_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSRESCMD_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPSUSRESCMD_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSRESCMD_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPSUSRESATTR_READMASK 0x3F1FU
#define xspimc_AIPwindow1_AIPSUSRESATTR_WRITEMASK 0x3F1FU
#define xspimc_AIPwindow1_AIPSUSRESATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPSUSRESATTR_RESETMASK 0x3F1FU
#define xspimc_AIPwindow1_AIPSUSRESATTR_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPSUSTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPSUSTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPDATATTR_READMASK 0xFFU
#define xspimc_AIPwindow1_AIPDATATTR_WRITEMASK 0xFFU
#define xspimc_AIPwindow1_AIPDATATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPDATATTR_RESETMASK 0xFFU
#define xspimc_AIPwindow1_AIPDATATTR_DEFAULT 0x00000001U

#define xspimc_AIPwindow1_AIPRESTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPRESTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPRESTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPRESTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPRESTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPSUSRESTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSRESTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSRESTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPSUSRESTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPSUSRESTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPRESSUSTIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPRESSUSTIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPRESSUSTIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPRESSUSTIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPRESSUSTIME_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPMODEBITS_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPMODEBITS_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPMODEBITS_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPMODEBITS_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPMODEBITS_DEFAULT 0x00000000U

#define xspimc_AIPwindow1_AIPMODEBITSATTR_READMASK 0x13F1FU
#define xspimc_AIPwindow1_AIPMODEBITSATTR_WRITEMASK 0x13F1FU
#define xspimc_AIPwindow1_AIPMODEBITSATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPMODEBITSATTR_RESETMASK 0x13F1FU
#define xspimc_AIPwindow1_AIPMODEBITSATTR_DEFAULT 0x00010000U

#define xspimc_AIPwindow1_AIPPRCMDATTR_READMASK 0x67F0FU
#define xspimc_AIPwindow1_AIPPRCMDATTR_WRITEMASK 0x67F0FU
#define xspimc_AIPwindow1_AIPPRCMDATTR_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPPRCMDATTR_RESETMASK 0x67F0FU
#define xspimc_AIPwindow1_AIPPRCMDATTR_DEFAULT 0x00000107U

#define xspimc_AIPwindow1_AIPPAGETIME_READMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPPAGETIME_WRITEMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPPAGETIME_VOLATILEMASK 0x0U
#define xspimc_AIPwindow1_AIPPAGETIME_RESETMASK 0xFFFFFFFFU
#define xspimc_AIPwindow1_AIPPAGETIME_DEFAULT 0x00000000U

#define xspimc_s_SIZE 0x2E0U

#define xspimc_CSR_SIZE 0x2E0U

#define xspimc_s_SIZE 0x2E0U

#define xspimc_GLBLCTRL_SIZE 0x4U

#define xspimc_SPICLKCFG_SIZE 0x4U

#define xspimc_MINCSHIGH_SIZE 0x4U

#define xspimc_FIFOSTS_SIZE 0x4U

#define xspimc_SPISTS_SIZE 0x4U

#define xspimc_IRQCTRL_SIZE 0x4U

#define xspimc_SPICMD_SIZE 0x4U

#define xspimc_SPICMDATTR_SIZE 0x4U

#define xspimc_SPIADDR_SIZE 0x4U

#define xspimc_SPIADDRATTR_SIZE 0x4U

#define xspimc_SPICS_SIZE 0x4U

#define xspimc_SPIDUMMYATTR_SIZE 0x4U

#define xspimc_AIPHOLDOFFTIME_SIZE 0x4U

#define xspimc_AIPHOLDOFFSEL_SIZE 0x4U

#define xspimc_AIPHOLDOFFCTRL_SIZE 0x4U

#define xspimc_SPIDATASIZE_SIZE 0x4U

#define xspimc_SPIDATAATTR_SIZE 0x4U

#define xspimc_SPITXDATA_SIZE 0x4U

#define xspimc_SPIRXDATA_SIZE 0x4U

#define xspimc_SPIMODEBITS_SIZE 0x4U

#define xspimc_SPIMODEBITSATTR_SIZE 0x4U

#define xspimc_AIPwindow0_SIZE 0x60U

#define xspimc_AIPwindow0_AIPCTRL_SIZE 0x4U

#define xspimc_AIPwindow0_AIPACCB_SIZE 0x4U

#define xspimc_AIPwindow0_AIPSIZE_SIZE 0x4U

#define xspimc_AIPwindow0_AIPWINADDR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPCMD_SIZE 0x4U

#define xspimc_AIPwindow0_AIPCMDATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPDIECMD_SIZE 0x4U

#define xspimc_AIPwindow0_AIPDIEATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPADRBASE_SIZE 0x4U

#define xspimc_AIPwindow0_AIPADRATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPCS_SIZE 0x4U

#define xspimc_AIPwindow0_AIPDIEPAGESTATE_SIZE 0x4U

#define xspimc_AIPwindow0_AIPDUMMYATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPSUSRESCMD_SIZE 0x4U

#define xspimc_AIPwindow0_AIPSUSRESATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPSUSTIME_SIZE 0x4U

#define xspimc_AIPwindow0_AIPDATATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPRESTIME_SIZE 0x4U

#define xspimc_AIPwindow0_AIPSUSRESTIME_SIZE 0x4U

#define xspimc_AIPwindow0_AIPRESSUSTIME_SIZE 0x4U

#define xspimc_AIPwindow0_AIPMODEBITS_SIZE 0x4U

#define xspimc_AIPwindow0_AIPMODEBITSATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPPRCMDATTR_SIZE 0x4U

#define xspimc_AIPwindow0_AIPPAGETIME_SIZE 0x4U

#define xspimc_DMASTARTADR_SIZE 0x4U

#define xspimc_DMAFXDBL_SIZE 0x4U

#define xspimc_DMASTS_SIZE 0x4U

#define xspimc_DMABDCNT_SIZE 0x4U

#define xspimc_GPIO_SIZE 0x4U

#define xspimc_GPIOOE_SIZE 0x4U

#define xspimc_WPCTRL_SIZE 0x4U

#define xspimc_HOLDTIME_SIZE 0x4U

#define xspimc_ACFGCTRL_SIZE 0x4U

#define xspimc_VERSION_SIZE 0x4U

#define xspimc_AIPIMPFEAT_SIZE 0x4U

#define xspimc_AIPIMPCSW_SIZE 0x4U

#define xspimc_AIPIMPGPIOW_SIZE 0x4U

#define xspimc_AIPIMPDQWIDTH_SIZE 0x4U

#define xspimc_GPIOIMPCDC_SIZE 0x4U

#define xspimc_AIPIMPTYPE_SIZE 0x4U

#define xspimc_AIPIMPAW_SIZE 0x4U

#define xspimc_AIPIMPIDW_SIZE 0x4U

#define xspimc_CFGFIFOAW_SIZE 0x4U

#define xspimc_IMPWRFIFOAW_SIZE 0x4U

#define xspimc_IMPRDFIFOAW_SIZE 0x4U

#define xspimc_ACFGROMAW_SIZE 0x4U

#define xspimc_IMPDMAAW_SIZE 0x4U

#define xspimc_ADDRDECN_SIZE 0x4U

#define xspimc_AIPwindow1_SIZE 0x60U

#define xspimc_AIPwindow1_AIPCTRL_SIZE 0x4U

#define xspimc_AIPwindow1_AIPACCB_SIZE 0x4U

#define xspimc_AIPwindow1_AIPSIZE_SIZE 0x4U

#define xspimc_AIPwindow1_AIPWINADDR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPCMD_SIZE 0x4U

#define xspimc_AIPwindow1_AIPCMDATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPDIECMD_SIZE 0x4U

#define xspimc_AIPwindow1_AIPDIEATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPADRBASE_SIZE 0x4U

#define xspimc_AIPwindow1_AIPADRATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPCS_SIZE 0x4U

#define xspimc_AIPwindow1_AIPDIEPAGESTATE_SIZE 0x4U

#define xspimc_AIPwindow1_AIPDUMMYATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPSUSRESCMD_SIZE 0x4U

#define xspimc_AIPwindow1_AIPSUSRESATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPSUSTIME_SIZE 0x4U

#define xspimc_AIPwindow1_AIPDATATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPRESTIME_SIZE 0x4U

#define xspimc_AIPwindow1_AIPSUSRESTIME_SIZE 0x4U

#define xspimc_AIPwindow1_AIPRESSUSTIME_SIZE 0x4U

#define xspimc_AIPwindow1_AIPMODEBITS_SIZE 0x4U

#define xspimc_AIPwindow1_AIPMODEBITSATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPPRCMDATTR_SIZE 0x4U

#define xspimc_AIPwindow1_AIPPAGETIME_SIZE 0x4U


#define xspimc_s_OFFSET 0x0
#define xspimc_CSR_OFFSET 0x0
#define xspimc_s_OFFSET 0x0

#define xspimc_GLBLCTRL_OFFSET 0x0

#define xspimc_SPICLKCFG_OFFSET 0x4

#define xspimc_MINCSHIGH_OFFSET 0x8

#define xspimc_FIFOSTS_OFFSET 0x10

#define xspimc_SPISTS_OFFSET 0x14

#define xspimc_IRQCTRL_OFFSET 0x18

#define xspimc_SPICMD_OFFSET 0x20

#define xspimc_SPICMDATTR_OFFSET 0x24

#define xspimc_SPIADDR_OFFSET 0x30

#define xspimc_SPIADDRATTR_OFFSET 0x34

#define xspimc_SPICS_OFFSET 0x38

#define xspimc_SPIDUMMYATTR_OFFSET 0x40

#define xspimc_AIPHOLDOFFTIME_OFFSET 0x44

#define xspimc_AIPHOLDOFFSEL_OFFSET 0x48

#define xspimc_AIPHOLDOFFCTRL_OFFSET 0x4C

#define xspimc_SPIDATASIZE_OFFSET 0x50

#define xspimc_SPIDATAATTR_OFFSET 0x54

#define xspimc_SPITXDATA_OFFSET 0x58

#define xspimc_SPIRXDATA_OFFSET 0x5C

#define xspimc_SPIMODEBITS_OFFSET 0x68

#define xspimc_SPIMODEBITSATTR_OFFSET 0x6C
#define xspimc_AIPwindow0_OFFSET 0x80

#define xspimc_AIPwindow0_AIPCTRL_OFFSET 0x0

#define xspimc_AIPwindow0_AIPACCB_OFFSET 0x4

#define xspimc_AIPwindow0_AIPSIZE_OFFSET 0x8

#define xspimc_AIPwindow0_AIPWINADDR_OFFSET 0xC

#define xspimc_AIPwindow0_AIPCMD_OFFSET 0x10

#define xspimc_AIPwindow0_AIPCMDATTR_OFFSET 0x14

#define xspimc_AIPwindow0_AIPDIECMD_OFFSET 0x18

#define xspimc_AIPwindow0_AIPDIEATTR_OFFSET 0x1C

#define xspimc_AIPwindow0_AIPADRBASE_OFFSET 0x20

#define xspimc_AIPwindow0_AIPADRATTR_OFFSET 0x24

#define xspimc_AIPwindow0_AIPCS_OFFSET 0x28

#define xspimc_AIPwindow0_AIPDIEPAGESTATE_OFFSET 0x2C

#define xspimc_AIPwindow0_AIPDUMMYATTR_OFFSET 0x30

#define xspimc_AIPwindow0_AIPSUSRESCMD_OFFSET 0x34

#define xspimc_AIPwindow0_AIPSUSRESATTR_OFFSET 0x38

#define xspimc_AIPwindow0_AIPSUSTIME_OFFSET 0x3C

#define xspimc_AIPwindow0_AIPDATATTR_OFFSET 0x40

#define xspimc_AIPwindow0_AIPRESTIME_OFFSET 0x44

#define xspimc_AIPwindow0_AIPSUSRESTIME_OFFSET 0x48

#define xspimc_AIPwindow0_AIPRESSUSTIME_OFFSET 0x4C

#define xspimc_AIPwindow0_AIPMODEBITS_OFFSET 0x50

#define xspimc_AIPwindow0_AIPMODEBITSATTR_OFFSET 0x54

#define xspimc_AIPwindow0_AIPPRCMDATTR_OFFSET 0x58

#define xspimc_AIPwindow0_AIPPAGETIME_OFFSET 0x5C

#define xspimc_DMASTARTADR_OFFSET 0xE0

#define xspimc_DMAFXDBL_OFFSET 0xE4

#define xspimc_DMASTS_OFFSET 0xE8

#define xspimc_DMABDCNT_OFFSET 0xEC

#define xspimc_GPIO_OFFSET 0xF0

#define xspimc_GPIOOE_OFFSET 0xF4

#define xspimc_WPCTRL_OFFSET 0xF8

#define xspimc_HOLDTIME_OFFSET 0xFC

#define xspimc_ACFGCTRL_OFFSET 0x100

#define xspimc_VERSION_OFFSET 0x134

#define xspimc_AIPIMPFEAT_OFFSET 0x180

#define xspimc_AIPIMPCSW_OFFSET 0x184

#define xspimc_AIPIMPGPIOW_OFFSET 0x188

#define xspimc_AIPIMPDQWIDTH_OFFSET 0x18C

#define xspimc_GPIOIMPCDC_OFFSET 0x190

#define xspimc_AIPIMPTYPE_OFFSET 0x194

#define xspimc_AIPIMPAW_OFFSET 0x198

#define xspimc_AIPIMPIDW_OFFSET 0x19C

#define xspimc_CFGFIFOAW_OFFSET 0x1A0

#define xspimc_IMPWRFIFOAW_OFFSET 0x1A8

#define xspimc_IMPRDFIFOAW_OFFSET 0x1B0

#define xspimc_ACFGROMAW_OFFSET 0x1B8

#define xspimc_IMPDMAAW_OFFSET 0x1BC

#define xspimc_ADDRDECN_OFFSET 0x1C0
#define xspimc_AIPwindow1_OFFSET 0x280

#define xspimc_AIPwindow1_AIPCTRL_OFFSET 0x0

#define xspimc_AIPwindow1_AIPACCB_OFFSET 0x4

#define xspimc_AIPwindow1_AIPSIZE_OFFSET 0x8

#define xspimc_AIPwindow1_AIPWINADDR_OFFSET 0xC

#define xspimc_AIPwindow1_AIPCMD_OFFSET 0x10

#define xspimc_AIPwindow1_AIPCMDATTR_OFFSET 0x14

#define xspimc_AIPwindow1_AIPDIECMD_OFFSET 0x18

#define xspimc_AIPwindow1_AIPDIEATTR_OFFSET 0x1C

#define xspimc_AIPwindow1_AIPADRBASE_OFFSET 0x20

#define xspimc_AIPwindow1_AIPADRATTR_OFFSET 0x24

#define xspimc_AIPwindow1_AIPCS_OFFSET 0x28

#define xspimc_AIPwindow1_AIPDIEPAGESTATE_OFFSET 0x2C

#define xspimc_AIPwindow1_AIPDUMMYATTR_OFFSET 0x30

#define xspimc_AIPwindow1_AIPSUSRESCMD_OFFSET 0x34

#define xspimc_AIPwindow1_AIPSUSRESATTR_OFFSET 0x38

#define xspimc_AIPwindow1_AIPSUSTIME_OFFSET 0x3C

#define xspimc_AIPwindow1_AIPDATATTR_OFFSET 0x40

#define xspimc_AIPwindow1_AIPRESTIME_OFFSET 0x44

#define xspimc_AIPwindow1_AIPSUSRESTIME_OFFSET 0x48

#define xspimc_AIPwindow1_AIPRESSUSTIME_OFFSET 0x4C

#define xspimc_AIPwindow1_AIPMODEBITS_OFFSET 0x50

#define xspimc_AIPwindow1_AIPMODEBITSATTR_OFFSET 0x54

#define xspimc_AIPwindow1_AIPPRCMDATTR_OFFSET 0x58

#define xspimc_AIPwindow1_AIPPAGETIME_OFFSET 0x5C

#define xspimc_s_ADDRESS 0x000
#define xspimc_CSR_ADDRESS 0x000
#define xspimc_s_ADDRESS 0x000
#define xspimc_GLBLCTRL_ADDRESS 0x000
#define xspimc_SPICLKCFG_ADDRESS 0x004
#define xspimc_MINCSHIGH_ADDRESS 0x008
#define xspimc_FIFOSTS_ADDRESS 0x010
#define xspimc_SPISTS_ADDRESS 0x014
#define xspimc_IRQCTRL_ADDRESS 0x018
#define xspimc_SPICMD_ADDRESS 0x020
#define xspimc_SPICMDATTR_ADDRESS 0x024
#define xspimc_SPIADDR_ADDRESS 0x030
#define xspimc_SPIADDRATTR_ADDRESS 0x034
#define xspimc_SPICS_ADDRESS 0x038
#define xspimc_SPIDUMMYATTR_ADDRESS 0x040
#define xspimc_AIPHOLDOFFTIME_ADDRESS 0x044
#define xspimc_AIPHOLDOFFSEL_ADDRESS 0x048
#define xspimc_AIPHOLDOFFCTRL_ADDRESS 0x04C
#define xspimc_SPIDATASIZE_ADDRESS 0x050
#define xspimc_SPIDATAATTR_ADDRESS 0x054
#define xspimc_SPITXDATA_ADDRESS 0x058
#define xspimc_SPIRXDATA_ADDRESS 0x05C
#define xspimc_SPIMODEBITS_ADDRESS 0x068
#define xspimc_SPIMODEBITSATTR_ADDRESS 0x06C
#define xspimc_AIPwindow0_ADDRESS 0x080
#define xspimc_AIPwindow0_AIPCTRL_ADDRESS 0x080
#define xspimc_AIPwindow0_AIPACCB_ADDRESS 0x084
#define xspimc_AIPwindow0_AIPSIZE_ADDRESS 0x088
#define xspimc_AIPwindow0_AIPWINADDR_ADDRESS 0x08C
#define xspimc_AIPwindow0_AIPCMD_ADDRESS 0x090
#define xspimc_AIPwindow0_AIPCMDATTR_ADDRESS 0x094
#define xspimc_AIPwindow0_AIPDIECMD_ADDRESS 0x098
#define xspimc_AIPwindow0_AIPDIEATTR_ADDRESS 0x09C
#define xspimc_AIPwindow0_AIPADRBASE_ADDRESS 0x0A0
#define xspimc_AIPwindow0_AIPADRATTR_ADDRESS 0x0A4
#define xspimc_AIPwindow0_AIPCS_ADDRESS 0x0A8
#define xspimc_AIPwindow0_AIPDIEPAGESTATE_ADDRESS 0x0AC
#define xspimc_AIPwindow0_AIPDUMMYATTR_ADDRESS 0x0B0
#define xspimc_AIPwindow0_AIPSUSRESCMD_ADDRESS 0x0B4
#define xspimc_AIPwindow0_AIPSUSRESATTR_ADDRESS 0x0B8
#define xspimc_AIPwindow0_AIPSUSTIME_ADDRESS 0x0BC
#define xspimc_AIPwindow0_AIPDATATTR_ADDRESS 0x0C0
#define xspimc_AIPwindow0_AIPRESTIME_ADDRESS 0x0C4
#define xspimc_AIPwindow0_AIPSUSRESTIME_ADDRESS 0x0C8
#define xspimc_AIPwindow0_AIPRESSUSTIME_ADDRESS 0x0CC
#define xspimc_AIPwindow0_AIPMODEBITS_ADDRESS 0x0D0
#define xspimc_AIPwindow0_AIPMODEBITSATTR_ADDRESS 0x0D4
#define xspimc_AIPwindow0_AIPPRCMDATTR_ADDRESS 0x0D8
#define xspimc_AIPwindow0_AIPPAGETIME_ADDRESS 0x0DC
#define xspimc_DMASTARTADR_ADDRESS 0x0E0
#define xspimc_DMAFXDBL_ADDRESS 0x0E4
#define xspimc_DMASTS_ADDRESS 0x0E8
#define xspimc_DMABDCNT_ADDRESS 0x0EC
#define xspimc_GPIO_ADDRESS 0x0F0
#define xspimc_GPIOOE_ADDRESS 0x0F4
#define xspimc_WPCTRL_ADDRESS 0x0F8
#define xspimc_HOLDTIME_ADDRESS 0x0FC
#define xspimc_ACFGCTRL_ADDRESS 0x100
#define xspimc_VERSION_ADDRESS 0x134
#define xspimc_AIPIMPFEAT_ADDRESS 0x180
#define xspimc_AIPIMPCSW_ADDRESS 0x184
#define xspimc_AIPIMPGPIOW_ADDRESS 0x188
#define xspimc_AIPIMPDQWIDTH_ADDRESS 0x18C
#define xspimc_GPIOIMPCDC_ADDRESS 0x190
#define xspimc_AIPIMPTYPE_ADDRESS 0x194
#define xspimc_AIPIMPAW_ADDRESS 0x198
#define xspimc_AIPIMPIDW_ADDRESS 0x19C
#define xspimc_CFGFIFOAW_ADDRESS 0x1A0
#define xspimc_IMPWRFIFOAW_ADDRESS 0x1A8
#define xspimc_IMPRDFIFOAW_ADDRESS 0x1B0
#define xspimc_ACFGROMAW_ADDRESS 0x1B8
#define xspimc_IMPDMAAW_ADDRESS 0x1BC
#define xspimc_ADDRDECN_ADDRESS 0x1C0
#define xspimc_AIPwindow1_ADDRESS 0x280
#define xspimc_AIPwindow1_AIPCTRL_ADDRESS 0x280
#define xspimc_AIPwindow1_AIPACCB_ADDRESS 0x284
#define xspimc_AIPwindow1_AIPSIZE_ADDRESS 0x288
#define xspimc_AIPwindow1_AIPWINADDR_ADDRESS 0x28C
#define xspimc_AIPwindow1_AIPCMD_ADDRESS 0x290
#define xspimc_AIPwindow1_AIPCMDATTR_ADDRESS 0x294
#define xspimc_AIPwindow1_AIPDIECMD_ADDRESS 0x298
#define xspimc_AIPwindow1_AIPDIEATTR_ADDRESS 0x29C
#define xspimc_AIPwindow1_AIPADRBASE_ADDRESS 0x2A0
#define xspimc_AIPwindow1_AIPADRATTR_ADDRESS 0x2A4
#define xspimc_AIPwindow1_AIPCS_ADDRESS 0x2A8
#define xspimc_AIPwindow1_AIPDIEPAGESTATE_ADDRESS 0x2AC
#define xspimc_AIPwindow1_AIPDUMMYATTR_ADDRESS 0x2B0
#define xspimc_AIPwindow1_AIPSUSRESCMD_ADDRESS 0x2B4
#define xspimc_AIPwindow1_AIPSUSRESATTR_ADDRESS 0x2B8
#define xspimc_AIPwindow1_AIPSUSTIME_ADDRESS 0x2BC
#define xspimc_AIPwindow1_AIPDATATTR_ADDRESS 0x2C0
#define xspimc_AIPwindow1_AIPRESTIME_ADDRESS 0x2C4
#define xspimc_AIPwindow1_AIPSUSRESTIME_ADDRESS 0x2C8
#define xspimc_AIPwindow1_AIPRESSUSTIME_ADDRESS 0x2CC
#define xspimc_AIPwindow1_AIPMODEBITS_ADDRESS 0x2D0
#define xspimc_AIPwindow1_AIPMODEBITSATTR_ADDRESS 0x2D4
#define xspimc_AIPwindow1_AIPPRCMDATTR_ADDRESS 0x2D8
#define xspimc_AIPwindow1_AIPPAGETIME_ADDRESS 0x2DC
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_OFFSET 16  /* DMAENABLE DESCRIPTION :To complete next command using DMA, set this bit to 1.  */
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_MASK 0x10000U
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_GLBLCTRL_DMAENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_OFFSET 0  /* AUTOCFGRESTART DESCRIPTION :When set to 1, the autoconfiguration procedure is repeated, if implemented.
Registers keep their old values.  */
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_MASK 0x1U
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_SIZE 1U
#define XSPI_MC_REGISTERS_GLBLCTRL_AUTOCFGRESTART_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_OFFSET 24  /* SAMPLEPOINT DESCRIPTION :Sets the sampling point of the input. The sampling point is
given as a number of clock cycles, less one, since the
refernce edge. See section 6.2.3 'SPI input behaviour'.  */
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_MASK 0xFF000000U
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_INV_MASK 0xFFFFFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_VALUE_MASK 0x7F800000U
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_INV_VALUE_MASK 0x807FFFFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_SIZE 8U
#define XSPI_MC_REGISTERS_SPICLKCFG_SAMPLEPOINT_DEFAULT 15U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_OFFSET 17  /* CLOCKPOLARITY DESCRIPTION :Selects the clock polarity as follows:
0: SPI clock output starts low and ends low
1: SPI clock output starts high and ends high  */
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_MASK 0x20000U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_INV_MASK 0xFFFDFFFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_VALUE_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_INV_VALUE_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_SIZE 1U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPOLARITY_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_OFFSET 16  /* TRANSMITDATAON DESCRIPTION :Select the clock edge on which the output data is changed (see
section 6.2.1) as follows:
1: Change output on the positive edge
0: Change output on the negative edge  */
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_SIZE 1U
#define XSPI_MC_REGISTERS_SPICLKCFG_TRANSMITDATAON_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_OFFSET 8  /* MINCSLOW DESCRIPTION :Time between CS going active and first clock edge, and time
from last clock edge to CS going inactive. The time is given in a
number of input clock cycles as follows:
Min. CS Low + 1
See section 6.2.1 'SPI output behaviour' for details.  */
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_MASK 0xFF00U
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_INV_MASK 0xFFFF00FFU
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_VALUE_MASK 0x7F80U
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_INV_VALUE_MASK 0xFFFF807FU
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_SIZE 8U
#define XSPI_MC_REGISTERS_SPICLKCFG_MINCSLOW_DEFAULT 7U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_OFFSET 0  /* CLOCKPERIOD DESCRIPTION :The period of the SPI output clock.
The internal SPI clock is divided by the following value to
provide the SPI output clock:
(Clock period + 1)
Note that the PHY used may have some restriction on the clock
divider value. For example some PHYs only support even clock
division factors.  */
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_MASK 0xFFU
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_INV_MASK 0xFFFFFF00U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_VALUE_MASK 0x7FU
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_INV_VALUE_MASK 0xFFFFFF80U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_SIZE 8U
#define XSPI_MC_REGISTERS_SPICLKCFG_CLOCKPERIOD_DEFAULT 15U
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_OFFSET 0  /* MINCSHIGH DESCRIPTION :Whenever the SPI memory controller is required to drive the CS line inactive, the
SPI controller will wait for the following number of internal SPI clock cycles
before driving it active again:
Min. CS High + 1  */
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_MASK 0xFFU
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_INV_MASK 0xFFFFFF00U
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_VALUE_MASK 0x7FU
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_INV_VALUE_MASK 0xFFFFFF80U
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_SIZE 8U
#define XSPI_MC_REGISTERS_MINCSHIGH_MINCSHIGH_DEFAULT 0U
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_OFFSET 17  /* FULL DESCRIPTION :The FIFO is full if this is set to 1  */
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_MASK 0x20000U
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_INV_MASK 0xFFFDFFFFU
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_VALUE_MASK 0x10000U
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_INV_VALUE_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_SIZE 1U
#define XSPI_MC_REGISTERS_FIFOSTS_FULL_DEFAULT 0U
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_OFFSET 16  /* EMPTY DESCRIPTION :The FIFO is empty if this is set to 1  */
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_MASK 0x10000U
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_SIZE 1U
#define XSPI_MC_REGISTERS_FIFOSTS_EMPTY_DEFAULT 1U
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_OFFSET 0  /* FIFOFILL DESCRIPTION :Current FIFO fill level.  */
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_MASK 0xFFFFU
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_INV_MASK 0xFFFF0000U
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_VALUE_MASK 0x7FFFU
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_SIZE 16U
#define XSPI_MC_REGISTERS_FIFOSTS_FIFOFILL_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_OFFSET 20  /* WRITEFIFOERROR DESCRIPTION :Erroneous (unexpected) FIFO write detected. It is cleared by writing 1 to it.
Unexpected write events include:
- Writing the FIFO when a read operation has been requested  */
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_MASK 0x100000U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_INV_MASK 0xFFEFFFFFU
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_VALUE_MASK 0x80000U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_INV_VALUE_MASK 0xFFF7FFFFU
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_SIZE 1U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOERROR_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_OFFSET 19  /* READFIFOERROR DESCRIPTION :Erroneous (unexpected) FIFO read detected. It is cleared by writing 1 to it.
Unexpected read events include:
- Reading the FIFO when a write operation has been requested
- Reading the FIFO while empty.  */
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_MASK 0x80000U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_INV_MASK 0xFFF7FFFFU
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_VALUE_MASK 0x40000U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_INV_VALUE_MASK 0xFFFBFFFFU
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_SIZE 1U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOERROR_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_OFFSET 18  /* WRITEFIFOSTATUS DESCRIPTION :0b1 indicates that Write FIFO fill level is less or equal to FIFO boundary. The FIFO boundary is
defined using bits [10:8] in the IRQ Control (0x18).  */
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_MASK 0x40000U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_INV_MASK 0xFFFBFFFFU
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_VALUE_MASK 0x20000U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_INV_VALUE_MASK 0xFFFDFFFFU
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_SIZE 1U
#define XSPI_MC_REGISTERS_SPISTS_WRITEFIFOSTATUS_DEFAULT 1U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_OFFSET 17  /* READFIFOSTATUS DESCRIPTION :b1 indicates that Read FIFO fill level is greater than FIFO boundary. The FIFO boundary is
defined using bits [10:8] in the IRQ Control (0x18).  */
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_MASK 0x20000U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_INV_MASK 0xFFFDFFFFU
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_VALUE_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_INV_VALUE_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_SIZE 1U
#define XSPI_MC_REGISTERS_SPISTS_READFIFOSTATUS_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPISTS_BUSY_OFFSET 16  /* BUSY DESCRIPTION :0b1 indicates SPI engine is busy performing an SPI memory access. While this
is set to 1 the configuration may not be changed nor new commands issued.  */
#define XSPI_MC_REGISTERS_SPISTS_BUSY_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPISTS_BUSY_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPISTS_BUSY_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPISTS_BUSY_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPISTS_BUSY_SIZE 1U
#define XSPI_MC_REGISTERS_SPISTS_BUSY_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_OFFSET 0  /* ENABLED DESCRIPTION :This bit is set when the controller has completed its internal initialization (all
resets are de-asserted) and all requested startup functions have been
completed (auto-configure and/or DMA boot loader copy).
While this bit is set to 0, no command may be issued  */
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_MASK 0x1U
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_SIZE 1U
#define XSPI_MC_REGISTERS_SPISTS_ENABLED_DEFAULT 1U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_OFFSET 18  /* DMAERRORIRQENABLE DESCRIPTION :RQ active when this bit is 0b1 and DMA Error Status is 0b1.  */
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_MASK 0x40000U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_INV_MASK 0xFFFBFFFFU
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_VALUE_MASK 0x20000U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_INV_VALUE_MASK 0xFFFDFFFFU
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAERRORIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_OFFSET 17  /* DMAIRQENABLE DESCRIPTION :IRQ active when this bit is 0b1 and DMA IRQ Status is 0b1  */
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_MASK 0x20000U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_INV_MASK 0xFFFDFFFFU
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_VALUE_MASK 0x10000U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_INV_VALUE_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_OFFSET 16  /* DMAIDLEIRQENABLE DESCRIPTION :IRQ active when this bit is 0b1 and DMA Idle Status is 0b1.  */
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_MASK 0x10000U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_DMAIDLEIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_OFFSET 8  /* FIFOBOUNDARY DESCRIPTION :FIFO fill limits setting in 1/8 of FIFO depth steps.
For example:
- 0x0 activates Read FIFO Status when FIFO is at least 1/8 full
during or after read command.
- 0x7 activates Read FIFO Status only when FIFO is full during or
after read command.
- 0x0 activates Write FIFO Status when FIFO is less than 1/8 full
during write command.
- 0x7 activates Write FIFO Status when FIFO is not full during write
command.  */
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_MASK 0x700U
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_INV_MASK 0xFFFFF8FFU
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_VALUE_MASK 0x380U
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_INV_VALUE_MASK 0xFFFFFC7FU
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_SIZE 3U
#define XSPI_MC_REGISTERS_IRQCTRL_FIFOBOUNDARY_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_OFFSET 4  /* WRITEFIFOERRORIRQENABLE DESCRIPTION :IRQ active when this bit is 0b1 and SPI Status (0x0014) bit [20] is 0b1.  */
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_MASK 0x10U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_INV_MASK 0xFFFFFFEFU
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_VALUE_MASK 0x8U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_INV_VALUE_MASK 0xFFFFFFF7U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOERRORIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_OFFSET 3  /* READFIFOERRORIRQENABLE DESCRIPTION :If this bit is set to 1, the SPI memory controller will interrupt if it is not
busy (i.e. when bit [16] in the SPI Status (0x0014) register is set to 1).  */
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_MASK 0x8U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_INV_MASK 0xFFFFFFF7U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_VALUE_MASK 0x4U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_INV_VALUE_MASK 0xFFFFFFFBU
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOERRORIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_OFFSET 2  /* WRITEFIFOFILLIRQENABLE DESCRIPTION :Enable interrupt when the read FIFO fill level is more than the level set by
bits [10:8] of this register (bit [17] of the SPI Status (0x0014) register).
In XIP mode the read FIFO fill level interrupt is unconditionally disabled,
irrespective of this bit.
Should be 0 during DMA, write or commands without data.  */
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_MASK 0x4U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_INV_MASK 0xFFFFFFFBU
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_VALUE_MASK 0x2U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_INV_VALUE_MASK 0xFFFFFFFDU
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_WRITEFIFOFILLIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_OFFSET 1  /* READFIFOFILLIRQENABLE DESCRIPTION :Enable interrupt when the write FIFO fill level is less-than or equal to the
level set by bits [10:8] of this register (bit [18] of the SPI Status (0x0014)
register).
In XIP mode the write FIFO fill level interrupt is unconditionally disabled,
irrespective of this bit.
This bit should be 0 during DMA, read or commands without data.  */
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_MASK 0x2U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_INV_MASK 0xFFFFFFFDU
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_VALUE_MASK 0x1U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_INV_VALUE_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_READFIFOFILLIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_OFFSET 0  /* NOTBUSYIRQENABLE DESCRIPTION :IRQ active when this bit is 0b1 and SPI Status (0x0014) bit [19] is 0b1.  */
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_MASK 0x1U
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_SIZE 1U
#define XSPI_MC_REGISTERS_IRQCTRL_NOTBUSYIRQENABLE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_OFFSET 0  /* COMMAND DESCRIPTION :For commands less than 16 bits wide, align command's most significant bit to
bit [15].  */
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_MASK 0xFFFFU
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_INV_MASK 0xFFFF0000U
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_VALUE_MASK 0x7FFFU
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_SIZE 16U
#define XSPI_MC_REGISTERS_SPICMD_COMMAND_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_OFFSET 31  /* WRITEERASE DESCRIPTION :This bit is only implemented when AIP_IMPL=0.
When this bit is set, accesses on AIP are either denied or RWW support
is enabled. Refer to section 6.3.2 'Read while Write support' for more
information on this feature.  */
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_INV_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_VALUE_MASK 0x40000000U
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_INV_VALUE_MASK 0xBFFFFFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_SIZE 1U
#define XSPI_MC_REGISTERS_SPICMDATTR_WRITEERASE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the command phase is to be skipped or not on
the next SPI transaction and is encoded as follows:
0: Command phase is present
1: Command phase is skipped  */
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_SIZE 1U
#define XSPI_MC_REGISTERS_SPICMDATTR_SKIP_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_OFFSET 15  /* HYPERRAM DESCRIPTION :Selects if the outgoing command uses the HyperRAM format. If this bit is set to 1, command generation occurs internally and the contents of register New AIP Command(window offset 0x10) is ignored.  */
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_INV_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_VALUE_MASK 0x4000U
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_INV_VALUE_MASK 0xFFFFBFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_SIZE 1U
#define XSPI_MC_REGISTERS_SPICMDATTR_HYPERRAM_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_REGISTERS_SPICMDATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the command phase is executed in DDR mode
(using both edges of the output clock) and is encoded as follows:
0: Normal (STR) output mode is used
1: DDR (DTR) output mode is used  */
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_SIZE 1U
#define XSPI_MC_REGISTERS_SPICMDATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the command output,
encoded as follows:
- 0x9 = 16-bit (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_MASK 0xF00U
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_SIZE 4U
#define XSPI_MC_REGISTERS_SPICMDATTR_MODE_DEFAULT 1U
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the command phase of the SPI
transaction in SPI clock cycles minus 1.
A few examples:
- 8-bit command in STR Octa mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR Octa mode: 0
- 16-bit command in x16 mode: 0  */
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_MASK 0xFU
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_VALUE_MASK 0x7U
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_SIZE 4U
#define XSPI_MC_REGISTERS_SPICMDATTR_DURATION_DEFAULT 7U
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_OFFSET 0  /* ADDRESS DESCRIPTION :This field holds the value of the address output on the address phase of the SPI
transaction.
For addresses less than 32 bits wide, align the most significant bit of the address
to bit [31].  */
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_SIZE 32U
#define XSPI_MC_REGISTERS_SPIADDR_ADDRESS_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_OFFSET 17  /* MASK DESCRIPTION :The lower two bits of address output to the memory chip shall be masked with this value. This may be used to support x16 bus widths where all accesses must be aligned on a 2-byte boundary.  */
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_MASK 0x60000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_INV_MASK 0xFFF9FFFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_VALUE_MASK 0x30000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_INV_VALUE_MASK 0xFFFCFFFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_SIZE 2U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MASK_DEFAULT 3U
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the address phase is to be skipped or not on the
next SPI transaction and is encoded as follows:
0: Address phase is present
1: Address phase is skipped  */
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_SIZE 1U
#define XSPI_MC_REGISTERS_SPIADDRATTR_SKIP_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_REGISTERS_SPIADDRATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the address phase is executed in DDR mode (using
both edges of the output clock) and is encoded as follows:
0: Normal (STR) output mode is used
1: DDR (DTR) output mode is used  */
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_SIZE 1U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the address output, encoded
as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_MASK 0xF00U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_SIZE 4U
#define XSPI_MC_REGISTERS_SPIADDRATTR_MODE_DEFAULT 1U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the address phase of the SPI transaction
in SPI clock cycles minus 1.
A few examples:
- 24-bit address in STR x8 mode: 2
- 24-bit address in STR x1 mode: 23
- 24-bit address in DDR x1 mode: 11
- 32-bit address in DDR x8 mode: 1
- 32-bit address in x16 mode: 1  */
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_MASK 0x1FU
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_SIZE 5U
#define XSPI_MC_REGISTERS_SPIADDRATTR_DURATION_DEFAULT 23U
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_OFFSET 0  /* CHIPSELECT DESCRIPTION :Each bit represents one Chip Select line.
For each bit set in this register, the corresponding chip-select line shall be
active for the next command.
Normally only a single bit is expected to be set in this register; however
multiple set bits may be used for global command broadcasts (e.g. Software
Reset all devices).  */
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_SIZE 32U
#define XSPI_MC_REGISTERS_SPICS_CHIPSELECT_DEFAULT 1U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_OFFSET 25  /* DYNWL DESCRIPTION :If set to 1 write latency will be doubled if data strobe is sampled 1 during the command phase.  */
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_MASK 0x2000000U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_INV_MASK 0xFDFFFFFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_VALUE_MASK 0x1000000U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_INV_VALUE_MASK 0xFEFFFFFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DYNWL_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_OFFSET 24  /* NOWL DESCRIPTION :If set to 1 no write latency will not be inserted  */
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_MASK 0x1000000U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_INV_MASK 0xFEFFFFFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_VALUE_MASK 0x800000U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_INV_VALUE_MASK 0xFF7FFFFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_NOWL_DEFAULT 1U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_OFFSET 16  /* WL DESCRIPTION :Write latency.  */
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_MASK 0x1F0000U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_INV_MASK 0xFFE0FFFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_VALUE_MASK 0xF8000U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_INV_VALUE_MASK 0xFFF07FFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_SIZE 5U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_WL_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_OFFSET 8  /* SKIP DESCRIPTION :This bit selects whether the dummy phase is to be skipped or not on the
next SPI transaction and is encoded as follows:
0: Dummy phase is present
1: Dummy phase is skipped  */
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_MASK 0x100U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_VALUE_MASK 0x80U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_SKIP_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field reflects the length of the dummy phase of the SPI transaction in SPI
clock cycles minus 1.  */
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_MASK 0x1FU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_SIZE 5U
#define XSPI_MC_REGISTERS_SPIDUMMYATTR_DURATION_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_OFFSET 0  /* AIPHOLDOFFTIME DESCRIPTION :his register gives the time during which AIP accesses are denied or RWW is
enabled, when the command is executed with bit [31]=1 in the SPI
Command Attributes (0x024) register.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_SIZE 32U
#define XSPI_MC_REGISTERS_AIPHOLDOFFTIME_AIPHOLDOFFTIME_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_OFFSET 0  /* AIPWINDOWS DESCRIPTION :This register gives the AIP windows for which the AIP hold off should be
applied.  */
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_SIZE 32U
#define XSPI_MC_REGISTERS_AIPHOLDOFFSEL_AIPWINDOWS_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_OFFSET 0  /* AIPHOLDOFFCONTROL DESCRIPTION :For each bit in this register, if set means that the given AIP window has a
hold off in progress.
Writing a 1 to a bit in this register cancels the holdoff for the given AIP
window.  */
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_SIZE 32U
#define XSPI_MC_REGISTERS_AIPHOLDOFFCTRL_AIPHOLDOFFCONTROL_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_OFFSET 0  /* SIZE DESCRIPTION :Number of data bits to transmit or receive, minus 1.
The number of bits provided here must be evenly divisible by the number of bits
handled per clock cycles.
For example, for normal (STR) x4 mode (4-bits/cycle) this register may be set to 4,
8, 12, etc. bits, or for DDR (DTR) x4 mode (8-bits/clock edge) this register may be
set to 16, 32, 24, etc. bits.  */
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_SIZE 32U
#define XSPI_MC_REGISTERS_SPIDATASIZE_SIZE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_OFFSET 16  /* DIRECTION DESCRIPTION :Data direction select:
0: Data is output (SPI memory is written)
1: Data in input (SPI memory is read)  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DIRECTION_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_OFFSET 8  /* SKIP DESCRIPTION :This bit selects whether the data phase is to be skipped or not on the next SPI
transaction and is encoded as follows:
0: Data phase is present
1: Data phase is skipped  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_MASK 0x100U
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_VALUE_MASK 0x80U
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDATAATTR_SKIP_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_OFFSET 7  /* FLIPBYTES DESCRIPTION :Byte order select
0: Return data using the same order as the memory chip provided the data in
1: Flip the order of 4-bits in each 8-bit bytes
This bit only has effect in DDR x4 mode and is ignored in all other cases.  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_MASK 0x80U
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_MASK 0xFFFFFF7FU
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_VALUE_MASK 0x40U
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_INV_VALUE_MASK 0xFFFFFFBFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDATAATTR_FLIPBYTES_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_OFFSET 6  /* DQS DESCRIPTION :Sampling mode to use, encoded as follows:
0: Use normal internal clock for sampling (i.e. no strobe used)
1: Use the strobe signal provided by the SPI memory chip for sampling.
Setting this bit to 1 while not in DDR mode is not supported.  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_MASK 0x40U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_MASK 0xFFFFFFBFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_VALUE_MASK 0x20U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_INV_VALUE_MASK 0xFFFFFFDFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DQS_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_OFFSET 5  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_MASK 0x20U
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_MASK 0xFFFFFFDFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_VALUE_MASK 0x10U
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFFFEFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDATAATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_OFFSET 4  /* DDRMODE DESCRIPTION :This bit selects whether the data phase is executed in DDR mode (using both
edges of the clock) and is encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_MASK 0x10U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_INV_MASK 0xFFFFFFEFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_VALUE_MASK 0x8U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_INV_VALUE_MASK 0xFFFFFFF7U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_SIZE 1U
#define XSPI_MC_REGISTERS_SPIDATAATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_OFFSET 0  /* MODE DESCRIPTION :This field selects the number of lines to use for the data output, encoded as
follows:
- 0x9 = 16bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)  */
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_MASK 0xFU
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_VALUE_MASK 0x7U
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_SIZE 4U
#define XSPI_MC_REGISTERS_SPIDATAATTR_MODE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_OFFSET 0  /* DATA DESCRIPTION :Window into the SPI custom command data FIFO. Writing this register pushes one 32-
bit word into the SPI custom command data FIFO. This data is used in the data phase
of custom transactions. See section 6.4 'Custom SPI command execution'
For data widths less than 32 bits or the last word of a transaction not a multiple of 32-
bits, the most significant data bit must be aligned to bit [31].
Reads return 0 and don't pop the FIFO.  */
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_SIZE 32U
#define XSPI_MC_REGISTERS_SPITXDATA_DATA_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_OFFSET 0  /* DATA DESCRIPTION :Window into the SPI custom command data FIFO. Reading this register pops one
32-bit word from the SPI custom command data FIFO. Read data from the data
phase of custom transactions can be read from this register.
The received data is such that the least-significant bit of the data is aligned to bit
[0] after reception.  */
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_SIZE 32U
#define XSPI_MC_REGISTERS_SPIRXDATA_DATA_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_OFFSET 0  /* BITS DESCRIPTION :SPI Mode bits to use for the mode phase of the SPI transaction.
For data widths less than 32 bits, the most significant data bit must be aligned
to bit [31].  */
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_SIZE 32U
#define XSPI_MC_REGISTERS_SPIMODEBITS_BITS_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the mode phase is to be skipped or not on the next
SPI transaction and is encoded as follows:
0: Mode phase is present
1: Mode phase is skipped  */
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_MASK 0x10000U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_SIZE 1U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_SKIP_DEFAULT 1U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the mode phase is executed in DDR mode (using
both edges of the clock) and is encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_SIZE 1U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :his field selects the number of lines to use for the mode output, encoded as
follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_MASK 0xF00U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_SIZE 4U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_MODE_DEFAULT 0U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the mode phase of the SPI transaction in
SPI clock cycles minus 1.
A few examples:
- 8-bit mode in STR x8 mode: 0
- 8-bit mode in STR x1 mode: 7
- 8-bit mode in DDR x1 mode: 3
- 16-bit mode in DDR x8 mode: 0  */
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_MASK 0x1FU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_SIZE 5U
#define XSPI_MC_REGISTERS_SPIMODEBITSATTR_DURATION_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_OFFSET 9  /* UPDATE DESCRIPTION :If this bit is set to 1, the attributes specified in the New AIP * registers
are applied.  */
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_MASK 0x200U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_INV_MASK 0xFFFFFDFFU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_VALUE_MASK 0x100U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_INV_VALUE_MASK 0xFFFFFEFFU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_UPDATE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_OFFSET 8  /* SUSRES DESCRIPTION :Set to 1 to enable suspend/resume support. Setting this bit is only
applied when bit [9] is also set to 1.  */
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_MASK 0x100U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_VALUE_MASK 0x80U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_SUSRES_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_OFFSET 1  /* BUSY DESCRIPTION :AIP operation state:
0: Idle. AIP transfer is not active.
1: Busy. AIP transfer in progress.  */
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_MASK 0x2U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_INV_MASK 0xFFFFFFFDU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_VALUE_MASK 0x1U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_INV_VALUE_MASK 0xFFFFFFFEU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_BUSY_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_OFFSET 0  /* AIPMODEENABLE DESCRIPTION :AIP window enable:
0: This AIP window is disabled
1: This AIP window is enabled
Any AIP window may be disabled at any time. If an AIP access is in
progress when the AIP window is disabled it will be finished cleanly.  */
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_MASK 0x1U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_VALUE_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCTRL_AIPMODEENABLE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_OFFSET 0  /* AIPACCESSBOUNDARY DESCRIPTION :Access boundary for AIP accesses. For any burst that would pass this
boundary, the controller will end the transaction and start a new one.
For NAND chips, set this register to the page size.
Some PSRAM chips have boundary limitations too.  */
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_MASK 0x1FU
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_SIZE 5U
#define XSPI_MC_AIPWINDOW0_AIPACCB_AIPACCESSBOUNDARY_DEFAULT 31U
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_OFFSET 0  /* AIPSIZE DESCRIPTION :This register gives the size of this AIP window. The size must a power
of two. If the size is 2N, the size is given by setting the low N bits to 1 in
this register and the rest to 0.  */
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPSIZE_AIPSIZE_DEFAULT 2097151U
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_OFFSET 0  /* AIPWINDOWADDRESS DESCRIPTION :For window 0: This register is hard wired to 0
For all other windows this is the window address as given on the
AHB/AXI interface.  */
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPWINADDR_AIPWINDOWADDRESS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_OFFSET 16  /* WCOMMAND DESCRIPTION :SPI command to use for AIP writes in case of PSRAM chips.
Page read command for NAND flash chips.
For commands less than 16 bits wide, align command's most significant bit
to bit 15.  */
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_INV_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_VALUE_MASK 0x7FFF8000U
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_INV_VALUE_MASK 0x80007FFFU
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW0_AIPCMD_WCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_OFFSET 0  /* RCOMMAND DESCRIPTION :SPI command to use for AIP reads. For commands less than 16 bits wide,
align command's most significant bit to bit 15.  */
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_INV_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_VALUE_MASK 0x7FFFU
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW0_AIPCMD_RCOMMAND_DEFAULT 2816U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the command phase is to be skipped or not
for AIP-based SPI transactions and is encoded as follows:
0: Command phase is present
1: Command phase is skipped  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_MASK 0x10000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_SKIP_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_OFFSET 15  /* HYPERAMCOMMAND DESCRIPTION :Selects if the outgoing command uses the HyperRAM format. If this bit
is set to 1, command generation occurs internally and the contents of
register New AIP Command(window offset 0x10) is ignored.  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_MASK 0x8000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_INV_MASK 0xFFFF7FFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_VALUE_MASK 0x4000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_INV_VALUE_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_HYPERAMCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_OFFSET 14  /* WRITESUPPORT DESCRIPTION :Selects if the outgoing command uses the HyperRAM format. If this bit
is set to 1, command generation occurs internally and the contents of
register New AIP Command(window offset 0x10) is ignored.  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_MASK 0x4000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_INV_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_VALUE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_INV_VALUE_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_WRITESUPPORT_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the command phase is executed in DDR mode
(using both edges of the output clock) and is encoded as follows:
0: Normal (STR) output mode is used
1: DDR (DTR) output mode is used  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for AIP command output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the command phase of the AIP
read in SPI clock cycles minus 1.
A few examples:
- 8-bit command in STR x8 mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_MASK 0x7U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_INV_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_VALUE_MASK 0x3U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_INV_VALUE_MASK 0xFFFFFFFCU
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_SIZE 3U
#define XSPI_MC_AIPWINDOW0_AIPCMDATTR_DURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_OFFSET 16  /* ADDRBITSINDIE DESCRIPTION :Number of address bits on a single die. If only a single die is supported, set
this to 0x1f.  */
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_MASK 0x1F0000U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_INV_MASK 0xFFE0FFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_VALUE_MASK 0xF8000U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_INV_VALUE_MASK 0xFFF07FFFU
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_SIZE 5U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_ADDRBITSINDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_OFFSET 0  /* DIESELECTCMD DESCRIPTION :The SPI command that selects the active die.
For commands less than 16 bits wide, align command's most significant bit to
bit 15.  */
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_INV_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_VALUE_MASK 0x7FFFU
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_SIZE 16U
#define XSPI_MC_AIPWINDOW0_AIPDIECMD_DIESELECTCMD_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_OFFSET 16  /* ADDRESSWIDTH DESCRIPTION :Address_width in the die select command as follows:
0: Use 24-bit address field
1: Use 32-bit address field
2: Use 16-bit address field
3: Use 8-bit address field  */
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_MASK 0x30000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_INV_MASK 0xFFFCFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_VALUE_MASK 0x18000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_INV_VALUE_MASK 0xFFFE7FFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_SIZE 2U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_ADDRESSWIDTH_DEFAULT 3U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_OFFSET 14  /* DIEENABLE DESCRIPTION :When set to 0 the controller does not send Die select commands. Settings this bit to 1 allows the controller to send Die select commands.  */
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_MASK 0x4000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_INV_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_VALUE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_INV_VALUE_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DIEENABLE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :Die select, include die mode in DDR mode after update.  */
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the die select command
including the die number, encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_OFFSET 0  /* COMMANDDURATION DESCRIPTION :This field must reflect the length of the die select command in SPI clock
cycles minus 1.
A few examples:
- 8-bit command in STR x8 mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_VALUE_MASK 0x7U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPDIEATTR_COMMANDDURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_OFFSET 0  /* BASEADDRESS DESCRIPTION :This register selects the memory address to which the controller maps
address 0 on the AIP slave interface. This base address must be aligned to the
value given in the New AIP Size (widow offset 0x08) register.
For example, if the New AIP Size (window offset 0x08) register is set to 17 (a
128KB window), the Base_Address may be set to any multiple of 128KB, e.g.
128KB, 256KB, 384KB, etc.  */
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPADRBASE_BASEADDRESS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_OFFSET 18  /* MASK DESCRIPTION :The lower two bits of address output to the memory chip shall be
masked with this value. This may be used to support x16 bus widths
where all accesses must be aligned on a 2-byte boundary.  */
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_MASK 0xC0000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_INV_MASK 0xFFF3FFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_VALUE_MASK 0x60000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_INV_VALUE_MASK 0xFFF9FFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_SIZE 2U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MASK_DEFAULT 3U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_OFFSET 16  /* WIDTH DESCRIPTION :Select address length used for AIP reads as follows:
0: Use 24-bit address field
1: Use 32-bit address field
2: Use 16-bit address field
3: Use 8-bit address field  */
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_MASK 0x30000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_INV_MASK 0xFFFCFFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_VALUE_MASK 0x18000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_INV_VALUE_MASK 0xFFFE7FFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_SIZE 2U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_WIDTH_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :Address DDR mode after update  */
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the address output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPADRATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_OFFSET 0  /* CHIPSELECT DESCRIPTION :The chip select line to use for AIP mode reads. A single bit is provided for each
chip select line.
Setting multiple bits to 1 in this register is guaranteed to cause bus conflicts and
may damage the external memory chips.  */
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPCS_CHIPSELECT_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_OFFSET 31  /* DIESELECTED DESCRIPTION :Indicates that the controller is tracking a selected die:
0: The controller is not tracking a selected die. The next access to this window
will send a die select command if it is enabled.
1: The controller assumes the die numer given in bits [30:24] is selected.
Writing this bit with 1 sets it to 0. This should be used when a custom command
changes the selected die.  */
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_INV_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_VALUE_MASK 0x40000000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_INV_VALUE_MASK 0xBFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_DIESELECTED_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_OFFSET 24  /* SELECTEDDIE DESCRIPTION :Reflects the selected die the controller is currently tracking. Only valid when bit
[31] is set to 1.  */
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_MASK 0x7F000000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_INV_MASK 0x80FFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_VALUE_MASK 0x3F800000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_INV_VALUE_MASK 0xC07FFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_SIZE 7U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_OFFSET 23  /* PAGESELECTED DESCRIPTION :Indicates that the controller is tracking a selected page:
0: The controller is not tracking a selected page. The next access to this window
will send a page read command if it is enabled.
1: The controller assumes the die numer given in bits [22:0] is selected.
Writing this bit with 1 sets it to 0. This should be used when a custom command
changes the selected page.  */
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_MASK 0x800000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_INV_MASK 0xFF7FFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_VALUE_MASK 0x400000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_INV_VALUE_MASK 0xFFBFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_PAGESELECTED_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_OFFSET 0  /* SELECTEDPAGE DESCRIPTION :Reflects the selected die the controller is currently tracking. Only valid when bit
[23] is set to 1.  */
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_MASK 0x7FFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_INV_MASK 0xFF800000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_VALUE_MASK 0x3FFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_INV_VALUE_MASK 0xFFC00000U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_SIZE 23U
#define XSPI_MC_AIPWINDOW0_AIPDIEPAGESTATE_SELECTEDPAGE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_OFFSET 25  /* DYNWRITELATENCY DESCRIPTION :If set to 1 write latency will be doubled if data strobe is sampled 1 during the command phase.  */
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_MASK 0x2000000U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_INV_MASK 0xFDFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_VALUE_MASK 0x1000000U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_INV_VALUE_MASK 0xFEFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DYNWRITELATENCY_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_OFFSET 24  /* NOWRITELATENCY DESCRIPTION :If set to 1 no write latency will not be inserted  */
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_MASK 0x1000000U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_INV_MASK 0xFEFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_VALUE_MASK 0x800000U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_INV_VALUE_MASK 0xFF7FFFFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_NOWRITELATENCY_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_OFFSET 16  /* WRITELATENCY DESCRIPTION :Write latency.  */
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_MASK 0x1F0000U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_INV_MASK 0xFFE0FFFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_VALUE_MASK 0xF8000U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_INV_VALUE_MASK 0xFFF07FFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_SIZE 5U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_WRITELATENCY_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_OFFSET 8  /* SKIP DESCRIPTION :This bit selects whether the dummy phase is to be skipped or not on AIP
reads and is encoded as follows:
0: Dummy phase is present
1: Dummy phase is skipped  */
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_MASK 0x100U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_VALUE_MASK 0x80U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_SKIP_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field reflects the length of the dummy phase of the AIP read in SPI
clock cycles minus 1.  */
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_MASK 0x1FU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_SIZE 5U
#define XSPI_MC_AIPWINDOW0_AIPDUMMYATTR_DURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_OFFSET 16  /* RESCOMMAND DESCRIPTION :SPI command to use to suspend writes.
For commands less than 16 bits wide, align command's most significant bit
to bit 15.  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_INV_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_VALUE_MASK 0x7FFF8000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_INV_VALUE_MASK 0x80007FFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_RESCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_OFFSET 0  /* SUSCOMMAND DESCRIPTION :SPI command to resume writes.
For commands less than 16 bits wide, align command's most significant bit
to bit 15.  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_INV_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_VALUE_MASK 0x7FFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESCMD_SUSCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the suspend and resume commands are
executed in DDR mode (using both edges of the clock) and is
encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the suspend and
resume command output, encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_MODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the suspend and resume
commands in SPI clock cycles minus 1.
A few examples:
- 8-bit mode in STR x8 mode: 0
- 8-bit mode in STR x1 mode: 7
- 8-bit mode in DDR x1 mode: 3
- 16-bit mode in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_MASK 0x1FU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_SIZE 5U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESATTR_DURATION_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_OFFSET 0  /* SUSPENDTIME DESCRIPTION :Time needed for the device to executed the suspend command.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPSUSTIME_SUSPENDTIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_OFFSET 7  /* FLIPBYTES DESCRIPTION :Byte order select
0: Return data using the same order as the memory chip provided the
data in
1: Flip the order of 4-bits in each 8-bit bytes
This bit only has effect in DDR x4 mode and is ignored in all other cases.  */
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_MASK 0x80U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_INV_MASK 0xFFFFFF7FU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_VALUE_MASK 0x40U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_INV_VALUE_MASK 0xFFFFFFBFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_FLIPBYTES_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_OFFSET 6  /* DQS DESCRIPTION :Sampling mode to use for AIP read data encoded as follows:
0: Use normal internal clock for sampling (i.e. no strobe used)
1: Use the strobe signal provided by the SPI memory chip for sampling.
Setting this bit to 1 while not in DDR mode is not supported.  */
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_MASK 0x40U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_INV_MASK 0xFFFFFFBFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_VALUE_MASK 0x20U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_INV_VALUE_MASK 0xFFFFFFDFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DQS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_OFFSET 5  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_MASK 0x20U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_INV_MASK 0xFFFFFFDFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_VALUE_MASK 0x10U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFFFEFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_OFFSET 4  /* DDRMODE DESCRIPTION :This bit selects whether the data phase is executed in DDR mode (using
both edges of the clock) and is encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_MASK 0x10U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_INV_MASK 0xFFFFFFEFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_VALUE_MASK 0x8U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_INV_VALUE_MASK 0xFFFFFFF7U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_OFFSET 0  /* MODE DESCRIPTION :This field selects the number of lines to use for the data output, encoded
as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_VALUE_MASK 0x7U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPDATATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_OFFSET 0  /* RESUMETIME DESCRIPTION :Time needed for the device to executed the resume command.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPRESTIME_RESUMETIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_OFFSET 0  /* SUSTORESTIME DESCRIPTION :Once a suspend command has been issued, the controller will not issue a
resume command for this amount of time. This time can be used to ensure
a number of reads complete between an expensive suspend resume cycle.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPSUSRESTIME_SUSTORESTIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_OFFSET 0  /* RESTOSUSTIME DESCRIPTION :Once a resume command has been issued, the controller will not issue a
suspend command for this amount of time. This time can be used to ensure forwared progress of writes.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPRESSUSTIME_RESTOSUSTIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_OFFSET 0  /* BITS DESCRIPTION :PI Mode bits to use for the mode phase of AIP reads.
For data widths less than 32 bits, the most significant data bit must be aligned
to bit [31].  */
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITS_BITS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the mode phase is to be skipped or not AIP
reads and is encoded as follows:
0: Mode phase is present
1: Mode phase is skipped  */
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_MASK 0x10000U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_SKIP_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the mode phase is executed in DDR mode
(using both edges of the clock) and is encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the mode output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_MODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the mode phase of AIP reads SPI
clock cycles minus 1.
A few examples:
- 8-bit mode in STR x8 mode: 0
- 8-bit mode in STR x1 mode: 7
- 8-bit mode in DDR x1 mode: 3
- 16-bit mode in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_MASK 0x1FU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_SIZE 5U
#define XSPI_MC_AIPWINDOW0_AIPMODEBITSATTR_DURATION_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_OFFSET 17  /* ADDRESSWIDTH DESCRIPTION :Selects the address width of the page read command as follows:
0: 24-bit address will be used
1: 32-bit address will be used
2: 16-bit address will be used
3: 8-bit address will be used  */
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_MASK 0x60000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_INV_MASK 0xFFF9FFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_VALUE_MASK 0x30000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_INV_VALUE_MASK 0xFFFCFFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_SIZE 2U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_ADDRESSWIDTH_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_OFFSET 14  /* PAGEENABLE DESCRIPTION :Paged read (NAND) command mode enable
0: Paged read mode disabled (e.g. NOR chips)
1: Paged read mode enabled (e.g. NAND chips)  */
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_MASK 0x4000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_INV_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_VALUE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_INV_VALUE_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_PAGEENABLE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the command phase is executed in DDR mode
(using both edges of the output clock) and is encoded as follows:
0: Normal (STR) output mode is used
1: DDR (DTR) output mode is used  */
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for AIP command output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the command phase of the AIP
read in SPI clock cycles minus 1.
A few examples:
- 8-bit command in STR x8 mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_MASK 0xFU
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_VALUE_MASK 0x7U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_SIZE 4U
#define XSPI_MC_AIPWINDOW0_AIPPRCMDATTR_DURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_OFFSET 0  /* BITS DESCRIPTION :Execution time of a Page Read command.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_SIZE 32U
#define XSPI_MC_AIPWINDOW0_AIPPAGETIME_BITS_DEFAULT 0U
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_OFFSET 2  /* ADDRESS DESCRIPTION :Set address for the first DMA descriptor. Can only be changed when DMA
is idle. The DMA engine updates this register to the address of the current
buffer descriptor being processed.  */
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_MASK 0xFFFFFFFCU
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_INV_MASK 0x3U
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_VALUE_MASK 0x7FFFFFFEU
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_INV_VALUE_MASK 0x80000001U
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_SIZE 30U
#define XSPI_MC_REGISTERS_DMASTARTADR_ADDRESS_DEFAULT 0U
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_OFFSET 8  /* AXIBL DESCRIPTION : Maximum burst length used for AXI transfers in number of words. This field is only used when DMA_TYPE = 1.
*/
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_MASK 0xFFFF00U
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_INV_MASK 0xFF0000FFU
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_VALUE_MASK 0x7FFF80U
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_INV_VALUE_MASK 0xFF80007FU
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_SIZE 16U
#define XSPI_MC_REGISTERS_DMAFXDBL_AXIBL_DEFAULT 15U
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_OFFSET 0  /* FIXEDBL DESCRIPTION :Select AHB Master interface's preferred incremental burst behavior.
- 0b00 = undetermined size
- 0b01 = burst 4
- 0b10 = burst 8
- 0b11 = burst 16
Note when Fixed BL is not 0x0, undetermined size burst can still be observed due
to 1KB boundary, buffer descriptor boundary, data size boundary and half FIFO size
limit, it will however always be shorter than the preferred burst length.
This field is only used when DMA_TYPE = 0.  */
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_MASK 0x3U
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_INV_MASK 0xFFFFFFFCU
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_VALUE_MASK 0x1U
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_INV_VALUE_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_SIZE 2U
#define XSPI_MC_REGISTERS_DMAFXDBL_FIXEDBL_DEFAULT 0U
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_OFFSET 2  /* DMAERROR DESCRIPTION :When set, it indicates that DMA completed with an error. Use software reset to
recover from error. Software must clear this bit after error recovery. It is cleared by writing 1 to it.  */
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_MASK 0x4U
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_INV_MASK 0xFFFFFFFBU
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_VALUE_MASK 0x2U
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_INV_VALUE_MASK 0xFFFFFFFDU
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_SIZE 1U
#define XSPI_MC_REGISTERS_DMASTS_DMAERROR_DEFAULT 0U
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_OFFSET 1  /* DMAIRQ DESCRIPTION :When set, it indicates DMA successfully transferred one or more buffer descriptors
with IRQ bit set. Software must clear this bit. It is cleared by writing 1 to it.  */
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_MASK 0x2U
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_INV_MASK 0xFFFFFFFDU
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_VALUE_MASK 0x1U
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_INV_VALUE_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_SIZE 1U
#define XSPI_MC_REGISTERS_DMASTS_DMAIRQ_DEFAULT 0U
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_OFFSET 0  /* DMAIDLE DESCRIPTION :Indicates DMA is available to process new requests  */
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_MASK 0x1U
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_SIZE 1U
#define XSPI_MC_REGISTERS_DMASTS_DMAIDLE_DEFAULT 1U
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_OFFSET 0  /* COUNT DESCRIPTION :Indicates how many DMA buffer descriptors were successfully transferred during
last DMA transfer  */
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_SIZE 32U
#define XSPI_MC_REGISTERS_DMABDCNT_COUNT_DEFAULT 0U
#define XSPI_MC_REGISTERS_GPIO_GPIO_OFFSET 0  /* GPIO DESCRIPTION :GPIO output value.
Each implemented bit may be connected some system-dependent GPIO signal.  */
#define XSPI_MC_REGISTERS_GPIO_GPIO_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_GPIO_GPIO_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_GPIO_GPIO_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_GPIO_GPIO_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_GPIO_GPIO_SIZE 32U
#define XSPI_MC_REGISTERS_GPIO_GPIO_DEFAULT 0U
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_OFFSET 0  /* GPIOOE DESCRIPTION :GPIO output enable.
Each implemented bit may be connected some system-dependent GPIO signal.  */
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_SIZE 32U
#define XSPI_MC_REGISTERS_GPIOOE_GPIOOE_DEFAULT 0U
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_OFFSET 1  /* WPZ DESCRIPTION :State of bit 2 during idle (CS inactive):
0: SPI output bit 2 is driven during transactions
1: SPI output bit 2 is HiZ during transactions  */
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_MASK 0x2U
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_INV_MASK 0xFFFFFFFDU
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_VALUE_MASK 0x1U
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_INV_VALUE_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_SIZE 1U
#define XSPI_MC_REGISTERS_WPCTRL_WPZ_DEFAULT 0U
#define XSPI_MC_REGISTERS_WPCTRL_WP_OFFSET 0  /* WP DESCRIPTION :Value to drive on the data bit 2 during idle (CS inactive). Many memory chips use
data bit 2 as a write-protect signal and its value may be set using this register.  */
#define XSPI_MC_REGISTERS_WPCTRL_WP_MASK 0x1U
#define XSPI_MC_REGISTERS_WPCTRL_WP_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_WPCTRL_WP_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_WPCTRL_WP_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_WPCTRL_WP_SIZE 1U
#define XSPI_MC_REGISTERS_WPCTRL_WP_DEFAULT 1U
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_OFFSET 0  /* HOLDTIME DESCRIPTION :Specifies the hold time of the output value for the phase preceeding the dummy
phase during SPI transactions. Refer to section 6.2.1 'SPI output behaviour',
specifically Figure 6  */
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_MASK 0xFFU
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_INV_MASK 0xFFFFFF00U
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_VALUE_MASK 0x7FU
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_INV_VALUE_MASK 0xFFFFFF80U
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_SIZE 8U
#define XSPI_MC_REGISTERS_HOLDTIME_HOLDTIME_DEFAULT 7U
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_OFFSET 24  /* CSNUMBER DESCRIPTION :Chip Select Line number to use during next software triggered
auto-configuration.  */
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_MASK 0x1F000000U
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_INV_MASK 0xE0FFFFFFU
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_VALUE_MASK 0xF800000U
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_INV_VALUE_MASK 0xF07FFFFFU
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_SIZE 5U
#define XSPI_MC_REGISTERS_ACFGCTRL_CSNUMBER_DEFAULT 1U
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_OFFSET 0  /* ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET DESCRIPTION :Set this register to 1 to have auto-configuration run after
software reset finishes.
Setting this register to 0 disables auto-configuration.  */
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_MASK 0x1U
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_SIZE 1U
#define XSPI_MC_REGISTERS_ACFGCTRL_ENABLEAUTOCONFIGURATIONAFTERSOFTWARERESET_DEFAULT 0U
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_OFFSET 16
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_MASK 0xFFFF0000U
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_INV_MASK 0xFFFFU
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_VALUE_MASK 0x7FFF8000U
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_INV_VALUE_MASK 0x80007FFFU
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_SIZE 16U
#define XSPI_MC_REGISTERS_VERSION_MAJORVERSION_DEFAULT 4U
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_OFFSET 8
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_MASK 0xFF00U
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_INV_MASK 0xFFFF00FFU
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_VALUE_MASK 0x7F80U
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_INV_VALUE_MASK 0xFFFF807FU
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_SIZE 8U
#define XSPI_MC_REGISTERS_VERSION_MINORVERSION_DEFAULT 3U
#define XSPI_MC_REGISTERS_VERSION_REVISION_OFFSET 0
#define XSPI_MC_REGISTERS_VERSION_REVISION_MASK 0xFFU
#define XSPI_MC_REGISTERS_VERSION_REVISION_INV_MASK 0xFFFFFF00U
#define XSPI_MC_REGISTERS_VERSION_REVISION_VALUE_MASK 0x7FU
#define XSPI_MC_REGISTERS_VERSION_REVISION_INV_VALUE_MASK 0xFFFFFF80U
#define XSPI_MC_REGISTERS_VERSION_REVISION_SIZE 8U
#define XSPI_MC_REGISTERS_VERSION_REVISION_DEFAULT 3U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_OFFSET 12  /* SRAMIMPL DESCRIPTION :If set to 1, SRAM support is implemented  */
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_MASK 0x1000U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_VALUE_MASK 0x800U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_SIZE 1U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_SRAMIMPL_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_OFFSET 8  /* ACFGIMPL DESCRIPTION :If set to 1, the auto configuration module is implemented  */
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_MASK 0x100U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_VALUE_MASK 0x80U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_SIZE 1U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_ACFGIMPL_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_OFFSET 4  /* DMAIMPL DESCRIPTION :If set to 1, the DMA engine is implemented  */
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_MASK 0x10U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_INV_MASK 0xFFFFFFEFU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_VALUE_MASK 0x8U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_INV_VALUE_MASK 0xFFFFFFF7U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_SIZE 1U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_DMAIMPL_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_OFFSET 0  /* AIPIMPL DESCRIPTION :If set to 1, the AIP interface is implemented  */
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_MASK 0x1U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_VALUE_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_SIZE 1U
#define XSPI_MC_REGISTERS_AIPIMPFEAT_AIPIMPL_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_OFFSET 0  /* CSLINES DESCRIPTION :Specifies the number of CS lines implemented  */
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_SIZE 32U
#define XSPI_MC_REGISTERS_AIPIMPCSW_CSLINES_DEFAULT 1U
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_OFFSET 0  /* GPIOLINES DESCRIPTION :Specifies the number of GPIO lines implemented  */
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_SIZE 32U
#define XSPI_MC_REGISTERS_AIPIMPGPIOW_GPIOLINES_DEFAULT 1U
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_OFFSET 0  /* DATALINES DESCRIPTION :Specifies the number of data lines implemented  */
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_SIZE 32U
#define XSPI_MC_REGISTERS_AIPIMPDQWIDTH_DATALINES_DEFAULT 4U
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_OFFSET 0  /* CDC DESCRIPTION :Specifies the allowed clocking option  */
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_SIZE 32U
#define XSPI_MC_REGISTERS_GPIOIMPCDC_CDC_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_OFFSET 0  /* AIPTYPE DESCRIPTION :Specifies the implemented AIP bus type:
0: AHB bus implemented
1: AXI bus implemented  */
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_SIZE 32U
#define XSPI_MC_REGISTERS_AIPIMPTYPE_AIPTYPE_DEFAULT 0U
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_OFFSET 0  /* AIPAW DESCRIPTION :Specifies the implemented AIP bus address width  */
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_SIZE 32U
#define XSPI_MC_REGISTERS_AIPIMPAW_AIPAW_DEFAULT 2U
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_OFFSET 0  /* AIPIDW DESCRIPTION :Specifies the implemented AIP bus' ID width, if using the AXI bus  */
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_SIZE 32U
#define XSPI_MC_REGISTERS_AIPIMPIDW_AIPIDW_DEFAULT 1U
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_OFFSET 0  /* CFGFIFOLEN DESCRIPTION :Specifies the depth of the custom command FIFO. The user can not write more
data to than the value specified here.  */
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_SIZE 32U
#define XSPI_MC_REGISTERS_CFGFIFOAW_CFGFIFOLEN_DEFAULT 2U
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_OFFSET 0  /* WRFIFO DESCRIPTION :Specifies the depth of the write data FIFO  */
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_SIZE 32U
#define XSPI_MC_REGISTERS_IMPWRFIFOAW_WRFIFO_DEFAULT 2U
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_OFFSET 0  /* RDFIFOLEN DESCRIPTION :Specifies the depth of the read data FIFO  */
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_SIZE 32U
#define XSPI_MC_REGISTERS_IMPRDFIFOAW_RDFIFOLEN_DEFAULT 2U
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_OFFSET 0  /* ACFGLEN DESCRIPTION :Specifies the maximum number of bytes of the auto configuration data  */
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_SIZE 32U
#define XSPI_MC_REGISTERS_ACFGROMAW_ACFGLEN_DEFAULT 2U
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_OFFSET 0  /* DMAAW DESCRIPTION :Specifies the number of bits the DMA address  */
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_SIZE 32U
#define XSPI_MC_REGISTERS_IMPDMAAW_DMAAW_DEFAULT 2U
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_OFFSET 0  /* AIPWINDOWS DESCRIPTION :Specifies the number of implemented AIP windows available to the programmer.  */
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_MASK 0xFFFFFFFFU
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_INV_MASK 0x0U
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_SIZE 32U
#define XSPI_MC_REGISTERS_ADDRDECN_AIPWINDOWS_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_OFFSET 9  /* UPDATE DESCRIPTION :If this bit is set to 1, the attributes specified in the New AIP * registers
are applied.  */
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_MASK 0x200U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_INV_MASK 0xFFFFFDFFU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_VALUE_MASK 0x100U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_INV_VALUE_MASK 0xFFFFFEFFU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_UPDATE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_OFFSET 8  /* SUSRES DESCRIPTION :Set to 1 to enable suspend/resume support. Setting this bit is only
applied when bit [9] is also set to 1.  */
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_MASK 0x100U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_VALUE_MASK 0x80U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_SUSRES_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_OFFSET 1  /* BUSY DESCRIPTION :AIP operation state:
0: Idle. AIP transfer is not active.
1: Busy. AIP transfer in progress.  */
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_MASK 0x2U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_INV_MASK 0xFFFFFFFDU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_VALUE_MASK 0x1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_INV_VALUE_MASK 0xFFFFFFFEU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_BUSY_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_OFFSET 0  /* AIPMODEENABLE DESCRIPTION :AIP window enable:
0: This AIP window is disabled
1: This AIP window is enabled
Any AIP window may be disabled at any time. If an AIP access is in
progress when the AIP window is disabled it will be finished cleanly.  */
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_MASK 0x1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_INV_MASK 0xFFFFFFFEU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_VALUE_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_INV_VALUE_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCTRL_AIPMODEENABLE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_OFFSET 0  /* AIPACCESSBOUNDARY DESCRIPTION :Access boundary for AIP accesses. For any burst that would pass this
boundary, the controller will end the transaction and start a new one.
For NAND chips, set this register to the page size.
Some PSRAM chips have boundary limitations too.  */
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_MASK 0x1FU
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_SIZE 5U
#define XSPI_MC_AIPWINDOW1_AIPACCB_AIPACCESSBOUNDARY_DEFAULT 31U
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_OFFSET 0  /* AIPSIZE DESCRIPTION :This register gives the size of this AIP window. The size must a power
of two. If the size is 2N, the size is given by setting the low N bits to 1 in
this register and the rest to 0.  */
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPSIZE_AIPSIZE_DEFAULT 2097151U
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_OFFSET 0  /* AIPWINDOWADDRESS DESCRIPTION :For window 0: This register is hard wired to 0
For all other windows this is the window address as given on the
AHB/AXI interface.  */
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPWINADDR_AIPWINDOWADDRESS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_OFFSET 16  /* WCOMMAND DESCRIPTION :SPI command to use for AIP writes in case of PSRAM chips.
Page read command for NAND flash chips.
For commands less than 16 bits wide, align command's most significant bit
to bit 15.  */
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_INV_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_VALUE_MASK 0x7FFF8000U
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_INV_VALUE_MASK 0x80007FFFU
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW1_AIPCMD_WCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_OFFSET 0  /* RCOMMAND DESCRIPTION :SPI command to use for AIP reads. For commands less than 16 bits wide,
align command's most significant bit to bit 15.  */
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_INV_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_VALUE_MASK 0x7FFFU
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW1_AIPCMD_RCOMMAND_DEFAULT 2816U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the command phase is to be skipped or not
for AIP-based SPI transactions and is encoded as follows:
0: Command phase is present
1: Command phase is skipped  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_MASK 0x10000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_SKIP_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_OFFSET 15  /* HYPERAMCOMMAND DESCRIPTION :Selects if the outgoing command uses the HyperRAM format. If this bit
is set to 1, command generation occurs internally and the contents of
register New AIP Command(window offset 0x10) is ignored.  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_MASK 0x8000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_INV_MASK 0xFFFF7FFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_VALUE_MASK 0x4000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_INV_VALUE_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_HYPERAMCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_OFFSET 14  /* WRITESUPPORT DESCRIPTION :Selects if the outgoing command uses the HyperRAM format. If this bit
is set to 1, command generation occurs internally and the contents of
register New AIP Command(window offset 0x10) is ignored.  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_MASK 0x4000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_INV_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_VALUE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_INV_VALUE_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_WRITESUPPORT_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the command phase is executed in DDR mode
(using both edges of the output clock) and is encoded as follows:
0: Normal (STR) output mode is used
1: DDR (DTR) output mode is used  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for AIP command output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the command phase of the AIP
read in SPI clock cycles minus 1.
A few examples:
- 8-bit command in STR x8 mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_MASK 0x7U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_INV_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_VALUE_MASK 0x3U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_INV_VALUE_MASK 0xFFFFFFFCU
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_SIZE 3U
#define XSPI_MC_AIPWINDOW1_AIPCMDATTR_DURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_OFFSET 16  /* ADDRBITSINDIE DESCRIPTION :Number of address bits on a single die. If only a single die is supported, set
this to 0x1f.  */
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_MASK 0x1F0000U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_INV_MASK 0xFFE0FFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_VALUE_MASK 0xF8000U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_INV_VALUE_MASK 0xFFF07FFFU
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_SIZE 5U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_ADDRBITSINDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_OFFSET 0  /* DIESELECTCMD DESCRIPTION :The SPI command that selects the active die.
For commands less than 16 bits wide, align command's most significant bit to
bit 15.  */
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_INV_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_VALUE_MASK 0x7FFFU
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_SIZE 16U
#define XSPI_MC_AIPWINDOW1_AIPDIECMD_DIESELECTCMD_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_OFFSET 16  /* ADDRESSWIDTH DESCRIPTION :Address_width in the die select command as follows:
0: Use 24-bit address field
1: Use 32-bit address field
2: Use 16-bit address field
3: Use 8-bit address field  */
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_MASK 0x30000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_INV_MASK 0xFFFCFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_VALUE_MASK 0x18000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_INV_VALUE_MASK 0xFFFE7FFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_SIZE 2U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_ADDRESSWIDTH_DEFAULT 3U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_OFFSET 14  /* DIEENABLE DESCRIPTION :When set to 0 the controller does not send Die select commands. Settings this bit to 1 allows the controller to send Die select commands.  */
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_MASK 0x4000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_INV_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_VALUE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_INV_VALUE_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DIEENABLE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :Die select, include die mode in DDR mode after update.  */
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the die select command
including the die number, encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_OFFSET 0  /* COMMANDDURATION DESCRIPTION :This field must reflect the length of the die select command in SPI clock
cycles minus 1.
A few examples:
- 8-bit command in STR x8 mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_VALUE_MASK 0x7U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPDIEATTR_COMMANDDURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_OFFSET 0  /* BASEADDRESS DESCRIPTION :This register selects the memory address to which the controller maps
address 0 on the AIP slave interface. This base address must be aligned to the
value given in the New AIP Size (widow offset 0x08) register.
For example, if the New AIP Size (window offset 0x08) register is set to 17 (a
128KB window), the Base_Address may be set to any multiple of 128KB, e.g.
128KB, 256KB, 384KB, etc.  */
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPADRBASE_BASEADDRESS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_OFFSET 18  /* MASK DESCRIPTION :The lower two bits of address output to the memory chip shall be
masked with this value. This may be used to support x16 bus widths
where all accesses must be aligned on a 2-byte boundary.  */
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_MASK 0xC0000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_INV_MASK 0xFFF3FFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_VALUE_MASK 0x60000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_INV_VALUE_MASK 0xFFF9FFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_SIZE 2U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MASK_DEFAULT 3U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_OFFSET 16  /* WIDTH DESCRIPTION :Select address length used for AIP reads as follows:
0: Use 24-bit address field
1: Use 32-bit address field
2: Use 16-bit address field
3: Use 8-bit address field  */
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_MASK 0x30000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_INV_MASK 0xFFFCFFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_VALUE_MASK 0x18000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_INV_VALUE_MASK 0xFFFE7FFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_SIZE 2U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_WIDTH_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :Address DDR mode after update  */
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the address output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPADRATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_OFFSET 0  /* CHIPSELECT DESCRIPTION :The chip select line to use for AIP mode reads. A single bit is provided for each
chip select line.
Setting multiple bits to 1 in this register is guaranteed to cause bus conflicts and
may damage the external memory chips.  */
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPCS_CHIPSELECT_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_OFFSET 31  /* DIESELECTED DESCRIPTION :Indicates that the controller is tracking a selected die:
0: The controller is not tracking a selected die. The next access to this window
will send a die select command if it is enabled.
1: The controller assumes the die numer given in bits [30:24] is selected.
Writing this bit with 1 sets it to 0. This should be used when a custom command
changes the selected die.  */
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_INV_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_VALUE_MASK 0x40000000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_INV_VALUE_MASK 0xBFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_DIESELECTED_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_OFFSET 24  /* SELECTEDDIE DESCRIPTION :Reflects the selected die the controller is currently tracking. Only valid when bit
[31] is set to 1.  */
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_MASK 0x7F000000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_INV_MASK 0x80FFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_VALUE_MASK 0x3F800000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_INV_VALUE_MASK 0xC07FFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_SIZE 7U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_OFFSET 23  /* PAGESELECTED DESCRIPTION :Indicates that the controller is tracking a selected page:
0: The controller is not tracking a selected page. The next access to this window
will send a page read command if it is enabled.
1: The controller assumes the die numer given in bits [22:0] is selected.
Writing this bit with 1 sets it to 0. This should be used when a custom command
changes the selected page.  */
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_MASK 0x800000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_INV_MASK 0xFF7FFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_VALUE_MASK 0x400000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_INV_VALUE_MASK 0xFFBFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_PAGESELECTED_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_OFFSET 0  /* SELECTEDPAGE DESCRIPTION :Reflects the selected die the controller is currently tracking. Only valid when bit
[23] is set to 1.  */
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_MASK 0x7FFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_INV_MASK 0xFF800000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_VALUE_MASK 0x3FFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_INV_VALUE_MASK 0xFFC00000U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_SIZE 23U
#define XSPI_MC_AIPWINDOW1_AIPDIEPAGESTATE_SELECTEDPAGE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_OFFSET 25  /* DYNWRITELATENCY DESCRIPTION :If set to 1 write latency will be doubled if data strobe is sampled 1 during the command phase.  */
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_MASK 0x2000000U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_INV_MASK 0xFDFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_VALUE_MASK 0x1000000U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_INV_VALUE_MASK 0xFEFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DYNWRITELATENCY_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_OFFSET 24  /* NOWRITELATENCY DESCRIPTION :If set to 1 no write latency will not be inserted  */
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_MASK 0x1000000U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_INV_MASK 0xFEFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_VALUE_MASK 0x800000U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_INV_VALUE_MASK 0xFF7FFFFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_NOWRITELATENCY_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_OFFSET 16  /* WRITELATENCY DESCRIPTION :Write latency.  */
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_MASK 0x1F0000U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_INV_MASK 0xFFE0FFFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_VALUE_MASK 0xF8000U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_INV_VALUE_MASK 0xFFF07FFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_SIZE 5U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_WRITELATENCY_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_OFFSET 8  /* SKIP DESCRIPTION :This bit selects whether the dummy phase is to be skipped or not on AIP
reads and is encoded as follows:
0: Dummy phase is present
1: Dummy phase is skipped  */
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_MASK 0x100U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_INV_MASK 0xFFFFFEFFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_VALUE_MASK 0x80U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_INV_VALUE_MASK 0xFFFFFF7FU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_SKIP_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field reflects the length of the dummy phase of the AIP read in SPI
clock cycles minus 1.  */
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_MASK 0x1FU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_SIZE 5U
#define XSPI_MC_AIPWINDOW1_AIPDUMMYATTR_DURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_OFFSET 16  /* RESCOMMAND DESCRIPTION :SPI command to use to suspend writes.
For commands less than 16 bits wide, align command's most significant bit
to bit 15.  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_INV_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_VALUE_MASK 0x7FFF8000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_INV_VALUE_MASK 0x80007FFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_RESCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_OFFSET 0  /* SUSCOMMAND DESCRIPTION :SPI command to resume writes.
For commands less than 16 bits wide, align command's most significant bit
to bit 15.  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_MASK 0xFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_INV_MASK 0xFFFF0000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_VALUE_MASK 0x7FFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_INV_VALUE_MASK 0xFFFF8000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_SIZE 16U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESCMD_SUSCOMMAND_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the suspend and resume commands are
executed in DDR mode (using both edges of the clock) and is
encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the suspend and
resume command output, encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_MODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the suspend and resume
commands in SPI clock cycles minus 1.
A few examples:
- 8-bit mode in STR x8 mode: 0
- 8-bit mode in STR x1 mode: 7
- 8-bit mode in DDR x1 mode: 3
- 16-bit mode in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_MASK 0x1FU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_SIZE 5U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESATTR_DURATION_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_OFFSET 0  /* SUSPENDTIME DESCRIPTION :Time needed for the device to executed the suspend command.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPSUSTIME_SUSPENDTIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_OFFSET 7  /* FLIPBYTES DESCRIPTION :Byte order select
0: Return data using the same order as the memory chip provided the
data in
1: Flip the order of 4-bits in each 8-bit bytes
This bit only has effect in DDR x4 mode and is ignored in all other cases.  */
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_MASK 0x80U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_INV_MASK 0xFFFFFF7FU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_VALUE_MASK 0x40U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_INV_VALUE_MASK 0xFFFFFFBFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_FLIPBYTES_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_OFFSET 6  /* DQS DESCRIPTION :Sampling mode to use for AIP read data encoded as follows:
0: Use normal internal clock for sampling (i.e. no strobe used)
1: Use the strobe signal provided by the SPI memory chip for sampling.
Setting this bit to 1 while not in DDR mode is not supported.  */
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_MASK 0x40U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_INV_MASK 0xFFFFFFBFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_VALUE_MASK 0x20U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_INV_VALUE_MASK 0xFFFFFFDFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DQS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_OFFSET 5  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_MASK 0x20U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_INV_MASK 0xFFFFFFDFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_VALUE_MASK 0x10U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFFFEFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_OFFSET 4  /* DDRMODE DESCRIPTION :This bit selects whether the data phase is executed in DDR mode (using
both edges of the clock) and is encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_MASK 0x10U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_INV_MASK 0xFFFFFFEFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_VALUE_MASK 0x8U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_INV_VALUE_MASK 0xFFFFFFF7U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_OFFSET 0  /* MODE DESCRIPTION :This field selects the number of lines to use for the data output, encoded
as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_VALUE_MASK 0x7U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPDATATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_OFFSET 0  /* RESUMETIME DESCRIPTION :Time needed for the device to executed the resume command.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPRESTIME_RESUMETIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_OFFSET 0  /* SUSTORESTIME DESCRIPTION :Once a suspend command has been issued, the controller will not issue a
resume command for this amount of time. This time can be used to ensure
a number of reads complete between an expensive suspend resume cycle.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPSUSRESTIME_SUSTORESTIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_OFFSET 0  /* RESTOSUSTIME DESCRIPTION :Once a resume command has been issued, the controller will not issue a
suspend command for this amount of time. This time can be used to ensure forwared progress of writes.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPRESSUSTIME_RESTOSUSTIME_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_OFFSET 0  /* BITS DESCRIPTION :PI Mode bits to use for the mode phase of AIP reads.
For data widths less than 32 bits, the most significant data bit must be aligned
to bit [31].  */
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITS_BITS_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_OFFSET 16  /* SKIP DESCRIPTION :This bit selects whether the mode phase is to be skipped or not AIP
reads and is encoded as follows:
0: Mode phase is present
1: Mode phase is skipped  */
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_MASK 0x10000U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_INV_MASK 0xFFFEFFFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_VALUE_MASK 0x8000U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_INV_VALUE_MASK 0xFFFF7FFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_SKIP_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the mode phase is executed in DDR mode
(using both edges of the clock) and is encoded as follows:
0: Normal (STR) mode is used
1: DDR (DTR) mode is used  */
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for the mode output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_MODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the mode phase of AIP reads SPI
clock cycles minus 1.
A few examples:
- 8-bit mode in STR x8 mode: 0
- 8-bit mode in STR x1 mode: 7
- 8-bit mode in DDR x1 mode: 3
- 16-bit mode in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_MASK 0x1FU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_INV_MASK 0xFFFFFFE0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_VALUE_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_SIZE 5U
#define XSPI_MC_AIPWINDOW1_AIPMODEBITSATTR_DURATION_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_OFFSET 17  /* ADDRESSWIDTH DESCRIPTION :Selects the address width of the page read command as follows:
0: 24-bit address will be used
1: 32-bit address will be used
2: 16-bit address will be used
3: 8-bit address will be used  */
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_MASK 0x60000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_INV_MASK 0xFFF9FFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_VALUE_MASK 0x30000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_INV_VALUE_MASK 0xFFFCFFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_SIZE 2U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_ADDRESSWIDTH_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_OFFSET 14  /* PAGEENABLE DESCRIPTION :Paged read (NAND) command mode enable
0: Paged read mode disabled (e.g. NOR chips)
1: Paged read mode enabled (e.g. NAND chips)  */
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_MASK 0x4000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_INV_MASK 0xFFFFBFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_VALUE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_INV_VALUE_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_PAGEENABLE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_OFFSET 13  /* STACKEDDIE DESCRIPTION :Selects operating modes for stacked-die configurations:
0: Normal mode
1: Stacked die-mode. See section 6.2.4 'Stacked die behaviour'  */
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_MASK 0x2000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_INV_MASK 0xFFFFDFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_VALUE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_INV_VALUE_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_STACKEDDIE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_OFFSET 12  /* DDRMODE DESCRIPTION :This bit selects whether the command phase is executed in DDR mode
(using both edges of the output clock) and is encoded as follows:
0: Normal (STR) output mode is used
1: DDR (DTR) output mode is used  */
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_MASK 0x1000U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_INV_MASK 0xFFFFEFFFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_VALUE_MASK 0x800U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_INV_VALUE_MASK 0xFFFFF7FFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_SIZE 1U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DDRMODE_DEFAULT 0U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_OFFSET 8  /* MODE DESCRIPTION :This field selects the number of lines to use for AIP command output,
encoded as follows:
- 0x9 = 16-bits (x16, 16-bits)
- 0x8 = Octa (x8, 8-bits)
- 0x4 = Quad (x4, 4-bits)
- 0x2 = Dual (x2, 2-bits)
- 0x1 = Single (x1, 1-bits)  */
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_MASK 0xF00U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_INV_MASK 0xFFFFF0FFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_VALUE_MASK 0x780U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_INV_VALUE_MASK 0xFFFFF87FU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_MODE_DEFAULT 1U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_OFFSET 0  /* DURATION DESCRIPTION :This field must reflect the length of the command phase of the AIP
read in SPI clock cycles minus 1.
A few examples:
- 8-bit command in STR x8 mode: 0
- 8-bit command in STR x1 mode: 7
- 8-bit command in DDR x1 mode: 3
- 16-bit command in DDR x8 mode: 0  */
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_MASK 0xFU
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_INV_MASK 0xFFFFFFF0U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_VALUE_MASK 0x7U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_INV_VALUE_MASK 0xFFFFFFF8U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_SIZE 4U
#define XSPI_MC_AIPWINDOW1_AIPPRCMDATTR_DURATION_DEFAULT 7U
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_OFFSET 0  /* BITS DESCRIPTION :Execution time of a Page Read command.
The time is given in a number bus clock cycles.  */
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_MASK 0xFFFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_INV_MASK 0x0U
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_VALUE_MASK 0x7FFFFFFFU
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_INV_VALUE_MASK 0x80000000U
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_SIZE 32U
#define XSPI_MC_AIPWINDOW1_AIPPAGETIME_BITS_DEFAULT 0U

#endif /* INPH_XSPI_REGS_H */

