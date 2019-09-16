#include "can.h"
#include "stm32f10x_it.h"
//#include "stm32f10x_can.h"


CanRxMsg    CAN_Receive_Data;
CanTxMsg    CAN_Transmit_Data;

void CAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct ;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin =CAN_TX_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin =CAN_RX_GPIO_PIN;
	GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStruct);
}

void CAN_MODE_Config(void)
{
	CAN_InitTypeDef CAN_InitStruct;
	
	CAN_APBx_CLK_CMD(CAN_CLK, ENABLE);
	
	CAN_InitStruct.CAN_ABOM = DISABLE;             //�Զ����߹�����
	CAN_InitStruct.CAN_AWUM = DISABLE;             //�Զ�����
	CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;  
	CAN_InitStruct.CAN_NART = DISABLE;             //�Զ��ش�
	CAN_InitStruct.CAN_RFLM = DISABLE;             //�Ƿ�����FIFO
	CAN_InitStruct.CAN_TTCM = DISABLE;            //ʱ�䴥������
	CAN_InitStruct.CAN_TXFP = DISABLE;            //�Ƿ��Ա��Ĵ���������Ⱥ�˳���ͣ������ձ���ID���ȼ�����
	
	CAN_InitStruct.CAN_BS1 =CAN_BS1_5tq;
	CAN_InitStruct.CAN_BS2 =CAN_BS2_3tq;
	CAN_InitStruct.CAN_SJW =CAN_SJW_2tq;
	CAN_InitStruct.CAN_Prescaler =4;
	
	CAN_Init(CAN1,&CAN_InitStruct);
}



void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitTypeStruct;
	
	CAN_FilterInitTypeStruct.CAN_FilterActivation =ENABLE;
	CAN_FilterInitTypeStruct.CAN_FilterFIFOAssignment =CAN_Filter_FIFO0;
	CAN_FilterInitTypeStruct.CAN_FilterNumber =0;
	CAN_FilterInitTypeStruct.CAN_FilterScale =CAN_FilterScale_32bit;
	CAN_FilterInitTypeStruct.CAN_FilterMode =CAN_FilterMode_IdMask;
	
	CAN_FilterInitTypeStruct.CAN_FilterIdHigh = ((PASS_ID<<3|CAN_Id_Extended|CAN_RTR_Data)&0xFFFF0000)>>16;//0x0000;//((PASS_ID<<3|CAN_Id_Extended|CAN_RTR_Data)&0xFFFF0000)>>16;
	CAN_FilterInitTypeStruct.CAN_FilterIdLow = ((PASS_ID<<3|CAN_Id_Extended|CAN_RTR_Data)&0xFFFF);//0x0000;//((PASS_ID<<3|CAN_Id_Extended|CAN_RTR_Data)&0xFFFF);
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdHigh =0x0000;//FFFF;
	CAN_FilterInitTypeStruct.CAN_FilterMaskIdLow =0x0000;//FFFF;
	
	CAN_FilterInit(&CAN_FilterInitTypeStruct);
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

void CAN_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
  NVIC_Init(&NVIC_InitStructure);

}

void CAN_Config(void)
{
	CAN_GPIO_Config();
	CAN_MODE_Config();
	//CAN_Filter_Config();
	//CAN_Receive(CAN1, CAN_FIFO0, &CAN_Receive_Data);
	//CAN_NVIC_Config();
}
/*
���ܣ���A�巢������
������sup_c_ready�����������Ƿ���������״̬���ڴ�״̬�°��¼����ϵ�ĳ��������ʹ�ó������ݷŵ磩
			V_status���������ݵĵ�ѹʣ�����Ƿ����V_OPEN����Ϊ1����Ϊ0
			sup_c_open�����������Ƿ���
*/
uint8_t CAN_TransmitPower(uint8_t *DataBuff)
{
	uint8_t tempbox;
	uint8_t back = 0;
	uint8_t i;
	for(i=0;i<8;i++)
		CAN_Transmit_Data.Data[i]=DataBuff[i];
	
	CAN_Transmit_Data.ExtId =PASS_ID;
	CAN_Transmit_Data.IDE =CAN_Id_Extended ;
	CAN_Transmit_Data.RTR =CAN_RTR_Data;
	CAN_Transmit_Data.StdId =0;
	CAN_Transmit_Data.DLC =8;
	tempbox = CAN_Transmit(CAN1, &CAN_Transmit_Data);
	back = CAN_TransmitStatus(CAN1, tempbox);
	return back;
}


