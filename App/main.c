/*
 * main.c
 *
 *  Created on: Oct 3, 2023
 *      Author: Lenovo
 */

#include <util/delay.h>.
#include <avr/interrupt.h>

#define F_CPU 8000000UL
#include "../MCAL/DIO-DRIVER/DIO_MCAL_Interface.h"
#include "../MCAL/GIE-DRIVER/GIE_MCAL_Interface.h"
#include "../MCAL/EXTI-DRIVER/EXTI_MCAL_Interface.h"
#include "../MCAL/ADC-DRIVER/ADC_MCAL_Interface.h"
#include "../MCAL/TMR-DRIVER/TMR_MCAL_Interface.h"
#include "../MCAL/USART-DRIVER/USART_MCAL_Interface.h"

#include "../HAL/LCD-DRIVER/LCD_HAL_Interface.h"
#include "../HAL/SEGMENT_DRIVER/SEG_HAL_Interface.h"
#include "../HAL/KPD_DRIVER/KPD_HAL_Interface.h"
#include "../HAL/LM_SENSOR-DIRVER/LM_HAL_Interface.h"
#include "../HAL/STEPPER_MOTOR-DRIVER/STEP_HAL_Interface.h"

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

static u8 counter = 0;
void fun(void);
int main() {
	DIO_SetPortDirection(DIO_PORTA, DIO_OUTPUT);
	DIO_SetPortDirection(DIO_PORTB, DIO_OUTPUT);
	DIO_SetPortDirection(DIO_PORTC, DIO_OUTPUT);
	u8 x = 0;
	u8 i = 0;
	u8 is_entered_three_times = 0; //1 correct 0 wrong
	u16 value = 0;
	u8 digit_count = 0;
	u8 choose_count = 0;
	u8 correct_flag = 0;
	u8 exit_flag = 0;
	LCD_Init();
	KPD_Init();
	LCD_SendString("Password : ");
	while (1) {
		LCD_SetPosition(1, 0);
		x = KPD_GetKey();
		if (x != 0b11111111) {
			if (x >= '0' && x <= '9') {
				if (digit_count < 4) //to only enter f digit password
						{
					LCD_SetPosition(1, i);
					i++;
					LCD_SendChar(x);
					value = value * 10 + (x - '0');
					digit_count++;
				}
			}
			if (x == '=') {
				if (value == 1234) {
					LCD_ClearDisplay();
					LCD_SendString("correct");
					correct_flag = 1;
				} else {
					is_entered_three_times++;

					if (is_entered_three_times == 1) {
						LCD_ClearDisplay();
						LCD_SendString("Wrong");
						LCD_SetPosition(1, 0);
						LCD_SendString("2 Times Left");
						digit_count = 0;
					}
					if (is_entered_three_times == 2) {
						LCD_ClearDisplay();
						LCD_SendString("Wrong");
						LCD_SetPosition(1, 0);
						LCD_SendString("1 Times Left");
						digit_count = 0;
					}
					_delay_ms(1000);
					LCD_ClearDisplay();
					x = 0;
					value = 0;
					i = 0;
					LCD_SendString("Password : ");
				}
			}
			if (is_entered_three_times == 3) {
				LCD_ClearDisplay();
				LCD_SendString("Wrong Trials");
				_delay_ms(1000);
				LCD_ClearDisplay();
				LCD_SendString("Closing....");
				_delay_ms(1000);
				LCD_ClearDisplay();
				break;
			}
			if (x == 'c') {
				LCD_ClearDisplay();
				x = 0;
				value = 0;
				i = 0;
				LCD_SendString("Password : ");
			}
		}
		if (correct_flag && exit_flag == 0) {
			value = 0;
			_delay_ms(1000);
			LCD_ClearDisplay();
			LCD_SendString("1-LedOff");
			LCD_SetPosition(0, 9);
			LCD_SendString("2-LedOn");
			LCD_SetPosition(1, 0);
			LCD_SendString("3-MCw");
			LCD_SetPosition(1, 9);
			LCD_SendString("4-MCCw");
			while (1) {
				x = KPD_GetKey();
				if (x != 0b11111111) {
					if (x > '0' && x <= '9') {
						if (choose_count < 1) //only one digit to enter
								{
							LCD_ClearDisplay();
							value = value * 10 + (x - '0');
						}
						switch (value) {
						case 1:
							DIO_SetPinValue(DIO_PORTC, DIO_PIN0, DIO_LOW);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN1, DIO_LOW);
							break;
						case 2:
							DIO_SetPinValue(DIO_PORTC, DIO_PIN0, DIO_HIGH);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN1, DIO_HIGH);
							break;
						case 3:
							DIO_SetPinValue(DIO_PORTC, DIO_PIN2, DIO_LOW);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_LOW);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN2, DIO_LOW);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_HIGH);
							break;
						case 4:
							DIO_SetPinValue(DIO_PORTC, DIO_PIN2, DIO_LOW);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_LOW);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN2, DIO_HIGH);
							DIO_SetPinValue(DIO_PORTC, DIO_PIN3, DIO_LOW);
							break;
						default:
							LCD_ClearDisplay();
							LCD_SendString("Wrong Value");
							_delay_ms(1000);
							LCD_ClearDisplay();
							break;
						}
					}
					LCD_SendString("c-Menu");
					LCD_SetPosition(1,0);
					LCD_SendString("0-Close");
					if (x == 'c') {
						LCD_ClearDisplay();
						x = 0;
						value = 0;
						choose_count = 0; // Reset choose count
						LCD_SendString("1-LedOff");
						LCD_SetPosition(0, 9);
						LCD_SendString("2-LedOn");
						LCD_SetPosition(1, 0);
						LCD_SendString("3-MCw");
						LCD_SetPosition(1, 9);
						LCD_SendString("4-MCCw");
					}
					if(x == '0')
					{
						LCD_ClearDisplay();
						LCD_SendString("Closing....");
						DIO_SetPortValue(DIO_PORTC,DIO_PORT_LOW);
						_delay_ms(1000);
						LCD_ClearDisplay();
						exit_flag = 1;
						break;
					}
				}
			}
		}

	}
	return 0;

}

