/*!****************************************************************************
 * @file
 * coreid.c
 *
 * @brief
 * RISC-V Core Identification
 *
 * @date  29.05.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include <string.h>
#include "hw_layer.h"
#include "coreid.h"


/*- Macros -------------------------------------------------------------------*/
/*! Range macro for ISA-Extension name LUT                                    */
#define EXT_NAMES_LUT_LEN           ((size_t)('Z' - 'A') + 1u)

/*! Maximum length of assembled extension name                                */
#define EXT_NAME_MAX_LEN            (64u)


/*- Private variables --------------------------------------------------------*/
/*! Lookup table for ISA-Extension names                                      */
static const char* const apszExtensionNames[EXT_NAMES_LUT_LEN] = {
  "Atomic extension",
  "Bit-Manipulation extension",
  "Compressed extension",
  "Double-precision floating-point extension",
  "RV32E base ISA",
  "Single-precision floating-point extension",
  "Additional standard extensions present",
  "Hypervisor extension",
  "RV32I/RV64I/RV128I base ISA",
  NULL,
  NULL,
  NULL,
  "Integer Multiply/Divide extension",
  "User-level interrupts supported",
  NULL,
  NULL,
  "Quad-precision floating-point extension",
  NULL,
  "Supervisor mode implemented",
  NULL,
  "User mode implemented",
  "Vector extension",
  NULL,
  "Non-standard extensions present",
  NULL,
  NULL
};

/*! Buffer for assembled extension name                                       */
static char acExtensionNameBuffer[EXT_NAME_MAX_LEN];


/*- Function prototypes ------------------------------------------------------*/
static bool bIsExtensionValid(char cExt);


/*- Private functions --------------------------------------------------------*/
/*!****************************************************************************
 * @brief
 * Check, if the entered char is assigned to an ISA extension
 *
 * @param[in] cExt        Extension
 * @return  (bool)      true, if the char marks a valid ISA extension
 * @date  29.05.2023
 ******************************************************************************/
static bool bIsExtensionValid(char cExt)
{
  return (cExt >= 'A') && (cExt <= 'Z');
}


/*- Exported functions -------------------------------------------------------*/
/*!****************************************************************************
 * @brief
 * Read the core XLEN from the MISA CSR
 *
 * @return  (coreid_xlen) Register width
 * @retval  EN_COREID_XLEN_Unknown  Invalid encoding
 * @date  29.05.2023
 ******************************************************************************/
coreid_xlen eCoreIdGetXlen(void)
{
  register uint32_t ulMxl = (__get_MISA() >> 30) & 0x3u;
  switch (ulMxl)
  {
  case 0x1u:  return EN_COREID_XLEN_32b;
  case 0x2u:  return EN_COREID_XLEN_64b;
  case 0x3u:  return EN_COREID_XLEN_128b;
  default:    return EN_COREID_XLEN_Unknown;
  }
}

/*!****************************************************************************
 * @brief
 * Check, if the selected extension is present on the current core
 *
 * @param[in] cExt        Extension
 * @return  (bool)      Extension presence on the current core
 * @date  29.05.2023
 ******************************************************************************/
bool bCoreIdIsExtensionPresent(char cExt)
{
  if (bIsExtensionValid(cExt))
  {
    register uint32_t ulMisa = __get_MISA();
    return !!(ulMisa & (1u << (unsigned)(cExt - 'A')));
  }
  else return false;
}

/*!****************************************************************************
 * @brief
 * Get a string representation of the selected extension's name
 *
 * @note
 * The generated strings use a shared buffer. The buffer will be destroyed on
 * the next function call.
 *
 * @note
 * Unknown extensions are marked as "reserved". Invalid extensions will return
 * a NULL pointer.
 *
 * @param[in] cExt        Extension
 * @return  (const char*) Null-terminated string of the extension's name
 * @retval  NULL          Invalid extension
 * @date  29.05.2023
 ******************************************************************************/
const char* pszCoreIdGetExtensionName(char cExt)
{
  if (bIsExtensionValid(cExt))
  {
    const char* pszName = apszExtensionNames[(unsigned)(cExt - 'A')];
    if (pszName == NULL) pszName = "(reserved)";

    memset(acExtensionNameBuffer, 0, sizeof(acExtensionNameBuffer));
    acExtensionNameBuffer[0] = cExt;
    strcat(acExtensionNameBuffer, " - ");
    strcat(acExtensionNameBuffer, pszName);

    return acExtensionNameBuffer;
  }
  else return NULL;
}

/*!****************************************************************************
 * @brief
 * Iterate over all available/present extensions
 *
 * @param[in] pfvExtensionCallback Function, called for every present extension
 * @date  29.05.2023
 ******************************************************************************/
void vCoreIdGetPresentExtensions(void (*pfvExtensionCallback)(char cExt))
{
  if (pfvExtensionCallback == NULL) return;

  uint32_t ulMisa = __get_MISA();

  for (char c = 'A'; c <= 'Z'; ++c)
  {
    if (ulMisa & (1u << (c - 'A'))) pfvExtensionCallback(c);
  }
}
