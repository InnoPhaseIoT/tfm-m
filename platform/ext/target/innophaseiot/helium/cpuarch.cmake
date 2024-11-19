#-------------------------------------------------------------------------------
# Copyright (c) 2023, Arm Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

# In the new split build this file defines a platform specific parameters
# like mcpu core, arch etc and to be included by toolchain files.

set(TFM_SYSTEM_PROCESSOR cortex-m33)
set(TFM_SYSTEM_ARCHITECTURE armv8-m.main)
set(TFM_SYSTEM_DSP OFF)
set(CONFIG_TFM_FP_ARCH "fpv5-d16")
set(CONFIG_TFM_FP_ARCH_ASM "FPv5_D16")

#set(CRYPTO_HW_ACCELERATOR_TYPE inph)
add_compile_definitions(
    HELIUMA0_FLASHONLY_CNTRL1
    HELIUMA0_FLASHONLY_CNTRL2
    HELIUMA0_FLASH_CNTRL1_PSRAM
    HELIUMA0_FLASH_CNTRL2_PSRAM
    HELIUMA0_PSRAMONLY_CNTRL1
    HELIUMA0_PSRAMONLY_CNTRL2
    HELIUMA0_NOFLASH_NOPSRAM    
)