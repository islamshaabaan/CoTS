/*
 * main.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Islam Shaaban
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MACROS.h"
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LED/LED_interface.h"
#include "HAL/SSD/SSD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#define F_CPU		8000000UL
#include <util/delay.h>
void TL_CountNSec(SSD_t* SSDPtr, u8 Copy_u8Number)
{
	for(s16 i=Copy_u8Number-1; i>=0; i--){
		SSD_voidEnable(SSDPtr,i);
		_delay_ms(1000);

	}
}

u8 Array[]= {
		0x0E,
		0x0A,
		0x0E,
		0x04,
		0x0E,
		0x15,
		0x0E,
		0x11
};

int main(void){
	/*
	LED_t TrafficLightLeds[3]={{ DIO_PORTC, DIO_PIN0, LED_ACTIVE_HIGH},
			{ DIO_PORTC, DIO_PIN1, LED_ACTIVE_HIGH},
			{ DIO_PORTC, DIO_PIN2, LED_ACTIVE_HIGH},
	};
	for(u8 i=0; i<3; i++){
		LED_voidInit(&TrafficLightLeds[i]);
	}

	SSD_t SSD1 = {DIO_PORTA, SSD_COMMON_CATHODE };
	SSD_voidInit(&SSD1);


	while(1){
		LED_voidON(&TrafficLightLeds[2]); // Green Led
		TL_CountNSec(&SSD1,10); // wait 10 second
		LED_voidOFF(&TrafficLightLeds[2]);

		LED_voidON(&TrafficLightLeds[1]); // Yellow Led
		TL_CountNSec(&SSD1,3); // wait 3 second
		LED_voidOFF(&TrafficLightLeds[1]);

		LED_voidON(&TrafficLightLeds[0]); // Red Led
		TL_CountNSec(&SSD1,10); // wait 10 second
		LED_voidOFF(&TrafficLightLeds[0]);


	}
	 */

	CLCD_voidInit();


	while(1)
	{
		for(u8 i = 1 ; i < 16 ; i++)
		{
			CLCD_voidSetPosition(CLCD_ROW_1 , CLCD_COL_5);
			CLCD_voidSendString((u8*)"Hamoksha");

			CLCD_voidSendExtraChar(0 , Array , CLCD_ROW_2 , i);
			_delay_ms(250);
			CLCD_voidSendCommand(CLCD_CLEAR_DISPLAY);

		}
	}

	/*
		CLCD_voidSendData(0x61);
		CLCD_voidSendData('M');
		CLCD_voidSendData('R');


		while(1)
		{

		}*/

	return 0 ;


}
