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

#include "gpio_utils.h"
#include "adc_utils.h"
#include "pwm_utils.h"

#include "usbtmc_app.h"

void initInstrument();

/**
 * Reimplement IEEE488.2 *TST?
 *
 * Result should be 0 if everything is ok
 * Result should be 1 if something goes wrong
 *
 * Return SCPI_RES_OK
 */
static scpi_result_t My_CoreTstQ(scpi_t * context) {

    SCPI_ResultInt32(context, 0);

    return SCPI_RES_OK;
}

static scpi_result_t SCPI_DigitalOutput(scpi_t * context) {
  scpi_bool_t param1;
  int32_t numbers[1];

  // retrieve the output index
  SCPI_CommandNumbers(context, numbers, 1, 0);
  if (! ((numbers[0] > -1) && (numbers[0] < outPinCount()))) {
    SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
    return SCPI_RES_ERR;
  }

  /* read first parameter if present */
  if (!SCPI_ParamBool(context, &param1, TRUE)) {
    return SCPI_RES_ERR;
  }

  setOutPinAt(numbers[0], param1 ? true : false);

  return SCPI_RES_OK;
}

static scpi_result_t SCPI_DigitalOutputQ(scpi_t * context) {
  int32_t numbers[1];

  // retrieve the output index
  SCPI_CommandNumbers(context, numbers, 1, 0);
  if (! ((numbers[0] > -1) && (numbers[0] < outPinCount()))) {
    SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
    return SCPI_RES_ERR;
  }

  SCPI_ResultBool(context, isOutPinAt(numbers[0]));
  return SCPI_RES_OK;
}

// TODO gpio in commands
// TODO adc commands
// TODO pwm in commands

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    { .pattern = "*CLS", .callback = SCPI_CoreCls,},
    { .pattern = "*ESE", .callback = SCPI_CoreEse,},
    { .pattern = "*ESE?", .callback = SCPI_CoreEseQ,},
    { .pattern = "*ESR?", .callback = SCPI_CoreEsrQ,},
    { .pattern = "*IDN?", .callback = SCPI_CoreIdnQ,},
    { .pattern = "*OPC", .callback = SCPI_CoreOpc,},
    { .pattern = "*OPC?", .callback = SCPI_CoreOpcQ,},
    { .pattern = "*RST", .callback = SCPI_CoreRst,},
    { .pattern = "*SRE", .callback = SCPI_CoreSre,},
    { .pattern = "*SRE?", .callback = SCPI_CoreSreQ,},
    { .pattern = "*STB?", .callback = SCPI_CoreStbQ,},
    { .pattern = "*TST?", .callback = My_CoreTstQ,},
    { .pattern = "*WAI", .callback = SCPI_CoreWai,},

    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {.pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,},
    {.pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,},
    {.pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,},

    /* custom commands for the switch */
    {.pattern = "DIGItal:OUTPut#", .callback = SCPI_DigitalOutput,},
    {.pattern = "DIGItal:OUTPut#?", .callback = SCPI_DigitalOutputQ,},
    // TODO gpio in commands
    // TODO adc commands
    // TODO pwm in commands
    SCPI_CMD_LIST_END
};

scpi_interface_t scpi_interface = {
    .error = NULL,            // haven't implemented an error logger
    .write = SCPI_Write,
    .control = NULL,        // haven't implemented communication channel control
    .flush = NULL,            // don't need flush for SCI / USB
    .reset = SCPI_Reset,
};

char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];

scpi_t scpi_context;


// init helper for this instrument
void scpi_instrument_init() {
    initInstrument(); // if you prefer no dependency on the gpio_utils in main,
              // you could move this call into the scpi_instrument_init() body.
              // like I did here
    
     SCPI_Init(&scpi_context,
             scpi_commands,
             &scpi_interface,
             scpi_units_def,
             SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
             scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
             scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

}

scpi_bool_t scpi_instrument_input(const char * data, int len) {
    return SCPI_Input(&scpi_context, data, len);
}

/*
 * The SCPI lib calls this function to write data back over the SCI2 interface
 * visual clue: dim user LED B after delivering the reply
 */
size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    (void) context;

  setReply(data, len);

    return len;
}

scpi_result_t SCPI_Reset(scpi_t * context) {
    (void) context;
    initInstrument();
    return SCPI_RES_OK;   
}

void initInstrument() {
    initOutPins();
    // TODO input pins
    initAdcPins();
    initPwmPins();
}