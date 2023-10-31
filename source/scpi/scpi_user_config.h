#ifndef _SCPI_USER_CONFIG_H
#define _SCPI_USER_CONFIG_H

// here you can override the SCPI lib default response terminator
/* set the termination character(s)   */
#ifndef SCPI_LINE_ENDING
#define LINE_ENDING_CR          "\r"    /*   use a <CR> carriage return as termination charcter */
#define LINE_ENDING_LF          "\n"    /*   use a <LF> line feed as termination charcter */
#define LINE_ENDING_CRLF        "\r\n"  /*   use <CR><LF> carriage return + line feed as termination charcters */
#define SCPI_LINE_ENDING        LINE_ENDING_CRLF
#endif

// define instrument specific registers
#define USE_CUSTOM_REGISTERS 1

#define USER_REGISTERS \
        USER_REG_DIGINEVENT, /* Digital In event status Register */ \
        USER_REG_DIGINEVENTE, /* Digital In event status enable Register */ \
        USER_REG_DIGINEVENTC, /* Digital In event status condition Register */ \
        USER_REG_DIGINEVENTP, /* Digital In event status positive filter Register */ \
        USER_REG_DIGINEVENTN, /* Digital In event status negative register Register */

#define USER_REGISTER_GROUPS \
        USER_REG_GROUP_DIGINEVENT,

#define USER_REGISTER_DETAILS \
    { SCPI_REG_CLASS_EVEN, USER_REG_GROUP_DIGINEVENT }, \
    { SCPI_REG_CLASS_ENAB, USER_REG_GROUP_DIGINEVENT }, \
    { SCPI_REG_CLASS_COND, USER_REG_GROUP_DIGINEVENT }, \
    { SCPI_REG_CLASS_PTR, USER_REG_GROUP_DIGINEVENT }, \
    { SCPI_REG_CLASS_NTR, USER_REG_GROUP_DIGINEVENT },

#define USER_REGISTER_GROUP_DETAILS \
{ \
        USER_REG_DIGINEVENT, \
        USER_REG_DIGINEVENTE, \
        USER_REG_DIGINEVENTC, \
	USER_REG_DIGINEVENTP, \
	USER_REG_DIGINEVENTN, \
	SCPI_REG_OPER, \
	1  /* this defines to what bit of the parent we trickle through */ \
    }, /* USER_REG_GROUP_DIGINEVENT */

#endif // _SCPI_USER_CONFIG_H
