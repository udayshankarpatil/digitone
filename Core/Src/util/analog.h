/*
 * analog.h
 *
 *  Created on: Mar 5, 2024
 *      Author: udayshankar
 */

#ifndef INC_ANALOG_H_
#define INC_ANALOG_H_


#include "base.h"


#define ADC_BITS 16
#define DAC_BITS 12
#define ADC_AMPLITUDE (1 << (ADC_BITS - 1))
#define DAC_AMPLITUDE (1 << (DAC_BITS - 1))
#define DAC_MAX (2 * DAC_AMPLITUDE - 1)


void adcIn(uint32_t *inp1, uint32_t *inp2, uint32_t *stagger, float32_t *outWave);
void dacOut(float32_t *val, uint16_t delay, uint32_t *delayBuffer, uint32_t *out1, uint32_t *out2);


#endif /* INC_ANALOG_H_ */
