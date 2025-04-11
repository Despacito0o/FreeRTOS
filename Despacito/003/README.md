# FreeRTOS动态任务创建 / FreeRTOS Dynamic Task Creation

<div align="center">

[English](#english) | [中文](#中文)

</div>

---

## 中文

### 📖 项目简介

本项目演示了FreeRTOS中动态任务创建的方法和基本原理，通过多个LED控制任务展示任务调度功能。

### ✨ 功能特点

- 动态内存分配创建FreeRTOS任务
- 多任务并行执行示例
- 任务优先级调度演示
- 任务间通信基础

### 🔧 硬件要求

- 开发板：STM32F103C8T6
- 外设：板载LED（PC13）及外接LED
- 调试器：ST-Link

### 🛠️ 开发环境

- IDE：Keil MDK 5.x / 6.x
- 编译器：ARM Compiler 5/6
- 库：
  - STM32标准外设库 (StdPeriph)
  - FreeRTOS V10.0.1

### 📂 项目结构

```
Despacito003/
├── Start/               # 启动文件
├── Library/             # 标准库文件
├── User/                # 用户代码
├── FreeRTOS/            # FreeRTOS源码
│   ├── inc/             # FreeRTOS头文件
│   ├── src/             # FreeRTOS源文件
│   └── port/            # 移植文件
├── Objects/             # 编译生成的目标文件
└── Listings/            # 编译生成的列表文件
```

### 🚀 使用方法

1. 打开项目：使用Keil MDK打开项目文件
2. 编译项目：点击"Build"按钮
3. 下载程序：连接ST-Link，点击"Download"按钮将程序下载到开发板
4. 观察结果：多个LED将以不同频率闪烁，展示多任务并行执行

### 📝 代码示例

```c
// 动态创建LED任务
xTaskCreate((TaskFunction_t )led_task,          // 任务函数
            (const char*    )"led_task",        // 任务名称
            (uint16_t       )128,               // 任务堆栈大小
            (void*          )NULL,              // 传递给任务的参数
            (UBaseType_t    )3,                 // 任务优先级
            (TaskHandle_t*  )&LEDTask_Handler); // 任务句柄
```

### 📚 相关文档

- [FreeRTOS动态任务创建](../../docs/zh/003-FreeRTOS动态任务创建.md)

---

## English

### 📖 Project Description

This project demonstrates the methods and basic principles of dynamic task creation in FreeRTOS, showcasing task scheduling functionality through multiple LED control tasks.

### ✨ Features

- FreeRTOS task creation using dynamic memory allocation
- Multi-task parallel execution example
- Task priority scheduling demonstration
- Basic inter-task communication

### 🔧 Hardware Requirements

- Development Board: STM32F103C8T6
- Peripherals: Onboard LED (PC13) and external LEDs
- Debugger: ST-Link

### 🛠️ Development Environment

- IDE: Keil MDK 5.x / 6.x
- Compiler: ARM Compiler 5/6
- Libraries:
  - STM32 Standard Peripheral Library (StdPeriph)
  - FreeRTOS V10.0.1

### 📂 Project Structure

```
Despacito003/
├── Start/               # Startup files
├── Library/             # Standard library files
├── User/                # User code
├── FreeRTOS/            # FreeRTOS source code
│   ├── inc/             # FreeRTOS header files
│   ├── src/             # FreeRTOS source files
│   └── port/            # Port files
├── Objects/             # Compiled object files
└── Listings/            # Compiled listing files
```

### 🚀 Usage

1. Open project: Use Keil MDK to open the project file
2. Compile project: Click the "Build" button
3. Download program: Connect ST-Link, click the "Download" button to download the program to the development board
4. Observe result: Multiple LEDs will blink at different frequencies, demonstrating parallel task execution

### 📝 Code Example

```c
// Dynamically create LED task
xTaskCreate((TaskFunction_t )led_task,          // Task function
            (const char*    )"led_task",        // Task name
            (uint16_t       )128,               // Task stack size
            (void*          )NULL,              // Parameters passed to the task
            (UBaseType_t    )3,                 // Task priority
            (TaskHandle_t*  )&LEDTask_Handler); // Task handle
```

### 📚 Related Documentation

- [FreeRTOS Dynamic Task Creation](../../docs/en/003-FreeRTOS-Dynamic-Task-Creation.md)

## License

This project is licensed under the MIT License - see the [LICENSE](../../LICENSE) file for details. 