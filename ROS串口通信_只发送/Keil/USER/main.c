#include "delay.h"
#include "sys.h"
#include "usart.h" 	 
#include "timer.h"
#include "led.h"

 int main(void)
 {
	 int i=0;
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为115200
	LED_Init();
  TIM3_Int_Init(72-1,1000-1);
	while(1)
	{
		printf("Hello,Ros!\r\n");
		delay_ms(100);
	}
}	 


