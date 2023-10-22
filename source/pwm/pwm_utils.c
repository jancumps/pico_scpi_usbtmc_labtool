/*  pwm_utils.c
 *  This function currently supports up to three pins, PWM_PIN0, PWM_PIN1, PWM_PIN2
 *  The PWM level can be set from 0 to 4095.
 *  The PWM frequency is approximately 30.517 kHz
*/


// ******** includes *****************
#include "hardware/pwm.h"
#include "pwm_utils.h"

// ********** global variables *********
uint slice_num[3]; // PWM slice value for each pin (two slices are used)
int pwm_level[3]; // PWM level for each pin

// *********** functions ***********

// pin_index is 0-2, and level is 0-4095
void
set_pwm_level(int pin_index, int level) {
    uint chan = 0;
    // The PWM module uses the concept of slices and channels.
    // For the three PWM pins, two slices are used. The mapping is:
    // PWM Pin index #:  0   1   2
    // Slice #:          0   0   1
    // Channel #:        0   1   0
    if (pin_index == 1) {
        chan = 1;
    }
    pwm_level[pin_index] = level;
    pwm_set_chan_level(slice_num[pin_index], chan, level); // set PWM value
}

void initPwmUtils() {
    return; // nothing to do
}

uint32_t pwmPinCount() {
    return(3); // The PWM pins are always enabled
}

void initPwmPins() {
    int i;
    // set the PWM pin functions
    gpio_set_function(PWM_PIN0, GPIO_FUNC_PWM);
    gpio_set_function(PWM_PIN1, GPIO_FUNC_PWM);
    gpio_set_function(PWM_PIN2, GPIO_FUNC_PWM);
    // store slice numbers. Each slice supports two pins (i.e. two channels)
    // The pins are ordered such that the slice numbers are 0, 0, 1 for pin indexes 0, 1, 2.
    slice_num[0] = pwm_gpio_to_slice_num(PWM_PIN0); // slice 0
    slice_num[1] =  slice_num[0]; // same slice as slice_num[0]
    slice_num[2] = pwm_gpio_to_slice_num(PWM_PIN2); // slice 1
    // PWM clock
    pwm_set_clkdiv(slice_num[0], CKDIV);
    pwm_set_clkdiv(slice_num[2], CKDIV);
    // the wrap value needs to be one less than the maximum value that will arrive via SCPI
    // the SDK documentation on the other hand seems to suggest it should be the maximum value,
    // but if you do that, then you can not reach 100.0% duty cycle.
    // we want 0 to be 0% duty cycle, and PWM_MAX (4095) to be 100% duty cycle.
    pwm_set_wrap(slice_num[0], PWM_MAX-1);
    pwm_set_wrap(slice_num[2], PWM_MAX-1);
    // default PWM levels set to zero
    for (i=0; i<3; i++) {
        set_pwm_level(i, 0);
    }
    // enable both PWM slices
    pwm_set_enabled(slice_num[0], true);
    pwm_set_enabled(slice_num[2], true);
}

void setPwmPinAt(uint32_t index, uint32_t value)  {
    // sanity check
    if (value > PWM_MAX) {
        value = PWM_MAX;
    } else if (value < 0) {
        value = 0;
    }
    set_pwm_level(index, value);
    return;
}

uint16_t getPwmPinAt(uint32_t index) {
    return(pwm_level[index]);
}

scpi_result_t SCPI_AnalogOutput(scpi_t * context) {
    int32_t param1;
    int32_t numbers[1];

    // retrieve the output index
    SCPI_CommandNumbers(context, numbers, 1, 0);
    if (! ((numbers[0] > -1) && (numbers[0] < pwmPinCount()))) {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
        return SCPI_RES_ERR;
    }

    /* read first parameter if present */
    if (!SCPI_ParamInt32(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }

    setPwmPinAt(numbers[0], param1);

    return SCPI_RES_OK;
}

scpi_result_t SCPI_AnalogOutputQ(scpi_t * context) {
    int32_t numbers[1];

    // retrieve the pwm index
    SCPI_CommandNumbers(context, numbers, 1, 0);
    if (! ((numbers[0] > -1) && (numbers[0] < pwmPinCount()))) {
        SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
        return SCPI_RES_ERR;
    }

    SCPI_ResultUInt16(context, getPwmPinAt(numbers[0]));
    return SCPI_RES_OK;
}
