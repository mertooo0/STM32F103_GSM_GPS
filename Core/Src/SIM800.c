#include <stdlib.h>
#include<SIM800.h>
#include "stm32f1xx_hal.h"
#include "string.h"

extern UART_HandleTypeDef huart1;
//extern UART_HandleTypeDef huart2;
//------Variables----------

extern char buffer22;

//-------------------------
//-------COMMANDS---------

char Command1[5]="AT\r\n",
	 Command2[]="AT+CPIN?",
	 Command3[]="AT+CREG?",
	 Command4[]="AT+CGATT?",
	 Command5[]="AT+CIPSHUT",
	 Command6[]="AT+CIPSTATUS",
	 Command7[]="AT+CIPMUX=0",
	 Command8[]="AT+CSTT=\"internet\"",
	 Command9[]="AT+CIICR",
	 Command10[]="AT+CIFSR",
	 Command11[]="AT+CIPSPRT=0",
	 Command12[]="AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"",
	 Command13[]="AT+CIPSEND",
	 Command14[]="GET https://api.thingspeak.com/update?api_key=I7HHP47YNWI8PSM8&field1=0",
	 Command15[]="AT+CIPSHUT"
;
//------------------------

void test()
{
	HAL_UART_Transmit(&huart1,(uint8_t*)Command1,strlen(Command1),100);//!!HUART1 TX VERİ GÖNDERMİYOR
	//HAL_UART_Receive(&huart1,(uint8_t*)buffer22,2, 100);

}
