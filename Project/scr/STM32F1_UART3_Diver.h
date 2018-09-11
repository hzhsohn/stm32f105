#ifndef __STM32F1_UART3_DIVER_H_
#define __STM32F1_UART3_DIVER_H_

#include "stm32f10x_usart.h"
#define u8_t unsigned char
#define u32_t unsigned int

void STM32F1_UART3SendData(u8_t nData);
void STM32F1_UART3SendDataS(u8_t* nData,u8_t nNum);
void STM32F1_UART3_Init(u32_t lBaudRate);

#endif
