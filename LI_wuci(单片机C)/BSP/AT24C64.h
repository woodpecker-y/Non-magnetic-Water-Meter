/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：Frame.h
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef AT24C64_H_
#define AT24C64_H_
#include "MSP430.h"
#include "I2C.h"

#define AT24C64_ADDR_READ		0xA1
#define AT24C64_ADDR_WRITE		0xA0


void I2C_24C64_Init(void);
unsigned char I2C_24C64_Write(unsigned int addr,unsigned char *pdate,unsigned char len);
unsigned char I2C_24C64_Read(unsigned int addr,unsigned char *pdate,unsigned char len);

#endif /* AT24C64_H_ */
