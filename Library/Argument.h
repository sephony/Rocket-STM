#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "Include.h"
/******�Զ������******/
extern float H0;								//��ʼ�߶�
extern float H,H_fire,H_para,Max_Height,T0;  	//��ǰ�߶�-�������߶�-��ɡ�߶�-���߶�-���߶�ʱ��

extern float H_50Hz;							//50Hz�˲��߶�
extern float H_OneFactorialFilter;				//һ�׵�ͨ�˲��߶�

extern float sign;
extern int T; 				   			//ѭ����־
extern int exti_signal;						//�ⲿ�ж�(������ʼ)��־

extern float height[DATA_NUM]; 		//ȫ�����߶ȼ�¼
extern float height_50Hz[DATA_NUM];
extern float height_OneFactorialFilter[DATA_NUM];

extern int m;				 	 			//������¼����
extern int end_signal;						//���������־

#endif
















