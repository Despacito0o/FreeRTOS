# FreeRTOS 文档目录 / FreeRTOS Documentation Directory

<div align="center">

[English](#english-documentation) | [中文](#中文文档)

</div>

---

## 中文文档

本目录包含了有关FreeRTOS嵌入式系统开发的文档资料。您可以根据自己的需求选择相应的文档阅读。

### 📚 核心文档

- [001-STM32标准库开发环境搭建教程](zh/001-STM32标准库开发环境搭建教程.md) - 详细介绍如何设置STM32开发环境
- [002-FreeRTOS移植到keil6](zh/002-FreeRTOS移植到keil6.md) - 介绍如何将FreeRTOS移植到STM32平台
- [003-FreeRTOS动态任务创建](zh/003-FreeRTOS动态任务创建.md) - 基于STM32F103的FreeRTOS动态任务创建
- [004-FreeRTOS静态任务创建](zh/004-FreeRTOS静态任务创建.md) - 使用静态内存分配方式创建FreeRTOS任务
- [005-FreeRTOS项目工程完善指南](zh/005-FreeRTOS项目工程完善指南.md) - 完善FreeRTOS工程，添加串口和优化配置

### 💡 教程

- [STM32上创建简单FreeRTOS程序详解](zh/tutorials/STM32上创建简单FreeRTOS程序详解.md) - 从零开始创建FreeRTOS程序

---

## English Documentation

This directory contains documentation about FreeRTOS embedded system development. You can choose the appropriate document based on your needs.

### 📚 Core Documentation

- [001-STM32 Development Environment Setup](en/001-STM32-Development-Environment-Setup.md) - Detailed guide on setting up STM32 development environment
- [002-FreeRTOS Port to Keil6](en/002-FreeRTOS-Port-to-Keil6.md) - Guide on porting FreeRTOS to STM32 platform
- [003-FreeRTOS Dynamic Task Creation](en/003-FreeRTOS-Dynamic-Task-Creation.md) - Creating dynamic tasks in FreeRTOS
- [004-FreeRTOS Static Task Creation](en/004-FreeRTOS-Static-Task-Creation.md) - Creating tasks using static memory allocation
- [005-FreeRTOS Project Improvement Guide](en/005-FreeRTOS-Project-Improvement-Guide.md) - Improving FreeRTOS projects with UART and optimized configurations

### 💡 Tutorials

- *Coming soon*

---

## 文档结构 / Directory Structure

```
docs/
├── README.md                  # 本文件 / This file
├── en/                        # 英文文档 / English documentation
│   ├── 001-STM32-Development-Environment-Setup.md
│   ├── 002-FreeRTOS-Port-to-Keil6.md
│   ├── 003-FreeRTOS-Dynamic-Task-Creation.md
│   ├── 004-FreeRTOS-Static-Task-Creation.md
│   ├── 005-FreeRTOS-Project-Improvement-Guide.md
│   └── tutorials/             # 英文教程 / English tutorials
│       └── ...
└── zh/                        # 中文文档 / Chinese documentation
    ├── 001-STM32标准库开发环境搭建教程.md
    ├── 002-FreeRTOS移植到keil6.md
    ├── 003-FreeRTOS动态任务创建.md
    ├── 004-FreeRTOS静态任务创建.md
    ├── 005-FreeRTOS项目工程完善指南.md
    └── tutorials/             # 中文教程 / Chinese tutorials
        └── STM32上创建简单FreeRTOS程序详解.md
``` 