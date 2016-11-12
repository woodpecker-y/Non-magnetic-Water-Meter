/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：LCD.c
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "LCD.h"
//液晶字符段码
												/*0     1      2     3      4      5      6      7      8      9     a      b     c     d     e       f     -     空*/
unsigned char  segTable[18] ={0xaF,0xa0,0xcb,0xe9,0xe4,0x6d,0x6F,0xa8,0xeF,0xed,0xee,0x67,0x0f,0xe3,0x4f,0x4e,0x40,0x00};
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：void LCD_Init(void)
 * 功能：液晶模块初始化
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：BTCTL  = BT_fLCD_DIV128;   fLCD = fACLK:128 无闪烁感，换成256分频是有闪烁感
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void LCD_Init(void)
{
	P5SEL |= 0xff;									//COM端第二功能使能
	BTCTL |= BT_fLCD_DIV128;                /* fLCD = fACLK:128*/
	LCDCTL = 0x5d;								// S0-S19,4-mux,enable
	/*--用到20个数据线，4个COM端，所以需要10个寄存器，寄存器全部清零-------*/
	LCDM1 = 0x00;
	LCDM2 = 0x00;
	LCDM3 = 0x00;
	LCDM4 = 0x00;
	LCDM5 = 0x00;
	LCDM6 = 0x00;
	LCDM7 = 0x00;
	LCDM8 = 0x00;
	LCDM9 = 0x00;
	LCDM10 = 0x00;
	LCDCTL |= LCDSON;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：void LCD_Test(unsigned char num)
 * 功能：测试程序，左右箭头交替闪烁，用于指示程序正确运行
 * 输入：unsigned char num：未使用，可以选择使用
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void LCD_Test(unsigned char num)
{
	uint32_t i;
	LCD_DIR_LEFT();
  	for (i = 0; i < 10000; i++);
	LCD_DIR_RIGHT();
	for (i = 0; i < 10000; i++);
}

