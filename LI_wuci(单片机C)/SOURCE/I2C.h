/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：LCD.c
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
 * SDA        ->       P6.5
 * SCL		 ->		P6.6
*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef I2C_H_
#define I2C_H_

#include "MSP430.h"

#define DELAY_TIME						1

#define I2C_SDA_PORT_SEL			P6SEL
#define I2C_SDA_PORT_DIR			P6DIR
#define I2C_SDA_PORT_IN				P6IN
#define I2C_SDA_PORT_OUT			P6OUT

#define I2C_SCL_PORT_SEL				P6SEL
#define I2C_SCL_PORT_DIR				P6DIR
#define I2C_SCL_PORT_IN				P6IN
#define I2C_SCL_PORT_OUT			P6OUT

#define I2C_WP_PORT_SEL				P6SEL
#define I2C_WP_PORT_DIR				P6DIR
#define I2C_WP_PORT_IN				P6IN
#define I2C_WP_PORT_OUT			P6OUT

#define I2C_SDA_BIT						BIT5
#define I2C_SCL_BIT						BIT6
#define I2C_WP_BIT						BIT7



void Delay_I2C(unsigned int  time);
void I2C_WP_H(void);
void I2C_WP_L(void);
void I2C_SDA_H(void);
void I2C_SDA_L(void);
void I2C_SCL_H(void);
void I2C_SCL_L(void);
unsigned char I2C_SDA_Read(void);
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NoACK(void);
unsigned char I2C_WriteByte(unsigned char byte);
unsigned char I2C_ReadByte(void);



#endif /* I2C_H_ */
