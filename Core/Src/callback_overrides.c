/*
 * callback_handlers.c
 *
 *  Created on: Aug 28, 2023
 *      Author: udayshankar
 */

#include "callbackHandlers.h"

// ADC --------------------------------------------------------

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
  adcHalfConverted(hadc);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  adcFullConverted(hadc);
}
