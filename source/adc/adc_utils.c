#include "hardware/adc.h"

#include "adc_utils.h"

/*
ADC0	GP26
ADC1	GP27 // used for button on the pico-eurocard
ADC2	GP28
*/

// supported pins
uint adcPins[][2] = {
    {0,26}, 
    // {1,27}, // this is used for the button on the eurocard.
    {2,28}
};

void initAdcUtils() {
    adc_init();
}

uint32_t adcPinCount() {
    return sizeof(adcPins)/(sizeof(adcPins[0][0])+sizeof(adcPins[0][1]));
}

void initAdcPins() {
    for (uint32_t i = 0; i < adcPinCount(); i++) {
        adc_gpio_init(adcPins[i][1]); // the gpio pin is needed here
    }
}

uint16_t getAdcPinAt(uint32_t index) {
      adc_select_input(adcPins[index][0]); // the ADC pin number is needed here
      return adc_read();
}
