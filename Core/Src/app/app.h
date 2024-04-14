/*
 * app.h
 *
 *  Created on: Mar 5, 2024
 *      Author: udayshankar
 */

#ifndef INC_APP_APP_H_
#define INC_APP_APP_H_

#include "base.h"


#ifdef __cplusplus
extern "C" {
#endif //---------------------------------------------------------------



void initApp();
typedef enum { FIRST_HALF=0, SECOND_HALF=1 } BufferSection;
void processAudio(BufferSection section);
void processSensors();



#ifdef __cplusplus  //---------------------------------------------------------------
}
#endif

#endif /* INC_APP_APP_H_ */
