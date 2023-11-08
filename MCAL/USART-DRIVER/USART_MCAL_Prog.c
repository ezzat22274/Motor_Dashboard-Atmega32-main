/*
 * USART_MCAL_Prog.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Lenovo
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <avr/interrupt.h>
#include "USART_MCAL_Config.h"
#include "USART_MCAL_Interface.h"
#include "USART_MCAL_Private.h"

static volatile void(*USART_pf)(void) = STD_TYPES_NULL;
void USART_Init(u16 BaudRate)
{
	//Asynch
	CLR_BIT(UCSRC_REG,UMSEL);
	//Enable access to UCSRC
	SET_BIT(UCSRC_REG,URSEL);

	u16 URRB_Value;
	//baudrate
#if U2X == U2X_Enable
	URRB_Value = (8000000 / (16 * BaudRate )) - 1;
	SET_BIT(UCSRA_REG,U2X);
#else //disabled
	URRB_Value = (8000000 / (8 * BaudRate )) - 1;
	CLR_BIT(UCSRA_REG,U2X);
#endif
	UBRRL_REG = URRB_Value;
	UBRRH_REG = URRB_Value >>8;
	//Enable TX and RX
	SET_BIT(UCSRB_REG,TXEN);
	SET_BIT(UCSRB_REG,RXEN);

		/*Frame*/
	//Char Size
	#if Char_Size == bits_5
	CLR_BIT(UCSRB_REG,UCSZ2);
	CLR_BIT(UCSRC_REG,UCSZ1);
	CLR_BIT(UCSRC_REG,UCSZ0);
	#elif Char_Size == bits_6
	CLR_BIT(UCSRB_REG,UCSZ2);
	CLR_BIT(UCSRC_REG,UCSZ1);
	SET_BIT(UCSRC_REG,UCSZ0);
	#elif Char_Size == bits_7
	CLR_BIT(UCSRB_REG,UCSZ2);
	SET_BIT(UCSRC_REG,UCSZ1);
	CLR_BIT(UCSRC_REG,UCSZ0);
	#elif Char_Size == bits_8
	CLR_BIT(UCSRB_REG,UCSZ2);
	SET_BIT(UCSRC_REG,UCSZ1);
	SET_BIT(UCSRC_REG,UCSZ0);
	#else // 9bits
	SET_BIT(UCSRB_REG,UCSZ2);
	SET_BIT(UCSRC_REG,UCSZ1);
	SET_BIT(UCSRC_REG,UCSZ0);
	#endif

	//parity
	#if Parity_Mode == Disabled
	CLR_BIT(UCSRC_REG,UPM1);
	CLR_BIT(UCSRC_REG,UPM0);
	#elif Parity_Mode == EVEN
	SET_BIT(UCSRC_REG,UPM1);
	CLR_BIT(UCSRC_REG,UPM0);
	#else //odd
	SET_BIT(UCSRC_REG,UPM1);
	SET_BIT(UCSRC_REG,UPM0);
	#endif

	//stop bits
	#if Stop_Bits == One_Bit
	CLR_BIT(UCSRC_REG,USBS);
	#else//two bits
	SET_BIT(UCSRC_REG,USBS);
	#endif

}
void USART_Transmit(u8 Data)
{
	while(GET_BIT(UCSRA_REG,UDRE) == 0);
	//Clear Flag
	SET_BIT(UCSRA_REG,UDRE);
#if Char_Size == bits_9
	UCSRB_REG &= ~(1 <<TXB8);
		if (Data &0x100)
		{
			UCSRB_REG |= (1 <<TXB8);
			UDR_REG = Data;
		}
		while(GET_BIT(UCSRA_REG,6) == 0);
		SET_BIT(UCSRA_REG,6);

#else
		UDR_REG =Data;
		while(GET_BIT(UCSRA_REG,6) == 0);
		SET_BIT(UCSRA_REG,6);
#endif

}
u16 USART_Recieve(void)
{
	u8 resH,resL;
	while(GET_BIT(UCSRA_REG,RXC) == 0);
#if Char_Size == bits_9
	//get 9th bit
	resH = UCSRB_REG;
	resL = UDR_REG;
	resH = (resH >> 1) &0x01;
	return ((resH << 8) |resL);
#else
	return UDR_REG;
#endif
}
void USART_SendString(char *str)
{
	u8 i = 0;
	while(str[i] != 0)
	{
		USART_Transmit(str[i]);
		i++;
	}
}
void USART_INTInit(u16 BaudRate)
{
	SET_BIT(UCSRB_REG,RXEN);
	SET_BIT(UCSRB_REG,TXEN);

	u16 URRB_Value;
		//baudrate
	#if U2X == U2X_Enable
		URRB_Value = (8000000 / (16 * BaudRate )) - 1;
		SET_BIT(UCSRA_REG,U2X);
	#else //disabled
		URRB_Value = (8000000 / (8 * BaudRate )) - 1;
		CLR_BIT(UCSRA_REG,U2X);
	#endif
		UBRRL_REG = URRB_Value;
		UBRRH_REG = URRB_Value >>8;
		//Enable TX and RX
		SET_BIT(UCSRB_REG,TXEN);
		SET_BIT(UCSRB_REG,RXEN);

	//Asynch
		CLR_BIT(UCSRC_REG,UMSEL);
		//Enable access to UCSRC
		SET_BIT(UCSRC_REG,URSEL);
		/*Frame*/
			//Char Size
			#if Char_Size == bits_5
			CLR_BIT(UCSRB_REG,UCSZ2);
			CLR_BIT(UCSRC_REG,UCSZ1);
			CLR_BIT(UCSRC_REG,UCSZ0);
			#elif Char_Size == bits_6
			CLR_BIT(UCSRB_REG,UCSZ2);
			CLR_BIT(UCSRC_REG,UCSZ1);
			SET_BIT(UCSRC_REG,UCSZ0);
			#elif Char_Size == bits_7
			CLR_BIT(UCSRB_REG,UCSZ2);
			SET_BIT(UCSRC_REG,UCSZ1);
			CLR_BIT(UCSRC_REG,UCSZ0);
			#elif Char_Size == bits_8
			CLR_BIT(UCSRB_REG,UCSZ2);
			SET_BIT(UCSRC_REG,UCSZ1);
			SET_BIT(UCSRC_REG,UCSZ0);
			#else // 9bits
			SET_BIT(UCSRB_REG,UCSZ2);
			SET_BIT(UCSRC_REG,UCSZ1);
			SET_BIT(UCSRC_REG,UCSZ0);
			#endif

			//parity
			#if Parity_Mode == Disabled
			CLR_BIT(UCSRC_REG,UPM1);
			CLR_BIT(UCSRC_REG,UPM0);
			#elif Parity_Mode == EVEN
			SET_BIT(UCSRC_REG,UPM1);
			CLR_BIT(UCSRC_REG,UPM0);
			#else //odd
			SET_BIT(UCSRC_REG,UPM1);
			SET_BIT(UCSRC_REG,UPM0);
			#endif

			//stop bits
			#if Stop_Bits == One_Bit
			CLR_BIT(UCSRC_REG,USBS);
			#else//two bits
			SET_BIT(UCSRC_REG,USBS);
			#endif

}
void USART_SetCallBack(void (*pf)(void))
{
	pf = USART_pf;
}
ISR(USART_RXC_vect)
{
	USART_pf();
}
