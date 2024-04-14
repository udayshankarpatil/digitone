#include "transformation.h"
#include "biquad.h"
#include <stdlib.h>
#include "mapper.h"




Tone tone;

void initFilter();
void applyFilter(float32_t *src, float32_t *dst, int size);
uint16_t resonate(float32_t *buffer, Tone *toneState);
uint16_t generate(float32_t *buffer, Tone *toneState);



//---------------------------------------------------------------



void initTransformation() {
  initFilter();
}

float32_t result[HALF_BUFFER_SIZE];
#define SCALE 1

uint16_t  applyDSP(float32_t *buffer, Key *keyState) {
  mapToTone(keyState, &tone);
  return generate(buffer, &tone);
}


//---------------------------------------------------------------
// Keys Tone mapping





//---------------------------------------------------------------
// Various processing options



uint16_t resonate(float32_t *buffer, Tone *toneState) {
  applyFilter(buffer, result, HALF_BUFFER_SIZE);
  arm_scale_f32(result, SCALE, buffer, HALF_BUFFER_SIZE);
  return 100;
}



//------------------



volatile float phase = 0;
const float twoPi = 2 * M_PI;

uint16_t generate(float32_t *buffer, Tone *toneState) {

  if (phase >= twoPi) {
    phase -= twoPi;
  }

  float phaseStep = twoPi * toneState->getFrequency() / SAMPLING_FREQUENCY;

  for (int t=0; t<HALF_BUFFER_SIZE; t++) {
    phase += phaseStep;
    float s = sinf(phase);

    buffer[t] = s * (0.5 + s * (0.2 - s *0.1)) * toneState->getAmplitude();
  }

  return 0;
}



//---------------------------------------------------------------



#define BIQUAD_STAGES 1

float32_t biquadState[4 * BIQUAD_STAGES];
float32_t biquadCoefficients[5 * BIQUAD_STAGES];
arm_biquad_cascade_df2T_instance_f32 biquadInstance;



void initFilter() {
  float32_t Fc = 240;
  setBiquadCoefficients(biquadCoefficients, 0, Fc, LOW_PASS);
  arm_biquad_cascade_df2T_init_f32(&biquadInstance, BIQUAD_STAGES, biquadCoefficients, biquadState);
}


void applyFilter(float32_t *src, float32_t *dst, int size) {
  arm_biquad_cascade_df2T_f32(&biquadInstance, src, dst, size);
}
