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
 * @file    inph_device.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Device wizard
 */


#ifndef __INPH_DEVICE_H
#define __INPH_DEVICE_H


#define INPH_HELIUM_A0 TRUE //fix during config
#define INPH_MPC_SRAM1_S TRUE

/* MPC SRAM ranges */

#define INPH_MPC_MEM_BASE_ADDR_S 0x0000
#define INPH_MPC_MEM_BASE_ADDR_NS 0x0000
#define INPH_MPC_SRAM1_RANGE_BASE_S 0x0000
#define INPH_MPC_SRAM1_RANGE_LIMIT_S 0x0000
#define INPH_MPC_SRAM1_RANGE_BASE_NS 0x0000
#define INPH_MPC_SRAM1_RANGE_LIMIT_NS 0x0000


#ifdef INPH_HELIUM_A0

static struct inph_ppc_dev_cfg_t APB_PPCHLMA0_DEV_CFG = {
    .spctrl_base  = CMSDK_SPCTRL_BASE_S,
    .nspctrl_base = CMSDK_NSPCTRL_BASE_NS };

static struct inph_ppc_dev_data_t APB_PPCHLMA0_DEV_DATA_S = {
    .p_ns_ppc  = 0,
    .p_sp_ppc  = 0,
    .p_nsp_ppc = 0,
    .int_bit_mask = 0,
    .state = 0 };

struct inph_ppc_dev_t APB_PPCEXP2_DEV_S = {
    &APB_PPCHLMA0_DEV_CFG, &APB_PPCHLMA0_DEV_DATA_S };

/* MPC definitions */

#ifdef INPH_MPC_SRAM1_S
static const struct inph_mpc_sie200_dev_cfg_t MPC_CODE_SRAM1_DEV_CFG_S = {
    .base = MPC_CODE_SRAM1_BASE_S};
static struct inph_mpc_sie200_dev_data_t MPC_CODE_SRAM1_DEV_DATA_S = {
    .range_list = 0,
    .nbr_of_ranges = 0,
    .state = 0,
    .reserved = 0};
struct inph_mpc_sie200_dev_t INPH_MPC_SRAM1_DEV_S = {
    &(MPC_CODE_SRAM1_DEV_CFG_S),
    &(MPC_CODE_SRAM1_DEV_DATA_S)};
#endif

#endif //INPH_HELIUM_A0


#endif  /* __INPH_DEVICE_H */
