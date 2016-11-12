/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����Motor.h
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*
 * K1		P1.5
 * K2		P1.4
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef MOTOR_H_
#define MOTOR_H_
#include "includes.h"
#define		K1			BIT5
#define		K2			BIT4

#define		K1DIR_OUTPUT		P1DIR |= K1
#define		K2DIR_OUTPUT		P1DIR |= K2

#define		K1SEL_GPIO			P1SEL &=~K1
#define		K2SEL_GPIO			P1SEL &=~K2

#define		K1_SET					P1OUT |= K1
#define		K1_RESET				P1OUT &=~K1
#define		K2_SET					P1OUT |= K2
#define		K2_RESET				P1OUT &=~K2
/*--�������ָ��*/
#define		MOTOR_OPEN		K1_RESET;K2_SET
#define		MOTOR_CLOSE		K1_SET;K2_RESET
#define		MOTOR_STOP		K1_RESET;K2_RESET

void Motor_Init(void);
void Motor_Open(void);
void Motor_Close(void);
void Motor_Stop(void);

#endif /* MOTOR_H_ */
