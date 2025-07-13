#include <stdio.h>
#include <string.h>
#include "hme_includes.h"
#include "hme_uart.h"
#include "hme_retarget.h"

#define RAM_REG_WORD_WRITE(base, offset, data) *(volatile uint32_t *)((base) + (offset)) = (data)
#define RAM_REG_WORD_READ(base, offset) (*(volatile uint32_t *)((base) + (offset)))
	
#define RAM_BASE	((uint32_t)0xa0000000)
#define RAM			  ((RAM_TYPE *)RAM_BASE)
#define RAM_TEST_SIZE    256
#define SRC_MAC_ADDR_BD  0xDA0102030405    //default src mac addr 0xDA0102030405
#define DEST_MAC_ADDR_BD 0x00E04CA80352    //default dest mac addr, !!! Yor PC MAC
#define SRC_IP_ADDR_BD   0xC0A8010B        //default src ip addr 0xC0A8010B
#define DEST_IP_ADDR_BD  0xC0A8010A        //default dest ip addr 0xC0A8010A

#define SRC_MAC_ADDR_LD  0x0504030201DA
#define DEST_MAC_ADDR_LD 0x5203A84CE000		// base DEST_MAC_ADDR_BD
#define SRC_IP_ADDR_LD   0x0B01A8C0
#define DEST_IP_ADDR_LD  0x0A01A8C0 

void Delay(int n) 
{
	int i,j;
	for (i=0; i<=n; i++)
		for (j=0; j<=100; j++);
}

uint32_t Splice(uint16_t a, uint16_t b)
{
	
    uint32_t result = (a << 16) | b; 
    return result;
}	

uint16_t SwapEndian16(uint16_t value) {
    return (value >> 8) | (value << 8);
}
uint32_t SwapEndian32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8)  & 0x0000FF00) |
           ((value << 8)  & 0x00FF0000) |
           (value << 24);
}

void Split32BitToTwo16Bits(uint32_t input32, uint16_t *output16_1, uint16_t *output16_2) {
    *output16_1 = (input32 >> 16) & 0x0000FFFF; 
    *output16_2 = input32 & 0x0000FFFF;         
}

uint16_t CalculateIpCheckSum(const uint16_t *buffer, size_t length) {
    uint32_t sum = 0;
    size_t i;

    for (i = 0; i < length; i++) {
        sum += buffer[i]; 
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return ~(uint16_t)sum;
}
void RxFifoStatus(void)
{
	uint32_t cnt;
	uint32_t mem_ctrl_stat;
	uint32_t mem_ctrl_stat_mask;
	uint32_t rx_fifo_enable;
	
	
	    cnt = 0x00000000;
	    rx_fifo_enable = 0x00000000;
			mem_ctrl_stat_mask = 0x00000020;
	    
			while(rx_fifo_enable != 0x00000020){
				cnt = cnt + 1;
			  mem_ctrl_stat = RAM_REG_WORD_READ(RAM_BASE,0x00001044);	
				rx_fifo_enable = mem_ctrl_stat & mem_ctrl_stat_mask;
			};
			printf("Time is : %x    ",cnt);

}

void SelectRamArea(uint32_t *select_ram,uint32_t *transmitte)

{
	if (*select_ram == 0x00000000){
		*select_ram = 0x00000010;
		*transmitte = 0x00000041;
	}
	else{
		*select_ram = 0x00000000;
		*transmitte = 0x00000031;
	}
}

void ReadData(uint32_t mem_rx_data[],uint32_t *mem_ctrl_rx_len,uint32_t *mem_ctrl_rx_len_div4)
{
	int i;

		*mem_ctrl_rx_len = RAM_REG_WORD_READ(RAM_BASE,0x0000104C); 
	
		if (*mem_ctrl_rx_len%4 == 0)
			*mem_ctrl_rx_len_div4 = *mem_ctrl_rx_len/4;
		else 
			*mem_ctrl_rx_len_div4 = *mem_ctrl_rx_len/4 + 1;
		
		for(i=0;i<*mem_ctrl_rx_len_div4;i++){
			mem_rx_data[i] = RAM_REG_WORD_READ(RAM_BASE, 0x00000800);
		};
		
		RAM_REG_WORD_WRITE(RAM_BASE, 0x00001040, 0x00000051); 
}

uint32_t FrameType(uint32_t mem_rx_data[])
{
	uint32_t result;
	uint32_t addr0 = (uint32_t)(SRC_MAC_ADDR_LD & 0xFFFFFFFF);
  uint32_t broad_addr1 = (uint32_t)((DEST_MAC_ADDR_LD << 16) | 0xFFFF);
	uint32_t icmp_addr1 = ((uint16_t)((SRC_MAC_ADDR_LD >> 32)) & 0xFFFF)|((uint32_t)((DEST_MAC_ADDR_LD & 0xFFFF) << 16));
	uint32_t addr2 = (uint32_t)(DEST_MAC_ADDR_LD >> 16);

	
  if (mem_rx_data[0] == 0xFFFFFFFF && mem_rx_data[1] == broad_addr1 && mem_rx_data[2] == addr2)
  //if (mem_rx_data[0] == 0xFFFFFFFF && mem_rx_data[1] == 0x3C6CFFFF && mem_rx_data[2] == 0x59532A8C)
		result = 0x00000001;
	else if (mem_rx_data[0] == addr0 && mem_rx_data[1] == icmp_addr1 && mem_rx_data[2] == addr2 && mem_rx_data[5] != 0x01800000)
	//else if (mem_rx_data[0] == 0x030201DA && mem_rx_data[1] == 0x3C6C0504 && mem_rx_data[2] == 0x59532A8C && mem_rx_data[5] != 0x01800000)
		result = 0x00000001;
	else if (mem_rx_data[0] == addr0 && mem_rx_data[1] == icmp_addr1 && mem_rx_data[2] == addr2 && mem_rx_data[5] == 0x01800000)
		result = 0x00000002;
  else 
		result = 0x00000000;
		
	return result; 	
}

void BroadcastReplay(uint32_t mem_tx_data[],uint32_t *mem_ctrl_tx_len_div4,uint32_t *mem_ctrl_tx_len,uint32_t *select_ram,uint32_t *transmitte)
{ 
	
	int i;

	uint16_t high_addr0;
	uint16_t low_addr0;
  uint16_t high_addr1;
	uint16_t low_addr1;
	uint32_t high_addr2;
	uint32_t low_addr2;
	uint16_t high_addr3;
	uint16_t low_addr3;
	
	uint32_t addr0;
	uint32_t addr1;
	uint32_t addr2;
	
		low_addr0  = mem_tx_data[1] >> 16;
		high_addr0 = mem_tx_data[2]; 
		
		low_addr1  = mem_tx_data[2] >> 16;
		high_addr1 = 0x01DA; 		
		addr0 = Splice(high_addr0,low_addr0);
		addr1 = Splice(high_addr1,low_addr1);
		addr2 = SRC_MAC_ADDR_LD >> 16;
		//addr2 = 0x05040302;
			
		//high_addr3 = 0x01DA;
		high_addr3 = SRC_MAC_ADDR_LD & 0xFFFF;
	  low_addr3  = 0x0200;
			
		mem_tx_data[0] = addr0;
		mem_tx_data[1] = addr1;
		mem_tx_data[2] = addr2;
		mem_tx_data[5] = Splice(high_addr3,low_addr3);
		//mem_tx_data[6] = 0x05040302;
		mem_tx_data[6] = addr2;
		mem_tx_data[7] = SRC_IP_ADDR_LD;
		//mem_tx_data[7] = 0x0B01A8C0;

		RAM_REG_WORD_WRITE(RAM_BASE, 0x00001044, *select_ram);          //Select RAM0 to Store Data
		//RAM_REG_WORD_WRITE(RAM_BASE, 0x00001040, *transmitte);          //indicating TX memory 0 contains a frame to be transmitte
		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000000, *mem_ctrl_tx_len);   	//Write Frame LEN to RAM0			
		
		for (i=0;i<*mem_ctrl_tx_len_div4;i++){
			RAM_REG_WORD_WRITE(RAM_BASE, 4*(i+1), mem_tx_data[i]);        //Write Frame Data to RAM0  mac frame head 0x2A8C3C6C 0x01DA5953
		};
		//RAM_REG_WORD_WRITE(RAM_BASE, 0x00001044, *select_ram);          //Select RAM0 to Store Data	
		RAM_REG_WORD_WRITE(RAM_BASE, 0x00001040, *transmitte);          //indicating TX memory 0 contains a frame to be transmitte
    
}

void IcmpEchoReplay(uint32_t mem_rx_data[],uint32_t *mem_ctrl_rx_len_div4,uint32_t *mem_ctrl_rx_len,uint32_t *select_ram,uint32_t *transmitte)
{
	int i;
	uint32_t mem_ctrl_stat;
	uint32_t mem_ctrl_rx_status;
	
	uint16_t high_addr0;
	uint16_t low_addr0;
  uint16_t high_addr1;
	uint16_t low_addr1;
	uint32_t high_addr2;
	uint32_t low_addr2;
	uint16_t high_addr3;
	uint16_t low_addr3;
	

	uint16_t sum;
	uint16_t sum_t;
	uint32_t mem[11];
	uint16_t mem16[20];
	uint32_t src_ip_addr;
	uint32_t dest_ip_addr;
	uint16_t mem_rx_data6;
	
	uint32_t addr0;
	uint32_t addr1;
	uint32_t addr2;
		
			low_addr0  = mem_rx_data[1] >> 16;
			high_addr0 = mem_rx_data[2]; 
				
		  low_addr1  = mem_rx_data[2] >> 16;
			high_addr1 = mem_rx_data[0]; 
				
			low_addr2  = mem_rx_data[0] >> 16;
			high_addr2 = mem_rx_data[1]; 
				
			addr0 = Splice(high_addr0,low_addr0);
			addr1 = Splice(high_addr1,low_addr1);
			addr2 = Splice(high_addr2,low_addr2);
			
		  mem_rx_data6 = mem_rx_data[6];
			
			dest_ip_addr = (mem_rx_data[7]<<16)|(mem_rx_data[6]>>16);  //0a01a8c0
			src_ip_addr = (mem_rx_data[8]<<16)|(mem_rx_data[7]>>16);   //0b01a8c0
			
			mem_rx_data[0] = addr0;
			mem_rx_data[1] = addr1;
			mem_rx_data[2] = addr2;

			for (i=9;i<21;i++){
				mem[i-9] = SwapEndian32(mem_rx_data[i]);
			}
			
			
			for(i=0;i<20;i=i+2){
				Split32BitToTwo16Bits(mem[i/2], &mem16[i], &mem16[i+1]);
			}
			
			mem16[0] = 0x0000;
			mem16[19] = 0x0000;
			for (i=0;i<20;i++){
				sum = CalculateIpCheckSum(mem16, 20);
			}

			sum = SwapEndian16(sum); 

			mem_rx_data[6] = Splice(src_ip_addr, mem_rx_data6);   
			mem_rx_data[7] = Splice(src_ip_addr,src_ip_addr>>16); 
			mem_rx_data[8] = Splice(0x0000,dest_ip_addr>>16);
			mem_rx_data[9] = Splice(mem_rx_data[9]>>16,sum);	

		  RAM_REG_WORD_WRITE(RAM_BASE, 0x00001044, *select_ram);  //Select RAM0 to Store Data
			//RAM_REG_WORD_WRITE(RAM_BASE, 0x00001040, *transmitte);  //indicating TX memory 0 contains a frame to be transmitte
			//RAM_REG_WORD_WRITE(RAM_BASE, 0x00000000, 0x0000004A);   //Write Frame LEN to RAM0	
			RAM_REG_WORD_WRITE(RAM_BASE, 0x00000000, *mem_ctrl_rx_len);   //Write Frame LEN to RAM0		
			//for (i=0;i<20;i++){
			for (i=0;i<*mem_ctrl_rx_len_div4;i++){
				RAM_REG_WORD_WRITE(RAM_BASE, 4*(i+1), mem_rx_data[i]);   //Write Frame Data to RAM0  mac frame head 0x2A8C3C6C 0x01DA5953
				//printf("squence num : %d data : %8x\n",mem16[2],mem_rx_data[i]);
			}
			//RAM_REG_WORD_WRITE(RAM_BASE, 0x00001044, *select_ram);   //Select RAM0 to Store Data	
			RAM_REG_WORD_WRITE(RAM_BASE, 0x00001040, *transmitte);   //indicating TX memory 0 contains a frame to be transmitte
			
			

}

void PhyConfig(uint32_t BASE_ADDR)
{ 
	
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A001);   //PHY0 Config data  //1.8V
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  phy0_addr 0x01  phy1_addr 0x03
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000100);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr      
	
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A003);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr 
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000f1);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr    
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000054);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000c000);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr    
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000a012);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000c8);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr   	
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000027);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00006812);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 	
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A006);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000008D);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000052);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A37D);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 	
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000DD);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000856e);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000051);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000014f6);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 	

	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000029);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000000d);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 	
		
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000A0);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A8D0);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001F87);   //PHY0 Config addr 
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000080c);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001487);   //PHY0 Config addr  	
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00001C01);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000487);   //PHY0 Config addr  		
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00004140);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000087);   //PHY0 Config addr   
		
		
    RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A001);   //PHY0 Config data  //1.8V
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  phy0_addr 0x01  phy1_addr 0x03
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000100);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr      
	
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A003);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr 
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000f1);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr    
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000054);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000c000);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr    
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000a012);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000c8);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr   	
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000027);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00006812);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 	
	
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A006);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000008D);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000052);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A37D);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 	
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000DD);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000856e);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000051);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000014f6);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 	

	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00000029);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000000d);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 	
		
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x000000A0);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000E87);   //PHY0 Config addr  
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000A8D0);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000F87);   //PHY0 Config addr 
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x0000080c);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00000487);   //PHY0 Config addr  	
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00001C01);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001E07);   //PHY0 Config addr  		
		
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000100C, 0x00004140);   //PHY0 Config data  
		RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001008, 0x00001A07);   //PHY0 Config addr   

}

void MacConfig(uint32_t BASE_ADDR){
	
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001000, 0x0100080C);                                                              //Config Register Setting
	  //RAM_REG_WORD_WRITE(RAM_BASE, 0x00001004, 0x000000C0);  //Frame Filter Setting
		//RAM_REG_WORD_WRITE(RAM_BASE, 0x00001004, 0x00000010);  //Frame Filter Setting
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001004, 0x80000000);   //Frame Filter Setting
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001010, 0x00000000);   //Flow Control 
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001014, 0x00000000);   //VLAN Tag Setting
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x0000101C, 0x8000DA01);   //Local MAC Address Setting H
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001020, 0x02030405);   //Local MAC Address Setting L
		                                                           
	  RAM_REG_WORD_WRITE(BASE_ADDR, 0x00001044, 0x00000080);   //Config Mmeory Control Register Setting
}

int main(void)
{
	uint32_t mem_rx_data[128];
	uint32_t mem_ctrl_rx_len;
	uint32_t mem_ctrl_rx_status;
	uint32_t mem_ctrl_rx_len_div4;

  uint32_t select_ram       = 0x00000000;
  uint32_t transmitte       = 0x00000031;
	uint32_t frame_type       = 0x00000000;
  uint32_t broadcast_replay = 0x00000001;
	uint32_t icmp_echo_replay = 0x00000002;
	
	  HME_UART_InitTypeDef init;
    HME_UART_DeInit(UART0);
    HME_UART_StructInit(&init);
    HME_UART_Init(UART0, &init);
    printf("sys start \n");
	  
	  PhyConfig(RAM_BASE);
    MacConfig(RAM_BASE);
    Delay(100);
		
	  while(1){
 			RxFifoStatus();
			ReadData(mem_rx_data,&mem_ctrl_rx_len,&mem_ctrl_rx_len_div4);
			mem_ctrl_rx_status = RAM_REG_WORD_READ(RAM_BASE,0x00001050);
			frame_type = FrameType(mem_rx_data);	
			if (frame_type == broadcast_replay){
				BroadcastReplay(mem_rx_data,&mem_ctrl_rx_len_div4,&mem_ctrl_rx_len,&select_ram,&transmitte);
				SelectRamArea(&select_ram,&transmitte);
      }
			else if (frame_type == icmp_echo_replay){
				IcmpEchoReplay(mem_rx_data,&mem_ctrl_rx_len_div4,&mem_ctrl_rx_len,&select_ram,&transmitte);
				SelectRamArea(&select_ram,&transmitte);
			}
			else{};
	  }
		
		Delay(100);
	return 0;
}


	
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x00000004, 0x6C3C8C2A);   //Write Frame Data to RAM0  mac frame head 
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x00000008, 0x5359DA01);   //Write Frame Data to RAM0
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x0000000C, 0x02030405);   //Write Frame Data to RAM0
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x00000010, 0x08000102);   //Write Frame Data to RAM0
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x00000014, 0x03040506);   //Write Frame Data to RAM0
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x00000018, 0x0708090A);   //Write Frame Data to RAM0
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x0000001C, 0x0B0C0D0E);   //Write Frame Data to RAM0
//	  RAM_REG_WORD_WRITE(RAM_BASE, 0x00000020, 0x0F101112);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000024, 0x13141516);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000028, 0x1718191A);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x0000002C, 0x1B1C1D1E);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000030, 0x1F202122);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000034, 0x23242526);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000038, 0x2728292A);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x0000003C, 0x2B2C2D2E);   //Write Frame Data to RAM0
//		RAM_REG_WORD_WRITE(RAM_BASE, 0x00000040, 0x2F303132);   //Write Frame Data to RAM0 
