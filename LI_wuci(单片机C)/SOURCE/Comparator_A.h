/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����LCD.H
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef COMPARATOR_A_H_
#define COMPARATOR_A_H_
#include <msp430.h>
#include <stdint.h>
/**
 * VREF	P2.1
**/
#define VREF_OUTPUT	P2DIR	 |=	BIT1
#define VREF_SET			P2OUT   |=    BIT1
#define VREF_RESET		P2OUT &=  ~BIT1

#define CMPA_PORT_SEL				P1SEL |= (BIT6+BIT7);
#define CMPA_PORT_DIR_INPUT		P1DIR &= ~(BIT6+BIT7);


void CMPA_Init(void);
void	CMPA_Enable(void);
void	CMPA_Disable(void);
unsigned char CMPA_Read_CAOUT(void);
#endif /* COMPARATOR_A_H_ */
