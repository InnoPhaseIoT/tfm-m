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
 * @file    inph_utils.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Utility functions to support main driver code
 */

#ifndef INPH_UTILS_H
#define INPH_UTILS_H

/* Private headers ----------------------------------------------------------*/
// --- #include "inph_console_io.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* Private typedef -----------------------------------------------------------*/

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char bool_t;
typedef unsigned int irq_t;

/* Private define ------------------------------------------------------------*/

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef NULL
#define NULL (0)
#endif

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __inline
#endif

#ifndef __IM
#define __IM volatile const /* Input structure Member (IM) */
#endif

#ifndef __OM
#define __OM volatile /* Output structure Member (OM) */
#endif

#ifndef __IOM
#define __IOM volatile /* Input Output structure Member (IOM) */
#endif

#ifndef bool
#define bool bool_t
#endif

#ifndef false
#define false FALSE
#endif

#ifndef true
#define true TRUE
#endif

/* suppress compiler warnings for unused parameters */
#define INPH_UNUSED_PARAMETER(x) ((void)(x))
#define INPH_CREATE_MASK(x) ((1U << (x + 1)) - 1) // x is number of bits in mask

/* Get the lower 8 bits of a 16-bit value. */
#define INPH_LO8(x) ((uint8_t)((x) & 0xFFU))
/* Get the upper 8 bits of a 16-bit value. */
#define INPH_HI8(x) ((uint8_t)((uint16_t)(x) >> 8U))

/* Get the lower 16 bits of a 32-bit value. */
#define INPH_LO16(x) ((uint16_t)((x) & 0xFFFFU))
/* Get the upper 16 bits of a 32-bit value. */
#define INPH_HI16(x) ((uint16_t)((uint32_t)(x) >> 16U))

/* Swap the byte ordering of a 16-bit value */
#define INPH_SWAP_ENDIAN16(x)                                                  \
    ((uint16_t)(((x) << 8U) | (((x) >> 8U) & 0x00FFU)))

/* Swap the byte ordering of a 32-bit value */
#define INPH_SWAP_ENDIAN32(x)                                                  \
    ((uint32_t)((((x) >> 24U) & 0x000000FFU) | (((x) & 0x00FF0000U) >> 8U)     \
                | (((x) & 0x0000FF00U) << 8U) | ((x) << 24U)))

/* Swap the byte ordering of a 64-bit value */
#define INPH_SWAP_ENDIAN64(x)                                                  \
    ((uint64_t)(((uint64_t)INPH_SWAP_ENDIAN32((uint32_t)(x)) << 32U)           \
                | INPH_SWAP_ENDIAN32((uint32_t)((x) >> 32U))))

/* register read and write operations */
#define INPH_GET_REG8(addr) (*((volatile uint8_t *const)(addr)))

#define INPH_SET_REG8(addr, value)                                             \
    (*((volatile uint8_t *)(addr)) = (uint8_t)(value))

#define INPH_GET_REG16(addr) (*((volatile uint16_t *const)(addr)))

#define INPH_SET_REG16(addr, value)                                            \
    (*((volatile uint16_t *)(addr)) = (uint16_t)(value))

#define INPH_GET_REG32(addr) (*((volatile uint32_t *const)(addr)))

#define INPH_SET_REG32(addr, value)                                            \
    (*((volatile uint32_t *)(addr)) = (uint32_t)(value))

/* bit field operations */
#define INPH_SET_BITS(reg, mask) (INPH_GET_REG32(reg) |= (mask))
#define INPH_CLR_BITS(reg, mask) (INPH_GET_REG32(reg) &= ~(mask))
#define INPH_GET_BITS(reg, mask) (INPH_GET_REG32(reg) & (mask))

// pad to 16/256-byte alignment
#define INPH_PAD16(x) (((x) % 16) != 0) ? ((x) + (16 - ((x) % 16))) : (x)
#define INPH_PAD32(x) (((x) % 32) != 0) ? ((x) + (32 - ((x) % 32))) : (x)
#define INPH_PAD64(x) (((x) % 64) != 0) ? ((x) + (64 - ((x) % 64))) : (x)
#define INPH_PAD256(x) (((x) % 256) != 0) ? ((x) + (256 - ((x) % 256))) : (x)

#define KB (1024)
#define MB (1024 * 1024)
#define GB (1024 * 1024 * 1024)

#define MILLISEC (1000)
#define MICROSEC (1000000)

/* Private declarations ------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/

#if defined(__cplusplus)
}
#endif

#endif // INPH_UTILS_H
