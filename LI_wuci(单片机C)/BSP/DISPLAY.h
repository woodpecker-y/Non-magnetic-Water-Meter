/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：DISPLAY.h
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "includes.h"
#include "stdio.h"
void LCD_DisplayS1S2(void);
void LCD_DisplayCNT1(void);
void LCD_DisplayCNT2(void);


void LCD_DisplayCNT1_10(void);
void LCD_DisplayCNT2_10(void);
void LCD_DisplayS1S2_78(void);

void LCD_DisplayWaterVolume(void);
#endif /* DISPLAY_H_ */
