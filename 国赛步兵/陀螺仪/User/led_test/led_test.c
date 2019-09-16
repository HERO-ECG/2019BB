#include "led_test.h"

void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);	//开启时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;//设置引脚
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);//使能相应GPIO
}

