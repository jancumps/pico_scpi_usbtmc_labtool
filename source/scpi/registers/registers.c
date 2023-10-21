#include "registers.h"

scpi_result_t SCPI_WriteReg(scpi_t * context, scpi_reg_name_t name) {
    int32_t new_OPERE;
    if (SCPI_ParamInt32(context, &new_OPERE, TRUE)) {
        SCPI_RegSet(context, name, (scpi_reg_val_t) new_OPERE);
    }
    return SCPI_RES_OK;
}

scpi_result_t SCPI_ReadReg(scpi_t * context, scpi_reg_name_t name) {
    /* return value */
    SCPI_ResultInt32(context, SCPI_RegGet(context, name));

    /* clear register */
    SCPI_RegSet(context, name, 0);

    return SCPI_RES_OK;
}

/**
 * STATus:OPERation:DIGItal:INPut:EVENt?
 * @param context
 * @return
 */
scpi_result_t SCPI_StatusOperationDigitalInputEventQ(scpi_t * context) {
    return SCPI_ReadReg(context, USER_REG_DIGINEVENT);
}

/**
 * STATus:OPERation:DIGItal:INPut:CONDition?
 * @param context
 * @return
 */
scpi_result_t SCPI_StatusOperationDigitalInputConditionQ(scpi_t * context) {
    return SCPI_ReadReg(context, USER_REG_DIGINEVENTC);
}

/**
 * STATus:OPERation:DIGItal:INPut:ENABle
 * @param context
 * @return
 */
scpi_result_t SCPI_StatusOperationDigitalInputEnable(scpi_t * context) {
    return SCPI_WriteReg(context, USER_REG_DIGINEVENTE);
}

/**
 * STATus:OPERation:DIGItal:INPut:ENABle?
 * @param context
 * @return
 */
 scpi_result_t SCPI_StatusOperationDigitalInputEnableQ(scpi_t * context) {
    return SCPI_ReadReg(context, USER_REG_DIGINEVENTE);
}

/**
 * STATus:OPERation:DIGItal:INPut:PTRansition
 * @param context
 * @return
 */
scpi_result_t SCPI_StatusOperationDigitalInputPTransition(scpi_t * context) {
    return SCPI_WriteReg(context, USER_REG_DIGINEVENTP);
}

/**
 * STATus:OPERation:DIGItal:INPut:PTRansition?
 * @param context
 * @return
 */
 scpi_result_t SCPI_StatusOperationDigitalInputPTransitionQ(scpi_t * context) {
    return SCPI_ReadReg(context, USER_REG_DIGINEVENTP);
}

/**
 * STATus:OPERation:DIGItal:INPut:NTRansition
 * @param context
 * @return
 */
scpi_result_t SCPI_StatusOperationDigitalInputNTransition(scpi_t * context) {
    return SCPI_WriteReg(context, USER_REG_DIGINEVENTN);
}

/**
 * STATus:OPERation:DIGItal:INPut:NTRansition?
 * @param context
 * @return
 */
 scpi_result_t SCPI_StatusOperationDigitalInputNTransitionQ(scpi_t * context) {
    return SCPI_ReadReg(context, USER_REG_DIGINEVENTN);
}

