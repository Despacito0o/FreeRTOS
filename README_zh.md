# FreeRTOS 嵌入式开发学习库

<div align="center">

[![GitHub stars](https://img.shields.io/github/stars/Despacito0o/FreeRTOS.svg?style=social&label=Stars)](https://github.com/Despacito0o/FreeRTOS)
[![GitHub forks](https://img.shields.io/github/forks/Despacito0o/FreeRTOS.svg?style=social&label=Forks)](https://github.com/Despacito0o/FreeRTOS)
[![GitHub watchers](https://img.shields.io/github/watchers/Despacito0o/FreeRTOS.svg?style=social&label=Watchers)](https://github.com/Despacito0o/FreeRTOS)

[English](README.md) | [中文](README_zh.md)

</div>

---

## 📚 项目概述

这是一个专注于FreeRTOS嵌入式系统开发的学习资源库，旨在帮助开发者快速入门STM32开发。该仓库提供了详细的教程、示例代码和开发环境配置指南，帮助您轻松开始FreeRTOS开发之旅。

### 🌟 主要特点

- 📖 详细的FreeRTOS移植教程
- 🔧 完整的STM32开发环境搭建指南
- 💡 实用的示例项目
- 📝 清晰的文档说明
- 🔍 常见问题解决方案

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
│       └── tutorials/        # 中文教程
├── Despacito/                # STM32F103示例项目
│   ├── 001/                  # STM32项目模板
│   ├── 002/                  # FreeRTOS基础示例
│   ├── 003/                  # FreeRTOS动态任务创建
│   ├── 004/                  # FreeRTOS静态任务创建
│   ├── 005/                  # FreeRTOS工程完善（串口+配置优化）
│   ├── 006/                  # FreeRTOS多任务创建与删除
│   └── 007/                  # FreeRTOS任务参数示例
├── templates/                # 项目模板
│   └── README_template.md    # 示例项目README模板
├── CONTRIBUTING.md           # 贡献指南
├── CHANGELOG.md              # 版本历史
├── LICENSE                   # MIT许可证
└── README.md/README_zh.md    # 项目文档
```

---

## 🚀 快速开始

1. **克隆仓库**
   ```bash
   git clone https://github.com/Despacito0o/FreeRTOS.git
   ```

2. **阅读文档**
   - 查看 [001-STM32标准库开发环境搭建教程](docs/zh/001-STM32标准库开发环境搭建教程.md)
   - 学习 [002-FreeRTOS移植到keil6](docs/zh/002-FreeRTOS移植到keil6.md)
   - 跟随 [003-FreeRTOS动态任务创建](docs/zh/003-FreeRTOS动态任务创建.md)
   - 学习 [004-FreeRTOS静态任务创建](docs/zh/004-FreeRTOS静态任务创建.md)
   - 阅读 [005-FreeRTOS项目工程完善指南](docs/zh/005-FreeRTOS项目工程完善指南.md)
   - 浏览[文档索引](docs/README.md)中的所有文档

3. **运行示例**
   - 进入 [STM32项目模板](Despacito/001)
   - 进入 [FreeRTOS基础示例](Despacito/002)
   - 进入 [FreeRTOS动态任务创建](Despacito/003)
   - 进入 [FreeRTOS静态任务创建](Despacito/004)
   - 进入 [FreeRTOS工程完善示例](Despacito/005)
   - 进入 [FreeRTOS多任务创建与删除](Despacito/006)
   - 进入 [FreeRTOS任务参数示例](Despacito/007)
   - 按照每个项目的README进行编译和运行

---

## 📖 文档导航

### 📁 核心文档

- [001-STM32标准库开发环境搭建教程](docs/zh/001-STM32标准库开发环境搭建教程.md)
- [002-FreeRTOS移植到keil6](docs/zh/002-FreeRTOS移植到keil6.md)
- [003-FreeRTOS动态任务创建](docs/zh/003-FreeRTOS动态任务创建.md)
- [004-FreeRTOS静态任务创建](docs/zh/004-FreeRTOS静态任务创建.md)
- [005-FreeRTOS项目工程完善指南](docs/zh/005-FreeRTOS项目工程完善指南.md)

### 📝 项目相关

- [文档索引](docs/README.md) - 导航所有可用文档
- [贡献指南](CONTRIBUTING.md) - 如何为项目做出贡献
- [变更日志](CHANGELOG.md) - 版本历史和变更记录

### 🧠 教程

- [STM32上创建简单FreeRTOS程序详解](docs/zh/tutorials/STM32上创建简单FreeRTOS程序详解.md) - 从零开始创建FreeRTOS程序

---

## 🔍 示例项目

### 🟢 Despacito/001
基础STM32F103项目模板，包含标准外设库。

### 🟢 Despacito/002
FreeRTOS基础示例，展示任务创建和基本功能。

### 🟢 Despacito/003
FreeRTOS动态任务创建示例 - 演示任务创建和调度，实现简单的LED闪烁模式。

### 🟢 Despacito/004
FreeRTOS静态任务创建示例 - 演示如何使用静态内存分配方式创建任务，适用于资源受限的系统。

### 🟢 Despacito/005
FreeRTOS工程完善示例 - 添加串口通信功能、printf调试输出、优化FreeRTOS配置，使工程更加健壮和实用。

### 🟢 Despacito/006
FreeRTOS多任务创建与删除示例 - 演示如何动态创建、管理和删除任务，展示任务优先级对系统行为的影响，以及任务状态监控的实用方法。

### 🟢 Despacito/007
FreeRTOS任务参数示例 - 演示如何使用任务参数使任务函数更灵活、可复用，展示如何通过void指针向任务传递不同类型的数据。

---

## 🤝 贡献

欢迎提交贡献来帮助改进这个项目。在提交任何Pull Request或Issue之前，请阅读我们的[贡献指南](CONTRIBUTING.md)。

关键要点：
- Fork本仓库并创建特性分支
- 遵循代码风格和文档标准
- 彻底测试您的更改
- 提交具有清晰描述的Pull Request

---

## 📄 许可证

本项目基于MIT许可证 - 详情请见 [LICENSE](LICENSE) 文件。

---

## 👨‍💻 作者

- [Despacito0o](https://github.com/Despacito0o) - FreeRTOS开发者和教程创作者
- 访问我的 [CSDN博客](https://blog.csdn.net/supershmily) 获取更多嵌入式开发内容

---

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者！ 