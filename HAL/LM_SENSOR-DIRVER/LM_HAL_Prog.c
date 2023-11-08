/*
 * LM_HAL_Prog.c
 *
 *  Created on: Oct 15, 2023
 *      Author: Lenovo
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/ADC-DRIVER/ADC_MCAL_Interface.h"
#include "../../HAL/LCD-DRIVER/LCD_HAL_Interface.h"
#include "LM_HAL_Config.h"
#include "LM_HAL_Interface.h"
#include <avr/delay.h>
f32 LM_GetTemp(u8 Channel)
{
    u16 adc_value = 0;
    f32 voltage = 0, temp = 0;
    adc_value = ADC_GetResult(Channel);

    // Calculate voltage based on ADC value and reference voltage
    voltage = ((f32)adc_value *2.56 ) /1023.0;

    // LM35 sensitivity is 10 mV per degree Celsius
    temp = voltage / 0.01;  // Assuming 10 mV per degree Celsius

    return temp;
}


