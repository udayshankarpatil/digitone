/*
 * transformation.h
 *
 *  Created on: Dec 19, 2023
 *      Author: udayshankar
 */

#ifndef INC_TRANSFORMATION_H_
#define INC_TRANSFORMATION_H_


#include "base.h"
#include "Key.h"



void initTransformation();
uint16_t  applyDSP(float32_t *buffer, Key *keys);



#endif /* INC_TRANSFORMATION_H_ */
