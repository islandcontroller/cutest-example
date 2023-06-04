/*!****************************************************************************
 * @file
 * coreid.c
 *
 * @brief
 * RISC-V Core Identification
 *
 * @date  29.05.2023
 ******************************************************************************/

/*- Test environment ---------------------------------------------------------*/
#include <CuTest.h>
#include "lambda.h"


/*- Stubs --------------------------------------------------------------------*/
#include "Stub_CSRs.h"


/*- Unit-Under-Test ----------------------------------------------------------*/
#include "../../FW_RV32CoreIdent/coreid.c"


/*- Stub implementation for CoreID -------------------------------------------*/
#include "Stub_CoreId_Impl.inc"


/*- IsExtensionValid private function tests ----------------------------------*/
/*!****************************************************************************
 * @brief
 * Valid extension code "uppercase A"
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_IsExtensionValid_ValidA)
{
  const char cInput = 'A';
  const bool bExpected = true;

  bool bActual = bIsExtensionValid(cInput);

  CuAssertIntEquals(bExpected, bActual);
}

/*!****************************************************************************
 * @brief
 * Invalid extension code "lowercase E"
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_IsExtensionValid_InvalidLowercaseE)
{
  const char cInput = 'e';
  const bool bExpected = false;

  bool bActual = bIsExtensionValid(cInput);

  CuAssertIntEquals(bExpected, bActual);
}

/*! Test group definition for IsExtensionValid                                */
TEST_GROUP(TestCoreId_IsExtensionValid)
{
  TEST_CoreId_IsExtensionValid_ValidA,
  TEST_CoreId_IsExtensionValid_InvalidLowercaseE
};


/*- GetXlen exported function tests ------------------------------------------*/
/*!****************************************************************************
 * @brief
 * Valid encoding for "RV32"
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetXlen_Valid32)
{
  vStub_CSRs_Reset();
  vStub_CSRs_SetMisa(0x40000000u);

  const coreid_xlen eExpected = EN_COREID_XLEN_32b;

  coreid_xlen eActual = eCoreIdGetXlen();

  CuAssertIntEquals(eExpected, eActual);
}

/*!****************************************************************************
 * @brief
 * Invalid encoding
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetXlen_Invalid)
{
  vStub_CSRs_Reset();

  const coreid_xlen eExpected = EN_COREID_XLEN_Unknown;

  coreid_xlen eActual = eCoreIdGetXlen();

  CuAssertIntEquals(eExpected, eActual);
}

/*! Test group definition for GetXlen                                         */
TEST_GROUP(TestCoreId_GetXlen)
{
  TEST_CoreId_GetXlen_Valid32,
  TEST_CoreId_GetXlen_Invalid
};


/*- IsExtensionPresent exported function tests -------------------------------*/
/*!****************************************************************************
 * @brief
 * Implemented extension 'A'
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_IsExtensionPresent_PresentA)
{
  vStub_CSRs_Reset();
  vStub_CSRs_SetMisa(0x1u); // A

  const char cInput = 'A';
  const bool bExpected = true;

  bool bActual = bCoreIdIsExtensionPresent(cInput);

  CuAssertIntEquals(bExpected, bActual);
}

/*!****************************************************************************
 * @brief
 * Non-implemented extension 'E'
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_IsExtensionPresent_NotPresentE)
{
  vStub_CSRs_Reset();
  vStub_CSRs_SetMisa(0x1u); // A

  const char cInput = 'E';
  const bool bExpected = false;

  bool bActual = bCoreIdIsExtensionPresent(cInput);

  CuAssertIntEquals(bExpected, bActual);
}

/*!****************************************************************************
 * @brief
 * Invalid extension code
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_IsExtensionPresent_Invalid)
{
  vStub_CSRs_Reset();
  vStub_CSRs_SetMisa(0x1u); // A

  const char cInput = 'a';
  const bool bExpected = false;

  bool bActual = bCoreIdIsExtensionPresent(cInput);

  CuAssertIntEquals(bExpected, bActual);
}

/*! Test group definition for IsExtensionPresent                              */
TEST_GROUP(TestCoreId_IsExtensionPresent)
{
  TEST_CoreId_IsExtensionPresent_PresentA,
  TEST_CoreId_IsExtensionPresent_NotPresentE,
  TEST_CoreId_IsExtensionPresent_Invalid
};


/*- GetExtensionName exported function tests ---------------------------------*/
/*!****************************************************************************
 * @brief
 * Description for 'A' extension
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetExtensionName_Value)
{
  const char cInput = 'A';
  const char* pszExpected = "A - Atomic extension";

  const char* pszActual = pszCoreIdGetExtensionName(cInput);

  CuAssertStrEquals(pszExpected, pszActual);
}

/*!****************************************************************************
 * @brief
 * Description for reserved 'T' extension
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetExtensionName_Reserved)
{
  const char cInput = 'T';
  const char* pszExpected = "T - (reserved)";

  const char* pszActual = pszCoreIdGetExtensionName(cInput);

  CuAssertStrEquals(pszExpected, pszActual);
}

/*!****************************************************************************
 * @brief
 * Invalid extension code yields NULL pointer
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetExtensionName_Invalid)
{
  const char cInput = 'a';
  const char* pszExpected = NULL;

  const char* pszActual = pszCoreIdGetExtensionName(cInput);

  CuAssertPtrEquals(pszExpected, pszActual);
}

/*! Test group definition for GetExtensionName                                */
TEST_GROUP(TestCoreId_GetExtensionName)
{
  TEST_CoreId_GetExtensionName_Value,
  TEST_CoreId_GetExtensionName_Reserved,
  TEST_CoreId_GetExtensionName_Invalid
};


/*- GetPresentExtensions -----------------------------------------------------*/
static void vDummy(char cExt __attribute__((unused))) {}

/*!****************************************************************************
 * @brief
 * MISA is only accessed once
 *
 * @date  29.05.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetPresentExtensions_AccessCount)
{
  vStub_CSRs_Reset();

  const uint32_t ulExpected = 1u;

  vCoreIdGetPresentExtensions(vDummy);
  uint32_t ulActual = ulStub_CSRs_GetMisaAccessCount();

  CuAssertIntEquals(ulExpected, ulActual);
}

/*!****************************************************************************
 * @brief
 * First found extension is 'C'
 *
 * @date  04.06.2023
 ******************************************************************************/
TEST_CASE(TEST_CoreId_GetPresentExtensions_AccessValue)
{
  vStub_CSRs_Reset();
  vStub_CSRs_SetMisa(0x1u << 2);

  const char cExpected = 'C';

  bool bCalled = false;
  char cActual = '\0';
  BEGIN_LAMBDA_SECTION();
  vCoreIdGetPresentExtensions(LAMBDA((char cExt), void, {
    bCalled = true;
    cActual = cExt;
  }));
  END_LAMBDA_SECTION();

  CuAssert(bCalled, "Callback not called");
  CuAssertIntEquals(cExpected, cActual);
}

/*! Test group definition for GetPresentExtensions                            */
TEST_GROUP(TestCoreId_GetPresentExtensions)
{
  TEST_CoreId_GetPresentExtensions_AccessCount,
  TEST_CoreId_GetPresentExtensions_AccessValue
};


/*- Test module definition ---------------------------------------------------*/
TEST_MODULE(TestCoreId)
{
  TestCoreId_IsExtensionValid,
  TestCoreId_GetXlen,
  TestCoreId_IsExtensionPresent,
  TestCoreId_GetExtensionName,
  TestCoreId_GetPresentExtensions
};
