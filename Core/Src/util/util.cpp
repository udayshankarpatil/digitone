/*
 * util.c
 *
 *  Created on: Dec 19, 2023
 *      Author: udayshankar
 */


#include "util.h"

//------------------------------------------------------------------


uint32_t measureSignalStrength(uint32_t *buffer, int begin, int end) {
  uint32_t min = UINT32_MAX;
  uint32_t max = 0;

  for (int index=begin; index<end; index++) {
    uint32_t val = buffer[index];
    if (val < min) {
      min = val;
    }
    if (val > max) {
      max = val;
    }
  }
  return max - min;
}

//------------------------------------------------------------------


#define TICK_BATCH_SIZE 1000
#define MAX_INTERVAL_MEASUREMENTS 10

typedef struct {
  unsigned short tickCount;
  uint32_t tick;
  float tickInterval;
} IntervalMeasurement;

IntervalMeasurement intervalMeasurements[MAX_INTERVAL_MEASUREMENTS];

float measureTimeIntervalInternal(unsigned int index) {
  IntervalMeasurement *im = intervalMeasurements + index;
  im->tickCount++;

  if (im->tickCount >= TICK_BATCH_SIZE) {
    im->tickCount = 0;
    uint32_t now = HAL_GetTick();
    uint32_t interval = now - im->tick;
    im->tickInterval *= 9;
    im->tickInterval += interval;
    im->tickInterval /= 10;
    im->tick = now;
  }
  return im->tickInterval;
}

float measureTimeInterval(unsigned int index) {
//  return measureTimeIntervalInternal(index);
  return 0;
}
