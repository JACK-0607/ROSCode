#ifndef __OLED_IIC_H
#define __OLED_MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
 
#define oled_SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define oled_SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO��������	 
#define oled_IIC_SCL    PBout(6) //SCL
#define oled_IIC_SDA    PBout(7) //SDA	 
#define oled_READ_SDA   PBin(7)  //����SDA          9i8o89i090o9i;['

//IIC���в�������
void oled_IIC_Init(void);                //��ʼ��IIC��IO��				 
void oled_IIC_Start(void);				//����IIC��ʼ�ź�
void oled_IIC_Stop(void);	  			//����IICֹͣ�ź�
void oled_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 oled_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 oled_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void oled_IIC_Ack(void);					//IIC����ACK�ź�
void oled_IIC_NAck(void);				//IIC������ACK�ź�

void oled_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 oled_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















