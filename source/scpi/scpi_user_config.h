#ifndef _SCPI_USER_CONFIG_H
#define _SCPI_USER_CONFIG_H


// define instrument specific registers
#define USE_CUSTOM_REGISTERS 1

#define USER_REGISTERS \
        USER_REG_DIGINEVENT, /* Digital In event status Register */ \
        USER_REG_DIGINEVENTE, /* Digital In event status enable Register */

#define USER_REGISTER_GROUPS \
        USER_REG_GROUP_DIGINEVENT,

#define USER_REGISTER_DETAILS \
    { SCPI_REG_CLASS_EVEN, USER_REG_GROUP_DIGINEVENT }, \
    { SCPI_REG_CLASS_ENAB, USER_REG_GROUP_DIGINEVENT },

#define USER_REGISTER_GROUP_DETAILS \
{ \
        USER_REG_DIGINEVENT, \
        USER_REG_DIGINEVENTE, \
        SCPI_REG_NONE, \
        SCPI_REG_NONE, \
        SCPI_REG_NONE, \
        SCPI_REG_STB, \
        STB_OPS  /* TODO what value should I put here? */ \
    }, /* USER_REG_GROUP_DIGINEVENT */

#endif // _SCPI_USER_CONFIG_H
