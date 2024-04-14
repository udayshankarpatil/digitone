/*
 * app.c
 *
 *  Created on: Mar 5, 2024
 *      Author: udayshankar
 */

#include "app.h"
#include "transformation.h"
#include "analog.h"
#include "Dimmer.h"
#include "Key.h"


#include "adc.h"
#include "dac.h"
#include "tim.h"



BUF buff;
Key keys[KEY_COUNT];
Dimmer dimmerGreen(LED_GREEN);
Dimmer dimmerYellow(LED_YELLOW);

void initApp() {
  initTransformation();
  HAL_ADC_Start_DMA(&hadc1, buff.adc1, BUFFER_SIZE);
  HAL_ADC_Start_DMA(&hadc2, buff.adc2, BUFFER_SIZE);
  HAL_ADC_Start_DMA(&hadc3, buff.sensor, SENSOR_CHANNELS * 2);
  HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, buff.dac1, BUFFER_SIZE, DAC_ALIGN_12B_R);
  HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, buff.dac2, BUFFER_SIZE, DAC_ALIGN_12B_R);
  HAL_TIM_Base_Start(&htim6);
  HAL_TIM_Base_Start(&htim3);

  BSP_LED_Off(LED_RED);
  dimmerGreen.setLevel(0);
  dimmerYellow.setLevel(0);
}

// ----------------------------------------------------------------

void processAudio(BufferSection section) {
  int begin = section * HALF_BUFFER_SIZE;
  adcIn(buff.adc2 + begin, buff.adc1 + begin, buff.stagger, buff.processing);
  uint16_t delay = applyDSP(buff.processing, keys);
  dacOut(buff.processing, delay, buff.delayBuffer, buff.dac1 + begin, buff.dac2 + begin);
  dimmerGreen.refresh();
  dimmerYellow.refresh();
}

// ----------------------------------------------------------------

// fingers 1, 2 and 3
int keySensorMap[KEY_COUNT] = { 6, 9, 4 };


const float DIMMER_RES_RANGE = 1 << 12;
const int DIMMER_RES_MASK = DIMMER_RES_RANGE - 1;


bool lighted = false;

void processSensors() {
  for (int k=0; k<KEY_COUNT; k++) {
    Key *ks = keys + k;



    if (lighted) {
      ks->updateSensor(buff.sensor[keySensorMap[k]]);
      BSP_LED_Off(LED_RED);
      lighted = false;
    } else {
      ks->updateSensorAmbient(buff.sensor[keySensorMap[k]]);
      BSP_LED_On(LED_RED);
      lighted = true;
    }
  }
  dimmerGreen.setLevel(keys[0].getPos() / 100000.0);
  dimmerYellow.setLevel((keys[0].getPos() & DIMMER_RES_MASK) / DIMMER_RES_RANGE);
}
