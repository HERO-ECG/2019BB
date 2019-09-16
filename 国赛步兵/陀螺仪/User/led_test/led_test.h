#ifndef __LED_TEST_H
#define __LED_TEST_H

#include "stm32f10x.h"


/**********************相关宏定义******************************/
#define LED_GPIO_PORT	GPIOB
#define	LED_GPIO_PIN	GPIO_Pin_0
#define LED_GPIO_CLK	RCC_APB2Periph_GPIOB

#define LED_OFF				GPIO_SetBits(LED_GPIO_PORT,LED_GPIO_PIN)//LED宏定义
#define LED_ON				GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN)

void LED_GPIO_Init(void);
#endif

