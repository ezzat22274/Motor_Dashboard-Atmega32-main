/*
 * EXTI_MCAL_Interface.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_EXTI_DRIVER_EXTI_MCAL_INTERFACE_H_
#define MCAL_EXTI_DRIVER_EXTI_MCAL_INTERFACE_H_

typedef enum {
		low_level = 0,
		any_level,
		falling,
		rising
}INT_Sense_Contorl;
typedef enum {
		falling_edge = 0,
		rising_edge,
}INT2_Sense_Contorl;


void EXTI_Init(void);
void EXTI_INT0ENABLE(void);
void EXTI_INT0DISABLE(void);
void EXTI_INT1ENABLE(void);
void EXTI_INT1DISABLE(void);
void EXTI_INT2ENABLE(void);
void EXTI_INT2DISABLE(void);
void EXTI_INT0Sense(INT_Sense_Contorl sense);
void EXTI_INT1Sense(INT_Sense_Contorl sense);
void EXTI_INT2Sense(INT2_Sense_Contorl sense);

void EXTI_INT0SetCallBack(void(*pf)(void));
void EXTI_INT1SetCallBack(void(*pf)(void));
void EXTI_INT2SetCallBack(void(*pf)(void));

#define EXTI_INT0	0
#define EXTI_INT1	1
#define EXTI_INT2	2

#define EXTI_LOW_LEVEL		0b00
#define EXTI_ANY_LEVEL		0b01
#define EXTI_FALLING_EDGE	0b10
#define EXTI_RISING_EDGE	0b11

#define EXTI_INT2_FALLING_EDGE		0
#define EXTI_INT2_RISING_EDGE		1

#define EXTI_ENABLE		1
#define EXTI_DISABLE	0

#endif /* MCAL_EXTI_DRIVER_EXTI_MCAL_INTERFACE_H_ */
