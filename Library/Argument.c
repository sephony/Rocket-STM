#include "Argument.h"

/******自定义变量******/
float H0,			//初始高度
	H,				//当前高度
	H_fire,			//二级点火高度
	H_para;			//开伞高度
//	h_max,			//最大高度
//	t_max_height  	//最大高度时刻

float H_50Hz;							//50Hz滤波高度
float H_OneFactorialFilter;				//一阶低通滤波高度

int T = 0; 					   			//循环标志
int exti_signal = 0;					//外部中断(程序起始)标志

float height[DATA_NUM] = {0}; 		//全弹道高度记录
float height_50Hz[DATA_NUM] = {0};
float height_OneFactorialFilter[DATA_NUM] = {0};

int m = 0;				 	 			//弹道记录参数
int end_signal = 1;						//程序结束标志

float sign = 0;							//备用调试标识
