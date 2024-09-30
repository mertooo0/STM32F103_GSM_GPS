/*
 * SIM800.h
 *
 *  Created on: Sep 17, 2023
 *      Author: merto
 */

#ifndef INC_SIM800_H_
#define INC_SIM800_H_


#include <stdlib.h>
#include<SIM800.h>
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdbool.h"




uint8_t test();
uint8_t test2();
uint8_t Check_OK();
void SIM800_Init();
void SIM800l_Send_Data(int val);





#endif /* INC_SIM800_H_ */

