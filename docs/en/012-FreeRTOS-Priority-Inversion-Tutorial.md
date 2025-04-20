# FreeRTOS Priority Inversion Tutorial: Analysis from Code to Phenomenon

## Introduction

In real-time operating systems, priority inversion is a common but often overlooked problem. This article will demonstrate the priority inversion phenomenon through actual code, helping everyone deeply understand this concept. If you are interested in FreeRTOS, you can visit my complete learning resource: [FreeRTOS Learning Library](https://github.com/Despacito0o/FreeRTOS), a comprehensive guide from beginner to expert!

## What is Priority Inversion?

Priority inversion refers to the phenomenon where a high-priority task is indirectly blocked by a low-priority task. The specific scenario is as follows:
- A low-priority task acquires a shared resource
- A high-priority task tries to acquire the same resource but is blocked because the resource is occupied
- A medium-priority task can preempt the low-priority task at this time
- Result: The medium-priority task executes before the high-priority task, violating the principle of priority scheduling

## Practical Demonstration: Creating a Priority Inversion Scenario

We will create three tasks with priorities as follows:
- Task1: Low priority (priority 2)
- Task2: Medium priority (priority 3)
- Task3: High priority (priority 4)

Task1 and Task3 need to share the same binary semaphore, while Task2 does not use this semaphore.

### 1. Copy Project Template

First, we create a new project (012) based on the previous binary semaphore example (010).

![Project Creation](https://i-blog.csdnimg.cn/direct/94a303792701484b8929c9ec25fee1c4.png)

### 2. Add Delay Function

To simulate task execution time, we need to add a non-blocking delay function. Create `delay.c` and `delay.h` files:

![Add delay.h](https://i-blog.csdnimg.cn/direct/9d92df2fa00b4b1aa5d82c80532edabf.png)
![Add delay.c](https://i-blog.csdnimg.cn/direct/d8e65c3537fc41b59d77ed5c96b6a4c9.png)

delay.h code content:
```c
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"                  // Device header


void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif
```

delay.c code content:
```c
#include "stm32f10x.h"

/**
  * @brief  Microsecond delay
  * @param  xus Delay duration, range: 0~233015
  * @retval None
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				// Set timer reload value
	SysTick->VAL = 0x00;					// Clear current count value
	SysTick->CTRL = 0x00000005;				// Set clock source to HCLK, start timer
	while(!(SysTick->CTRL & 0x00010000));	// Wait for count to reach 0
	SysTick->CTRL = 0x00000004;				// Close timer
}

/**
  * @brief  Millisecond delay
  * @param  xms Delay duration, range: 0~4294967295
  * @retval None
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  Second delay
  * @param  xs Delay duration, range: 0~4294967295
  * @retval None
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
```

### 3. Implement Three Tasks

#### Task1: Low Priority Task

Task1 will acquire the semaphore, perform operations for 3 seconds, and then release the semaphore. The key point is that this task has a long execution time.

```c
void myTask1(void *arg)
{
    BaseType_t res = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        /* Acquire semaphore */
        printf("The low-priority Task1 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task1 failed to get semaphore\r\n");
        }

        /* Execute other logic */
        printf("A low-priority Task1 is being executed\r\n");
        
        Delay_ms(3000);

        /* Release semaphore */
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

#### Task2: Medium Priority Task

Task2 does not use semaphores, it just executes its own logic, simulating other tasks in the system.

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

#### Task3: High Priority Task

Task3 also needs to use the same semaphore as Task1, but the processing time is only 1 second.

```c
void myTask3(void *arg)
{
    BaseType_t res = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        
        /* Acquire semaphore */
        printf("The high priority Task3 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task3 failed to get semaphore\r\n");
        }

        /* Execute other logic */
        printf("High Priority Task3 is executing...\r\n");
        Delay_ms(1000);

        /* Release semaphore */
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

### 4. Main Function Implementation

In the main function, we create a semaphore and three tasks:

```c
int main(void)
{
    USART_Config();
    
    //xSemaphoreCreateBinary(myPrintfQueueHandler,0);// x-prefix, will not actively release semaphore
    vSemaphoreCreateBinary(myPrintfQueueHandler); // v-prefix, will actively release semaphore once after creation
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

### 5. Execution Result Analysis

Compile and run the code, we can observe the priority inversion phenomenon:

![Running Result](https://i-blog.csdnimg.cn/direct/a473b55a3fb94982b16f74a476edd03a.png)

#### Detailed Execution Flow Analysis:

1. **Initial Stage**:
   - The semaphore is released once by default after successful creation
   - The highest priority Task3 executes first, acquiring the semaphore
   - Task3 releases the semaphore after 1 second of execution, entering a 1-second blocking wait

2. **Middle Stage**:
   - Task2 begins to execute, requiring 1.5 seconds
   - When Task2 has executed for 1 second, Task3's blocking time ends, and it acquires the semaphore again
   - After Task3 completes execution, it enters a 1-second blocking wait again

3. **Priority Inversion Occurs**:
   - Task2 continues to execute for the remaining 0.5 seconds
   - Task2 enters blocking after execution, and Task1 gets the chance to execute
   - Task1 acquires the semaphore and begins to execute time-consuming operations
   - After 0.5 seconds, Task3's blocking ends, tries to acquire the semaphore but fails (occupied by Task1)
   - **Key Point**: At this time, Task3 (high priority) is indirectly blocked by Task1 (low priority)
   - Task2 (medium priority) can preempt Task1's execution, while the high-priority Task3 must wait

4. **Final Stage**:
   - After Task2 completes one round, Task1 continues to execute the remaining work
   - After Task1 releases the semaphore, Task3 immediately acquires the semaphore and executes

## Solutions to Priority Inversion

In practical applications, priority inversion may cause system response delays or even serious problems. The main solutions are:

1. **Priority Inheritance**: When a high-priority task is waiting for a resource occupied by a low-priority task, temporarily increase the priority of the low-priority task. The mutex provided by FreeRTOS supports this feature.

2. **Priority Ceiling**: Set the same high priority for all tasks that may access shared resources.

3. **Disable Interrupts**: Disable interrupts in critical sections to ensure atomicity of operations. But this method is not suitable for time-consuming operations.

## Summary

Priority inversion is a common problem in embedded real-time systems. This article demonstrates the process of its occurrence through a practical example. In practical development, it is recommended to:

1. Reduce the use of shared resources
2. Shorten critical section execution time
3. Properly use mutexes instead of binary semaphores
4. Consider alternative approaches for inter-task communication

For more learning resources about FreeRTOS, please visit my GitHub project: [https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS), which includes a comprehensive guide from beginner to expert, suitable for beginners and professional developers!

---

If you find this article helpful, please like, favorite, and follow. Your support is my motivation for creation!

--- 