# FreeRTOS Embedded Development Learning Library

<div align="center">

[![GitHub stars](https://img.shields.io/github/stars/Despacito0o/FreeRTOS.svg?style=social&label=Stars)](https://github.com/Despacito0o/FreeRTOS)
[![GitHub forks](https://img.shields.io/github/forks/Despacito0o/FreeRTOS.svg?style=social&label=Forks)](https://github.com/Despacito0o/FreeRTOS)
[![GitHub watchers](https://img.shields.io/github/watchers/Despacito0o/FreeRTOS.svg?style=social&label=Watchers)](https://github.com/Despacito0o/FreeRTOS)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Last Commit](https://img.shields.io/github/last-commit/Despacito0o/FreeRTOS)
![STM32](https://img.shields.io/badge/MCU-STM32-blue)
![FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS-brightgreen)

<p align="center">
  <img src="https://www.freertos.org/fr-content-src/uploads/2018/07/logo-1.jpg" width="400">
</p>

[English](README.md) | [中文](README_zh.md)

</div>

---

## 📚 Project Overview

A comprehensive learning resource for FreeRTOS on STM32 microcontrollers. This repository provides step-by-step tutorials, fully functional example projects, and detailed guides to help you master embedded RTOS development.

**Perfect for:**
- 🎓 Beginners learning embedded systems
- 🔄 Developers transitioning to RTOS-based applications
- 🛠️ Engineers seeking practical STM32+FreeRTOS examples
- 📝 Students working on academic projects

### 🌟 Key Features

- 📖 Detailed FreeRTOS porting tutorials from basics to advanced topics
- 🔧 Complete STM32 development environment setup guide with troubleshooting tips
- 💡 Progressive learning path with practical example projects
- 🔄 Real-world demonstrations of RTOS concepts (tasks, queues, semaphores, etc.)
- 📝 Clear documentation in both English and Chinese
- 🔍 Common problem solutions and debugging techniques

---

## 🚀 Quick Start

### 1. **Clone the repository**
```bash
git clone https://github.com/Despacito0o/FreeRTOS.git
cd FreeRTOS
```

### 2. **Follow the learning path**
This repository is organized as a progressive learning journey, from basics to advanced:

| Level | Project Numbers | Focus | Skills Gained |
|-------|----------|-------|--------------|
| Beginner | 001-002 | Environment setup, FreeRTOS basics | Development setup, Basic concepts |
| Intermediate | 003-006 | Task management, Memory models | Task creation/deletion, Memory optimization |
| Advanced | 007-012 | Inter-task communication and synchronization | Parameters, Queues, Semaphores, Resource management |

### 3. **Explore example projects**
Each example builds on previous concepts, gradually increasing complexity and functionality:

| Number | Example Project | Description | Key Skills |
|-------|----------|-------|--------------|
| 001 | STM32 Project Template | Starting point for STM32 development | Standard peripheral library setup |
| 002 | FreeRTOS Basic Example | First steps with FreeRTOS | Task creation and execution |
| 003 | Dynamic Task Creation | Basics of multitasking | Dynamic memory allocation |
| 004 | Static Task Creation | Memory-optimized task creation | Static memory allocation |
| 005 | Project Enhancement | Adding UART, debugging capabilities | Peripheral integration & debugging |
| 006 | Multi-Task Operations | Creating, deleting, and monitoring tasks | Task lifecycle management |
| 007 | Task Parameters | Flexible task functions with parameters | Parameter passing techniques |
| 008 | Queue Communication | Basic inter-task communication | Data sharing and transfer |
| 009 | Advanced Queue Operations | Efficient data transfer techniques | Structured data transfer |
| 010 | Binary Semaphores | Task synchronization and mutual exclusion | Resource protection & synchronization |
| 011 | Counting Semaphores | Resource management and event counting | Resource pool management |
| 012 | Priority Inversion | Understanding and solving priority inversion | System stability & real-time behavior |

---

## 📋 Project Structure

```
FreeRTOS/
├── docs/                     # Documentation
│   ├── README.md             # Documentation index
│   ├── en/                   # English documentation
│   │   ├── 001-STM32-Development-Environment-Setup.md
│   │   ├── 002-FreeRTOS-Port-to-Keil6.md
│   │   ├── ...
│   │   └── 012-FreeRTOS-Priority-Inversion-Tutorial.md
│   └── zh/                   # Chinese documentation
│       ├── 001-STM32标准库开发环境搭建教程.md
│       ├── 002-FreeRTOS移植到keil6.md
│       ├── ...
│       └── 012-FreeRTOS优先级翻转详解与实战教程.md
├── Despacito/                # STM32F103 example projects
│   ├── 001/                  # STM32 project template
│   ├── 002/                  # FreeRTOS basic example
│   ├── ...
│   └── 012/                  # FreeRTOS priority inversion example
├── templates/                # Project templates
│   └── README_template.md    # README template for examples
├── CONTRIBUTING.md           # Contribution guidelines
├── CHANGELOG.md              # Version history
├── LICENSE                   # MIT License
└── README.md/README_zh.md    # Project documentation
```

---

## 📖 Documentation Navigation

### 📁 Core Documentation

Browse our comprehensive guides following the learning path:

- **[001]** [STM32 Development Environment Setup](docs/en/001-STM32-Development-Environment-Setup.md)
- **[002]** [FreeRTOS Port to Keil6](docs/en/002-FreeRTOS-Port-to-Keil6.md)
- **[003]** [FreeRTOS Dynamic Task Creation](docs/en/003-FreeRTOS-Dynamic-Task-Creation.md)
- **[004]** [FreeRTOS Static Task Creation](docs/en/004-FreeRTOS-Static-Task-Creation.md)
- **[005]** [FreeRTOS Project Improvement Guide](docs/en/005-FreeRTOS-Project-Improvement-Guide.md)
- **[010]** [FreeRTOS Binary Semaphore Tutorial (Chinese)](docs/zh/010-FreeRTOS二值信号量详解与实战教程.md)
- **[011]** [FreeRTOS Counting Semaphore Tutorial (Chinese)](docs/zh/011-FreeRTOS计数型信号量详解与实战教程.md)
- **[012]** [FreeRTOS Priority Inversion Tutorial](docs/en/012-FreeRTOS-Priority-Inversion-Tutorial.md)

### 📝 Project Resources

- [Documentation Index](docs/README.md) - Navigate all available documentation
- [Contribution Guidelines](CONTRIBUTING.md) - How to contribute to this project
- [Change Log](CHANGELOG.md) - Version history and recent updates

---

## 🔍 Example Projects in Detail

### 🟢 Beginner Stage (Projects 001-002)

#### [001] STM32 Project Template
A clean, ready-to-use STM32F103 template with standard peripheral library, providing the foundation for all other examples.

#### [002] FreeRTOS Basic Example
Your first steps with FreeRTOS - demonstrates basic task creation and simple functionality with LED blinking.

### 🟠 Intermediate Stage (Projects 003-006)

#### [003] Dynamic Task Creation
Learn how tasks are dynamically created and scheduled in FreeRTOS, with practical examples of task priorities and scheduling.

#### [004] Static Task Creation
Explore static memory allocation for task creation - crucial for memory-constrained embedded systems.

#### [005] Project Enhancement
Take your project to the next level with UART communication, printf debugging, and optimized configurations - making development easier and more productive.

#### [006] Multi-Task Operations
Master task lifecycle management with dynamic creation and deletion, priority management, and state monitoring techniques.

### 🔴 Advanced Stage (Projects 007-012)

#### [007] Task Parameters
Make your tasks flexible and reusable by learning how to pass parameters using void pointers.

#### [008] Queue Communication
Implement reliable inter-task communication using queues, with examples of both simple message passing and structured data transmission.

#### [009] Advanced Queue Operations
Explore advanced techniques for efficient data transfer between tasks, including pointer-based methods and solutions for common pitfalls.

#### [010] Binary Semaphores
Master the use of binary semaphores for task synchronization and mutual exclusion.

#### [011] Counting Semaphores
Learn to use counting semaphores for resource pool management and event counting, with practical examples for advanced synchronization scenarios.

#### [012] Priority Inversion
Understand the priority inversion problem in real-time systems, its causes, and how to solve it using priority inheritance and mutexes.

---

## 🤝 Contributing

Your contributions make this resource better for everyone! Please read our [Contribution Guidelines](CONTRIBUTING.md) before submitting pull requests or issues.

Ways to contribute:
- 📝 Improve documentation and explanations
- 🐛 Fix bugs in example code
- ✨ Add new examples or tutorials
- 🌍 Help with translations
- 💡 Suggest improvements or enhancements

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author & Contact

- **[Despacito0o](https://github.com/Despacito0o)** - FreeRTOS developer and tutorial creator
- Visit my **[CSDN Blog](https://blog.csdn.net/supershmily)** for more embedded development content
- Questions or suggestions? Open an issue or reach out directly!

---

## 🙏 Acknowledgments

- The FreeRTOS development team for their excellent documentation
- STMicroelectronics for their comprehensive peripheral libraries
- All contributors and community members who have improved this resource

---

<div align="center">
⭐ If you found this helpful, please star the repository! ⭐
</div>

# FreeRTOS优先级翻转实战教程：从代码到现象分析

## 前言

在实时操作系统中，优先级翻转是一个常见但又容易被忽视的问题。本文将通过实际代码演示优先级翻转现象，帮助大家深入理解这一概念。如果你对FreeRTOS有兴趣，可以访问我的完整学习资源：[FreeRTOS学习库](https://github.com/Despacito0o/FreeRTOS)，从入门到精通的全面指南！

## 什么是优先级翻转？

优先级翻转是指高优先级任务被低优先级任务间接阻塞的现象。具体场景如下：
- 低优先级任务获取了某个共享资源
- 高优先级任务尝试获取同一资源，但因资源被占用而阻塞
- 中优先级任务此时可以抢占低优先级任务执行
- 结果：中优先级任务先于高优先级任务执行，违背了优先级调度原则

## 实战演示：创建优先级翻转场景

我们将创建三个任务，优先级依次为：
- Task1：低优先级（优先级2）
- Task2：中优先级（优先级3）
- Task3：高优先级（优先级4）

其中Task1和Task3需要共享同一个二值信号量，而Task2不使用该信号量。

### 1. 拷贝工程模板

首先，我们基于之前的二值信号量示例（010）创建新工程（012）。

![工程创建](https://i-blog.csdnimg.cn/direct/94a303792701484b8929c9ec25fee1c4.png)

### 2. 添加延时函数

为模拟任务执行时间，我们需要添加非阻塞的延时函数。创建`delay.c`和`delay.h`文件：

![添加delay.h](https://i-blog.csdnimg.cn/direct/9d92df2fa00b4b1aa5d82c80532edabf.png)
![添加delay.c](https://i-blog.csdnimg.cn/direct/d8e65c3537fc41b59d77ed5c96b6a4c9.png)

delay.h代码内容：
```c
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"                  // Device header


void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif
```

delay.c代码内容：
```c
#include "stm32f10x.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
```