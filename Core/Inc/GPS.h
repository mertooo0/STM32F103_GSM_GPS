/*
 * GPS.h
 *
 *  Created on: Sep 4, 2023
 *      Author: CASPER
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include <string.h>
#include <stdio.h>
#include <main.h>
#include "stm32f1xx_hal.h"
#include "stdbool.h"
//Prototype

void Get_GGA();
void Get_RMC();
void Set_Time();
void Set_Location();
void Reorder_data(uint16_t sp,uint8_t s_case);
uint16_t Sp_finder(uint8_t s_case);

#endif /* INC_GPS_H_ */
