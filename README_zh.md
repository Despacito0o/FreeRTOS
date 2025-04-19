# FreeRTOS 嵌入式开发学习库

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

## 📚 项目概述

这是一个专注于STM32微控制器上的FreeRTOS开发的综合学习资源。本仓库提供了循序渐进的教程、功能完整的示例项目和详细的指南，帮助您掌握嵌入式RTOS开发。

**适合人群：**
- 🎓 嵌入式系统初学者
- 🔄 正在转向基于RTOS的应用开发的开发者
- 🛠️ 寻找实用STM32+FreeRTOS示例的工程师
- 📝 从事学术项目的学生

### 🌟 主要特点

- 📖 从基础到高级的详细FreeRTOS移植教程
- 🔧 完整的STM32开发环境搭建指南和故障排除提示
- 💡 渐进式学习路径和实用示例项目
- 🔄 RTOS概念的实际演示（任务、队列、信号量等）
- 📝 中英双语的清晰文档
- 🔍 常见问题解决方案和调试技巧

---

## 📋 项目结构

```
FreeRTOS/
├── docs/                     # 文档
│   ├── README.md             # 文档索引
│   ├── en/                   # 英文文档
│   │   ├── 001-STM32-Development-Environment-Setup.md
│   │   ├── 002-FreeRTOS-Port-to-Keil6.md
│   │   ├── 003-FreeRTOS-Dynamic-Task-Creation.md
│   │   ├── 004-FreeRTOS-Static-Task-Creation.md
│   │   ├── 005-FreeRTOS-Project-Improvement-Guide.md
│   │   └── tutorials/        # 英文教程
│   └── zh/                   # 中文文档
│       ├── 001-STM32标准库开发环境搭建教程.md
│       ├── 002-FreeRTOS移植到keil6.md
│       ├── 003-FreeRTOS动态任务创建.md
│       ├── 004-FreeRTOS静态任务创建.md
│       ├── 005-FreeRTOS项目工程完善指南.md
│       ├── 010-FreeRTOS二值信号量详解与实战教程.md
│       ├── 011-FreeRTOS计数型信号量详解与实战教程.md
│       └── tutorials/        # 中文教程
├── Despacito/                # STM32F103示例项目
│   ├── 001/                  # STM32项目模板
│   ├── 002/                  # FreeRTOS基础示例
│   ├── 003/                  # FreeRTOS动态任务创建
│   ├── 004/                  # FreeRTOS静态任务创建
│   ├── 005/                  # FreeRTOS工程完善（串口+配置优化）
│   ├── 006/                  # FreeRTOS多任务创建与删除
│   ├── 007/                  # FreeRTOS任务参数示例
│   ├── 008/                  # FreeRTOS队列通信示例
│   ├── 009/                  # FreeRTOS队列高级操作
│   ├── 010/                  # FreeRTOS二值信号量示例
│   └── 011/                  # FreeRTOS计数型信号量示例
├── templates/                # 项目模板
│   └── README_template.md    # 示例项目README模板
├── CONTRIBUTING.md           # 贡献指南
├── CHANGELOG.md              # 版本历史
├── LICENSE                   # MIT许可证
└── README.md/README_zh.md    # 项目文档
```

---

## 🚀 快速开始

### 1. **克隆仓库**
```bash
git clone https://github.com/Despacito0o/FreeRTOS.git
cd FreeRTOS
```

### 2. **按学习路径进行**
本仓库按循序渐进的学习旅程组织：

| 级别 | 项目 | 重点 | 获得的技能 |
|-------|----------|-------|--------------|
| 初级 | 001-002 | 环境搭建，FreeRTOS基础 | 开发环境设置，基本概念 |
| 中级 | 003-006 | 任务管理，内存模型 | 任务创建/删除，内存优化 |
| 高级 | 007-011 | 任务间通信与同步 | 参数传递，队列，信号量，资源管理 |

### 3. **探索示例项目**
每个示例都在前一个基础上构建，并添加新技能：

- **[001] STM32项目模板** - STM32开发的起点
- **[002] FreeRTOS基础示例** - FreeRTOS的第一步
- **[003] 动态任务创建** - 多任务处理
- **[004] 静态任务创建** - 内存优化的任务创建
- **[005] 项目完善** - 添加串口通信、调试功能
- **[006] 多任务操作** - 创建、删除和监控任务
- **[007] 任务参数** - 使用参数实现灵活的任务函数
- **[008] 队列通信** - 基本的任务间通信
- **[009] 队列高级操作** - 高效的数据传输技术
- **[010] 二值信号量** - 任务同步与互斥访问控制
- **[011] 计数型信号量** - 资源管理与事件计数

每个项目都包含完整源代码和详细的README文件，提供解释和使用说明。

---

## 📖 文档导航

### 📁 核心文档

浏览我们的综合指南：

- **[001]** [STM32标准库开发环境搭建教程](docs/zh/001-STM32标准库开发环境搭建教程.md)
- **[002]** [FreeRTOS移植到keil6](docs/zh/002-FreeRTOS移植到keil6.md)
- **[003]** [FreeRTOS动态任务创建](docs/zh/003-FreeRTOS动态任务创建.md)
- **[004]** [FreeRTOS静态任务创建](docs/zh/004-FreeRTOS静态任务创建.md)
- **[005]** [FreeRTOS项目工程完善指南](docs/zh/005-FreeRTOS项目工程完善指南.md)
- **[010]** [FreeRTOS二值信号量详解与实战教程](docs/zh/010-FreeRTOS二值信号量详解与实战教程.md)
- **[011]** [FreeRTOS计数型信号量详解与实战教程](docs/zh/011-FreeRTOS计数型信号量详解与实战教程.md)

### 📝 项目资源

- [文档索引](docs/README.md) - 导航所有可用文档
- [贡献指南](CONTRIBUTING.md) - 如何为项目做出贡献
- [变更日志](CHANGELOG.md) - 版本历史和最近更新

### 🧠 实用教程

- [STM32上创建简单FreeRTOS程序详解](docs/zh/tutorials/STM32上创建简单FreeRTOS程序详解.md)

---

## 🔍 示例项目详解

### 🟢 [001] STM32项目模板
一个干净、即用的STM32F103模板，包含标准外设库，是所有其他示例的基础。

### 🟢 [002] FreeRTOS基础示例
FreeRTOS的第一步 - 演示基本任务创建和LED闪烁等简单功能。

### 🟢 [003] 动态任务创建
学习FreeRTOS中任务如何动态创建和调度，包含任务优先级和调度的实际示例。

### 🟢 [004] 静态任务创建
探索任务创建的静态内存分配 - 对于内存受限的嵌入式系统至关重要，特别是在动态分配可能存在问题的情况下。

### 🟢 [005] 项目完善
通过串口通信、printf调试和优化配置提升项目水平 - 使开发更加便捷和高效。

### 🟢 [006] 多任务操作
掌握任务生命周期管理，包括动态创建和删除、优先级管理和状态监控技术。

### 🟢 [007] 任务参数
通过学习如何使用void指针传递参数，使任务更灵活和可重用 - 构建模块化RTOS应用的基本技能。

### 🟢 [008] 队列通信
使用队列实现可靠的任务间通信，包括简单消息传递和结构化数据传输的示例。

### 🟢 [009] 队列高级操作
探索高效的任务间数据传输高级技术，包括基于指针的方法和常见问题的解决方案。

### 🟢 [010] 二值信号量
掌握二值信号量的使用，实现任务同步和互斥资源访问，包括详细的信号量API解析和典型应用场景。

### 🟢 [011] 计数型信号量
学习使用计数型信号量进行资源池管理和事件计数，通过实例掌握高级同步场景的应用。

---

## 🤝 贡献

您的贡献使这个资源对所有人都更有价值！在提交拉取请求或问题之前，请阅读我们的[贡献指南](CONTRIBUTING.md)。

贡献方式：
- 📝 改进文档和解释
- 🐛 修复示例代码中的错误
- ✨ 添加新的示例或教程
- 🌍 帮助翻译
- 💡 提出改进建议

---

## 📄 许可证

本项目基于MIT许可证 - 详情请见 [LICENSE](LICENSE) 文件。

---

## 👨‍💻 作者与联系方式

- **[Despacito0o](https://github.com/Despacito0o)** - FreeRTOS开发者和教程创作者
- 访问我的 **[CSDN博客](https://blog.csdn.net/supershmily)** 获取更多嵌入式开发内容
- 有问题或建议？请创建issue或直接联系！

---

## 🙏 致谢

- FreeRTOS开发团队的优秀文档
- STMicroelectronics的全面外设库
- 所有为改进这个资源的贡献者和社区成员

---

<div align="center">
⭐ 如果您觉得这个项目有帮助，请给它点亮星标！ ⭐
</div> 