/*
 * ADC_MCAL_Interface.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_ADC_DRIVER_ADC_MCAL_INTERFACE_H_
#define MCAL_ADC_DRIVER_ADC_MCAL_INTERFACE_H_



void ADC_Init(void);
u16 ADC_GetResult(u8 Channel);
u16 ADC_GetValueINT(u8 ADCCHANNEL, void(*ADC_pf)(u16));

#define ADC0	0
#define ADC1	1
#define ADC2	2
#define ADC3	3
#define ADC4	4
#define ADC5	5
#define ADC6	6
#define ADC7	7

#define PRESCALAR_2 	1
#define PRESCALAR_4 	2
#define PRESCALAR_8 	3
#define PRESCALAR_16 	4
#define PRESCALAR_32	5
#define PRESCALAR_64 	6
#define PRESCALAR_128 	7




#endif /* MCAL_ADC_DRIVER_ADC_MCAL_INTERFACE_H_ */
