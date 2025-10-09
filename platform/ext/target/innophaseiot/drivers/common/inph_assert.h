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
 * @file    inph_assert.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Utility functions for handling asserts
 *
 */

#ifndef INPH_ASSERTS_H
#define INPH_ASSERTS_H

#include "inph_console_io.h"
#include "inph_utils.h"
#include <stdio.h>

/* Private headers ----------------------------------------------------------*/

#if defined(__cplusplus)
extern "C" {
#endif

__STATIC_INLINE void
breakExecution();

/* Private define ------------------------------------------------------------*/

#define ASSERTDebug(M, ...)                                                    \
    {                                                                          \
        printf("[%s_%d]" M "\n", __FILE__, __LINE__, ##__VA_ARGS__);           \
        breakExecution();                                                      \
    }

#define INPH_ASSERT(x)                                                         \
    {                                                                          \
        if (!((uint32_t)(x))) {                                                \
            ASSERTDebug("ASSERT failed! [%d] == 0.\n", ((int)(x)));            \
        }                                                                      \
    }

#define INPH_ASSERT_TRUE(x)                                                    \
    {                                                                          \
        if (!((uint32_t)(x))) {                                                \
            ASSERTDebug("ASSERT_TRUE failed! [%d] == 0.\n", ((int)(x)));       \
        }                                                                      \
    }

#define INPH_ASSERT_FALSE(x)                                                   \
    {                                                                          \
        if (((uint32_t)(x))) {                                                 \
            ASSERTDebug("ASSERT_FALSE failed! [%d] != 0.\n", ((int)(x)));      \
        }                                                                      \
    }

#define INPH_ASSERT_EQ(x, y)                                                   \
    {                                                                          \
        if (((uint32_t)(x)) != ((uint32_t)(y))) {                              \
            ASSERTDebug("ASSERT_EQ failed! [%d] != [%d].\n", ((int)(x)),       \
                        ((int)(y)));                                           \
        }                                                                      \
    }

#define INPH_ASSERT_NEQ(x, y)                                                  \
    {                                                                          \
        if (((uint32_t)(x)) == ((uint32_t)(y))) {                              \
            ASSERTDebug("ASSERT_NEQ failed! [%d] == [%d].\n", ((int)(x)),      \
                        ((int)(y)));                                           \
        }                                                                      \
    }

// greater than
#define INPH_ASSERT_GT(x, y)                                                   \
    {                                                                          \
        if (((uint32_t)(x)) <= ((uint32_t)(y))) {                              \
            ASSERTDebug("ASSERT_GT failed! [%d] <= [%d].\n", ((int)(x)),       \
                        ((int)(y)));                                           \
        }                                                                      \
    }

// greater or equal
#define INPH_ASSERT_GE(x, y)                                                   \
    {                                                                          \
        if (((uint32_t)(x)) < ((uint32_t)(y))) {                               \
            ASSERTDebug("ASSERT_GE failed! [%d] < [%d].\n", ((int)(x)),        \
                        ((int)(y)));                                           \
        }                                                                      \
    }

// less than
#define INPH_ASSERT_LT(x, y)                                                   \
    {                                                                          \
        if (((uint32_t)(x)) >= ((uint32_t)(y))) {                              \
            ASSERTDebug("ASSERT_LT failed! [%d] >= [%d].\n", ((int)(x)),       \
                        ((int)(y)));                                           \
        }                                                                      \
    }

/*******************************************************************************
 * Function Name:
 ****************************************************************************//**
*
* description:
*
* @param[in] None
*
* @param[out] None
*
* @return
* None
*
*
*******************************************************************************/
__STATIC_INLINE void
breakExecution()
{
    //--- putNewLine();
    //--- putStr("break execution...");
    while (TRUE)
        ;
}

#if defined(__cplusplus)
}
#endif

#endif // INPH_ASSERTS_H
