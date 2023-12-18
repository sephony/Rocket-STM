#include "interrupt.h"
#include "Function.h"
/*------------------------------------------------------
�ⲿ�жϷ������
�����ܣ���ȡ�����ж���Ϊ������ʼ
--------------------------------------------------------*/
void EXTI_Interrupt(void)
{
	HAL_GPIO_WritePin(Run_Sign_GPIO_Port,Run_Sign_Pin,GPIO_PIN_RESET);		//���жϣ��̵���
	exti_signal = 1;
}
/*------------------------------------------------------
��ʱ��3�жϷ������
�����ܣ����͸߶�����
--------------------------------------------------------*/
void TransmitHeight_Interrupt(void)
{
	MS561101BA_GetTemperature(); 
	MS561101BA_getPressure();
	H = Get_High()-H0;
	LPFUpdate(H);
	H_OneFactorialFilter=OneFactorialFilter(H);
	__HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);  //���TIMx�����жϱ�־ 
//	printf("%f\n", H);
}


/*------------------------------------------------------
��ʱ��2�жϷ������
�����ܣ�ʱ�����
--------------------------------------------------------*/
void TimeControl_Interrupt(void)
{
	if(exti_signal == 1)
	{
		++T;
		/* �߶ȼ�¼ */
		HANDLE_HEIGHT;
		/* ����� */
		HANDLE_FIRE;
		/* ��ɡ��� */
		HANDLE_PARA;
		/* ���н�������ӡ���� */
		TRANSMIT_HEIGHT;		
	}
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);  //���TIMx�����жϱ�־ 
}
