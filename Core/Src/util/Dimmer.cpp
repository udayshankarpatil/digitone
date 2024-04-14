/*
 * Dimmer.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: udayshankar
 */

#include "Dimmer.h"

Dimmer::Dimmer(Led_TypeDef l): led(l), currentLevel(0), targetLevel(0), ledOn(false) {}

Dimmer::~Dimmer() {
  // TODO Auto-generated destructor stub
}

void Dimmer::setLed(bool on) {
  if (on and !ledOn) {
    BSP_LED_On(led);
    ledOn = true;
  } else if (!on and ledOn) {
    BSP_LED_Off(led);
    ledOn = false;
  }
}

void Dimmer::setLevel(float level) {
  if (level < 0 || level > 1) {
    return;
  }
  targetLevel = level * level;
}

void Dimmer::refresh() {
  currentLevel -= targetLevel;
  if (ledOn) {
    currentLevel += 1;
  }
  setLed(targetLevel > currentLevel);
}
