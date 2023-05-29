/*- Header files -------------------------------------------------------------*/
#include <stdio.h>
#include <CuTest.h>


/*- Test modules -------------------------------------------------------------*/
EXTERN_TEST_MODULE(TestCoreId);


/*!****************************************************************************
 * @brief
 * Test Runner main entry point
 *
 * @return  (int)       Test run result
 * @retval  EXIT_SUCCESS  Test run successful
 * @retval  EXIT_FAILURE  Test run not successful
 * @date  08.05.2023
 ******************************************************************************/
int main(void)
{
  BEGIN_TEST_RUN();
  RUN_TEST_MODULE(TestCoreId);
  END_TEST_RUN();

  return GET_RUN_RESULT();
}
