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
 * @file    inph_tzm_drv.c
 * @author  InnophaseIOT Firmware Team
 * @brief   TZM functions
 */

#include "inph_tzm_drv.h"
#include "platform_retarget.h"


enum inph_tzm_error_t inph_tzm_config(struct inph_tzm_dev_t* dev,
                                          uint8_t tzm,
                                          enum inph_tzm_sec_attr_t sec_attr)
{
    inph_security_cntrl_t* p_spctrl =
                     (inph_security_cntrl_t*)dev->spctrl_base;

    if (dev->state != INPH_TZM_INITIALIZED)
    {
        return INPH_TZM_ERROR;
    }

    if (sec_attr == INPH_TZM_SECURE_ONLY)
    {
        p_spctrl->NSMSC.dw &= ~(1 << tzm);
    }
    else
    {
        p_spctrl->NSMSC.dw |= (1 << tzm);
    }

    return INPH_TZM_ERR_NONE;
}

enum inph_tzm_error_t inph_tzm_irq_enable(struct inph_tzm_dev_t* dev,
                                          uint8_t tzm)
{
    inph_security_cntrl_t* p_spctrl =
                         (inph_security_cntrl_t*)dev->spctrl_base;

    if (dev->state != INPH_TZM_INITIALIZED)
    {
        return INPH_TZM_ERROR;
    }
    
    p_spctrl->SECMPCINTEN.dw |= (1 << tzm);

    return INPH_TZM_ERR_NONE;
}

void inph_tzm_irq_disable(struct inph_tzm_dev_t* dev, uint8_t tzm)
{
    inph_security_cntrl_t* p_spctrl =
                     (inph_security_cntrl_t*)dev->spctrl_base;    

    p_spctrl->SECMPCINTEN.dw &= ~(1 << tzm);
   
}

void inph_tzm_clear_irq(struct inph_tzm_dev_t* dev, uint8_t tzm)
{
    inph_security_cntrl_t* p_spctrl =
                     (inph_security_cntrl_t*)dev->spctrl_base;
    
    p_spctrl->SECMSCINTCLR.dw = (1 << tzm);
}


