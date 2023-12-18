#include "interrupt.h"
#include "Function.h"
/*------------------------------------------------------
外部中断服务程序
任务功能：读取霍尔中断作为程序起始
--------------------------------------------------------*/
void EXTI_Interrupt(void)
{
	HAL_GPIO_WritePin(Run_Sign_GPIO_Port,Run_Sign_Pin,GPIO_PIN_RESET);		//进中断，绿灯亮
	exti_signal = 1;
}
/*------------------------------------------------------
定时器3中断服务程序
任务功能：发送高度数据
--------------------------------------------------------*/
void TransmitHeight_Interrupt(void)
{
	MS561101BA_GetTemperature(); 
	MS561101BA_getPressure();
	H = Get_High()-H0;
	LPFUpdate(H);
	H_OneFactorialFilter=OneFactorialFilter(H);
	__HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);  //清除TIMx更新中断标志 
//	printf("%f\n", H);
}


/*------------------------------------------------------
定时器2中断服务程序
任务功能：时序控制
--------------------------------------------------------*/
void TimeControl_Interrupt(void)
{
	if(exti_signal == 1)
	{
		++T;
		/* 高度记录 */
		HANDLE_HEIGHT;
		/* 点火检测 */
		HANDLE_FIRE;
		/* 开伞检测 */
		HANDLE_PARA;
		/* 飞行结束，打印数据 */
		TRANSMIT_HEIGHT;		
	}
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);  //清除TIMx更新中断标志 
}
