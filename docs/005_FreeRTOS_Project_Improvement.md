# FreeRTOS项目工程完善指南：STM32系列

> 本文是FreeRTOS + STM32开发系列教程的一部分。我们将完善之前移植的FreeRTOS工程，添加串口功能并优化配置文件。
> 
> **更多优质资源，请访问我的GitHub仓库：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)**

## 准备工作

首先，我们需要准备以下文件：
1. FreeRTOS配置文件（FreeRTOSConfig.h）
2. 串口初始化文件（usart.h和usart.c）

## 关键文件解析

### usart.h文件核心部分

这个文件定义了STM32串口通信所需的宏和函数声明。以下是文件的核心部分：

```c
#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

/** 
  * 串口宏定义，不同的串口挂载的总线和IO不一样，移植时需要修改这几个宏
  * 1-修改总线时钟的宏，uart1挂载到apb2总线，其他uart挂载到apb1总线
  * 2-修改GPIO的宏
  */
	
// 串口1-USART1
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

// 其他串口配置...

void USART_Config(void);
#endif /* __USART_H */
```

### usart.c文件核心部分

此文件实现了串口初始化和重定向printf函数的功能：

```c
#include "usart.h"

/**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
```

### FreeRTOSConfig.h文件核心部分

FreeRTOSConfig.h是FreeRTOS的核心配置文件，通过修改这些宏定义，可以灵活调整RTOS的行为：

```c
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
#define configUSE_TICKLESS_IDLE                 1  // 启用低功耗无滴答模式
 
// 时钟配置
#define configCPU_CLOCK_HZ                      (SystemCoreClock)  // CPU 时钟频率
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )  // 系统节拍频率
#define configUSE_16_BIT_TICKS                  0  // 使用 32 位节拍计数器
```

## 工程完善步骤

### 1. 准备新工程

复制003动态创建工程模板并重命名为005，这将作为我们新的工程模板。

### 2. 替换FreeRTOSConfig.h文件

打开005工程，导航到`...\Despacito\005\FreeRTOS`目录，更换我们准备好的FreeRTOSConfig.h文件。

### 3. 创建驱动文件夹

导航到`...\Desktop\Despacito\005`，新建一个Driver文件夹。

### 4. 添加串口文件

在Driver文件夹中新建一个usart文件夹，用来存放串口初始化文件，并将usart.c和usart.h这两个文件放进该目录下。

### 5. 配置工程包含路径

打开工程，点击魔法棒->C/C++(AC6)->Include Paths->...添加如下路径，点击OK->OK。

### 6. 添加Driver组和串口文件

添加Driver组以及串口初始化文件，并整理一下点击OK。

### 7. 修改main.c

在main.c中添加`#include "usart.h"`头文件，并调用串口初始化函数`USART_Config()`。

### 8. 处理静态内存分配问题

编译后发现有错误，这是因为我们开启了静态内存分配但没有实现相关函数。有两种解决方法：
1. 将`configSUPPORT_STATIC_ALLOCATION`改为0
2. 自己实现相关函数

我们选择方法2，从004项目中复制静态任务创建函数：

```c
StaticTask_t        IdleTaskTCB;
StackType_t         IdleTaskStack[configMINIMAL_STACK_SIZE];
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                   StackType_t ** ppxIdleTaskStackBuffer,
                                   uint32_t * pulIdleTaskStackSize )
{
    * ppxIdleTaskTCBBuffer = &IdleTaskTCB;
    * ppxIdleTaskStackBuffer = IdleTaskStack;
    * pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
```

### 9. 优化SysTick中断处理

前面我们在FreeRTOSConfig.h中注释了`xPortSysTickHandler`的定义，现在我们需要规范化SysTick中断处理：

1. 打开port.c，找到xPortSysTickHandler函数
2. 在stm32f10x_it.c中修改SysTick_Handler函数，加入FreeRTOS调度相关代码：

```c
#include "stm32f10x_it.h"
#include "FreeRTOS.h"
#include "task.h"

void SysTick_Handler(void)
{
    #if(INCLUDE_xTaskGetSchedulerState==1)
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    #endif
    {
        xPortSysTickHandler();
    }
}
```

### 10. 最终编译

完成以上步骤后，我们的工程就可以方便地使用宏配置和printf打印信息了。

## 总结

通过本文的步骤，我们成功完善了FreeRTOS工程，添加了：

1. 完整的FreeRTOSConfig.h配置文件
2. 串口通信功能
3. printf调试输出功能
4. 更规范的中断处理方式

这些改进使得我们的FreeRTOS工程更加健壮和实用，为后续开发复杂应用奠定了良好基础。 