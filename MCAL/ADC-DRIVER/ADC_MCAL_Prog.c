/*
 * ADC_MCAL_Prog.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Lenovo
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "ADC_MCAL_Private.h"
#include "ADC_MCAL_Interface.h"
#include "ADC_MCAL_Config.h"


void ADC_Init(void) {

	//Ref Select
#if ADC_VREF == ADC_AREF
	ADMUX_REG &= 0b00111111;
	ADMUX_REG |= 0b00000000;
#elif ADC_VREF == ADC_AVCC
	ADMUX_REG &= 0b00111111;
	ADMUX_REG |= 0b01000000;
#elif ADC_VREF == ADC_INTERNAL
	ADMUX_REG &= 0b00111111;
	ADMUX_REG |= 0b11000000;
#endif

//	//Adjusment
//	#if ADC_ADJ == ADC_LEFT_ADJ
//	ADMUX_REG &= 0b11011111;
//	ADMUX_REG |= 0b00100000;
//	#elif ADC_ADJ == ADC_RIGHT_ADJ
//	ADMUX_REG &= 0b11011111;
//	ADMUX_REG |= 0b00000000;
//	#endif


	//prescalar 64
	ADCSRA_REG &= 0b11111000;
	ADCSRA_REG |= 0b00000110;


	//Enable ADC
		SET_BIT(ADCSRA_REG, ADEN);
}

u16 ADC_GetResult(u8 Channel) {
	u16 Value;
	u8 TimerCounter = 0; //for time out
	//Channel
	ADMUX_REG &= 0b11100000;
	ADMUX_REG |= (Channel &0xF8);
	//start convesrion
	SET_BIT(ADCSRA_REG, ADSC);
	// trun off auto trigger
	CLR_BIT(ADCSRA_REG,ADATE);
	//disable INT
	CLR_BIT(ADCSRA_REG,ADIE);
	//wait polling
	while (GET_BIT(ADCSRA_REG,ADIF) && TimerCounter < ADC_TIMEROUT) {
		TimerCounter++;
	}
	SET_BIT(ADCSRA_REG,ADIF);
	/***REG_ADJ*****/
//#if ADC_ADJ == ADC_RIGHT_ADJ
////	Value = ADC_REG;
//	return ADC_REG;
//#else
////	Value = (ADCL_REG);
////	Value |=( ADCH_REG << 8);
//	return (ADCH_REG << 8 | ADCL_REG >>2);
//#endif
return ADC_REG;

}
//
//u16 ADC_GetValueINT(u8 ADCCHANNEL, void(*ADC_pf)(u16))
//{
//	//make busy flag
//	BusyFlag = ADC_BUSY;
//	//pointer to fun
//	ADC_SetCallback = ADC_pf;
//	//clear channel
//	ADMUX_REG &= 0b11100000;
//	//select chaennel
//	ADMUX_REG |= ADCCHANNEL;
//	//enaable INT
//	SET_BIT(ADCSRA_REG,3);
//	//start con
//	SET_BIT(ADCSRA_REG,6);
//}
//void __vector_16(void) __attribute__((signal));
//void __vector_16(void)
//{
//	//set flag not busy
//	BusyFlag = ADC_NOT_BUSY;
//	ADC_SetCallback(ADC_REG);
//	//disable INT
//	CLR_BIT(ADCSRA_REG,3);
//}
