#include <stdio.h>
#include <string.h>
#include "hme_includes.h"


#define FLASH_SECTOR_SIZE                       0x001000
#define XMODEM_DATA_SIZE						128

uint8_t uartRnum = 0;
uint8_t ubuf[133]={0};
uint8_t ready_cmd 	= 0x43;
uint8_t data_ack 	= 0x06;
uint8_t data_nak 	= 0x15;
uint32_t flash_rdbuf[128];

typedef struct{
	
	uint8_t head;
	uint8_t num;
	uint8_t num_neg;
	uint8_t *data_ptr;
	uint8_t crc_h;
	uint8_t crc_l;

}datastreanm_type;


void my_delay(uint32_t delay_t)
{
	uint32_t a,b;
	for(a=0;a<delay_t;a++)
		for(b=0;b<delay_t;b++);
}

void ledDelay(int n) {
int i,j;
for (i=0; i<=n; i++)
  for (j=0; j<=5; j++)
    ;
}

static void longdelay()
{
	int i;
	for(i=0;i<50;i++)
		delay_t(50000);
		delay_t(50000);
}

unsigned short do_crc(unsigned char *ptr, int len)
{
    unsigned int i;
    unsigned short crc = 0x0000;
    
    while(len--)
    {
        crc ^= (unsigned short)(*ptr++) << 8;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }
    
    return crc;
}

void ISP_task(void)
{
	uint8_t i;

	volatile uint32_t stream_totalsize=0;
	volatile uint32_t flash_base=0;
	volatile uint32_t flash_offset=0;
	
	volatile uint32_t xmodem_packetTimes_133B=0;
	volatile uint8_t xmodem_lastPacketValidDataCnt=0;
	datastreanm_type xmodem_data;
	volatile uint32_t recv_packet_cnt=0;
	
	bool handshake = false;
	static bool already_got_packet = false;
	volatile unsigned short crc=0;
	volatile unsigned short packet_crc=0;
	volatile uint32_t eraser_flashtimes=0;
	
	uint8_t real_getdata[XMODEM_DATA_SIZE];


	HME_UART_InitTypeDef init;
	HME_GPIO_InitTypeDef GPIO_Init;

	uartRnum = 0;
	memset(ubuf,0,sizeof(ubuf));

	DEMO_SPI->Transfer_Format_b.DataMerge = 0;
	
	HME_GPIO_DeInit(DEMO_GPIO);
    GPIO_Init.Mode = PIN_MODE_OUTPUT;
    GPIO_Init.Pins = GPIO_PIN0;
    HME_GPIO_Init(DEMO_GPIO, &GPIO_Init);
	
    HME_UART_DeInit(DEMO_UART);
    HME_UART_StructInit(&init);
    HME_UART_Init(DEMO_UART, &init);

    NVIC_EnableIRQ(DEMO_UART_IRQn);
    
    HME_UART_ITConfig(DEMO_UART, UART_Int_Received_Data_Available, true);

	while(1)
	{
		if(!handshake)
		{
			if(uartRnum == 8)
			{
				if(ubuf[0]==0x53)    											//握手信息，获取配置文件大小和flash中的存储地址
				{
					stream_totalsize = (ubuf[1]<<24)|(ubuf[2]<<16)|(ubuf[3]<<8)|(ubuf[4]);
					flash_base       = (ubuf[5]<<16)|(ubuf[6]<<8)|(ubuf[7]);
					
					xmodem_packetTimes_133B	  = stream_totalsize/XMODEM_DATA_SIZE;
					xmodem_lastPacketValidDataCnt = stream_totalsize%XMODEM_DATA_SIZE;					
					if(xmodem_lastPacketValidDataCnt > 0)
						xmodem_packetTimes_133B = xmodem_packetTimes_133B + 1;
	
					eraser_flashtimes = stream_totalsize/FLASH_SECTOR_SIZE;   	//通过文件大小计算需要擦除flash的sector数量
					
					for(i=0;i<=eraser_flashtimes;i++)							//对FLASH要写入的指定区间擦除	
					{
						spiFlashEraseSector(flash_base+i*FLASH_SECTOR_SIZE);
					}
					my_delay(10000);	
				}	
				
				memset(ubuf,uartRnum,0);
				uartRnum=0;
				handshake = true;
			}
		}

		if(!already_got_packet)													//未获取到xmodem数据包前周期发送0x43
		{
			HME_UART_SendData(DEMO_UART, 1, &ready_cmd);   //send ‘C’ 0x43
			my_delay(5000);
		}
				
		if(uartRnum == XMODEM_DATA_SIZE+5)										//获取到数据包
		{	
			already_got_packet 		= true;
			
			xmodem_data.head 		= ubuf[0];
			xmodem_data.num 		= ubuf[1];
			xmodem_data.num_neg 	= ubuf[2];
			xmodem_data.data_ptr 	= ubuf+3;
			xmodem_data.crc_h		= ubuf[131];
			xmodem_data.crc_l		= ubuf[132];  
			
			packet_crc = (xmodem_data.crc_h<<8)|xmodem_data.crc_l;
			
			crc = do_crc((ubuf+3), XMODEM_DATA_SIZE);								//crc计算
					
			if((packet_crc == crc)&&((xmodem_data.num |xmodem_data.num_neg)==0xFF)) //校验无误写入flash
			{
				memset(real_getdata,0,XMODEM_DATA_SIZE);
				
				flash_offset = recv_packet_cnt*XMODEM_DATA_SIZE;
				
				spiFlashPageProgram(xmodem_data.data_ptr,flash_base+flash_offset,XMODEM_DATA_SIZE);
				spiFlashPageRead(flash_rdbuf,flash_base+flash_offset,XMODEM_DATA_SIZE);
							
				for(i=0;i<XMODEM_DATA_SIZE;i++)										
				{
					real_getdata[i] = flash_rdbuf[i] & 0xFF;				
				}
				
				if(memcmp(xmodem_data.data_ptr,real_getdata,XMODEM_DATA_SIZE)!=0)	//对每次写入flash的数据做比对校验
				{
					uartRnum=0;
					xmodem_data.data_ptr = NULL;
					memset(ubuf,0,sizeof(ubuf));
					
					HME_UART_SendData(DEMO_UART, 1, &data_nak);   					//send nak 0x15
				}
				else
				{			
					recv_packet_cnt++;      										//this packet is valid,cnt+1
					
					uartRnum=0;
					xmodem_data.data_ptr = NULL;
					memset(ubuf,0,sizeof(ubuf));
					
					HME_UART_SendData(DEMO_UART, 1, &data_ack);   					//send ack 0x06
				}
			}
		}
		else if(uartRnum == 1)
		{
			if(ubuf[0] == 0x04)    												//EOT结束包
			{	
				HME_UART_SendData(DEMO_UART, 1, &data_ack);   					//send ack 0x06
				
				
				for(i=0;i<5;i++)
				{
					HME_GPIO_Set(DEMO_GPIO, GPIO_PIN0);
					longdelay();
					HME_GPIO_Clear(DEMO_GPIO, GPIO_PIN0);
					longdelay();
				}
				
				if(recv_packet_cnt == xmodem_packetTimes_133B)		
				{	
																				//reconfig
					#ifdef HME_H7	
						SYS_CHIP_IMAGE_RECONFIG(flash_base);						
					#endif
					
					#ifdef HME_P2	
						SYS_CHIP_IMAGE_RECONFIG(flash_base,RCFG_24BIT_ADDR);						
					#endif		
					
				}
			}
		}
	}
}
