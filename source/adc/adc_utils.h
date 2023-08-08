#ifndef _ADC_UTILS_H
#define _ADC_UTILS_H

void initAdcUtils();
uint32_t adcPinCount();
void initAdcPins();
uint16_t getAdcPinAt(uint32_t index);

#endif // _ADC_UTILS_H