/*
 * USART_MCAL_Interface.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_USART_DRIVER_USART_MCAL_INTERFACE_H_
#define MCAL_USART_DRIVER_USART_MCAL_INTERFACE_H_



void USART_Init(u16 BaudRate);
void USART_Transmit(u8 Data);
u16 USART_Recieve(void);
void USART_SendString(char *str);
void USART_INTInit(u16 BaudRate);
void USART_SetCallBack(void (*pf)(void));




#define bits_5 		0b000
#define bits_6 		0b001
#define bits_7 		0b010
#define bits_8 		0b011
#define bits_9 		0b111

#define Disabled	0b00
#define EVEN		0b10
#define ODD			0b11


#define One_Bit			0
#define Two_Bit			1

#define U2X_Enable	 1
#define U2X_Disabled 0


#endif /* MCAL_USART_DRIVER_USART_MCAL_INTERFACE_H_ */
