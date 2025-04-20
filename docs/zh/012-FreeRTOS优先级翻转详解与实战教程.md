# FreeRTOS优先级翻转详解与实战教程：从代码到现象分析

## 前言

在实时操作系统中，优先级翻转是一个常见但又容易被忽视的问题。本文将通过实际代码演示优先级翻转现象，帮助大家深入理解这一概念。如果你对FreeRTOS有兴趣，可以访问我的完整学习资源：[FreeRTOS学习库](https://github.com/Despacito0o/FreeRTOS)，从入门到精通的全面指南！

## 什么是优先级翻转？

优先级翻转是指高优先级任务被低优先级任务间接阻塞的现象。具体场景如下：
- 低优先级任务获取了某个共享资源
- 高优先级任务尝试获取同一资源，但因资源被占用而阻塞
- 中优先级任务此时可以抢占低优先级任务执行
- 结果：中优先级任务先于高优先级任务执行，违背了优先级调度原则

## 实战演示：创建优先级翻转场景

我们将创建三个任务，优先级依次为：
- Task1：低优先级（优先级2）
- Task2：中优先级（优先级3）
- Task3：高优先级（优先级4）

其中Task1和Task3需要共享同一个二值信号量，而Task2不使用该信号量。

### 1. 拷贝工程模板

首先，我们基于之前的二值信号量示例（010）创建新工程（012）。

![工程创建](https://i-blog.csdnimg.cn/direct/94a303792701484b8929c9ec25fee1c4.png)

### 2. 添加延时函数

为模拟任务执行时间，我们需要添加非阻塞的延时函数。创建`delay.c`和`delay.h`文件：

![添加delay.h](https://i-blog.csdnimg.cn/direct/9d92df2fa00b4b1aa5d82c80532edabf.png)
![添加delay.c](https://i-blog.csdnimg.cn/direct/d8e65c3537fc41b59d77ed5c96b6a4c9.png)

delay.h代码内容：
```c
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"                  // Device header


void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif
```

delay.c代码内容：
```c
#include "stm32f10x.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
```

### 3. 实现三个任务

#### Task1：低优先级任务

Task1会获取信号量，执行3秒钟的操作，然后释放信号量。关键点是这个任务执行时间较长。

```c
void myTask1(void *arg)
{
    BaseType_t res = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        /* 获取信号量 */
        printf("The low-priority Task1 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task1 failed to get semaphore\r\n");
        }

        /* 执行其他逻辑 */
        printf("A low-priority Task1 is being executed\r\n");
        
        Delay_ms(3000);

        /* 释放信号量 */
        printf("Low-priority Task1 releases semaphores\r\n");
        res = xSemaphoreGive(myPrintfQueueHandler);
        if (res != pdPASS)
        {
            printf("Task1 failed to release semaphore\r\n");
        }

        taskEXIT_CRITICAL();
        
        vTaskDelay(1000);
    }
}
```

#### Task2：中优先级任务

Task2不使用信号量，只是执行自己的逻辑，模拟系统中的其他任务。

```c
void myTask2(void *arg)
{
    while (1)
    {
        taskENTER_CRITICAL();
        printf("Task 2 of medium priority is being executed\r\n");
        Delay_ms(1500);
        printf("task2 is executed once\r\n");
        taskEXIT_CRITICAL();
        vTaskDelay(1000);
    }
}
```

#### Task3：高优先级任务

Task3也需要使用与Task1相同的信号量，但处理时间只有1秒。

```c
void myTask3(void *arg)
{
    BaseType_t res = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        
        /* 获取信号量 */
        printf("The high priority Task3 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task3 failed to get semaphore\r\n");
        }

        /* 执行其他逻辑 */
        printf("High Priority Task3 is executing...\r\n");
        Delay_ms(1000);

        /* 释放信号量 */
        printf("A high-priority Task3 releases a semaphore\r\n");
        res = xSemaphoreGive(myPrintfQueueHandler);
        if (res != pdPASS)
        {
            printf("Failed to release semaphore in Task3\r\n");
        }

        taskEXIT_CRITICAL();
        
        vTaskDelay(1000);
    }
}
```

### 4. 主函数实现

在主函数中，我们创建信号量和三个任务：

```c
int main(void)
{
    USART_Config();
    
    //xSemaphoreCreateBinary(myPrintfQueueHandler,0);//x开头的，不会主动释放信号量
    vSemaphoreCreateBinary(myPrintfQueueHandler); //v开头的，创建完会主动释放一次信号量
    if(myPrintfQueueHandler == NULL)
    {
        printf("The semaphore is created failed\r\n");
    }
    else 
    {
        printf("The semaphore is created successfully\r\n");
    }

    xTaskCreate(startTask,"startTask",128,NULL,2,&startTaskHandler);
    
    vTaskStartScheduler();
    
    while (1)
    {
        
    }
}
```

### 5. 执行结果分析

编译并运行代码，我们可以观察到优先级翻转现象：

![运行结果](https://i-blog.csdnimg.cn/direct/a473b55a3fb94982b16f74a476edd03a.png)

#### 执行流程详细分析：

1. **初始阶段**：
   - 信号量创建成功后默认释放一次
   - 最高优先级的Task3先执行，获取信号量
   - Task3执行1秒后释放信号量，进入1秒阻塞等待

2. **中间阶段**：
   - Task2开始执行，需执行1.5秒
   - 当Task2执行到1秒时，Task3阻塞时间结束，再次获取信号量
   - Task3执行完毕后再次进入1秒阻塞等待

3. **优先级翻转发生**：
   - Task2继续执行剩余的0.5秒
   - Task2执行完进入阻塞，Task1获得执行机会
   - Task1获取信号量并开始执行耗时操作
   - 0.5秒后Task3阻塞结束，尝试获取信号量但失败（被Task1占用）
   - **关键点**：此时Task3（高优先级）被Task1（低优先级）间接阻塞
   - Task2（中优先级）能够抢占Task1执行，而高优先级的Task3却必须等待

4. **最终阶段**：
   - 当Task2执行完一轮后，Task1继续执行剩余工作
   - Task1释放信号量后，Task3立即获得信号量并执行

## 优先级翻转的解决方案

在实际应用中，优先级翻转可能导致系统响应延迟，甚至引发严重问题。解决方案主要有：

1. **优先级继承**：当高优先级任务等待低优先级任务占用的资源时，临时提升低优先级任务的优先级。FreeRTOS提供的互斥量（mutex）支持此特性。

2. **优先级天花板**：为所有可能访问共享资源的任务设置相同的高优先级。

3. **禁用中断**：在关键区域禁用中断，确保操作的原子性。但这种方法不适用于耗时操作。

## 小结

优先级翻转是嵌入式实时系统中的常见问题，本文通过实际例子演示了其发生过程。在实际开发中，建议：

1. 减少共享资源的使用
2. 缩短临界区执行时间
3. 合理使用互斥量代替二值信号量
4. 考虑任务间通信的替代方案

更多关于FreeRTOS的学习资源，欢迎访问我的GitHub项目：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)，包含从入门到精通的全面指南，适合初学者和专业开发者！

---

如果您觉得本文有帮助，请点赞、收藏并关注，您的支持是我创作的动力！

--- 