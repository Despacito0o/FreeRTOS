# STM32上创建简单FreeRTOS程序详解

本教程将指导你如何在STM32平台上创建一个简单的FreeRTOS程序，实现LED闪烁功能。

## 准备工作

1. STM32F103C8T6开发板
2. Keil MDK开发环境
3. ST-Link调试器
4. FreeRTOS源码

## 基本步骤

### 1. 创建项目

首先，在Keil MDK中创建一个新的STM32项目：

1. 打开Keil MDK，选择"Project" -> "New uVision Project..."
2. 选择芯片型号STM32F103C8
3. 在"Run-Time Environment"中添加必要的组件

### 2. 配置FreeRTOS

1. 创建FreeRTOS文件夹，并添加核心文件：
   - tasks.c
   - list.c
   - queue.c
   - timers.c
   - port.c
   - heap_4.c等内存管理文件

2. 创建FreeRTOSConfig.h文件，进行基本配置：

```c
#define configUSE_PREEMPTION                1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_IDLE_HOOK                 0
#define configUSE_TICK_HOOK                 0
#define configCPU_CLOCK_HZ                  (72000000)
#define configTICK_RATE_HZ                  (1000)
#define configMAX_PRIORITIES                (32)
#define configMINIMAL_STACK_SIZE            (128)
#define configTOTAL_HEAP_SIZE               (15*1024)
```

### 3. 配置中断

确保正确设置SysTick、PendSV和SVC中断处理函数：

```c
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
```

### 4. 初始化系统

在main.c中，进行系统初始化：

```c
int main(void)
{
    // 系统时钟配置
    SystemInit();
    
    // 外设初始化
    LED_Init();
    
    // 创建任务
    xTaskCreate(LED_Task, "LED_Task", 128, NULL, 1, NULL);
    
    // 启动调度器
    vTaskStartScheduler();
    
    // 如果一切正常，永远不会到这里
    while(1);
}
```

### 5. 创建LED任务

```c
void LED_Task(void *pvParameters)
{
    while(1)
    {
        LED_Toggle();       // 切换LED状态
        vTaskDelay(500);    // 延时500ms
    }
}
```

### 6. LED控制函数

```c
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void LED_Toggle(void)
{
    static uint8_t ledStatus = 0;
    
    if(ledStatus)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        ledStatus = 0;
    }
    else
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        ledStatus = 1;
    }
}
```

## 项目编译与下载

1. 编译项目，确保无错误
2. 连接ST-Link调试器
3. 下载程序到STM32开发板
4. 运行程序，观察LED闪烁

## 调试技巧

1. 使用printf重定向到串口进行调试输出
2. 使用逻辑分析仪观察信号时序
3. 使用Keil的逻辑分析器观察变量变化

## 常见问题解决

1. 如遇到启动失败，检查时钟配置
2. 如遇到任务创建失败，检查堆栈大小配置
3. 如遇到中断问题，检查中断优先级配置

## 高级功能扩展

成功运行基本示例后，可以尝试：

1. 创建多个任务
2. 使用队列在任务间传递消息
3. 使用信号量同步任务
4. 使用互斥量保护共享资源

## 相关资源

- [FreeRTOS官方文档](https://www.freertos.org/Documentation/RTOS_book.html)
- [FreeRTOS移植到keil6](../002-FreeRTOS移植到keil6.md)
- [FreeRTOS动态任务创建](../003-FreeRTOS动态任务创建.md)
- [FreeRTOS静态任务创建](../004-FreeRTOS静态任务创建.md) 