/*
 * LCD_HAL_Interface.h
 *
 *  Created on: Oct 4, 2023
 *      Author: Lenovo
 */

#ifndef HAL_LCD_DRIVER_LCD_HAL_INTERFACE_H_
#define HAL_LCD_DRIVER_LCD_HAL_INTERFACE_H_

void LCD_Init(void);
u8 LCD_SendCommand(u8 cmd);
void LCD_SendChar(u8 Char);
u8 LCD_SendString(u8* string);
u8 LCD_SetPosition(u8 Line, u8 Col);
u8 LCD_SendNumber(s32 Num);
u8 LCD_SendFloatNumber(float num, u8 DecimalPlaces);
u8 LCD_GenerateSpecialChar(u8* Pattern, u8 CGROM_INDEX);
u8 LCD_DisplaySpecialChar(u8 CGRAM_INDEX, u8 LineNum, u8 CharNum);
u8 LCD_ClearDisplay(void);

#define LCD_LINE_1	1
#define LCD_LINE_2	2

#define LCD_COL_0	0
#define LCD_COL_1	1
#define LCD_COL_2	2
#define LCD_COL_3	3
#define LCD_COL_4	4
#define LCD_COL_5	5
#define LCD_COL_6	6
#define LCD_COL_7	7
#define LCD_COL_8	8
#define LCD_COL_9	9
#define LCD_COL_10	10
#define LCD_COL_11	11
#define LCD_COL_12	12
#define LCD_COL_13	13
#define LCD_COL_14	14
#define LCD_COL_15	15

#define NOT_PRESSED = 0b1111111

#define CLR_DISP		0x01
#define RETURN_HOME		0x02
#define EntryMode		0x06
#define DISPLAY_Control 0b00001100
//#define DISPLAY_Control 0x0f//for Display on cursor on and blinks on
#define FunctionSet		0x38

#define Cursor_Off		0b00010100

#endif /* HAL_LCD_DRIVER_LCD_HAL_INTERFACE_H_ */
