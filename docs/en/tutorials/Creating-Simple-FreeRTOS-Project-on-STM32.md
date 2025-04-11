# Creating a Simple FreeRTOS Project on STM32

This tutorial will guide you on how to create a simple FreeRTOS program on the STM32 platform, implementing an LED blinking functionality.

## Prerequisites

1. STM32F103C8T6 development board
2. Keil MDK development environment
3. ST-Link debugger
4. FreeRTOS source code

## Basic Steps

### 1. Create a Project

First, create a new STM32 project in Keil MDK:

1. Open Keil MDK, select "Project" -> "New uVision Project..."
2. Choose the STM32F103C8 chip model
3. Add necessary components in the "Run-Time Environment"

### 2. Configure FreeRTOS

1. Create a FreeRTOS folder and add core files:
   - tasks.c
   - list.c
   - queue.c
   - timers.c
   - port.c
   - Memory management file such as heap_4.c

2. Create a FreeRTOSConfig.h file with basic configuration:

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

### 3. Configure Interrupts

Ensure proper configuration of SysTick, PendSV, and SVC interrupt handlers:

```c
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
```

### 4. Initialize the System

In main.c, initialize the system:

```c
int main(void)
{
    // System clock configuration
    SystemInit();
    
    // Peripheral initialization
    LED_Init();
    
    // Create task
    xTaskCreate(LED_Task, "LED_Task", 128, NULL, 1, NULL);
    
    // Start the scheduler
    vTaskStartScheduler();
    
    // If everything is normal, will never reach here
    while(1);
}
```

### 5. Create LED Task

```c
void LED_Task(void *pvParameters)
{
    while(1)
    {
        LED_Toggle();       // Toggle LED state
        vTaskDelay(500);    // Delay 500ms
    }
}
```

### 6. LED Control Functions

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

## Project Compilation and Download

1. Compile the project, ensure no errors
2. Connect the ST-Link debugger
3. Download the program to the STM32 development board
4. Run the program and observe the LED blinking

## Debugging Tips

1. Redirect printf to UART for debug output
2. Use a logic analyzer to observe signal timing
3. Use Keil's logic analyzer to observe variable changes

## Common Problem Solutions

1. If startup fails, check clock configuration
2. If task creation fails, check stack size configuration
3. If interrupt issues occur, check interrupt priority configuration

## Advanced Feature Extensions

After successfully running the basic example, you can try:

1. Creating multiple tasks
2. Using queues to pass messages between tasks
3. Using semaphores to synchronize tasks
4. Using mutexes to protect shared resources

## Related Resources

- [FreeRTOS Official Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [FreeRTOS Port to Keil6](../002-FreeRTOS-Port-to-Keil6.md)
- [FreeRTOS Dynamic Task Creation](../003-FreeRTOS-Dynamic-Task-Creation.md)
- [FreeRTOS Static Task Creation](../004-FreeRTOS-Static-Task-Creation.md) 