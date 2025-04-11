# FreeRTOS静态任务创建

这篇教程将指导您如何在FreeRTOS中使用静态内存分配方式创建任务。代码部分可以在`Despacito/004`项目中找到。

## 简介

与动态任务创建不同，静态任务创建使用预先分配的内存来创建任务，适用于资源受限的嵌入式系统。

## 静态任务创建基本步骤

1. 预先声明任务控制块和任务栈
2. 使用xTaskCreateStatic()函数创建任务
3. 实现空闲任务和定时器任务的静态内存回调函数

## 示例代码

```c
// 定义任务控制块和栈空间
StaticTask_t xTaskBuffer;
StackType_t xStack[configMINIMAL_STACK_SIZE];

// 静态创建任务
TaskHandle_t xHandle = xTaskCreateStatic(
    vTaskFunction,            // 任务函数
    "STATIC_TASK",            // 任务名称
    configMINIMAL_STACK_SIZE, // 栈深度
    (void*)1,                 // 参数
    1,                        // 优先级
    xStack,                   // 栈空间指针
    &xTaskBuffer              // 任务控制块指针
);

// 空闲任务所需的静态内存回调
void vApplicationGetIdleTaskMemory(
    StaticTask_t **ppxIdleTaskTCBBuffer,
    StackType_t **ppxIdleTaskStackBuffer,
    uint32_t *pulIdleTaskStackSize
) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];
    
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
```

## 配置项

要启用静态内存分配，需要在FreeRTOSConfig.h中进行以下配置：

```c
#define configSUPPORT_STATIC_ALLOCATION 1
```

如果还需要使用定时器，则需要实现定时器任务的静态内存回调函数：

```c
void vApplicationGetTimerTaskMemory(
    StaticTask_t **ppxTimerTaskTCBBuffer,
    StackType_t **ppxTimerTaskStackBuffer,
    uint32_t *pulTimerTaskStackSize
) {
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];
    
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
```

## 优势

1. 固定的内存占用，可在编译时确定
2. 避免了动态内存分配可能的内存碎片问题
3. 更适合安全关键型应用
4. 便于内存使用分析和优化

## 总结

静态任务创建是FreeRTOS提供的一种重要功能，尤其适用于内存受限或对内存使用有严格要求的场景。通过本教程和`Despacito/004`项目，您可以掌握如何在实际项目中应用静态内存分配创建任务。 