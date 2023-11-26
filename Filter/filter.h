#ifndef __FILTER_H
#define __FILTER_H	 

//一阶低通滤波常数
#define OneFactorialFilter_Const 0.9

typedef struct
{
	float xv[3];
	float yv[3];
	float input;
	float output;
}Bw30HzLPFTypeDef;

typedef struct
{
	float xv[4];
	float yv[4];
	float input;
	float output;
}Bw50HzLPFTypeDef;

typedef struct
{
	//Bw30HzLPFTypeDef AltitudeLPF_30;
	Bw50HzLPFTypeDef AltitudeLPF_50;

}FilterTypeDef;


extern FilterTypeDef Filters;
void Butterworth30HzLPF(Bw30HzLPFTypeDef* pLPF);
void Butterworth50HzLPF(Bw50HzLPFTypeDef* pLPF);
void LPFUpdate(float height);
float OneFactorialFilter(float height);
#endif
