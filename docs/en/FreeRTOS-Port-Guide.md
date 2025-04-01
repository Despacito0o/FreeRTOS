# FreeRTOS Porting Guide

> This guide provides detailed instructions for porting FreeRTOS to the STM32 platform, including source code acquisition, project configuration, and file modifications.

## Prerequisites

### 1.1 Open Project Folder
First, open the previously created keil6 folder to prepare for FreeRTOS porting.

[Click to open keil6 folder creation tutorial](https://blog.csdn.net/supershmily/article/details/146780134?spm=1001.2014.3001.5501)

![Open keil6 folder](https://i-blog.csdnimg.cn/direct/953f51d2cfe047b3a7963093f9647e5f.png)

### 1.2 Download FreeRTOS Source Code
Visit the FreeRTOS official website to download the latest version:

![Download FreeRTOS source code](https://i-blog.csdnimg.cn/direct/1b330855776f4a688cf8ce1e15a993b1.png)

### 1.3 Get Kernel Documentation
Find the FreeRTOS kernel documentation on the official website:

![Get kernel documentation](https://i-blog.csdnimg.cn/direct/77acc0a6f0b9453896b7c1419819609a.png)

### 1.4 Select Download Version
Click to download FreeRTOS, select the latest version FreeRTOS 202212.01:

![Select download version](https://i-blog.csdnimg.cn/direct/ce5830134bd7473f83f10734946861f7.png)

### 1.5 Extract Files
Extract the downloaded files to the created FreeRTOS directory:

![Extract files](https://i-blog.csdnimg.cn/direct/d632ebe55ec245e096146ea1df2ae3c1.png)

## Project Configuration

### 2.1 Create New Project
1. Create a new 002 project file
2. Copy the project template from the previous lesson
3. Add FreeRTOS src and FreeRTOS portable folders

![Create new project](https://i-blog.csdnimg.cn/direct/3ba0bf8841ac4939bc6fd8235cf4c17a.png)

### 2.2 Copy Source Files
Navigate to `...\FreeRTOSv202212.01\FreeRTOS\Source` and copy all .c files to the 002's freertos src folder:

![Copy source files 1](https://i-blog.csdnimg.cn/direct/b556b5c9559142bab694f00b775dc854.png)
![Copy source files 2](https://i-blog.csdnimg.cn/direct/ab9e3acc65a74930bb36c6c6d15e0478.png)

### 2.3 Copy Port Files
Navigate to `...\FreeRTOSv202212.01\FreeRTOS\Source\portable` and copy the "MemMang" folder and "RVDS" folder to the newly created freertos port folder:

![Copy port files 1](https://i-blog.csdnimg.cn/direct/eb30108c2e424bd8acf22f3c0ec91c98.png)
![Copy port files 2](https://i-blog.csdnimg.cn/direct/6c5a764f67004e009e721712530b724e.png)

### 2.4 Copy Header Files
Navigate to `...\FreeRTOSv202212.01\FreeRTOS\Source` and copy the include folder directly to the project folder and rename it to freertos include:

![Copy header files 1](https://i-blog.csdnimg.cn/direct/386d0fa8afba4d9fbe3a0ea3aea87e6c.png)
![Copy header files 2](https://i-blog.csdnimg.cn/direct/12673f270b124a46aaf98d140e407af9.png)

### 2.5 Organize File Structure
For better file organization, create a FreeRTOS folder under the 002 directory and place the three folders created above in it:

![Organize file structure](https://i-blog.csdnimg.cn/direct/88c40549c293436095b2fc6a53eb0c5f.png)

### 2.6 Configure FreeRTOSConfig.h
Navigate to `...\FreeRTOSv202212.01\FreeRTOS\Demo\CORTEX_STM32F103_Keil` to find freertosconfig.h and copy it to the user folder:

![Configure FreeRTOSConfig.h](https://i-blog.csdnimg.cn/direct/3bef10073b364903a0b3097a5e4e1f84.png)

## Keil Project Configuration

### 3.1 Add File Groups
1. Open Keil, click the three small boxes to the right of the magic wand
2. Add freertos port group, add the following files:
   - `...\Despacito\002\FreeRTOS\freertos portable\RVDS\ARM_CM3\port.c`
   - `...\Despacito\002\FreeRTOS\freertos portable\MemMang\heap_4.c`

![Add file groups 1](https://i-blog.csdnimg.cn/direct/d6fa53a8c2074a89944ba443f6b1815f.png)

3. Add freertos src group, add all .c files:

![Add file groups 2](https://i-blog.csdnimg.cn/direct/8759c58afa1e475f823e5b3bc8924a5a.png)

4. Add FreeRTOSConfig.h file to the user group:

![Add file groups 3](https://i-blog.csdnimg.cn/direct/d71638dd9cee4df588e2d9838f76cc88.png)

### 3.2 Configure Header File Paths
Click magic wand --> c/c++(AC6) --> include path, add the following paths:

![Configure header file paths](https://i-blog.csdnimg.cn/direct/43f73e6f19f04411a400a5e07ce9f0c3.png)

## File Modifications

### 4.1 Modify FreeRTOSConfig.h
The FreeRTOSConfig.h file needs few modifications, mainly:
1. Modify the development board corresponding header file (e.g., STM32F1 series uses `#include "stm32f10x.h"`)
2. Add serial port header file `#include "stm32f10x_usart.h"` (for assertion operation printing information)

![Modify FreeRTOSConfig.h](https://i-blog.csdnimg.cn/direct/3464377815724a94b1230a67c5d75001.png)

### 4.2 Modify stm32f10x_it.c
The SysTick interrupt service function is the heartbeat clock of FreeRTOS, driving FreeRTOS operation. FreeRTOS has already implemented:
1. `vPortSetupTimerInterrupt()` function in port.c
2. Generic `xPortSysTickHandler()` function

We only need to implement the `SysTick_Handler()` function on the STM32 platform in stm32f10x_it.c.

Also, comment out the `PendSV_Handler()` and `SVC_Handler()` functions, as FreeRTOS has already implemented `xPortPendSVHandler()` and `vPortSVCHandler()` functions in port.c.

```c
/* Modified stm32f10x_it.c file */
#include "stm32f10x_it.h"
#include "FreeRTOS.h"                    //FreeRTOS usage
#include "task.h" 

/* Other code remains unchanged */

// Comment out SVC_Handler
//void SVC_Handler(void)
//{
//}

// Comment out PendSV_Handler
//void PendSV_Handler(void)
//{
//}

// Implement SysTick_Handler
void SysTick_Handler(void)
{
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) //System is running
    {
        xPortSysTickHandler();    
    }
}
```

### 4.3 Modify main.c
Modify main.c file, add FreeRTOS related header files and initialization code:

```c
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

int main(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    while(1) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  
    }
}
```

## Compilation Problem Solving

### 5.1 Common Compilation Errors
FreeRTOS porting compilation errors are mainly caused by:

1. **Compiler Version Incompatibility**
   - `__forceinline` keyword not recognized: `__forceinline` in RVDS port files is ARM Compiler 5 (AC5) specific inline syntax
   - Assembly syntax errors: Assembly instruction syntax in RVDS port files is incompatible with AC6

2. **Missing Key Configurations**
   - Interrupt service function renaming issues
   - Undefined data types

3. **Other Possible Causes**
   - Interrupt priority conflicts
   - Memory allocation issues

### 5.2 Solutions
1. **Replace Port Files**
   - Delete portable/RVDS/ARM_CM3 directory
   - Copy files from FreeRTOS/portable/GCC/ARM_CM3 to project
   - Update Keil project file reference paths

2. **Modify Compiler Settings**
   - In Keil's Options for Target → C/C++ tab:
     - Use AC5 compiler
     - Or enable AC6's GNU compatibility mode

3. **Verify Key Configurations**
```c
// FreeRTOSConfig.h key configuration example
#define configUSE_TIMERS 1
#define configTIMER_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define configTIMER_QUEUE_LENGTH 10
#define configKERNEL_INTERRUPT_PRIORITY 255
```

### 5.3 Switch to GCC Compiler
Switch to GCC compiler in Keil:

![Switch to GCC compiler 1](https://i-blog.csdnimg.cn/direct/ab4d0ab1a18e4f3c8728279f7c2ec04b.png)
![Switch to GCC compiler 2](https://i-blog.csdnimg.cn/direct/6cbc7465a2854ee88ae59b4a3ca57a16.png)
![Switch to GCC compiler 3](https://i-blog.csdnimg.cn/direct/0ae79ce28d264311bd42c2d3a54deed1.png)

### 5.4 Compilation Results
Compilation completed with no errors or warnings, porting successful:

![Compilation results](https://i-blog.csdnimg.cn/direct/2d99480e286647f78b09ef4867bfbd51.png)

## Summary
Through the above steps, we have successfully completed the FreeRTOS porting on the STM32 platform. The main steps include:
1. Obtain and configure FreeRTOS source code
2. Create project and add necessary files
3. Modify related configuration files
4. Solve compilation issues

After porting is complete, you can start developing with FreeRTOS. As a lightweight real-time operating system, FreeRTOS has wide applications in embedded system development. 