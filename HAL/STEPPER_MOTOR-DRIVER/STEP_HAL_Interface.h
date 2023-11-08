/*
 * STEP_HAL_Interface.h
 *
 *  Created on: Oct 8, 2023
 *      Author: Lenovo
 */

#ifndef HAL_STEPPER_MOTOR_DRIVER_STEP_HAL_INTERFACE_H_
#define HAL_STEPPER_MOTOR_DRIVER_STEP_HAL_INTERFACE_H_


void STEP_NoOfSteps(u32 No, u8 Wise);
void STEP_NoOfRev(u32 Rev, u8 Wise);

#define CLOCKWISE 	0U
#define ACLOCKWISE	1U

#endif /* HAL_STEPPER_MOTOR_DRIVER_STEP_HAL_INTERFACE_H_ */
