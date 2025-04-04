# FreeRTOS LED Blink Example for STM32F103

This project demonstrates a basic implementation of FreeRTOS on an STM32F103 microcontroller. It creates a simple task that blinks an LED connected to pin PC13 at a 500ms interval.

## Project Overview

This project serves as a minimal working example of FreeRTOS on STM32, showing:
- FreeRTOS task creation and scheduling
- LED control via GPIO
- FreeRTOS task delay for timing control

## Hardware Requirements

- STM32F103C8 development board (Blue Pill or similar)
- ST-Link V2 programmer (for hardware deployment)
- LED connected to PC13 (typically built into most STM32F103 boards)

## Software Requirements

- Keil MDK 5.x or higher
- STM32 Standard Peripheral Library
- FreeRTOS kernel files (included in project)

## Project Structure

- `/FreeRTOS` - Contains the FreeRTOS kernel source and port files
- `/Library` - STM32 Standard Peripheral Library
- `/Start` - Startup and system files
- `/User` - Application code including main.c

## Key Files

- `User/main.c` - Contains the application code with LED blink task
- `FreeRTOS/inc` - FreeRTOS header files
- `FreeRTOS/src` - FreeRTOS source files
- `FreeRTOS/port` - ARM Cortex-M3 port files

## How It Works

1. The system initializes the GPIO for the LED
2. A FreeRTOS task is created that controls the LED
3. The FreeRTOS scheduler is started
4. The task alternates the LED state with 500ms delays between transitions

## Key Code

```c
TaskHandle_t myTaskHandler;

void myTask(void *arg)
{
    while(1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED on
        vTaskDelay(500);                     // Delay 500 clock ticks
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED off
        vTaskDelay(500);                     // Delay 500 clock ticks
    }
}

int main(void)
{
    // Initialize GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    // Create FreeRTOS task
    xTaskCreate(myTask, "myTask", 128, NULL, 2, &myTaskHandler);
    
    // Start scheduler
    vTaskStartScheduler();
    
    // Should never reach here
    while(1);
}
```

## Building and Running

1. Open the project in Keil MDK
2. Build the project (F7 or Build button)
3. Connect your STM32 board via ST-Link
4. Flash the program (F8 or Load button)
5. The LED should start blinking with 500ms on/off intervals

## Simulation

If you don't have the hardware, you can simulate this project:

1. Open the project in Keil MDK
2. Click on the Magic Wand icon (Debug button)
3. Select "Use Simulator"
4. Set Dialog DLL to DARMSTM.DLL and Parameter to -PSTM32F103C8
5. Start debugging and open the Logic Analyzer
6. Add portc.13 as a monitoring variable
7. Set the display type to "bit"
8. Run the simulation and observe the LED state changes

## Further Documentation

For a detailed explanation of this project, see:
- [Creating a Simple FreeRTOS Project on STM32 (English)](../../docs/en/Creating-Simple-FreeRTOS-Project-on-STM32.md)
- [STM32上创建简单FreeRTOS程序详解 (Chinese)](../../docs/zh/FreeRTOS移植详解-003.md)

## License

This project is licensed under the MIT License - see the [LICENSE](../../LICENSE) file for details. 