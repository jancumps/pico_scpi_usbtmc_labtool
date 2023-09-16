#ifndef _SCPI_USER_CONFIG_H
#define _SCPI_USER_CONFIG_H

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
		1  /* TODO this defines to what bit of the parent we trickle through */ \
    }, /* USER_REG_GROUP_DIGINEVENT */

#endif // _SCPI_USER_CONFIG_H
