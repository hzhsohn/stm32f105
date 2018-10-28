#include "system_init.h"
#include "Stm32f1_uart1.h"
#include "Stm32f1_uart2.h"
#include "Stm32f1_uart3.h"
#include "InputDrive.h"
#include "mini-data.h"
#include "ds18b20.h"
#include "Stm32f1_ADC1.h"
#include "Stm32f1_ADC2.h"
#include "ds18b20_1.h"
#include "watchdog.h"
#include "flash_rw.h"
#include "Stm32F1_Timer2.h"
#include "Stm32F1_Timer3.h"
#include "key.h"
#include "OutputDrive.h"

//--
//温度
int ntmp;
s16 rWaterTemperature=0,rWaterTemp=0,rGasTemperature=0,rGasTemp=0;
s16 rTrueWaterTemp=0,rTrueGasTemp=0;
int isCheckWaterSensorErr=0; //水温防错误限制
int isCheckDZCQSensorErr=0;

//气压
u16_t rPressure=0,rPressureTmp=0;
u16_t rTruePressure1=0;
//
//工作时间设置
TagTimeingSetting g_tmeSetting={0};


void aurtEventBtn(int i)
{
		uchar dst_buf[10]={0};
		int myDataLen=0;
		unsigned char cbuf[5]={0};
		cbuf[0]=0x01;
		cbuf[1]=i;
		myDataLen = miniDataCreate(2,cbuf,dst_buf);
		STM32F1_UART1SendDataS(dst_buf,myDataLen);
}

void setFlashData()
{
	char binFlag[4]={0};
	FLASH_ReadByte(STARTADDRFLAG ,(uint8_t*)binFlag,4);
	FLASH_ReadByte(STARTADDR ,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));
	
	if(!(binFlag[0]=='a' && binFlag[1]=='b' && binFlag[2]=='c' && binFlag[3]=='d'))
	{
			binFlag[0]='a';
			binFlag[1]='b';
			binFlag[2]='c';
			binFlag[3]='d';

			//初始化FLASH内容
			g_tmeSetting.pooDelay=1;					  //拉屎后多少秒启动 ,单位分钟
				
			FLASH_WriteByte(STARTADDRFLAG,(uint8_t*)binFlag,4);
			FLASH_WriteByte(STARTADDR,(uint8_t*)&g_tmeSetting,sizeof(g_tmeSetting));

	}
}
int main(void)
{
	EzhKeyEvent ev;
  EzhKeyState GPIOAStatus1;
  zhSCM_initKeyState(&GPIOAStatus1);
		
	STM32_Delay_init();
	STM32F1_UART1_Init(115200);
	STM32F1_UART2_Init(230400);
	STM32F1_UART3_Init(9600);
	
	DS18B20_Init();
	DS18B20_Init1();
	Adc_Init();
	Adc2_Init();	
	Stm32F1_Timer2Init();
	Stm32F1_Timer3Init();
	InputDriveInit();
	OutputDriveInit();

	//-----------------------------------------
	//获取FALSH数据
	setFlashData();
  //-----------------------------------------

	//看门狗
	//watchdog_init();
	
	while(1)
	{
			//看门狗
			//watchdog_action();
			//
			//---------------------
			//按键1		护卫键
			ev=zhSCM_keyState(&GPIOAStatus1,TOUCHKEY_1_GPIO,TOUCHKEY_1_PIN);
			switch(ev)
			{
				case ZH_KEY_EVENT_NONE:
					break;
				case ZH_KEY_EVENT_DOWN:
					break;
				case ZH_KEY_EVENT_PRESS:
					break;
				case ZH_KEY_EVENT_UP:
				 break;
			}
			//------------------------------------------------------------------
			//水温加热
			rWaterTemp=DS18B20_Get_Temp();
			if(rWaterTemp<2000 && rWaterTemp> -200) //限制位
			{
				ntmp=rWaterTemp-rWaterTemperature;
				if(ntmp<20 && ntmp>-20)	//限制突变幅度
				{
					//rTrueWaterTemp水的实际温度
					rTrueWaterTemp=rWaterTemp;
					isCheckWaterSensorErr=0;
				}
				rWaterTemperature=rWaterTemp;
			}
			else
			{
				isCheckWaterSensorErr++;						
				if(isCheckWaterSensorErr>10) //传感数据毛病太多关掉加热继电器
				{
					//传感器有毛病了.关掉继电器
				}
			}

			
			//------------------------------------------------------------------
			//裤档气压ADC			
			rPressureTmp = Get_Adc_Average(10);
			ntmp=rPressureTmp-rPressure;
			if(ntmp<60 && ntmp>-60) //限制突变幅度
			{
				//rTruePressure1气压参数
				rTruePressure1=rPressureTmp;
				isCheckDZCQSensorErr=0;
			}
			else
			{
				isCheckDZCQSensorErr++;						
				if(isCheckDZCQSensorErr>10) 
				{
					//传感数据有毛病关掉继电器
				}
			}
			rPressure=rPressureTmp;			
	}	
}
