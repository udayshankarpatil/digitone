/*
 * util.h
 *
 *  Created on: Dec 19, 2023
 *      Author: udayshankar
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

#include "base.h"
#include "stm32h7xx_nucleo.h"

uint32_t measureSignalStrength(uint32_t *buffer, int begin, int end);

float measureTimeInterval(unsigned int index);



#endif /* INC_UTIL_H_ */
