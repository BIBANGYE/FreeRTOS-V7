/*
 * FreeRTOS Kernel V10.4.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "FreeRTOS.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* ��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ� */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  extern uint32_t SystemCoreClock;
#endif



/**
  * 1��ʹ����ռʽ RTOS ������
  * 0��ʹ��Эͬʽ RTOS ��������ʱ��Ƭ��
  * ע��Эͬʽ����ϵͳ�����������ͷ�CPU���л�����һ������
  * �����л���ʱ����ȫȡ�����������е�����
  */
#define configUSE_PREEMPTION					1

/**
  * ͨ�÷�ʽ    0
  *     - �������� FreeRTOS ��ֲ
  *     - ��ȫʹ�� C ��д����ר�÷�����Ч
  *     - �����ƿ������ȼ����������
  *
  * ר�÷�ʽ    1
  *     - ����ƽ̨֧��
  *     - ����ƽ̨ר�õĻ��ָ������㷨ִ���ٶ�
  *     - ��ͨ�÷�ʽ��Ч
  *     - ���ƿ������ȼ����������Ϊ 32
  */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	0


/**
  * 1��ʹ�ÿ��й���
  * 0�����Կ��й���
  */
#define configUSE_IDLE_HOOK						0

/**
  * �������񡢶��л��ź���ʱ���ں˵��� pvPortMalloc() �Ӷ��з����ڴ�
  * 1��ʹ�ܶ�̬�ڴ�����ʧ��ʱ�Ĺ��Ӻ���
  * 0�����ܶ�̬�ڴ�����ʧ��ʱ�Ĺ��Ӻ���
  */
#define configUSE_MALLOC_FAILED_HOOK			0

/**
  * 1��ʹ�ܵδ�ʱ���ж�����ִ�еĹ��Ӻ���
  * 0�����ܵδ�ʱ���ж�����ִ�еĹ��Ӻ���
  */
#define configUSE_TICK_HOOK						0

/**
  * ���� CPU ����Ƶ�� ��λ Hz
  */
#define configCPU_CLOCK_HZ						( SystemCoreClock )

/**
  * ����ϵͳʱ�ӽ������� ��λ Hz��һ��ȡ 1000Hz ����
  */
#define configTICK_RATE_HZ						( ( TickType_t ) 1000 )

/**
  * Ӧ�ó���������õ����ȼ���������������������ɹ�����ͬ�����ȼ�
  * ������������� 5�� ��ô�û�����ʹ�õ����ȼ����� 0,1,2,3,4�������� 5
  */
#define configMAX_PRIORITIES					( 56 )

/**
  * ��������ʹ�õĶ�ջ��С�����֣�4���ֽڣ�ָ��
  */
#define configMINIMAL_STACK_SIZE				( ( uint16_t ) 512 )

/**
  * ����Ѵ�С�� FreeRTOS �ںˣ� �û���̬�ڴ����룬����ջ�����񴴽����ź�����������Ϣ���д���
  * �ȶ���Ҫ������ռ�
  * 
  * ע��ֻ���� configSUPPORT_DYNAMIC_ALLOCATION ����Ϊ 1 ʱ����ʹ�ø�ֵ
  */
#define configTOTAL_HEAP_SIZE					( ( size_t ) 15 * 1024 )

/**
  * ��������ʱ���������Ƶ����������
  * �ó��Ȱ��ַ���ָ���� ���� NULL ��ֹ�ֽ�
  */
#define configMAX_TASK_NAME_LEN					( 16 )

/**
  * ϵͳʱ�ӽ��ļ���ʹ�� TickType_t �������Ͷ���
  *     - ʹ���˺궨�� configUSE_16_BIT_TICKS��TickType_t ����ľ��� 16 λ�޷�����
  *     - û��ʹ�ܣ���ô TickType_t ����ľ��� 32 λ�޷�����
  *
  * ע��16 λ�޷�����������Ҫ���� 8 λ�� 16 λ�ܹ��Ĵ�����
  */
#define configUSE_16_BIT_TICKS					0

/**
  * 1��ʹ�ܻ����ź���
  * 0����ֹ�����ź���
  */
#define configUSE_MUTEXES						1

/**
  * 1��ʹ�ܵݹ黥���ź���
  * 0����ֹ�ݹ黥���ź���
  */
#define configUSE_RECURSIVE_MUTEXES				1

/**
  * ͨ���˶��������ÿ���ע����ź�������Ϣ���и���
  * ����ע���������Ŀ�ģ����� RTOS �ں˸�֪������أ�
  *     - ���Թ����ı����ƺͶ��У������ڵ��� GUI ��ʶ�����
  *     - ������������λÿ����ע����к��ź����������Ϣ
  * ע������ RTOS �ں˵��������������ע���û���κ���;
  */
#define configQUEUE_REGISTRY_SIZE				8

/**
  * 1���ڹ����а��������ź�������
  * 0���ڹ����к��Լ����ź�������
  */
#define configUSE_COUNTING_SEMAPHORES			1

/**
  * ��ջ������
  * 1������ 1
  * 0������ 2
  */
#define configCHECK_FOR_STACK_OVERFLOW			0

/**
  * ���������ṹ��Ա�ͺ���������ִ�п��ӻ��͸���
  * 1������
  * 0������
  */
#define configUSE_TRACE_FACILITY				1

/**
  * 1��RTOS ������� ʹ��Ӧ�ó����д���ṩ�� RAM ����
  * 0��RTOS ����ֻ�� ʹ�ô� RAM ���з���� FreeRTOS ����
  */
#define configSUPPORT_STATIC_ALLOCATION			0

/**
  * 1��RTOS ������� ʹ�ô� RAM �����Զ������ FreeRTOS ����
  * 0��RTOS ����ֻ�� ʹ��Ӧ�ó����д���ṩ�� RAM ����
  */
#define configSUPPORT_DYNAMIC_ALLOCATION		1

/**
  * ��Ϣ������ÿ����Ϣ�ĳ��ȵ�����
  */
#define configMESSAGE_BUFFER_LENGTH_TYPE		size_t

/* Software timer definitions. */
/**
  * 1��ʹ�������ʱ������
  * 0�����������ʱ������
  */
#define configUSE_TIMERS						1
/**
  * ���������ʱ������/�ػ���������ȼ�
  */
#define configTIMER_TASK_PRIORITY				( 2 )
/**
  * ���������ʱ��������еĳ���
  */
#define configTIMER_QUEUE_LENGTH				10
/**
  * ���÷���������ʱ������/�ػ�����Ķ�ջ���
  */
#define configTIMER_TASK_STACK_DEPTH			256

/* Set the following definitions to 1 to include the API function, or zero
 * to exclude the API function. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			0
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_xTaskGetSchedulerState			1
#define INCLUDE_xTimerPendFunctionCall			1
#define INCLUDE_xQueueGetMutexHolder			1
#define INCLUDE_uxTaskGetStackHighWaterMark		1
#define INCLUDE_eTaskGetState					1


//#define __NVIC_PRIO_BITS
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS						__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS						4
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
 * function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY	15

/** �� FreeRTOS �����������ȼ��ж�
  *	�����û�������жϷ�������������FreeRTOS �� API ��������ȼ�
  */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
 * to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY				( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY		( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

/* Normal assert() semantics without relying on the provision of an assert.h
 * header file. */
#define configASSERT( x )							if ( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
 * standard names. */
#define vPortSVCHandler								SVC_Handler
#define xPortPendSVHandler							PendSV_Handler
#define xPortSysTickHandler							SysTick_Handler

/* Allow system call from within FreeRTOS kernel only. */
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY	1

/* STM32H743 has 16 MPU regions and therefore it is necessary to configure
 * configTOTAL_MPU_REGIONS correctly. */
#define configTOTAL_MPU_REGIONS						16

/* The default TEX,S,C,B setting marks the SRAM as shareable and as a result,
 * disables cache. Do not mark the SRAM as shareable because caching is being
 * used. TEX=0, S=0, C=1, B=1. */
#define configTEX_S_C_B_SRAM						( 0x03UL )

#endif /* FREERTOS_CONFIG_H */
