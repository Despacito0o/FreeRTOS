# FreeRTOS移植到STM32 / FreeRTOS Port to STM32

<div align="center">

[English](#english) | [中文](#中文)

</div>

---

## 中文

### 📖 项目简介

本项目展示了如何将FreeRTOS实时操作系统移植到STM32F103平台，并通过LED闪烁演示基本任务创建功能。

### ✨ 功能特点

- 完整的FreeRTOS移植示例
- 基于STM32标准库的GPIO控制
- 简单LED任务演示

### 🔧 硬件要求

- 开发板：STM32F103C8T6
- 外设：板载LED（PC13）
- 调试器：ST-Link

### 🛠️ 开发环境

- IDE：Keil MDK 5.x / 6.x
- 编译器：ARM Compiler 5/6
- 库：
  - STM32标准外设库 (StdPeriph)
  - FreeRTOS V10.0.1

### 📂 项目结构

```
Despacito002/
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
4. 观察结果：LED将以0.5秒的间隔闪烁，表示FreeRTOS任务正在运行

### 📝 代码示例

```c
// LED任务函数
void led_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED亮
        vTaskDelay(500);                     // 延时500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED灭
        vTaskDelay(500);                     // 延时500ms
    }
}
```

### 📚 相关文档

- [FreeRTOS移植到keil6](../../docs/zh/002-FreeRTOS移植到keil6.md)

---

## English

### 📖 Project Description

This project demonstrates how to port the FreeRTOS real-time operating system to the STM32F103 platform and showcases basic task creation functionality through LED blinking.

### ✨ Features

- Complete FreeRTOS porting example
- GPIO control based on STM32 standard library
- Simple LED task demonstration

### 🔧 Hardware Requirements

- Development Board: STM32F103C8T6
- Peripherals: Onboard LED (PC13)
- Debugger: ST-Link

### 🛠️ Development Environment

- IDE: Keil MDK 5.x / 6.x
- Compiler: ARM Compiler 5/6
- Libraries:
  - STM32 Standard Peripheral Library (StdPeriph)
  - FreeRTOS V10.0.1

### 📂 Project Structure

```
Despacito002/
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
4. Observe result: The LED will blink at 0.5-second intervals, indicating that the FreeRTOS task is running

### 📝 Code Example

```c
// LED task function
void led_task(void *pvParameters)
{
    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED on
        vTaskDelay(500);                     // Delay 500ms
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED off
        vTaskDelay(500);                     // Delay 500ms
    }
}
```

### 📚 Related Documentation

- [FreeRTOS Port to Keil6](../../docs/en/002-FreeRTOS-Port-to-Keil6.md) 