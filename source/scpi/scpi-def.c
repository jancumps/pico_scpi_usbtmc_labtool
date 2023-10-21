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

#include "gpio_utils.h"
#include "adc_utils.h"
#include "i2c_utils.h"
#include "adc16_utils.h"
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

static scpi_result_t SCPI_DigitalInputQ(scpi_t * context) {
  int32_t numbers[1];

  // retrieve the output index
  SCPI_CommandNumbers(context, numbers, 1, 0);
  if (! ((numbers[0] > -1) && (numbers[0] < inPinCount()))) {
    SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
    return SCPI_RES_ERR;
  }

  SCPI_ResultBool(context, isInPinAt(numbers[0]));
  return SCPI_RES_OK;
}

static scpi_result_t SCPI_AnalogInputQ(scpi_t * context) {
  int32_t numbers[1];

  // retrieve the adc index
  SCPI_CommandNumbers(context, numbers, 1, 0);
  if (! ((numbers[0] > -1) && (numbers[0] < adcPinCount()))) {
    SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
    return SCPI_RES_ERR;
  }

  SCPI_ResultUInt16(context, getAdcPinAt(numbers[0]));
  return SCPI_RES_OK;
}

static scpi_result_t SCPI_Analog16InputQ(scpi_t * context) {
    int32_t numbers[1];

    // retrieve the adc index
    SCPI_CommandNumbers(context, numbers, 1, 0);
    if (! ((numbers[0] > -1) && (numbers[0] < adc16PinCount()))) {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
        return SCPI_RES_ERR;
    }

    SCPI_ResultUInt16(context, getAdc16PinAt(numbers[0]));
    return SCPI_RES_OK;
}

// PWM
static scpi_result_t SCPI_AnalogOutput(scpi_t * context) {
    int32_t param1;
    int32_t numbers[1];

    // retrieve the output index
    SCPI_CommandNumbers(context, numbers, 1, 0);
    if (! ((numbers[0] > -1) && (numbers[0] < pwmPinCount()))) {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
        return SCPI_RES_ERR;
    }

    /* read first parameter if present */
    if (!SCPI_ParamInt32(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }

    setPwmPinAt(numbers[0], param1);

    return SCPI_RES_OK;
}

static scpi_result_t SCPI_AnalogOutputQ(scpi_t * context) {
    int32_t numbers[1];

    // retrieve the pwm index
    SCPI_CommandNumbers(context, numbers, 1, 0);
    if (! ((numbers[0] > -1) && (numbers[0] < pwmPinCount()))) {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
        return SCPI_RES_ERR;
    }

    SCPI_ResultUInt16(context, getPwmPinAt(numbers[0]));
    return SCPI_RES_OK;
}





void triggerHandler() {
    // this function is the handler for SCPI and usbtmc trigger requests.
    // current firmware ignores triggers
    // if there is a use for it, move this to the dedicated module
    return;
}

/**
 * *TRG - This command asserts trigger. 
 *        https://www.ni.com/docs/en-US/bundle/labview-api-ref/page/functions/visa-assert-trigger.html
 *        throw SCPI error, because not implemented
 * @param context
 * @return 
 */
scpi_result_t SCPI_VisaTrg(scpi_t * context) {
    triggerHandler();
    SCPI_ErrorPush(context, SCPI_ERROR_UNDEFINED_HEADER); // TODO: remove when trigger implemented
    return SCPI_RES_ERR; // TODO: return OK when trigger implemented
}

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


    {.pattern = "STATus:OPERation:EVENt?", .callback = SCPI_StatusOperationEventQ,},
    {.pattern = "STATus:OPERation:CONDition?", .callback = SCPI_StatusOperationConditionQ,},
    {.pattern = "STATus:OPERation:ENABle", .callback = SCPI_StatusOperationEnable,},
    {.pattern = "STATus:OPERation:ENABle?", .callback = SCPI_StatusOperationEnableQ,},

    {.pattern = "STATus:QUEStionable[:EVENt]?", .callback = SCPI_StatusQuestionableEventQ,},
    /* {.pattern = "STATus:QUEStionable:CONDition?", .callback = scpi_stub_callback,}, */
    {.pattern = "STATus:QUEStionable:ENABle", .callback = SCPI_StatusQuestionableEnable,},
    {.pattern = "STATus:QUEStionable:ENABle?", .callback = SCPI_StatusQuestionableEnableQ,},

    {.pattern = "STATus:PRESet", .callback = SCPI_StatusPreset,},

    /* custom commands for the switch */
    {.pattern = "DIGItal:OUTPut#", .callback = SCPI_DigitalOutput,},
    {.pattern = "DIGItal:OUTPut#?", .callback = SCPI_DigitalOutputQ,},
    {.pattern = "DIGItal:INPut#?", .callback = SCPI_DigitalInputQ,},
    // adc commands
    {.pattern = "ANAlog:INPut#:RAW?", .callback = SCPI_AnalogInputQ,},
    {.pattern = "ANAlog:HIRES:INPut#:RAW?", .callback = SCPI_Analog16InputQ,},
    // pwm commands
    {.pattern = "ANAlog:OUTPut#:RAW", .callback = SCPI_AnalogOutput,},
    {.pattern = "ANAlog:OUTPut#:RAW?", .callback = SCPI_AnalogOutputQ,},

    // instrument specific registers commands
    INSTRUMENT_SPECIFIC_REGISTERS


    // VISA commands
    // support VISA ASSERT TRIGGER 
    // https://www.ni.com/docs/en-US/bundle/labview-api-ref/page/functions/visa-assert-trigger.html
    { .pattern = "*TRG", .callback = SCPI_VisaTrg,},

    SCPI_CMD_LIST_END
};

scpi_interface_t scpi_interface = {
    .error = NULL,            // haven't implemented an error logger
    .write = SCPI_Write,
    .control = SCPI_Control,
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

scpi_result_t SCPI_Control(scpi_t* context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val)
{
    (void)context;
    (void) val;

    if (SCPI_CTRL_SRQ == ctrl) {
        setControlReply();
    }
    return SCPI_RES_OK;
}

uint8_t getSTB() {
    return (uint8_t) SCPI_RegGet(&scpi_context, SCPI_REG_STB);
}

void setSTB(uint8_t stb) {
    SCPI_RegSet(&scpi_context, SCPI_REG_STB, (scpi_reg_val_t) stb);    
}

void doTrigger() {
    triggerHandler();
}

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
    SCPI_RegSet(&scpi_context, USER_REG_DIGINEVENTC, digi_in);
}

void maintainInstrumentRegs() {
  maintainDigiInReg();
}