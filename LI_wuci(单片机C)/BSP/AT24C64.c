/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����Frame.h
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "AT24C64.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ���ƣ�void I2C_24C64_Init(void)
 * ���ܣ�AT24C64��ʼ��
 * ���룺��
 * �������
 * ���ߣ��
 * �汾��1.0
 * ��ע��
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void I2C_24C64_Init(void)
{
	I2C_Init();
	I2C_WP_H();
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ���ƣ�unsigned char I2C_24C64_Write(unsigned int addr,unsigned char *pdate,unsigned char len)
 * ���ܣ����ƶ���ַд������
 * ���룺unsigned int addr��	E2PROM���ڲ���ַ
 * 			unsigned char *pdate��	Ҫд�����ݵ��׵�ַ
 *			unsigned char len��	Ҫд����ַ���
 * �����unsigned char��������0����������1
 * ���ߣ��
 * �汾��1.0
 * ��ע��
---------------------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char I2C_24C64_Write(unsigned int addr,unsigned char *pdate,unsigned char len)
{
	unsigned char i;
	I2C_WP_H();
	Delay_I2C(1000);
	I2C_Start();
	if(I2C_WriteByte(AT24C64_ADDR_WRITE) == 0)
	{
		I2C_Stop();
		return 0;
	}
	if(I2C_WriteByte(addr>>8) == 0)
	{
		I2C_Stop();
		return 0;
	}
	if(I2C_WriteByte(addr&0xff) == 0)
	{
		I2C_Stop();
		return 0;
	}
	for(i=0;i<len;i++)
	{
		if(I2C_WriteByte(pdate[i]) == 0)
		{
			I2C_Stop();
			return 0;
		}
	}
	I2C_Stop();
	Delay_I2C(1000);
	I2C_WP_L();
	return 1;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * ���ƣ�unsigned char I2C_24C64_Read(unsigned int addr,unsigned char *pdate,unsigned char len)
 * ���ܣ����ƶ���ַ������
 * ���룺��unsigned int addr��	E2PROM���ڲ���ַ
 * 			unsigned char *pdate��	�������ݵ��׵�ַ
 *			unsigned char len��	Ҫ���յ��ַ���
 * �����unsigned char��������0����������1
 * ���ߣ��
 * �汾��1.0
 * ��ע��
---------------------------------------------------------------------------------------------------------------------------------------------------*/
unsigned char I2C_24C64_Read(unsigned int addr,unsigned char *pdate,unsigned char len)
{
	unsigned char i;
	I2C_WP_H();
	Delay_I2C(1000);
	I2C_Start();
	if(I2C_WriteByte(AT24C64_ADDR_WRITE) == 0)
	{
		I2C_Stop();
		return 0;
	}
	if(I2C_WriteByte(addr>>8) == 0)
	{
		I2C_Stop();
		return 0;
	}
	if(I2C_WriteByte(addr&0xff) == 0)
	{
		I2C_Stop();
		return 0;
	}
	I2C_Start();
	if(I2C_WriteByte(AT24C64_ADDR_READ) == 0)
	{
		I2C_Stop();
		return 0;
	}
	for(i=0;i<len-1;i++)
	{
		pdate[i] = I2C_ReadByte();
		I2C_ACK();
	}
	pdate[i] = I2C_ReadByte();
	I2C_NoACK();
	I2C_Stop();
	Delay_I2C(1000);
	I2C_WP_L();
	return 1;
}
