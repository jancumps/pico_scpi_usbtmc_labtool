#ifndef _PWM_UTILS_H
#define _PWM_UTILS_H

/********** includes **********/
#include "pico/stdlib.h"
#include "scpi/scpi.h"

/******* defines *********************/

#define INSTRUMENT_ANA_OUTP_COMMANDS \
    {.pattern = "ANAlog:OUTPut#:RAW", .callback = SCPI_AnalogOutput,}, \
    {.pattern = "ANAlog:OUTPut#:RAW?", .callback = SCPI_AnalogOutputQ,},

// frequency of PWM will be 125 MHz / (PWM_MAX * CKDIV)
// i.e. about 30.5 kHz for PWM_MAX = 4095
#define PWM_MAX 4095
// set CKDIV to 1 for approx 30.5 kHz PWM frequency if PWM_MAX is 4095
#define CKDIV 1
#define PWM_PIN0 16
#define PWM_PIN1 17
#define PWM_PIN2 18

/********* functions *********/
void initPwmUtils(); // configures the PWM feature
uint32_t pwmPinCount(); // returns the number of PWM pins (always 3)
void initPwmPins(); // sets up the pin mode to PWM
void setPwmPinAt(uint32_t index, uint32_t value); // sets the PWM pin index (0-3) PWM level to value (0-4095)
uint16_t getPwmPinAt(uint32_t index); // returns the PWM level for the pin index (0-3)

scpi_result_t SCPI_AnalogOutput(scpi_t * context);
scpi_result_t SCPI_AnalogOutputQ(scpi_t * context);

#endif // _PWM_UTILS_H