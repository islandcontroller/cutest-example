/*!****************************************************************************
 * @file
 * Stub_CSRs.h
 *
 * @brief
 * Hardware CSR Stub
 *
 * @date  29.05.2023
 ******************************************************************************/

#ifndef STUB_CSRS_H_
#define STUB_CSRS_H_

/*- Header files -------------------------------------------------------------*/
#include <stdint.h>


/*- Access functions ---------------------------------------------------------*/
void vStub_CSRs_Reset(void);
void vStub_CSRs_SetMisa(uint32_t ulValue);
uint32_t ulStub_CSRs_GetMisaAccessCount(void);

uint32_t ulStub_CSRs_GetMisa(void);

#endif /* STUB_CSRS_H_ */
