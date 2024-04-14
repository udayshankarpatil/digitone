/*
 * Key.h
 *
 *  Created on: Apr 11, 2024
 *      Author: udayshankar
 */

#ifndef SRC_UTIL_KEY_H_
#define SRC_UTIL_KEY_H_

#include "Key.h"

#include "base.h"

class Key {
public:
  Key();
  virtual ~Key();

  float down;
  float vel;

  void updateSensorAmbient(uint32_t sensorValue);
  void updateSensor(uint32_t sensorValue);

  inline int32_t getPos() const {
    return pos;
  }

private:

  int32_t pos;
  int32_t posAmbient;

  int32_t posMax;
  int32_t posMin;

  void updateState();
};

#endif /* SRC_UTIL_KEY_H_ */
