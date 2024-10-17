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
 * @file    inph_mpc_registers.h
 * @author  InnophaseIOT Firmware Team
 * @brief   Device wizard
 */

#ifndef __INPH_MPC_REGISTERS_H
#define __INPH_MPC_REGISTERS_H

#include "tfm_utils.h"

/*  CTRL DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t SECCFGLOCK : 1;               /*31 SW=rw HW=ro 0x0 */
            uint32_t RESERVED309 : 22;               /*30:9 SW=ro HW=ro 0x0 */
            uint32_t AUTOINCEN : 1;               /*8 SW=rw HW=ro 0x1 */
            uint32_t RESERVED75 : 3;               /*7:5 SW=ro HW=ro 0x0 */
            uint32_t CFGSECRESP : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t RESERVED30 : 4;               /*3:0 SW=ro HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t RESERVED30 : 4;               /*0:3 SW=ro HW=ro 0x0 */
            uint32_t CFGSECRESP : 1;               /*4 SW=rw HW=ro 0x0 */
            uint32_t RESERVED75 : 3;               /*5:7 SW=ro HW=ro 0x0 */
            uint32_t AUTOINCEN : 1;               /*8 SW=rw HW=ro 0x1 */
            uint32_t RESERVED309 : 22;               /*9:30 SW=ro HW=ro 0x0 */
            uint32_t SECCFGLOCK : 1;               /*31 SW=rw HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_CTRL;

/*  BLKMAX DESCRIPTION :description */
typedef union {
    struct {
        uint32_t BlockMax : 32;               /*31:0 SW=ro HW=ro 0x1F */
    } bf;
    uint32_t  dw;
    
    
}sie200ahb5memprot_BLKMAX;

/*  BLKCFG DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t Initinprogress : 1;               /*31 SW=ro HW=ro 0x0 */
            uint32_t RESERVED304 : 27;               /*30:4 SW=ro HW=ro 0x0 */
            uint32_t BLKCFG : 4;               /*3:0 SW=ro HW=ro 0x3 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t BLKCFG : 4;               /*0:3 SW=ro HW=ro 0x3 */
            uint32_t RESERVED304 : 27;               /*4:30 SW=ro HW=ro 0x0 */
            uint32_t Initinprogress : 1;               /*31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_BLKCFG;

/*  BLKIDX DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED : 27;               /*31:5 SW=ro HW=ro 0x0 */
            uint32_t BlockIndex : 5;               /*4:0 SW=rw HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t BlockIndex : 5;               /*0:4 SW=rw HW=ro 0x0 */
            uint32_t RESERVED : 27;               /*5:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_BLKIDX;

/*  BLKLUT DESCRIPTION :description */
typedef union {
    struct {
        uint32_t BlockLUT : 32;               /*31:0 SW=rw HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}sie200ahb5memprot_BLKLUT;

/*  INTSTAT DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED311 : 31;               /*31:1 SW=ro HW=ro 0x0 */
            uint32_t MPCIRQTriggered : 1;               /*0 SW=ro HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t MPCIRQTriggered : 1;               /*0 SW=ro HW=ro 0x0 */
            uint32_t RESERVED311 : 31;               /*1:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_INTSTAT;

/*  INTCLEAR DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED311 : 31;               /*31:1 SW=ro HW=ro 0x0 */
            uint32_t MPCIRQClear : 1;               /*0 SW=wo HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t MPCIRQClear : 1;               /*0 SW=wo HW=ro 0x0 */
            uint32_t RESERVED311 : 31;               /*1:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_INTCLEAR;

/*  INTEN DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED311 : 31;               /*31:1 SW=ro HW=ro 0x0 */
            uint32_t MPCIRQEnable : 1;               /*0 SW=rw HW=ro 0x1 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t MPCIRQEnable : 1;               /*0 SW=rw HW=ro 0x1 */
            uint32_t RESERVED311 : 31;               /*1:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_INTEN;

/*  INTINFO1 DESCRIPTION :description */
typedef union {
    struct {
        uint32_t HADDRField : 32;               /*31:0 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}sie200ahb5memprot_INTINFO1;

/*  INTINFO2 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED3118 : 14;               /*31:18 SW=ro HW=ro 0x0 */
            uint32_t CFGNSField : 1;               /*17 SW=ro HW=ro 0x0 */
            uint32_t HNONSECField : 1;               /*16 SW=ro HW=ro 0x0 */
            uint32_t HMASTERField : 16;               /*15:0 SW=ro HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t HMASTERField : 16;               /*0:15 SW=ro HW=ro 0x0 */
            uint32_t HNONSECField : 1;               /*16 SW=ro HW=ro 0x0 */
            uint32_t CFGNSField : 1;               /*17 SW=ro HW=ro 0x0 */
            uint32_t RESERVED3118 : 14;               /*18:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_INTINFO2;

/*  INTSET DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED311 : 31;               /*31:1 SW=ro HW=ro 0x0 */
            uint32_t MPCIRQSet : 1;               /*0 SW=wo HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t MPCIRQSet : 1;               /*0 SW=wo HW=ro 0x0 */
            uint32_t RESERVED311 : 31;               /*1:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_INTSET;

/*  PIDR4 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t SIZE : 4;               /*7:4 SW=ro HW=ro 0x0 */
            uint32_t DES2 : 4;               /*3:0 SW=ro HW=ro 0x4 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t DES2 : 4;               /*0:3 SW=ro HW=ro 0x4 */
            uint32_t SIZE : 4;               /*4:7 SW=ro HW=ro 0x0 */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR4;

/*  PIDR5 DESCRIPTION :description */
typedef union {
    struct {
        uint32_t RESERVED310 : 32;               /*31:0 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR5;

/*  PIDR6 DESCRIPTION :description */
typedef union {
    struct {
        uint32_t RESERVED310 : 32;               /*31:0 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR6;

/*  PIDR7 DESCRIPTION :description */
typedef union {
    struct {
        uint32_t RESERVED310 : 32;               /*31:0 SW=ro HW=ro 0x0 */
    } bf;
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR7;

/*  PIDR0 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t PART0 : 8;               /*7:0 SW=ro HW=ro 0x60 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PART0 : 8;               /*0:7 SW=ro HW=ro 0x60 */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR0;

/*  PIDR1 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t DES0 : 4;               /*7:4 SW=ro HW=ro 0xB */
            uint32_t PART1 : 4;               /*3:0 SW=ro HW=ro 0x8 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PART1 : 4;               /*0:3 SW=ro HW=ro 0x8 */
            uint32_t DES0 : 4;               /*4:7 SW=ro HW=ro 0xB */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR1;

/*  PIDR2 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t REVISION : 4;               /*7:4 SW=ro HW=ro 0x1 */
            uint32_t JEDEC : 1;               /*3 SW=ro HW=ro 0x1 */
            uint32_t DES1 : 3;               /*2:0 SW=ro HW=ro 0x3 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t DES1 : 3;               /*0:2 SW=ro HW=ro 0x3 */
            uint32_t JEDEC : 1;               /*3 SW=ro HW=ro 0x1 */
            uint32_t REVISION : 4;               /*4:7 SW=ro HW=ro 0x1 */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR2;

/*  PIDR3 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t REVAND : 4;               /*7:4 SW=ro HW=ro 0x0 */
            uint32_t CMOD : 4;               /*3:0 SW=ro HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t CMOD : 4;               /*0:3 SW=ro HW=ro 0x0 */
            uint32_t REVAND : 4;               /*4:7 SW=ro HW=ro 0x0 */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_PIDR3;

/*  CIDR0 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t PRMBL0 : 8;               /*7:0 SW=ro HW=ro 0xD */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PRMBL0 : 8;               /*0:7 SW=ro HW=ro 0xD */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_CIDR0;

/*  CIDR1 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED318 : 24;               /*31:8 SW=ro HW=ro 0x0 */
            uint32_t CLASS : 4;               /*7:4 SW=ro HW=ro 0xF */
            uint32_t PRMBL1 : 4;               /*3:0 SW=ro HW=ro 0x0 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PRMBL1 : 4;               /*0:3 SW=ro HW=ro 0x0 */
            uint32_t CLASS : 4;               /*4:7 SW=ro HW=ro 0xF */
            uint32_t RESERVED318 : 24;               /*8:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_CIDR1;

/*  CIDR2 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED314 : 28;               /*31:4 SW=ro HW=ro 0x0 */
            uint32_t PRMBL2 : 4;               /*3:0 SW=ro HW=ro 0x5 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PRMBL2 : 4;               /*0:3 SW=ro HW=ro 0x5 */
            uint32_t RESERVED314 : 28;               /*4:31 SW=ro HW=ro 0x0 */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_CIDR2;

/*  CIDR3 DESCRIPTION :description */
typedef union {
    #ifdef IDS_BIG_ENDIAN
        struct {
            uint32_t RESERVED314 : 28;               /*31:4 SW=ro HW=ro 0xB */
            uint32_t PRMBL3 : 4;               /*3:0 SW=ro HW=ro 0x1 */
        } bf;
        
    #else     /* IDS_LITTLE_ENDIAN */
        struct {
            uint32_t PRMBL3 : 4;               /*0:3 SW=ro HW=ro 0x1 */
            uint32_t RESERVED314 : 28;               /*4:31 SW=ro HW=ro 0xB */
        } bf;
        
    #endif
    uint32_t  dw;
    
    
}sie200ahb5memprot_CIDR3;

typedef volatile struct inph_mpc_base {
    sie200ahb5memprot_CTRL  CTRL;
    
    uint8_t filler1[0xC];
    
    sie200ahb5memprot_BLKMAX  BLKMAX;
    sie200ahb5memprot_BLKCFG  BLKCFG;
    sie200ahb5memprot_BLKIDX  BLKIDX;
    sie200ahb5memprot_BLKLUT  BLKLUT;
    sie200ahb5memprot_INTSTAT  INTSTAT;
    sie200ahb5memprot_INTCLEAR  INTCLEAR;
    sie200ahb5memprot_INTEN  INTEN;
    sie200ahb5memprot_INTINFO1  INTINFO1;
    sie200ahb5memprot_INTINFO2  INTINFO2;
    sie200ahb5memprot_INTSET  INTSET;
    
    uint8_t filler11[0xF98];
    
    sie200ahb5memprot_PIDR4  PIDR4;
    sie200ahb5memprot_PIDR5  PIDR5;
    sie200ahb5memprot_PIDR6  PIDR6;
    sie200ahb5memprot_PIDR7  PIDR7;
    sie200ahb5memprot_PIDR0  PIDR0;
    sie200ahb5memprot_PIDR1  PIDR1;
    sie200ahb5memprot_PIDR2  PIDR2;
    sie200ahb5memprot_PIDR3  PIDR3;
    sie200ahb5memprot_CIDR0  CIDR0;
    sie200ahb5memprot_CIDR1  CIDR1;
    sie200ahb5memprot_CIDR2  CIDR2;
    sie200ahb5memprot_CIDR3  CIDR3;
    
    
} inph_mpc_base_t;


#endif /* __INPH_MPC_REGISTERS_H */


