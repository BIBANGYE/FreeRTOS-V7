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

/* 针对不同的编译器调用不同的stdint.h文件 */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  extern uint32_t SystemCoreClock;
#endif



/**
  * 1：使用抢占式 RTOS 调度器
  * 0：使用协同式 RTOS 调度器（时间片）
  * 注：协同式操作系统是任务主动释放CPU后，切换到下一个任务。
  * 任务切换的时机完全取决于正在运行的任务。
  */
#define configUSE_PREEMPTION					1

/**
  * 通用方式    0
  *     - 用于所有 FreeRTOS 移植
  *     - 完全使用 C 编写，比专用方法低效
  *     - 不限制可用优先级的最大数量
  *
  * 专用方式    1
  *     - 部分平台支持
  *     - 依赖平台专用的汇编指令，加速算法执行速度
  *     - 比通用方式高效
  *     - 限制可用优先级的最大数量为 32
  */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	0


/**
  * 1：使用空闲钩子
  * 0：忽略空闲钩子
  */
#define configUSE_IDLE_HOOK						0

/**
  * 创建任务、队列或信号量时，内核调用 pvPortMalloc() 从堆中分配内存
  * 1：使能动态内存申请失败时的钩子函数
  * 0：禁能动态内存申请失败时的钩子函数
  */
#define configUSE_MALLOC_FAILED_HOOK			0

/**
  * 1：使能滴答定时器中断里面执行的钩子函数
  * 0：禁能滴答定时器中断里面执行的钩子函数
  */
#define configUSE_TICK_HOOK						0

/**
  * 定义 CPU 的主频， 单位 Hz
  */
#define configCPU_CLOCK_HZ						( SystemCoreClock )

/**
  * 定义系统时钟节拍数， 单位 Hz，一般取 1000Hz 即可
  */
#define configTICK_RATE_HZ						( ( TickType_t ) 1000 )

/**
  * 应用程序任务可用的优先级数量，任意数量的任务可共用相同的优先级
  * 如果这个定义的是 5， 那么用户可以使用的优先级号是 0,1,2,3,4，不包含 5
  */
#define configMAX_PRIORITIES					( 56 )

/**
  * 空闲任务使用的堆栈大小，按字（4个字节）指定
  */
#define configMINIMAL_STACK_SIZE				( ( uint16_t ) 512 )

/**
  * 定义堆大小， FreeRTOS 内核， 用户动态内存申请，任务栈，任务创建，信号量创建，消息队列创建
  * 等都需要用这个空间
  * 
  * 注：只有在 configSUPPORT_DYNAMIC_ALLOCATION 设置为 1 时，才使用该值
  */
#define configTOTAL_HEAP_SIZE					( ( size_t ) 15 * 1024 )

/**
  * 创建任务时，任务名称的最大允许长度
  * 该长度按字符数指定， 包括 NULL 终止字节
  */
#define configMAX_TASK_NAME_LEN					( 16 )

/**
  * 系统时钟节拍计数使用 TickType_t 数据类型定义
  *     - 使能了宏定义 configUSE_16_BIT_TICKS，TickType_t 定义的就是 16 位无符号数
  *     - 没有使能，那么 TickType_t 定义的就是 32 位无符号数
  *
  * 注：16 位无符号数类型主要用于 8 位和 16 位架构的处理器
  */
#define configUSE_16_BIT_TICKS					0

/**
  * 1：使能互斥信号量
  * 0：禁止互斥信号量
  */
#define configUSE_MUTEXES						1

/**
  * 1：使能递归互斥信号量
  * 0：禁止递归互斥信号量
  */
#define configUSE_RECURSIVE_MUTEXES				1

/**
  * 通过此定义来设置可以注册的信号量和消息队列个数
  * 队列注册表有两个目的，都与 RTOS 内核感知调试相关：
  *     - 可以关联文本名称和队列，便于在调试 GUI 中识别队列
  *     - 包含调试器定位每个已注册队列和信号量所需的信息
  * 注：除非 RTOS 内核调试器，否则队列注册表没有任何用途
  */
#define configQUEUE_REGISTRY_SIZE				8

/**
  * 1：在构建中包含计数信号量功能
  * 0：在构建中忽略计数信号量功能
  */
#define configUSE_COUNTING_SEMAPHORES			1

/**
  * 堆栈溢出检查
  * 1：方法 1
  * 0：方法 2
  */
#define configCHECK_FOR_STACK_OVERFLOW			0

/**
  * 包含其它结构成员和函数来辅助执行可视化和跟踪
  * 1：启用
  * 0：禁用
  */
#define configUSE_TRACE_FACILITY				1

/**
  * 1：RTOS 对象可以 使用应用程序编写者提供的 RAM 创建
  * 0：RTOS 对象只能 使用从 RAM 堆中分配的 FreeRTOS 创建
  */
#define configSUPPORT_STATIC_ALLOCATION			0

/**
  * 1：RTOS 对象可以 使用从 RAM 堆中自动分配的 FreeRTOS 创建
  * 0：RTOS 对象只能 使用应用程序编写者提供的 RAM 创建
  */
#define configSUPPORT_DYNAMIC_ALLOCATION		1

/**
  * 消息缓冲区每个消息的长度的类型
  */
#define configMESSAGE_BUFFER_LENGTH_TYPE		size_t

/* Software timer definitions. */
/**
  * 1：使能软件定时器功能
  * 0：忽略软件定时器功能
  */
#define configUSE_TIMERS						1
/**
  * 设置软件定时器服务/守护任务的优先级
  */
#define configTIMER_TASK_PRIORITY				( 2 )
/**
  * 设置软件定时器命令队列的长度
  */
#define configTIMER_QUEUE_LENGTH				10
/**
  * 设置分配给软件定时器服务/守护任务的堆栈深度
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

/** 受 FreeRTOS 管理的最高优先级中断
  *	允许用户在这个中断服务程序里面调用FreeRTOS 的 API 的最高优先级
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
