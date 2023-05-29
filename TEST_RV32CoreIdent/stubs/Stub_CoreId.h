/*!****************************************************************************
 * @file
 * Stub_CoreId.h
 *
 * @brief
 * Stub implementation for the "Core ID" unit under test
 *
 * This stub can be used for testing higher-level functionality, such as
 * modules accessing "Core ID" internally. Other use cases would include pre-
 * setting internal state machines for each test case.
 *
 * @date  29.05.2023
 ******************************************************************************/

#ifndef STUBS_STUB_COREID_H_
#define STUBS_STUB_COREID_H_

/*- Access functions ---------------------------------------------------------*/
void vStub_CoreID_Reset(void);
void vStub_CoreID_SetExtensionNameBuffer(const char* pszStr);

#endif /* STUBS_STUB_COREID_H_ */
