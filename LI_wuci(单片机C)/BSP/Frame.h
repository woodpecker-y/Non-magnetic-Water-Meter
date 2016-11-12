/*-----------------copyright(c)------------------------------------------------------------------------------------------------------------------*/
/*文件名：Frame.h
 * 作者：李超
 * 时间：3015/3/18
 * 使用范围：MSP430FW427,适用于能联第一版的板子
 * 备注：
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
