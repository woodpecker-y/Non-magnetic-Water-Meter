/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����DISPLAY.h
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
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
