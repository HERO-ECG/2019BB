#include "main.h"
#include "control.h"
#include "t_moto.h"
#include "robodata.h"
#include "t_monitor.h"
#include "chassis.h"
//#include "mavlink.h"

uint32_t time_piece=0x0000;
uint32_t divider;

void vcan_sendware(u8 *wareaddr, u32 waresize)
{
#define CMD_WARE     3
    u8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    u8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

		HAL_UART_Transmit(&huart8,cmdf,sizeof(cmdf),1000);
		HAL_UART_Transmit(&huart8,wareaddr,waresize,1000);
		HAL_UART_Transmit(&huart8,cmdr,sizeof(cmdr),1000);
}


int k;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t divider100hz;
	if((time_piece&time_piece_start) == time_piece_start){
		if(htim == &htim3)        //100hz
		{ 
			time_piece |= time_piece_0100hz;
			divider100hz++;
			if(divider100hz%20==0)
			{		
				CustomSend();
			}
			
			Monitor_LED_Display();
			TX2_SetMode();
			Chassis_Fun();
		
		Monitor_Motor();
		monitor_tx2_process(&monitor_tx2);//tx2监控器
		monitor_tx2_valid_process(&monitor_tx2_valid);
		monitor_can_power_process(&monitor_can_power);	
		monitor_dji_process(&monitor_dji);			
//				var[0] = DJI_ReadData.ext_power_heat_data.chassis_power;
//				var[1] = DJI_ReadData.ext_power_heat_data.chassis_power_buffer;
			var[0] = Chassis.speed.spd_right;		
			var[1] = Chassis.speed.spd_forward;
			var[2] = RoboData.robo_ctrlmode.ctrl_source;
//				//var[3] = (fabs(Chassis.speed.now[0])+fabs(Chassis.speed.now[1])+fabs(Chassis.speed.now[2])+fabs(Chassis.speed.now[3]))/200.0f;
//				var[3] = Chassis.supercapacitor.Voltage_realtime*10;
//				var[4] = Chassis.power.power_set;
//				var[7] = -Chassis.power.speed_decreasement/20;
////			
//					var[0] = TX2_Data.pitch_angle;
//					var[1] = TX2_Data.yaw_angle;
//					var[2] = testdata[0];
//					var[3] = testdata[1];
//					var[4] = testdata[2];
//					
	//			vcan_sendware((u8*) var, (u32)sizeof(var));

		if(divider100hz==100000)
			divider100hz=0;
		}
		else if(htim == &htim5)//1000hz
		{
					time_piece |= time_piece_1000hz;
//			static uint8_t flag;
//			
//			if(flag==0)
//			{
//				flag=1;
//				HAL_GPIO_WritePin(GPIOH,GPIO_PIN_6,GPIO_PIN_SET);
//			}
//			else
//			{
//				
//				flag=0;
//				HAL_GPIO_WritePin(GPIOH,GPIO_PIN_6,GPIO_PIN_RESET);
//			}
			
//					var[0] = TX2_Data.pitch_angle;
//					var[1] = TX2_Data.yaw_angle;
//					var[2] = testdata[0];
//					var[3] = testdata[1];
//					var[4] = testdata[2]/100.0f;
//					var[5] = testdata[3];

////				var[4] = Chassis.power.power_set;
////				var[5] = Chassis.speed.base;
////				var[6] = Chassis.speed.set[0];
//				//var[7] = -Chassis.power.speed_decreasement/20

//			if(divider<10000)
//				divider++;
//			else
//				divider=0;
//			if(divider%4==0)
//				vcan_sendware((u8*) var, (u32)sizeof(var));
//			

			
			IMU_Get_Data();
			RoboData.chassis_ctrl.pitch_speed_gyro=imu_data.gy;
			RoboData.chassis_ctrl.yaw_speed_gyro=imu_data.gz;

				//底盘电机信号发送
			
		SetMotoCurrent(&hcan2, STDID_3508, Chassis_MOTO[0].send_current, Chassis_MOTO[1].send_current, Chassis_MOTO[2].send_current, Chassis_MOTO[3].send_current);
		}
	}
}


void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
		
		/*template
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
		{
			static int i1;
			i1++;
			if(i1>250)
			{
				i1 = 0;
				__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_1,1300);
				//htim->Instance->CCR1 = 1300;
				htim->Instance->CCR2 = 1300;
				HAL_TIM_OC_Stop_IT(&htim2,TIM_CHANNEL_1);
				HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_2);
			}
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			static int i2;
			i2++;
			if(i2>250)
			{
				i2 = 0;
				htim->Instance->CCR1 = 1000;				
				__HAL_TIM_SET_COMPARE(htim,TIM_CHANNEL_2,1000);
				//htim->Instance->CCR2 = 1000;
				HAL_TIM_OC_Start_IT(&htim2,TIM_CHANNEL_1);
				HAL_TIM_OC_Stop_IT(&htim2,TIM_CHANNEL_2);
			}
		}
		***template*/
		
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
		{
			
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)
		{
			
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
		{
			
		}
	}
	else if(htim == &htim4)
	{
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
		{
			
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)
		{
			
		}
		else if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
		{
			
		}
	}
	
}


//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
//void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
//void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
//void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);




