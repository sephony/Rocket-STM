#ifndef USER_H_
#define USER_H_
/**
  ******************************************************************************
  * @file   	User.h
  * @author  	HITMA Rocket Team
  * @version  	�������հ�
  * @date     	10. Augest 2023
  * @brief  	�����������п�����صĺ�
  ==============================================================================
                     ##### ���ʹ������ļ� #####
  ******************************************************************************
  * @attention
  *	�������󣬽��޸� @b��
  * �ϱ�����#define OLD_CADC �� ȫ������
  * �±�����#define NEW_CADC �� ȫ����
  ******************************************************************************
  */

#define OLD_CADC			//�ϱ���
//#define NEW_CADC			//�±���

#ifdef OLD_CADC
	#ifdef NEW_CADC
		#undef OLD_CADC
	#endif
#else
	#ifndef NEW_CADC
		#define OLD_CADC
	#endif
#endif
/*************************************ʱ��*************************************/
#ifdef OLD_CADC				//�ϱ���

#define ROCKET_BEGIN			0			//	�����ʼ���л�׼ʱ��
#define ROCKET_FIRE				1.2			//	������ʱ��			1.2	��
#define ROCKET_FIRE_CONTINUE	0.8			//	����������ʱ��		0.8	��
#define ROCKET_PARA				2.3			//	�����ɡʱ��			2.3	��
#define ROCKET_PARA_CONTINUE	1			//	���������ɡʱ��		1	��
#define ROCKET_PARA_PROTECT		8			//	�����ɡ����ʱ��		8	��
#define ROCKET_END				30			//	���������ʱ��		30	��

#endif
/*----------------------------------------------------------------------------*/
#ifdef NEW_CADC				//�±���


#define ROCKET_BEGIN			0			//	�����ʼ���л�׼ʱ��
#define ROCKET_PARA				0.8			//	�����ɡʱ��			0.8	��
#define ROCKET_PARA_CONTINUE	0.8			//	���������ɡʱ��		0.8	��
#define ROCKET_PARA_PROTECT		6			//	�����ɡ����ʱ��		6	��
#define ROCKET_SEPA				1			//	�������ʱ��			1	��
#define ROCKET_SEPA_CONTINUE	1.5			//	�����������ʱ��		1.5	��
#define ROCKET_END				30			//	���������ʱ��		30	��

#endif
/********************************�߶ȿ��Ʋ���**********************************/
#define PARA_FIXED_HEIGHT										//���߿�ɡ

#ifdef OLD_CADC
	#define H_PARA_ON			65								//�ϱ����̶��߶�
#else
	#define H_PARA_ON			12								//�±����̶��߶�
#endif

#define PARA_PROTECT											//��ɡ����
/**********************************��ɡ���************************************/
#define ANGLE					180								//�����ת�Ƕ�
/******************************************************************************/
#endif  //!USER_H_
