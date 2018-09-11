
#include "stm32f10x.h"
#include "sysinit.h"
#include "Stm32f1_uart3_diver.h"

int main(void)
{
 u32 x=400000,i,count=0;

	//STM32_Delay_init();
	//STM32F1_UART1_Init(115200);
	//STM32F1_UART2_Init(230400);
	STM32F1_UART3_Init(9600);
	//DS18B20_Init();
	//Adc_Init();
	//Adc2_Init();
	//Stm32F1_Timer2Init();
	//Stm32F1_Timer3Init();
	
 Gpio_int(); 
 while(1)
 {	 
    for(i=0;i<x;i++); 		
	if((count&0x01)==1) GPIO_ResetBits(GPIOC,GPIO_Pin_13);   //'0'ºìÉ«ÁÁ
	else 	 GPIO_SetBits(GPIOC,GPIO_Pin_13);
	count=1-count;
   } 	  
 
	 
}
																 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
