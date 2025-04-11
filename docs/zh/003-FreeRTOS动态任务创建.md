# FreeRTOS动态任务创建

这篇教程将指导您如何在FreeRTOS中动态创建任务。代码部分可以在`Despacito/003`项目中找到。

## 动态任务创建简介

FreeRTOS中的动态任务创建允许使用堆内存管理在运行时创建和删除任务。这种方法提供了应用设计的灵活性，使您的应用能够适应运行时的变化需求。

## 前提条件

在继续之前，请确保您已经：

- 完成FreeRTOS移植教程(002)
- 具备STM32编程的基础知识
- 正确设置Keil MDK环境
- 拥有STM32F103开发板

## FreeRTOS中的内存管理

FreeRTOS提供了几种内存分配方案：

- **heap_1.c**：简单分配器，不支持释放内存
- **heap_2.c**：允许释放但可能存在碎片化问题
- **heap_3.c**：标准malloc()和free()的包装器
- **heap_4.c**：具有碎片整理能力，最常用
- **heap_5.c**：允许跨多个非相邻内存区域的内存管理

对于动态任务创建，我们通常使用**heap_4.c**，它提供了功能和性能的良好平衡。

## 动态任务创建API

要动态创建任务，使用`xTaskCreate()`API函数：

```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,           // 指向任务代码的函数指针
    const char * const pcName,           // 用于调试的描述性名称
    configSTK_SIZE_TYPE usStackDepth,    // 堆栈大小（以字为单位，非字节）
    void *pvParameters,                  // 传递给任务的参数
    UBaseType_t uxPriority,              // 任务优先级（0最低）
    TaskHandle_t *pxCreatedTask          // 任务句柄，用于引用
);
```

如果任务创建成功，函数返回`pdPASS`，如果内存不足，返回`errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY`。

## 示例：创建多个任务

在这个示例中，我们将创建多个具有不同优先级和闪烁模式的LED任务：

```c
// 任务句柄
TaskHandle_t LED1Task_Handler;
TaskHandle_t LED2Task_Handler;

// 任务函数
void LED1_Task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED亮
        vTaskDelay(500);                     // 延时500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED灭
        vTaskDelay(500);                     // 延时500ms
    }
}

void LED2_Task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_14);    // LED亮
        vTaskDelay(200);                     // 延时200ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_14);  // LED灭
        vTaskDelay(800);                     // 延时800ms
    }
}

int main(void)
{
    // 系统初始化
    SystemInit();
    
    // 配置LED
    LED_GPIO_Config();
    
    // 创建任务
    xTaskCreate((TaskFunction_t )LED1_Task,     
                (const char*    )"LED1_Task",   
                (uint16_t       )128,           
                (void*          )NULL,          
                (UBaseType_t    )3,             
                (TaskHandle_t*  )&LED1Task_Handler);
                
    xTaskCreate((TaskFunction_t )LED2_Task,     
                (const char*    )"LED2_Task",   
                (uint16_t       )128,           
                (void*          )NULL,          
                (UBaseType_t    )2,             
                (TaskHandle_t*  )&LED2Task_Handler);
    
    // 启动调度器
    vTaskStartScheduler();
    
    // 正常情况下不会到达这里
    while(1) {}
}
```

## 向任务传递参数

在创建任务时可以传递参数：

```c
// 任务参数结构体
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t delay_on;
    uint32_t delay_off;
} LedParams_t;

// 创建LED参数
LedParams_t led1Params = {GPIOC, GPIO_Pin_13, 500, 500};
LedParams_t led2Params = {GPIOC, GPIO_Pin_14, 200, 800};

// 通用LED任务函数
void LED_Task(void *pvParameters)
{
    // 转换参数
    LedParams_t *params = (LedParams_t*)pvParameters;
    
    while(1)
    {
        GPIO_SetBits(params->port, params->pin);      // LED亮
        vTaskDelay(params->delay_on);                 // 延时亮的时间
        GPIO_ResetBits(params->port, params->pin);    // LED灭
        vTaskDelay(params->delay_off);                // 延时灭的时间
    }
}

// 创建带参数的任务
xTaskCreate((TaskFunction_t )LED_Task,     
            (const char*    )"LED1_Task",   
            (uint16_t       )128,           
            (void*          )&led1Params,    // 传递LED1参数  
            (UBaseType_t    )3,             
            (TaskHandle_t*  )&LED1Task_Handler);
            
xTaskCreate((TaskFunction_t )LED_Task,     
            (const char*    )"LED2_Task",   
            (uint16_t       )128,           
            (void*          )&led2Params,    // 传递LED2参数
            (UBaseType_t    )2,             
            (TaskHandle_t*  )&LED2Task_Handler);
```

## 任务控制函数

创建任务后，您可以使用各种API函数控制它：

```c
// 删除任务（可以删除自己或其他任务）
void vTaskDelete(TaskHandle_t xTaskToDelete);

// 挂起任务
void vTaskSuspend(TaskHandle_t xTaskToSuspend);

// 恢复被挂起的任务
void vTaskResume(TaskHandle_t xTaskToResume);

// 从中断服务例程中恢复任务
BaseType_t xTaskResumeFromISR(TaskHandle_t xTaskToResume);

// 获取任务优先级
UBaseType_t uxTaskPriorityGet(TaskHandle_t xTask);

// 设置任务优先级
void vTaskPrioritySet(TaskHandle_t xTask, UBaseType_t uxNewPriority);
```

## 内存注意事项

使用动态任务创建时，请考虑以下重要事项：

1. 在FreeRTOSConfig.h中设置足够大的`configTOTAL_HEAP_SIZE`以容纳所有任务
2. 使用`xPortGetFreeHeapSize()`监控堆使用情况
3. 为复杂任务（例如，使用printf的任务）使用更大的堆栈大小
4. 注意频繁任务创建/删除带来的内存碎片化问题

## 故障排除

动态任务创建的常见问题：

1. **"无法分配所需内存"**：增加`configTOTAL_HEAP_SIZE`
2. **堆栈溢出**：增加`xTaskCreate()`中的堆栈大小参数
3. **任务行为异常**：检查任务优先级并确保正确的同步
4. **应用崩溃**：使用`configCHECK_FOR_STACK_OVERFLOW`检测堆栈问题

## 完整项目

有关完整实现，请参考`Despacito/003`项目，其中包含带有动态任务创建示例的完整源代码。

## 相关链接

- [FreeRTOS任务创建API](https://www.freertos.org/a00019.html)
- [FreeRTOS内存管理](https://www.freertos.org/a00111.html)
- [任务控制API](https://www.freertos.org/RTOS-task-control.html)

## 下一步

了解动态任务创建后，您可能想探索：

1. [FreeRTOS静态任务创建](004-FreeRTOS静态任务创建.md)
2. [FreeRTOS项目工程完善指南](005-FreeRTOS项目工程完善指南.md) 