# FreeRTOS 学习资源文档索引

<div align="center">
<img src="https://www.freertos.org/fr-content-src/uploads/2018/07/logo-1.jpg" width="300">
</div>

## 📚 文档概览

欢迎访问FreeRTOS学习资源文档！这里提供了从入门到精通的系统化教程和指南，帮助您高效学习嵌入式RTOS开发。

我们的文档遵循渐进式学习路径，让您能够循序渐进地掌握FreeRTOS的核心概念和实际应用技术。

## 🗂️ 文档分类

### 📖 英文文档 (English Documentation)

#### 基础入门 (Getting Started)
* **[001-STM32 Development Environment Setup](en/001-STM32-Development-Environment-Setup.md)** - STM32开发环境配置
* **[002-FreeRTOS Port to Keil6](en/002-FreeRTOS-Port-to-Keil6.md)** - FreeRTOS在Keil6中的移植

#### 核心概念 (Core Concepts)
* **[003-FreeRTOS Dynamic Task Creation](en/003-FreeRTOS-Dynamic-Task-Creation.md)** - 动态任务创建
* **[004-FreeRTOS Static Task Creation](en/004-FreeRTOS-Static-Task-Creation.md)** - 静态任务创建
* **[005-FreeRTOS Project Improvement Guide](en/005-FreeRTOS-Project-Improvement-Guide.md)** - 项目改进指南

#### 高级主题 (Advanced Topics)
* **[006-FreeRTOS Multi-Task Management](en/006-FreeRTOS-Multi-Task-Management.md)** - 多任务管理
* **[007-FreeRTOS Task Parameters](en/007-FreeRTOS-Task-Parameters.md)** - 任务参数
* **[008-FreeRTOS Queue Communication](en/008-FreeRTOS-Queue-Communication.md)** - 队列通信
* **[009-FreeRTOS Advanced Queue Operations](en/009-FreeRTOS-Queue-Advanced-Operations.md)** - 高级队列操作
* **[010-FreeRTOS Binary Semaphore](en/010-FreeRTOS-Binary-Semaphore.md)** - 二值信号量
* **[011-FreeRTOS Counting Semaphore](en/011-FreeRTOS-Counting-Semaphore.md)** - 计数型信号量

#### 实用教程 (Practical Tutorials)
* **[Creating a Simple FreeRTOS Project on STM32](en/tutorials/Creating-Simple-FreeRTOS-Project-on-STM32.md)** - 在STM32上创建简单FreeRTOS项目

### 📖 中文文档 (Chinese Documentation)

#### 基础入门
* **[001-STM32标准库开发环境搭建教程](zh/001-STM32标准库开发环境搭建教程.md)** - STM32开发环境配置
* **[002-FreeRTOS移植到keil6](zh/002-FreeRTOS移植到keil6.md)** - FreeRTOS在Keil6中的移植

#### 核心概念
* **[003-FreeRTOS动态任务创建](zh/003-FreeRTOS动态任务创建.md)** - 动态任务创建
* **[004-FreeRTOS静态任务创建](zh/004-FreeRTOS静态任务创建.md)** - 静态任务创建
* **[005-FreeRTOS项目工程完善指南](zh/005-FreeRTOS项目工程完善指南.md)** - 项目改进指南

#### 高级主题
* **[006-FreeRTOS多任务管理](zh/006-FreeRTOS多任务管理.md)** - 多任务管理
* **[007-FreeRTOS任务参数](zh/007-FreeRTOS任务参数.md)** - 任务参数
* **[008-FreeRTOS队列通信](zh/008-FreeRTOS队列通信.md)** - 队列通信
* **[009-FreeRTOS队列高级操作](zh/009-FreeRTOS队列高级操作.md)** - 高级队列操作
* **[010-FreeRTOS二值信号量详解与实战教程](zh/010-FreeRTOS二值信号量详解与实战教程.md)** - 二值信号量与同步控制
* **[011-FreeRTOS计数型信号量详解与实战教程](zh/011-FreeRTOS计数型信号量详解与实战教程.md)** - 计数型信号量与资源管理

#### 实用教程
* **[STM32上创建简单FreeRTOS程序详解](zh/tutorials/STM32上创建简单FreeRTOS程序详解.md)** - 在STM32上创建简单FreeRTOS项目

## 🗺️ 学习路径

推荐的学习路径如下：

1. **环境设置** - 首先设置开发环境并完成基本移植 (001-002)
2. **任务基础** - 学习任务创建和内存管理模型 (003-004)
3. **项目完善** - 添加调试功能和提升项目质量 (005)
4. **高级任务管理** - 掌握任务生命周期管理和参数传递 (006-007)
5. **任务间通信** - 学习队列通信和高级数据传输技术 (008-009)
6. **任务同步机制** - 掌握二值信号量和计数信号量实现任务同步和资源管理 (010-011)

每个文档都配有相应的示例项目，位于仓库的`Despacito/`目录下。

## 🔄 最近更新

* 添加了FreeRTOS计数型信号量详解与实战教程文档和示例 (011)
* 添加了FreeRTOS二值信号量详解与实战教程文档和示例 (010)
* 添加了FreeRTOS队列高级操作文档和示例 (009)
* 更新了队列通信示例 (008)

## 📝 贡献文档

欢迎贡献新的文档或改进现有内容！请参阅[贡献指南](../CONTRIBUTING.md)了解更多信息。

---

<div align="center">

[返回主页](../README.md) | [English](README.md) | [中文](README_zh.md)

</div> 