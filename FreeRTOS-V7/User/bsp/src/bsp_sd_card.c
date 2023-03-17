#include "bsp_sd_card.h"

SD_HandleTypeDef hsd1;

uint8_t bsp_sd_init(void)
{
    uint8_t sd_state = MSD_OK;

    hsd1.Instance = SDMMC1;
    hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
    hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
    hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
    hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd1.Init.ClockDiv = 2;

    sd_state = HAL_SD_Init(&hsd1);

    if (sd_state == MSD_OK)
    {
        printf("File:%s ;\r\nline %d ;\r\nSD����ʼ���ɹ�\r\n", __FILE__, __LINE__);
    }

    return  sd_state;
}

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* SDMMC1 clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration
    PC8     ------> SDMMC1_D0
    PC9     ------> SDMMC1_D1
    PC10    ------> SDMMC1_D2
    PC11    ------> SDMMC1_D3
    PC12    ------> SDMMC1_CK
    PD2     ------> SDMMC1_CMD

    */
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_8
                          | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    __HAL_RCC_SDMMC1_FORCE_RESET();
    __HAL_RCC_SDMMC1_RELEASE_RESET();
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle)
{
    if(sdHandle->Instance == SDMMC1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SDMMC1_CLK_DISABLE();

        /**SDMMC1 GPIO Configuration
        PC10     ------> SDMMC1_D2
        PC11     ------> SDMMC1_D3
        PC12     ------> SDMMC1_CK
        PD2     ------> SDMMC1_CMD
        PC8     ------> SDMMC1_D0
        PC9     ------> SDMMC1_D1
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_8
                        | GPIO_PIN_9);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
    }
}


uint8_t bsp_SD_ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout)
{
    if( HAL_SD_ReadBlocks(&hsd1, (uint8_t *)pData, ReadAddr, NumOfBlocks, Timeout) == HAL_OK)
    {
        return MSD_OK;
    }
    else
    {
        return MSD_ERROR;
    }
}

uint8_t bsp_SD_WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout)
{

    if( HAL_SD_WriteBlocks(&hsd1, (uint8_t *)pData, WriteAddr, NumOfBlocks, Timeout) == HAL_OK)
    {
        return MSD_OK;
    }
    else
    {
        return MSD_ERROR;
    }
}

uint8_t bsp_SD_Erase(uint32_t StartAddr, uint32_t EndAddr)
{

    if( HAL_SD_Erase(&hsd1, StartAddr, EndAddr) == HAL_OK)
    {
        return MSD_OK;
    }
    else
    {
        return MSD_ERROR;
    }
}

uint8_t bsp_SD_GetCardState(void)
{
    return((HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

/**
  * @brief  Get SD information about specific SD card.
  * @param  CardInfo: Pointer to HAL_SD_CardInfoTypedef structure
  * @retval None
  */
void bsp_SD_GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo)
{
    HAL_SD_GetCardInfo(&hsd1, CardInfo);
}


