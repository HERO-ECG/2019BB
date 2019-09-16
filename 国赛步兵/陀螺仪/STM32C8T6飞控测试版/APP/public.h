#ifndef __PUBLIC_H
#define __PUBLIC_H

#include "stm32f10x.h"
#include "stm32f10x_it.h" 


struct Sense_Data{
	
	   float accl_origin_x;
		 float accl_origin_y;
	   float accl_origin_z;//accl ADCԭʼ����
	   float gyro_origin_x;
	   float gyro_origin_y;
	   float gyro_origin_z;//gyro ADCԭʼ����
		 float gyro_quiet_x;
	   float gyro_quiet_y;
	   float gyro_quiet_z;//���ٶȾ���
	   float mag_origin_x;
		 float mag_origin_y;
		 float mag_origin_z;//������ ADCԭʼ����
	
	   float accl_filtered_x;
		 float accl_filtered_y;
	   float accl_filtered_z;//���ٶȼƵ�ͨ�˲�������
	   float gyro_filtered_x;
	   float gyro_filtered_y;
	   float gyro_filtered_z;//���ٶȵ�ͨ�˲�������
	   float mag_filtered_x;
	   float mag_filtered_y;
	   float mag_filtered_z;//�����Ƶ�ͨ�˲�������
		 
		 float temperature;
	   float pressure_origin;
		 float pressure_filtered;
		 float altitude_orign;
		 float altitude_filtered;
		 float altitude_start_quiet;
            };
extern struct Sense_Data senser_datas;

#endif
