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

#ifndef __INPH_XSPI_FLASH_DEV_H
#define __INPH_XSPI_FLASH_DEV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "memdev_cfg.h"

#define FLASH_BASE                    INPH_FLASH_BASE        // go platform_retarget.h for defines
#define FLASH_SIZE                    INPH_FLASH_SIZE        // you need to set the values there
#define FLASH_SECTOR_SIZE             INPH_FLASH_SIZEOF_ROW  //
#define FLASH_PAGE_SIZE               INPH_FLASH_SIZEOF_ROW  //

#define ARM_FLASH_DRV_ERASE_VALUE              0xFF
#define INPH_XSPI_DESELECT_DELAY               (3UL)
#define INPH_XSPI_TIMEOUT_10_MS                (10000UL)
#define INPH_XSPI_FLASH_QUAD_ENABLE_TIMEOUT_US (5000lu) // in us

/* for FLASH GPIO configuration --- if possible use from GPIO driver .h file */
#define GPIO_ARM_CNTRL0 (0x500A0000UL)
#define GPIO_ARM_CNTRL1 (0x500A1000UL)

#define GPIO_PORTA_BASE (0x500A0060UL)
#define GPIO_PORTB_BASE (0x500A0080UL)
#define GPIO_PORTC_BASE (0x500A1060UL)
#define GPIO_PORTD_BASE (0x500A1080UL)

#define GPIO_ALT1_BASE (0x500A0018UL)
#define GPIO_ALT2_BASE (0x500A1018UL)

typedef struct {
    XSPI_Type *base;

    /* Active slave select */
    inph_en_xspi_chip_select_t slave_select;
    uint8_t mode;
    inph_stc_xspi_context_t context;
    inph_en_xspi_data_select_t data_select;

    // callbacks, if any
} inph_xspi_t;

extern inph_xspi_t xspi_obj;
extern const inph_stc_xspi_mem_config_t* const inphXSPIMemConfigs1[];

/* FLASH device configuration structure */
struct inph_flash_dev_cfg_t {

    /** move the "inph_xspi_t xspi_obj" -- here and do initialisation from: ARM_FLASHx_Initialize() :: platform/ext/target/innophaseiot/drivers/flash/Driver_Flash_CMSDK.h **/

    const uint32_t base;              /*!< FLASH base address */
    const uint32_t default_baudrate;  /*!< Default baudrate */
};

/* FLASH device data structure */
struct inph_flash_dev_data_t {
    uint32_t state;       /*!< Indicates if the uart driver is initialized and enabled */
    uint32_t system_clk;
    uint32_t baudrate;    /*!< Baudrate */

};

/*  FLASH device structure */
struct inph_flash_dev_t {
    const struct inph_flash_dev_cfg_t* const cfg;  /*!< FLASH configuration */
    struct inph_flash_dev_data_t* const data;      /*!< FLASH data */
};


void flash_config_io(void);

inph_en_xspi_status_t Inph_XSPI_SerialFlashInit(
                      const inph_stc_xspi_mem_config_t *qspi_flash_mem_config);

#ifdef __cplusplus
}
#endif
#endif /* __INPH_XSPI_FLASH_DEV_H */
