/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart.h"
#include "timbase.h"
#include "led_test.h"
#include "can.h"
#include "MPU65xx.h"
#include "PID.h"
#include "heat_ctrl.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

 void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
			
	} 
	 
}

uint8_t test[8];
uint8_t return_val;
void macTIM_INT_FUN (void)
{
	static uint32_t timer;
	if(TIM_GetFlagStatus(macTIMbasex ,TIM_FLAG_Update)==SET)
	{
		timer++;
		if(timer==100000)
			timer=0;
		
		if(senser_datas.err_code==0)
		{
			if(senser_datas.autojust==1)
			{
				if(timer%1000<500)
					LED_ON;
				else
					LED_OFF; 
			}
			else
				LED_ON;
		}
		if(senser_datas.err_code==1)
		{
			if(timer%1000<100)
				LED_ON;
			else
				LED_OFF;
		}
		else if(senser_datas.err_code==2)
		{
			if(timer%1000<100)
				LED_ON;
			else if(timer%1000<200)
				LED_OFF;
			else if(timer%1000<300)
				LED_ON; 
			else
				LED_OFF;
		}
		else if(senser_datas.err_code==3)
		{
			if(timer%1000<100)
				LED_ON;
			else if(timer%1000<200)
				LED_OFF;
			else if(timer%1000<300)
				LED_ON; 
			else if(timer%1000<400)
				LED_OFF;
			else if(timer%1000<500)
				LED_ON; 
			else
				LED_OFF;
		}
		
		if(timer%10==0)
		{
			HEAT_Ctrl(35);
			AutoOffset();
		}
		if(timer%50==0)
		{
		//	AutoOffset();
		}
		MPU6xxx_ReadAll(&senser_datas);
		
		if(senser_datas.err_code==0)
		{
			test[0] = (int16_t)(((int16_t)(senser_datas.gyro_compensated_x*16.384))>>8);
			test[1] = (int16_t)(((int16_t)(senser_datas.gyro_compensated_x*16.384)));
			test[2] = (int16_t)(((int16_t)(senser_datas.gyro_compensated_y*16.384))>>8);
			test[3] = (int16_t)(((int16_t)(senser_datas.gyro_compensated_y*16.384)));
			test[4] = (int16_t)(((int16_t)(senser_datas.gyro_compensated_z*16.384))>>8);
			test[5] = (int16_t)(((int16_t)(senser_datas.gyro_compensated_z*16.384)));
			test[6] = (int16_t)(((int16_t)(senser_datas.temperature*100.0))>>8);
			test[7] = (int16_t)(((int16_t)(senser_datas.temperature*100.0)));
			return_val=CAN_TransmitPower(test);
		}
		
		

		


		
		TIM_ClearITPendingBit(macTIMbasex,TIM_FLAG_Update);
	}
	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
