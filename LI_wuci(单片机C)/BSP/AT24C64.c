/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：Frame.h
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "AT24C64.h"

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：void I2C_24C64_Init(void)
 * 功能：AT24C64初始化
 * 输入：无
 * 输出：无
 * 作者：李超
 * 版本：1.0
 * 备注：
---------------------------------------------------------------------------------------------------------------------------------------------------*/
void I2C_24C64_Init(void)
{
	I2C_Init();
	I2C_WP_H();
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * 名称：unsigned char I2C_24C64_Write(unsigned int addr,unsigned char *pdate,unsigned char len)
 * 功能：往制定地址写入数据
 * 输入：unsigned int addr：	E2PROM的内部地址
 * 			unsigned char *pdate：	要写入数据的首地址
 *			unsigned char len：	要写入的字符数
 * 输出：unsigned char：出错返回0，正常返回1
 * 作者：李超
 * 版本：1.0
 * 备注：
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
 * 名称：unsigned char I2C_24C64_Read(unsigned int addr,unsigned char *pdate,unsigned char len)
 * 功能：读制定地址的数据
 * 输入：：unsigned int addr：	E2PROM的内部地址
 * 			unsigned char *pdate：	接收数据的首地址
 *			unsigned char len：	要接收的字符数
 * 输出：unsigned char：出错返回0，正常返回1
 * 作者：李超
 * 版本：1.0
 * 备注：
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
