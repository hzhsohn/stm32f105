#ifndef __DS18B20_H
#define __DS18B20_H

#include "system_init.h"
#include "STM32_Delay.h"

/*

int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0;
s16 rTrueWaterTemp=0;
int isWaterTooHot=0;
int isCheckWaterSensorErr=0; 

放在主循环
	//------------------------------------------------------------------

					rWaterTemp=DS18B20_Get_Temp();
					if(rWaterTemp<2000 && rWaterTemp> -200) //突变限幅度
					{
						ntmp=rWaterTemp-rWaterTemperature;
						if(ntmp<20 && ntmp>-20)	//突变限幅度
						{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //过热
							{
								isWaterTooHot=1;
							}
							else if(rWaterTemp<g_tmeSetting.waterTemperature*10 && 0==bCleanWaterLow) //????40????
							{
 								udoWaterHeating(1);
							}
							else
							{
								udoWaterHeating(0);
							}
							rTrueWaterTemp=rWaterTemp;
							isCheckWaterSensorErr=0;
						}
						rWaterTemperature=rWaterTemp;
					}
					else
					{
						isCheckWaterSensorErr++;						
						if(isCheckWaterSensorErr>10) //???????????????
						{
							//???????.?????
							if(g_cCleanCurrentSence==0)
							{	udoWaterHeating(0);}
						}
					}

*/

#define DS18B20_DQ_GPIO 	    GPIOA
#define DS18B20_DQ_PIN  	    GPIO_Pin_5
#define DS18B20_DQ_STATE(x) (x)>0?GPIO_SetBits(DS18B20_DQ_GPIO,DS18B20_DQ_PIN):GPIO_ResetBits(DS18B20_DQ_GPIO,DS18B20_DQ_PIN)
#define DS18B20_DQ_GET() GPIO_ReadInputDataBit(DS18B20_DQ_GPIO,DS18B20_DQ_PIN)
u8 DS18B20_Init(void);			//初始化DS18B20
s16 DS18B20_Get_Temp(void);		//获取温度
void DS18B20_Start(void);			//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20 

#endif
