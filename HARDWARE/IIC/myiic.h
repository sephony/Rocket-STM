#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

/* IO操作函数 */
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	0x42345A80 
#define READ_SDA   PBin(7)  //输入SDA 
//#define GPIO_PIN_INPUT_PP	0x0000008
//#define GPIO_PIN_OUTPUT_PP
/* IO方向设置 */
// 配置PB7为上下拉输入模式
#define SDA_IN()                         \
    {                                    \
        GPIOB->CRL &= 0X0FFFFFFF;        \
        GPIOB->CRL |= (uint32_t)8 << 28; \
    }
// 配置PB7为高速通用推挽输出模式
#define SDA_OUT()                        \
    {                                    \
        GPIOB->CRL &= 0X0FFFFFFF;        \
        GPIOB->CRL |= (uint32_t)3 << 28; \
    }

/* IIC所有操作函数 */
void IIC_Init(void);							//初始化IIC的IO口				 
void IIC_Start(void);							//发送IIC开始信号
void IIC_Stop(void);							//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);				//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);		//IIC读取一个字节
uint8_t IIC_Wait_Ack(void);						//IIC等待ACK信号
void IIC_Ack(void);								//IIC发送ACK信号
void IIC_NAck(void);							//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif	/* myiic.h */
















