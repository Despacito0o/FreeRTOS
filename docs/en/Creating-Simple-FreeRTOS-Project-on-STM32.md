# Creating a Simple FreeRTOS Project on STM32

## Introduction
This article will provide a detailed explanation of how to create a simple FreeRTOS program on the STM32 platform, and verify the program's correct operation through an LED blinking task. The entire process will be presented step by step, ensuring that even beginners can easily get started.

> **Source Code**: The project files for this tutorial have been uploaded to GitHub, you can get the complete code from the following link:
> [https://github.com/Despacito0o/FreeRTOS.git](https://github.com/Despacito0o/FreeRTOS.git)

## Development Environment Preparation
- Keil MDK 5.x or higher version
- STM32F103 series development board (this tutorial uses STM32F103C8)
- ST-Link debugger (if using actual hardware)

## Detailed Steps

### 1. Copy the Project Template
First, we need to copy a previously created project template and name it 003. This is to preserve the original project while developing the FreeRTOS program on the new project, avoiding damage to the original project. Using a template also ensures that the basic STM32 configuration has been completed, eliminating the tedious steps of starting from scratch.

> **Tip**: If you cloned the project directly from GitHub, you can find the basic project template in the `Despacito/002` directory.

![Copy Project Template](https://i-blog.csdnimg.cn/direct/62e7f9855aba4f08be71028476798cec.png)

### 2. Clean Up Unnecessary Header Files
Open the project file and delete unnecessary header files. This step is to streamline the project, removing components not related to our current FreeRTOS program development, reducing possible conflicts and compilation errors. At the same time, a clean project structure helps us better understand the components of FreeRTOS and our program structure.

![Delete Unnecessary Header Files](https://i-blog.csdnimg.cn/direct/29216208fa0543dd86fa7c9338a5cc7d.png)

### 3. Modify the FreeRTOS Configuration File
Next, we need to modify the `freertosconfig.h` file to add definitions for three key interrupt handlers. This is an important step in FreeRTOS program development. FreeRTOS needs to use some system interrupts, including:
- PendSV_Handler: Used for task switching
- SVC_Handler: Used for system service calls
- SysTick_Handler: Used for system tick timing, the time basis for FreeRTOS task scheduling

By defining these, we tell the compiler that FreeRTOS's interrupt handler functions will use the system's default functions of the same name.

```cpp
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler
#define xPortSysTickHandler SysTick_Handler
```

![Modify FreeRTOS Configuration](https://i-blog.csdnimg.cn/direct/7bb208bd7d6a4b0898697b89894f30eb.png)

### 4. Comment Out the Original Interrupt Handler Functions
Since we have already handed over the three key interrupts to FreeRTOS in the previous step, we need to comment out the original three interrupt handler functions in STM32's interrupt file `stm32f10x_it.c`. If not commented out, it will cause function redefinition errors because both FreeRTOS and the STM32 standard library define functions with the same name.

![Comment Interrupt Handler 1](https://i-blog.csdnimg.cn/direct/685c23e1c58342d4b609b5a0db610e05.png)
![Comment Interrupt Handler 2](https://i-blog.csdnimg.cn/direct/85ca5f72949c435ead14443615f5d7f9.png)

### 5. Write the Test Program
After completing the basic configuration, we need to write a test program to verify that FreeRTOS is working correctly. In embedded system development, LED blinking is usually the simplest and most intuitive test method, also known as the "Hello World of the embedded world."

#### 5.1 Define the Task Handle
First, define a task handle, which is an identifier used in FreeRTOS to operate and manage tasks.
```cpp
TaskHandle_t myTaskHandler;
```

#### 5.2 Create a Task
Use the `xTaskCreate` function to create a task. This function has six parameters:
- Task function name: `myTask`, specifies the entry function of the task
- Task name: `"myTask"`, a string for debugging identification
- Stack size: `128`, specifies the stack space size required by the task
- Input parameters: `NULL`, can be passed to the task
- Priority: `2`, task priority, higher number means higher priority
- Task handle: `&myTaskHandler`, used to return the task handle

```cpp
xTaskCreate(myTask, "myTask", 128, NULL, 2, &myTaskHandler);
```

#### 5.3 Start the Task Scheduler
After creating the task, you need to start the FreeRTOS task scheduler to make the system start running and schedule according to task priorities.
```cpp
vTaskStartScheduler();
```

#### 5.4 Create the Task Function
Define the task function, which is the entry point for task execution. FreeRTOS task functions are usually an infinite loop, as task termination would cause the system to error.
```cpp
void myTask(void *arg)
{
    while(1)
    {
        // Task code will be executed here
    }
}
```

#### 5.5 Implement the LED Blinking Functionality
Add LED toggle operations to the task function to make the LED blink at fixed time intervals, so we can visually observe if the task is executing as expected.
```cpp
void myTask(void *arg)
{
    while(1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED on
        vTaskDelay(500);                     // Delay 500 clock ticks, equivalent to 500ms
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED off
        vTaskDelay(500);                     // Delay another 500ms
    }
}
```
The `vTaskDelay` function here is provided by FreeRTOS. It puts the current task in a blocked state and allows other tasks to run, achieving true multitasking.

> **Code Explanation**: Unlike traditional delay functions, `vTaskDelay` does not consume CPU resources. When a task calls this function, FreeRTOS puts the task in a blocked state and switches to other ready tasks to execute until the specified delay time is reached.

### 6. Configure the Debug Environment
To verify our program, we need to correctly configure the debug environment. Click the "Magic Wand" (Debug button) in the IDE, select "use Simulator", and set the debug parameters suitable for the STM32F103C8 chip:
- Dialog DLL: DARMSTM.DLL
- Parameter: -PSTM32F103C8

These settings tell the debugger to use the STM32 device simulator and specify the correct chip model, ensuring the simulation environment is consistent with the actual hardware.

![Configure Debug Environment](https://i-blog.csdnimg.cn/direct/b98362ff706f4be6a5af329ed011a8ad.png)

### 7. Start Debugging
After configuration, click the debug button to start the debugging process. At this point, the debugger will load the program into the virtual STM32 chip and prepare to execute.

![Start Debugging](https://i-blog.csdnimg.cn/direct/744beaaf32194e77ad01d3ac7095beab.png)

### 8. Open the Logic Analyzer
To visually observe the LED state changes, we need to open the logic analyzer tool in the IDE. The logic analyzer can display real-time changes in GPIO pin states, helping us confirm if the task is executing as expected.

![Open Logic Analyzer](https://i-blog.csdnimg.cn/direct/e26592b59cfe4ce79017144749d046be.png)

### 9. Configure the Logic Analyzer
Click the "Setup..." button in the upper left corner of the logic analyzer to start configuring the pins to monitor.

![Configure Logic Analyzer](https://i-blog.csdnimg.cn/direct/e8c109e28bcd49358c538f9e8ab61ad2.png)

### 10. Add Monitoring Variables
In the pop-up configuration window, add the GPIO pin you want to monitor. In this example, we're using pin PC13 (pin 13 of GPIOC), which is typically the control pin for the onboard LED of the STM32F103C8. Enter "portc.13" and click a blank space to confirm the addition.

![Add Monitoring Variables](https://i-blog.csdnimg.cn/direct/07f99b3b7a9b400fa2373377e90414e0.png)

### 12. Set the Display Type
Continue by clicking on the variable just added (PC13), change the display type to "bit" for a clearer view of the high and low level changes of the pin. After completing the settings, click "Close" to close the configuration window.

![Set Display Type](https://i-blog.csdnimg.cn/direct/8a8657129a004159a7b5ff3a24f137ce.png)

### 13. Run the Program
After configuration, click the "Run" button to start running the program. At this point, the FreeRTOS scheduler will start and begin executing our LED blinking task.

![Run Program](https://i-blog.csdnimg.cn/direct/bc4fc56263524915ac23d434c770e853.png)

### 14. Observe the Results
If everything is normal, we should be able to observe the PC13 pin's level state changing periodically at 500ms intervals in the logic analyzer, indicating that our FreeRTOS task has been successfully created and is running normally. This also proves that our simple FreeRTOS program is running successfully.

![Observe Results](https://i-blog.csdnimg.cn/direct/4bf3362ad4a84d148d25f329296042e3.png)

## Common Problems and Solutions

### 1. Compilation Error: Function Redefinition
**Problem**: Function redefinition errors for PendSV_Handler, SVC_Handler, or SysTick_Handler during compilation.  
**Solution**: Check if the corresponding functions in `stm32f10x_it.c` are properly commented out.

### 2. LED Not Blinking
**Problem**: After running the program, the LED does not blink as expected.  
**Solution**:
- Check if the GPIO configuration is correct
- Confirm if the delay time is appropriate
- Check if the task was successfully created (can use task status viewing functions)

### 3. Stack Overflow
**Problem**: Stack overflow error during operation.  
**Solution**: Increase the task stack size, modify the stack parameter in `xTaskCreate` (the third parameter).

## Advanced Extensions

### Multi-task Example
Here is an example of creating two tasks, one controlling LED blinking and the other outputting information via UART:

```cpp
TaskHandle_t ledTaskHandler;
TaskHandle_t uartTaskHandler;

void ledTask(void *arg)
{
    while(1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        vTaskDelay(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        vTaskDelay(500);
    }
}

void uartTask(void *arg)
{
    while(1)
    {
        printf("FreeRTOS running...\r\n");
        vTaskDelay(1000);
    }
}

int main(void)
{
    // Initialize peripherals...
    
    // Create tasks
    xTaskCreate(ledTask, "LED", 128, NULL, 2, &ledTaskHandler);
    xTaskCreate(uartTask, "UART", 128, NULL, 1, &uartTaskHandler);
    
    // Start the scheduler
    vTaskStartScheduler();
    
    // Should not reach here under normal circumstances
    while(1);
}
```

## Summary
Through the above steps, we have successfully created a simple FreeRTOS program on the STM32 platform and verified the program's correct operation through an LED blinking task. FreeRTOS is a powerful real-time operating system that provides important functions such as multitasking, inter-task communication, and resource management for embedded development, greatly simplifying the development of complex embedded applications.

In future learning, we will further explore the advanced features of FreeRTOS, such as semaphores, message queues, task notifications, etc., to develop more complex and powerful embedded applications.

## More Resources

To learn FreeRTOS in depth, you can refer to the following resources:

1. [Complete Code on GitHub](https://github.com/Despacito0o/FreeRTOS.git)
2. [FreeRTOS Official Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
3. [STM32 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

## References
1. FreeRTOS Official Documentation: [https://www.freertos.org/Documentation/RTOS_book.html](https://www.freertos.org/Documentation/RTOS_book.html)
2. STM32 Standard Peripheral Library User Manual
3. FreeRTOS Source Code Analysis

---
If you have any questions, feel free to leave a message in the comments! You can also submit an Issue or Pull Request on GitHub to help improve this project. 