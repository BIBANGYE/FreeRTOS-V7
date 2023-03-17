#include "task_config.h"

TaskHandle_t	xHandleTaskPrintf;
TaskHandle_t	xHandleTaskLED;
TaskHandle_t	xHandleTaskStack;

#if (TASKPRINTFINFO == 1)
static void vTaskPrintfInfo(void *pvParameters)
{
    for(;;)
    {
        printf("������ʾ:\r\n");
        printf("1. ����һ���Զ���װ�����ʱ����ÿ100ms��תһ��LED1��LED2\r\n");
        printf("2. ������һ���Զ���װ�����ʱ����ÿ500ms��תһ��LED3��LED4\r\n");
        vTaskDelay(500);
    }
}
#endif

static void vTaskLED(void *pvParameters)
{
    while(1)
    {
        bsp_LedToggle(2);
        vTaskDelay(200);
    }
}

# if(configCHECK_FOR_STACK_OVERFLOW > 0)
static void vTaskStack(void *pvParameters)
{
    uint8_t buf[4096];

    for(uint32_t i = 4096; i > 0; i--)
    {
        buf[i] = 0xA5;
        vTaskDelay(10);
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName )
{
    printf("���� %s ����ջ���\r\n", pcTaskName);
}
#endif

void AppTaskCreate (void)
{
    xTaskCreate(vTaskLED,
                "vTaskLED",
                512,
                NULL,
                3,
                &xHandleTaskLED);

    # if(configCHECK_FOR_STACK_OVERFLOW > 0)
    xTaskCreate(vTaskStack,
                "vTaskStack",
                512,
                NULL,
                3,
                &xHandleTaskStack);
    #endif

#if (TASKPRINTFINFO == 1)
    xTaskCreate(vTaskPrintfInfo,
                "vTaskPrintfInfo",
                512,
                NULL,
                2,
                &xHandleTaskPrintf);
#endif
}









