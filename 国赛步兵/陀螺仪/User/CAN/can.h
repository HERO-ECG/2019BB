#ifndef  __BSP_CAN_H_
#define  __BSP_CAN_H_
#include "stm32f10x.h"

#define PASS_ID      ((uint32_t)0x1315)

#define CAN_TX_GPIO_PORT    GPIOA
#define CAN_TX_GPIO_PIN     GPIO_Pin_12

#define CAN_RX_GPIO_PORT    GPIOA
#define CAN_RX_GPIO_PIN     GPIO_Pin_11

#define CAN_GPIO_CLK        RCC_APB2Periph_GPIOA
#define CAN_APBx_CLK_CMD    RCC_APB1PeriphClockCmd     
#define CAN_CLK             RCC_APB1Periph_CAN1

#define V_OPEN     220
#define V_CLOSE    200

#define OPEN				0x00//超级电容放电
#define CLOSE       0x01//电池给底盘供电

#define   Current_40W   ((float)40/26.0)
#define   Current_80W   ((float)80/26.0)
	

void CAN_Config(void);
uint8_t CAN_TransmitPower(uint8_t *DataBuff);
#endif  /*__BSP_CAN_H_*/
