/*
 * EXTI_MCAL_Prog.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Lenovo
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <avr/interrupt.h>
#include "EXTI_MCAL_Private.h"
#include "EXTI_MCAL_Interface.h"
#include "EXTI_MCAL_Config.h"

static void (*Int0CallBack)(void) =STD_TYPES_NULL;
static void (*Int1CallBack)(void)= STD_TYPES_NULL;
static void (*Int2CallBack)(void) = STD_TYPES_NULL;

void EXTI_Init(void)
{
	//clear first
	CLR_BIT(MCUCR_REG,0);
	CLR_BIT(MCUCR_REG,1);
	CLR_BIT(MCUCR_REG,2);
	CLR_BIT(MCUCR_REG,3);
	CLR_BIT(MCUCSR_REG,6);
	//INT0 sense
	#if  EXT_INT0_SENSE == EXTI_LOW_LEVEL
			MCUCR_REG &= 0b11111100;
			MCUCR_REG |= 0b00000000;
	#elif EXT_INT0_SENSE == EXTI_ANY_LEVEL
			MCUCR_REG &= 0b11111100;
			MCUCR_REG |= 0b00000001;
	#elif EXT_INT0_SENSE == EXTI_FALLING_EDGE
			MCUCR_REG &= 0b11111100;
			MCUCR_REG |= 0b00000010;
	#elif EXT_INT0_SENSE == EXTI_RISING_EDGE
			MCUCR_REG &= 0b11111100;
			MCUCR_REG |= 0b00000011;
	#endif

	//INT1 sense
	#if  EXT_INT1_SENSE == EXTI_LOW_LEVEL
			MCUCR_REG &= 0b11110011;
			MCUCR_REG |= 0b00000000;
	#elif EXT_INT1_SENSE == EXTI_ANY_LEVEL
			MCUCR_REG &= 0b11110011;
			MCUCR_REG |= 0b00000100;
	#elif EXT_INT1_SENSE == EXTI_FALLING_EDGE
			MCUCR_REG &= 0b11110011;
			MCUCR_REG |= 0b00001000;
	#elif EXT_INT1_SENSE == EXTI_RISING_EDGE
			MCUCR_REG &= 0b11110011;
			MCUCR_REG |= 0b00001100;
	#endif
			//INT1 sense
	#if EXT_INT2_SENSE == EXTI_INT2_FALLING_EDGE
			MCUCSR_REG &= 0b10111111;
			MCUCSR_REG |= 0b00000000;
	#elif EXT_INT2_SENSE == EXTI_INT2_RISING_EDGE
			MCUCSR_REG &= 0b10111111;
			MCUCSR_REG |= 0b01000000;
	#endif

}
/*state*/
//INT0 state
void EXTI_INT0ENABLE(void)
{
			SET_BIT(GICR_REG,6);
}
void EXTI_INT0DISABLE(void)
{
	CLR_BIT(GICR_REG,6);
}
void EXTI_INT1ENABLE(void)
{
	SET_BIT(GICR_REG,7);
}
void EXTI_INT1DISABLE(void)
{
	CLR_BIT(GICR_REG,7);
}
void EXTI_INT2ENABLE(void)
{
		SET_BIT(GICR_REG,5);
}
void EXTI_INT2DISABLE(void)
{
	CLR_BIT(GICR_REG,5);
}
void EXTI_INT0Sense(INT_Sense_Contorl sense)
{
	switch(sense)
	{
	case low_level :
		MCUCR_REG &= 0b11111100;
		MCUCR_REG |= 0b00000000;
		break;
	case  any_level :
		MCUCR_REG &= 0b11111100;
		MCUCR_REG |= 0b00000001;
		break;
	case falling :
		MCUCR_REG &= 0b11111100;
		MCUCR_REG |= 0b00000010;
		break;
	case rising :
		MCUCR_REG &= 0b11111100;
		MCUCR_REG |= 0b00000011;
		break;
	}
}
void EXTI_INT1Sense(INT_Sense_Contorl sense)
{
	switch(sense)
	{
	case low_level :
		MCUCR_REG &= 0b11110011;
		MCUCR_REG |= 0b00000000;
		break;
	case any_level :
		MCUCR_REG &= 0b11110011;
		MCUCR_REG |= 0b00000100;
		break;
	case falling :
		MCUCR_REG &= 0b11110011;
		MCUCR_REG |= 0b00001000;
		break;
	case rising :
		MCUCR_REG &= 0b11110011;
		MCUCR_REG |= 0b00001100;
		break;
	}
}
void EXTI_INT2Sense(INT2_Sense_Contorl sense)
{
	switch(sense)
	{
	case falling_edge :
		MCUCSR_REG &= 0b10111111;
		MCUCSR_REG |= 0b00000000;
		break;
	case rising_edge :
		MCUCSR_REG &= 0b10111111;
		MCUCSR_REG |= 0b01000000;
		break;
	}
}
void EXTI_INT0SetCallBack(void(*pf)(void))
{
	Int0CallBack = pf;
}
void EXTI_INT1SetCallBack(void(*pf)(void))
{
	Int1CallBack = pf;
}
void EXTI_INT2SetCallBack(void(*pf)(void))
{
	Int2CallBack = pf;
}
ISR(INT0_vect)
{
	Int0CallBack();
}
ISR(INT1_vect)
{
	Int1CallBack();
}
ISR(INT2_vect)
{
	Int2CallBack();
}
