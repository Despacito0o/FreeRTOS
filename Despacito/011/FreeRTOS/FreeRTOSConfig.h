/**
 * @file FreeRTOSConfig.h
 * @author Despacito (https://github.com/Despacito0o/FreeRTOS)
 * @brief FreeRTOS配置文件
 */

 #ifndef FREERTOS_CONFIG_H
 #define FREERTOS_CONFIG_H
 
 #include "stm32f10x.h"  // 设备头文件
 
 // 调度器配置
 #define configUSE_PREEMPTION                    1  // 启用抢占式调度器
 //#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0  // 是否使用优化的任务选择方法
 #define configUSE_TICKLESS_IDLE                 1  // 启用低功耗无滴答模式
 
 // 时钟配置
 #define configCPU_CLOCK_HZ                      (SystemCoreClock)  // CPU 时钟频率
 //#define configSYSTICK_CLOCK_HZ                  configCPU_CLOCK_HZ  // SysTick 时钟频率
 #define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )  // 系统节拍频率
 #define configUSE_16_BIT_TICKS                  0  // 使用 32 位节拍计数器
 
 // 任务配置
 #define configMAX_PRIORITIES                    (32)  // 最大任务优先级
 #define configMINIMAL_STACK_SIZE                ( ( unsigned short ) 128 )  // 最小任务堆栈大小
 #define configMAX_TASK_NAME_LEN                 16  // 任务名称最大长度
 //#define configTICK_TYPE_WIDTH_IN_BITS           TICK_TYPE_WIDTH_32_BITS  // 滴答计数器宽度
 #define configIDLE_SHOULD_YIELD                 1  // 空闲任务是否放弃 CPU 使用权
 //#define configUSE_TASK_NOTIFICATIONS            1  // 是否启用任务通知功能
 //#define configTASK_NOTIFICATION_ARRAY_ENTRIES   3  // 任务通知数组的大小
 //#define configUSE_MUTEXES                       0  // 是否启用互斥信号量
 //#define configUSE_RECURSIVE_MUTEXES             0  // 是否启用递归互斥信号量
 #define configUSE_COUNTING_SEMAPHORES           1  // 是否启用计数信号量
 //#define configUSE_ALTERNATIVE_API               0  // 是否启用替代 API（已废弃）
 //#define configQUEUE_REGISTRY_SIZE               10  // 可注册的信号量和队列数量
 //#define configUSE_QUEUE_SETS                    0  // 是否启用队列集合
 //#define configUSE_TIME_SLICING                  1  // 是否启用时间片调度
 //#define configUSE_NEWLIB_REENTRANT              0  // 是否启用 newlib 重入支持
 //#define configENABLE_BACKWARD_COMPATIBILITY     0  // 是否启用向后兼容
 //#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5  // 线程本地存储指针数量
 //#define configUSE_MINI_LIST_ITEM                1  // 是否使用 MiniListItem_t
 //#define configSTACK_DEPTH_TYPE                  uint16_t  // 堆栈深度类型
 //#define configMESSAGE_BUFFER_LENGTH_TYPE        size_t  // 消息缓冲区长度类型
 //#define configHEAP_CLEAR_MEMORY_ON_FREE         1  // 是否在释放内存时清零
 
 // 内存配置
 #define configSUPPORT_STATIC_ALLOCATION         1  // 支持静态内存分配
 #define configSUPPORT_DYNAMIC_ALLOCATION        1  // 支持动态内存分配
 #define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 10 * 1024 ) )  // 总堆大小
 //#define configAPPLICATION_ALLOCATED_HEAP        1  // 应用程序分配堆
 //#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 1  // 堆栈从单独的堆分配
 
 // 钩子函数配置
 #define configUSE_IDLE_HOOK                     0  // 是否启用空闲任务钩子
 #define configUSE_TICK_HOOK                     0  // 是否启用时钟节拍钩子
 //#define configCHECK_FOR_STACK_OVERFLOW          0  // 是否启用堆栈溢出检测
 #define configUSE_MALLOC_FAILED_HOOK            0  // 是否启用内存分配失败钩子
 //#define configUSE_DAEMON_TASK_STARTUP_HOOK      0  // 是否启用守护任务启动钩子
 //#define configUSE_SB_COMPLETED_CALLBACK         0  // 是否启用 StreamBuffer 完成回调
 
 // API 函数配置
 #define INCLUDE_vTaskPrioritySet                1  // 包含任务优先级设置函数
 #define INCLUDE_uxTaskPriorityGet               1  // 包含获取任务优先级函数
 #define INCLUDE_vTaskDelete                     1  // 包含删除任务函数
 #define INCLUDE_vTaskSuspend                    1  // 包含挂起任务函数
 #define INCLUDE_vTaskDelayUntil                 1  // 包含延迟到指定时间函数
 #define INCLUDE_vTaskDelay                      1  // 包含延迟函数
 #define INCLUDE_xResumeFromISR                  1  // 包含从 ISR 恢复任务函数
 #define INCLUDE_xTaskGetSchedulerState          1  // 包含获取调度器状态函数
 #define INCLUDE_xTaskGetCurrentTaskHandle       1  // 包含获取当前任务句柄函数
 #define INCLUDE_uxTaskGetStackHighWaterMark     0  // 包含获取任务堆栈高水位标记函数
 #define INCLUDE_uxTaskGetStackHighWaterMark2    0  // 包含获取任务堆栈高水位标记函数（扩展）
 #define INCLUDE_xTaskGetIdleTaskHandle          0  // 包含获取空闲任务句柄函数
 #define INCLUDE_eTaskGetState                   0  // 包含获取任务状态函数
 #define INCLUDE_xEventGroupSetBitFromISR        1  // 包含从 ISR 设置事件组位函数
 #define INCLUDE_xTimerPendFunctionCall          0  // 包含挂起函数调用函数
 #define INCLUDE_xTaskAbortDelay                 0  // 包含中止任务延迟函数
 #define INCLUDE_xTaskGetHandle                  0  // 包含获取任务句柄函数
 #define INCLUDE_xTaskResumeFromISR              1  // 包含从 ISR 恢复任务函数
 #define INCLUDE_vTaskCleanUpResources           0  // 包含清理任务资源函数
 
 // 中断优先级配置
 #ifdef __NVIC_PRIO_BITS
     #define configPRIO_BITS                     __NVIC_PRIO_BITS  // 中断优先级位数
 #else
     #define configPRIO_BITS                     4  // 默认中断优先级位数
 #endif
 #define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15  // 库最低中断优先级
 #define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5  // 库最大系统调用中断优先级
 #define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )  // 内核中断优先级
 #define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )  // 最大系统调用中断优先级
 //#define configMAX_API_CALL_INTERRUPT_PRIORITY   [dependent on processor and application]  // 最大 API 调用中断优先级
 
 // 中断处理函数配置
 #define xPortPendSVHandler                      PendSV_Handler  // 定义 PendSV 中断处理函数
 #define vPortSVCHandler                         SVC_Handler  // 定义 SVC 中断处理函数
 //#define xPortSysTickHandler                     SysTick_Handler  // 定义 SysTick 中断处理函数
 
 // 协程配置
 #define configUSE_CO_ROUTINES                   0  // 是否启用协程
 #define configMAX_CO_ROUTINE_PRIORITIES         2  // 协程的有效优先级数目
 
 // 软件定时器配置
 #define configUSE_TIMERS                        0  // 是否启用软件定时器
 #define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 )  // 软件定时器任务优先级
 #define configTIMER_QUEUE_LENGTH                10  // 软件定时器队列长度
 #define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 2 )  // 软件定时器任务堆栈大小
 
 // 运行时间和任务状态收集配置
 //#define configGENERATE_RUN_TIME_STATS           0  // 是否启用运行时间统计功能
 //#define configUSE_TRACE_FACILITY                0  // 是否启用可视化跟踪调试
 //#define configUSE_STATS_FORMATTING_FUNCTIONS    1  // 是否启用统计格式化函数
 
 #endif /* FREERTOS_CONFIG_H */