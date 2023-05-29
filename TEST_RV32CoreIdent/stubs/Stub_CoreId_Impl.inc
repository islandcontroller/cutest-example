/*!****************************************************************************
 * @file
 * Stub_CoreId_Impl.inc
 *
 * @brief
 * Stub implementation for the "Core ID" unit under test
 *
 * This stub can be used for testing higher-level functionality, such as
 * modules accessing "Core ID" internally. Other use cases would include pre-
 * setting internal state machines for each test case.
 *
 * @note
 * This file needs to be included **inside the TEST_CoreId test module** and
 * **after the UUT include** in order to access private module members!
 *
 * @date  29.05.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include <string.h>
#include "Stub_CoreId.h"


/*- Access functions ---------------------------------------------------------*/
/*!****************************************************************************
 * @brief
 * Re-initialise "Core ID" private module members
 *
 * @date  29.05.2023
 ******************************************************************************/
void vStub_CoreID_Reset(void)
{
  // Private members and methods are accessible in this file
  memset(acExtensionNameBuffer, '\0', sizeof(acExtensionNameBuffer));
}

/*!****************************************************************************
 * @brief
 * Force-assign a value to a private module member
 *
 * @param[in] *pszStr     New buffer value
 * @date  29.05.2023
 ******************************************************************************/
void vStub_CoreID_SetExtensionNameBuffer(const char* pszStr)
{
  strcpy(acExtensionNameBuffer, pszStr);
}
