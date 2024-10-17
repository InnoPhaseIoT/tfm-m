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
 * @file    inph_nspriv_registers.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Device wizard
 */

#ifndef __INPH_NSPRIV_REGISTERS_H
#define __INPH_NSPRIV_REGISTERS_H

/* Private headers ----------------------------------------------------------*/
#include "tfm_utils.h"

/*  APBNSPRVPPCBASE0 DESCRIPTION :Base 0 Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_0_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_0_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_APBNSPRVPPCBASE0;

/*  APBNSPRVPPCBASE1 DESCRIPTION :Base 1 (MPCs) Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_1_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_1_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_APBNSPRVPPCBASE1;

/*  APBNSPRVPPCBASE2 DESCRIPTION :Base 1 (Misc) Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_BASE_2_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_BASE_2_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_APBNSPRVPPCBASE2;

/*  APBNSPRVPPCSYS DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_APB_SYS_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_APB_SYS_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_APBNSPRVPPCSYS;

/*  AHBNSPRVPPCSYS DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_AHB_SYS_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_AHB_SYS_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_AHBNSPRVPPCSYS;

/*  APBNSPRVPPCPERIPH0 DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_0_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_0_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_APBNSPRVPPCPERIPH0;

/*  APBNSPRVPPCPERIPH1 DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_PERIPH_1_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_PERIPH_1_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_APBNSPRVPPCPERIPH1;

/*  AHBNSPRVPPCSDIO DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Reserved : 16;               /*31:16 SW=ro HW=ro 0x0 */
            uint32_t PPC_SDIO_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_SDIO_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t Reserved : 16;               /*16:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_AHBNSPRVPPCSDIO;

/*  AHBNSPRVPPCCXIP DESCRIPTION :System Control Sub Non-Secure unprivileged Access APB slave Peripheral Protection Control. Each field defines the Non-Secure unprivileged settings for an associated peripheral:

1: Allow Non-Secure unprivileged access
0: Disallow Non-Secure unprivileged access
Resets to 0 */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t PPC_CRYPTO_XIP2_NS_PRV_N : 16;               /*31:16 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP1_NS_PRV_N : 16;               /*15:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PPC_CRYPTO_XIP1_NS_PRV_N : 16;               /*0:15 SW=rw HW=ro 0x0 */
            uint32_t PPC_CRYPTO_XIP2_NS_PRV_N : 16;               /*16:31 SW=rw HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}ns_privilege_regs_AHBNSPRVPPCCXIP;

typedef volatile struct inph_nspriv_security_base{
    ns_privilege_regs_APBNSPRVPPCBASE0  APBNSPRVPPCBASE0;
    ns_privilege_regs_APBNSPRVPPCBASE1  APBNSPRVPPCBASE1;
    ns_privilege_regs_APBNSPRVPPCBASE2  APBNSPRVPPCBASE2;
    ns_privilege_regs_APBNSPRVPPCSYS  APBNSPRVPPCSYS;
    ns_privilege_regs_AHBNSPRVPPCSYS  AHBNSPRVPPCSYS;
    ns_privilege_regs_APBNSPRVPPCPERIPH0  APBNSPRVPPCPERIPH0;
    ns_privilege_regs_APBNSPRVPPCPERIPH1  APBNSPRVPPCPERIPH1;
    ns_privilege_regs_AHBNSPRVPPCSDIO  AHBNSPRVPPCSDIO;
    ns_privilege_regs_AHBNSPRVPPCCXIP  AHBNSPRVPPCCXIP;
    
    uint8_t filler10[0x1FDC];
    
    
} inph_nspriv_security_t;

#endif /* __INPH_NSPRIV_REGISTERS_H */

/* end */


