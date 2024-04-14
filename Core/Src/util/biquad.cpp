/*
 * biquad.c
 *
 *  Created on: Feb 20, 2024
 *      Author: udayshankar
 */

#include "biquad.h"


void calcBiquad(FilterType type, float32_t fc, float32_t Q, float32_t peakGain, float32_t *result);

// Ref: Fs = 44.1 kHz, Fc = 100 Hz
// Act: Fs = 106 kHz, Fc = 240 Hz,
// BiQuad Coefficients - b0, b1, b2, a1, a2

const float32_t Q0 = 1.0 / sqrt(2);


float32_t lowpassCoefficients[5] = {
    0.00005024141818873903,
    0.00010048283637747806,
    0.00005024141818873903,
    1.979851353142371,
    -0.9800523188151258
};

float32_t highpassCoefficients[5] = {
    0.9899759179893742,
    -1.9799518359787485,
    0.9899759179893742,
    1.979851353142371,
    -0.9800523188151258
};


void setBiquadCoefficients(float32_t *coefficients, int stage, float32_t Fc, FilterType type) {
  float32_t *coef;
  switch (type) {
  case LOW_PASS:
    coef = lowpassCoefficients;
    break;
  case HIGH_PASS:
    coef = highpassCoefficients;
    break;
  default:
    return;
    break;
  }
  for (int index=0; index<5; index++) {
    coefficients[stage*5 + index] = coef[index];
  }
}


inline void calcBiquadLowpass(float32_t Fc, float32_t Q, float32_t *result) {
  calcBiquad(LOW_PASS, Fc / SAMPLING_FREQUENCY, Q, 1, result);
}


inline void calcBiquadHighpass(float32_t Fc, float32_t Q, float32_t *result) {
  calcBiquad(HIGH_PASS, Fc / SAMPLING_FREQUENCY, Q, 1, result);
}

inline void calcBiquadBandpass(float32_t Fc, float32_t Q, float32_t *result) {
  calcBiquad(BAND_PASS, Fc / SAMPLING_FREQUENCY, Q, 1, result);
}


inline void calcBiquadNotch(float32_t Fc, float32_t Q, float32_t *result) {
  calcBiquad(NOTCH, Fc / SAMPLING_FREQUENCY, Q, 1, result);
}

void calcBiquad(FilterType type, float32_t fc, float32_t Q, float32_t V, float32_t *result) {
  float32_t a0, a1, a2, b1, b2, norm;
  float32_t K = tan(M_PI * fc);

  float32_t K2 = K * K;
  float32_t KQ = K / Q;

  switch (type) {
  case LOW_PASS:
    norm = 1 / (1 + KQ + K2);
    a0 = K2 * norm;
    a1 = 2 * a0;
    a2 = a0;
    b1 = 2 * (K2 - 1) * norm;
    b2 = (1 - KQ + K2) * norm;
    break;
  case HIGH_PASS:
    norm = 1 / (1 + KQ + K2);
    a0 = 1 * norm;
    a1 = -2 * a0;
    a2 = a0;
    b1 = 2 * (K2 - 1) * norm;
    b2 = (1 - KQ + K2) * norm;
    break;
  case BAND_PASS:
    norm = 1 / (1 + KQ + K2);
    a0 = KQ * norm;
    a1 = 0;
    a2 = -a0;
    b1 = 2 * (K2 - 1) * norm;
    b2 = (1 - KQ + K2) * norm;
    break;
  case NOTCH:
    norm = 1 / (1 + KQ + K2);
    a0 = (1 + K2) * norm;
    a1 = 2 * (K2 - 1) * norm;
    a2 = a0;
    b1 = a1;
    b2 = (1 - KQ + K2) * norm;
    break;
  case PEAK:
    if (V >= 1) {
        norm = 1 / (1 + KQ + K2);
        a0 = (1 + V * KQ + K2) * norm;
        a1 = 2 * (K2 - 1) * norm;
        a2 = (1 - V * KQ + K2) * norm;
        b1 = a1;
        b2 = (1 - KQ + K2) * norm;
    }
    else {
        norm = 1 / (1 + V * KQ + K2);
        a0 = (1 + KQ + K2) * norm;
        a1 = 2 * (K2 - 1) * norm;
        a2 = (1 - KQ + K2) * norm;
        b1 = a1;
        b2 = (1 - V * KQ + K2) * norm;
    }
    break;
  case LOW_SHELF:
    if (V >= 1) {
        norm = 1 / (1 + sqrt(2) * K + K2);
        a0 = (1 + sqrt(2*V) * K + V * K2) * norm;
        a1 = 2 * (V * K2 - 1) * norm;
        a2 = (1 - sqrt(2*V) * K + V * K2) * norm;
        b1 = 2 * (K2 - 1) * norm;
        b2 = (1 - sqrt(2) * K + K2) * norm;
    }
    else {
        norm = 1 / (1 + sqrt(2*V) * K + V * K2);
        a0 = (1 + sqrt(2) * K + K2) * norm;
        a1 = 2 * (K2 - 1) * norm;
        a2 = (1 - sqrt(2) * K + K2) * norm;
        b1 = 2 * (V * K2 - 1) * norm;
        b2 = (1 - sqrt(2*V) * K + V * K2) * norm;
    }
    break;
  case HIGH_SHELF:
    if (V >= 1) {
        norm = 1 / (1 + sqrt(2) * K + K2);
        a0 = (V + sqrt(2*V) * K + K2) * norm;
        a1 = 2 * (K2 - V) * norm;
        a2 = (V - sqrt(2*V) * K + K2) * norm;
        b1 = 2 * (K2 - 1) * norm;
        b2 = (1 - sqrt(2) * K + K2) * norm;
    }
    else {
        norm = 1 / (V + sqrt(2*V) * K + K2);
        a0 = (1 + sqrt(2) * K + K2) * norm;
        a1 = 2 * (K2 - 1) * norm;
        a2 = (1 - sqrt(2) * K + K2) * norm;
        b1 = 2 * (K2 - V) * norm;
        b2 = (V - sqrt(2*V) * K + K2) * norm;
    }
    break;
  default:
    return;
    break;
  }

  result[0] = a0;
  result[1] = a1;
  result[2] = a2;
  result[3] = b1;
  result[4] = b2;
}



