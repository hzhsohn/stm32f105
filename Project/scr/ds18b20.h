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

������ѭ��
	//------------------------------------------------------------------

					rWaterTemp=DS18B20_Get_Temp();
					if(rWaterTemp<2000 && rWaterTemp> -200) //ͻ���޷���
					{
						ntmp=rWaterTemp-rWaterTemperature;
						if(ntmp<20 && ntmp>-20)	//ͻ���޷���
						{
							isWaterTooHot=0;							
							if(rWaterTemp > 60*10) //����
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
u8 DS18B20_Init(void);			//��ʼ��DS18B20
s16 DS18B20_Get_Temp(void);		//��ȡ�¶�
void DS18B20_Start(void);			//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20 

#endif
