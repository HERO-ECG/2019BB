#include "MPU6050.h"
#include "math.h"


IIC_STRUCT MPU_I2C;//MPU���õ�IIC�ṹ��

double accgyo[7]={0};	//ԭʼ���ٶ�����

ANGLE angle;//����ó��ĽǶȽṹ��





/********************************************************
*��������MPUInit
*���ܣ���ʼ��MPU�����Լ���������
*��������
*���أ���
***********************************************************************
*/
void MPU6050_Init(void)
{
	I2C_Struct_Config(&MPU_I2C,GPIOA,GPIO_Pin_5,GPIOA,GPIO_Pin_7);
	I2C_Simu_Init(MPU_I2C);
	I2C_delay_ms(200);
  I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,PWR_MGMT_1, 0x00);	//�������״̬
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,SMPLRT_DIV, 0x07);	 //SMPLRT_DIV=0x19
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,CONFIG, 0x06);		 ///CONFIG	��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,GYRO_CONFIG, 0x18);	 //GYRO-CFG�����������ã� +-2000d/s
	I2C_Single_Write(MPU_I2C,MPU6050_I2C_ADDRESS  ,ACCEL_CONFIG, 0x01);	 //ACCEL�����ٶȼ����ã�  
}

/********************************************************
*��������MPU6050_GetRawAccelGyro
*���ܣ���ȡMPU���е�ԭʼ���ݣ��������ٶȽ��ٶȺ��¶�
*������double* AccelGyro���洢��Ϣ�ĵ�ַ
*���أ���
***********************************************************************
*/
void MPU6050_GetRawAccelGyro(double* AccelGyro) 
{

  uint8_t tmpBuffer[14],i; 
   I2C_ReadBuffer(MPU_I2C,MPU6050_I2C_ADDRESS , tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14);
/* Get acceleration */  
  for(i=0; i<3; i++) 												//���ٶ�ֵ
  {
		AccelGyro[i]=A*((int16_t)((uint16_t)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);		
	}
																						//�¶�ֵ
	AccelGyro[3]=36.53+T*((int16_t)((uint16_t)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);
/* Get Angular rate */ 
  for(i=4; i<7; i++)												//���ٶ�ֵ
	{
		AccelGyro[i]=B*((int16_t)((uint16_t)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);           
	}
}

/********************************************************
*��������MPU6050_GetAngle
*���ܣ�����ó�MPU6050�ĽǶ�
*��������
*���أ���
***********************************************************************
*/

void MPU6050_GetAngle(void)
{
	MPU6050_GetRawAccelGyro(accgyo);
	accgyo[2]+=1.1;					//Z������
	angle.angle_x=-(180*atan(accgyo[0]/accgyo[2])/3.1415)+90;
	if(accgyo[2]<0) angle.angle_x+=180;
	
	angle.angle_y=-(180*atan(accgyo[1]/accgyo[2])/3.1415)+90;
	if(accgyo[2]<0) angle.angle_y+=180;
	
}




