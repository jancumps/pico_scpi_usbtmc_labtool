#ifndef _GPIO_UTILS_H
#define _GPIO_UTILS_H


uint32_t pinCount();
void initPins();
void setPinAt(uint32_t index, bool on);
bool isPinAt(uint32_t index);

#endif // _GPIO_UTILS_H