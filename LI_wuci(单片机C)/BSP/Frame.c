/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：Frame.c
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
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
 * 名称：void Frame_Get(void)
 * 功能：数据帧获取
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void Frame_Get(void)
{
	unsigned char RxTxget;											//定义一个接收字符
	RxTxget = RXTXData;												//接收收发缓冲区的数据
	switch(stepFlag)													//判断当前状态
	{
		case STEP_HEAD1:												//如果处在STEP_HEAD1
		{
			if(RxTxget == 0x68)											//判断收到的字符是不是0x68
				stepFlag = STEP_HEAD2;									//是则进入下一状态
			else																//否则
				stepFlag = STEP_HEAD1;									//回到初始状态
		}
			break;															//结束
		case STEP_HEAD2:												//如果处在STEP_HEAD2
		{
			if(RxTxget == 0x86)											//判断收到的字符是不是0x86
			{
				stepFlag = STEP_DATA;									//是则进入下一状态
				RxTx_Buffer.cnt = 0;										//接收计数清零
			}
			else																//否则
				stepFlag = STEP_HEAD1;									//回到状态初始
		}
			break;
		case STEP_DATA:												//如果处在STEP_DATA
		{
			RxTx_Buffer.buffer[RxTx_Buffer.cnt] = RxTxget;		//把接收到的字符写入到缓冲区里面
			RxTx_Buffer.cnt++;												//计数加一
			if(RxTx_Buffer.cnt == 8)										//如果收到8个字符
				stepFlag = STEP_END1;											//进入下一状态
		}
			break;																//结束
		case STEP_END1:												//如果处在STEP_END1
		{
			if(RxTxget == 0x80)												//如果接收到的字符是0x80
			{
				stepFlag = STEP_END2;										//进入下一状态
			}
			else
			{
				stepFlag = STEP_HEAD1;										//否则退回初始状态
				RxTx_Buffer.cnt = 0;											//计数器清零
			}
		}
			break;
		default:																//其他情况
			stepFlag = STEP_HEAD1;										//退回初始状态
			break;
	}
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：void Frame_Work(void)
 * 功能：数据帧处理函数
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void Frame_Work(void)
{
	switch(RxTx_Buffer.buffer[0])									//电机控制
	{
		case 0x10:															//关闭
			Motor_Close();
			break;
		case 0x20:															//打开
			Motor_Open();
			break;
		case 0x30:															//停止
			Motor_Stop();
			break;
		default:
			break;
	}
	switch(RxTx_Buffer.buffer[1])										//液晶开关
	{
		case 0x10:															//打开
			LCDCTL |= LCDSON;
			break;
		case 0x20:															//关闭
			LCDCTL &= ~LCDSON;
			break;
	}
	switch(RxTx_Buffer.buffer[2])									//读数
	{
		case 0x40:															//读取
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
		case 0x60:																//设置
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
	switch(RxTx_Buffer.buffer[3])										//存储E2PROM
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
