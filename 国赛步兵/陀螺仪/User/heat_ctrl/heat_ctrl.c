  
#include "heat_ctrl.h"
#include "PID.h"
#include "MPU65xx.h"
struct PID PID_heat;

static void HEAT_CTRL_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOB clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
  HEAT_CTRL_TIM_GPIO_APBxClock_FUN  ( HEAT_CTRL_TIM_GPIO_CLK, ENABLE );

  /* 配置呼吸灯用到的PB0引脚 */
  GPIO_InitStructure.GPIO_Pin =  HEAT_CTRL_TIM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init( HEAT_CTRL_TIM_PORT , &GPIO_InitStructure );
	

}


/**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */

/**
  * @brief  配置TIM3输出的PWM信号的模式，如周期、极性
  * @param  无
  * @retval 无
  */

/*
 * HEAT_CTRL_TIMCLK/CK_PSC --> HEAT_CTRL_TIMCNT --> HEAT_CTRL_TIM_ARR --> 中断 & HEAT_CTRL_TIMCNT 重新计数
 *                    HEAT_CTRL_TIM_CCR(电平发生变化)
 *
 * 信号周期=(HEAT_CTRL_TIM_ARR +1 ) * 时钟周期
 * 
 */

/*    _______    ______     _____      ____       ___        __         _
 * |_|       |__|      |___|     |____|    |_____|   |______|  |_______| |________|
 */
static void HEAT_CTRL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	
	/* 设置TIM3CLK 时钟为72MHZ */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 					//使能TIM3时钟
	HEAT_CTRL_TIM_APBxClock_FUN ( HEAT_CTRL_TIM_CLK, ENABLE );

  /* 基本定时器配置 */		 
  TIM_TimeBaseStructure.TIM_Period = 9999;       							  //当定时器从0计数到255，即为256次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 71;	    							//设置预分频：
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//设置时钟分频系数：不分频(这里用不到)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//向上计数模式
  TIM_TimeBaseInit(HEAT_CTRL_TIM, &TIM_TimeBaseStructure);

  /* PWM模式配置 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
  TIM_OCInitStructure.TIM_Pulse = 0;										  			//设置初始PWM脉冲宽度为0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为低电平

  HEAT_CTRL_TIM_OCxInit ( HEAT_CTRL_TIM, &TIM_OCInitStructure );	 									//使能通道3								//使能通道4
	
	

  HEAT_CTRL_TIM_OCxPreloadConfig ( HEAT_CTRL_TIM, TIM_OCPreload_Enable );						//使能预装载	

  TIM_ARRPreloadConfig(HEAT_CTRL_TIM, ENABLE);			 										//使能TIM3重载寄存器ARR
	

  /* TIM3 enable counter */
  TIM_Cmd(HEAT_CTRL_TIM, ENABLE);                   										//使能定时器3	

	
}

/**
  * @brief  TIM3 呼吸灯初始化
  *         配置PWM模式和GPIO
  * @param  无
  * @retval 无
  */
void HEAT_CTRL_TIM_PWM_Init(void)
{
	HEAT_CTRL_TIM_GPIO_Config();
	HEAT_CTRL_TIM_Mode_Config();	
	PIDdataInit(&PID_heat,7000,60,1000,6000,-6000,9999,0);
}

void HEAT_Ctrl(float set_temp)
{
	if(senser_datas.err_code==0)
	{
		PID_heat.set=set_temp;
		PID_heat.feedback=senser_datas.temperature;
		PIDUpData(&PID_heat);
		GetPID(&PID_heat);
		HEAT_CTRL_TIM->CCRx=PID_heat.out;
	}
	else
		HEAT_CTRL_TIM->CCRx=0;
}

/*********************************************END OF FILE**********************/

