#ifndef _ADC_UTILS_H
#define _ADC_UTILS_H

#include "scpi/scpi.h"

#define INSTRUMENT_ANA_INP_COMMANDS \
    {.pattern = "ANAlog:INPut#:RAW?", .callback = SCPI_AnalogInputQ,},


void initAdcUtils();
uint32_t adcPinCount();
void initAdcPins();
uint16_t getAdcPinAt(uint32_t index);

scpi_result_t SCPI_AnalogInputQ(scpi_t * context);

#endif // _ADC_UTILS_H