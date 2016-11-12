/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*�ļ�����Frame.h
 * ���ߣ��
 * ʱ�䣺3015/3/18
 * ʹ�÷�Χ��MSP430FW427,������������һ��İ���
 * ��ע��
 *
 * */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#ifndef FRAME_H_
#define FRAME_H_
#include "includes.h"

#define STEP_HEAD1	1
#define STEP_HEAD2	2
#define STEP_DATA	3
#define STEP_END1	4
#define STEP_END2	5

void Frame_Get(void);
void Frame_Work(void);
void Write_WaterVolume(void);
void Read_WaterVolume(void);
#endif /* FRAME_H_ */
