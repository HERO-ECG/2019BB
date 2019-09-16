#ifndef __PUBLIC_H
#define __PUBLIC_H

#include "stm32f10x.h"
#include "stm32f10x_it.h" 


struct Sense_Data{
	
	   float accl_origin_x;
		 float accl_origin_y;
	   float accl_origin_z;//accl ADC原始数据
	   float gyro_origin_x;
	   float gyro_origin_y;
	   float gyro_origin_z;//gyro ADC原始数据
		 float gyro_quiet_x;
	   float gyro_quiet_y;
	   float gyro_quiet_z;//角速度静差
	   float mag_origin_x;
		 float mag_origin_y;
		 float mag_origin_z;//磁力计 ADC原始数据
	
	   float accl_filtered_x;
		 float accl_filtered_y;
	   float accl_filtered_z;//加速度计低通滤波后数据
	   float gyro_filtered_x;
	   float gyro_filtered_y;
	   float gyro_filtered_z;//角速度低通滤波后数据
	   float mag_filtered_x;
	   float mag_filtered_y;
	   float mag_filtered_z;//磁力计低通滤波后数据
		 
		 float temperature;
	   float pressure_origin;
		 float pressure_filtered;
		 float altitude_orign;
		 float altitude_filtered;
		 float altitude_start_quiet;
            };
extern struct Sense_Data senser_datas;

#endif
