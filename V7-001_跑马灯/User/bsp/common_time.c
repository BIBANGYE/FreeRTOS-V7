#include "common_time.h"

TIM_HandleTypeDef com_tim_handle = {0};

void common_time_init(void)
{
    __HAL_RCC_TIM15_CLK_ENABLE();

    com_tim_handle.Instance = TIM15;
    com_tim_handle.Init.Prescaler = ((SystemCoreClock / 2) / 1000000) - 1; // 1us
    com_tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                  // ���ϼ���ģʽ
    com_tim_handle.Init.Period = 0xFFFF - 1;
    com_tim_handle.Init.ClockDivision = 0;
    com_tim_handle.Init.RepetitionCounter = 0;                             // �������ظ�����
    com_tim_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; // �����Զ���װ��

    if (HAL_TIM_Base_Init(&com_tim_handle) != HAL_OK)
    {
        printf("��ʱ����ʼ������\n");
    }

    HAL_NVIC_SetPriority(TIM15_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM15_IRQn);

    HAL_TIM_Base_Start(&com_tim_handle);
}

void star_timing(uint32_t tim_delay)
{
    uint32_t cnt_now;
    uint32_t cnt_tail;

    cnt_now = __HAL_TIM_GET_COUNTER(&com_tim_handle);
    cnt_tail = cnt_now + tim_delay;

    __HAL_TIM_SET_COMPARE(&com_tim_handle, TIM_CHANNEL_1, cnt_tail);    /* ���ò���Ƚϼ�����CC1 */
    __HAL_TIM_ENABLE_IT(&com_tim_handle, TIM_IT_CC1);   /* ʹ��CC1�ж� */
    __HAL_TIM_CLEAR_IT(&com_tim_handle, TIM_FLAG_CC1);  /* ���CC1�жϱ�־ */
}

void TIM15_IRQHandler(void)
{
    if ((TIM15->SR & TIM_IT_CC1)&&(TIM15->DIER & TIM_IT_CC1))
    {
        TIM15->SR = (uint16_t)~TIM_FLAG_CC1;
        TIM15->DIER &= (uint16_t)~TIM_IT_CC1; /* ����CC1�ж� */
        printf("TIM15 CC1 ����ʱ�䵽\n");
    }
}


