# STM32 标准库开发环境模板 / STM32 Standard Library Development Template

<div align="center">

[English](#english) | [中文](#中文)

</div>

---

## 中文

### 📖 项目简介

本项目是一个基于STM32F103系列的标准库开发环境模板，提供了开发STM32应用程序的基础框架。

### ✨ 功能特点

- 配置完整的STM32标准外设库环境
- 文件结构清晰，易于扩展
- 包含基本的GPIO配置示例

### 🔧 硬件要求

- 开发板：STM32F103C8T6
- 外设：板载LED（PC13）
- 调试器：ST-Link

### 🛠️ 开发环境

- IDE：Keil MDK 5.x / 6.x
- 编译器：ARM Compiler 5/6
- 库：STM32标准外设库 (StdPeriph)

### 📂 项目结构

```
Despacito001/
├── Start/               # 启动文件
├── Library/             # 标准库文件
├── User/                # 用户代码
├── Objects/             # 编译生成的目标文件
└── Listings/            # 编译生成的列表文件
```

### 🚀 使用方法

1. 打开项目：使用Keil MDK打开Despacito001.uvprojx文件
2. 编译项目：点击"Build"按钮
3. 下载程序：连接ST-Link，点击"Download"按钮将程序下载到开发板

### 📚 相关文档

- [STM32标准库开发环境搭建教程](../../docs/zh/001-STM32标准库开发环境搭建教程.md)

---

## English

### 📖 Project Description

This project is a development environment template based on STM32F103 series with standard peripheral library, providing a basic framework for developing STM32 applications.

### ✨ Features

- Complete STM32 standard peripheral library environment configuration
- Clear file structure, easy to extend
- Basic GPIO configuration example

### 🔧 Hardware Requirements

- Development Board: STM32F103C8T6
- Peripherals: Onboard LED (PC13)
- Debugger: ST-Link

### 🛠️ Development Environment

- IDE: Keil MDK 5.x / 6.x
- Compiler: ARM Compiler 5/6
- Libraries: STM32 Standard Peripheral Library (StdPeriph)

### 📂 Project Structure

```
Despacito001/
├── Start/               # Startup files
├── Library/             # Standard library files
├── User/                # User code
├── Objects/             # Compiled object files
└── Listings/            # Compiled listing files
```

### 🚀 Usage

1. Open project: Use Keil MDK to open Despacito001.uvprojx file
2. Compile project: Click the "Build" button
3. Download program: Connect ST-Link, click the "Download" button to download the program to the development board

### 📚 Related Documentation

- [STM32 Development Environment Setup](../../docs/en/001-STM32-Development-Environment-Setup.md) 