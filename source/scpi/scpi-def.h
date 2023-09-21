#ifndef __SCPI_DEF_H_
#define __SCPI_DEF_H_

#include "scpi/scpi.h"

#define SCPI_INPUT_BUFFER_LENGTH 256
#define SCPI_ERROR_QUEUE_SIZE 17


// manufacturer
#define SCPI_IDN1 "PICO-PI"
// model
#define SCPI_IDN2 "LABTOOL"
// serial number
#define SCPI_IDN3 NULL
// version
#define SCPI_IDN4 "01.00"

extern const scpi_command_t scpi_commands[];
extern scpi_interface_t scpi_interface;
extern char scpi_input_buffer[];
extern scpi_error_t scpi_error_queue_data[];
extern scpi_t scpi_context;

void scpi_instrument_init();
scpi_bool_t scpi_instrument_input(const char * data, int len);
size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);

// helper functions to simplyfy integration of TinyUSB tmcusb and the scpi-lib
uint8_t getSTB();
void setSTB(uint8_t);


void maintainInstrumentRegs();

#endif /* __SCPI_DEF_H_ */

