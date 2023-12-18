#ifndef USER_H_
#define USER_H_
/**
  ******************************************************************************
  * @file   	User.h
  * @author  	HITMA Rocket Team
  * @version  	比赛最终版
  * @date     	10. Augest 2023
  * @brief  	定义与火箭飞行控制相关的宏
  ==============================================================================
                     ##### 如何使用这个文件 #####
  ******************************************************************************
  * @attention
  *	如有需求，仅修改 @b宏
  * 老比赛：#define OLD_CADC 或 全不定义
  * 新比赛：#define NEW_CADC 或 全定义
  ******************************************************************************
  */

#define OLD_CADC			//老比赛
//#define NEW_CADC			//新比赛

#ifdef OLD_CADC
	#ifdef NEW_CADC
		#undef OLD_CADC
	#endif
#else
	#ifndef NEW_CADC
		#define OLD_CADC
	#endif
#endif
/*************************************时间*************************************/
#ifdef OLD_CADC				//老比赛

#define ROCKET_BEGIN			0			//	火箭起始飞行基准时间
#define ROCKET_FIRE				1.2			//	火箭点火时间			1.2	秒
#define ROCKET_FIRE_CONTINUE	0.8			//	火箭持续点火时间		0.8	秒
#define ROCKET_PARA				2.3			//	火箭开伞时间			2.3	秒
#define ROCKET_PARA_CONTINUE	1			//	火箭持续开伞时间		1	秒
#define ROCKET_PARA_PROTECT		8			//	火箭开伞保护时间		8	秒
#define ROCKET_END				30			//	火箭最大飞行时间		30	秒

#endif
/*----------------------------------------------------------------------------*/
#ifdef NEW_CADC				//新比赛


#define ROCKET_BEGIN			0			//	火箭起始飞行基准时间
#define ROCKET_PARA				0.8			//	火箭开伞时间			0.8	秒
#define ROCKET_PARA_CONTINUE	0.8			//	火箭持续开伞时间		0.8	秒
#define ROCKET_PARA_PROTECT		6			//	火箭开伞保护时间		6	秒
#define ROCKET_SEPA				1			//	火箭分离时间			1	秒
#define ROCKET_SEPA_CONTINUE	1.5			//	火箭持续分离时间		1.5	秒
#define ROCKET_END				30			//	火箭最大飞行时间		30	秒

#endif
/********************************高度控制参数**********************************/
#define PARA_FIXED_HEIGHT										//定高开伞

#ifdef OLD_CADC
	#define H_PARA_ON			65								//老比赛固定高度
#else
	#define H_PARA_ON			12								//新比赛固定高度
#endif

#define PARA_PROTECT											//开伞保护
/**********************************开伞相关************************************/
#define ANGLE					180								//舵机旋转角度
/******************************************************************************/
#endif  //!USER_H_
