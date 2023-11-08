/*
 * USART_MCAL_Config.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_USART_DRIVER_USART_MCAL_CONFIG_H_
#define MCAL_USART_DRIVER_USART_MCAL_CONFIG_H_



/*
 * Char Size :
 * 				bits_5
 * 				bits_6
 * 				bits_7
 * 				bits_8
 * 				bits_9
 */
#define Char_Size	bits_8
/*
 * Parity Mode :
 * 				Disabled
 * 				EVEN
 * 				ODD
 */
#define Parity_Mode Disabled
/*
 * Stop Bits
 * 			One_Bit
 * 			Two_Bit
 */
#define Stop_Bits	One_Bit
/*
 * U2X :
 * 		 U2X_Enabled
 * 		 U2X_Disabled
 */
#define U2X		U2X_Disabled

#endif /* MCAL_USART_DRIVER_USART_MCAL_CONFIG_H_ */
