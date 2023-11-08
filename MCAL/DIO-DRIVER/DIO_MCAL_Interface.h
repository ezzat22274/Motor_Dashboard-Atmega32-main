/*
 * DIO_MCAL_Interface.h
 *
 *  Created on: Oct 3, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_DIO_DRIVER_DIO_MCAL_INTERFACE_H_
#define MCAL_DIO_DRIVER_DIO_MCAL_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"


u8 DIO_Init(void);
u8 DIO_SetPinDirection(u8 Port_Id, u8 Pin_ID,u8 Pin_Direction);
u8 DIO_SetPinValue(u8 Port_Id, u8 Pin_Id,u8 Pin_Value);
u8 DIO_GetPinValue(u8 Port_Id, u8 Pin_Id);
u8 DIO_TogglePin(u8 Port_Id,u8 Pin_Id);
u8 DIO_TogglePort(u8 Port_Id);

u8 DIO_SetPortDirection(u8 Port_Id, u8 Port_Dirction);
u8 DIO_SetPortValue(u8 Port_Id, u8 Port_Value);




#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2	2
#define DIO_PIN3	3
#define DIO_PIN4	4
#define DIO_PIN5	5
#define DIO_PIN6	6
#define DIO_PIN7	7

#define DIO_OUTPUT	1
#define DIO_INPUT	0

#define DIO_LOW		0
#define DIO_HIGH	1
#define DIO_PORT_HIGH 0b11111111
#define DIO_PORT_LOW  0b00000000




#endif /* MCAL_DIO_DRIVER_DIO_MCAL_INTERFACE_H_ */
