#ifndef __MS5611_H_
#define __MS5611_H_

/******User Include******/
#include "stdbool.h"
#include "sys.h"
#include "delay.h"
#include "math.h"
#include "myiic.h"

#define MS561101BA_ADC_RD          0x00
#define	MS561101BA_PROM_RD 	       0xA0
#define MS561101BA_PROM_CRC        0xAE
 
#define MS561101BA_SlaveAddress    0xEE  //MS5611地址
#define MS561101BA_RST             0x1E  //cmd 复位

#define	MS561101BA_D2_OSR_4096   	 0x58	// 9.04 mSec conversion time ( 110.62 Hz)
#define	MS561101BA_D1_OSR_4096   	 0x48
 
#define MS5611_OSR256					 		 0x40
#define MS5611_OSR512					 		 0x42
#define MS5611_OSR1024					   0x44
#define MS5611_OSR2048					   0x46
#define MS5611_OSR4096					   0x48

u8  MS5611_init(void);
float Get_High(void);
void MS561101BA_getPressure(void);
void MS561101BA_GetTemperature(void);
void MS561101BA_RESET(void);

uint32_t MS561101BA_getConversion(uint8_t command);

bool MS5611_CRC(uint16_t *prom);



extern uint32_t  Cal_C[8];	        //从PROM读取出厂校准数据
extern float dT,TEMP,T2;
extern double OFF_,SENS;
extern float Aux,OFF2,SENS2;
extern uint32_t PRES;				//气压
extern uint32_t D1_Pres,D2_Temp;	// 数字气压，数字温度
extern double MSbaro_h,h_h;

#endif
 
