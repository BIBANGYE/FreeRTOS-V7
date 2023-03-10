# FreeRTOS-V7
[FreeRTOS](https://sourceforge.net/projects/freertos/files/FreeRTOS/)源码下载

# 编码标准

## 命名标准

- 变量

    > u：表示 unsigned
    >
    > l：表示 long
    >
    > s：表示 short
    >
    > c：表示 char

    - uint8_t 类型变量以 uc 为前缀
    - uint16_t 类型变量以 us 为前缀
    - uint32_t 类型变量以 ul 为前缀
    - 非 stdint 类型的变量以 x 为前缀，如BaseType_t 和 TickType_t定义的变量
    - 非 stdint 类型的无符号变量附加前缀 u，如UBaseType_t类型变量以 ux 为前缀
    - size_t 类型变量也带有 x 前缀
    - 枚举变量以 e 为前缀
    - 指针以附加 p 为前缀，如，指向 uint16_t 的指针将以 pus 为前缀、
    - char 定义的变量只能用于 ASCII 字符，前缀使用 c
    - char *定义的指针变量只能用于 ASCII 字符串， 前缀使用 pc

- 函数

    - 文件作用域静态（私有）函数以 prv 为前缀
    - API 函数以其返回类型为前缀，并为 void 添加前缀 v
    - API 函数名称以定义 API 函数文件的名称开头。例如，在 tasks.c 中定义 vTaskDelete，并且具有 void 返回类型

- 宏

    - 宏以定义宏的文件为前缀。前缀为小写。例如，在 FreeRTOSConfig.h 中定义 configUSE_PREEMPTION
    - 除前缀外，所有宏均使用大写字母书写，并使用下划线来分隔单词

## 数据类型

- TickType_t
    - configUSE_16_BIT_TICKS 设置为非零 (true)，那么 TickType_t 定义的就是 16 位无符号数
    - configUSE_16_BIT_TICKS 设置为零 (false)，那么 TickType_t 定义的就是 32 位无符号数

- BaseType_t

    - 在 32 位架构上，BaseType_t 会被定义为 32 位有符号类型
    - 在 16 位架构上，BaseType_t 会被定义为 16 位有符号类型

    > 如果 BaseType_t 被定义成了 char 型，要特别注意将其设置为有符号数，因为部分函数的返回值是用负数来表示错误类型

- UBaseType_t
    - 无符号BaseType_t类型
- StackType_t
    - 用于存储堆栈项目的类型
    - 16 位架构上的 16 位类型
    - 32 位架构上的 32 位类型

# 内存管理

每次创建任务、队列、互斥锁、软件定时器、信号量或事件组时，RTOS 内核都需要 RAM ， RAM 可以从 RTOS API 对象创建函数内的 RTOS 堆自动动态分配， 或者由应用程序编写者提供。

FreeRTOS 提供了几种堆管理方案：

- heap_1 —— 最简单，不允许释放内存
- heap_2—— 允许释放内存，但不会合并相邻的空闲块
- heap_3 —— 简单包装了标准 malloc() 和 free()，以保证线程安全
- heap_4 —— 合并相邻的空闲块以避免碎片化。 包含绝对地址放置选项
- heap_5 —— 如同 heap_4，能够跨越多个不相邻内存区域的堆

> 🏷heap_1 不太有用，因为 FreeRTOS 添加了静态分配支持 🐱‍🐉heap_2 现在被视为旧版，因为较新的 heap_4 实现是首选

# 栈空间

Cortex-M3 拥有两个堆栈指针，但在任一时刻只能使用其中的一个。

- MSP：主堆栈指针(使用系统栈空间)
- PSP：任务堆栈指针（使用任务栈空间）

# 堆栈溢出检测

每个任务都拥有其独立维护的堆栈。

- [xTaskCreate()](https://www.freertos.org/zh-cn-cmn-s/a00125.html) 创建任务：任务堆栈的内存由 FreeRTOS 堆自动分配
- [xTaskCreateStatic()](https://www.freertos.org/zh-cn-cmn-s/xTaskCreateStatic.html) 创建任务：任务堆栈的内存由使用者预先分配

> 🏷使用 configCHECK_FOR_STACK_OVERFLOW 进行配置
>
> 🐱‍🚀任务栈空间是在任务创建的时候从 FreeRTOSConfig.h 文件中定义的 heap 空间中申请的

如果 configCHECK_FOR_STACK_OVERFLOW 未设置为 0 ，则应用程序必须提供堆栈溢出钩子函数。堆栈溢出检查会增加上下文切换的开销，因此建议只在开发或测试阶段使用此检查。

```c
// xTask 和 pcTaskName 参数分别为违规任务的句柄和名称
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName );
```

1. 堆栈溢出检测——方法 1

#define configCHECK_FOR_STACK_OVERFLOW		1

任务切换时检测堆栈指针是否越界，如果越界则触发堆栈溢出钩子函数。

1. 堆栈溢出检测——方法 2

#define configCHECK_FOR_STACK_OVERFLOW		2

任务首次创建时，会在堆栈中会填充一个已知值。 任务切换时，RTOS 内核检查堆栈的最后 16 个字节。如果这 16 个字节中的任何一个不再为初始值，则调用堆栈溢出钩子函数。

# 任务调度

在任何给定时间， 每个处理器核心只能有一个任务处于运行状态。

## 默认 RTOS 调度策略（单核）

FreeRTOS 默认使用固定优先级抢占式调度策略，对同等优先级的任务执行时间片轮询调度：

- “固定优先级” 是指调度器不会永久更改任务的优先级， 尽管它可能会因优先级继承而暂时提高任务的优先级
- “抢占式调度” 是指调度器始终运行优先级最高且可运行的 RTOS 任务。例如， 如果中断服务程序 (ISR) 更改了优先级最高且可运行的任务， 调度器会停止当前正在运行的低优先级任务 并启动高优先级任务——即使这发生在同一个时间片内
- “轮询调度” 是指具有相同优先级的任务轮流进入运行状态
- “时间片” 是指调度器会在每个 tick 中断上在同等优先级任务之间进行切换， tick 中断之间的时间构成一个时间片。tick 中断是 RTOS 用来衡量时间的周期性中断

### 任务饥饿

总是运行优先级最高且可运行的任务的后果是， 永远不会进入“阻塞”或 “挂起”状态的高优先级任务会让所有任意执行时长的低优先级任务永久饥饿 。

## 调度锁

调度锁就是 RTOS 提供的调度器开关函数， 如果某个任务调用了调度锁开关函数，处于调度锁开和调度锁关之间的代码在执行期间是不会被高优先级的任务抢占的，即任务调度被禁止。（只是禁止了任务调度，并没有关闭任何中断）

如果调度器被挂起时，中断请求切换上下文，那么请求将会被挂起。而且只有在调度器恢复（取消挂起）时才会执行。

> 🎉不得在调度器挂起时调用其他 FreeRTOS API 函数

```c
void vTaskSuspendAll( void );// 关闭调度器
BaseType_t xTaskResumeAll( void ); // 打开调度器
// 由于恢复调度器已经导致了上下文切换，则返回 pdTRUE，否则返回 pdFALSE
```
