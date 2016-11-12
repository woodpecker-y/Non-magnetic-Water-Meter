/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����Frame.c
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "Frame.h"
typedef struct
{
	char buffer[10];
	uint8_t cnt;
}Buffertypedef;
Buffertypedef RxTx_Buffer={0};

uint8_t stepFlag =  1;
extern uint32_t WaterVolume;
uint8_t I2Cbuff[4];
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ���ƣ�void Frame_Get(void)
 * ���ܣ�����֡��ȡ
 * ���룺��
 * �������
 * ���ߣ��
 * �汾��1.0
 * ��ע��
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void Frame_Get(void)
{
	unsigned char RxTxget;											//����һ�������ַ�
	RxTxget = RXTXData;												//�����շ�������������
	switch(stepFlag)													//�жϵ�ǰ״̬
	{
		case STEP_HEAD1:												//�������STEP_HEAD1
		{
			if(RxTxget == 0x68)											//�ж��յ����ַ��ǲ���0x68
				stepFlag = STEP_HEAD2;									//���������һ״̬
			else																//����
				stepFlag = STEP_HEAD1;									//�ص���ʼ״̬
		}
			break;															//����
		case STEP_HEAD2:												//�������STEP_HEAD2
		{
			if(RxTxget == 0x86)											//�ж��յ����ַ��ǲ���0x86
			{
				stepFlag = STEP_DATA;									//���������һ״̬
				RxTx_Buffer.cnt = 0;										//���ռ�������
			}
			else																//����
				stepFlag = STEP_HEAD1;									//�ص�״̬��ʼ
		}
			break;
		case STEP_DATA:												//�������STEP_DATA
		{
			RxTx_Buffer.buffer[RxTx_Buffer.cnt] = RxTxget;		//�ѽ��յ����ַ�д�뵽����������
			RxTx_Buffer.cnt++;												//������һ
			if(RxTx_Buffer.cnt == 8)										//����յ�8���ַ�
				stepFlag = STEP_END1;											//������һ״̬
		}
			break;																//����
		case STEP_END1:												//�������STEP_END1
		{
			if(RxTxget == 0x80)												//������յ����ַ���0x80
			{
				stepFlag = STEP_END2;										//������һ״̬
			}
			else
			{
				stepFlag = STEP_HEAD1;										//�����˻س�ʼ״̬
				RxTx_Buffer.cnt = 0;											//����������
			}
		}
			break;
		default:																//�������
			stepFlag = STEP_HEAD1;										//�˻س�ʼ״̬
			break;
	}
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ���ƣ�void Frame_Work(void)
 * ���ܣ�����֡������
 * ���룺��
 * �������
 * ���ߣ��
 * �汾��1.0
 * ��ע��
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void Frame_Work(void)
{
	switch(RxTx_Buffer.buffer[0])									//�������
	{
		case 0x10:															//�ر�
			Motor_Close();
			break;
		case 0x20:															//��
			Motor_Open();
			break;
		case 0x30:															//ֹͣ
			Motor_Stop();
			break;
		default:
			break;
	}
	switch(RxTx_Buffer.buffer[1])										//Һ������
	{
		case 0x10:															//��
			LCDCTL |= LCDSON;
			break;
		case 0x20:															//�ر�
			LCDCTL &= ~LCDSON;
			break;
	}
	switch(RxTx_Buffer.buffer[2])									//����
	{
		case 0x40:															//��ȡ
			TX_Byte(0x86);
			TX_Byte(0x68);
			TX_Byte(WaterVolume>>24);
			TX_Byte(WaterVolume>>16);
			TX_Byte(WaterVolume>>8);
			TX_Byte(WaterVolume);
			TX_Byte(0x08);
			/*
			TX_Byte(WaterVolume/10000000 + '0');
			TX_Byte(WaterVolume/1000000%10 + '0');
			TX_Byte(WaterVolume/100000%10 + '0');
			TX_Byte(WaterVolume/10000%10 + '0');
			TX_Byte(WaterVolume/1000%10 + '0');
			TX_Byte(WaterVolume/100%10 + '0');
			TX_Byte(WaterVolume/10%10 + '0');
			TX_Byte(WaterVolume%10 + '0');
			TX_Byte('\n');
			TX_Byte( '\0' );
			*/
			break;
		case 0x60:																//����
			WaterVolume = ((uint32_t)RxTx_Buffer.buffer[4]<<24) | ((uint32_t)RxTx_Buffer.buffer[5]<<16) | ((uint32_t)RxTx_Buffer.buffer[6]<<8) | ((uint32_t)RxTx_Buffer.buffer[7]);
			TX_Byte(0x86);
			TX_Byte(0x68);
			TX_Byte(WaterVolume>>24);
			TX_Byte(WaterVolume>>16);
			TX_Byte(WaterVolume>>8);
			TX_Byte(WaterVolume);
			TX_Byte(0x08);
			break;
	}
	switch(RxTx_Buffer.buffer[3])										//�洢E2PROM
	{
		case 0x90:
			Write_WaterVolume();
//			TX_String("Write OK\r\n");
			break;
		case 0xa0:
			Read_WaterVolume();
			TX_Byte(0x86);
			TX_Byte(0x68);
			TX_Byte(WaterVolume>>24);
			TX_Byte(WaterVolume>>16);
			TX_Byte(WaterVolume>>8);
			TX_Byte(WaterVolume);
			TX_Byte(0x08);
//			TX_String("Read OK\r\n");
			break;
	}

	stepFlag = STEP_HEAD1;
	memset(RxTx_Buffer.buffer,0,8);
}
void Write_WaterVolume(void)
{
	_DINT();
	I2Cbuff[0] = WaterVolume>>24 ;
	I2Cbuff[1] = WaterVolume>>16;
	I2Cbuff[2] = WaterVolume>>8;
	I2Cbuff[3] = WaterVolume;
	I2C_24C64_Write(0x01,I2Cbuff,4);
	_EINT();
	memset(I2Cbuff,55,4);
}

void Read_WaterVolume(void)
{
	_DINT();
	I2C_24C64_Read(0x01,I2Cbuff,4);
	WaterVolume = ((uint32_t)I2Cbuff[0]<<24) | ((uint32_t)I2Cbuff[1]<<16) | ((uint32_t)I2Cbuff[2]<<8) | ((uint32_t)I2Cbuff[3]);
	_EINT();
}
