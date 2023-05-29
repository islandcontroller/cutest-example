/*!****************************************************************************
 * @file
 * hw_layer.h
 *
 * @brief
 * Hardware Layer Stub
 *
 * @date  29.05.2023
 ******************************************************************************/

#ifndef HW_LAYER_H_
#define HW_LAYER_H_

/*- Header files -------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>


/*- Redirection of hardware functions to stub implementation -----------------*/
#define __get_MISA()              ulStub_CSRs_GetMisa()

#endif /* HW_LAYER_H_ */
