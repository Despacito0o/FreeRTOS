# FreeRTOS Dynamic Task Creation

This tutorial will guide you on how to dynamically create tasks in FreeRTOS. The code part can be found in the `Despacito/003` project.

## Introduction to Dynamic Task Creation

Dynamic task creation in FreeRTOS allows tasks to be created and deleted during runtime using heap memory management. This approach provides flexibility in application design, allowing your application to adapt to changing requirements at runtime.

## Prerequisites

Before proceeding, ensure you have:

- Completed the FreeRTOS porting tutorial (002)
- Basic knowledge of STM32 programming
- Keil MDK environment set up properly
- STM32F103 development board

## Memory Management in FreeRTOS

FreeRTOS provides several memory allocation schemes:

- **heap_1.c**: Simple allocator, doesn't support freeing memory
- **heap_2.c**: Allows freeing but may suffer from fragmentation
- **heap_3.c**: Wrapper for standard malloc() and free()
- **heap_4.c**: Defragmentation capabilities, most commonly used
- **heap_5.c**: Allows memory across multiple non-adjacent memory regions

For dynamic task creation, we typically use **heap_4.c** which provides a good balance of features and performance.

## Dynamic Task Creation API

To create a task dynamically, use the `xTaskCreate()` API function:

```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,           // Function pointer to task code
    const char * const pcName,           // Descriptive name for debugging
    configSTK_SIZE_TYPE usStackDepth,    // Stack size in words (not bytes)
    void *pvParameters,                  // Parameters passed to the task
    UBaseType_t uxPriority,              // Task priority (0 is lowest)
    TaskHandle_t *pxCreatedTask          // Task handle for reference
);
```

The function returns `pdPASS` if the task was created successfully, or `errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY` if there was not enough memory.

## Example: Creating Multiple Tasks

In this example, we'll create multiple LED tasks with different priorities and blinking patterns:

```c
// Task handles
TaskHandle_t LED1Task_Handler;
TaskHandle_t LED2Task_Handler;

// Task functions
void LED1_Task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // Turn LED ON
        vTaskDelay(500);                     // Delay 500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // Turn LED OFF
        vTaskDelay(500);                     // Delay 500ms
    }
}

void LED2_Task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_14);    // Turn LED ON
        vTaskDelay(200);                     // Delay 200ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_14);  // Turn LED OFF
        vTaskDelay(800);                     // Delay 800ms
    }
}

int main(void)
{
    // System initialization
    SystemInit();
    
    // Configure LEDs
    LED_GPIO_Config();
    
    // Create tasks
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
    
    // Start scheduler
    vTaskStartScheduler();
    
    // Should never reach here
    while(1) {}
}
```

## Passing Parameters to Tasks

Parameters can be passed to tasks during creation:

```c
// Structure for task parameters
typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t delay_on;
    uint32_t delay_off;
} LedParams_t;

// Create LED parameters
LedParams_t led1Params = {GPIOC, GPIO_Pin_13, 500, 500};
LedParams_t led2Params = {GPIOC, GPIO_Pin_14, 200, 800};

// Generic LED task function
void LED_Task(void *pvParameters)
{
    // Cast parameters
    LedParams_t *params = (LedParams_t*)pvParameters;
    
    while(1)
    {
        GPIO_SetBits(params->port, params->pin);      // Turn LED ON
        vTaskDelay(params->delay_on);                 // Delay ON time
        GPIO_ResetBits(params->port, params->pin);    // Turn LED OFF
        vTaskDelay(params->delay_off);                // Delay OFF time
    }
}

// Creating tasks with parameters
xTaskCreate((TaskFunction_t )LED_Task,     
            (const char*    )"LED1_Task",   
            (uint16_t       )128,           
            (void*          )&led1Params,    // Pass LED1 parameters  
            (UBaseType_t    )3,             
            (TaskHandle_t*  )&LED1Task_Handler);
            
xTaskCreate((TaskFunction_t )LED_Task,     
            (const char*    )"LED2_Task",   
            (uint16_t       )128,           
            (void*          )&led2Params,    // Pass LED2 parameters
            (UBaseType_t    )2,             
            (TaskHandle_t*  )&LED2Task_Handler);
```

## Task Control Functions

After creating a task, you can control it using various API functions:

```c
// Delete a task (can delete itself or another task)
void vTaskDelete(TaskHandle_t xTaskToDelete);

// Suspend a task
void vTaskSuspend(TaskHandle_t xTaskToSuspend);

// Resume a suspended task
void vTaskResume(TaskHandle_t xTaskToResume);

// Resume a task from ISR context
BaseType_t xTaskResumeFromISR(TaskHandle_t xTaskToResume);

// Get task priority
UBaseType_t uxTaskPriorityGet(TaskHandle_t xTask);

// Set task priority
void vTaskPrioritySet(TaskHandle_t xTask, UBaseType_t uxNewPriority);
```

## Memory Considerations

When using dynamic task creation, consider these important points:

1. Set `configTOTAL_HEAP_SIZE` in FreeRTOSConfig.h large enough for all tasks
2. Monitor heap usage with `xPortGetFreeHeapSize()`
3. Use higher stack sizes for complex tasks (e.g., tasks with printf)
4. Be aware of memory fragmentation with frequent task creation/deletion

## Troubleshooting

Common issues with dynamic task creation:

1. **"Failed to allocate required memory"**: Increase `configTOTAL_HEAP_SIZE`
2. **Stack overflow**: Increase the stack size parameter in `xTaskCreate()`
3. **Unexpected task behavior**: Check task priorities and ensure proper synchronization
4. **Application crashes**: Use `configCHECK_FOR_STACK_OVERFLOW` to detect stack issues

## Complete Project

For a complete implementation, refer to the `Despacito/003` project which contains the full source code with dynamic task creation examples.

## Related Links

- [FreeRTOS Task Creation API](https://www.freertos.org/a00019.html)
- [FreeRTOS Memory Management](https://www.freertos.org/a00111.html)
- [Task Control APIs](https://www.freertos.org/RTOS-task-control.html)

## Next Steps

After understanding dynamic task creation, you might want to explore:

1. [FreeRTOS Static Task Creation](004-FreeRTOS-Static-Task-Creation.md)
2. [FreeRTOS Project Improvement Guide](005-FreeRTOS-Project-Improvement-Guide.md) 