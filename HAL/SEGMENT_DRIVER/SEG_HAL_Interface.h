/*
 * SEG_HAL_Interface.h
 *
 *  Created on: Oct 5, 2023
 *      Author: Lenovo
 */

#ifndef HAL_SEGMENT_DRIVER_SEG_HAL_INTERFACE_H_
#define HAL_SEGMENT_DRIVER_SEG_HAL_INTERFACE_H_


u8 SEG_Init(u8 Port);
u8 SEG_DispalyNum(u8 Port,u8 Num);

#define CATHODE 1
#define ANODE	0

#endif /* HAL_SEGMENT_DRIVER_SEG_HAL_INTERFACE_H_ */
