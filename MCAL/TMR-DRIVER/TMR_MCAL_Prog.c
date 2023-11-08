/*
 * TMR_MCAL_Prog.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Lenovo
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <avr/interrupt.h>
#include "TMR_MCAL_Config.h"
#include "TMR_MCAL_Interface.h"
#include "TMR_MCAL_Private.h"


static volatile void (*TMR0_Ov_SetCallBackPf)(void) = STD_TYPES_NULL;
static volatile void (*TMR0_CTC_SetCallBackpf)(void) = STD_TYPES_NULL;

static volatile void (*TMR2_Ov_SetCallBackPf)(void) = STD_TYPES_NULL;
static volatile void (*TMR2_CTC_SetCallBackpf)(void) = STD_TYPES_NULL;
/*
 * TMR0_SetPreload(u8 preloadValue) :
 *									Function to Set TNCT0 Reg
 *									With the requried value passed
 */
void TMR0_SetPreload(u8 preloadValue)
{
	TCNT0_REG = preloadValue;
}
/*
 * TMR0_OVF_Init : How To Use
 * In main Function
 * ======================>
 * 1) Call this function
 * 2) Call ISR using callback function for TIMER0_OVF_vect
 * 3)Set calculated preload value using TMR0_SetPreload() function
 * 4)Enable GIE
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * 1)Set Counter  to 0 (note if counter value > 256)
 * 					  You need to make counter of type u16 not u8
 * 					  Otherwise it will never reach its value and
 * 					  there will be no timer)
 * 2) DO your action and try not to forget
 * 	  to clear counter and set preload value again
 */
void TMR0_OVF_Init(void)
{
	CLR_BIT(TCCR0_REG,FOCO);
	CLR_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,COM01);
	CLR_BIT(TCCR0_REG,COM00);
	CLR_BIT(TCCR0_REG,WGM01);
	TCCR0_REG |= (TMR0_PreScalar_Value & 0b00000111);
	SET_BIT(TIMSK_REG,TOIE0);
}
/*
 * TMR0_CTC_Init : How To Use
 * A)If OC0 Disconnected
 * 				NOTE : This mode worked fine on hardwaere
 * In main Function
 * ======================>
 * 1) Call this function and Pass OC0_Diconnected to it
 * 2) Call ISR using callback function for TIMER0_COMP_vect
 * 3)Enable GIE
 *
 *<<<<<To Generate a wave using CTC Mode on Pin OC0>>
 *	NOTE : this mode needs protoes with oscliscope to observe
 *		on hardware cant observe
 * B) OC0 With Some State on it
 * In main Function
 * ======================>
 * 1)Set Direction of PB3 as output
 * 2)call this function and pass OC0 state you want
 * 3)Enable GIE
 * No ISR needed
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * 1)Set Counter  to 0 (note if counter value > 256)
 * 					  You need to make counter of type u16 not u8
 * 					  Otherwise it will never reach its value and
 * 					  there will be no timer)
 * 2) DO your action and try not to forget
 * 	  to clear counter and set CTC value using TMR0_SetOCR0_Value() function
 */
void TMR0_CTC_Init(OC0_CTC_MODE OC0_State, u8 OCR0_Value)
{
	OCR0_REG = OCR0_Value;
	CLR_BIT(TCCR0_REG,FOCO); //0
	CLR_BIT(TCCR0_REG,WGM00);//0
	SET_BIT(TCCR0_REG,WGM01);//1
	TCCR0_REG |= (TMR0_PreScalar_Value & 0b00000111);
	switch(OC0_State)
	{
	case Normal:
		// OC0 State
		CLR_BIT(TCCR0_REG,COM00);//0
		CLR_BIT(TCCR0_REG,COM01);//0
		SET_BIT(TIMSK_REG,OCIE0);
		break;
	case Toggle_OC0_On_Comp_Match:
		CLR_BIT(TCCR0_REG,COM01);//0
		SET_BIT(TCCR0_REG,COM00);//1
		break;
	case Clear_OC0_on_Comp_Match :
		CLR_BIT(TCCR0_REG,COM00);//0
		SET_BIT(TCCR0_REG,COM01);//1
		break;
	case Set_OC0_on_Comp_Match :
		SET_BIT(TCCR0_REG,COM00);//0
		SET_BIT(TCCR0_REG,COM01);//1
		break;
	}
}
/*
 * TMR0_FastPWM : How To use
 * In main Function
 * ======================>
 * 1) Make PB3 as output(its a must as its OC0) if Inverted
 * 												or Non-Inverted
 * 2) Call this function, just select OC0 mode, and pass
 * 		Duty Cycle you want
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * No need for ISR cuz its related with the Hardware, there
 * is now INT included here
 */
void TMR0_FastPWM(OC0_Fast_Mode OC0_State,u8 DutyCylce)
{
	CLR_BIT(TCCR0_REG,FOCO); //0
	SET_BIT(TCCR0_REG,WGM00);//0
	SET_BIT(TCCR0_REG,WGM01);//1
	TCCR0_REG |= (TMR0_PreScalar_Value & 0b00000111);
	if(DutyCylce > 100)
	{
		DutyCylce = 100;
	}
	switch(OC0_State)
	{
	case OC0_Disconnected:
		CLR_BIT(TCCR0_REG,COM00);
		CLR_BIT(TCCR0_REG,COM01);
		OCR0_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Non_Inverted :
		SET_BIT(TCCR0_REG,COM01);
		CLR_BIT(TCCR0_REG,COM00);
		OCR0_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Inverted :
		SET_BIT(TCCR0_REG,COM01);
		SET_BIT(TCCR0_REG,COM00);
		OCR0_REG = (  (TOP_8Bit + 1) - ((TOP_8Bit * DutyCylce) / 100) );
		break;
	}
}
/*
 * TMR0_PhasePWM : How To use
 * In main Function
 * ======================>
 * 1) Make PB3 as output(its a must as its OC0) if Inverted
 * 												or Non-Inverted
 * 2) Call this function, just select OC0 mode, and pass
 * 		Duty Cycle you want
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * No need for ISR cuz its related with the Hardware, there
 * is now INT included here
 */
void TMR0_PhasePWM(OC0_Fast_Mode OC0_State,u8 DutyCylce)
{
	CLR_BIT(TCCR0_REG,FOCO); //0
	SET_BIT(TCCR0_REG,WGM00);//0
	CLR_BIT(TCCR0_REG,WGM01);//1
	TCCR0_REG |= (TMR0_PreScalar_Value & 0b00000111);
	if(DutyCylce > 100)
	{
		DutyCylce = 100;
	}
	switch(OC0_State)
	{
	case OC0_Disconnected:
		CLR_BIT(TCCR0_REG,COM00);
		CLR_BIT(TCCR0_REG,COM01);
		OCR0_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Non_Inverted :
		SET_BIT(TCCR0_REG,COM01);
		CLR_BIT(TCCR0_REG,COM00);
		OCR0_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Inverted :
		SET_BIT(TCCR0_REG,COM01);
		SET_BIT(TCCR0_REG,COM00);
		OCR0_REG = (  (TOP_8Bit + 1) - ((TOP_8Bit * DutyCylce) / 100) );
		break;
	}
}
u8 TMR0_ReadTCNT(void)
{
	return TCNT0_REG;
}
/*
 * TMR2_SetPreload(u8 preloadValue) :
 *									Function to Set TNCT0 Reg
 *									With the requried value passed
 */
void TMR2_SetPreload(u8 preloadValue)
{
	TCNT2_REG = preloadValue;
}
/*
 * TMR2_OVF_Init : How To Use
 * In main Function
 * ======================>
 * 1) Call this function
 * 2) Call ISR using callback function for TIMER2_OVF_vect
 * 3)Set calculated preload value using TMR2_SetPreload() function
 * 4)Enable GIE
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * 1)Set Counter  to 0 (note if counter value > 256)
 * 					  You need to make counter of type u16 not u8
 * 					  Otherwise it will never reach its value and
 * 					  there will be no timer)
 * 2) DO your action and try not to forget
 * 	  to clear counter and set preload value again
 */
void TMR2_OVF_Init(void)
{
	CLR_BIT(TCCR2_REG,FOC2);
	CLR_BIT(TCCR2_REG,WGM20);
	CLR_BIT(TCCR2_REG,COM21);
	CLR_BIT(TCCR2_REG,COM20);
	CLR_BIT(TCCR2_REG,WGM21);
	TCCR2_REG |= (TMR2_PreScalar_Value & 0b00000111);
	SET_BIT(TIMSK_REG,TOIE2);
}
/*
 * TMR2_CTC_Init : How To Use
 * A)If OC0 Disconnected
 * 				NOTE : This mode worked fine on hardwaere
 * In main Function
 * ======================>
 * 1) Call this function and Pass OC0_Diconnected to it
 * 2) Call ISR using callback function for TIMER2_COMP_vect
 * 3)Enable GIE
 *
 *<<<<<To Generate a wave using CTC Mode on Pin OC0>>
 *	NOTE : this mode needs protoes with oscliscope to observe
 *		on hardware cant observe
 * B) OC0 With Some State on it
 * In main Function
 * ======================>
 * 1)Set Direction of PD7 as output
 * 2)call this function and pass OC2 state you want
 * 3)Enable GIE
 * No ISR needed
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * 1)Set Counter  to 0 (note if counter value > 256)
 * 					  You need to make counter of type u16 not u8
 * 					  Otherwise it will never reach its value and
 * 					  there will be no timer)
 * 2) DO your action and try not to forget
 * 	  to clear counter and set CTC value using TMR0_SetOCR0_Value() function
 */
void TMR2_CTC_Init(OC0_CTC_MODE OC0_State, u8 OCR2_Value)
{
	OCR2_REG = OCR2_Value;
	CLR_BIT(TCCR2_REG,FOC2); //0
	CLR_BIT(TCCR2_REG,WGM20);//0
	SET_BIT(TCCR2_REG,WGM21);//1
	TCCR2_REG |= (TMR2_PreScalar_Value & 0b00000111);
	switch(OC0_State)
	{
	case Normal:
		// OC0 State
		CLR_BIT(TCCR2_REG,COM20);//0
		CLR_BIT(TCCR2_REG,COM21);//0
		SET_BIT(TIMSK_REG,OCIE2);
		break;
	case Toggle_OC0_On_Comp_Match:
		CLR_BIT(TCCR2_REG,COM21);//0
		SET_BIT(TCCR2_REG,COM20);//1
		break;
	case Clear_OC0_on_Comp_Match :
		CLR_BIT(TCCR2_REG,COM20);//0
		SET_BIT(TCCR2_REG,COM21);//1
		break;
	case Set_OC0_on_Comp_Match :
		SET_BIT(TCCR2_REG,COM20);//0
		SET_BIT(TCCR2_REG,COM21);//1
		break;
	}
}
/*
 * TMR0_FastPWM : How To use
 * In main Function
 * ======================>
 * 1) Make PD3 as output(its a must as its OC2) if Inverted
 * 												or Non-Inverted
 * 2) Call this function, just select OC2 mode, and pass
 * 		Duty Cycle you want
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * No need for ISR cuz its related with the Hardware, there
 * is now INT included here
 */
void TMR2_FastPWM(OC0_Fast_Mode OC0_State,u8 DutyCylce)
{
	CLR_BIT(TCCR2_REG,FOC2); //0
	SET_BIT(TCCR2_REG,WGM20);//0
	SET_BIT(TCCR2_REG,WGM21);//1
	TCCR2_REG |= (TMR2_PreScalar_Value & 0b00000111);
	if(DutyCylce > 100)
	{
		DutyCylce = 100;
	}
	switch(OC0_State)
	{
	case OC0_Disconnected:
		CLR_BIT(TCCR2_REG,COM20);
		CLR_BIT(TCCR2_REG,COM21);
		OCR2_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Non_Inverted :
		SET_BIT(TCCR2_REG,COM21);
		CLR_BIT(TCCR2_REG,COM20);
		OCR2_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Inverted :
		SET_BIT(TCCR2_REG,COM21);
		SET_BIT(TCCR2_REG,COM20);
		OCR2_REG = (  (TOP_8Bit + 1) - ((TOP_8Bit * DutyCylce) / 100) );
		break;
	}
}
/*
 * TMR0_PhasePWM : How To use
 * In main Function
 * ======================>
 * 1) Make PD7 as output(its a must as its OC0) if Inverted
 * 												or Non-Inverted
 * 2) Call this function, just select OC2 mode, and pass
 * 		Duty Cycle you want
 * ---------------------------------------------------
 * In callback Function
 * ======================>
 * No need for ISR cuz its related with the Hardware, there
 * is now INT included here
 */
void TMR2_PhasePWM(OC0_Fast_Mode OC0_State,u8 DutyCylce)
{
	CLR_BIT(TCCR2_REG,FOC2); //0
	SET_BIT(TCCR2_REG,WGM20);//0
	CLR_BIT(TCCR2_REG,WGM21);//1
	TCCR2_REG |= (TMR2_PreScalar_Value & 0b00000111);
	if(DutyCylce > 100)
	{
		DutyCylce = 100;
	}
	switch(OC0_State)
	{
	case OC0_Disconnected:
		CLR_BIT(TCCR2_REG,COM20);
		CLR_BIT(TCCR2_REG,COM21);
		OCR2_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Non_Inverted :
		SET_BIT(TCCR2_REG,COM21);
		CLR_BIT(TCCR2_REG,COM20);
		OCR2_REG = ( ((DutyCylce * TOP_8Bit)/100) - 1 );
		break;
	case Inverted :
		SET_BIT(TCCR2_REG,COM21);
		SET_BIT(TCCR2_REG,COM20);
		OCR2_REG = (  (TOP_8Bit + 1) - ((TOP_8Bit * DutyCylce) / 100) );
		break;
	}
}
u8 TMR2_ReadTCNT(void)
{
	return TCNT2_REG;
}




void TMR0_CTC_SetCallBack(void (*pf)(void))
{
	TMR0_CTC_SetCallBackpf =pf;
}
void TMR2_CTC_SetCallBack(void (*pf)(void))
{
	TMR2_CTC_SetCallBackpf =pf;
}
void TMR0_OV_SetCallBack(void (*pf)(void))
{
	TMR0_Ov_SetCallBackPf = pf;
}
void TMR2_OV_SetCallBack(void (*pf)(void))
{
	TMR2_Ov_SetCallBackPf = pf;
}
ISR(TIMER0_OVF_vect)
{
	TMR0_Ov_SetCallBackPf();
}
ISR(TIMER0_COMP_vect)
{
	TMR0_CTC_SetCallBackpf();
}
ISR(TIMER2_OVF_vect)
{
	TMR2_Ov_SetCallBackPf();
}
ISR(TIMER2_COMP_vect)
{
	TMR2_CTC_SetCallBackpf();
}

