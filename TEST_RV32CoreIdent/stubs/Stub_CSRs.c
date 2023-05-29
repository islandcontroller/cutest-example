/*!****************************************************************************
 * @file
 * Stub_CSRs.c
 *
 * @brief
 * Hardware CSR Stub
 *
 * @date  29.05.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "Stub_CSRs.h"


/*- Private variables --------------------------------------------------------*/
/*! MISA register value                                                       */
static uint32_t ulMisaValue;

/*! Access counter                                                            */
static uint32_t ulMisaAccessCount;


/*- Access functions ---------------------------------------------------------*/
/*!****************************************************************************
 * @brief
 * Reset test environment
 *
 * @date  29.05.2023
 ******************************************************************************/
void vStub_CSRs_Reset(void)
{
  ulMisaValue = 0u; // invalid MXL encoding
  ulMisaAccessCount = 0u;
}

/*!****************************************************************************
 * @brief
 * Set MISA register value
 *
 * @param[in] ulValue     MISA Register value
 * @date  29.05.2023
 ******************************************************************************/
void vStub_CSRs_SetMisa(uint32_t ulValue)
{
  ulMisaValue = ulValue;
}

/*!****************************************************************************
 * @brief
 * Retrieve the number of times the MISA register was accessed since reset
 *
 * @return  (uint32_t)  Access count
 * @date  29.05.2023
 ******************************************************************************/
uint32_t ulStub_CSRs_GetMisaAccessCount(void)
{
  return ulMisaAccessCount;
}

/*!****************************************************************************
 * @brief
 * Retrieve MISA register value
 *
 * @note This function simulates a "csrr" read access to the MISA CSR.
 *
 * @return  (uint32_t)  Assigned MISA value
 * @date  29.05.2023
 ******************************************************************************/
uint32_t ulStub_CSRs_GetMisa(void)
{
  ++ulMisaAccessCount;
  return ulMisaValue;
}
