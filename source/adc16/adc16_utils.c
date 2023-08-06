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
uint8_t adc16Installed = 0;
uint32_t adc16Channel = 0;
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
    // is the ADC chip installed?
    buf[0] = ADS1115_REG_CONFIG;
    i2c_write_blocking(i2c_default, ADS_ADDR, buf, 1, false);
    i2c_read_blocking(i2c_default, ADS_ADDR, buf, 2, false);
    if (buf[0] != 0x85 || buf[1] != 0x83) {
        adc16Installed = 0; // no chip found
        return;
    } else {
        adc16Installed = 1; // chip found
    }
    // set config register to desired values
    confreg[0] = 0x44; // MUX set to AIN0, and PGA set to +-2.048V and continuous conversion mode
    confreg[1] = 0x43; // rate = 32 SPS
    buf[0] = ADS1115_REG_CONFIG;
    buf[1] = confreg[0];
    buf[2] = confreg[1];
    i2c_write_blocking(i2c_default, ADS_ADDR, buf, 3, false);
}

// set the multiplexer to the desired input
void setAdc16Mux(uint8_t mux) {
    uint8_t buf[3];
    confreg[0] &= ~0x70; // clear the MUX bits
    confreg[0] |= (mux<<4); // set the MUX bits
    buf[0] = ADS1115_REG_CONFIG;
    buf[1] = confreg[0];
    buf[2] = confreg[1];
    i2c_write_blocking(i2c_default, ADS_ADDR, buf, 3, false);
}

// start a conversion (this is only for single-shot mode)
// will delete this function if it's not needed
void startAdc16Conv(void) {
    uint8_t buf[3];
    buf[0] = ADS1115_REG_CONFIG;
    buf[1] = confreg[0] | 0x80; // set 'OS' bit to start a conversion
    buf[2] = confreg[1];
    i2c_write_blocking(i2c_default, ADS_ADDR, buf, 3, false);
}

// check if the conversion is complete (this may only work for single-shot mode)
// will delete this function if it's not needed
uint8_t adc16ConvDone(void) {
    uint8_t buf[3];
    buf[0] = ADS1115_REG_CONFIG;
    i2c_write_blocking(i2c_default, ADS_ADDR, buf, 1, false);
    i2c_read_blocking(i2c_default, ADS_ADDR, buf, 2, false);
    if (buf[0] & 0x80) {
        return 0; // conversion not done
    } else {
        return 1; // conversion done
    }
}

// read the conversion register
uint16_t readAdc16Meas(void) {
    uint16_t meas;
    uint16_t buf;
    uint8_t* buf8_ptr = (uint8_t*)&buf;
    *buf8_ptr = ADS1115_REG_CONVERSION;
    i2c_write_blocking(i2c_default, ADS_ADDR, buf8_ptr, 1, false);
    i2c_read_blocking(i2c_default, ADS_ADDR, buf8_ptr, 2, false);
    meas = buf>>8 | buf<<8; // swap bytes
    return(meas);
}

// provide a pin count. returns 0 if the ADS1115 is not installed
uint32_t adc16PinCount() {
    if (adc16Installed) {
        return(4);
    } else {
        return(0);
    }
}

// get ADC result from the ADS1115
uint16_t getAdc16PinAt(uint32_t index) {
    uint16_t res;
    if (adc16Channel == index) {
        // already set to this channel
    } else {
        // switch channel, and then wait for a conversion to be done
        adc16Channel = index;
        setAdc16Mux(ADS1115_CH0 + index);
        // no need to start conversion, since we are in continuous conversion mode
        sleep_ms(150); // wait for conversion to complete
    }
    res = readAdc16Meas();
    // no need to start another conversion, since we are in continuous conversion mode
    return(res);
}
