#include "led_test.h"

void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);	//����ʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�
	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;//��������
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);//ʹ����ӦGPIO
}

