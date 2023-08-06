#include "adc16_utils.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"


/*
ADC16 uses the I2C bus to communicate with the ASD1115 chip.
The I2C bus is connected to the following pins:
SCL: GP5
SDA: GP4
*/

/************** global vars ***************/
uint8_t confreg[2]; // config register

/************** functions *****************/
// initialize the I2C bus
void initAdc16I2C(void) {
    i2c_init(i2c_default, 10000); // I2C0 on GPIO 4[SDA],5[SCL]
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN); // weak pull-ups but enable them anyway
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

// initialize the ADS1115 registers
void initAdc16Reg(void) {
    uint8_t buf[3];
    confreg[0] = 0x44; // MUX set to AIN0, and PGA set to +-2.048V and Continuous Conversion mode
    confreg[1] = 0x03; // rate = 8 SPS
    buf[0] = ADS1115_REG_CONFIG;
    buf[1] = confreg[0];
    buf[2] = confreg[1];
    i2c_write_blocking(i2c_default, ADS_ADDR, buf, 3, false);
}

// read the conversion register
uint16_t readAdc16Meas(void) {
    uint16_t buf;
    uint8_t* buf8_ptr = (uint8_t*)&buf;
    *buf8_ptr = ADS1115_REG_CONVERSION;
    i2c_write_blocking(i2c_default, ADS_ADDR, buf8_ptr, 1, true);
    i2c_read_blocking(i2c_default, ADS_ADDR, buf8_ptr, 2, false);
    return(buf);
}
