/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
static CanTxMsgTypeDef		Tx1Message;
static CanRxMsgTypeDef 		Rx1Message;

static CanTxMsgTypeDef		Tx2Message;
static CanRxMsgTypeDef 		Rx2Message;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  hcan1.Instance=CAN1;
  hcan1.Init.Prescaler=9;
  hcan1.Init.Mode=CAN_MODE_NORMAL;
  hcan1.Init.SJW=CAN_SJW_1TQ;
  hcan1.Init.BS1=CAN_BS1_2TQ;
  hcan1.Init.BS2=CAN_BS2_1TQ;
  hcan1.Init.TTCM=DISABLE;
  hcan1.Init.ABOM=DISABLE;
  hcan1.Init.AWUM=DISABLE;
  hcan1.Init.NART=DISABLE;
  hcan1.Init.RFLM=DISABLE;
  hcan1.Init.TXFP=ENABLE;
  if (HAL_CAN_Init(&hcan1) !=HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

//	hcan1.pTxMsg=&Tx1Message;
//		hcan1.pRxMsg=&Rx1Message;
}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  hcan2.Instance=CAN2;
  hcan2.Init.Prescaler=9;
  hcan2.Init.Mode=CAN_MODE_NORMAL;
  hcan2.Init.SJW=CAN_SJW_1TQ;
  hcan2.Init.BS1=CAN_BS1_2TQ;
  hcan2.Init.BS2=CAN_BS2_1TQ;
  hcan2.Init.TTCM=DISABLE;
  hcan2.Init.ABOM=DISABLE;
  hcan2.Init.AWUM=DISABLE;
  hcan2.Init.NART=DISABLE;
  hcan2.Init.RFLM=DISABLE;
  hcan2.Init.TXFP=ENABLE;
  if (HAL_CAN_Init(&hcan2) !=HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
  
    /**CAN1 GPIO Configuration    
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX 
    */
    GPIO_InitStruct.Pin=GPIO_PIN_8;
    GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull=GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin=GPIO_PIN_9;
    GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
  
    /**CAN2 GPIO Configuration    
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX 
    */
    GPIO_InitStruct.Pin=GPIO_PIN_12;
    GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull=GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin=GPIO_PIN_13;
    GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_TX_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }
  
    /**CAN1 GPIO Configuration    
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }
  
    /**CAN2 GPIO Configuration    
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

void CAN_Filter_Init_Recv_ALL(CAN_HandleTypeDef* _hcan)
{
	//can1 &can2 use same filter config
	CAN_FilterConfTypeDef		CAN_FilterConfigStructure;

	CAN_FilterConfigStructure.FilterNumber=0;
	CAN_FilterConfigStructure.FilterMode=CAN_FILTERMODE_IDMASK;
	CAN_FilterConfigStructure.FilterScale=CAN_FILTERSCALE_32BIT;
	CAN_FilterConfigStructure.FilterIdHigh=0x0000;
	CAN_FilterConfigStructure.FilterIdLow=0x0000;
	CAN_FilterConfigStructure.FilterMaskIdHigh=0x0000;
	CAN_FilterConfigStructure.FilterMaskIdLow=0x0000;
	CAN_FilterConfigStructure.FilterFIFOAssignment=CAN_FILTER_FIFO0;//CAN_FILTER_FIFO1
	//CAN_FilterConfigStructure.BankNumber=14;//can1(0-13)和can2(14-27)分别得到一半的filter
	CAN_FilterConfigStructure.FilterActivation=ENABLE;

	//HAL_CAN_ConfigFilter(_hcan, &CAN_FilterConfigStructure);

	if(_hcan==&hcan1){
		CAN_FilterConfigStructure.BankNumber=0;
		_hcan->pTxMsg=&Tx1Message;
		_hcan->pRxMsg=&Rx1Message;
	}
	if(_hcan==&hcan2){
		CAN_FilterConfigStructure.BankNumber=14;
		_hcan->pTxMsg=&Tx2Message;
		_hcan->pRxMsg=&Rx2Message;
	}
	HAL_CAN_ConfigFilter(_hcan, &CAN_FilterConfigStructure);
}

void CAN_Filter_Init_Recv_SP(CAN_HandleTypeDef* _hcan, uint32_t pass_id)
{
	//can1 &can2 use same filter config
	CAN_FilterConfTypeDef		CAN_FilterConfigStructure;

	if(_hcan==&hcan1){
		_hcan->pTxMsg=&Tx1Message;
		_hcan->pRxMsg=&Rx1Message;
	}
	if(_hcan==&hcan2){
		_hcan->pTxMsg=&Tx2Message;
		_hcan->pRxMsg=&Rx2Message;
	}
	CAN_FilterConfigStructure.FilterNumber=0;
	CAN_FilterConfigStructure.FilterMode=CAN_FILTERMODE_IDMASK;
	CAN_FilterConfigStructure.FilterScale=CAN_FILTERSCALE_32BIT;
	CAN_FilterConfigStructure.FilterIdHigh=((pass_id<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000)>>16;
	CAN_FilterConfigStructure.FilterIdLow=((pass_id<<3|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF);
	CAN_FilterConfigStructure.FilterMaskIdHigh=0xFFFF;
	CAN_FilterConfigStructure.FilterMaskIdLow=0xFFFF;
	CAN_FilterConfigStructure.FilterFIFOAssignment=CAN_FILTER_FIFO0;
	CAN_FilterConfigStructure.BankNumber=14;//can1(0-13)和can2(14-27)分别得到一半的filter
	CAN_FilterConfigStructure.FilterActivation=ENABLE;

	HAL_CAN_ConfigFilter(_hcan,&CAN_FilterConfigStructure);
	
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
