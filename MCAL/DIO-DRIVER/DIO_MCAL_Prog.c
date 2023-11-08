/*
 * DIO_MCAL_Prog.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Lenovo
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "DIO_MCAL_Config.h"
#include "DIO_MCAL_Interface.h"
#include "DIO_MCAL_Private.h"


u8 DIO_Init(void)
{
	u8 ERROR = STD_TYPES_OK;
	DIO_DDRA_REG = 0b00000000; //input
	DIO_DDRB_REG = 0b00000000; //input
	DIO_DDRC_REG = 0b00000000; //input
	DIO_DDRD_REG = 0b00000000; //input

	DIO_PORTA_REG = 0b00000000;//initial value
	DIO_PORTB_REG = 0b00000000;//initial value
	DIO_PORTC_REG = 0b00000000;//initial value
	DIO_PORTD_REG = 0b00000000;//initial value

	return ERROR;
}

u8 DIO_SetPinDirection(u8 Port_Id, u8 Pin_Id,u8 Pin_Direction)
{
	u8 ERROR = STD_TYPES_NOK;
	if(Port_Id <= DIO_PORTD && Pin_Id <= DIO_PIN7)
	{
		ERROR = STD_TYPES_OK;
		if(Pin_Direction == DIO_OUTPUT)
		{
			switch(Port_Id)
			{
			case DIO_PORTA :
				SET_BIT(DIO_DDRA_REG,Pin_Id);
				break;
			case DIO_PORTB :
				SET_BIT(DIO_DDRB_REG,Pin_Id);
				break;
			case DIO_PORTC :
				SET_BIT(DIO_DDRC_REG,Pin_Id);
				break;
			case DIO_PORTD :
				SET_BIT(DIO_DDRD_REG,Pin_Id);
				break;
			}
		}
		else if(Pin_Direction == DIO_INPUT)
		{
			switch(Port_Id)
			{
			case DIO_PORTA :
				CLR_BIT(DIO_DDRA_REG,Pin_Id);
				break;
			case DIO_PORTB :
				CLR_BIT(DIO_DDRB_REG,Pin_Id);
				break;
			case DIO_PORTC :
				CLR_BIT(DIO_DDRC_REG,Pin_Id);
				break;
			case DIO_PORTD :
				CLR_BIT(DIO_DDRD_REG,Pin_Id);
				break;
			}
		}
		else
		{
			ERROR = STD_TYPES_NOK;
		}
	}
	return ERROR;
}
u8 DIO_SetPinValue(u8 Port_Id, u8 Pin_Id,u8 Pin_Value)
{
	u8 ERROR = STD_TYPES_NOK;
	if(Port_Id <= DIO_PORTD && Pin_Id <= DIO_PIN7)
		{
			ERROR = STD_TYPES_OK;
			if(Pin_Value == DIO_HIGH)
			{
				switch(Port_Id)
				{
				case DIO_PORTA :
					SET_BIT(DIO_PORTA_REG,Pin_Id);
					break;
				case DIO_PORTB :
					SET_BIT(DIO_PORTB_REG,Pin_Id);
					break;
				case DIO_PORTC :
					SET_BIT(DIO_PORTC_REG,Pin_Id);
					break;
				case DIO_PORTD :
					SET_BIT(DIO_PORTD_REG,Pin_Id);
					break;
				}
			}
			else if(Pin_Value == DIO_LOW)
			{
				switch(Port_Id)
				{
				case DIO_PORTA :
					CLR_BIT(DIO_PORTA_REG,Pin_Id);
					break;
				case DIO_PORTB :
					CLR_BIT(DIO_PORTB_REG,Pin_Id);
					break;
				case DIO_PORTC :
					CLR_BIT(DIO_PORTC_REG,Pin_Id);
					break;
				case DIO_PORTD :
					CLR_BIT(DIO_PORTD_REG,Pin_Id);
					break;
				}
			}
			else
			{
				ERROR = STD_TYPES_NOK;
			}
		}
		return ERROR;
}
u8 DIO_GetPinValue(u8 Port_Id, u8 Pin_Id)
{
	u8 Value;
	if(Port_Id <= DIO_PORTD && Pin_Id <= DIO_PIN7)
	{

		switch(Port_Id)
		{
		case DIO_PORTA :
			Value = GET_BIT(DIO_PINA_REG,Pin_Id);
			break;
		case DIO_PORTB :
			Value = GET_BIT(DIO_PINB_REG,Pin_Id);
			break;
		case DIO_PORTC :
			Value = GET_BIT(DIO_PINC_REG,Pin_Id);
			break;
		case DIO_PORTD :
			Value = GET_BIT(DIO_PIND_REG,Pin_Id);
			break;
		default  :

			break;
		}
	}
	return Value;
}

u8 DIO_TogglePin(u8 Port_Id,u8 Pin_Id)
{
	u8 ERROR = STD_TYPES_NOK;
			if(Port_Id <= DIO_PORTD && Pin_Id<=DIO_PIN7)
			{
				ERROR = STD_TYPES_OK;
				DIO_SetPinDirection(Port_Id,Pin_Id,DIO_OUTPUT);
				switch(Port_Id)
				{
				case DIO_PORTA :
					TOG_BIT(DIO_PORTA_REG,Pin_Id);
					break;
				case DIO_PORTB :
					TOG_BIT(DIO_PORTB_REG,Pin_Id);
					break;
				case DIO_PORTC :
					TOG_BIT(DIO_PORTC_REG,Pin_Id);
					break;
				case DIO_PORTD :
					TOG_BIT(DIO_PORTD_REG,Pin_Id);
					break;
				}
			}
		return ERROR;
}
u8 DIO_SetPortDirection(u8 Port_Id, u8 Port_Dirction)
{
	u8 ERROR = STD_TYPES_NOK;
	if(Port_Id <= DIO_PORTD)
	{
		ERROR = STD_TYPES_OK;
		switch(Port_Dirction)
		{
		case DIO_OUTPUT :
			switch(Port_Id)
			{
			case DIO_PORTA :
				DIO_DDRA_REG = 0xff;
				break;
			case DIO_PORTB :
				DIO_DDRB_REG = 0xff;
				break;
			case DIO_PORTC :
				DIO_DDRC_REG = 0xff;
				break;
			case DIO_PORTD :
				DIO_DDRD_REG  = 0xff;
				break;
			}
			break;
			case DIO_INPUT :
				switch(Port_Id)
				{
				case DIO_PORTA :
					DIO_DDRA_REG = 0x00;
					break;
				case DIO_PORTB :
					DIO_DDRB_REG = 0x00;
					break;
				case DIO_PORTC :
					DIO_DDRC_REG = 0x00;
					break;
				case DIO_PORTD :
					DIO_DDRD_REG  = 0x00;
					break;
				}
				break;
				default :
					ERROR = STD_TYPES_NOK;
					break;
		}
	}
	return ERROR;
}
u8 DIO_SetPortValue(u8 Port_Id, u8 Port_Value)
{
	u8 ERROR = STD_TYPES_NOK;
	if(Port_Id <= DIO_PORTD)
	{
		ERROR = STD_TYPES_OK;
		switch(Port_Id)
		{
		case DIO_PORTA :
			DIO_PORTA_REG = Port_Value;
			break;
		case DIO_PORTB :
			DIO_PORTB_REG = Port_Value;
			break;
		case DIO_PORTC :
			DIO_PORTC_REG = Port_Value;
			break;
		case DIO_PORTD :
			DIO_PORTD_REG = Port_Value;
			break;
		}
	}
	return ERROR;
}
u8 DIO_TogglePort(u8 Port_Id)
{
	u8 ERROR = STD_TYPES_NOK;
		if(Port_Id <= DIO_PORTD)
		{
			ERROR = STD_TYPES_OK;
			switch(Port_Id)
			{
			case DIO_PORTA :
				TOG_PORT(DIO_PORTA_REG);
				break;
			case DIO_PORTB :
				TOG_PORT(DIO_PORTB_REG);
				break;
			case DIO_PORTC :
				TOG_PORT(DIO_PORTC_REG);
				break;
			case DIO_PORTD :
				TOG_PORT(DIO_PORTD_REG);
				break;
			}
		}
		return ERROR;
}



