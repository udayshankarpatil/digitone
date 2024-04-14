/*
 * Tone.h
 *
 *  Created on: Apr 11, 2024
 *      Author: udayshankar
 */

#ifndef SRC_UTIL_TONE_H_
#define SRC_UTIL_TONE_H_

#include "base.h"
#define BASE_FREQUENCY 440


class Tone {
public:
  Tone();
  virtual ~Tone();

  void update(float freq, float amp);

  inline float getFrequency() const {
    return frequency;
  }

  inline float getAmplitude() const {
    return amplitude;
  }

private:
  float32_t frequency;
  float32_t amplitude;
};

#endif /* SRC_UTIL_TONE_H_ */


