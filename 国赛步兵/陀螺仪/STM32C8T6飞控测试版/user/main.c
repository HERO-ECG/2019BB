#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_it.h"
#include "IIC.h"
#include "math.h"
#include "USART1.h"
#include "stdio.h"
#include "SYS_FUN.h"
#include "Tim.h"
#include "motor.h"
#include "filter.h"
#include "delay.h"
#include "usart2.h"
#include "gpio.h"
#include "public.h"
#include "HMC5983_spi.h"
#include "MPU6500_spi.h"

float data_mpu6050[3];

struct Sense_Data senser_datas;

int main()
{
	SystemClock_HSE(9);           //初始化系统时钟为8*6=48MHz;
  cycleCounterInit();				//得出当前系统时钟频率
  SysTick_Config(SystemCoreClock / 1000);	//SysTick精准延时,1ms

	UART1_init(SysClock,115200);   //串口1初始化
  USART2_Init(38400);  //GPS用
  //MotorInit();  //电机PWM口初始化
	IIC_Init();	
	SPI1_Init();
	TIM4_Init(SysClock,1000);//计时定时器 周期1ms
	NVIC_INIT();	    //中断初始化
	
	//MPU65xx_Init();  //mpu6500初始化
	//HMC5883L_Init();  //磁力计初始化
//	MS5611_Init();   //气压计初始化
	
//	MPU6500_spi_Init();	
//  HMC5983_spi_init();
//	MS5611_SPI_Init();
	
  //Low_Passfilter_Init(); //低通滤波器初始化
	//CommAppUpload();
	
	
  while(1)  
  {
//	  MPU6050AccRead(gyro);
//		gyro_filter[0]=LPF2pApply_4(gyro[0]);
//		gyro_filter[1]=LPF2pApply_5(gyro[1]);
//		gyro_filter[2]=LPF2pApply_6(gyro[2]);
//		//MPU6050GyroRead(gyro);
//	  for(i=0;i<3;i++)
//		{
//				data_mpu6050[i]=gyro[i];
//			  data_mpu6050[i+3]=gyro_filter[i];
//			 
//		}
//		MPU6500_spi_ReadALL(&senser_datas);
//		HMC5983_spi_Read_All(&senser_datas);
//		data_mpu6050[0]=senser_datas.mag_origin_x;
//		data_mpu6050[1]=senser_datas.mag_origin_y;
//		data_mpu6050[2]=senser_datas.mag_origin_z;
////		data_mpu6050[3]=senser_datas.gyro_origin_x;
////		data_mpu6050[4]=senser_datas.gyro_origin_y;
////		data_mpu6050[5]=senser_datas.gyro_origin_z;
//		MS5611_Get_Altittude();
//		MS5611_SPI_Get_Altittude();
//		USART1_SendData((unsigned char *)(&senser_datas.altitude_orign),sizeof(senser_datas.altitude_orign));
//		delay_ms(10);
		
  }     
}
