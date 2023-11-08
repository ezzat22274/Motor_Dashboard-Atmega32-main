/*
 * SEG_HAL_Prog.c
 *
 *  Created on: Oct 5, 2023
 *      Author: Lenovo
 */
/*
 * SEG_Init
 * 			: Initialize Seven Segment Port
 */
#include<avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "SEG_HAL_Interface.h"
#include "SEG_HAL_Config.h"
#include "SEG_HAL_Private.h"
static const u8 Cathode_Nums [10] =
		{
				 ~0b10111111,//0
				 ~0b10000110,//1
				 ~0b11011011,//2
				 ~0b11001111,//3
				 ~0b11100110,//4
				 ~0b11101101,//5
				 ~0b11111101,//6
				 ~0b10000111,//7
				 ~0b11111111,//8
				 ~0b11101111//9
		};
static const u8 Anode_Nums [10] =
		{
				 0b10111111,//0
				 0b10000110,//1
				 0b11011011,//2
				 0b11001111,//3
				 0b11100110,//4
				 0b11101101,//5
				 0b11111101,//6
				 0b10000111,//7
				 0b11111111,//8
				 0b11101111//9
		};
u8 SEG_Init(u8 Port)
{
	u8 ERROR = STD_TYPES_NOK;
	if(Port <= DIO_PORTD)
	{
		ERROR = STD_TYPES_OK;
		DIO_SetPortDirection(Port,DIO_OUTPUT);
	}
	else
	{
		ERROR = STD_TYPES_NOK;
	}
	return ERROR;
}
u8 SEG_DispalyNum(u8 Port,u8 Num)
{
	u8 ERROR = STD_TYPES_NOK;
	if(Port <= DIO_PORTD && (Num >= 0 && Num <= 9))
			{
			ERROR = STD_TYPES_OK;
#if SEG_TYPE == CATHODE
			DIO_SetPortValue(Port,Cathode_Nums[Num]);
#else
			DIO_SetPortValue(Port,Anode_Nums[Num]);
#endif
			}
return ERROR;
}

