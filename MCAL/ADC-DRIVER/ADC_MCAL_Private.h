/*
 * ADC_MCAL_Private.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_ADC_DRIVER_ADC_MCAL_PRIVATE_H_
#define MCAL_ADC_DRIVER_ADC_MCAL_PRIVATE_H_

#define ADMUX_REG	*((volatile u8*)(0x27))
#define ADCSRA_REG	*((volatile u8*)(0x26))
#define SFIOR_REG	*((volatile u8*)(0x50))

#define ADCL_REG	*((volatile u8*)(0x24))
#define ADCH_REG	*((volatile u8*)(0x25))

#define ADC_REG		*((volatile u16*)(0x24))






#define ADC_AREF		0
#define ADC_AVCC		1
#define ADC_INTERNAL	3
//ADMUX
#define REFS1	7
#define REFS0	6
#define ADLAR	5
//ADCSRA
#define ADEN 	7
#define ADSC 	6
#define ADATE	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0
//SFIOR
#define ADTS2	7
#define ADTS1	6
#define ADTS0	5


#define AUTO_TRIGGER_MODE 		1
#define SINGLE_CONVERSION_MODE	0

#define RUNNING_MODE		0b000
#define ANALOG_COMP			0b001
#define EXTI_REQ0			0b010
#define TIMER0_COMPA		0b011
#define TIMER0_OVF			0b100
#define TIMER1_COMPB		0b101
#define TIMER1_OVF			0b110
#define TIMER1_CAP_EVENT	0b111

#define INT_ENABLE	1
#define INT_DISABLE	0

#define ADC_NOT_BUSY       1
#define ADC_BUSY           0


#define ADC_LEFT_ADJ	1
#define ADC_RIGHT_ADJ	0




#endif /* MCAL_ADC_DRIVER_ADC_MCAL_PRIVATE_H_ */
