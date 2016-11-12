/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：Comparator_A.c
 * 作者：李超
 * 时间：3015/3/19
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "ScanIF.h"
#define HYSTERESIS			5
#define SCANIF_CAL_INIT_VALUE		0x80
#define STATE_SEPERATION				15

/*
const unsigned char PSM[] = {
	0x00,  // no rotation
	0x01,  // turns right
	0x0C,  // turns left (-1)
	0x49,  // error
	0x00,  // turns left
	0x01,  // no rotation
	0x48,  // error
	0x09,  // turns right
	0x02,  // turns right (+1)
	0x41,  // error
	0x08,  // no rotation
	0x09,  // turns left
	0x40,  // error
	0x01,  // turns left
	0x08,  // turns right
	0x09   // no rotation
};
*/

const unsigned char PSM[] = {
	0x00,			// no rotation
	0x13,			//Change Direction
	0x0c,			//Turns Left (-1)
	0x4d,			//Error
	0x04,			//Turns Left (-1)
	0x01,			//No Rotation
	0x4c,			//Error
	0x1b,			//Change Direction
	0x12,			//Change Direction
	0x45,			//Error
	0x08,			//No Rotation
	0x0d,			//Turns Left (-1)
	0x44,			//Error
	0x05,			//Turns Left (-1)
	0x1a,			//Change Direction
	0x09,			//No Rotation
	0x10,			//No Rotation
	0x13,			//Turns Right (+1)
	0x0d,			//Change Direction
	0x5b,			//Error
	0x04,			//Change Direction
	0x11,			//No Rotation
	0x5a,			//Error
	0x1b,			//Turns Right (+1)
	0x12,			//Turns Right (+1)
	0x53,			//Error
	0x18,			//No Rotation
	0x0d,			//Change Direction
	0x52,			//Error
	0x05,			//Change Direction
	0x1a,			//Turns Right (+1)
	0x19			//No Rotation
};


void ScanIF_Init(void)
{
	uint32_t i;

/*--GPIO----*/
	P6SEL   |=   (BIT0|BIT1);
	P6DIR &=~(BIT0|BIT1);
/*--SIFTMSx*/
	SIFTSM0 = 0x8800;								//空闲状态，18 x SIFCLK
	SIFTSM1 = 0x002c;								//传感器1激励，1 x SIFCLK
	SIFTSM2 = 0x0424;								//延时，1 x ACLK（实际为：11.5 x SIFCLK）
	SIFTSM3 = 0x6934;								//打开DAC和比较器，13 x SIFCLK
	SIFTSM4 = 0x1974;								//输出，5 x SIFCLK，
	SIFTSM5 = 0x002d;							//传感器2激励，1 x SIFCLK
	SIFTSM6 = 0x0425;								//延时，	1 x ACLK(实际为10.5 x SIFCLK)
	SIFTSM7 = 0x6935;								//打开DAC和比较器，13 x SIFCLK
	SIFTSM8 = 0x1975;								//输出，5 x SIFCLK
	SIFTSM9 = 0x0220;								//结束，1 x SIFCLK
/*--SIFCTLx*/
	SIFCTL2 = 0x0150;
	for (i=0;i<=857;i++);				// wait loop. SIFVCCEx has to settle
	SIFCTL3 = 0x4500;					//原为0x4000,添加一个CNT1中断，改为0x4200
	SIFCTL4 = 0x53f0 ;					//原为0x73f0；
	SIFCTL5 = 0x0045;
/*--SIFDACRx*/
	SIFDACR0 = 0x295;  // SIFCH.0 - set to VCC/2
	SIFDACR1 = 0x28b;
	SIFDACR2 = 0x315;  // SIFCH.1 - set to VCC/2
	SIFDACR3 = 0x30b;

	SIFPSMV = (unsigned int) &PSM;		// Definition of PSM vector
	SIFCNT = SIFCNT;
//	SIFCTL1 = SIFEN;
	SIFCTL1 = SIFEN | SIFIE3 | SIFIE4;
//	ScanIF_Cal();
}

void ScanIF_Delay(void)
{
	uint16_t i;
	for(i = 50; i>0;i--);
}
void ScanIF_Cal(void)
{

	uint16_t step = 2,
			DAC1,DAC2,
			upperDAC1 = 0x0000,
			upperDAC2 = 0x0000,
			lowerDAC1 = 0x03ff,
			lowerDAC2 = 0x03ff,
			tempDAC;

	SIFDACR0 = 0x0200;  // SIFCH.0 - set to VCC/2
	SIFDACR1 = 0x0200;
	SIFDACR2 = 0x0200;  // SIFCH.1 - set to VCC/2
	SIFDACR3 = 0x0200;

//----------------------------------------------------------------------
//传感器1
//-----------------------------------------------------------------------
	do
	{
//--传感器1，从大到小--------------------------------------
		tempDAC = 0x03ff;
		do
		{
			ScanIF_Delay();
			SIFDACR0 = tempDAC;
			SIFDACR1 = tempDAC;
			if( (SIFCTL3 & SIF0OUT) == 0)
			{
				tempDAC -=step;
				if(tempDAC < 0x200)
				{
					tempDAC = 0x200;
				}
			}
			else
			{
				if(tempDAC >upperDAC1)
				{
					upperDAC1 = tempDAC;
				}
				break;
			}
		}while(1);
//--传感器1，从小到大--------------------------------------------
		tempDAC = 0x0200;

		do
		{
			ScanIF_Delay();
			SIFDACR0 = tempDAC;
			SIFDACR1 = tempDAC;
			if( (SIFCTL3 & SIF0OUT) == SIF0OUT )
			{
				tempDAC += step;
				if(tempDAC > 0x3ff)
				{
					tempDAC = 0x3ff;
				}
			}
			else
			{
				if(tempDAC < lowerDAC1)
					lowerDAC1 = tempDAC;
				break;
			}
		}while(1);
//--判断跳出条件-------------------------------------------------------------------
		tempDAC = 0x3ff;
		if( (upperDAC1 > lowerDAC1) && (upperDAC1 - lowerDAC1 > STATE_SEPERATION) )
			break;
	}while(1);

//----------------------------------------------------------------------
//传感器2
//-----------------------------------------------------------------------
	do
	{
	/*--传感器2，从大到小--------------------------------------*/
		tempDAC = 0x03ff;
		do
		{
			ScanIF_Delay();
			SIFDACR2 = tempDAC;
			SIFDACR3 = tempDAC;
			if( (SIFCTL3 & SIF1OUT) ==0)
			{
				tempDAC -=step;
				if(tempDAC < 0x200)  tempDAC = 0x200;
			}
			else
			{
				if(tempDAC >upperDAC2)
					upperDAC2 = tempDAC;
				break;
			}
		}while(1);
	/*--传感器2，从小到大--------------------------------------------*/
		tempDAC = 0x0200;
		do
		{
			ScanIF_Delay();
			SIFDACR2 = tempDAC;
			SIFDACR3 = tempDAC;
			if( (SIFCTL3 & SIF1OUT) == SIF0OUT )
			{
				tempDAC +=step;
				if(tempDAC > 0x3ff)	tempDAC = 0x3ff;
			}
			else
			{
				if(tempDAC < lowerDAC2)
					lowerDAC2 = tempDAC;
				break;
			}
		}while(1);
//--判断跳出条件-------------------------------------------------------------------
		tempDAC = 0x3ff;
		if( (upperDAC2 > lowerDAC2) && (upperDAC2 - lowerDAC2 > STATE_SEPERATION) )
			break;
	}while(1);
/*--end of loop*/
	DAC1 = (upperDAC1 + lowerDAC1)>>1;
	DAC2 = (upperDAC2 + lowerDAC2)>>1;
	SIFDACR0 = DAC1+ HYSTERESIS;
	SIFDACR1 = DAC1 - HYSTERESIS;
	SIFDACR2 = DAC2 + HYSTERESIS;
	SIFDACR3 = DAC2 - HYSTERESIS;
	tempDAC = 0x3ff;
	SIFCTL1 = SIFEN | SIFIE3 | SIFIE4;
}
