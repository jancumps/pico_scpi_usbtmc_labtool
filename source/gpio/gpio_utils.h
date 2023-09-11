#ifndef _GPIO_UTILS_H
#define _GPIO_UTILS_H

void initGpioUtils();

uint32_t outPinCount();

void initOutPins();
void setOutPinAt(uint32_t index, bool on);
bool isOutPinAt(uint32_t index);

uint32_t inPinCount();

void initInPins();
bool isInPinAt(uint32_t index);

#endif // _GPIO_UTILS_H