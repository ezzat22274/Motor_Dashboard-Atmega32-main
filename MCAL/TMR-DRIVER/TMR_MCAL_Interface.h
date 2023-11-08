/*
 * TMR_MCAL_Interface.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_TMR_DRIVER_TMR_MCAL_INTERFACE_H_
#define MCAL_TMR_DRIVER_TMR_MCAL_INTERFACE_H_

typedef enum {
	Normal= 0,
	Toggle_OC0_On_Comp_Match,
	Clear_OC0_on_Comp_Match,
	Set_OC0_on_Comp_Match
}OC0_CTC_MODE;

typedef enum{
	OC0_Disconnected = 0,
	Non_Inverted = 2,
	Inverted
}OC0_Fast_Mode;

/* TIMER0 */
void TMR0_OVF_Init(void);
void TMR0_SetPreload(u8 preloadValue);
void TMR0_OV_SetCallBack(void (*pf)(void));

void TMR0_CTC_Init(OC0_CTC_MODE OC0_State, u8 OCR0_Value);
void TMR0_CTC_SetCallBack(void (*pf)(void));

void TMR0_FastPWM(OC0_Fast_Mode OC0_State,u8 DutyCylce);

void TMR0_PhasePWM(OC0_Fast_Mode OC0_State,u8 DutyCylce);

u8 TMR0_ReadTCNT(void);


/*TIMER2*/
void TMR2_OVF_Init(void);
void TMR2_SetPreload(u8 preloadValue);
void TMR2_OV_SetCallBack(void (*pf)(void));

void TMR2_CTC_Init(OC0_CTC_MODE OC0_State, u8 OCR2_Value);
void TM2_CTC_SetCallBack(void (*pf)(void));

void TMR2_FastPWM(OC0_Fast_Mode OC0_State,u8 DutyCylce);

void TMR2_PhasePWM(OC0_Fast_Mode OC0_State,u8 DutyCylce);
u8 TMR2_ReadTCNT(void);





/* Timer 0 preScaler value*/
#define TMR0_NO_CLOCK_SOURCE               0b000
#define TMR0_NO_PRESCALING                 0b001
#define TMR0_PRESCALER_8                   0b010
#define TMR0_PRESCALER_64                  0b011
#define TMR0_PRESCALER_256                 0b100
#define TMR0_PRESCALER_1024                0b101
#define TMR0_EXTRNAL_CLK_FALLING_EDGE      0b110
#define TMR0_EXTRNAL_CLK_RISING_EDGE       0b111

/* Timer 2 preScaler value*/
#define TMR2_NO_CLOCK_SOURCE               0b000
#define TMR2_NO_PRESCALING                 0b001
#define TMR2_PRESCALER_8                   0b010
#define TMR2_PRESCALER_32                  0b011
#define TMR2_PRESCALER_64                  0b100
#define TMR2_PRESCALER_128                 0b101
#define TMR2_PRESCALER_256 		 	       0b110
#define TMR2_PRESCALER_1024			       0b111





#endif /* MCAL_TMR_DRIVER_TMR_MCAL_INTERFACE_H_ */
