/*
 * STEP_HAL_Prog.c
 *
 *  Created on: Oct 8, 2023
 *      Author: Lenovo
 */

#include<avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "STEP_HAL_Interface.h"
#include "STEP_HAL_Config.h"
#include "STEP_HAL_Private.h"

void STEP_NoOfSteps(u32 No, u8 Wise)
{
	u32 copy = No;

	if (Wise == CLOCKWISE) {
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_HIGH);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_LOW);
		_delay_ms(5);
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_HIGH);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_LOW);
		_delay_ms(5);
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_HIGH);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_LOW);
		_delay_ms(5);
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_HIGH);
		_delay_ms(5);
	} else if (Wise == ACLOCKWISE)
	{
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_HIGH);
		_delay_ms(5);
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_HIGH);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_LOW);
		_delay_ms(5);
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_HIGH);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_LOW);
		_delay_ms(5);
		DIO_SetPinValue(STEP_PORT, BLUE, DIO_HIGH);
		DIO_SetPinValue(STEP_PORT, PINK, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, YELLOW, DIO_LOW);
		DIO_SetPinValue(STEP_PORT, ORANGE, DIO_LOW);
		_delay_ms(5);
	}
	}

void STEP_NoOfRev(u32 Rev, u8 Wise)
{
	u32 x = Rev * 64;
		STEP_NoOfSteps(x,Wise);
}
