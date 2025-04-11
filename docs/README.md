# FreeRTOS 文档目录 / FreeRTOS Documentation Directory

<div align="center">

[English](#english-documentation) | [中文](#中文文档)

</div>

---

## 中文文档

本目录包含了有关FreeRTOS嵌入式系统开发的文档资料。您可以根据自己的需求选择相应的文档阅读。

### 📚 核心文档

- [STM32标准库开发环境搭建教程](zh/STM32标准库开发环境搭建教程.md) - 详细介绍如何设置STM32开发环境
- [FreeRTOS移植详解](zh/FreeRTOS移植详解.md) - 介绍如何将FreeRTOS移植到STM32平台
- [FreeRTOS移植详解-003](zh/FreeRTOS移植详解-003.md) - 基于STM32F103的FreeRTOS移植实践
- [FreeRTOS工程完善指南](zh/FreeRTOS工程完善指南.md) - 添加串口功能并优化FreeRTOS配置

### 💡 教程

- [STM32上创建简单FreeRTOS程序详解](zh/tutorials/STM32上创建简单FreeRTOS程序详解.md) - 从零开始创建FreeRTOS程序

---

## English Documentation

This directory contains documentation about FreeRTOS embedded system development. You can choose the appropriate document based on your needs.

### 📚 Core Documentation

- [STM32 Development Environment Setup](en/STM32-Dev-Environment-Setup.md) - Detailed guide on setting up STM32 development environment
- [FreeRTOS Porting Guide](en/FreeRTOS-Port-Guide.md) - Guide on porting FreeRTOS to STM32 platform
- [Creating a Simple FreeRTOS Project on STM32](en/Creating-Simple-FreeRTOS-Project-on-STM32.md) - Creating a FreeRTOS project from scratch on STM32
- [FreeRTOS Project Improvement Guide](en/FreeRTOS-Project-Improvement-Guide.md) - Adding UART functionality and optimizing FreeRTOS configuration

### 💡 Tutorials

- *Coming soon*

---

## 文档结构 / Directory Structure

```
docs/
├── README.md                  # 本文件 / This file
├── en/                        # 英文文档 / English documentation
│   ├── FreeRTOS-Port-Guide.md
│   ├── STM32-Dev-Environment-Setup.md
│   ├── Creating-Simple-FreeRTOS-Project-on-STM32.md
│   ├── FreeRTOS-Project-Improvement-Guide.md
│   └── tutorials/             # 英文教程 / English tutorials
│       └── ...
└── zh/                        # 中文文档 / Chinese documentation
    ├── FreeRTOS移植详解.md
    ├── STM32标准库开发环境搭建教程.md
    ├── FreeRTOS移植详解-003.md
    ├── FreeRTOS工程完善指南.md
    └── tutorials/             # 中文教程 / Chinese tutorials
        └── STM32上创建简单FreeRTOS程序详解.md
``` 