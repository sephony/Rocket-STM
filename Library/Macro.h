/**
  ******************************************************************************
  * @file   	Macro.h
  * @author  	HITMA Rocket Team
  * @version  	比赛最终版
  * @date     	10. Augest 2023
  * @brief  	定义与火箭飞行控制相关的宏
  ==============================================================================
                     ##### 如何使用这个文件 #####
  ******************************************************************************
  * @attention
  * 定时器采集频率为20Hz，周期0.05s采集一次高度数据
  ******************************************************************************
  */
#ifndef MACRO_H_
#define MACRO_H_

#include "User.h"

/*********************************时序控制参数*********************************/

#define FREQ					20  				// 定时器频率		20Hz
#define TIME					(1 / FREQ)			// 定时器时钟周期	0.05s
#define CAL_TIME(X)				((X) * FREQ)  		// 将标准时间转变为定时器时间
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifdef OLD_CADC				//老比赛

#define T_BEGIN					CAL_TIME(ROCKET_BEGIN)							//	0	秒
#define T_FIRE_ON				CAL_TIME(ROCKET_FIRE)                         	//	1.2	秒后点火
#define T_FIRE_OFF				CAL_TIME(ROCKET_FIRE + ROCKET_FIRE_CONTINUE)  	//	2.0	秒后停止供电点火
#define T_PARA_ON				CAL_TIME(ROCKET_PARA)                         	//	2.3	秒后开伞
#define T_PARA_OFF				CAL_TIME(ROCKET_PARA + ROCKET_PARA_CONTINUE)  	//	3.3	秒后停止供电开伞
#define T_END					CAL_TIME(ROCKET_END)							//	30	秒

#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifdef NEW_CADC				//新比赛

#define T_BEGIN					CAL_TIME(ROCKET_BEGIN)							//	0	秒
#define T_PARA_ON				CAL_TIME(ROCKET_PARA)                         	//	0.8	秒后开伞
#define T_PARA_OFF				CAL_TIME(ROCKET_PARA + ROCKET_PARA_CONTINUE)  	//	1.6	秒后停止供电开伞
#define T_SEPA_ON				CAL_TIME(ROCKET_SEPA)                        	//	1	秒后分离
#define T_SEPA_OFF				CAL_TIME(ROCKET_SEPA + ROCKET_SEPA_CONTINUE)  	//	2.5	秒后停止供电分离
#define T_END					CAL_TIME(ROCKET_END)							//	30	秒

#endif			
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define T_PARA_PROTECT			CAL_TIME(ROCKET_PARA_PROTECT)					//	开伞保护时间
//#define OUTPUT_CONTINUE											  	  	  	//	持续点火(点火口一直输出电压)

/********************************高度控制参数**********************************/

#ifndef PARA_FIXED_HEIGHT
	#define PARA_FIXED_TIME										//定时开伞
#endif

/**********************************开伞相关************************************/

#define SERVO(X)				(((X) / 45 + 1) * 18)			//将舵机角度转变为PWM数值

/******************************用户自定义变量**********************************/
enum {
    EndOfProgram = CAL_TIME(ROCKET_END)							// 程序结束时间
};
#define DATA_NUM				EndOfProgram					// 数据数组个数(600)

/******************************************************************************/

#define LPF														//滤波

#ifndef LPF
	#define USER_DEFINED_LPF									//自定义一阶低通滤波
#endif

/**
  ******************************************************************************
  * @brief  	时序控制相关处理宏
  * @note		HANDLE_HEIGHT-------高度采样
  *				HANDLE_FIRE---------点火控制
  *				HANDLE_PARA---------开伞控制
  *				TRANSMIT_FIRE-------发送数据
  ******************************************************************************
  * @attention	老比赛和新比赛相互独立
  ******************************************************************************
  */
/**********************************************************************************************************************/
#ifdef OLD_CADC
/*--------------------------------------------------------------------------------------------------------------------*/
	#ifdef USER_DEFINED_LPF
			#define HANDLE_HEIGHT do{																					\
				if((T > 0) && (T <= T_END)) {																			\
					height[m]=H;																						\
					height_50Hz[m]=Filters.AltitudeLPF_50.output;														\
					height_OneFactorialFilter[m]=H_OneFactorialFilter;													\
					m++;																								\
				}																										\
			}while(0)
	#else
			#define HANDLE_HEIGHT do{																					\
				if((T > 0) && (T <= T_END)) {																			\
					height[m]=H;																						\
					height_50Hz[m]=Filters.AltitudeLPF_50.output;														\
					m++;																								\
				}																										\
			}while(0)
	#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */	
	#ifdef OUTPUT_CONTINUE
			#define HANDLE_FIRE do{																						\
				if((T >= T_FIRE_ON) && (T <= T_FIRE_OFF)) {																\
					HAL_GPIO_WritePin(Fire_1_GPIO_Port, Fire_1_Pin, GPIO_PIN_SET);										\
					HAL_GPIO_WritePin(Fire_2_GPIO_Port, Fire_2_Pin, GPIO_PIN_SET);										\
					HAL_GPIO_WritePin(Fire_Sign_1_GPIO_Port, Fire_Sign_1_Pin, GPIO_PIN_RESET);							\
				}																										\
			}while(0)
	#else
			#define HANDLE_FIRE do{																						\
				if((T >= T_FIRE_ON) && (T <= T_FIRE_OFF)) {																\
					HAL_GPIO_WritePin(Fire_1_GPIO_Port, Fire_1_Pin, GPIO_PIN_SET);										\
					HAL_GPIO_WritePin(Fire_2_GPIO_Port, Fire_2_Pin, GPIO_PIN_SET);										\
					HAL_GPIO_WritePin(Fire_Sign_1_GPIO_Port, Fire_Sign_1_Pin, GPIO_PIN_RESET);							\
				}																										\
				if(T > T_FIRE_OFF) {																					\
					HAL_GPIO_WritePin(Fire_1_GPIO_Port, Fire_1_Pin, GPIO_PIN_RESET);									\
					HAL_GPIO_WritePin(Fire_2_GPIO_Port, Fire_2_Pin, GPIO_PIN_RESET);									\
				}																										\
			}while(0)
	#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	#ifdef PARA_FIXED_HEIGHT
			#ifdef PARA_PROTECT
				#define HANDLE_PARA do{																					\
					if(Filters.AltitudeLPF_50.output >= H_PARA_ON) {													\
						sign = 1;																						\
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));										\
						HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);						\
					}																									\
					if((T >= T_PARA_PROTECT) && (sign != 1)) {															\
						sign = 1;																						\
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));										\
						HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);						\
					}																									\
				}while(0)
			#else
				#define HANDLE_PARA do{																					\
					if(Filters.AltitudeLPF_50.output >= H_PARA_ON) {													\
						sign = 1;																						\
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));										\
						HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);						\
					}																									\
				}while(0)
			#endif
	#else
			#define HANDLE_PARA do{																						\
				if((T >= T_PARA_ON) && (T <= T_PARA_OFF)) {																\
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));											\
					HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);							\
				}																										\
			}while(0)
	#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	#ifdef LPF
			#define TRANSMIT_HEIGHT do{																					\
				if(T > T_END) {																							\
					HAL_TIM_Base_Stop_IT(&htim3);																		\
					HAL_GPIO_TogglePin(Run_Sign_GPIO_Port,Run_Sign_Pin);												\
					printf("%d %d\r\n", 1000, 1000);																	\
					for (int t = 0; t < T_END; t++) {																	\
						printf("%.4f %.4f\r\n", height[t], height_50Hz[t]);												\
					}																									\
					printf("%d %d\r\n", 1001, 1001);																	\
				}																										\
			}while(0)
	#else
			#define TRANSMIT_HEIGHT do{																					\
				if(T > T_END) {																							\
					HAL_TIM_Base_Stop_IT(&htim3);																		\
					HAL_GPIO_TogglePin(Run_Sign_GPIO_Port,Run_Sign_Pin);												\
					printf("%d %d %d\r\n", 1000, 1000, 1000);															\
					for (int t = 0; t < T_END; t++) {																	\
						printf("%.4f %.4f %.4f\r\n", height[t], height_50Hz[t], height_OneFactorialFilter[t]);
					}																									\
					printf("%d %d %d\r\n", 1001, 1001, 1001);															\
				}																										\
			}while(0)
	#endif
/*--------------------------------------------------------------------------------------------------------------------*/
#endif
/**********************************************************************************************************************/
#ifdef NEW_CADC
/*--------------------------------------------------------------------------------------------------------------------*/
	#ifdef USER_DEFINED_LPF
			#define HANDLE_HEIGHT do{\
				if((T > 0) && (T <= T_END)) {\
					height[m]=H;\
					height_50Hz[m]=Filters.AltitudeLPF_50.output;\
					height_OneFactorialFilter[m]=H_OneFactorialFilter;\
					m++;\
				}\
			}while(0)
	#else
			#define HANDLE_HEIGHT do{\
				if((T > 0) && (T <= T_END)) {\
					height[m]=H;\
					height_50Hz[m]=Filters.AltitudeLPF_50.output;\
					m++;\
				}\
			}while(0)
	#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */	
#define HANDLE_FIRE do{\
					}while(0)
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	#ifdef PARA_FIXED_HEIGHT
			#ifdef PARA_PROTECT
				#define HANDLE_PARA do{\
					if(Filters.AltitudeLPF_50.output >= H_PARA_ON) {\
						sign = 1;\
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));\
						HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);\
					}\
					if((T >= T_PARA_PROTECT) && (sign != 1)) {\
						sign = 1;\
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));\
						HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);\
					}\
				}while(0)
			#else
				#define HANDLE_PARA do{\
					if(Filters.AltitudeLPF_50.output >= H_PARA_ON) {\
						sign = 1;\
						__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));\
						HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);\
					}\
				}while(0)
			#endif
	#else
			#define HANDLE_PARA do{\
				if((T >= T_PARA_ON) && (T <= T_PARA_OFF)) {\
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, SERVO(ANGLE));\
					HAL_GPIO_WritePin(Fire_Sign_2_GPIO_Port, Fire_Sign_2_Pin, GPIO_PIN_RESET);\
				}\
			}while(0)
	#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	#ifdef LPF
			#define TRANSMIT_HEIGHT do{\
				if(T > T_END) {\
					HAL_TIM_Base_Stop_IT(&htim3);\
					HAL_GPIO_TogglePin(Run_Sign_GPIO_Port,Run_Sign_Pin);\
					printf("%d %d\r\n", 1000, 1000);\
					for (int t = 0; t < T_END; t++) {\
						printf("%.4f %.4f\r\n", height[t], height_50Hz[t]);\
					}\
					printf("%d %d\r\n", 1001, 1001);\
				}\
			}while(0)
	#else
			#define TRANSMIT_HEIGHT do{\
				if(T > T_END) {\
					HAL_TIM_Base_Stop_IT(&htim3);\
					HAL_GPIO_TogglePin(Run_Sign_GPIO_Port,Run_Sign_Pin);\
					printf("%d %d %d\r\n", 1000, 1000, 1000);\
					for (int t = 0; t < T_END; t++) {\
						printf("%.4f %.4f %.4f\r\n", height[t], height_50Hz[t], height_OneFactorialFilter[t]);
					}\
					printf("%d %d %d\r\n", 1001, 1001, 1001);\
				}\
			}while(0)
	#endif
/*--------------------------------------------------------------------------------------------------------------------*/
#endif
/**********************************************************************************************************************/
#endif  //!MACRO_H_
