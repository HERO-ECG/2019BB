#include "USART1.h"
#include "stdio.h"
#include "math.h"

//uart reicer flag
#define b_uart_head  0x80
#define b_rx_over    0x40

//÷ß≥÷printf ‰≥ˆ	  
#if 1
#pragma import(__use_no_semihosting)             
//??????????                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedefí d in stdio.h. */ 
FILE __stdout;       
//??_sys_exit()??????????    
_sys_exit(int x) 
{ 
	x = x; 
} 
//???fputc?? 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//????,??????   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 




/**************************????********************************************
	void U1NVIC_Configuration(void)
   ¥Æø⁄1÷–∂œ≈‰÷√
*******************************************************************************/
void UART1NVIC_Configuration(void)
{
        NVIC_InitTypeDef NVIC_InitStructure; 
        /* Enable the USART1 Interrupt */
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
}



/**************************????********************************************
      void Initial_UART1(u32 baudrate)
         ≥ı ºªØusart1
 ‰»Î:u32 baudrate  

*******************************************************************************/
void UART1_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);
	mantissa=temp;				 //??????
	fraction=(temp-mantissa)*16; //??????	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //??PORTA???  
	RCC->APB2ENR|=1<<14;  //?????? 
	GPIOA->CRH&=0XFFFFF00F;//IO????
	GPIOA->CRH|=0X000008B0;//IO????
	RCC->APB2RSTR|=1<<14;   //????1
	RCC->APB2RSTR&=~(1<<14);//????	   	   
	//?????
 	USART1->BRR=mantissa; // ?????	 
	USART1->CR1|=0X200C;  //1???,????.
  USART1->CR1|=1<<8;    //PE????
	USART1->CR1|=1<<5;    //???????????	    	
 
  UART1NVIC_Configuration();//????
  
  
  UartTxbuf.Wd_Indx = 0;
  UartTxbuf.Rd_Indx = 0;
  UartTxbuf.Mask = TX_BUFFER_SIZE - 1;
  UartTxbuf.pbuf = &tx_buffer[0];
  
  UartRxbuf.Wd_Indx = 0;
  UartRxbuf.Rd_Indx = 0;
  UartRxbuf.Mask = RX_BUFFER_SIZE - 1;
  UartRxbuf.pbuf = &rx_buffer[0];
  
//  
//  printf("MCU clock frequency:%dMHz \r\n",pclk2);
//  printf("UART 1 baud frequncy:%d \r\n",bound);
// 
  
}

/**************************????********************************************
		void UART1_Put_Char(unsigned char DataToSend)
               ∑¢ÀÕ“ª∏ˆ◊÷Ω⁄
		     unsigned char DataToSend   
*******************************************************************************/
void UART1_Put_Char(unsigned char DataToSend)
{
  
  UartBuf_WD(&UartTxbuf,DataToSend);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  
}


uint8_t Uart1_Put_Char(unsigned char DataToSend)
{
  UartBuf_WD(&UartTxbuf,DataToSend);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  
	return DataToSend;
}



//ª∑–Œ ˝æ›Ω·ππ
UartBuf UartTxbuf;
UartBuf UartRxbuf;

unsigned char rx_buffer[RX_BUFFER_SIZE];
unsigned char tx_buffer[TX_BUFFER_SIZE];

//Ω´“ª∏ˆ◊÷Ω⁄ ˝æ›∂¡≥ˆª∑–ŒΩ·ππÃÂ
uint8_t UartBuf_RD(UartBuf *Ringbuf)
{
  uint8_t temp;
  temp = Ringbuf->pbuf[Ringbuf->Rd_Indx & Ringbuf->Mask];
  Ringbuf->Rd_Indx++;
  return temp;
}
//Ω´“ª∏ˆ◊÷Ω⁄–¥»Î......
void UartBuf_WD(UartBuf *Ringbuf,uint8_t DataIn)
{
  
  Ringbuf->pbuf[Ringbuf->Wd_Indx & Ringbuf->Mask] = DataIn;
  Ringbuf->Wd_Indx++;
}


uint16_t UartBuf_Cnt(UartBuf *Ringbuf)
{
  return (Ringbuf->Wd_Indx - Ringbuf->Rd_Indx) & Ringbuf->Mask;//?????????,???????????
}

void UartBufClear(UartBuf *Ringbuf)
{
	Ringbuf->Rd_Indx=Ringbuf->Wd_Indx;
}

void UartSendBuffer(uint8_t *dat, uint8_t len)
{
	uint8_t i;
	
	for(i=0;i<len;i++)
	{
		UartBuf_WD(&UartTxbuf,*dat);
		dat++;
	}
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}



volatile uint8_t Udatatmp;//¡Ÿ ±Ω” ’ ˝æ›◊÷Ω⁄
//--------∑¢ÀÕ£¨Ω” ’÷–∂œ∫Ø ˝----------------
void USART1_IRQHandler(void)
{
	
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART1, UartBuf_RD(&UartTxbuf)); 
    if(UartBuf_Cnt(&UartTxbuf)==0)  
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
  }
  
  else if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		 
    Udatatmp = (uint8_t) USART_ReceiveData(USART1);         
		
		UartBuf_WD(&UartRxbuf,Udatatmp);             
    
	}
  
}

static uint8_t checksum=0;

static  void uart8chk(uint8_t _x)
{
    UartBuf_WD(&UartTxbuf,_x);
    checksum ^= _x;
}
static  void uart32chk(uint32_t a)
{
    static uint8_t t;
    t = a;
    UartBuf_WD(&UartTxbuf,t);
    checksum ^= t;
    t = a >> 8;
    UartBuf_WD(&UartTxbuf,t);
    checksum ^= t;
    t = a >> 16;
    UartBuf_WD(&UartTxbuf,t);
    checksum ^= t;
    t = a >> 24;
    UartBuf_WD(&UartTxbuf,t);
    checksum ^= t;
}

static void uart16chk(int16_t a)
{
    static uint8_t t;
    t = a;
    UartBuf_WD(&UartTxbuf,t);
    checksum ^= t;
    t = a >> 8 & 0xff;
    UartBuf_WD(&UartTxbuf,t);
    checksum ^= t;
}

void CommAppUpload(void)
{
    uart8chk('$');
    uart8chk('M');
    uart8chk('>');
    checksum = 0;
    uart8chk(12+2);
    uart8chk(16);

    uart16chk((int16_t)10);
    uart32chk((int32_t)100);	//altitude,????
    
    uart8chk(checksum);
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	
}




void USART1_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ClearITPendingBit(USART1, USART_FLAG_TXE);
	while(len--)
	{
	 USART_SendData(USART1, *tx_buf);
	 while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != 1);
	 USART_ClearFlag(USART1, USART_FLAG_TC);
	 USART_ClearITPendingBit(USART1, USART_FLAG_TXE);
	 tx_buf++;
	}

}

void USART1_SendData(unsigned char *Data, int16_t Datasize)
{
    #define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};
    USART1_Send(cmdf, sizeof(cmdf));
    USART1_Send(Data, Datasize);
    USART1_Send(cmdr, sizeof(cmdr));
}


