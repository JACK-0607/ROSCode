#include "oled_iic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��IIC
void oled_IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//ʹ��GPIOBʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 �����
}
////����IIC��ʼ�ź�
//void oled_IIC_Start(void)
//{
//	oled_SDA_OUT();     //sda�����
//	oled_IIC_SDA=1;	  	  
//	oled_IIC_SCL=1;
//	delay_us(4);
// 	oled_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
//	delay_us(4);
//	oled_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
//}	  
////����IICֹͣ�ź�
//void oled_IIC_Stop(void)
//{
//	oled_SDA_OUT();//sda�����
//	oled_IIC_SCL=0;
//	oled_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
// 	delay_us(4);
//	oled_IIC_SCL=1; 
//	oled_IIC_SDA=1;//����I2C���߽����ź�
//	delay_us(4);							   	
//}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 oled_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	oled_SDA_IN();      //SDA����Ϊ����  
	oled_IIC_SDA=1;delay_us(1);	   
	oled_IIC_SCL=1;delay_us(1);	 
	while(oled_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			oled_IIC_Stop();
			return 1;
		}
	}
	oled_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void oled_IIC_Ack(void)
{
	oled_IIC_SCL=0;
	oled_SDA_OUT();
	oled_IIC_SDA=0;
	oled_delay_us(2);
	oled_IIC_SCL=1;
	oled_delay_us(2);
	oled_IIC_SCL=0;
}
//������ACKӦ��		    
void oled_IIC_NAck(void)
{
	oled_IIC_SCL=0;
	oled_SDA_OUT();
	oled_IIC_SDA=1;
	delay_us(2);
	oled_IIC_SCL=1;
	delay_us(2);
	oled_IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void oled_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  oled_SDA_OUT(); 	    
    oled_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        oled_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		oled_IIC_SCL=1;
		delay_us(2); 
		oled_IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 oled_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	oled_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        oled_IIC_SCL=0; 
        delay_us(2);
		oled_IIC_SCL=1;
        receive<<=1;
        if(oled_READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        oled_IIC_NAck();//����nACK
    else
        oled_IIC_Ack(); //����ACK   
    return receive;
}



























