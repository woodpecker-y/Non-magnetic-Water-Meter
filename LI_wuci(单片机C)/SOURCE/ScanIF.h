/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����Comparator_A.c
 * ���ߣ��
 * ʱ�䣺3015/3/19
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef SCANIF_H_
#define SCANIF_H_

#include <msp430.h>
#include <stdint.h>

#define		SCAN_PORT_DIR_IN		P6DIR &=~ (SCANIF_CH0 + SCANIF_CH1)
#define		SCAN_PORT_SEL				P6SEL |= (SCANIF_CH0 + SCANIF_CH1)

#define		SCANIF_CH0		BIT0
#define		SCANIF_CH1		BIT1
#define		SCANIF_CH2		BIT2
#define		SCANIF_CH3		BIT3




void ScanIF_Init(void);
void ScanIF_Delay(void);
void ScanIF_Cal(void);

#endif /* SCANIF_H_ */
