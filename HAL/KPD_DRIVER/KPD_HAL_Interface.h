/*
 * KPD_HAL_Interface.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Lenovo
 */

#ifndef HAL_KPD_KPD_HAL_INTERFACE_H_
#define HAL_KPD_KPD_HAL_INTERFACE_H_

#define KPD_NOTPRESSED 0b11111111

void KPD_Init(void);
u8 KPD_GetKey(void);
#endif /* HAL_KPD_KPD_HAL_INTERFACE_H_ */
