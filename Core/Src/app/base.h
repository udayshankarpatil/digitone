/*
 * base.h
 *
 *  Created on: Feb 12, 2024
 *      Author: udayshankar
 */

#ifndef INC_BASE_H_
#define INC_BASE_H_

#include "stm32h7xx_hal.h"
#include "cmsis.h"



#define SAMPLING_FREQUENCY 62500 // 62.5kHz  16uS




// Sound ------------------------------------------------



// min delay 2ms
// buffer delay = buffer size X 5us

#define HALF_BUFFER_SIZE 50
#define BUFFER_SIZE (2 * HALF_BUFFER_SIZE)
#define DIFF_DELAY 11
#define DELAY_BUFFER_SIZE 200

#define SENSOR_CHANNELS 10

typedef struct BUFFERS {
  uint32_t adc1[BUFFER_SIZE];
  uint32_t adc2[BUFFER_SIZE];
  uint32_t dac1[BUFFER_SIZE];
  uint32_t dac2[BUFFER_SIZE];
  uint32_t stagger[DIFF_DELAY];
  float32_t processing[HALF_BUFFER_SIZE];
  uint32_t delayBuffer[DELAY_BUFFER_SIZE];
  uint32_t sensor[SENSOR_CHANNELS * 2];
} BUF;



// Control ------------------------------------------------



#define KEY_COUNT 3



#endif /* INC_BASE_H_ */
