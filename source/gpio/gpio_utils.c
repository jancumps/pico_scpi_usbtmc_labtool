
#include "hardware/gpio.h"

#include "gpio_utils.h"

// supported pins
uint pins[] = {
    /*PICO_DEFAULT_LED_PIN, removed in this project, because the USBTMC code makes good use of it to show USB status
    if you want to use this pin, remove the led_blinking_task() */
    22, 14, 15};


uint32_t pinCount() {
    return sizeof(pins)/sizeof(pins[0]);
}

void initPins() {
    for (uint32_t i = 0; i < pinCount(); i++) {
        gpio_init(pins[i]);
        gpio_set_dir(pins[i], 1);
        gpio_put(pins[i], 0);
    }
}

void setPinAt(uint32_t index, bool on) {
    gpio_put(pins[index], on);
}

bool isPinAt(uint32_t index) {
    return gpio_get_out_level(pins[index]);
}

