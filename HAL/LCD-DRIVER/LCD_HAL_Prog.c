/*
 * LCD_HAL_Prog.c

 *
 *  Created on: Oct 4, 2023
 *      Author: Lenovo
 */
#include<avr/delay.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "LCD_HAL_Interface.h"
#include "LCD_HAL_Config.h"
#include "LCD_HAL_Private.h"



void LCD_Init(void)
{
	DIO_SetPortDirection(LCD_DATA_PORT,DIO_OUTPUT);
	DIO_SetPinDirection(LCD_CONT_PORT,LCD_RS_PIN,DIO_OUTPUT);
	DIO_SetPinDirection(LCD_CONT_PORT,LCD_RW_PIN,DIO_OUTPUT);
	DIO_SetPinDirection(LCD_CONT_PORT,LCD_E_PIN,DIO_OUTPUT);
	_delay_ms(40);
	LCD_SendCommand(FunctionSet);
	_delay_ms(1);
	LCD_SendCommand(DISPLAY_Control);
	_delay_ms(1);
	LCD_SendCommand(CLR_DISP);
	_delay_ms(1);
	LCD_SendCommand(EntryMode);
}
u8 LCD_SendCommand(u8 cmd)
{
	u8 ERROR = STD_TYPES_OK;
	//rs = low
	DIO_SetPinValue(LCD_CONT_PORT,LCD_RS_PIN,DIO_LOW);
	//RW = low
	DIO_SetPinValue(LCD_CONT_PORT,LCD_RW_PIN,DIO_LOW);
	DIO_SetPortValue(LCD_DATA_PORT,cmd);
	//enable high to low
	DIO_SetPinValue(LCD_CONT_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_us(1);
	DIO_SetPinValue(LCD_CONT_PORT,LCD_E_PIN,DIO_LOW);
	return ERROR;
}
void LCD_SendChar(u8 Char)
{
	//rs = high
	DIO_SetPinValue(LCD_CONT_PORT, LCD_RS_PIN, DIO_HIGH);
	//RW = low
	DIO_SetPinValue(LCD_CONT_PORT, LCD_RW_PIN, DIO_LOW);
	DIO_SetPortValue(LCD_DATA_PORT, Char);
	//enable high to low
	DIO_SetPinValue(LCD_CONT_PORT, LCD_E_PIN, DIO_HIGH);
	_delay_ms(2);
	DIO_SetPinValue(LCD_CONT_PORT, LCD_E_PIN, DIO_LOW);
}
u8 LCD_SendString(u8* string)
{
	u8 ERROR = STD_TYPES_OK;
	for(u8 i = 0; string[i] != '\0'; i++)
	{
		LCD_SendChar(string[i]);
	}
	return ERROR;
}
u8 LCD_SetPosition(u8 Line, u8 Col)
{
	u8  ERROR = STD_TYPES_OK;
	if(Line == 0)//first line
		{
			LCD_SendCommand(0x80+Col);
		}
		else if(Line == 1)//second line
		{
			LCD_SendCommand(0xC0+Col);
		}
		else

		{
			ERROR = STD_TYPES_NOK;
		}
	return ERROR;
}

u8 LCD_SendNumber(s32 Num)
{
//	u8 ERROR = STD_TYPES_OK;
//	u8 i = 0;
//	u8 arr[10];
////	if(Num < 0)
////	{
////		LCD_SendChar('-');
////		Num*=-1;
////	}
//	if(Num == 0)
//	{
//		LCD_SendChar('0');
//	}
//
//	while(Num != 0)
//	{
//		arr[i] = Num % 10;
//		i++;
//		Num /= 10;
//	}
//	while(i >= 0)
//	{
//		LCD_SendChar(arr[i]);
//		i--;
//	}
//	return ERROR;
	if(Num < 0)
		{
			LCD_SendChar('-');
			Num*=-1;
		}
	if(Num / 10 != 0)
		{
			LCD_SendNumber(Num / 10 );
		}
		LCD_SendChar(Num%10 + 48);
}
u8 LCD_SendFloatNumber(float num, u8 DecimalPlaces)
{
	if(num < 0)
	{
		LCD_SendChar('-');
		num*=-1;
	}
	s64 RealPart = num;
	LCD_SendNumber(RealPart);
	LCD_SendChar('.');
	s64 FloatPart = (num - (f32)RealPart) * 1000.0;
	LCD_SendNumber(FloatPart);

}

u8 LCD_GenerateSpecialChar(u8* Pattern, u8 CGROM_INDEX)
{
	u8  ERROR = STD_TYPES_OK;
	u8 add;
	if(CGROM_INDEX <= 8)
	{
		add = CGROM_INDEX * 8;
		add = SET_BIT(add,6);
		LCD_SendCommand(add);
		for(u8 i = 0;i < 8; i++)
		{
			LCD_SendChar(Pattern[i]);
		}
	}
	//return home
	LCD_SendCommand(0x02);
	return ERROR;
}



u8 LCD_DisplaySpecialChar(u8 CGRAM_INDEX, u8 LineNum, u8 CharNum)
{
	u8  ERROR = STD_TYPES_OK;
	LCD_SetPosition(LineNum,CharNum);
	LCD_SendChar(CGRAM_INDEX);
	return ERROR;
}
u8 LCD_ClearDisplay(void)
{
	LCD_SendCommand(CLR_DISP);
	return 2;
}


