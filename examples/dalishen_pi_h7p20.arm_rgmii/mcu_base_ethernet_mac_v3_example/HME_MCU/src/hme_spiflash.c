#include <stdio.h>
#include <string.h>
#include "hme_includes.h"
#include "hme_spiflash.h"

void spiFlashCSN(uint8_t mode)
{
	if(mode)
		HME_GPIO_Set(0,GPIO_PIN1);
	else
		HME_GPIO_Clear(0,GPIO_PIN1);
}

bool flashEnterDuadMode()
{
	uint8_t sta;
    sta = spiFlashReadQuardStatus();
	
	return (sta & 0x02) ? true : false;
}

uint8_t spiFlashQE(void)
{
	uint32_t OutCount = 0;
	uint32_t cmd=0x31;
	uint8_t QE = 0x02;
	uint8_t tmp;
	
	while (spiFlashIsWrInProgress()){};
    spiFlashWrEn();
    while (spiFlashIsWrInProgress()){};
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Write_only,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)){}; //wait for trans end
		
	SPI_Set_Cmd(DEMO_SPI,cmd);
		
    while ((OutCount < 1)) {
        if (!DEMO_SPI->Status_b.TXFULL) {   //TFNF
            DEMO_SPI->Data = QE;  
            OutCount++;
        }     
	} 

	delay_t(5000);	
	while(1)
	{
		tmp = spiFlashReadQuardStatus();
		if(tmp &0x02)
			break;
	}
	
	return 0;
}

uint8_t spiFlashDisableQE(void)
{
	uint32_t OutCount = 0;
	
	uint32_t cmd=0x31;
	uint8_t QE = 0x00;
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Write_only,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)){}; //wait for trans end
		
	SPI_Set_Cmd(DEMO_SPI,cmd);
		
    while ((OutCount < 1)) {
        if (!DEMO_SPI->Status_b.TXFULL) {   //TFNF
            DEMO_SPI->Data = QE;  
            OutCount++;
        }     
	} 
	
	return 0;
}

uint8_t spiFlashReadStatus(void)
{
	uint32_t cmd=0x05;			 // Read identification : 0x05
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Read_only,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	SPI_Set_Cmd(DEMO_SPI,cmd);
	
	SPI_RecieveData(DEMO_SPI, &cmd, 1);

	delay_t(10);

    return cmd;			 		// Return data : status register
}

bool spiFlashIsWrInProgress()
{
    uint8_t sta;

    sta = spiFlashReadStatus();

    // b0 is WIP
    return (sta & 0x01) ? true : false;
}

void spiFlashWrEn()
{
	uint8_t cmd[1];
	cmd[0]=0x06;
	while (spiFlashIsWrInProgress());
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_None_Data,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	SPI_Set_Cmd(DEMO_SPI,cmd[0]);

	delay_t(50);
}


void spiContrller_SendCmd(uint8_t cmd)
{
	while (spiFlashIsWrInProgress());

	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_None_Data,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	SPI_Set_Cmd(DEMO_SPI,cmd);

	delay_t(50);
}

uint8_t spiFlashReadStatus_Cmd(uint8_t cmd)
{
	uint32_t status;
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Read_only,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);

	SPI_Set_Cmd(DEMO_SPI,cmd);

	SPI_RecieveData(DEMO_SPI, &status, 1);

	delay_t(10);
	
    return cmd;
}

void spiFlashWrDisable()
{
	uint8_t cmd[1];
	cmd[0]=0x04;
	while (spiFlashIsWrInProgress());

	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_None_Data,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	SPI_Set_Cmd(DEMO_SPI,cmd[0]);

	while (spiFlashIsWrInProgress());
}

uint8_t spiFlashReadQuardStatus(void)
{
	uint32_t cmd=0x35;
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Read_only,SPI_CMD_Enable,SPI_ADDR_Disable,0,0);
	
	SPI_Set_Cmd(DEMO_SPI,cmd);

	SPI_RecieveData(DEMO_SPI, &cmd, 1);
	
    return cmd;
}

void spiFlashReadId(void)
{
	uint8_t cmd=0x9f;
	uint32_t flash_id[3];
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Read_only,SPI_CMD_Enable,SPI_ADDR_Disable,3,0);
    while (spiFlashIsWrInProgress());
	spiFlashCSN(0);
	SPI_Set_Cmd(DEMO_SPI,cmd);
	SPI_RecieveData(DEMO_SPI,flash_id,3);
	spiFlashCSN(1);
}


void spiFlashEraseSector(uint32_t addr)
{
	uint8_t cmd = 0x20;

	while (spiFlashIsWrInProgress()){};
    spiFlashWrEn();
    while (spiFlashIsWrInProgress()){};
	
	SPI_Set_Addr(DEMO_SPI,addr);	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_None_Data,SPI_CMD_Enable,SPI_ADDR_Enable,0,0);
	SPI_Set_Cmd(DEMO_SPI,cmd);	

	delay_t(100);
	delay_t(100);
}

void spiFlashPageProgram(uint8_t *dbuf, uint32_t addr, uint32_t length)
{
	uint8_t cmd = 0x02;
	
    spiFlashWrEn();
	
    while (spiFlashIsWrInProgress()){};
	
	SPI_Set_Addr(DEMO_SPI,addr);

	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Write_only,SPI_CMD_Enable,SPI_ADDR_Enable,0,length-1);
	
	while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)){}; //wait for spi controller idle
		
	SPI_Set_Cmd(DEMO_SPI,cmd);

	SPI_SendData(DEMO_SPI,dbuf,length);
}

void spiFlashPageRead(uint32_t *dbuf, uint32_t addr, uint32_t length)
{
	uint8_t cmd = 0x03;
	
	while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)){};
	
	while (spiFlashIsWrInProgress()){};
	
	SPI_Set_Addr(DEMO_SPI,addr);
	
	SPI_Set_Transfer_Control_Reg(DEMO_SPI,SPI_Transfermode_Read_only,SPI_CMD_Enable,SPI_ADDR_Enable,length-1,0);

	while(HME_SPI_GetFlagStatus(DEMO_SPI,SPI_Status_Active)){}; //wait for spi controller idle
		
	SPI_Set_Cmd(DEMO_SPI,cmd);
		
	HME_SPI_ITConfig(DEMO_SPI,SPI_EndInt_ENABLE,TRUE);	
	
	SPI_RecieveData(DEMO_SPI,dbuf,length);
}
