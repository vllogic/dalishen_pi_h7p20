#ifndef __HME_SPIFLASH_H__
#define __HME_SPIFLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hme_includes.h"
#include "hme_spi.h"


extern void spiFlashCSN(uint8_t mode);
extern void spiFlashReadId(void);
extern void spiFlashEraseSector(uint32_t addr);
extern void spiFlashPageProgram(uint8_t *dbuf, uint32_t addr, uint32_t length);
extern void spiFlashWrEn(void);
extern uint8_t spiFlashReadQuardStatus(void);
extern bool spiFlashIsWrInProgress(void);
extern void spiFlashPageRead(uint32_t *dbuf, uint32_t addr, uint32_t length);
extern uint8_t spiFlashReadStatus(void);
extern void spiFlashWrDisable(void);
extern uint8_t spiFlashQE(void);
extern uint8_t spiFlashDisableQE(void);
void spiContrller_SendCmd(uint8_t cmd);
uint8_t spiFlashReadStatus_Cmd(uint8_t cmd);


#ifdef __cplusplus
}
#endif

#endif
