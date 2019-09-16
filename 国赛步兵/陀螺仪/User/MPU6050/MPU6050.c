#include "MPU6050.h"
#include "math.h"


IIC_STRUCT MPU_I2C;//MPU所用的IIC结构体

double accgyo[7]={0};	//原始加速度数据

ANGLE angle;//计算得出的角度结构体





/********************************************************
*函数名：MPUInit
*功能：初始化MPU引脚以及参数设置
*参数：无
*返回：无
***********************************************************************
*/
void MPU6050_Init(void)
{
	I2C_Struct_Config(&MPU_I2C,GPIOA,GPIO_Pin_5,GPIOA,GPIO_Pin_7);
	I2C_Simu_Init(MPU_I2C);
	I2C_delay_ms(200);
  I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,PWR_MGMT_1, 0x00);	//解除休眠状态
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,SMPLRT_DIV, 0x07);	 //SMPLRT_DIV=0x19
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,CONFIG, 0x06);		 ///CONFIG	低通滤波频率，典型值：0x06(5Hz)
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,GYRO_CONFIG, 0x18);	 //GYRO-CFG（陀螺仪配置） +-2000d/s
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,ACCEL_CONFIG, 0x01);	 //ACCEL（加速度计配置）  
}

/********************************************************
*函数名：MPU6050_GetRawAccelGyro
*功能：读取MPU所有的原始数据，包括加速度角速度和温度
*参数：double* AccelGyro，存储信息的地址
*返回：无
***********************************************************************
*/
void MPU6050_GetRawAccelGyro(double* AccelGyro) 
{

  uint8_t tmpBuffer[14],i; 
   I2C_ReadBuffer(MPU_I2C,MPU6050_I2C_ADDRESS , tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14);
/* Get acceleration */  
  for(i=0; i<3; i++) 												//加速度值
  {
		AccelGyro[i]=A*((int16_t)((uint16_t)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);		
	}
																						//温度值
	AccelGyro[3]=36.53+T*((int16_t)((uint16_t)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);
/* Get Angular rate */ 
  for(i=4; i<7; i++)												//角速度值
	{
		AccelGyro[i]=B*((int16_t)((uint16_t)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);           
	}
}

/********************************************************
*函数名：MPU6050_GetAngle
*功能：计算得出MPU6050的角度
*参数：无
*返回：无
***********************************************************************
*/

void MPU6050_GetAngle(void)
{
	MPU6050_GetRawAccelGyro(accgyo);
	accgyo[2]+=1.1;					//Z轴修正
	angle.angle_x=-(180*atan(accgyo[0]/accgyo[2])/3.1415)+90;
	if(accgyo[2]<0) angle.angle_x+=180;
	
	angle.angle_y=-(180*atan(accgyo[1]/accgyo[2])/3.1415)+90;
	if(accgyo[2]<0) angle.angle_y+=180;
	
}




