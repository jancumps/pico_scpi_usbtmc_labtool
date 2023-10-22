#ifndef _REGISTERS_H
#define _REGISTERS_H

#include "scpi/scpi.h"

# define INSTRUMENT_SPECIFIC_REGISTERS \
    {.pattern = "STATus:OPERation:DIGItal:INPut:EVENt?", .callback = SCPI_StatusOperationDigitalInputEventQ,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:CONDition?", .callback = SCPI_StatusOperationDigitalInputConditionQ,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:ENABle", .callback = SCPI_StatusOperationDigitalInputEnable,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:ENABle?", .callback = SCPI_StatusOperationDigitalInputEnableQ,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:PTRansition", .callback = SCPI_StatusOperationDigitalInputPTransition,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:PTRansition?", .callback = SCPI_StatusOperationDigitalInputPTransitionQ,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:NTRansition", .callback = SCPI_StatusOperationDigitalInputNTransition,}, \
    {.pattern = "STATus:OPERation:DIGItal:INPut:NTRansition?", .callback = SCPI_StatusOperationDigitalInputNTransitionQ,},

scpi_result_t SCPI_StatusOperationDigitalInputEventQ(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputConditionQ(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputEnable(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputEnableQ(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputPTransition(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputPTransitionQ(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputNTransition(scpi_t * context);
scpi_result_t SCPI_StatusOperationDigitalInputNTransitionQ(scpi_t * context);

#endif // _REGISTERS_H