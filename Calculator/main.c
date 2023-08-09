/*
 * Main.c
 *
 *  Created on: Aug 6, 2023
 *      Author: Islam Shaaban
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MACROS.h"
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LED/LED_interface.h"
#include "HAL/SSD/SSD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "HAL/KPAD/KPAD_interface.h"
#include "APP/CALC_interface.h"
#define F_CPU		8000000UL
#include <util/delay.h>


int main()
{

	CLCD_voidInit();
	KPAD_voidInit();

	u8 Equation[20]={0};
	u8 EquationSize = 0;
	u32 Result = 0;
	u32 Op1=0;
	u32 Op2=0;
	u8 Operator;
	CLCD_voidSetPosition(1,1);
	CLCD_voidSendString((u8 *)"Welcome!!");
	_delay_ms(500);
	while (1)
	{
		u8 key = KPAD_u8GetPressed();

		if (key != 0xff)
		{

			if(key != 'C'){
				Equation[EquationSize] = key;
				EquationSize++;
				CLCD_voidSendData(key);
			}


			if (key == '=')
			{
				_delay_ms(500);
				if(EquationSize == 1){
					CLCD_voidSetPosition(2,1);
					CLCD_voidSendString((u8 *)"Invalid Equ!!");
					return 1;
				}
				for (u8 OperatorSize = 0; OperatorSize < EquationSize; OperatorSize++){
					if(Equation[OperatorSize]=='+' || Equation[OperatorSize]=='-'|| Equation[OperatorSize]=='*' || Equation[OperatorSize]=='/'){
						Operator = Equation[OperatorSize];
						for(u8 Digits=0; Digits<OperatorSize; Digits++){
							Op1 = (Op1 * 10) + ( Equation[Digits] - 48 );
						}

						for(u8 Ind2=OperatorSize+1; Ind2<EquationSize-1; Ind2++){
							Op2 = (Op2 * 10) + ( Equation[Ind2] - 48);
						}


						CLCD_voidCLearDisplay();

						switch(Operator){
						case '+':
							Result=0;
							Result = Op1 + Op2;
							CLCD_voidCLearDisplay();
							CLCD_voidSetPosition(1,1);
							CLCD_voidSendString((u8 *)"The Result:");
							CLCD_voidSetPosition(2,1);
							CLCD_voidSendu32Number(Result);
							EquationSize =0;
							Op1 = 0;
							Op2 = 0;
							break;
						case '-':
							Result=0;
							Result = Op1 - Op2;
							CLCD_voidSetPosition(1,1);
							CLCD_voidSendString((u8 *)"The Result:");
							CLCD_voidSetPosition(2,1);
							CLCD_voidSendu32Number(Result);
							EquationSize = 0;
							Op1 = 0;
							Op2 = 0;
							break;
						case '*':
							Result = 0;
							Result = Op1 * Op2;
							CLCD_voidSetPosition(1,1);
							CLCD_voidSendString((u8 *)"The Result:");
							CLCD_voidSetPosition(2,1);
							CLCD_voidSendu32Number(Result);
							EquationSize =0;
							Op1 = 0;
							Op2 = 0;
							break;
						case '/':
							Result = 0;
							if(Op2 == 0){
								CLCD_voidSetPosition(2,1);
								CLCD_voidSendString((u8 *)"Undefined!");
							}
							else{
								Result = Op1 / Op2;
								CLCD_voidSetPosition(1,1);
								CLCD_voidSendString((u8 *)"The Result:");
								CLCD_voidSetPosition(2,1);
								CLCD_voidSendu32Number(Result);
							}
							EquationSize = 0;
							Op1 = 0;
							Op2 = 0;
							break;
						default:
							CLCD_voidSetPosition(2,1);
							CLCD_voidSendString((u8 *)"Invalid Op!!");
						}
						break;
					}
				}


			}
			else if(key == 'C'){
				CLCD_voidSetPosition(1,1);
				CLCD_voidCLearDisplay();

				CLCD_voidSendString((u8 *)"Clear Display");
				_delay_ms(500);
				CLCD_voidCLearDisplay();
				Result =0;
				Op1 = 0;
				Op2 = 0;
				EquationSize = 0;
				for(u8 init=0; init<20; init++)
					Equation[init]=0;

			}
		}
	}
	return 0;
}
