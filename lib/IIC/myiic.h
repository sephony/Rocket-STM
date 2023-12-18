#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

/* IO�������� */
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	0x42345A80 
#define READ_SDA   PBin(7)  //����SDA 
//#define GPIO_PIN_INPUT_PP	0x0000008
//#define GPIO_PIN_OUTPUT_PP
/* IO�������� */
// ����PB7Ϊ����������ģʽ
#define SDA_IN()                         \
    {                                    \
        GPIOB->CRL &= 0X0FFFFFFF;        \
        GPIOB->CRL |= (uint32_t)8 << 28; \
    }
// ����PB7Ϊ����ͨ���������ģʽ
#define SDA_OUT()                        \
    {                                    \
        GPIOB->CRL &= 0X0FFFFFFF;        \
        GPIOB->CRL |= (uint32_t)3 << 28; \
    }

/* IIC���в������� */
void IIC_Init(void);							//��ʼ��IIC��IO��				 
void IIC_Start(void);							//����IIC��ʼ�ź�
void IIC_Stop(void);							//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);				//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);		//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void);						//IIC�ȴ�ACK�ź�
void IIC_Ack(void);								//IIC����ACK�ź�
void IIC_NAck(void);							//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);

#endif	/* myiic.h */
















