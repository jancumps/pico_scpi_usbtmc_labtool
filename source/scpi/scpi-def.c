/*
 * Jan Cumps
 * 20230129
 * Raspberry Pico SCPI implementation based on the SCPI parser test example of Jan Breur
 *
 *
 */

 /**
 * @file   scpi-def.c
 * @date   Thu Nov 15 10:58:45 UTC 2012
 *
 * @brief  SCPI parser function definitions
 *
 *
 */


/*-
 * Copyright (c) 2012-2013 Jan Breuer,
 *
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi-def.h"

#include "registers/registers.h"
#include "scpi/scpi_base.h"

#include "gpio_utils.h"
#include "adc_utils.h"
#include "i2c_utils.h"
#include "adc16_utils.h"
#include "pwm_utils.h"

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    SCPI_BASE_COMMANDS

    /* custom commands for the switch */
    // gpio commands
    INSTRUMENT_DIGI_OUTP_COMMANDS
    INSTRUMENT_DIGI_INP_COMMANDS
    // adc commands
    INSTRUMENT_ANA_INP_COMMANDS
    INSTRUMENT_ANA_HIRES_INP_COMMANDS
    // pwm commands
    INSTRUMENT_ANA_OUTP_COMMANDS

    // instrument specific registers commands
    INSTRUMENT_SPECIFIC_REGISTERS

    SCPI_CMD_LIST_END
};

void initInstrument() {
    initGpioUtils();
    initOutPins();
    initInPins();
    initI2CUtils();
    initAdcUtils();
    initAdcPins();
    initAdc16Reg();
    initPwmUtils();
    initPwmPins();
}

/**
 * current implementation does not use interrupts to set the digital in control register
*/
void maintainDigiInReg() {
    scpi_reg_val_t digi_in = 0U;
    for (uint32_t i = 0; i < inPinCount(); i++) {
      int j = isInPinAt(i) << i;      
      digi_in |= j ;
    }
    SCPI_RegSet(getScpiContext(), USER_REG_DIGINEVENTC, digi_in);
}

void maintainInstrumentRegs() {
  maintainDigiInReg();
}