#include "task_config.h"

TaskHandle_t	xHandleTaskPrintf;
TaskHandle_t	xHandleTaskLED;


static void vTaskPrintfInfo(void *pvParameters)
{
    for(;;)
    {
        printf("操作提示:\r\n");
        printf("1. 启动一个自动重装软件定时器，每100ms翻转一次LED1和LED2\r\n");
        printf("2. 再启动一个自动重装软件定时器，每500ms翻转一次LED3和LED4\r\n");
        vTaskDelay(500);
    }

}

static void vTaskLED(void *pvParameters)
{
    xTaskCreate(vTaskPrintfInfo,
                "vTaskPrintfInfo",
                512,
                NULL,
                2,
                &xHandleTaskPrintf);
    
    if(xHandleTaskPrintf != NULL)
    {
//        vTaskDelete(xHandleTaskPrintf);
        vTaskSuspend(xHandleTaskPrintf);
        printf("任务挂起完毕\n");
    }
    
    vTaskResume(xHandleTaskPrintf);
    printf("恢复任务完毕\n");

    while(1)
    {
        bsp_LedToggle(2);
        vTaskDelay(200);
    }
}


void AppTaskCreate (void)
{
    xTaskCreate(vTaskLED,
                "vTaskLED",
                512,
                NULL,
                3,
                &xHandleTaskLED);
}









