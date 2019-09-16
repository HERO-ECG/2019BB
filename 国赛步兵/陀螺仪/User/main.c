#include "stm32f10x.h"
#include "usart.h"
#include "timbase.h"
#include "led_test.h"
#include "can.h"
#include "delay.h"
#include "MPU6500_spi.h"
#include "I2C_simu.h"
#include "MPU65xx.h"
#include "heat_ctrl.h"
#include "PID.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	delay_init(72);
	LED_GPIO_Init();
	
	SPI1_Init();
	MPU65xx_Init();
	HEAT_CTRL_TIM_PWM_Init();
	CAN_Config();
	Timebase_Init();
	while( 1 )
	{

	}
}

	


