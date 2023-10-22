#ifndef __SCPI_DEF_H_
#define __SCPI_DEF_H_

#include "scpi/scpi.h"


// manufacturer
#define SCPI_IDN1 "PICO-PI"
// model
#define SCPI_IDN2 "LABTOOL"
// serial number
#define SCPI_IDN3 NULL
// version
#define SCPI_IDN4 "01.00"

extern const scpi_command_t scpi_commands[];

void initInstrument();
void maintainInstrumentRegs();

#endif /* __SCPI_DEF_H_ */

