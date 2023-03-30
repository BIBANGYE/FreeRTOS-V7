#include "base_time.h"

TIM_HandleTypeDef tim_handle = {0};

void base_time_init(TIM_TypeDef * TIMx)
{
    __HAL_RCC_TIM6_CLK_ENABLE();

    tim_handle.Instance = TIMx;
    tim_handle.Init.Prescaler = ((SystemCoreClock/2) / 1000000)-1; // 1ms
    tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数模式
    tim_handle.Init.Period = 1000-1;
    tim_handle.Init.ClockDivision = 0;
    tim_handle.Init.RepetitionCounter = 0; // 不允许重复计数
    tim_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; // 允许自动重装载
    
    HAL_TIM_Base_Init(&tim_handle);
    
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn,1,0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
    
    HAL_TIM_Base_Start_IT(&tim_handle);
}


void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&tim_handle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    printf("1\n");
}

