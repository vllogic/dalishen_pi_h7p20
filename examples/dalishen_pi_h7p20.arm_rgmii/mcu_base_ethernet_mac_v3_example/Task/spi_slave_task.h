#ifndef __HME_SLAVE_SLAVE_H__
#define __HME_SLAVE_SLAVE_H__

#include <stdio.h>
#include <string.h>
#include "hme_spi.h"
#include "BasicDataType.h"

#define     SPI_SLAVE_TX_BUF_SIZE                           16
#define     SPI_SLAVE_RX_BUF_SIZE                           16

//spi����״̬��
typedef enum{
    SPI_IDLE,                   //SPI����
    SPI_READY,        			//�������
    SPI_RECV_DATA,        		//��������
    SPI_TRAN_DATA,        		//��������
}spi_sstatus_t;

//spi�豸�ӻ����Խṹ
typedef    struct{
    SPI_Type        	*device;
    spi_sstatus_t 		status;
    uint8_t         	recv_buffer[SPI_SLAVE_RX_BUF_SIZE];
    uint8_t         	tran_buffer[SPI_SLAVE_TX_BUF_SIZE];
    uint8_t         	*precv_buf;
    uint8_t         	*ptran_buf;
    uint16_t         	recv_count;
    uint16_t         	tran_count;
}spi_slave_t;


void spi_slave_init(spi_slave_t *pdev);
void SPI1_NVIC_CONFIG(void);
void HME_SPI_SLAVE_Init(SPI_Type *SPIx);
int16_t Spi_Slave_Recv_Data(spi_slave_t *pdev,uint8_t *pd);
void spi_slave_transfer(void);
int16_t Spi_Slave_Send_Data(spi_slave_t *pdev,uint8_t *pd,uint16_t count);
void spi0_slave_isr(spi_slave_t *pdev);

#endif
