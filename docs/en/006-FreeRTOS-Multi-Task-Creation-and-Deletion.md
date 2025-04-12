# FreeRTOS Multi-Task Creation and Deletion

> This document is part of the FreeRTOS + STM32 development series. In this chapter, we will learn about multi-task creation and deletion in FreeRTOS.
> 
> **For more quality resources, please visit my GitHub repository: [https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)**

## Introduction

This section builds upon our previous project and explores the creation and deletion mechanisms of FreeRTOS multiple tasks. We will learn how to dynamically create, manage, and delete tasks, and how to effectively utilize these mechanisms to build real-time systems.

## Key Concepts

### Task States in FreeRTOS

In FreeRTOS, a task can be in one of several states:
- **Running**: The task is currently executing
- **Ready**: The task is ready to execute but another task with higher priority is running
- **Blocked**: The task is waiting for an event (time delay, semaphore, etc.)
- **Suspended**: The task has been suspended and will not be scheduled
- **Deleted**: The task has been deleted

### Task Creation API

FreeRTOS offers two methods for task creation:

1. **Dynamic Memory Allocation**:
```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,
    const char * const pcName,
    uint16_t usStackDepth,
    void *pvParameters,
    UBaseType_t uxPriority,
    TaskHandle_t *pxCreatedTask
);
```

2. **Static Memory Allocation**:
```c
TaskHandle_t xTaskCreateStatic(
    TaskFunction_t pvTaskCode,
    const char * const pcName,
    uint32_t ulStackDepth,
    void *pvParameters,
    UBaseType_t uxPriority,
    StackType_t *puxStackBuffer,
    StaticTask_t *pxTaskBuffer
);
```

### Task Deletion API

To delete a task, use the following function:
```c
void vTaskDelete(TaskHandle_t xTaskToDelete);
```

If `NULL` is passed as the parameter, the calling task will delete itself.

## Example Project

The example project demonstrates:

1. **Sequential Task Creation**: Task1 creates Task2, and later creates Task3
2. **Task Self-Deletion**: Task2 counts to 10 and then deletes itself
3. **Task Deletion by Another Task**: Task3 counts to 5 and then deletes Task1
4. **Task Priority Effects**: Observing how priority affects execution

### Key Code Sections

#### Main Function
```c
int main(void)
{
    /* Initialize system clock */
    SystemInit();
    
    /* Initialize UART */
    USART_Config();
    
    printf("\r\n======== FreeRTOS Multi-Task Creation and Deletion Example ========\r\n");
    
    /* Create Task1 */
    xTaskCreate((TaskFunction_t)Task1_Entry,          /* Task function */
                (const char *)"Task1",                /* Task name */
                (uint16_t)512,                        /* Stack size */
                (void *)NULL,                         /* Parameters */
                (UBaseType_t)1,                       /* Priority */
                (TaskHandle_t *)&Task1_Handle);       /* Task handle */
    
    /* Start scheduler */
    vTaskStartScheduler();
    
    /* Should never reach here */
    while(1)
    {
    }
}
```

#### Task1 (Creates Task2 and Task3)
```c
static void Task1_Entry(void *parameter)
{
    uint32_t count = 0;
    
    printf("Task1 created successfully!\r\n");
    
    /* Create Task2 */
    xTaskCreate((TaskFunction_t)Task2_Entry,
                (const char *)"Task2",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)2,
                (TaskHandle_t *)&Task2_Handle);
    
    while(1)
    {
        printf("Task1 running, count value:%d\r\n", count++);
        
        /* Create Task3 after 5 iterations */
        if(count == 5)
        {
            printf("Task1 creating Task3...\r\n");
            xTaskCreate((TaskFunction_t)Task3_Entry,
                        (const char *)"Task3",
                        (uint16_t)512,
                        (void *)NULL,
                        (UBaseType_t)3,
                        (TaskHandle_t *)&Task3_Handle);
        }
        
        vTaskDelay(500);
    }
}
```

#### Task2 (Self-Deletion)
```c
static void Task2_Entry(void *parameter)
{
    uint32_t count = 0;
    
    printf("Task2 created successfully!\r\n");
    
    while(1)
    {
        printf("Task2 running, count value:%d\r\n", count++);
        
        /* Delete itself after 10 iterations */
        if(count == 10)
        {
            printf("Task2 deleting itself...\r\n");
            vTaskDelete(NULL);
        }
        
        vTaskDelay(500);
    }
}
```

#### Task3 (Deletes Task1)
```c
static void Task3_Entry(void *parameter)
{
    uint32_t count = 0;
    
    printf("Task3 created successfully!\r\n");
    
    while(1)
    {
        printf("Task3 running, count value:%d\r\n", count++);
        
        /* Delete Task1 after 5 iterations */
        if(count == 5)
        {
            printf("Task3 deleting Task1...\r\n");
            vTaskDelete(Task1_Handle);
        }
        
        vTaskDelay(500);
    }
}
```

## Expected Output

The program will produce output similar to the following:

```
======== FreeRTOS Multi-Task Creation and Deletion Example ========
Task1 created successfully!
Task2 created successfully!
Task1 running, count value:0
Task2 running, count value:0
Task1 running, count value:1
Task2 running, count value:1
Task1 running, count value:2
Task2 running, count value:2
Task1 running, count value:3
Task2 running, count value:3
Task1 running, count value:4
Task2 running, count value:4
Task1 creating Task3...
Task1 running, count value:5
Task2 running, count value:5
Task3 created successfully!
Task3 running, count value:0
Task1 running, count value:6
Task2 running, count value:6
Task3 running, count value:1
...
Task2 running, count value:9
Task3 running, count value:4
Task2 deleting itself...
Task3 deleting Task1...
Task3 running, count value:5
Task3 running, count value:6
...
```

## Key Points to Remember

1. **Task Priority**: Higher priority tasks preempt lower priority tasks
2. **Task Deletion**: When a task is deleted, its resources are reclaimed
3. **Self-Deletion**: A task can delete itself by passing NULL to vTaskDelete()
4. **Task Management**: Always maintain proper task handles for management
5. **Memory Usage**: Be careful with dynamic task creation in resource-constrained systems

## Complete Code

For the complete code example and more detailed documentation, please refer to:
[https://github.com/Despacito0o/FreeRTOS/Despacito/006](https://github.com/Despacito0o/FreeRTOS/tree/main/Despacito/006)

## Learning Tips

This section on multi-task creation and deletion forms the foundation for more advanced FreeRTOS features. A solid understanding of these concepts is essential before moving on to inter-task communication and synchronization. 