#ifndef Interrupt_H_
#define Interrupt_H_

#include "Include.h"

/******Variables Referrence******/
extern float H,H_fire,H_para,Max_Height,T0;  //当前高度-二级点火高度-开伞高度-最大高度-最大高度时刻

extern float H_50Hz;
extern float H_OneFactorialFilter;

extern float H0;

extern int T;   //循环标志
extern int exti_signal;		//外部中断(程序起始)标志
extern float height[DATA_NUM];   //全弹道高度记录

//extern float height_30Hz[EndOfProgram];
extern float height_50Hz[DATA_NUM];
extern float height_OneFactorialFilter[DATA_NUM];



extern int m;
extern int end_signal;			 //程序结束标志
/******Interrupt Function******/
void TransmitHeight_Interrupt(void);		//任务功能：发送高度数据
void TimeControl_Interrupt(void);			//任务功能：时序控制
void EXTI_Interrupt(void);					//任务功能：读取霍尔中断作为程序起始

#endif



