#ifndef __STM32F1_ADC1_DIVER_H_
#define __STM32F1_ADC1_DIVER_H_
#include "system_init.h"

/*
u16_t rPressure=0,rPressureTmp=0;
u16_t rTruePressure1=0;
int isCheckDZCQSensorErr=0;
//------------------------------------------------------------------

rPressureTmp = Get_Adc_Average(10);
ntmp=rPressureTmp-rPressure;
if(ntmp<60 && ntmp>-60) //ÏÞÖÆÍ»±ä
{
	if(rPressureTmp<g_tmeSetting.crotchPressure*100)
	{

	}
	else
	{

	}
	rTruePressure1=rPressureTmp;
	isCheckDZCQSensorErr=0;
}
else
{
	isCheckDZCQSensorErr++;						
	if(isCheckDZCQSensorErr>10)
	{
		if(g_cCleanCurrentSence==0)
		{	udoKuZiCongQi(0);}
	}
}
rPressure=rPressureTmp;

*/
void Adc_Init(void);
u16 Get_Adc_Average(u8 times);
#endif
