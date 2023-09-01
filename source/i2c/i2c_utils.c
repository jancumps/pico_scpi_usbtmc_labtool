#include "i2c_utils.h"

#include "hardware/gpio.h"
#include "hardware/i2c.h"

// initialize the I2C bus
void initI2CUtils() {
    i2c_init(i2c_default, 10000); // I2C0 on GPIO 4[SDA],5[SCL]
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN); // weak pull-ups but enable them anyway
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    return;
}