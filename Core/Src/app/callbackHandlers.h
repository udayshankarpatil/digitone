/*
 * callbackHandlers.h
 *
 *  Created on: Apr 10, 2024
 *      Author: udayshankar
 */

#ifndef INC_APP_CALLBACKHANDLERS_H_
#define INC_APP_CALLBACKHANDLERS_H_

#include "app.h"
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif //---------------------------------------------------------------



void adcHalfConverted(ADC_HandleTypeDef *hadc);
void adcFullConverted(ADC_HandleTypeDef *hadc);



#ifdef __cplusplus //---------------------------------------------------------------
}
#endif

#endif /* INC_APP_CALLBACKHANDLERS_H_ */
