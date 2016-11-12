/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����includes.h
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdint.h>

#define	TXD	BIT0
#define	RXD	BIT1

#define BitTime_5	0x06
#define BitTime		0x0e

unsigned int RXTXData;
unsigned char BitCnt;
char RXbuff[10];
unsigned char RXCnt;


void UART_Init(void);
void TX_Ready(void);
void TX_Byte(unsigned char byte);
void TX_String(unsigned char *string);
void RX_Ready(void);

#endif /* UART_H_ */
