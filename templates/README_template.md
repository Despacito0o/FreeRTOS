# [项目名称] - FreeRTOS示例项目

<div align="center">

![Project Status: Active](https://img.shields.io/badge/Project%20Status-Active-green)
![MCU](https://img.shields.io/badge/MCU-STM32F103-blue)
![IDE](https://img.shields.io/badge/IDE-Keil%20MDK-lightgrey)
![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-brightgreen)

<img src="./project_image.png" alt="项目图片" width="400">
</div>

## 📋 项目概述

简洁明了地描述本示例项目的主要功能和目的。解释这个项目展示了哪些FreeRTOS的关键概念，以及读者能从中学到什么。

### 🎯 学习目标

- 学习目标1：例如了解FreeRTOS任务创建
- 学习目标2：例如掌握队列通信机制
- 学习目标3：例如实践参数传递方法

### 📔 先决条件

- STM32F103系列开发板
- Keil MDK开发环境 (推荐v5.25以上)
- ST-Link调试器
- 基本的嵌入式C编程知识
- [可选] 串口调试工具

## ⚙️ 硬件连接

详细说明项目所需的硬件连接方式：

| 引脚 | 功能 | 连接 |
|-----|------|------|
| PA9 | USART1_TX | USB转串口RX |
| PA10 | USART1_RX | USB转串口TX |
| PC13 | LED | 板载LED |
| ... | ... | ... |

<div align="center">
  <img src="./connection_diagram.png" alt="连接图" width="60%">
</div>

## 🚀 快速开始

### 编译和下载

1. 使用Keil MDK打开项目文件 `Project.uvprojx`
2. 编译项目（F7或点击Build按钮）
3. 连接开发板和ST-Link
4. 下载程序到开发板（F8或点击Download按钮）

### 查看运行结果

1. 打开串口调试工具（波特率：115200，数据位：8，停止位：1，校验：无）
2. 复位开发板，观察串口输出
3. 预期可以看到以下输出：
   ```
   System initialized...
   FreeRTOS Kernel starting...
   Task1 running...
   Task2 running...
   ...
   ```

## 📝 代码结构

```
项目根目录/
├── FreeRTOS/              # FreeRTOS内核文件
├── Driver/                # 驱动文件
│   └── usart/             # 串口驱动
├── User/                  # 用户代码
│   ├── main.c             # 主程序
│   ├── stm32f10x_it.c     # 中断处理
│   └── ...
└── ...
```

## 💡 核心代码讲解

### 1. 任务创建

```c
/* 创建任务示例 */
xTaskCreate(
    vTask1,                /* 任务函数 */
    "Task1",               /* 任务名称 */
    configMINIMAL_STACK_SIZE, /* 任务栈大小 */
    NULL,                  /* 任务参数 */
    1,                     /* 任务优先级 */
    &xTask1Handle);        /* 任务句柄 */
```

这段代码展示了如何创建一个FreeRTOS任务。`xTaskCreate`函数是FreeRTOS提供的API，用于动态创建任务。

### 2. 关键功能

此处讲解项目中最重要的代码片段，解释它们如何工作以及为何这样设计。包括：

- 初始化过程
- 任务函数实现
- 通信机制
- 特殊技巧

## 🔄 关键流程

描述系统的整体工作流程，可以使用流程图：

```
初始化硬件 → 创建任务 → 启动调度器 → 任务1执行 → 任务2执行 → ...
```

## 📚 学习要点

1. **要点1**：例如任务优先级影响调度顺序
2. **要点2**：例如队列阻塞机制的影响
3. **要点3**：例如内存管理策略的选择

## 🧪 实验变体

尝试以下修改来更深入理解概念：

1. 修改任务优先级，观察执行顺序变化
2. 更改队列长度，测试不同阻塞场景
3. 添加新任务，实现更复杂的功能

## 📌 常见问题

1. **问题**: 程序无法编译？  
   **解答**: 检查包含路径是否正确设置，确保所有源文件都已添加到项目中。

2. **问题**: 串口没有输出？  
   **解答**: 确认波特率设置，检查TX/RX连接是否正确。

## 📚 延伸阅读

- [FreeRTOS官方文档](https://www.freertos.org/Documentation/RTOS_book.html)
- [STM32参考手册](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- 相关示例项目：[项目链接]

## 🤝 贡献

欢迎提交问题和改进建议！请查看[贡献指南](../../CONTRIBUTING.md)了解更多信息。

---

<div align="center">

[返回主页](../../README.md) | [English](./README.md) | [中文](./README_zh.md)

</div> 