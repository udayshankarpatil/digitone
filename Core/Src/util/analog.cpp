/*
 * analog.c
 *
 *  Created on: Mar 5, 2024
 *      Author: udayshankar
 */

#include "analog.h"


float32_t fromADC(uint32_t v) {
  return (0.0f + v) / ADC_AMPLITUDE - 1;
}

uint32_t toDAC(float32_t f) {
  float32_t g = (f + 1) * DAC_AMPLITUDE;

  if (g <= 0) {
    return 0;
  } else if (g >= DAC_MAX) {
      return DAC_MAX;
  } else {
      return g;
  }
}

float32_t mapInput(uint32_t input1, uint32_t input2) {
  return fromADC(input1) - fromADC(input2);
}

void adcIn(uint32_t *inp1, uint32_t *inp2, uint32_t *stagger, float32_t *outWave) {

  for (int index=0; index<DIFF_DELAY; index++) {
    outWave[index] = mapInput(inp1[index], stagger[index]);
    stagger[index] = inp2[index + (HALF_BUFFER_SIZE - DIFF_DELAY)];
  }

  for (int index=DIFF_DELAY; index<HALF_BUFFER_SIZE; index++) {
    outWave[index]  = mapInput(inp1[index], inp2[index - DIFF_DELAY]);
  }
}

volatile int delayBufferPos = 0;

volatile uint32_t dynamicDelay = 0;

volatile int readIndex = 0;
volatile int writeIndex = 0;



void dacOut(float32_t *val, uint16_t delay, uint32_t *delayBuffer, uint32_t *out1, uint32_t *out2) {

  int rIndex = readIndex;
  int wIndex = writeIndex;
  for (int index=0; index<HALF_BUFFER_SIZE; index++) {
    if (delay > dynamicDelay) {
      wIndex++;
      dynamicDelay++;
    } else if (delay < dynamicDelay) {
      rIndex++;
      dynamicDelay--;
    } else {
      wIndex++;
      rIndex++;
    }

    out1[index] = out2[index] = delayBuffer[rIndex % DELAY_BUFFER_SIZE];
    delayBuffer[wIndex % DELAY_BUFFER_SIZE] = toDAC(val[index]);
  }
  readIndex = rIndex % DELAY_BUFFER_SIZE;
  writeIndex = wIndex % DELAY_BUFFER_SIZE;
}

