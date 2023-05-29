/*!****************************************************************************
 * @file
 * main.c
 *
 * @brief
 * Main program entry point
 *
 * @date  29.05.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "hw_layer.h"
#include "coreid.h"


/*- Global variables ---------------------------------------------------------*/
/* Access these variables using the debugger                                  */
volatile coreid_xlen eXlen;
volatile bool bRV32E;


/*!****************************************************************************
 * @brief
 * Main program entry point
 *
 * @date  29.05.2023
 ******************************************************************************/
int main(void)
{
  bRV32E = bCoreIdIsExtensionPresent('E');
  eXlen = eCoreIdGetXlen();

  while (1);
}
