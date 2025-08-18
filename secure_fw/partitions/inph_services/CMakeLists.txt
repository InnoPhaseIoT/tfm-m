#-------------------------------------------------------------------------------
# Copyright (c) 2021-2022, Arm Limited. All rights reserved.
# Copyright (c) 2021-2023 Cypress Semiconductor Corporation (an Infineon company)
# or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

if (NOT TFM_PARTITION_INPH_SERVICES)
    return()
endif()

add_library(tfm_app_rot_partition_inph_services STATIC)

target_sources(tfm_app_rot_partition_inph_services
    PRIVATE
        tfm_inph_services_partition.c
)

# The intermedia file defines the partition stack.
target_sources(tfm_app_rot_partition_inph_services
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/inph_services/auto_generated/intermedia_tfm_inph_services.c
)

# The load info file includes the static data of the partition.
target_sources(tfm_partitions
    INTERFACE
        ${CMAKE_BINARY_DIR}/generated/secure_fw/partitions/inph_services/auto_generated/load_info_tfm_inph_services.c
)

add_dependencies(tfm_app_rot_partition_inph_services manifest_tool)

target_link_libraries(tfm_app_rot_partition_inph_services
    PRIVATE
        tfm_sprt
)

target_link_libraries(tfm_partitions
    INTERFACE
        tfm_app_rot_partition_inph_services
)

