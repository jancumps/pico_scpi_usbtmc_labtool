#include "hardware/i2c.h"

#include "i2c_utils.h"

void initI2CUtils() {
    i2c_init(i2c_default, 10000); // I2C0 on GPIO 4[SDA],5[SCL]
    return;
}