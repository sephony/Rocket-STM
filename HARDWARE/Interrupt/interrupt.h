#ifndef Interrupt_H_
#define Interrupt_H_

#include "Include.h"

/******Variables Referrence******/
extern float H,H_fire,H_para,Max_Height,T0;  //��ǰ�߶�-�������߶�-��ɡ�߶�-���߶�-���߶�ʱ��

extern float H_50Hz;
extern float H_OneFactorialFilter;

extern float H0;

extern int T;   //ѭ����־
extern int exti_signal;		//�ⲿ�ж�(������ʼ)��־
extern float height[DATA_NUM];   //ȫ�����߶ȼ�¼

//extern float height_30Hz[EndOfProgram];
extern float height_50Hz[DATA_NUM];
extern float height_OneFactorialFilter[DATA_NUM];



extern int m;
extern int end_signal;			 //���������־
/******Interrupt Function******/
void TransmitHeight_Interrupt(void);		//�����ܣ����͸߶�����
void TimeControl_Interrupt(void);			//�����ܣ�ʱ�����
void EXTI_Interrupt(void);					//�����ܣ���ȡ�����ж���Ϊ������ʼ

#endif



