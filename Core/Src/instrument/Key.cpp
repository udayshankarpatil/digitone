/*
 * Key.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: udayshankar
 */

#include "Key.h"


Key::Key() {
  // TODO Auto-generated constructor stub
}

Key::~Key() {
  // TODO Auto-generated destructor stub
}

void Key::updateSensorAmbient(uint32_t sensorValue) {
  posAmbient += sensorValue * 2;
  posAmbient /= 3;
  updateState();
}

void Key::updateSensor(uint32_t sensorValue) {
  pos = sensorValue;
}

void Key::updateState() {
  int32_t diff = pos - posAmbient;

  float prevDown = down;

  float range = posMax - posMin;
  if (range < 20000) {
    range = 20000;
  }

  float newDown = (diff - posMin) / range;
  down *= 0.9;
  down += 0.1 * newDown;

  vel *= 0.9;
  vel += 0.1 * (newDown - prevDown) * SAMPLING_FREQUENCY;

  posMax -= 1;
  if (posMax < diff) {
    posMax = diff;
  }

  posMin += 1;
  if (posMin > diff) {
    posMin = diff;
  }
}
