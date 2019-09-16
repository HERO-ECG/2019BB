#include "MPU65xx.h"
#include "I2C_simu.h"
#include "math.h"

IIC_STRUCT MPU65XX_I2C;

int16_t  MPU6500_ACCL_FIFO[3][9];
int16_t  MPU6500_GYRO_FIFO[3][9];

/**************************????********************************************
	   void  MPU65xx_newValues(int16_t x,int16_t y,int16_t z)
功能:	  均值滤波，更新FIFO数组
输入:  最新ADC值
*******************************************************************************/
void  MPU6500_ACCL_newValues(int16_t x,int16_t y,int16_t z)
{
	unsigned char i ;
	int32_t sum=0;

	for(i=1;i<8;i++){
		MPU6500_ACCL_FIFO[0][i-1]=MPU6500_ACCL_FIFO[0][i];
		MPU6500_ACCL_FIFO[1][i-1]=MPU6500_ACCL_FIFO[1][i];
		MPU6500_ACCL_FIFO[2][i-1]=MPU6500_ACCL_FIFO[2][i];
	}

	MPU6500_ACCL_FIFO[0][7]=x;
	MPU6500_ACCL_FIFO[1][7]=y;
	MPU6500_ACCL_FIFO[2][7]=z;

	sum=0;
	for(i=0;i<8;i++){	//??????????????
   		sum+=MPU6500_ACCL_FIFO[0][i];
	}
	MPU6500_ACCL_FIFO[0][8]=sum/10;	//??????

	sum=0;
	for(i=0;i<8;i++){
   		sum+=MPU6500_ACCL_FIFO[1][i];
	}
	MPU6500_ACCL_FIFO[1][8]=sum/10;

	sum=0;
	for(i=0;i<8;i++){
   		sum+=MPU6500_ACCL_FIFO[2][i];
	}
	MPU6500_ACCL_FIFO[2][8]=sum/10;
} //HMC58X3_newValues


/**************************????********************************************
	   void  MPU65xx_newValues(int16_t x,int16_t y,int16_t z)
功能:	  均值滤波，更新FIFO数组
输入:  最新ADC值
*******************************************************************************/
void  MPU6500_GYRO_newValues(int16_t x,int16_t y,int16_t z)
{
	unsigned char i ;
	int32_t sum=0;

	for(i=1;i<8;i++){
		MPU6500_GYRO_FIFO[0][i-1]=MPU6500_GYRO_FIFO[0][i];
		MPU6500_GYRO_FIFO[1][i-1]=MPU6500_GYRO_FIFO[1][i];
		MPU6500_GYRO_FIFO[2][i-1]=MPU6500_GYRO_FIFO[2][i];
	}

	MPU6500_GYRO_FIFO[0][7]=x;
	MPU6500_GYRO_FIFO[1][7]=y;
	MPU6500_GYRO_FIFO[2][7]=z;

	sum=0;
	for(i=0;i<8;i++){	//??????????????
   		sum+=MPU6500_GYRO_FIFO[0][i];
	}
	MPU6500_GYRO_FIFO[0][8]=sum/10;	//??????

	sum=0;
	for(i=0;i<8;i++){
   		sum+=MPU6500_GYRO_FIFO[1][i];
	}
	MPU6500_GYRO_FIFO[1][8]=sum/10;

	sum=0;
	for(i=0;i<8;i++){
   		sum+=MPU6500_GYRO_FIFO[2][i];
	}
	MPU6500_GYRO_FIFO[2][8]=sum/10;
} //HMC58X3_newValues






/*************************
检测是否挂载mpu6500，读 WHO AM I 地址，返回具体型号
  mpu6500----0x70(此地址并非iic通讯的器件地址)
**************************/
	u8 IDtemp;
uint8_t add_test;
void MPU65xx_Check()
{
	uint8_t err_time=0;
	//IDtemp=I2C_ReadOneByte(0xD0,0x75);

//	while(!I2C_CheckDevice(MPU65XX_I2C,add_test))
//		add_test++;
	I2C_ReadBuffer(MPU65XX_I2C,MPU65xx_devAddr,&IDtemp,0x75, 1);
//	IICreadBytes(0xd0,0x75,1,&IDtemp);
//	printf("%c",IDtemp);
//
	while(IDtemp!=0x70&&senser_datas.err_code==0)
	{
		err_time++;
			I2C_ReadBuffer(MPU65XX_I2C,MPU65xx_devAddr,&IDtemp,0x75, 1);
		if(err_time>100)
		{
			senser_datas.err_code=1;
		}
	}
//	else
//		printf("MPU65xx not found...\r\n");
}

/**************************????********
原型:		void MPU6050_initialize(void)
功能:	   初始化mpu6500进入使用状态
**************************************/
void MPU65xx_Init(void) {
	
	//I2C_Struct_Config(&MPU65XX_I2C,GPIOA,GPIO_Pin_8,GPIOA,GPIO_Pin_9);
	I2C_Struct_Config(&MPU65XX_I2C,GPIOA,GPIO_Pin_5,GPIOA,GPIO_Pin_7);
	I2C_Simu_Init(MPU65XX_I2C);
	
	   delay_ms(200);
	
	  MPU65xx_Check();

	
		I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_PWR_MGMT_1, 0x80);      //PWR_MGMT_1    -- DEVICE_RESET 1
	delay_ms(50);
    I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_SMPLRT_DIV, 0x00);      //1000hz      --SMPLRT_DIV    -- SMPLRT_DIV = 0  Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_PWR_MGMT_1, 0x03);      //PWR_MGMT_1    -- SLEEP 0; CYCLE 0; TEMP_DIS 0; CLKSEL 3 (PLL with Z Gyro reference)
    I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_INT_PIN_CFG, 0 << 7 | 0 << 6 | 0 << 5 | 0 << 4 | 0 << 3 | 0 << 2 | 1 << 1 | 0 << 0);  // INT_PIN_CFG   -- INT_LEVEL_HIGH, INT_OPEN_DIS, LATCH_INT_DIS, INT_RD_CLEAR_DIS, FSYNC_INT_LEVEL_HIGH, FSYNC_INT_DIS, I2C_BYPASS_EN, CLOCK_DIS
    I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_CONFIG, MPU6050_DLPF_BW_42);  //CONFIG        -- EXT_SYNC_SET 0 (disable input pin for data sync) ; default DLPF_CFG = 0 => ACC bandwidth = 260Hz  GYRO bandwidth = 256Hz)
		I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_GYRO_CONFIG, 0x18);       //+- 2000 dps
		I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr,MPU6050_RA_SMPLRT_DIV,0x00);
    I2C_Single_Write(MPU65XX_I2C,MPU65xx_devAddr, MPU6050_RA_ACCEL_CONFIG, 0x10);      // Accel scale 8g (4096 LSB/g)
    
//	  printf("MPU65xx init success...\r\n");
}


//读accl
void MPU65xxAccRead(int16_t *accData)       //int16_t = short int  
{
    uint8_t buf[8];

    //IICreadBytes(MPU65xx_devAddr, MPU6050_RA_ACCEL_XOUT_H, 6, buf);
	I2C_ReadBuffer(MPU65XX_I2C,MPU65xx_devAddr,buf,MPU6050_RA_ACCEL_XOUT_H, 8);
    accData[0] = (int16_t)((buf[0] << 8) | buf[1]);
    accData[1] = (int16_t)((buf[2] << 8) | buf[3]);
    accData[2] = (int16_t)((buf[4] << 8) | buf[5]);
		accData[3] = (int16_t)((buf[6] << 8) | buf[7]);


}
//读gyro
void MPU65xxGyroRead(int16_t *gyroData)
{
    uint8_t buf[6];

  //  IICreadBytes(MPU65xx_devAddr, MPU6050_RA_GYRO_XOUT_H, 6, buf);
	I2C_ReadBuffer(MPU65XX_I2C,MPU65xx_devAddr,buf,MPU6050_RA_GYRO_XOUT_H, 6);
    gyroData[0] = (int16_t)((buf[0] << 8) | buf[1]) ;
    gyroData[1] = (int16_t)((buf[2] << 8) | buf[3]) ;
    gyroData[2] = (int16_t)((buf[4] << 8) | buf[5]) ;
}

void MPU6xxx_ReadAll(struct Sense_Data *SensorTemp)
{
	int16_t acc[4],gyro[3];
	
	MPU65xxAccRead(acc);
	MPU65xxGyroRead(gyro);
	
	//归一化
	SensorTemp->accl_origin_x=(float)acc[0]/4096;
	SensorTemp->accl_origin_y=(float)acc[1]/4096;
	SensorTemp->accl_origin_z=(float)acc[2]/4096;
	SensorTemp->gyro_origin_x=(float)gyro[0]/16.384;
	SensorTemp->gyro_origin_y=(float)gyro[1]/16.384;
	SensorTemp->gyro_origin_z=(float)gyro[2]/16.384;
	SensorTemp->temperature=(float)acc[3]/256;
	
	SensorTemp->gyro_compensated_x=SensorTemp->gyro_origin_x-SensorTemp->gyro_offset_x;
	SensorTemp->gyro_compensated_y=SensorTemp->gyro_origin_y-SensorTemp->gyro_offset_y;
	SensorTemp->gyro_compensated_z=SensorTemp->gyro_origin_z-SensorTemp->gyro_offset_z;
	
	SensorTemp->gyro_x=gyro[0];
	SensorTemp->gyro_y=gyro[1];
	SensorTemp->gyro_z=gyro[2];
}


#define SET 0
#define GET 1

float pitch_history[50];
float yaw_history[50];
float roll_history[50];

void GyroQueue(float *pitch,float *yaw,float *roll,uint16_t index,uint8_t mode)
{
	static uint16_t pointer;


	if(mode==SET)
	{
		pointer++;
		if(pointer==50)
			pointer=0;
		pitch_history[pointer]=*pitch;
		yaw_history[pointer]=*yaw;
		roll_history[pointer]=*roll;
	}
	else
	{
		if(index>=50)
		{
			*pitch=0;
			*yaw=0;
			*roll=0;
		}
		else
		{
			if(index<pointer)
			{
				*pitch=pitch_history[pointer-index];
				*yaw=yaw_history[pointer-index];
				*roll=roll_history[pointer-index];
			}
			else
			{
				*pitch=pitch_history[50-index+pointer-1];
				*yaw=yaw_history[50-index+pointer-1];
				*roll=roll_history[50-index+pointer-1];
			}
		}
	}
}

float GetVariance(float *data,uint16_t length)
{
	float average;
	float sum=0;
	float variance;
	uint16_t i;
	
	for(i=0;i<length;i++)
		sum+=data[i];
	average=sum/length;
	for(i=0;i<length;i++)
		variance+=(data[i]-average)*(data[i]-average)/length;
	return variance;
}

float GetAverage(float *data,uint16_t length)
{
	float average;
	float sum=0;
	uint16_t i;
	
	for(i=0;i<length;i++)
		sum+=data[i];
	average=sum/length;
	return average;
}
uint16_t still_counter;
float variance_sum;
float average[3];
void AutoOffset()
{
	static uint8_t autojust_flag;

	GyroQueue(&senser_datas.gyro_origin_x,&senser_datas.gyro_origin_y,&senser_datas.gyro_origin_z,0,SET);
	variance_sum=sqrt(GetVariance(pitch_history,50)+GetVariance(yaw_history,50)+GetVariance(roll_history,50));
	average[0]=GetAverage(pitch_history,50);
	average[1]=GetAverage(yaw_history,50);
	average[2]=GetAverage(roll_history,50);

	if(senser_datas.temperature>32&&autojust_flag==0)
	{
		if(variance_sum<0.25f&&(fabs(average[0])+fabs(average[1])+fabs(average[2])<6.0f))
		{
			if(still_counter<0xffff)
				still_counter++;
		}
		else
			still_counter=0;
		if(still_counter>200)
		{
			senser_datas.gyro_offset_x=average[0];
			senser_datas.gyro_offset_y=average[1];
			senser_datas.gyro_offset_z=average[2];
			senser_datas.still=1;
			autojust_flag=1;
			senser_datas.autojust=1;
		}
		else
			senser_datas.still=0;
	}

}

