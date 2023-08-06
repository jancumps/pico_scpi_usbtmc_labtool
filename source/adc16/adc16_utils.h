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

/******* functions *********/
void initAdc16I2C(void);
void initAdc16Reg(void);
uint16_t readAdc16Meas(void);

#endif // _ADC16_UTILS_H