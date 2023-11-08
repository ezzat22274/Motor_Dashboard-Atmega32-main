/*
 * TMR_MCAL_Private.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_TMR_DRIVER_TMR_MCAL_PRIVATE_H_
#define MCAL_TMR_DRIVER_TMR_MCAL_PRIVATE_H_

/*****************Common Register****************/
#define TIMSK_REG	*((volatile u8*)(0x59))
#define TIFR_REG	*((volatile u8*)(0x58)

/**********************TIMER 0*******************/
#define TCCR0_REG	*((volatile u8*)(0x53))
#define TCNT0_REG	*((volatile u8*)(0x52))
#define OCR0_REG	*((volatile u8*)(0x5C))




#define FOCO 	7
#define WGM00	6
#define COM01	5
#define COM00	4
#define WGM01	3
#define CS02	2
#define CS01  	1
#define CS00	0

#define TOIE0	0
#define OCIE0	1

#define TOVO	0
#define OCF0	0

/**********************TIMER 2*******************/
#define TCCR2_REG	*((volatile u8*)(0x45))
#define TCNT2_REG	*((volatile u8*)(0x44))
#define OCR2_REG	*((volatile u8*)(0x43))
#define ASSR_REG 	*((volatile u8*)(0x42))



#define FOC2 	7
#define WGM20	6
#define COM21	5
#define COM20	4
#define WGM21	3
#define CS22	2
#define CS21  	1
#define CS20	0

#define TOIE2	6
#define OCIE2	7

#define TOV2	6
#define OCF2	7





#define TOP_8Bit		256 //Top is the reslotion of timer here its 8bit so 2 to the power 8 = 256








#endif /* MCAL_TMR_DRIVER_TMR_MCAL_PRIVATE_H_ */
