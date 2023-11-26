#include "ms5611.h"
#include "math.h"
#include "delay.h"
#include "myiic.h"
#include "stdbool.h"
 
#define SCTemperature    0x01	  //??????
#define CTemperatureing  0x02 //??????
#define SCPressure  		 0x03	    //??????
#define SCPressureing    0x04	  //??????

/*
C1  压力灵敏度 SENS|T1
C2  压力抵消  OFF|T1
C3	温度压力灵敏度系数 TCS
C4	温度系数的压力抵消 TCO
C5	参考温度 T|REF
C6 	温度系数 TEMPSENS
*/
uint32_t  Cal_C[8];	        //从PROM读取出厂校准数据
float dT,TEMP,T2;
double OFF_,SENS;
float Aux,OFF2,SENS2;
uint32_t PRES;				//气压
uint32_t D1_Pres,D2_Temp;	// 数字气压，数字温度
double MSbaro_h,h_h;
uint32_t temp[3]={0};
/*
dT 实际与参考温度之间的差异
TEMP 实际温度
OFF 实际温度抵消
SENS 实际温度灵敏度
*/

/*******************************************************************************
  *	MS561101BA_RESET
  * 在读取PROM数据之前必须RESET芯片
  * reset命令固定是0x1E
	* RESET芯片后，必须要延时一段时间才能读取出厂校准值，否则如果延时时间不足，读取的出厂校准值肯定是错误的！！！
*******************************************************************************/
void MS561101BA_RESET(void)
{
	IIC_Start();
	IIC_Send_Byte(0xEE);//CSB接地,主机地址:0XEE；否则 0X77
	IIC_Wait_Ack();
	IIC_Send_Byte(0x1E);//发送复位命令
	IIC_Wait_Ack();
	IIC_Stop();
	delay_ms(200);
}
/*******************************************************************************
  * MS5611_init
  * 读取PROM内存的数据，PROM存放8个16位数据（工厂校准数据）
  * C0为工厂保留，读出来的数值为0，如果读出的数值不为0，说明你的IIC时序有问题或者你硬件复位后延时时间不足时就着急读出了工厂校准数据
  * C1---C6，参见技术手册，用于补偿气压和温度
  * C7为CRC校验数据，用于检查读出的工厂校准数据是否正确
*******************************************************************************/
u8 MS5611_init(void)
{	 
  u8  inth,intl;
  int i;
  for (i=0;i<=7;i++) 
	{
 
		IIC_Start();
    IIC_Send_Byte(0xEE);
		IIC_Wait_Ack();
		IIC_Send_Byte(0xA0 + (i*2));
		IIC_Wait_Ack();
    IIC_Stop();
		delay_us(200);
		
		IIC_Start();
		IIC_Send_Byte(0xEE+0x01);  //进入接收模式
		delay_us(1);
		IIC_Wait_Ack();
		inth = IIC_Read_Byte(1);  		//?ACK????
		delay_us(1);
		intl = IIC_Read_Byte(0); 			//??????NACK
		IIC_Stop();
    Cal_C[i] = (((uint16_t)inth << 8) | intl);
	}
	 return !Cal_C[0];//如果Cal_C[0]=0，说明读出的出厂校验值第一步成功
										//下面还需要通过Cal_C[7]验证CRC校验值，
										//如果CRC校验值通过，才能证明读出的出厂校验值正确
}
 
//验证工厂校准值CRC,函数的入口参数就是读出的工厂校准数据
bool MS5611_CRC(uint16_t *prom)
{
	int32_t i, j;
	uint32_t res = 0;
	uint8_t zero = 1;
	uint8_t crc = prom[7] & 0xF;
	prom[7] &= 0xFF00;

	// if eeprom is all zeros, we're probably fucked - BUT this will return valid CRC lol
	for (i = 0; i < 8; i++) 
	{
		if (prom[i] != 0)
		zero = 0;
	}
	if (zero)
		return (false);
	
	for (i = 0; i < 16; i++)
	{
		if (i & 1)
			res ^= ((prom[i >> 1]) & 0x00FF);
		else
			res ^= (prom[i >> 1] >> 8);
		for (j = 8; j > 0; j--)
		{
			if (res & 0x8000)
			res ^= 0x1800;
			res <<= 1;
		}
	}
	prom[7] |= crc;
	if (crc == ((res >> 12) & 0xF))
		return (true);
	return (false);
}
/**************************????********************************************
* uint32_t MS561101BA_getConversion(void)
* 启动温度AD转换，然后读取温度AD转换结果，以及启动压力AD转换，然后读取AD转换结果共用下面的一段程序
*******************************************************************************/
uint32_t MS561101BA_getConversion(uint8_t command)
{
			uint32_t conversion = 0;
//			uint32_t temp[3];
	
	    IIC_Start();
			IIC_Send_Byte(0xEE); 	
			IIC_Wait_Ack();
			IIC_Send_Byte(command);
			IIC_Wait_Ack();
			IIC_Stop();
			delay_ms(12);//等待9.04ms以上
	
			IIC_Start();
			IIC_Send_Byte(0xEE); 		
			IIC_Wait_Ack();
			IIC_Send_Byte(0);				// start read sequence
			IIC_Wait_Ack();
			IIC_Stop();
		 
			IIC_Start();
			IIC_Send_Byte(0xEE+0x01); 
			IIC_Wait_Ack();
			temp[0] = IIC_Read_Byte(1);  //?ACK????  bit 23-16
			temp[1] = IIC_Read_Byte(1);  //?ACK????  bit 8-15
			temp[2] = IIC_Read_Byte(0);  //?NACK???? bit 0-7
			IIC_Stop();
			
			conversion = temp[0] * 65536 + temp[1] * 256 + temp[2];
			return conversion;
}
 
 
/**************************????********************************************
* void MS561101BA_GetTemperature(void)
* 计算温度
*******************************************************************************/

void MS561101BA_GetTemperature(void)
{
	D2_Temp = MS561101BA_getConversion(0x58);
	delay_ms(10);
	if (D2_Temp > (((uint32_t)Cal_C[5]) << 8 ))
	{
		dT	= D2_Temp - (((uint32_t)Cal_C[5]) << 8 );
	}
	else
	{
		dT	= ((( uint32_t)Cal_C[5]) << 8) - D2_Temp;
		dT *= -1;
	}
	TEMP=2000+dT*((uint32_t)Cal_C[6])/8388608;
}

/***********************************************
  * void MS561101BA_getPressure(void)
  * 计算气压，
************************************************/
void MS561101BA_getPressure(void)
{
	D1_Pres= MS561101BA_getConversion(0x48);
	delay_ms(10);
	
	OFF_=(uint32_t)Cal_C[2]*65536+((uint32_t)Cal_C[4]*dT)/128;
	SENS=(uint32_t)Cal_C[1]*32768+((uint32_t)Cal_C[3]*dT)/256;
 
	if(TEMP<2000)
	{
		Aux = (2000-TEMP)*(2000-TEMP);
		T2 = (dT*dT) / 0x80000000; 
		OFF2 = (float)2.5*Aux;
		SENS2 = (float)1.25*Aux;
		if (TEMP < -1500)
		{
			Aux = (TEMP + 1500)*(TEMP + 1500);
			OFF2 = OFF2 + 7 * Aux;
			SENS2 = SENS + (float)(5.5)*Aux;
		}
	}
	else
	{
		T2=0;
		OFF2=0;
		SENS2=0;
	}
		TEMP = TEMP - T2;
		OFF_ = OFF_ - OFF2;
		SENS = SENS - SENS2;	
	
  PRES= (D1_Pres*SENS/2097152-OFF_)/32768;
}
/**********************
 * float Get_High(void)
 * 计算高度，单位m
**********************/
float Get_High(void)
{
	PRES= (D1_Pres*SENS/2097152-OFF_)/32768;
	MSbaro_h = 44330*(1-pow(((double)(PRES))/((double)(101325)),1.0/5.255));//barometric公式
	
	
	//MSbaro_h=(pow(((double)(PRES))/((double)(101325)),1.0/5.257)-1)*(TEMP+27315)/0.0065;//hypsometric公式
	return (float)MSbaro_h;
}	
