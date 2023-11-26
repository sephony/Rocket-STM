#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include "Include.h"
/******自定义变量******/
extern float H0;								//初始高度
extern float H,H_fire,H_para,Max_Height,T0;  	//当前高度-二级点火高度-开伞高度-最大高度-最大高度时刻

extern float H_50Hz;							//50Hz滤波高度
extern float H_OneFactorialFilter;				//一阶低通滤波高度

extern float sign;
extern int T; 				   			//循环标志
extern int exti_signal;						//外部中断(程序起始)标志

extern float height[DATA_NUM]; 		//全弹道高度记录
extern float height_50Hz[DATA_NUM];
extern float height_OneFactorialFilter[DATA_NUM];

extern int m;				 	 			//弹道记录参数
extern int end_signal;						//程序结束标志

#endif
















