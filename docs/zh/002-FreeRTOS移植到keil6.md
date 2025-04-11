# FreeRTOS移植到Keil6详解

本教程将指导您如何将FreeRTOS移植到Keil6环境中。代码部分可以在`Despacito/002`项目中找到。

## 准备工作

在开始移植FreeRTOS之前，需要准备以下内容：

1. Keil MDK (本教程使用Keil MDK V5.38或更高版本)
2. STM32F1系列标准库
3. FreeRTOS源码 (本教程使用FreeRTOS V10.0.1)
4. 一个基于STM32F103的工程模板 (可以使用`Despacito/001`中的模板)

## 移植步骤

### 1. 创建FreeRTOS文件夹结构

首先在项目中创建如下文件夹结构：

```
YourProject/
├── FreeRTOS/
│   ├── inc/      # FreeRTOS头文件
│   ├── src/      # FreeRTOS源文件
│   ├── port/     # 移植文件
```

### 2. 添加FreeRTOS内核文件

从FreeRTOS官方下载的源码中，将以下文件复制到相应的文件夹中：

**FreeRTOS/inc文件夹**:
- FreeRTOS/Source/include/*.h (所有头文件)

**FreeRTOS/src文件夹**:
- FreeRTOS/Source/tasks.c
- FreeRTOS/Source/queue.c
- FreeRTOS/Source/list.c
- FreeRTOS/Source/croutine.c
- FreeRTOS/Source/timers.c
- FreeRTOS/Source/event_groups.c
- FreeRTOS/Source/stream_buffer.c

### 3. 添加移植文件

**FreeRTOS/port文件夹**:
- FreeRTOS/Source/portable/RVDS/ARM_CM3/port.c
- FreeRTOS/Source/portable/RVDS/ARM_CM3/portmacro.h
- FreeRTOS/Source/portable/MemMang/heap_x.c (根据需要选择heap_1.c到heap_5.c)

### 4. 创建FreeRTOSConfig.h文件

在FreeRTOS文件夹下创建FreeRTOSConfig.h文件，配置如下：

```c
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

// 包含标准库头文件
#include "stm32f10x.h"

// FreeRTOS基本配置
#define configUSE_PREEMPTION                1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_IDLE_HOOK                 0
#define configUSE_TICK_HOOK                 0
#define configCPU_CLOCK_HZ                  ( ( unsigned long ) 72000000 )
#define configTICK_RATE_HZ                  ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES                32
#define configMINIMAL_STACK_SIZE            ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE               ( ( size_t ) ( 20 * 1024 ) )
#define configMAX_TASK_NAME_LEN             16
#define configUSE_TRACE_FACILITY            1
#define configUSE_16_BIT_TICKS              0
#define configIDLE_SHOULD_YIELD             1
#define configUSE_MUTEXES                   1
#define configUSE_RECURSIVE_MUTEXES         1
#define configUSE_COUNTING_SEMAPHORES       1
#define configQUEUE_REGISTRY_SIZE           10
#define configUSE_QUEUE_SETS                1

// 内存分配相关配置
#define configSUPPORT_DYNAMIC_ALLOCATION    1
#define configSUPPORT_STATIC_ALLOCATION     0

// 钩子函数配置
#define configUSE_IDLE_HOOK                 0
#define configUSE_TICK_HOOK                 0
#define configCHECK_FOR_STACK_OVERFLOW      0
#define configUSE_MALLOC_FAILED_HOOK        0

// 定时器相关配置
#define configUSE_TIMERS                    1
#define configTIMER_TASK_PRIORITY           ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH            10
#define configTIMER_TASK_STACK_DEPTH        ( configMINIMAL_STACK_SIZE * 2 )

// 中断优先级配置
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY     15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5
#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

// 可选功能配置
#define INCLUDE_vTaskPrioritySet            1
#define INCLUDE_uxTaskPriorityGet           1
#define INCLUDE_vTaskDelete                 1
#define INCLUDE_vTaskSuspend                1
#define INCLUDE_vTaskDelayUntil             1
#define INCLUDE_vTaskDelay                  1
#define INCLUDE_uxTaskGetStackHighWaterMark 1

// 中断处理宏
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
```

### 5. Keil工程配置

1. 在Keil MDK中打开项目工程
2. 添加FreeRTOS相关文件到项目中
3. 添加包含路径：
   - 项目路径/FreeRTOS/inc
   - 项目路径/FreeRTOS/port

### 6. 中断相关配置

在`stm32f10x_it.c`中添加：

```c
#include "FreeRTOS.h"
#include "task.h"

// 确保SysTick中断处理被正确调用
void SysTick_Handler(void)
{
#if (INCLUDE_xTaskGetSchedulerState == 1)
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif
    xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
  }
#endif
}
```

### 7. 测试移植

在main.c中添加测试代码：

```c
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

// LED任务句柄
TaskHandle_t LEDTask_Handler;

// LED任务函数
void led_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED亮
        vTaskDelay(500);                     // 延时500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED灭
        vTaskDelay(500);                     // 延时500ms
    }
}

int main(void)
{
    // 初始化GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    // 创建LED任务
    xTaskCreate((TaskFunction_t )led_task,
                (const char*    )"led_task",
                (uint16_t       )128,
                (void*          )NULL,
                (UBaseType_t    )3,
                (TaskHandle_t*  )&LEDTask_Handler);
    
    // 启动调度器
    vTaskStartScheduler();
    
    // 正常情况下不会运行到这里
    while(1);
}
```

## 常见问题与解决方案

### 1. 编译错误：找不到FreeRTOS头文件

**解决方案**：检查包含路径设置是否正确，确保已添加FreeRTOS/inc和FreeRTOS/port路径。

### 2. 系统无法启动

**解决方案**：
- 检查FreeRTOSConfig.h中的配置参数，特别是时钟频率和堆大小
- 确保中断处理函数正确配置
- 检查任务堆栈大小是否足够

### 3. 内存分配错误

**解决方案**：
- 增加configTOTAL_HEAP_SIZE的值
- 考虑使用不同的heap实现（heap_1.c到heap_5.c）
- 检查任务的堆栈使用情况

## 总结

通过以上步骤，您已经成功将FreeRTOS移植到STM32F103平台并创建了一个简单的任务。这为后续开发更复杂的RTOS应用奠定了基础。在进一步的开发中，可以添加更多任务、使用信号量、互斥量、队列等RTOS特性，充分发挥实时操作系统的优势。 