# FreeRTOS静态任务创建 / FreeRTOS Static Task Creation

<div align="center">

[English](#english) | [中文](#中文)

</div>

---

## 中文

### 📖 项目简介

本项目演示了FreeRTOS中静态任务创建的方法，使用预先分配的内存来创建任务，适用于资源受限和需要确定性内存使用的系统。

### ✨ 功能特点

- 静态内存分配创建FreeRTOS任务
- 使用静态任务堆栈和任务控制块
- 内存占用固定，无内存碎片问题
- 适合安全关键型应用

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
Despacito004/
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
4. 观察结果：LED将按预期模式闪烁，演示静态任务运行状态

### 📝 代码示例

```c
// 静态任务相关变量
static StaticTask_t xTaskBuffer;
static StackType_t xStack[128];

// 静态创建LED任务
TaskHandle_t LEDTask_Handler = xTaskCreateStatic(
                             (TaskFunction_t)led_task,     // 任务函数
                             (const char*)"led_task",      // 任务名称
                             (uint32_t)128,               // 任务堆栈大小
                             (void*)NULL,                 // 传递给任务的参数
                             (UBaseType_t)3,              // 任务优先级
                             (StackType_t*)xStack,        // 任务堆栈
                             (StaticTask_t*)&xTaskBuffer  // 任务控制块
                           );
```

### 📚 相关文档

- [FreeRTOS静态任务创建](../../docs/zh/004-FreeRTOS静态任务创建.md)

---

## English

### 📖 Project Description

This project demonstrates the method of static task creation in FreeRTOS, using pre-allocated memory to create tasks, suitable for resource-constrained systems and those requiring deterministic memory usage.

### ✨ Features

- FreeRTOS task creation using static memory allocation
- Using static task stacks and task control blocks
- Fixed memory footprint, no memory fragmentation issues
- Suitable for safety-critical applications

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
Despacito004/
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
4. Observe result: The LED will blink in the expected pattern, demonstrating static task operation

### 📝 Code Example

```c
// Static task related variables
static StaticTask_t xTaskBuffer;
static StackType_t xStack[128];

// Statically create LED task
TaskHandle_t LEDTask_Handler = xTaskCreateStatic(
                             (TaskFunction_t)led_task,     // Task function
                             (const char*)"led_task",      // Task name
                             (uint32_t)128,               // Task stack size
                             (void*)NULL,                 // Parameters passed to the task
                             (UBaseType_t)3,              // Task priority
                             (StackType_t*)xStack,        // Task stack
                             (StaticTask_t*)&xTaskBuffer  // Task control block
                           );
```

### 📚 Related Documentation

- [FreeRTOS Static Task Creation](../../docs/en/004-FreeRTOS-Static-Task-Creation.md) 