#include "delay.h"
#include "sys.h"
#include "usart.h" 	 
#include "timer.h"
#include "led.h"

 int main(void)
 {
	 int i=0;
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();
  TIM3_Int_Init(72-1,1000-1);
	while(1)
	{
		printf("Hello,Ros!\r\n");
		delay_ms(100);
	}
}	 


