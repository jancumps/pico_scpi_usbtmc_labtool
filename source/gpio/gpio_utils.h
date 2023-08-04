#ifndef _GPIO_UTILS_H
#define _GPIO_UTILS_H


uint32_t outPinCount();
void initGpioUtils();
void initOutPins();
void setOutPinAt(uint32_t index, bool on);
bool isOutPinAt(uint32_t index);

// TODO gpio input pins

#endif // _GPIO_UTILS_H