#ifndef _ADC16_UTILS_H
#define _ADC16_UTILS_H

/********** includes **********/
#include "pico/stdlib.h"

/******* defines *********************/
// ADS1115 ADDR pin set to 0V results in I2C address 0x48
#define ADS_ADDR 0x48
// ADS1115 registers (4)
#define ADS1115_REG_CONVERSION 0x00
#define ADS1115_REG_CONFIG 0x01
#define ADS1115_REG_LO_THRESH 0x02
#define ADS1115_REG_HI_THRESH 0x03
// ADS1115 mux values
#define ADS1115_CH0 0x04
#define ADS1115_CH1 0x05
#define ADS1115_CH2 0x06
#define ADS1115_CH3 0x07
#define ADS1115_DIFF_0_1 0x00
#define ADS1115_DIFF_2_3 0x11

/******* functions *********/
void initAdc16Reg(void);
uint32_t adc16PinCount();
uint16_t getAdc16PinAt(uint32_t index);

#endif // _ADC16_UTILS_H