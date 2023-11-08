/*
 * ADC_MCAL_Config.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_ADC_DRIVER_ADC_MCAL_CONFIG_H_
#define MCAL_ADC_DRIVER_ADC_MCAL_CONFIG_H_

/*ADC_VREF :
 * 				ADC_AREF
 * 				ADC_AVCC
 * 				ADC_INTERNAL
 */
#define ADC_VREF ADC_INTERNAL
/*
 * ADC_ADJ :
 * 			ADC_LEFT_ADJ
 * 			ADC_RIGHT_ADJ
 */
#define ADC_ADJ	ADC_RIGHT_ADJ
/*
 * ADC_Conversion_MODE :
 * 						AUTO_TRIGGER_MODE
 * 						SINGLE_CONVERSION_MODE
 */
#define ADC_Conversion_MODE	SINGLE_CONVERSION_MODE
/*
 * INT State :
 * 			  INT_ENABLE
 * 			  INT_DISABLE
 */
#define ADC_INTState INT_DISABLE
/*
 * PRESCALAR Value :
 * 					PRESCALAR_2
 * 					PRESCALAR_4
 * 					PRESCALAR_8
 * 					PRESCALAR_16
 * 					PRESCALAR_32
 * 					PRESCALAR_64
 * 					PRESCALAR_128
 * 	note : ADC must operates in 50-200 KHZ
 */
#define ADC_PRESCALAR_VALUE	PRESCALAR_64

/*
 * ADC_TRIGGER_SOURCE:
 * 						RUNNING_MODE
 * 						ANALOG_COMP
 * 						EXTI0
 * 						TMR0_COMP
 * 						TMR0_OVF
 * 						TMR1_COMPB
 * 						TMR1_OVF
 * 						TIMER1_CAP_EVENT
 */
#define ADC_TRIGGER_SOURCE	RUNNING_MODE


#define ADC_TIMEROUT		5000

#endif /* MCAL_ADC_DRIVER_ADC_MCAL_CONFIG_H_ */
