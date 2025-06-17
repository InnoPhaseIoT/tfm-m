/*
 * Copyright (c) 2023 Arm Limited. All rights reserved.
 *
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
 */

#ifndef __DRIVER_FLASH_CMSDK_H__
#define __DRIVER_FLASH_CMSDK_H__

#include "Driver_Flash_Common.h"
#include "inph_xspi_memslot.h"
#include "inph_xspi.h"
#include "tfm_utils.h"
#include "Driver_Flash.h"

/* Driver version */
#define ARM_FLASH_DRV_VERSION      ARM_DRIVER_VERSION_MAJOR_MINOR(1, 1)
#define ARM_FLASH_DRV_ERASE_VALUE  0xFF

#define FLASH_BASE                    INPH_FLASH_BASE        // go platform_retarget.h for defines
#define FLASH_SIZE                    INPH_FLASH_SIZE        // you need to set the values there
#define FLASH_SECTOR_SIZE             INPH_FLASH_SIZEOF_ROW  //
#define FLASH_PAGE_SIZE               INPH_FLASH_SIZEOF_ROW  //

enum {
   DATA_WIDTH_8BIT   = 0u,
   DATA_WIDTH_16BIT,
   DATA_WIDTH_32BIT,
   DATA_WIDTH_ENUM_MAX
};

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
    1, //event_ready
    DATA_WIDTH_8BIT, //8 bit with
    1  //erase_chip
};

typedef struct {
    struct inph_flash_dev_t *dev;      /* FLASH device structure */
    uint32_t read_nbr_bytes;           /* Number of bytes transfered */
    uint32_t prog_nbr_bytes;           /* Number of bytes recevied */
    ARM_FLASH_SignalEvent_t cb_event;  /* Callback function for events */
} FLASHx_Resources;

static ARM_FLASH_INFO ARM_FLASH_DEV_DATA =
{
    .sector_info  = NULL,                  /* Uniform sector layout */
    .sector_count = FLASH_SIZE / FLASH_SECTOR_SIZE,
    .sector_size  = FLASH_SECTOR_SIZE,
    .page_size    = FLASH_PAGE_SIZE,
    .program_unit = 4,
    .erased_value = 0xFF
};

static inline ARM_FLASH_CAPABILITIES ARM_FLASH_GetCapabilities(void)
{
    return DriverCapabilities;
}

static inline int32_t ARM_FLASHx_Initialize(FLASHx_Resources *flash_dev)
{
    /* Initializes  flash driver */
    Inph_XSPI_Init(flash_dev->dev);

    return ARM_DRIVER_OK;
}

static inline int32_t ARM_FLASHx_Uninitialize(FLASHx_Resources *flash_dev)
{
    /* Initializes generic UART driver */
    Inph_XSPI_DeInit(uart_dev->dev);

    return ARM_DRIVER_OK;
}

static inline int32_t ARM_FLASHx_PowerControl(FLASHx_Resources *flash_dev,
                                              ARM_POWER_STATE state)
{
    ARG_UNUSED(uart_dev);

    switch (state) {
    case ARM_POWER_OFF:
    case ARM_POWER_LOW:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    case ARM_POWER_FULL:
        /* Nothing to be done */
        return ARM_DRIVER_OK;
    /* default:  The default is not defined intentionally to force the
     *           compiler to check that all the enumeration values are
     *           covered in the switch.*/
    }
    return ARM_DRIVER_OK;
}

static inline int32_t ARM_FLASHx_ReadData(FLASHx_Resources *flash_dev,
                                      uint32_t addr, const void *data,
                                      uint32_t num)
{
    //put your code here
    //for example: Inph_XSPI_ReceiveData();
    return ARM_DRIVER_OK;
}

static inline int32_t ARM_FLASHx_ProgramData(FLASHx_Resources *flash_dev,
                               uint32_t addr, void *data, uint32_t num)
{
    //Put your code here to call your driver function

    return ARM_DRIVER_OK;
}

static inline uint32_t ARM_FLASHx_EraseSector(FLASHx_Resources *flash_dev,
                                              uint32_t num)
{
    //your function calls here
    return ARM_DRIVER_OK;
}

static inline uint32_t ARM_FLASHx_EraseChip(FLASHx_Resources *flash_dev)
{
    //your function calls here
    return ARM_DRIVER_OK;
}

static inline int32_t ARM_FLASHx_GetStatus(FLASHx_Resources *flash_dev)
{
    //your function calls here
    return ARM_DRIVER_OK;
}

static inline int32_t ARM_FLASHx_GetInfo(FLASHx_Resources *flash_dev)
{
    //your function calls here
    return ARM_DRIVER_OK;
}

/*
 * \brief Macro for FLASH CMSDK Driver
 *
 * \param[in]  FLASH_DEV          Native driver device
 *                                \ref flash_cmsdk_dev_t
 * \param[out] FLASH_DRIVER_NAME  Resulting Driver name
 */
#define ARM_DRIVER_FLASH_CMSDK(FLASH_DEV, FLASH_DRIVER_NAME)                  \
static FLASHx_Resources FLASH_DRIVER_NAME##_DEV = {                           \
    .dev = &FLASH_DEV,                                                        \
    .read_nbr_bytes = 0,                                                      \
    .prog_nbr_bytes = 0,                                                      \
    .cb_event = NULL,                                                         \
};                                                                            \
                                                                              \
static int32_t FLASH_DRIVER_NAME##_Initialize(                                \
                                        ARM_FLASH_SignalEvent_t cb_event)     \
{                                                                             \
    FLASH_DRIVER_NAME##_DEV.cb_event = cb_event;                              \
                                                                              \
    return ARM_FLASHx_Initialize(&FLASH_DRIVER_NAME##_DEV);                   \
}                                                                             \
                                                                              \
static int32_t FLASH_DRIVER_NAME##_Uninitialize(void)                         \
{                                                                             \
    ARM_FLASHx_Uninitialize(&FLASH_DRIVER_NAME##_DEV);                        \
    return ARM_DRIVER_OK;                                                     \
}                                                                             \
                                                                              \
static int32_t FLASH_DRIVER_NAME##_PowerControl(ARM_POWER_STATE state)        \
{                                                                             \
    return ARM_FLASHx_PowerControl(&FLASH_DRIVER_NAME##_DEV, state);          \
}                                                                             \
                                                                              \
static int32_t FLASH_DRIVER_NAME##_ReadData                                   \
                                   (uint32_t addr, void *data, uint32_t num)  \
{                                                                             \
    return ARM_FLASHx_ReadData(&FLASH_DRIVER_NAME##_DEV, addr, data, num);    \
}                                                                             \
                                                                              \
static int32_t FLASH_DRIVER_NAME##_ProgramData                                \
                          (uint32_t addr, const void *data, uint32_t cnt)     \
{                                                                             \
    return ARM_FLASHx_ProgrammData                                            \
                            (&FLASH_DRIVER_NAME##_DEV, addr, data, num);      \
}                                                                             \
                                                                              \
static int32_t FLASH_DRIVER_NAME##_EraseSector(uint32_t addr)                 \
{                                                                             \
    return ARM_FLASHx_EraseSector(addr);                                      \
}                                                                             \
                                                                              \
static uint32_t FLASH_DRIVER_NAME##EraseChip(void)                            \
{                                                                             \
    return ARM_FLASHx_EraseChip(&FLASH_DRIVER_NAME##_DEV);                    \
}                                                                             \
                                                                              \
static uint32_t FLASH_DRIVER_NAME##_GetStatus(void)                           \
{                                                                             \
    return ARM_FLASHx_GetStatus(&FLASH_DRIVER_NAME##_DEV);                    \
}                                                                             \
static int32_t FLASH_DRIVER_NAME##_GetInfo(void)                              \
{                                                                             \
    return ARM_FLASHx_GetInfo(&FLASH_DRIVER_NAME##_DEV);                      \
}                                                                             \
                                                                              \
extern ARM_DRIVER_USART FLASH_DRIVER_NAME;                                    \
ARM_DRIVER_USART FLASH_DRIVER_NAME   = {                                      \
    ARM_USART_GetVersion,                                                     \
    ARM_USART_GetCapabilities,                                                \
    FLASH_DRIVER_NAME##_Initialize,                                           \
    FLASH_DRIVER_NAME##_Uninitialize,                                         \
    FLASH_DRIVER_NAME##_PowerControl,                                         \
    FLASH_DRIVER_NAME##_ReadData,                                             \
    FLASH_DRIVER_NAME##_ProgramData,                                          \
    FLASH_DRIVER_NAME##_EraseSector,                                          \
    FLASH_DRIVER_NAME##EraseChip,                                             \
    FLASH_DRIVER_NAME##GetStatus,                                             \
    FLASH_DRIVER_NAME##GetInfo
}

#endif  /* __DRIVER_FLASH_CMSDK_H__ */
