#include "task_config.h"

TaskHandle_t	xHandleTaskPrintf;
TaskHandle_t	xHandleTaskLED;


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
        printf("����������\n");
    }
    
    vTaskResume(xHandleTaskPrintf);
    printf("�ָ��������\n");

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









