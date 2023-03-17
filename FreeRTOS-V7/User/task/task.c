#include "task_config.h"

TaskHandle_t	xHandleTaskLED;

#if (TASKPRINTFINFO == 1)
TaskHandle_t	xHandleTaskPrintf;
static void vTaskPrintfInfo(void *pvParameters)
{
    for(;;)
    {
        printf("操作提示:\r\n");
        vTaskDelay(500);
    }
}
#endif

static void vTaskLED(void *pvParameters)
{
    while(1)
    {
//        printf("vTaskLED\n");
        bsp_LedToggle(2);
        vTaskDelay(800);
    }
}

# if(configCHECK_FOR_STACK_OVERFLOW > 0)
TaskHandle_t	xHandleTaskStack;
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
    printf("任务： %s 发现栈溢出\r\n", pcTaskName);
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









