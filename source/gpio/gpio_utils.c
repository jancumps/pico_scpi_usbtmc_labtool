
#include "hardware/gpio.h"

#include "gpio_utils.h"

// supported pins
uint outPins[] = {
    /*PICO_DEFAULT_LED_PIN, removed in this project, because the USBTMC code makes good use of it to show USB status
    if you want to use this pin, remove the led_blinking_task() */
    22, 14, 15};


uint32_t outPinCount() {
    return sizeof(outPins)/sizeof(outPins[0]);
}

void initOutPins() {
    for (uint32_t i = 0; i < outPinCount(); i++) {
        gpio_init(outPins[i]);
        gpio_set_dir(outPins[i], 1);
        gpio_put(outPins[i], 0);
    }
}

void setOutPinAt(uint32_t index, bool on) {
    gpio_put(outPins[index], on);
}

bool isOutPinAt(uint32_t index) {
    return gpio_get_out_level(outPins[index]);
}

