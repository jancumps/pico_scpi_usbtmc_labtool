#ifndef __USBTMC_DEVICE_CUSTOM_H
#define __USBTMC_DEVICE_CUSTOM_H

#include "tusb.h"
#include "class/usbtmc/usbtmc.h"
#include "class/usbtmc/usbtmc_device.h"

#if (CFG_TUD_USBTMC_ENABLE_488)
bool tud_usbtmc_send_srq(void); 
#endif

#endif // __USBTMC_DEVICE_CUSTOM_H
