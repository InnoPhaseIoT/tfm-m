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
 * @file    inph_console_io.h
 * @author  Innophase Firmware Team
 * @brief
 *
 */

#ifndef INPH_CONSOLE_IO_H
#define INPH_CONSOLE_IO_H

/* Private headers ----------------------------------------------------------*/

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>
/* Private define ------------------------------------------------------------*/
#define MAX_INPUT_STR_SIZE (80)

/* Private typedef -----------------------------------------------------------*/

/* Private declarations ------------------------------------------------------*/

/* Private function ----------------------------------------------------------*/

void
putChr(char chr);
void
putStr(char *string);
char
getChr();
int8_t
getString(char *str_data);
char
getMenuChr();
void
intToString(uint32_t num, char *str);
void
putNewLine();

#if defined(__cplusplus)
}
#endif

#endif // INPH_CONSOLE_IO_H
