#include "common_time.h"

TIM_HandleTypeDef com_tim_handle = {0};

void common_time_init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    com_tim_handle.Instance = TIM2;
    com_tim_handle.Init.Prescaler = ((SystemCoreClock / 2) ) - 1; // 1us
    com_tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数模式
    com_tim_handle.Init.Period = 0xFFFF - 1;
    com_tim_handle.Init.ClockDivision = 0;
    com_tim_handle.Init.RepetitionCounter = 0; // 不允许重复计数
    com_tim_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; // 允许自动重装载

    HAL_TIM_Base_Init(&com_tim_handle);

    HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    HAL_TIM_Base_Start(&com_tim_handle);
}


void star_timing(uint32_t tim_delay)
{
    uint32_t cnt_now;
    uint32_t cnt_tail;

//    cnt_now = __HAL_TIM_GET_COUNTER(&com_tim_handle);
    cnt_now = TIM2->CNT;
    cnt_tail = cnt_now + tim_delay;

    __HAL_TIM_SET_COMPARE(&com_tim_handle, TIM_CHANNEL_1, cnt_tail);

    __HAL_TIM_DISABLE_IT(&com_tim_handle, TIM_IT_CC1);

    __HAL_TIM_ENABLE_IT(&com_tim_handle, TIM_IT_CC1);

    __HAL_TIM_CLEAR_IT(&com_tim_handle, TIM_FLAG_CC1);
    __HAL_TIM_CLEAR_IT(&com_tim_handle, TIM_FLAG_CC2);
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&com_tim_handle);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    printf("捕获时间到\n");
    __HAL_TIM_DISABLE_IT(&com_tim_handle, TIM_IT_CC1); 
}

