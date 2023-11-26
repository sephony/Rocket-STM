/**
  ******************************************************************************
  * @file   	Macro.h
  * @author  	HITMA Rocket Team
  * @version  	�������հ�
  * @date     	10. Augest 2023
  * @brief  	�����������п�����صĺ�
  ==============================================================================
                     ##### ���ʹ������ļ� #####
  ******************************************************************************
  * @attention
  * ��ʱ���ɼ�Ƶ��Ϊ20Hz������0.05s�ɼ�һ�θ߶�����
  ******************************************************************************
  */
#ifndef MACRO_H_
#define MACRO_H_

#include "User.h"

/*********************************ʱ����Ʋ���*********************************/

#define FREQ					20  				// ��ʱ��Ƶ��		20Hz
#define TIME					(1 / FREQ)			// ��ʱ��ʱ������	0.05s
#define CAL_TIME(X)				((X) * FREQ)  		// ����׼ʱ��ת��Ϊ��ʱ��ʱ��
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifdef OLD_CADC				//�ϱ���

#define T_BEGIN					CAL_TIME(ROCKET_BEGIN)							//	0	��
#define T_FIRE_ON				CAL_TIME(ROCKET_FIRE)                         	//	1.2	�����
#define T_FIRE_OFF				CAL_TIME(ROCKET_FIRE + ROCKET_FIRE_CONTINUE)  	//	2.0	���ֹͣ������
#define T_PARA_ON				CAL_TIME(ROCKET_PARA)                         	//	2.3	���ɡ
#define T_PARA_OFF				CAL_TIME(ROCKET_PARA + ROCKET_PARA_CONTINUE)  	//	3.3	���ֹͣ���翪ɡ
#define T_END					CAL_TIME(ROCKET_END)							//	30	��

#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifdef NEW_CADC				//�±���

#define T_BEGIN					CAL_TIME(ROCKET_BEGIN)							//	0	��
#define T_PARA_ON				CAL_TIME(ROCKET_PARA)                         	//	0.8	���ɡ
#define T_PARA_OFF				CAL_TIME(ROCKET_PARA + ROCKET_PARA_CONTINUE)  	//	1.6	���ֹͣ���翪ɡ
#define T_SEPA_ON				CAL_TIME(ROCKET_SEPA)                        	//	1	������
#define T_SEPA_OFF				CAL_TIME(ROCKET_SEPA + ROCKET_SEPA_CONTINUE)  	//	2.5	���ֹͣ�������
#define T_END					CAL_TIME(ROCKET_END)							//	30	��

#endif			
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define T_PARA_PROTECT			CAL_TIME(ROCKET_PARA_PROTECT)					//	��ɡ����ʱ��
//#define OUTPUT_CONTINUE											  	  	  	//	�������(����һֱ�����ѹ)

/********************************�߶ȿ��Ʋ���**********************************/

#ifndef PARA_FIXED_HEIGHT
	#define PARA_FIXED_TIME										//��ʱ��ɡ
#endif

/**********************************��ɡ���************************************/

#define SERVO(X)				(((X) / 45 + 1) * 18)			//������Ƕ�ת��ΪPWM��ֵ

/******************************�û��Զ������**********************************/
enum {
    EndOfProgram = CAL_TIME(ROCKET_END)							// �������ʱ��
};
#define DATA_NUM				EndOfProgram					// �����������(600)

/******************************************************************************/

#define LPF														//�˲�

#ifndef LPF
	#define USER_DEFINED_LPF									//�Զ���һ�׵�ͨ�˲�
#endif

/**
  ******************************************************************************
  * @brief  	ʱ�������ش����
  * @note		HANDLE_HEIGHT-------�߶Ȳ���
  *				HANDLE_FIRE---------������
  *				HANDLE_PARA---------��ɡ����
  *				TRANSMIT_FIRE-------��������
  ******************************************************************************
  * @attention	�ϱ������±����໥����
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
