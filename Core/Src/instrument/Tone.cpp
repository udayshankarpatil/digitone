/*
 * Tone.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: udayshankar
 */

#include "Tone.h"

Tone::Tone() {
  // TODO Auto-generated constructor stub
}

Tone::~Tone() {
  // TODO Auto-generated destructor stub
}

const float DECAY = 0.004;

void Tone::update(float freq, float amp) {
  if (amp > 1) {
    amp = 1;
  }
  frequency = BASE_FREQUENCY * freq;
  amplitude *= (1.0 - DECAY);
  amplitude += amp * DECAY;
}
