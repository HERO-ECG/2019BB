  
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

  /* ���ú������õ���PB0���� */
  GPIO_InitStructure.GPIO_Pin =  HEAT_CTRL_TIM_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init( HEAT_CTRL_TIM_PORT , &GPIO_InitStructure );
	

}


/**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */

/**
  * @brief  ����TIM3�����PWM�źŵ�ģʽ�������ڡ�����
  * @param  ��
  * @retval ��
  */

/*
 * HEAT_CTRL_TIMCLK/CK_PSC --> HEAT_CTRL_TIMCNT --> HEAT_CTRL_TIM_ARR --> �ж� & HEAT_CTRL_TIMCNT ���¼���
 *                    HEAT_CTRL_TIM_CCR(��ƽ�����仯)
 *
 * �ź�����=(HEAT_CTRL_TIM_ARR +1 ) * ʱ������
 * 
 */

/*    _______    ______     _____      ____       ___        __         _
 * |_|       |__|      |___|     |____|    |_____|   |______|  |_______| |________|
 */
static void HEAT_CTRL_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;																				
	
	
	/* ����TIM3CLK ʱ��Ϊ72MHZ */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 					//ʹ��TIM3ʱ��
	HEAT_CTRL_TIM_APBxClock_FUN ( HEAT_CTRL_TIM_CLK, ENABLE );

  /* ������ʱ������ */		 
  TIM_TimeBaseStructure.TIM_Period = 9999;       							  //����ʱ����0������255����Ϊ256�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 71;	    							//����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
  TIM_TimeBaseInit(HEAT_CTRL_TIM, &TIM_TimeBaseStructure);

  /* PWMģʽ���� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = 0;										  			//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ

  HEAT_CTRL_TIM_OCxInit ( HEAT_CTRL_TIM, &TIM_OCInitStructure );	 									//ʹ��ͨ��3								//ʹ��ͨ��4
	
	

  HEAT_CTRL_TIM_OCxPreloadConfig ( HEAT_CTRL_TIM, TIM_OCPreload_Enable );						//ʹ��Ԥװ��	

  TIM_ARRPreloadConfig(HEAT_CTRL_TIM, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR
	

  /* TIM3 enable counter */
  TIM_Cmd(HEAT_CTRL_TIM, ENABLE);                   										//ʹ�ܶ�ʱ��3	

	
}

/**
  * @brief  TIM3 �����Ƴ�ʼ��
  *         ����PWMģʽ��GPIO
  * @param  ��
  * @retval ��
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

