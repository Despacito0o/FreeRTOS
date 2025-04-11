# FreeRTOS Port to Keil6

This guide will walk you through the process of porting FreeRTOS to STM32F103 using Keil MDK 6. The complete example code can be found in the `Despacito/002` project.

## Introduction

Porting FreeRTOS to a new development environment involves several steps, including correctly configuring the FreeRTOS kernel, adapting it to the target platform, and integrating it with your existing project structure. This guide focuses specifically on porting FreeRTOS to STM32F103 microcontrollers using the Keil MDK 6 IDE.

## Prerequisites

Before starting, you should have:

1. Keil MDK 6 (or newer) installed with STM32F1xx support
2. STM32F103 development board (such as Blue Pill or similar)
3. ST-Link V2 (or compatible) programmer
4. FreeRTOS source code (V10.0.0 or newer recommended)
5. STM32 standard peripheral library

## Step 1: Prepare Your Keil Project

1. Open Keil MDK and create a new project for your STM32F103 board
2. In the Device selection window, choose STMicroelectronics > STM32F1 Series > STM32F103
3. Configure the project for your specific chip (e.g., STM32F103C8T6)
4. Add the necessary CMSIS and peripheral library files to your project

## Step 2: Download and Extract FreeRTOS

1. Download the latest FreeRTOS from the [official website](https://www.freertos.org/a00104.html)
2. Extract the downloaded file to a convenient location
3. You will need files from the following directories:
   - `FreeRTOS/Source/` - Core FreeRTOS files
   - `FreeRTOS/Source/portable/MemMang/` - Memory management
   - `FreeRTOS/Source/portable/RVDS/ARM_CM3/` - ARM Cortex-M3 port files

## Step 3: Add FreeRTOS Files to Your Project

Create the following folder structure in your project:

```
YourProject/
├── FreeRTOS/
│   ├── inc/          (for FreeRTOS headers)
│   ├── port/         (for portable files)
│   └── src/          (for FreeRTOS source)
```

Add the following files to your project:

1. Core files (to `src/`):
   - tasks.c
   - list.c
   - queue.c
   - timers.c

2. Memory management (to `src/`):
   - Choose one based on your needs, typically heap_4.c is recommended

3. Port files (to `port/`):
   - port.c
   - portmacro.h

4. Header files (to `inc/`):
   - FreeRTOS.h
   - task.h
   - queue.h
   - semphr.h
   - etc.

## Step 4: Create the FreeRTOSConfig.h File

Create a file named `FreeRTOSConfig.h` in your project's include directory with the following basic configuration:

```c
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f10x.h"

/* Basic configurations */
#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_TICKLESS_IDLE                 0
#define configCPU_CLOCK_HZ                      72000000
#define configTICK_RATE_HZ                      1000
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                128
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configUSE_MUTEXES                       1
#define configQUEUE_REGISTRY_SIZE               8
#define configCHECK_FOR_STACK_OVERFLOW          2
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_APPLICATION_TASK_TAG          0
#define configUSE_COUNTING_SEMAPHORES           1
#define configGENERATE_RUN_TIME_STATS           0

/* Memory allocation */
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTOTAL_HEAP_SIZE                   10240

/* Hook function configurations */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_MALLOC_FAILED_HOOK            0

/* Interrupt configurations */
#define configKERNEL_INTERRUPT_PRIORITY         255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    191

/* Define mapping for Cortex-M3 */
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler
#define xPortSysTickHandler                     SysTick_Handler

/* Include runtime statistics functions */
#ifdef INCLUDE_FREERTOS_RUNTIME_STATS
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() 
#define portGET_RUN_TIME_COUNTER_VALUE()         0
#endif

/* Optional functions - most used */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetCurrentTaskHandle       1

#endif /* FREERTOS_CONFIG_H */
```

Adjust the configuration values to match your specific hardware and application requirements.

## Step 5: Configure the SysTick Timer

The FreeRTOS port for ARM Cortex-M3 uses the SysTick timer for its tick interrupt. Configure your system clock and SysTick:

```c
/* In your system initialization code */
void SystemInit(void)
{
    /* Reset the RCC clock configuration to the default reset state */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)
    {
    }

    /* Configure PLL */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }

    /* Configure HCLK, PCLK1, PCLK2 */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
}
```

## Step 6: Setup Vector Table and Interrupt Handlers

Ensure your startup code correctly initializes the vector table and that the interrupt handlers are properly defined:

```c
/* In your startup file */
void SVC_Handler(void)
{
    /* This will be overridden by the FreeRTOS macro */
}

void PendSV_Handler(void)
{
    /* This will be overridden by the FreeRTOS macro */
}

void SysTick_Handler(void)
{
    /* This will be overridden by the FreeRTOS macro */
}
```

## Step 7: Create Your First Task

Create a simple blinking LED task to test your FreeRTOS port:

```c
/* LED task function */
void vLEDTask(void *pvParameters)
{
    /* Initialize GPIO for LED (PC13 for Blue Pill) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    while(1)
    {
        /* Toggle LED */
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
        
        /* Delay for 500ms */
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/* Main function */
int main(void)
{
    /* Setup the system */
    SystemInit();
    
    /* Create LED task */
    xTaskCreate(vLEDTask, "LED", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    
    /* Start the scheduler */
    vTaskStartScheduler();
    
    /* Should never reach here */
    while(1);
}
```

## Step 8: Build and Debug

1. Compile your project
2. Connect your STM32F103 board via ST-Link
3. Flash the program and debug

## Common Issues and Solutions

### Issue 1: "Error: Undefined symbol xPortPendSVHandler"
- Check that the proper macro definitions are in FreeRTOSConfig.h:
  ```c
  #define vPortSVCHandler SVC_Handler
  #define xPortPendSVHandler PendSV_Handler
  #define xPortSysTickHandler SysTick_Handler
  ```

### Issue 2: "Error: L6218E: Undefined symbol (section: .text)"
- Ensure all required FreeRTOS files are included in your build
- Check that heap management file (e.g., heap_4.c) is included

### Issue 3: FreeRTOS crashes upon starting the scheduler
- Check that configCPU_CLOCK_HZ matches your actual system clock
- Ensure priority settings are correct for your microcontroller

### Issue 4: Tasks not running or sharing time properly
- Verify configTICK_RATE_HZ is set appropriately
- Check task priorities and stack sizes

## Advanced Topics

Once you have the basic port working, you can explore these advanced features:

1. **Task notifications** - Lightweight alternative to semaphores and queues
2. **Software timers** - Time-triggered functions
3. **Event groups** - Multiple event flags in a single variable
4. **Stream and message buffers** - Efficient data passing between tasks
5. **Static allocation** - No dynamic memory allocation required

## Conclusion

You have now successfully ported FreeRTOS to your STM32F103 using Keil MDK 6. This provides a solid foundation for developing more complex multitasking applications.

For a complete implementation, refer to the `Despacito/002` project which contains the full source code with a working FreeRTOS port.

## Next Steps

- [FreeRTOS Dynamic Task Creation](003-FreeRTOS-Dynamic-Task-Creation.md)
- [FreeRTOS Static Task Creation](004-FreeRTOS-Static-Task-Creation.md)
- [FreeRTOS Project Improvement Guide](005-FreeRTOS-Project-Improvement-Guide.md)