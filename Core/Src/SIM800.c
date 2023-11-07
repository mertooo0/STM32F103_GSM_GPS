#include <stdlib.h>
#include<SIM800.h>
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdbool.h"

extern UART_HandleTypeDef huart1;
//extern UART_HandleTypeDef huart2;
//------Variables----------

extern char RxBuffer[25];

//-------------------------
//-------COMMANDS---------

char Command1[5]="AT\r\n",
	 Command2[]="AT+CPIN?\r\n",
	 Command3[]="AT+CREG?\r\n",
	 Command4[]="AT+CGATT?\r\n",
	 Command5[]="AT+CIPSHUT\r\n",
	 Command6[]="AT+CIPSTATUS\r\n",
	 Command7[]="AT+CIPMUX=0\r\n",
	 Command8[]="AT+CSTT=\"internet\"\r\n",
	 Command9[]="AT+CIICR\r\n",
	 Command10[]="AT+CIFSR\r\n",
	 Command11[]="AT+CIPSPRT=0\r\n",
	 Command12[]="AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\r\n",
	 Command13[]="AT+CIPSEND\r\n",
	 Command14[]="GET https://api.thingspeak.com/update?api_key=I7HHP47YNWI8PSM8&field1=25\r\n",
	 Command15[]="\032\r\n",
	 Command16[]="AT+CIPSHUT\r\n"
;
//------------------------

uint8_t test()
{
	uint8_t ans=0;
	memset(RxBuffer,0,sizeof(RxBuffer)*strlen(RxBuffer)); //yanlış nedir ?

	HAL_UART_Transmit(&huart1,(uint8_t*)Command1,strlen(Command1),100);//!!HUART1 TX VERİ GÖNDERMİYOR
	//HAL_UART_Receive(&huart1,(uint8_t*)RxBuffer,6, 1000);
	ans=Check_OK();
	return ans;
}


uint8_t test2()
{
	uint8_t ans=0;
	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));
	HAL_UART_Transmit(&huart1,(uint8_t*)Command15,strlen(Command15),100);
	ans=Check_OK();
	return ans;
}


void SIM800_Init()//HER BİR KOMUT İÇİN KONTROL MEKANİZMASI EKLENECEK
{

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSHUT --
	HAL_UART_Transmit(&huart1,(uint8_t*)Command5,strlen(Command5),1000);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT -- iletişim var
	HAL_UART_Transmit(&huart1,(uint8_t*)Command1,strlen(Command1),100);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CPIN? -- ready ise pin kodu istemiyor
	HAL_UART_Transmit(&huart1,(uint8_t*)Command2,strlen(Command2),100);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CREG? --Ağ kayıtlı mı
	HAL_UART_Transmit(&huart1,(uint8_t*)Command3,strlen(Command3),100);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CGATT? --internet bağlası (GPRS) var mı yok mu?
	HAL_UART_Transmit(&huart1,(uint8_t*)Command4,strlen(Command4),1000);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSHUT --
	HAL_UART_Transmit(&huart1,(uint8_t*)Command5,strlen(Command5),1000);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSTATUS
	HAL_UART_Transmit(&huart1,(uint8_t*)Command6,strlen(Command6),1000);
	HAL_Delay(750);


	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPMUX=0 --çoklu bağlantı modu devre dışı
	HAL_UART_Transmit(&huart1,(uint8_t*)Command7,strlen(Command7),100);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CSTT=\"internet\" -- vodafone apn ayarı
	HAL_UART_Transmit(&huart1,(uint8_t*)Command8,strlen(Command8),1000);
	HAL_Delay(750);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIICR -- GPRS Bağlantısı kurulmaya çalışılır.Başaralı bir şekilde kurulduğunda modül IP adresi alır.
	HAL_UART_Transmit(&huart1,(uint8_t*)Command9,strlen(Command9),1000);
	HAL_Delay(750);




}


void SIM800l_Send_Data(int val)
{

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIFSR --
	HAL_UART_Transmit(&huart1,(uint8_t*)Command10,strlen(Command10),1000);
	HAL_Delay(1000);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSPRT=0 --Seri port iletişimini devre dışı bırakır.Cihaz yalnızca AT komutları ile yönlendirilir.
	HAL_UART_Transmit(&huart1,(uint8_t*)Command11,strlen(Command11),1000);
	HAL_Delay(1000);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\r\n
	HAL_UART_Transmit(&huart1,(uint8_t*)Command12,strlen(Command12),1000);
	HAL_Delay(1500);//

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSEND
	HAL_UART_Transmit(&huart1,(uint8_t*)Command13,strlen(Command13),1000);
	HAL_Delay(1500);

	char buffer[120];
	sprintf(buffer,"GET https://api.thingspeak.com/update?api_key=I7HHP47YNWI8PSM8&field1=%d\r\n",val);


	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//
	HAL_UART_Transmit(&huart1,(uint8_t*)buffer,strlen(buffer),1000);
	HAL_Delay(1500);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//
	HAL_UART_Transmit(&huart1,(uint8_t*)Command15,strlen(Command15),1000);
	HAL_Delay(1500);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//
	HAL_UART_Transmit(&huart1,(uint8_t*)Command16,strlen(Command16),1000);
	HAL_Delay(750);

}

void test4()
{



	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\r\n
	HAL_UART_Transmit(&huart1,(uint8_t*)Command12,strlen(Command12),1000);
	HAL_Delay(1500);//

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//AT+CIPSEND
	HAL_UART_Transmit(&huart1,(uint8_t*)Command13,strlen(Command13),1000);
	HAL_Delay(1500);

	char buffer[120];
	sprintf(buffer,"GET https://api.thingspeak.com/update?api_key=I7HHP47YNWI8PSM8&field1=%d\r\n",59);


	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//
	HAL_UART_Transmit(&huart1,(uint8_t*)buffer,strlen(buffer),1000);
	HAL_Delay(1500);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//
	HAL_UART_Transmit(&huart1,(uint8_t*)Command15,strlen(Command15),1000);
	HAL_Delay(1500);

	memset(RxBuffer,0,sizeof(char)*strlen(RxBuffer));//
	HAL_UART_Transmit(&huart1,(uint8_t*)Command16,strlen(Command16),1000);
	HAL_Delay(750);
}
/*
void reset_array()
{
	for(int i=0;i<25;i++)
	{
		RxBuffer[i]='0';
	}
}*/

uint8_t Check_OK()
{
	uint8_t ans=3;

	for(int i=0;i<strlen(RxBuffer);i++)
	{
		if(RxBuffer[i]=='O')//Check OK
		{

			if(RxBuffer[i+1]=='K')
			{
				ans=1;
			}

		}

		if(RxBuffer[i]=='E')//Check ERROR
		{
			if(RxBuffer[i+1]=='R')
			{
				if(RxBuffer[i+2]=='R')
				{
					if(RxBuffer[i+3]=='O')
					{
						if(RxBuffer[i+4]=='R')
						{
							ans=2;
						}
					}
				}
			}
		}


		if(RxBuffer[i]=='R')//Check ERROR
		{
			if(RxBuffer[i+1]=='E')
			{
				if(RxBuffer[i+2]=='A')
				{
					if(RxBuffer[i+3]=='D')
					{
						if(RxBuffer[i+4]=='Y')
						{
							ans=2;
						}
					}
				}
			}
		}
	}

	return ans;

}
