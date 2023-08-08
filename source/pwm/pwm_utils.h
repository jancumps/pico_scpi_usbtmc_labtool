#ifndef _PWM_UTILS_H
#define _PWM_UTILS_H

void initPwmUtils();
uint32_t pwmPinCount();
void initPwmPins();
void setPwmPinAt(uint32_t index, uint32_t value);

#endif // _PWM_UTILS_H