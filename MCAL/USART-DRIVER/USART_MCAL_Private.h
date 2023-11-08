/*
 * USART_MCAL_Private.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_USART_DRIVER_USART_MCAL_PRIVATE_H_
#define MCAL_USART_DRIVER_USART_MCAL_PRIVATE_H_


#define UDR_REG			*((volatile u8*) (0x2C))
#define UCSRA_REG		*((volatile u8*) (0x2B))
#define UCSRB_REG		*((volatile u8*) (0x2A))
#define UCSRC_REG		*((volatile u8*) (0x40))

#define UBRRL_REG		*((volatile u8*) (0x29))
#define UBRRH_REG		*((volatile u8*) (0x40))


#define RXC 	7
#define TXC 	6
#define UDRE	5
#define FE 		4
#define DOR 	3
#define PE 		2
#define U2X 	1
#define MPCM 	0

#define RXIE	7
#define TXIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3
#define UCSZ2	2
#define	RXB8	1
#define TXB8	0

#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0



#endif /* MCAL_USART_DRIVER_USART_MCAL_PRIVATE_H_ */
