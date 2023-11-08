/*
 * TMR_MCAL_Config.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_TMR_DRIVER_TMR_MCAL_CONFIG_H_
#define MCAL_TMR_DRIVER_TMR_MCAL_CONFIG_H_


/*choose the preScaler
 * 1-TMR0_NO_CLOCK_SOURCE
   2-TMR0_NO_PRESCALING
   3-TMR0_PRESCALER_8
   4-TMR0_PRESCALER_64
   5-TMR0_PRESCALER_256
   6-TMR0_PRESCALER_1024
   7-TMR0_EXTRNAL_CLK_FALLING_EDGE
   8-TMR0_EXTRNAL_CLK_RISING_EDGE
  */

#define TMR0_PreScalar_Value            TMR0_PRESCALER_1024
/*
 * 1-TMR2_NO_CLOCK_SOURCE               0b000
 * 2-TMR2_NO_PRESCALING                 0b001
 * 3-TMR2_PRESCALER_8                   0b010
 * 4-TMR2_PRESCALER_32                  0b011
 * 5-TMR2_PRESCALER_64                  0b100
 * 6-TMR2_PRESCALER_128                 0b101
 * 7-TMR2_PRESCALER_256 		 	    0b110
 * 8-TMR2_PRESCALER_1024			    0b111
*/
#define TMR2_PreScalar_Value            TMR2_PRESCALER_128




#endif /* MCAL_TMR_DRIVER_TMR_MCAL_CONFIG_H_ */
