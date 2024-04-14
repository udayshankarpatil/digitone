/*
 * biquad.h
 *
 *  Created on: Feb 20, 2024
 *      Author: udayshankar
 */

#ifndef INC_BIQUAD_H_
#define INC_BIQUAD_H_

#include "base.h"

typedef enum {
  LOW_PASS,
  HIGH_PASS,
  BAND_PASS,
  NOTCH,
  PEAK,
  LOW_SHELF,
  HIGH_SHELF
} FilterType;


void setBiquadCoefficients(float32_t *coefficients, int stage, float32_t Fc, FilterType type);


extern const float32_t Q0;

void calcBiquadLowpass(float32_t Fc, float32_t Q, float32_t *result);

void calcBiquadHighpass(float32_t Fc, float32_t Q, float32_t *result);

void calcBiquadBandpass(float32_t Fc, float32_t Q, float32_t *result);

void calcBiquadNotch(float32_t Fc, float32_t Q, float32_t *result);



#endif /* INC_BIQUAD_H_ */
