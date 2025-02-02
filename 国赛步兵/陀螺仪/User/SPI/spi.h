#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"


#define SPI1_CS1_Disable 		GPIO_SetBits(GPIOA,GPIO_Pin_4)		//PB0		MPU6500
#define SPI1_CS1_Enable 	  GPIO_ResetBits(GPIOA,GPIO_Pin_4)




void SPI1_Init(void);
u8 SPI1_Read_Write_Byte(uint8_t TxData);

#endif
