#ifndef _MPU6500_spi_H
#define _MPU6500_spi_H

#include "stm32f10x.h"
#include "spi.h"
#include "delay.h"

struct Sense_Data{
	
	   float accl_origin_x;
		 float accl_origin_y;
	   float accl_origin_z;//accl ADC原始数据
	   float gyro_origin_x;
	   float gyro_origin_y;
		 float gyro_origin_z;//gyro ADC原始数据
	
	   float gyro_compensated_x;
	   float gyro_compensated_y;
	   float gyro_compensated_z;//gyro 零飘修正
	
		 float gyro_offset_x;
	   float gyro_offset_y;
	   float gyro_offset_z;//gyro 零飘修正
	
		 float temperature;
		 
		 int16_t gyro_x;
		 int16_t gyro_y;
		 int16_t gyro_z;
		 
		 uint8_t still;
		 uint8_t autojust;
		 uint8_t err_code;
 };
extern struct Sense_Data senser_datas;
//寄存器定义
#define SELF_TEST_X_GYRO		0X00
#define SELF_TEST_Y_GYRO		0X01
#define SELF_TEST_Z_GYRO		0X02

#define SELF_TEST_X_ACCEL		0X0D
#define SELF_TEST_Y_ACCEL		0X0E
#define SELF_TEST_Z_ACCEL		0X0F

#define XG_OFFSET_H					0X13
#define XG_OFFSET_L					0X14
#define YG_OFFSET_H					0X15
#define YG_OFFSET_L					0X16
#define ZG_OFFSET_H					0X17
#define ZG_OFFSET_L					0X18

#define SMPLRT_DIV					0X19 //陀螺仪采样率
#define CONFIG							0X1A //低通滤波器  典型值0x06 5hz
#define GYRO_CONFIG					0X1B //陀螺仪测量范围 0X18 正负2000度
#define ACCEL_CONFIG				0X1C //加速度计测量范围 0X18 正负16g
#define ACCEL_CONFIG2				0X1D //加速度计低通滤波器 0x06 5hz

#define LP_ACCEL_ODR				0X1E
#define WOM_THR							0X1F
#define FIFO_EN							0X23

#define ACCEL_XOUT_H				0X3B  //加速度计输出数据
#define ACCEL_XOUT_L				0X3C
#define ACCEL_YOUT_H				0X3D
#define ACCEL_YOUT_L				0X3E
#define ACCEL_ZOUT_H				0X3F
#define ACCEL_ZOUT_L				0X40

#define TEMP_OUT_H					0X41  //温度计输出数据
#define TEMP_OUT_L					0X42

#define GYRO_XOUT_H					0X43  //陀螺仪输出数据
#define GYRO_XOUT_L					0X44
#define GYRO_YOUT_H					0X45
#define GYRO_YOUT_L					0X46
#define GYRO_ZOUT_H					0X47
#define GYRO_ZOUT_L					0X48

#define SIGNAL_PATH_RESET   0X68 //陀螺仪、加速度计、温度传感器信号复位
#define USER_CTRL						0X6A //用户配置 当为0X10时使用SPI模式
#define PWR_MGMT_1					0X6B //电源管理1 典型值为0x00
#define PWR_MGMT_2					0X6C //电源管理2 典型值为0X00

#define WHO_AM_I						0X75 //器件ID MPU9250默认ID为0X71
#define WHO_AM_MAG					0X00 //器件ID MPU9250默认ID为0X71



void  MPU65xx_ACCL_newValues(int16_t x,int16_t y,int16_t z);
void  MPU65xx_GYRO_newValues(int16_t x,int16_t y,int16_t z);
u8 MPU6500_Write_Reg(uint8_t reg,uint8_t value);
u8 MPU6500_Read_Reg(uint8_t reg);
void MPU6500_spi_Check(void);
void MPU6500_spi_ReadALL(struct Sense_Data *SensorTemp);
void MPU6500_spi_Init(void);


#endif



