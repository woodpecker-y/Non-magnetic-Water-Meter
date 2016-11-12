/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：main.c
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include "includes.h"

uint32_t WaterVolume;
 void main(void)
{
 	MSP430_Init();
	_EINT();
	WaterVolume = 0;
//    Write_WaterVolume();
//	LCD_Test(1);
//   Read_WaterVolume();
	while(1)
	{
//		Motor_Open();
		LPM3;
		Frame_Work();
	}
}

#ifdef BASICTIMER_H_
#pragma vector=BASICTIMER_VECTOR
__interrupt void BT_IRQ(void)
{
	LCD_DisplayWaterVolume();
	LCD_T2(CMPA_Read_CAOUT() );
	LCDM9 ^= 0x08;
}
#endif
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：__interrupt void CMP_ISR(void)
 * 功能：比较器A中断服务程序，关闭电机
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：复制该段至main文件
---------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifdef COMPARATOR_A_H_
#pragma	vector = COMPARATORA_VECTOR
__interrupt void CMP_ISR(void)
{
	Motor_Stop();
}
#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：__interrupt void CMP_ISR(void)
 * 功能：比较器A中断服务程序，关闭电机
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：复制该段至main文件
---------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifdef SCANIF_H_
#pragma vector = SCANIF_VECTOR
__interrupt void ScanIF_ISR(void)
{
	if( (SIFCTL1 & SIFIE3) && (SIFCTL1 & SIFIFG3) )
	{
		SIFCTL1 &= ~SIFIFG3;
		WaterVolume ++;
		LCD_DisplayWaterVolume();
		LCD_DIR_RIGHT();
	}
	if( (SIFCTL1 & SIFIE4) && (SIFCTL1 & SIFIFG4) )
	{
		SIFCTL1 &= ~SIFIFG4;
		WaterVolume --;
		LCD_DisplayWaterVolume();
		LCD_DIR_LEFT();
	}
	if(WaterVolume > 99999999)
		WaterVolume = 0;
}
#endif
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：__interrupt void Timer_A(void)
 * 功能：Timer_A中断服务程序，作为串口波特率发生器使用
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：当定义了FRAME_H_头文件时，可以接收数据帧
---------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifdef UART_H_
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	TACCR0 += BitTime;
	if(TACCTL0 & CCIS_1)
	//RX
	{
//		TACTL = (TASSEL_1+MC_2);						 			//add
		if(TACCTL0 & CAP)
		{
			TACCTL0 &=~CAP;
			TACCR0 += BitTime_5;
		}
		else
		{

		      if(BitCnt == 0)
		      {
		      	TACCTL0 &= ~CCIE;
//		      	TACTL = (TASSEL_1+MC_0);							//add
		 //---------------------------------------------
#ifdef	 FRAME_H_
		      	extern uint8_t stepFlag;
		      	Frame_Get();
		      	RX_Ready();
		      	if(stepFlag == STEP_END2)
		      		LPM3_EXIT;
#else
		 //--------------------------------------------
		      	LPM3_EXIT;
#endif
		      }
		      else
		      {
		    	  RXTXData = RXTXData >> 1;
				  if(TACCTL0&SCCI)
					  RXTXData |= 0x80;
				  BitCnt--;
		      }
		}
	}
	else
	//TX
	{
		if(BitCnt == 0)
		{
			TACCTL0 &= ~CCIE;
//			TACTL = (TASSEL_1+MC_0);								//add
		}
		else
		{
//-1-begin--------------------------------------------------------------------------------------------------------------------
//======================================================================
//修改内容： 修改为反向，在使用MBUS时取反，再经过一次取反得正。上为原始,下为修改，原始可直接用于PC通讯。
//修改时间：2015/4/1
//修改人：李超
//======================================================================
#if 1
			if(RXTXData & 0X01)									//如果最低位为高
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_1; 						//设置模式1：set
			}
			else
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_5; 						//设置模式5：reset
			}
#else
			if(RXTXData & 0X01)									//如果最低位为高
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_5; 						//设置模式5：reset
			}
			else
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_1; 						//设置模式1：set
			}
#endif
//-1-end--------------------------------------------------------------------------------------------------------------------------
			RXTXData = RXTXData >> 1;						//收发缓冲器右移一位
			BitCnt --;													//发送位计数减一
		}
	}
}
#endif
/*-----------------------------------------------------------------------------------------------------------------------*/
