# FreeRTOS Task Parameters Example

This project demonstrates how to use FreeRTOS task parameters to make task functions more flexible and reusable. Through task parameters, we can pass different types of data to tasks, enabling a single task function to handle various operations.

## Overview

In this project, we create a simple system with three tasks all using the same task function, but each task behaves differently because it receives different parameters. This demonstrates code reuse and the power of FreeRTOS task parameters.

## Features

- Multiple tasks using a single task function
- Passing string parameters to tasks
- Using critical sections to protect shared resources
- Demonstration of proper task parameter usage patterns

## Hardware Requirements

- STM32F103 development board (any variant)
- UART connection for debug output

## Software Requirements

- Keil MDK v5 or above
- STM32 Standard Peripheral Library
- FreeRTOS V10.0.0 or above

## Project Structure

- Main task function that can be reused for different purposes
- Three tasks all using the same function but performing different operations
- UART output to demonstrate task execution

## Usage

1. Open the project in Keil MDK
2. Compile the project with no errors
3. Download to the STM32F103 development board
4. Monitor UART output to see different tasks printing different messages

## Key Concepts

This project demonstrates:

- How to pass parameters to FreeRTOS tasks
- Type casting between void pointers and specific types
- Critical section protection for shared resources
- Task creation with parameters

## Code Example

```c
// Define different task parameters
char str1[20] = "myTask1 running!";
char str2[20] = "myTask2 running!";
char str3[20] = "myTask3 running!";

// Reusable task function that works with parameters
void myPrintf(void *arg)
{
    char *str = arg;  // Cast void* to char*
    while(1)
    {
        taskENTER_CRITICAL();
        printf("%s\n", str);
        taskEXIT_CRITICAL();
        vTaskDelay(500);
    }
}

// Creating tasks with different parameters
xTaskCreate(myPrintf, "myTask1", 128, str1, 2, &myTaskHandler1);
xTaskCreate(myPrintf, "myTask2", 128, str2, 2, &myTaskHandler2);
xTaskCreate(myPrintf, "myTask3", 128, str3, 2, &myTaskHandler3);
```

## Further Learning

For more information on FreeRTOS task parameters and other features, please visit:
- [Complete FreeRTOS Learning Library](https://github.com/Despacito0o/FreeRTOS)
- [FreeRTOS Task Parameters Explained](https://blog.csdn.net/supershmily)

## Author

- [Despacito0o](https://github.com/Despacito0o) - Embedded Systems Developer 