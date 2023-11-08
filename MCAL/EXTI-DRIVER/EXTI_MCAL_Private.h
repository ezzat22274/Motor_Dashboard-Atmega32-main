/*
 * EXTI_MCAL_Private.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_EXTI_DRIVER_EXTI_MCAL_PRIVATE_H_
#define MCAL_EXTI_DRIVER_EXTI_MCAL_PRIVATE_H_

#define  MCUCR_REG      *((volatile u8*)0x55)
#define  MCUCSR_REG     *((volatile u8*)0x54)

#define  GICR_REG       *((volatile u8*)(0x5B))
#define  GIFR_REG       *((volatile u8*)(0x5A))

//MCUCR
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
//MCUCSR
#define ISC2 6
//GICR
#define INT0 6
#define INT1 7
#define INT2 5
//GIFR
#define INTF2 5
#define INTF0 6
#define INTF1 7

#endif /* MCAL_EXTI_DRIVER_EXTI_MCAL_PRIVATE_H_ */
