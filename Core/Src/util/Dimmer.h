/*
 * Dimmer.h
 *
 *  Created on: Apr 11, 2024
 *      Author: udayshankar
 */

#ifndef SRC_DIMMER_H_
#define SRC_DIMMER_H_

#include "stm32h7xx_nucleo.h"




class Dimmer {
public:
  Dimmer(Led_TypeDef l);
  virtual ~Dimmer();
  void setLevel(float level);
  void refresh();

private:
  Led_TypeDef led;
  float currentLevel;
  float targetLevel;
  bool ledOn;
  void setLed(bool on);
};



#endif /* SRC_DIMMER_H_ */
