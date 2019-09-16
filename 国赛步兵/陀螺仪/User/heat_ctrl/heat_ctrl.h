#ifndef __HEAT_CTRL_H
#define __HEAT_CTRL_H

#include "stm32f10x.h"




#define Min 600


/********************TIM�������壬ֻ��TIM2��3��4��5**************************/
#define             HEAT_CTRL_TIM                               TIM3

#define             HEAT_CTRL_TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             HEAT_CTRL_TIM_CLK                             RCC_APB1Periph_TIM3
#define             HEAT_CTRL_TIM_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             HEAT_CTRL_TIM_GPIO_CLK                        RCC_APB2Periph_GPIOB

#define             HEAT_CTRL_TIM_PORT                        GPIOB
#define             HEAT_CTRL_TIM_PIN                         GPIO_Pin_1
#define             HEAT_CTRL_TIM_OCxInit                         TIM_OC4Init            //ͨ��ѡ��1~4
#define             HEAT_CTRL_TIM_OCxPreloadConfig                TIM_OC4PreloadConfig  
#define             CCRx                                CCR4

void                HEAT_CTRL_TIM_PWM_Init                 (void);

void HEAT_Ctrl(float set_temp);
#endif
