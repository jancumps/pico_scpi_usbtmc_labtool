#ifndef _PWM_UTILS_H
#define _PWM_UTILS_H


uint32_t pwmPinCount();
void initPwmPins();
void setOutPinAt(uint32_t index, uint32_t value);

#endif // _PWM_UTILS_H