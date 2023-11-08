/*
 * GIE_MCAL_Prog.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Lenovo
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "GIE_MCAL_Config.h"
#include "GIE_MCAL_Interface.h"
#include "GIE_MCAL_Private.h"

void GIE_Enable(void)
{
	SET_BIT(SREG_REG, GIE_PIN);
}
void GIE_Disable(void)
{
	CLR_BIT(SREG_REG, GIE_PIN);
}
