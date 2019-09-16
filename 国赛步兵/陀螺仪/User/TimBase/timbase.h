#ifndef TIMEBASE_H
#define TIMEBASE_H


#include "stm32f10x.h"


/********************������ʱ��TIM�������壬ֻ��TIM6��7************/
#define macTIM4 // ���ʹ��TIM7��ע�͵�����꼴��

#ifdef  macTIM4 // ʹ�û�����ʱ��TIM6
#define             macTIMbasex                 TIM4
#define             macTIM_APBxClock_FUN    RCC_APB1PeriphClockCmd
#define             macTIM_CLK              RCC_APB1Periph_TIM4
#define             macTIM_IRQ              TIM4_IRQn
#define             macTIM_INT_FUN          TIM4_IRQHandler

#else  // ʹ�û�����ʱ��TIM7
#define             macTIMbasex                 TIM7
#define             macTIM_APBxClock_FUN    RCC_APB1PeriphClockCmd
#define             macTIM_CLK              RCC_APB1Periph_TIM7
#define             macTIM_IRQ              TIM7_IRQn
#define             macTIM_INT_FUN          TIM7_IRQHandler

#endif
/**************************��������********************************/
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

