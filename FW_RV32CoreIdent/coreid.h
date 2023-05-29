/*!****************************************************************************
 * @file
 * coreid.h
 *
 * @brief
 * RISC-V Core Identification
 *
 * @date  29.05.2023
 ******************************************************************************/

#ifndef COREID_H_
#define COREID_H_

/*- Header files  ------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>


/*- Type definitions ---------------------------------------------------------*/
/*! XLEN / Register width                                                     */
typedef enum
{
  EN_COREID_XLEN_32b,                 /*!< RV32                               */
  EN_COREID_XLEN_64b,                 /*!< RV64                               */
  EN_COREID_XLEN_128b,                /*!< RV128                              */
  EN_COREID_XLEN_Unknown              /*!< Invalid encoding                   */
} coreid_xlen;


/*- Exported functions -------------------------------------------------------*/
coreid_xlen eCoreIdGetXlen(void);
bool bCoreIdIsExtensionPresent(char cExt);
const char* pszCoreIdGetExtensionName(char cExt);
void vCoreIdGetPresentExtensions(void (*pfvExtensionCallback)(char cExt));

#endif /* COREID_H_ */
