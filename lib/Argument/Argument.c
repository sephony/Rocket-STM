#include "Argument.h"

/******�Զ������******/
float H0,			//��ʼ�߶�
	H,				//��ǰ�߶�
	H_fire,			//�������߶�
	H_para;			//��ɡ�߶�
//	h_max,			//���߶�
//	t_max_height  	//���߶�ʱ��

float H_50Hz;							//50Hz�˲��߶�
float H_OneFactorialFilter;				//һ�׵�ͨ�˲��߶�

int T = 0; 					   			//ѭ����־
int exti_signal = 0;					//�ⲿ�ж�(������ʼ)��־

float height[DATA_NUM] = {0}; 		//ȫ�����߶ȼ�¼
float height_50Hz[DATA_NUM] = {0};
float height_OneFactorialFilter[DATA_NUM] = {0};

int m = 0;				 	 			//������¼����
int end_signal = 1;						//���������־

float sign = 0;							//���õ��Ա�ʶ
