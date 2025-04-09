/**
 * @file FreeRTOSConfig.h
 * @author Despacito (https://github.com/Despacito0o/FreeRTOS)
 * @brief FreeRTOS配置文件
 */
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


// 调度器配置
#define configUSE_PREEMPTION		1  // 启用抢占式调度
#define configIDLE_SHOULD_YIELD		1  // 空闲任务应让出CPU

// 时钟配置
#define configCPU_CLOCK_HZ			( ( unsigned long ) 72000000 )  // CPU时钟频率，单位Hz
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )  // 时钟节拍频率，单位Hz
#define configUSE_16_BIT_TICKS		0  // 使用32位时钟节拍

// 任务配置
#define configMAX_PRIORITIES		( 5 )  // 最大任务优先级数
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )  // 最小任务堆栈大小
#define configMAX_TASK_NAME_LEN		( 16 )  // 任务名称最大长度

// 内存配置
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 17 * 1024 ) )  // 总堆大小

// 钩子函数配置
#define configUSE_IDLE_HOOK			0  // 禁用空闲任务钩子
#define configUSE_TICK_HOOK			0  // 禁用时钟节拍钩子

// API函数配置
#define INCLUDE_vTaskPrioritySet		1  // 包含任务优先级设置函数
#define INCLUDE_uxTaskPriorityGet		1  // 包含获取任务优先级函数
#define INCLUDE_vTaskDelete				1  // 包含删除任务函数
#define INCLUDE_vTaskCleanUpResources	0  // 不包含清理任务资源函数
#define INCLUDE_vTaskSuspend			1  // 包含挂起任务函数
#define INCLUDE_vTaskDelayUntil			1  // 包含延迟到指定时间函数
#define INCLUDE_vTaskDelay				1  // 包含延迟函数

// 中断优先级配置
#define configKERNEL_INTERRUPT_PRIORITY 		255  // 内核中断优先级
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191  // 相当于0xb0，或优先级11
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15  // 库内核中断优先级

// 中断处理函数配置
#define xPortPendSVHandler 	PendSV_Handler  // 定义PendSV中断处理函数
#define vPortSVCHandler 	SVC_Handler  // 定义SVC中断处理函数
#define xPortSysTickHandler SysTick_Handler  // 定义SysTick中断处理函数

#endif /* FREERTOS_CONFIG_H */


