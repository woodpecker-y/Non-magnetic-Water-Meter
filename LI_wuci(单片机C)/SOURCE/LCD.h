/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：LCD.h
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef LCD_H_
#define LCD_H_

#include <msp430.h>
#include <stdint.h>

extern unsigned char  segTable[18];

#define		ON		1
#define		OFF		0
/*--液晶数字显示，1-8个数码管，可以显示0-f的数字*/
#define		LCD_NUM1(a)		LCDM2 = (LCDM2&0x0f)|(segTable[a]&0xf0);LCDM3 = (LCDM3&0xf0)|(segTable[a]&0x0f)
#define		LCD_NUM2(a)		LCDM1 = (LCDM1&0x0f)|(segTable[a]&0xf0);LCDM2 = (LCDM2&0xf0)|(segTable[a]&0x0f)
#define		LCD_NUM3(a)		LCDM3 = (LCDM3&0x0f)|(segTable[a]&0xf0);LCDM1 = (LCDM1&0xf0)|(segTable[a]&0x0f)
#define		LCD_NUM4(a)		LCDM4 = segTable[a]
#define		LCD_NUM5(a)		LCDM5 = segTable[a]
#define		LCD_NUM6(a)		LCDM6 = segTable[a]
#define		LCD_NUM7(a)		LCDM7 = segTable[a]
#define		LCD_NUM8(a)		LCDM8 = segTable[a]

/*--P1到P12*/
#define		LCD_P1(a)				if(a) LCDM4 |= 0x10;else LCDM4 &= (~0x10);
#define		LCD_P2(a)				if(a) LCDM5 |= 0x10;else LCDM5 &= (~0x10);
#define		LCD_P3(a)				if(a) LCDM6 |= 0x10;else LCDM6 &= (~0x10);
#define		LCD_P4(a)				if(a) LCDM7 |= 0x10;else LCDM7 &= (~0x10);
#define		LCD_P5(a)				if(a) LCDM2 |= 0x10;else LCDM2 &= (~0x10);
#define		LCD_P6(a)				if(a) LCDM1 |= 0x10;else LCDM1 &= (~0x10);
#define		LCD_P7(a)				if(a) LCDM3 |= 0x10;else LCDM3 &= (~0x10);
#define		LCD_P8(a)				if(a) LCDM10 |= 0x10;else LCDM10 &= (~0x10);
#define		LCD_P9(a)				if(a) LCDM10 |= 0x20;else LCDM10 &= (~0x20);
#define		LCD_P10(a)			if(a) LCDM10 |= 0x40;else LCDM10 &= (~0x40);
#define		LCD_P11(a)			if(a) LCDM10 |= 0x08;else LCDM10 &= (~0x08);
#define		LCD_P12(a)			if(a) LCDM10 |= 0x04;else LCDM10 &= (~0x04);

/*--T1到T11*/
#define		LCD_T1(a)				if(a) LCDM9 |= 0x08;else  LCDM9 &= (~0x08);
#define		LCD_T2(a)				if(a) LCDM9 |= 0x80;else  LCDM9 &= (~0x80);
#define		LCD_T3(a)				if(a) LCDM9 |= 0x04;else  LCDM9 &= (~0x04);
#define		LCD_T4(a)				if(a) LCDM9 |= 0x02;else  LCDM9 &= (~0x02);
#define		LCD_T5(a)				if(a) LCDM9 |= 0x01;else  LCDM9 &= (~0x01);
#define		LCD_T6(a)				if(a) LCDM9 |= 0x40;else  LCDM9 &= (~0x40);
#define		LCD_T7(a)				if(a) LCDM8 |= 0x10;else  LCDM8 &= (~0x10);
#define		LCD_T8(a)				if(a) LCDM9 |= 0x20;else  LCDM9 &= (~0x20);
#define		LCD_T9(a)				if(a) LCDM9 |= 0x10;else  LCDM9 &= (~0x10);
#define		LCD_T10(a)			if(a) LCDM10 |= 0x02;else  LCDM10 &= (~0x02);
#define		LCD_T11(a)			if(a) LCDM10 |= 0x01;else  LCDM10 &= (~0x01);

/*--显示左右标识符，当一个显示时另一个关闭*/
#define		LCD_DIR_LEFT()			LCDM10 = (LCDM10&0xfc)|0x01
#define		LCD_DIR_RIGHT()		LCDM10 = (LCDM10&0xfc)|0x02

void LCD_Init(void);
void LCD_Test(unsigned char num);


#endif /* LCD_H_ */
