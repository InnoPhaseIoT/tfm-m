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
 * @file    platform_retarget_dev.c
 * @author  InnophaseIOT Firmware Team
 * @brief   Device wizard
 */

#include "platform_retarget_dev.h"
#include "platform_retarget.h"
#include "inph_mpc_drv.h"
#include "inph_ppc_drv.h"

/* PPC definitions */

static struct inph_ppc_dev_cfg_t APB_PPCBASE0_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCBASE0_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCBASE0_DEV_S = {
    &APB_PPCBASE0_DEV_CFG, &APB_PPCBASE0_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCBASE1_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCBASE1_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCBASE1_DEV_S = {
    &APB_PPCBASE1_DEV_CFG, &APB_PPCBASE1_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCBASE2_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCBASE2_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCBASE2_DEV_S = {
    &APB_PPCBASE2_DEV_CFG, &APB_PPCBASE2_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCPERIPH0_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCPERIPH0_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCPERIPH0_DEV_S = {
    &APB_PPCPERIPH0_DEV_CFG, &APB_PPCPERIPH0_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCPERIPH1_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCPERIPH1_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCPERIPH1_DEV_S = {
    &APB_PPCPERIPH1_DEV_CFG, &APB_PPCPERIPH1_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t AHB_PPCCXIP_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCCXIP_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCCXIP_DEV_S = {
    &AHB_PPCCXIP_DEV_CFG, &AHB_PPCCXIP_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t AHB_PPCSDIO_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t AHB_PPCSDIO_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t AHB_PPCSDIO_DEV_S = {
    &AHB_PPCSDIO_DEV_CFG, &AHB_PPCSDIO_DEV_DATA_S };

static struct inph_ppc_dev_cfg_t APB_PPCSYSTEM_DEV_CFG = {
    .spctrl_base  = INPH_SPCTRL_BASE_S,
    .nspctrl_base = INPH_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCSYSTEM_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCSYSTEM_DEV_S = {
    &APB_PPCSYSTEM_DEV_CFG, &APB_PPCSYSTEM_DEV_DATA_S };


/* MPC definitions */


static const struct inph_mpc_sie200_dev_cfg_t MPC_CODE_SRAM0_DEV_CFG_S = {
    .base = MPC_CODE_SRAM0_BASE_S};

static struct inph_mpc_sie200_dev_data_t MPC_CODE_SRAM0_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};

struct inph_mpc_sie200_dev_t INPH_MPC_SRAM0_DEV_S = {
    &(MPC_CODE_SRAM0_DEV_CFG_S),
    &(MPC_CODE_SRAM0_DEV_DATA_S)};


//#endif //INPH_HELIUM_A0

