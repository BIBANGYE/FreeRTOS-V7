#ifndef __BSP_SD_CARD_H
#define __BSP_SD_CARD_H

#include "bsp.h"

#define   MSD_OK                        ((uint8_t)0x00)
#define   MSD_ERROR                     ((uint8_t)0x01)
#define   MSD_ERROR_SD_NOT_PRESENT      ((uint8_t)0x02)

/**
  * @brief  SD transfer state definition
  */
#define   SD_TRANSFER_OK                ((uint8_t)0x00)
#define   SD_TRANSFER_BUSY              ((uint8_t)0x01)

uint8_t bsp_sd_init(void);
uint8_t bsp_SD_GetCardState(void);
void bsp_SD_GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo);
uint8_t bsp_SD_Erase(uint32_t StartAddr, uint32_t EndAddr);
uint8_t bsp_SD_ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t bsp_SD_WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout);

#endif