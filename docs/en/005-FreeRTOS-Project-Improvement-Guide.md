# FreeRTOS Project Improvement Guide: STM32 Series

> This article is part of the FreeRTOS + STM32 development tutorial series. We will improve the previously ported FreeRTOS project by adding UART functionality and optimizing configuration files. The code part can be found in the `Despacito/005` project.

## Preparation

First, we need to prepare the following files:
1. FreeRTOS configuration file (FreeRTOSConfig.h)
2. UART initialization files (usart.h and usart.c)

## Key File Analysis

### Core Parts of usart.h

This file defines the macros and function declarations needed for STM32 UART communication. Here are the core parts of the file:

```c
#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

/** 
  * UART macro definitions. Different UARTs are attached to different buses and IOs, which need to be modified when porting:
  * 1-Modify the bus clock macro; UART1 is attached to APB2 bus, other UARTs are attached to APB1 bus
  * 2-Modify GPIO macros
  */
	
// UART1-USART1
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO Pin Definitions
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

// Other UART configurations...

void USART_Config(void);
#endif /* __USART_H */
```

### Core Parts of usart.c

This file implements UART initialization and the redirection of the printf function:

```c
#include "usart.h"

/**
  * @brief  Configure the nested vectored interrupt controller NVIC
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Nested vectored interrupt controller group selection */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Configure USART as interrupt source */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* Preemption priority */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* Sub priority */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* Enable interrupt */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* Initialize NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
```

### Core Parts of FreeRTOSConfig.h

FreeRTOSConfig.h is the core configuration file for FreeRTOS. By modifying these macro definitions, you can flexibly adjust the behavior of the RTOS:

```c
/**
 * @file FreeRTOSConfig.h
 * @author Despacito (https://github.com/Despacito0o/FreeRTOS)
 * @brief FreeRTOS configuration file
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
 
#include "stm32f10x.h"  // Device header file
 
// Scheduler configuration
#define configUSE_PREEMPTION                    1  // Enable preemptive scheduler
#define configUSE_TICKLESS_IDLE                 1  // Enable low power tickless mode
 
// Clock configuration
#define configCPU_CLOCK_HZ                      (SystemCoreClock)  // CPU clock frequency
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )  // System tick frequency
#define configUSE_16_BIT_TICKS                  0  // Use 32-bit tick counter
```

## Project Improvement Steps

### 1. Prepare a New Project

Copy the 003 dynamic task creation project template and rename it to 005, which will serve as our new project template.

### 2. Replace FreeRTOSConfig.h

Open the 005 project, navigate to the `...\Despacito\005\FreeRTOS` directory, and replace with our prepared FreeRTOSConfig.h file.

### 3. Create a Driver Folder

Navigate to `...\Desktop\Despacito\005` and create a new Driver folder.

### 4. Add UART Files

Inside the Driver folder, create a usart folder to store UART initialization files, and place usart.c and usart.h in this directory.

### 5. Configure Project Include Paths

Open the project, click the magic wand -> C/C++(AC6) -> Include Paths -> ... and add the appropriate paths, then click OK -> OK.

### 6. Add the Driver Group and UART Files

Add the Driver group along with the UART initialization files, organize them, and click OK.

### 7. Modify main.c

Add the `#include "usart.h"` header to main.c and call the UART initialization function `USART_Config()`.

### 8. Handle Static Memory Allocation Issues

When compiling, you may encounter errors because we enabled static memory allocation but didn't implement the related functions. There are two solutions:
1. Change `configSUPPORT_STATIC_ALLOCATION` to 0
2. Implement the required functions ourselves

We choose option 2 and copy the static task creation function from the 004 project:

```c
StaticTask_t        IdleTaskTCB;
StackType_t         IdleTaskStack[configMINIMAL_STACK_SIZE];
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                   StackType_t ** ppxIdleTaskStackBuffer,
                                   uint32_t * pulIdleTaskStackSize )
{
    * ppxIdleTaskTCBBuffer = &IdleTaskTCB;
    * ppxIdleTaskStackBuffer = IdleTaskStack;
    * pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
```

### 9. Optimize SysTick Interrupt Handling

Earlier, we commented out the `xPortSysTickHandler` definition in FreeRTOSConfig.h. Now we need to standardize the SysTick interrupt handling:

1. Open port.c and find the xPortSysTickHandler function
2. Modify the SysTick_Handler function in stm32f10x_it.c by adding FreeRTOS scheduling related code:

```c
#include "stm32f10x_it.h"
#include "FreeRTOS.h"
#include "task.h"

void SysTick_Handler(void)
{
    #if(INCLUDE_xTaskGetSchedulerState==1)
    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    #endif
    {
        xPortSysTickHandler();
    }
}
```

### 10. Final Compilation

After completing the above steps, our project can now conveniently use macro configurations and printf for printing information.

## Summary

Through the steps in this article, we have successfully improved the FreeRTOS project by adding:

1. A complete FreeRTOSConfig.h configuration file
2. UART communication functionality
3. Printf debugging output
4. More standardized interrupt handling

These improvements make our FreeRTOS project more robust and practical, laying a solid foundation for developing complex applications in the future. 