# FreeRTOS Static Task Creation

This tutorial will guide you on how to create tasks using static memory allocation in FreeRTOS. The code part can be found in the `Despacito/004` project.

## Introduction

Unlike dynamic task creation, static task creation uses pre-allocated memory to create tasks, suitable for resource-constrained embedded systems.

## Basic Steps for Static Task Creation

1. Pre-declare the task control block and task stack
2. Use the xTaskCreateStatic() function to create tasks
3. Implement static memory callback functions for idle tasks and timer tasks

## Example Code

```c
// Define task control block and stack space
StaticTask_t xTaskBuffer;
StackType_t xStack[configMINIMAL_STACK_SIZE];

// Static task creation
TaskHandle_t xHandle = xTaskCreateStatic(
    vTaskFunction,            // Task function
    "STATIC_TASK",            // Task name
    configMINIMAL_STACK_SIZE, // Stack depth
    (void*)1,                 // Parameters
    1,                        // Priority
    xStack,                   // Stack pointer
    &xTaskBuffer              // Task control block pointer
);

// Static memory callback for idle task
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

## Configuration Items

To enable static memory allocation, you need to configure the following in FreeRTOSConfig.h:

```c
#define configSUPPORT_STATIC_ALLOCATION 1
```

If you also need to use timers, you need to implement a static memory callback function for the timer task:

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

## Advantages

1. Fixed memory usage that can be determined at compile time
2. Avoids memory fragmentation issues possible with dynamic memory allocation
3. More suitable for safety-critical applications
4. Easier to analyze and optimize memory usage

## Summary

Static task creation is an important feature provided by FreeRTOS, especially suitable for scenarios with limited memory or strict memory usage requirements. Through this tutorial and the `Despacito/004` project, you can master how to apply static memory allocation to create tasks in real projects. 