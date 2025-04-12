# FreeRTOS项目工程完善指南 / FreeRTOS Project Improvement Guide

<div align="center">

[English](#english) | [中文](#中文)

</div>

---

## 中文

### 📖 项目简介

本项目在前面FreeRTOS示例的基础上，进行了功能扩展和完善，添加了串口通信、调试输出和更多实用功能，打造更加健壮和实用的嵌入式应用框架。

### ✨ 功能特点

- 完整的串口通信功能
- 重定向printf输出到串口
- 优化的FreeRTOS配置参数
- 任务监控和调试功能
- 多种通信外设示例

### 🔧 硬件要求

- 开发板：STM32F103C8T6
- 外设：
  - 板载LED（PC13）
  - USB-TTL串口转换器
- 调试器：ST-Link

### 🛠️ 开发环境

- IDE：Keil MDK 5.x / 6.x
- 编译器：ARM Compiler 5/6
- 库：
  - STM32标准外设库 (StdPeriph)
  - FreeRTOS V10.0.1

### 📂 项目结构

```
Despacito005/
├── Start/               # 启动文件
├── Library/             # 标准库文件
├── User/                # 用户代码
│   ├── usart.c/h        # 串口相关代码
│   └── main.c           # 主程序
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
4. 连接串口：
   - PC端使用串口调试助手，波特率115200
   - RX连接PA9，TX连接PA10
5. 观察结果：通过串口可以看到系统运行状态和调试信息

### 📝 代码示例

```c
// 初始化USART1
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    // 使能GPIO和USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置USART1 TX (PA.09) 为复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 配置USART1 RX (PA.10) 为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 配置USART1参数
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    
    // 使能USART1
    USART_Cmd(USART1, ENABLE);
}

// 重定向printf到串口
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}
```

### 📚 相关文档

- [FreeRTOS项目工程完善指南](../../docs/zh/005-FreeRTOS项目工程完善指南.md)

---

## English

### 📖 Project Description

This project extends and improves upon the previous FreeRTOS examples by adding UART communication, debug output, and more practical features to create a more robust and useful embedded application framework.

### ✨ Features

- Complete UART communication functionality
- Redirected printf output to UART
- Optimized FreeRTOS configuration parameters
- Task monitoring and debugging capabilities
- Multiple communication peripheral examples

### 🔧 Hardware Requirements

- Development Board: STM32F103C8T6
- Peripherals:
  - Onboard LED (PC13)
  - USB-TTL UART converter
- Debugger: ST-Link

### 🛠️ Development Environment

- IDE: Keil MDK 5.x / 6.x
- Compiler: ARM Compiler 5/6
- Libraries:
  - STM32 Standard Peripheral Library (StdPeriph)
  - FreeRTOS V10.0.1

### 📂 Project Structure

```
Despacito005/
├── Start/               # Startup files
├── Library/             # Standard library files
├── User/                # User code
│   ├── usart.c/h        # UART related code
│   └── main.c           # Main program
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
4. Connect UART:
   - Use a serial terminal on PC, baudrate 115200
   - RX connects to PA9, TX connects to PA10
5. Observe result: View system status and debug information through the serial port

### 📝 Code Example

```c
// Initialize USART1
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    // Enable GPIO and USART1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
    
    // Configure USART1 TX (PA.09) as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Configure USART1 RX (PA.10) as input floating
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Configure USART1 parameters
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    
    // Enable USART1
    USART_Cmd(USART1, ENABLE);
}

// Redirect printf to UART
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}
```

### 📚 Related Documentation

- [FreeRTOS Project Improvement Guide](../../docs/en/005-FreeRTOS-Project-Improvement-Guide.md) 