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
 * @file    inph_status_codes.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Generic status codes
 *
 */
#ifndef INPH_STATUS_CODES_H
#define INPH_STATUS_CODES_H

/* Private headers ----------------------------------------------------------*/

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>

/* Private typedef -----------------------------------------------------------*/

typedef enum {
    /** The result code is informational-only */
    INPH_RSLT_TYPE_INFO = 0U,
    /** The result code is warning of a problem but will proceed */
    INPH_RSLT_TYPE_WARNING = 1U,
    /** The result code is an error */
    INPH_RSLT_TYPE_ERROR = 2U,
    /** The result code is a fatal error */
    INPH_RSLT_TYPE_FATAL = 3U
} inph_en_rslt_type_t;

/* Private define ------------------------------------------------------------*/
#define INPH_DRIVER_ID_POSITION (18)
#define INPH_STATUS_TYPE_POSITION (16)
#define INPH_PDL_DRV_ID(id)                                                    \
    ((uint32_t)((uint32_t)((id) & 0x3FFF) << INPH_DRIVER_ID_POSITION))

#define INPH_PDL_STATUS_INFO                                                   \
    ((uint32_t)INPH_RSLT_TYPE_INFO                                             \
     << INPH_STATUS_TYPE_POSITION) /**< The error status type */
#define INPH_PDL_STATUS_WARNING                                                \
    ((uint32_t)INPH_RSLT_TYPE_WARNING                                          \
     << INPH_STATUS_TYPE_POSITION) /**< The error status type */
#define INPH_PDL_STATUS_ERROR                                                  \
    ((uint32_t)INPH_RSLT_TYPE_ERROR                                            \
     << INPH_STATUS_TYPE_POSITION) /**< The error status type */

#define INPH_RTC_ID INPH_PDL_DRV_ID(0x28)
#define INPH_I2C_ID INPH_PDL_DRV_ID(0x29) // TODO: define the ID number for I2C
#define INPH_SPI_ID INPH_PDL_DRV_ID(0x2B) // TODO: define the ID number for SPI
#define INPH_PWM_ID INPH_PDL_DRV_ID(0x2D)
#define INPH_OTP_ID INPH_PDL_DRV_ID(0x2F) // TODO: define the ID number for OTP

#define INPH_GPIO_ID INPH_PDL_DRV_ID(0x16)
#define INPH_UART_ID INPH_PDL_DRV_ID(0x2A)
#define INPH_UDMA_ID INPH_PDL_DRV_ID(0x13)
#define INPH_DMAC_ID INPH_PDL_DRV_ID(0x3F)

/** The XSPI driver ID, reported as part of an unsuccessful API return status
 * @ref inph_en_xspi_status_t
 */
#define INPH_XSPI_ID INPH_PDL_DRV_ID(0x2C)

/** The SDIO device driver ID, reported as part of an unsuccessful API return
 * status
 * @ref inph_en_sdiod_status_t
 */
#define INPH_SDIOD_ID INPH_PDL_DRV_ID(0x3A)

/** The I2S driver ID, reported as part of an unsuccessful API return
 * status
 * @ref inph_en_i2s_status_t
 */
#define INPH_I2S_ID INPH_PDL_DRV_ID(0x20)

/**
 * \addtogroup group_rtc_enums
 * \{
 */
/** RTC status enumeration */
typedef enum {
    INPH_RTC_SUCCESS = 0x00U, /**< Successful */
    INPH_RTC_BAD_PARAM = INPH_RTC_ID | INPH_PDL_STATUS_ERROR
        | 0x01U, /**< One or more invalid parameters */
    INPH_RTC_TIMEOUT
    = INPH_RTC_ID | INPH_PDL_STATUS_ERROR | 0x02U, /**< Time-out occurs */
    INPH_RTC_INVALID_STATE = INPH_RTC_ID | INPH_PDL_STATUS_ERROR
        | 0x03U, /**< Operation not setup or is in an improper state */
    INPH_RTC_UNKNOWN
    = INPH_RTC_ID | INPH_PDL_STATUS_ERROR | 0xFFU /**< Unknown failure */
} inph_en_rtc_status_t;

/** \} group_rtc_enums */

/**
 * \addtogroup group_i2c_enums
 * \{
 */

/**
 * @enum inph_en_i2c_status_t
 *
 * @brief I2C status codes
 */
typedef enum {
    /**
     * @brief Successful
     */
    INPH_I2C_SUCCESS = 0x00U,
    /**
     * @brief Bad Parameter
     */
    INPH_I2C_BAD_PARAM = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 1U),
    /**
     * @brief Master not ready
     */
    INPH_I2C_MASTER_NOT_READY = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 2U),
    /**
     * @brief Master Manual Timeout
     */
    INPH_I2C_MASTER_MANUAL_TIMEOUT = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 3U),
    /**
     * @brief Master Manual Address NAK
     */
    INPH_I2C_MASTER_MANUAL_ADDR_NAK
    = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 4U),
    /**
     * @brief Master Manual NAK
     */
    INPH_I2C_MASTER_MANUAL_NAK = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 5U),
    /**
     * @brief Master Manual Arbitarator lost
     */
    INPH_I2C_MASTER_MANUAL_ARB_LOST
    = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 6U),
    /**
     * @brief Master BUS error
     */
    INPH_I2C_MASTER_MANUAL_BUS_ERR = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 7U),
    /**
     * @brief Master Manual Abort Start
     */
    INPH_I2C_MASTER_MANUAL_ABORT_START
    = (INPH_I2C_ID | INPH_PDL_STATUS_ERROR | 8U)
} inph_en_i2c_status_t;

/** \} group_i2c_enums */

/** PWM status definitions */
typedef enum {
    INPH_PWM_SUCCESS = 0x00U, /**< Successful */
    INPH_PWM_BAD_PARAM = INPH_PWM_ID | INPH_PDL_STATUS_ERROR
        | 0x01U, /**< One or more invalid parameters */
    INPH_PWM_UNSUPPORTED_FEATURE
    = INPH_PWM_ID | INPH_PDL_STATUS_ERROR | 0x02U, /**< Feature Unsupported */
} inph_en_pwm_status_t;


/** TCPWM status definitions */
typedef enum {
	INPH_TCPWM_PWM_SUCCESS = 0x00U, /**< Successful */
	INPH_TCPWM_PWM_BAD_PARAM = 0x01U, /**< One or more invalid parameters */
	INPH_TCPWM_PWM_UNSUPPORTED_FEATURE = 0x02U, /**< Feature Unsupported */
} inph_en_tcpwm_pwm_status_t;

/** TCPWM status definitions */
typedef enum
{
    INPH_TCPWM_SUCCESS = 0x00U,                                           /**< Successful */
    INPH_TCPWM_BAD_PARAM =  0x01U,     /**< One or more invalid parameters */
    INPH_TCPWM_UNSUPPORTED_FEATURE =  0x02U,  /**< Feature Unsupported */
} inph_en_tcpwm_status_t;

/** TRIGMATRIX status definitions */
typedef enum
{
    INPH_TRIGMATRIX_SUCCESS = 0x00U,                                           /**< Successful *//**< INPH_TRIGMATRIX_SUCCESS */
    INPH_TRIGMATRIX_BAD_PARAM =  0x01U,     /**< One or more invalid parameters */               /**< INPH_TRIGMATRIX_BAD_PARAM */          /**< INPH_TRIGMATRIX_BAD_PARAM *//**< INPH_TRIGMATRIX_BAD_PARAM */
    INPH_TRIGMATRIX_UNSUPPORTED_FEATURE =  0x02U,  /**< Feature Unsupported */                   /**< INPH_TRIGMATRIX_UNSUPPORTED_FEATURE *//**< INPH_TRIGMATRIX_UNSUPPORTED_FEATURE */
} inph_en_trigmatrix_status_t;
/**
 * \addtogroup group_spi_enums
 * \{
 */

/** SPI status codes */
typedef enum {
    INPH_SPI_SUCCESS = 0U, /**< Successful */
    INPH_SPI_BAD_PARAM = (INPH_SPI_ID | INPH_PDL_STATUS_ERROR | 1U),
    INPH_SPI_TRANSFER_BUSY = (INPH_SPI_ID | INPH_PDL_STATUS_ERROR | 2U),
    INPH_SPI_NOT_READY = (INPH_SPI_ID | INPH_PDL_STATUS_ERROR | 3U),
    INPH_SPI_RECEIVE_ERROR = (INPH_SPI_ID | INPH_PDL_STATUS_ERROR | 4U),
    INPH_SPI_TRANSFER_ERROR = (INPH_SPI_ID | INPH_PDL_STATUS_ERROR | 5U),
    INPH_SPI_TRANCIVER_ERROR = (INPH_SPI_ID | INPH_PDL_STATUS_ERROR | 6U)
} inph_en_spi_status_t;

/** \} group_spi_enums */

/**
 * \addtogroup group_uart_enums_uart
 * \{
 */

/**
 * @enum inph_en_uart_status_t
 *
 * @brief UART PDL result status
 */
typedef enum {
    /**
     * @brief Operation completed successfully
     */
    INPH_UART_SUCCESS = 0U,
    /**
     * @brief invalid parameter passed
     */
    INPH_UART_BAD_PARAM = (INPH_UART_ID | INPH_PDL_STATUS_ERROR | 1U),
    /**
     * @brief UART is busy
     */
    INPH_UART_RECEIVE_BUSY = (INPH_UART_ID | INPH_PDL_STATUS_ERROR | 2U),
    /**
     * @brief transmit is process and busy
     */
    INPH_UART_TRANSMIT_BUSY = (INPH_UART_ID | INPH_PDL_STATUS_ERROR | 3U)
} inph_en_uart_status_t;

/** \} group_uart_enums_uart */

typedef enum inph_en_udma_status {
    INPH_UDMA_IDLE = 0,
    INPH_UDMA_READ_CNTL_DATA = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 1U),
    INPH_UDMA_READ_SRC_DATA_PTR = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 2U),
    INPH_UDMA_READ_END_DATA_PTR = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 3U),
    INPH_UDMA_READ_SRC_DATA = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 4U),
    INPH_UDMA_WRITE_DST_DATA = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 5U),
    INPH_UDMA_WAIT_TO_CLEAR = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 6U),
    INPH_UDMA_WRITE_CHANNEL_DATA = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 7U),
    INPH_UDMA_STALLED = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 8U),
    INPH_UDMA_DONE = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 9U),
    INPH_UDMA_SCT_GTHR_TRAN = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 10U),
    INPH_UDMA_UNDEFINED = (INPH_UDMA_ID | INPH_PDL_STATUS_ERROR | 11U)
} inph_en_udma_status_t;

/**
 * \addtogroup group_gpio_enums
 * \{
 */

/**
 * @enum inph_en_gpio_status_t
 *
 * @brief GPIO PDL result status
 */
typedef enum {
    /**
     * @brief Success
     */
    INPH_GPIO_SUCCESS = 0x00UL,

    /**
     * @brief Bad Parameter
     */
    INPH_GPIO_BAD_PARAM = (INPH_GPIO_ID | INPH_PDL_STATUS_ERROR | 1U)
} inph_en_gpio_status_t;

/** \} group_gpio_enums */

/** \addtogroup group_dmac_enums
 * \{
 */

/**
 * @enum inph_en_dmac_status_t
 *
 * @brief DMAC API status enumeration
 */
typedef enum {
    /**
     * @brief Success
     */
    INPH_DMAC_SUCCESS = 0x00UL,

    /**
     * @brief Error
     */
    INPH_DMAC_BAD_PARAM = (INPH_DMAC_ID | INPH_PDL_STATUS_ERROR | 1U)
} inph_en_dmac_status_t;

/** \} group_dmac_enums */

/** \addtogroup group_xspi_enums
 * \{
 */

/** xSPI device error codes. */
typedef enum {
    INPH_XSPI_SUCCESS = 0x00U, /**< Successful. */
    INPH_XSPI_ERROR = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x01U, /**< Non-specific error code. */
    INPH_XSPI_ERROR_INVALID_PARAMETER = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x02U, /**< Invalid input parameter error code */
    INPH_XSPI_OPERATION_INPROGRESS = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x03U, /**< Previous operation in progress(busy) error code */
    INPH_XSPI_ERROR_TIMEOUT = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x04U, /**< Previous operation timed-out error code */
    INPH_XSPI_ERROR_FIFO_FULL
    = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR | 0x05U, /**< FIFO Full error code */
    INPH_XSPI_NO_QE_BIT = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x06, /**< Device does not have QE bit */
    INPH_XSPI_NO_SFDP_SUPPORT = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x07, /**< Device does not support SFDP */
    INPH_XSPI_SFDP_CS0_FAILED = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x08 << 0, /**< Failed to initialize memory connected to chip select 0
                        by SFDP */
    INPH_XSPI_SFDP_CS1_FAILED = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x08 << 1, /**< Failed to initialize memory connected to chip select 1
                        by SFDP */
    INPH_XSPI_SFDP_ADDRMODE_UNSUPPORTED = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x80, /**< Address Mode not supported by device */
    INPH_XSPI_SFDP_MEMSIZE_UNSUPPORTED = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x81, /**< Device does not support the memory size */
    INPH_XSPI_SFDP_4K_ERASE_UNSUPPORTED = INPH_XSPI_ID | INPH_PDL_STATUS_ERROR
        | 0x82 /**< Device does not support the 4K erase */
} inph_en_xspi_status_t;

/** \} group_xspi_enums */

/** \addtogroup group_sdio_enums
 * \{
 */

/** SD device error codes. */
typedef enum {
    INPH_SDIO_DEV_SUCCESS = 0x00U, /**< Successful. */
    INPH_SDIO_DEV_ERROR = INPH_SDIOD_ID | INPH_PDL_STATUS_ERROR
        | 1u, /**< Non-specific error code. */
    INPH_SDIO_DEV_ERROR_INVALID_PARAMETER = INPH_SDIOD_ID
        | INPH_PDL_STATUS_ERROR | 2u, /**< Invalid input parameter error code */
    INPH_SDIO_DEV_OPERATION_INPROGRESS = INPH_SDIOD_ID | INPH_PDL_STATUS_ERROR
        | 3u, /**< Previous operation is progress err ocode */
    INPH_SDIO_DEV_ERROR_TIMEOUT = INPH_SDIOD_ID | INPH_PDL_STATUS_ERROR
        | 4u /**< Previous operation timed-out error code */
} inph_en_sdio_dev_status_t;

/** \} group_sdio_enums */

/**
 * \addtogroup group_i2s_enums
 * \{
 */

/** I2S error codes. */
typedef enum {
    INPH_I2S_SUCCESS = 0x00U, /**< Successful. */
    INPH_I2S_ERROR
    = INPH_I2S_ID | INPH_PDL_STATUS_ERROR | 1u, /**< Non-specific error code. */
    INPH_I2S_BAD_PARAM = INPH_I2S_ID | INPH_PDL_STATUS_ERROR
        | 2u /**< Invalid input parameter error code */
} inph_en_i2s_status_t;

/** \} group_i2s_enums */

/**
 * \addtogroup group_dualtimer_enums
 * \{
 */
/** Dual Timer error codes */
typedef enum {
    /**
     * @brief Success
     */
    INPH_DUALTIMER_SUCCESS = 0x00U,

    /**
     * @brief Address Error
     */
    INPH_DUALTIMER_ADDRESS_ERROR = 0x01U,

    /**
     * @brief Mode Error
     */
    INPH_DUALTIMER_MODE_ERROR = 0x02U,
} inph_en_dualtimer_status_t;

/** \} group_dualtimer_enums */

/**
 * \addtogroup group_lptimer_enums
 * \{
 */

/** Low Power Timer error codes */
typedef enum {
    /**
     * @brief Success
     */
    INPH_LPTIMER_SUCCESS = 0x00U,
    /**
     * @brief ID Error
     */
    INPH_LPTIMER_ID_ERROR = 0x01U,
    /**
     * @brief Mode Error
     */
    INPH_LPTIMER_MODE_ERROR = 0x02U,
} inph_en_lptimer_status_t;

/** \} group_lptimer_enums */

/** OTP User Region status codes */
typedef enum {
    INPH_OTP_SUCCESS = 0,
    INPH_OTP_PARM_NUM_BITS_ERROR = (INPH_OTP_ID | INPH_PDL_STATUS_ERROR | 1U),
    INPH_OTP_PARM_BIT_OFFSET_ERROR = (INPH_OTP_ID | INPH_PDL_STATUS_ERROR | 2U),
    INPH_OTP_PARM_INVALID_RANGE = (INPH_OTP_ID | INPH_PDL_STATUS_ERROR | 3U),
    INPH_OTP_PARM_RANGE_MISMATCH = (INPH_OTP_ID | INPH_PDL_STATUS_ERROR | 4U),
    INPH_OTP_WRITE_READ_VERIFY_ERROR
    = (INPH_OTP_ID | INPH_PDL_STATUS_ERROR | 5U)
} inph_en_otp_status_t;
/** PDM error codes */
typedef enum {
    INPH_PDM_SUCCESS = 0x00U,
    INPH_PDM_ERROR = 0x01U,
    INPH_PDM_MODE_ERROR = 0x02U,
} inph_en_pdm_status_t;

/**
 * \addtogroup group_hkadc_enums
 * \{
 */
typedef enum {
    INPH_HKADC_SUCCESS =0,
    INPH_HKADC_ERROR,
    INPH_HKADC_MODE_ERROR,
	INPH_HKADC_PARAMETER_ERROR,
	INPH_HKADC_NON_SUPPORTED
} inph_en_hkadc_status_t;
/** \} group_hkadc_enums */

/* Private declarations ------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#if defined(__cplusplus)
}
#endif

#endif // INPH_STATUS_CODES_H
