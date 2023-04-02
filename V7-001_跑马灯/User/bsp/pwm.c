#include "pwm.h"

void pwm_init(uint8_t pulse)
{
    GPIO_InitTypeDef GPIO_Handle = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();

    GPIO_Handle.Pin = GPIO_PIN_1;
    GPIO_Handle.Pull = GPIO_PULLUP;
    GPIO_Handle.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_Handle.Mode = GPIO_MODE_AF_PP;
    GPIO_Handle.Alternate = GPIO_AF2_TIM3;

    HAL_GPIO_Init(GPIOB, &GPIO_Handle);

    TIM_HandleTypeDef TimHandle = {0};
    TIM_OC_InitTypeDef sConfig = {0};

    TimHandle.Instance = TIM3;
    TimHandle.Init.Prescaler = 10000 - 1;
    TimHandle.Init.Period = 500;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle.Init.RepetitionCounter = 0;
    TimHandle.Init.AutoReloadPreload = 0;

    HAL_TIM_PWM_Init(&TimHandle);

    /* 配置定时器PWM输出通道 */
	sConfig.OCMode       = TIM_OCMODE_PWM1;
	sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;

    sConfig.Pulse = pulse;

    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&TimHandle,TIM_CHANNEL_1);
}
