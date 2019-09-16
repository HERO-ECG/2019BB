#ifndef TIMEBASE_H
#define TIMEBASE_H


#include "stm32f10x.h"


/********************基本定时器TIM参数定义，只限TIM6、7************/
#define macTIM4 // 如果使用TIM7，注释掉这个宏即可

#ifdef  macTIM4 // 使用基本定时器TIM6
#define             macTIMbasex                 TIM4
#define             macTIM_APBxClock_FUN    RCC_APB1PeriphClockCmd
#define             macTIM_CLK              RCC_APB1Periph_TIM4
#define             macTIM_IRQ              TIM4_IRQn
#define             macTIM_INT_FUN          TIM4_IRQHandler

#else  // 使用基本定时器TIM7
#define             macTIMbasex                 TIM7
#define             macTIM_APBxClock_FUN    RCC_APB1PeriphClockCmd
#define             macTIM_CLK              RCC_APB1Periph_TIM7
#define             macTIM_IRQ              TIM7_IRQn
#define             macTIM_INT_FUN          TIM7_IRQHandler

#endif
/**************************函数声明********************************/
void               TIMx_NVIC_Configuration                   (void);
void               TIMx_Configuration                        (void);
void 						   Timebase_Init									   					(void);

#endif	/* TIME_TEST_H */
/*
void macTIM_INT_FUN (void)
{
	
	if(TIM_GetFlagStatus(macTIMbasex ,TIM_FLAG_Update)==SET)
	{
					TIM_ClearITPendingBit(macTIMbasex , TIM_FLAG_Update); 
	}
	
}

*/

