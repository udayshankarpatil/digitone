/*
 * mapper.c
 *
 *  Created on: Mar 7, 2024
 *      Author: udayshankar
 */

#include "mapper.h"
#include "Tone.h"


float keyWeight[KEY_COUNT] = { 0.035, 0.09, 0.18 };

void mapToTone(Key *keyState, Tone *tone) {


  float down = 0;
  float amp = 0;
  for (int k=0; k<KEY_COUNT; k++) {
    down += keyState[k].down * keyWeight[k];
    amp += keyState[k].vel * keyState[k].vel / 10000;
  }

  float freq = 1.0/(1 + down);

  amp *= 0.001;
  tone->update(freq, amp);
}
