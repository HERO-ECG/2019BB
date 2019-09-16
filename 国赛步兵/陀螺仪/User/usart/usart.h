#ifndef _USART_H
#define _USART_H


#include "stm32f10x.h"
#include <stdio.h>

/***********************串口硬件配置******************************************/
#define             USART1_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define             USART1_CLK                             RCC_APB2Periph_USART1
#define             USART1_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             USART1_GPIO_CLK                        (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)     
#define             USART1_TX_PORT                         GPIOA   
#define             USART1_TX_PIN                          GPIO_Pin_9
#define             USART1_RX_PORT                         GPIOA  
#define             USART1_RX_PIN                          GPIO_Pin_10



/*************************函数声明******************************************/
void USART1_Config(uint16_t baudrate);
void NVIC_USART1_Configuration(void);
int fputc(int ch, FILE *f);
#endif
