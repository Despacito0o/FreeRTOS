# FreeRTOS多任务创建与删除

> 本文是FreeRTOS + STM32开发系列教程的一部分。本章我们将学习FreeRTOS的多任务创建与删除相关知识。
> 
> **更多优质资源，请访问GitHub仓库：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)**

## 简介

本节将在之前完善的工程基础上，进一步探索FreeRTOS多任务的创建与删除机制。我们将学习如何动态创建、管理和删除任务，以及如何有效利用这些机制构建实时系统。

## 关键概念

### FreeRTOS中的任务状态

在FreeRTOS中，任务可以处于以下几种状态：
- **运行态（Running）**：任务当前正在执行
- **就绪态（Ready）**：任务已准备好执行，但另一个更高优先级的任务正在运行
- **阻塞态（Blocked）**：任务正在等待某个事件（时间延迟、信号量等）
- **挂起态（Suspended）**：任务已被挂起，不会被调度执行
- **删除态（Deleted）**：任务已被删除

### 任务创建API

FreeRTOS提供了两种任务创建方法：

1. **动态内存分配方式**：
```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,      /* 任务函数指针 */
    const char * const pcName,      /* 任务名称 */
    uint16_t usStackDepth,          /* 任务堆栈大小 */
    void *pvParameters,             /* 传递给任务的参数 */
    UBaseType_t uxPriority,         /* 任务优先级 */
    TaskHandle_t *pxCreatedTask     /* 任务句柄 */
);
```

2. **静态内存分配方式**：
```c
TaskHandle_t xTaskCreateStatic(
    TaskFunction_t pvTaskCode,      /* 任务函数指针 */
    const char * const pcName,      /* 任务名称 */
    uint32_t ulStackDepth,          /* 任务堆栈大小 */
    void *pvParameters,             /* 传递给任务的参数 */
    UBaseType_t uxPriority,         /* 任务优先级 */
    StackType_t *puxStackBuffer,    /* 任务堆栈缓冲区 */
    StaticTask_t *pxTaskBuffer      /* 任务控制块 */
);
```

### 任务删除API

要删除任务，使用以下函数：
```c
void vTaskDelete(TaskHandle_t xTaskToDelete);
```

如果传入参数为`NULL`，则删除当前调用此函数的任务自身。

## 示例项目

示例项目演示了：

1. **顺序任务创建**：任务1创建任务2，之后再创建任务3
2. **任务自删除**：任务2计数到10后删除自己
3. **任务被其他任务删除**：任务3计数到5后删除任务1
4. **任务优先级效应**：观察优先级如何影响执行顺序

### 关键代码部分

#### 主函数
```c
int main(void)
{
    /* 初始化系统时钟 */
    SystemInit();
    
    /* 初始化串口 */
    USART_Config();
    
    printf("\r\n======== FreeRTOS多任务创建与删除示例 ========\r\n");
    
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t)Task1_Entry,          /* 任务入口函数 */
                (const char *)"Task1",                /* 任务名称 */
                (uint16_t)512,                        /* 任务堆栈大小 */
                (void *)NULL,                         /* 任务入口函数参数 */
                (UBaseType_t)1,                       /* 任务优先级 */
                (TaskHandle_t *)&Task1_Handle);       /* 任务句柄 */
    
    /* 启动任务调度器 */
    vTaskStartScheduler();
    
    /* 正常情况下不会执行到这里 */
    while(1)
    {
    }
}
```

#### 任务1（创建任务2和任务3）
```c
static void Task1_Entry(void *parameter)
{
    uint32_t count = 0;
    
    printf("任务1创建成功!\r\n");
    
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t)Task2_Entry,          /* 任务入口函数 */
                (const char *)"Task2",                /* 任务名称 */
                (uint16_t)512,                        /* 任务堆栈大小 */
                (void *)NULL,                         /* 任务入口函数参数 */
                (UBaseType_t)2,                       /* 任务优先级 */
                (TaskHandle_t *)&Task2_Handle);       /* 任务句柄 */
    
    while(1)
    {
        printf("任务1运行中，计数值:%d\r\n", count++);
        
        /* 任务运行5次后创建任务3 */
        if(count == 5)
        {
            printf("任务1即将创建任务3...\r\n");
            
            /* 创建任务3 */
            xTaskCreate((TaskFunction_t)Task3_Entry,          /* 任务入口函数 */
                        (const char *)"Task3",                /* 任务名称 */
                        (uint16_t)512,                        /* 任务堆栈大小 */
                        (void *)NULL,                         /* 任务入口函数参数 */
                        (UBaseType_t)3,                       /* 任务优先级 */
                        (TaskHandle_t *)&Task3_Handle);       /* 任务句柄 */
        }
        
        /* 延时500个tick */
        vTaskDelay(500);
    }
}
```

#### 任务2（自删除）
```c
static void Task2_Entry(void *parameter)
{
    uint32_t count = 0;
    
    printf("任务2创建成功!\r\n");
    
    while(1)
    {
        printf("任务2运行中，计数值:%d\r\n", count++);
        
        /* 任务运行10次后删除自己 */
        if(count == 10)
        {
            printf("任务2即将删除自己...\r\n");
            vTaskDelete(NULL);
        }
        
        /* 延时500个tick */
        vTaskDelay(500);
    }
}
```

#### 任务3（删除任务1）
```c
static void Task3_Entry(void *parameter)
{
    uint32_t count = 0;
    
    printf("任务3创建成功!\r\n");
    
    while(1)
    {
        printf("任务3运行中，计数值:%d\r\n", count++);
        
        /* 任务运行5次后删除任务1 */
        if(count == 5)
        {
            printf("任务3即将删除任务1...\r\n");
            vTaskDelete(Task1_Handle);
        }
        
        /* 延时500个tick */
        vTaskDelay(500);
    }
}
```

## 预期输出

程序将产生类似以下的输出：

```
======== FreeRTOS多任务创建与删除示例 ========
任务1创建成功!
任务2创建成功!
任务1运行中，计数值:0
任务2运行中，计数值:0
任务1运行中，计数值:1
任务2运行中，计数值:1
任务1运行中，计数值:2
任务2运行中，计数值:2
任务1运行中，计数值:3
任务2运行中，计数值:3
任务1运行中，计数值:4
任务2运行中，计数值:4
任务1即将创建任务3...
任务1运行中，计数值:5
任务2运行中，计数值:5
任务3创建成功!
任务3运行中，计数值:0
任务1运行中，计数值:6
任务2运行中，计数值:6
任务3运行中，计数值:1
...
任务2运行中，计数值:9
任务3运行中，计数值:4
任务2即将删除自己...
任务3即将删除任务1...
任务3运行中，计数值:5
任务3运行中，计数值:6
...
```

## 重点记忆事项

1. **任务优先级**：高优先级任务会抢占低优先级任务
2. **任务删除**：当任务被删除时，其资源会被回收
3. **自删除**：任务可以通过向vTaskDelete()传递NULL来删除自己
4. **任务管理**：始终保持适当的任务句柄以进行管理
5. **内存使用**：在资源受限的系统中要谨慎使用动态任务创建

## 完整代码

完整代码示例和更详细的文档请参考：
[https://github.com/Despacito0o/FreeRTOS/Despacito/006](https://github.com/Despacito0o/FreeRTOS/tree/main/Despacito/006)

## 学习提示

多任务创建与删除这一部分是后续学习更高级FreeRTOS特性的基础。在转向任务间通信和同步之前，扎实掌握这些概念至关重要。 