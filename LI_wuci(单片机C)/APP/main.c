/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����main.c
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
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
 * ���ƣ�__interrupt void CMP_ISR(void)
 * ���ܣ��Ƚ���A�жϷ�����򣬹رյ��
 * ���룺��
 * �������
 * ���ߣ��
 * �汾��1.0
 * ��ע�����Ƹö���main�ļ�
---------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifdef COMPARATOR_A_H_
#pragma	vector = COMPARATORA_VECTOR
__interrupt void CMP_ISR(void)
{
	Motor_Stop();
}
#endif

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ���ƣ�__interrupt void CMP_ISR(void)
 * ���ܣ��Ƚ���A�жϷ�����򣬹رյ��
 * ���룺��
 * �������
 * ���ߣ��
 * �汾��1.0
 * ��ע�����Ƹö���main�ļ�
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
 * ���ƣ�__interrupt void Timer_A(void)
 * ���ܣ�Timer_A�жϷ��������Ϊ���ڲ����ʷ�����ʹ��
 * ���룺��
 * �������
 * ���ߣ��
 * �汾��1.0
 * ��ע����������FRAME_H_ͷ�ļ�ʱ�����Խ�������֡
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
//�޸����ݣ� �޸�Ϊ������ʹ��MBUSʱȡ�����پ���һ��ȡ����������Ϊԭʼ,��Ϊ�޸ģ�ԭʼ��ֱ������PCͨѶ��
//�޸�ʱ�䣺2015/4/1
//�޸��ˣ��
//======================================================================
#if 1
			if(RXTXData & 0X01)									//������λΪ��
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_1; 						//����ģʽ1��set
			}
			else
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_5; 						//����ģʽ5��reset
			}
#else
			if(RXTXData & 0X01)									//������λΪ��
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_5; 						//����ģʽ5��reset
			}
			else
			{
				TACCTL0 = (TACCTL0&~OUTMOD_7)|OUTMOD_1; 						//����ģʽ1��set
			}
#endif
//-1-end--------------------------------------------------------------------------------------------------------------------------
			RXTXData = RXTXData >> 1;						//�շ�����������һλ
			BitCnt --;													//����λ������һ
		}
	}
}
#endif
/*-----------------------------------------------------------------------------------------------------------------------*/
