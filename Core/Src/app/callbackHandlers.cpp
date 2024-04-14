/*
 * callbackHandlers.cpp
 *
 *  Created on: Apr 10, 2024
 *      Author: udayshankar
 */

#include "callbackHandlers.h"



void adcHalfConverted(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1) {
    processAudio(FIRST_HALF);
    measureTimeInterval(0);
  }
  else if (hadc->Instance == ADC3) {
    processSensors();
    measureTimeInterval(2);
  }
}

void adcFullConverted(ADC_HandleTypeDef *hadc)
{
  if (hadc->Instance == ADC1) {
    processAudio(SECOND_HALF);
    measureTimeInterval(1);
  }
  else if (hadc->Instance == ADC3) {
    measureTimeInterval(3);
  }
}
