/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����Frame.h
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
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
