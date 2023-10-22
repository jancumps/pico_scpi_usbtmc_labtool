#include "registers.h"
#include "scpi/scpi_base.h"

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

