/*
 * KPD_HAL_Prog.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Lenovo
 */

#include "../../LIB/Bit_Math.h"
#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "KPD_HAL_Config.h"
#include "KPD_HAL_Interface.h"
#include "KPD_HAL_Private.h"
#include <avr/delay.h>
u8 u8CharArr[4][4] = {	{'7','8','9','/'},
						{'4','5','6','*'},
						{'1','2','3','-'},
						{'c','0','=','+'}
					 };



void KPD_Init(void)
{
	//col as pull up  //first makes it as input the write high in it
		DIO_SetPinDirection( KPD_PORT , 4 , DIO_INPUT );
		DIO_SetPinDirection( KPD_PORT , 5, DIO_INPUT );
		DIO_SetPinDirection( KPD_PORT , 6, DIO_INPUT );
		DIO_SetPinDirection( KPD_PORT , 7,DIO_INPUT );

		DIO_SetPinValue( KPD_PORT , 4, DIO_HIGH );
		DIO_SetPinValue( KPD_PORT , 5, DIO_HIGH );
		DIO_SetPinValue( KPD_PORT , 6, DIO_HIGH );
		DIO_SetPinValue( KPD_PORT , 7, DIO_HIGH );

		//row  direction as output then puts high on them
		DIO_SetPinDirection( KPD_PORT , 0 , DIO_OUTPUT );
		DIO_SetPinDirection( KPD_PORT , 1, DIO_OUTPUT );
		DIO_SetPinDirection( KPD_PORT , 2, DIO_OUTPUT );
		DIO_SetPinDirection( KPD_PORT , 3, DIO_OUTPUT );

		DIO_SetPinValue( KPD_PORT , 0 , DIO_HIGH );
		DIO_SetPinValue( KPD_PORT , 1, DIO_HIGH );
		DIO_SetPinValue( KPD_PORT , 2, DIO_HIGH );
		DIO_SetPinValue( KPD_PORT , 3, DIO_HIGH );
}

u8 KPD_GetKey(void)
{
	u8 RetValue =KPD_NOTPRESSED;
	for (u8 row = ROWS; row <= ROWE;row++)
	{
		DIO_SetPinValue(KPD_PORT,row,DIO_LOW);
		for(u8 col = COLS; col <= COLE;col++)
		{
			if(DIO_GetPinValue(KPD_PORT,col) == DIO_LOW)
			{
				RetValue = u8CharArr[row][col - 4];
				_delay_ms(50);
				while(DIO_GetPinValue(KPD_PORT,col) == DIO_LOW);
			}
		}
		DIO_SetPinValue(KPD_PORT,row,DIO_HIGH);
	}
	return RetValue;
}
