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

## 📋 Project Structure

```
FreeRTOS/
├── docs/                     # Documentation
│   ├── README.md             # Documentation index
│   ├── en/                   # English documentation
│   │   ├── 001-STM32-Development-Environment-Setup.md
│   │   ├── 002-FreeRTOS-Port-to-Keil6.md
│   │   ├── 003-FreeRTOS-Dynamic-Task-Creation.md
│   │   ├── 004-FreeRTOS-Static-Task-Creation.md
│   │   ├── 005-FreeRTOS-Project-Improvement-Guide.md
│   │   └── tutorials/        # English tutorials
│   └── zh/                   # Chinese documentation
│       ├── 001-STM32标准库开发环境搭建教程.md
│       ├── 002-FreeRTOS移植到keil6.md
│       ├── 003-FreeRTOS动态任务创建.md
│       ├── 004-FreeRTOS静态任务创建.md
│       ├── 005-FreeRTOS项目工程完善指南.md
│       ├── 010-FreeRTOS二值信号量详解与实战教程.md
│       ├── 011-FreeRTOS计数型信号量详解与实战教程.md
│       └── tutorials/        # Chinese tutorials
├── Despacito/                # STM32F103 example projects
│   ├── 001/                  # STM32 project template
│   ├── 002/                  # FreeRTOS basic example
│   ├── 003/                  # FreeRTOS dynamic task creation
│   ├── 004/                  # FreeRTOS static task creation
│   ├── 005/                  # FreeRTOS project improvement (UART+config optimization)
│   ├── 006/                  # FreeRTOS multi-task creation and deletion
│   ├── 007/                  # FreeRTOS task parameters example
│   ├── 008/                  # FreeRTOS queue communication example
│   ├── 009/                  # FreeRTOS advanced queue operations
│   ├── 010/                  # FreeRTOS binary semaphore example
│   └── 011/                  # FreeRTOS counting semaphore example
├── templates/                # Project templates
│   └── README_template.md    # README template for examples
├── CONTRIBUTING.md           # Contribution guidelines
├── CHANGELOG.md              # Version history
├── LICENSE                   # MIT License
└── README.md/README_zh.md    # Project documentation
```

---

## 🚀 Quick Start

### 1. **Clone the repository**
```bash
git clone https://github.com/Despacito0o/FreeRTOS.git
cd FreeRTOS
```

### 2. **Follow the learning path**
This repository is organized as a progressive learning journey:

| Level | Projects | Focus | Skills Gained |
|-------|----------|-------|--------------|
| Beginner | 001-002 | Environment setup, FreeRTOS basics | Development setup, Basic concepts |
| Intermediate | 003-006 | Task management, Memory models | Task creation/deletion, Memory optimization |
| Advanced | 007-011 | Inter-task communication and synchronization | Parameters, Queues, Semaphores, Resource management |

### 3. **Explore example projects**
Each example builds on previous concepts and adds new skills:

- **[001] STM32 Project Template** - Starting point for STM32 development
- **[002] FreeRTOS Basic Example** - First steps with FreeRTOS
- **[003] Dynamic Task Creation** - Working with multiple tasks
- **[004] Static Task Creation** - Memory-optimized task creation
- **[005] Project Enhancement** - Adding UART, debugging capabilities
- **[006] Multi-Task Operations** - Creating, deleting, and monitoring tasks
- **[007] Task Parameters** - Flexible task functions with parameters
- **[008] Queue Communication** - Basic inter-task communication
- **[009] Advanced Queue Operations** - Efficient data transfer techniques
- **[010] Binary Semaphores** - Task synchronization and mutual exclusion
- **[011] Counting Semaphores** - Resource management and event counting

Each project includes complete source code and a detailed README with explanations and instructions.

---

## 📖 Documentation Navigation

### 📁 Core Documentation

Browse our comprehensive guides:

- **[001]** [STM32 Development Environment Setup](docs/en/001-STM32-Development-Environment-Setup.md)
- **[002]** [FreeRTOS Port to Keil6](docs/en/002-FreeRTOS-Port-to-Keil6.md)
- **[003]** [FreeRTOS Dynamic Task Creation](docs/en/003-FreeRTOS-Dynamic-Task-Creation.md)
- **[004]** [FreeRTOS Static Task Creation](docs/en/004-FreeRTOS-Static-Task-Creation.md)
- **[005]** [FreeRTOS Project Improvement Guide](docs/en/005-FreeRTOS-Project-Improvement-Guide.md)
- **[010]** [FreeRTOS Binary Semaphore Tutorial (Chinese)](docs/zh/010-FreeRTOS二值信号量详解与实战教程.md)
- **[011]** [FreeRTOS Counting Semaphore Tutorial (Chinese)](docs/zh/011-FreeRTOS计数型信号量详解与实战教程.md)

### 📝 Project Resources

- [Documentation Index](docs/README.md) - Navigate all available documentation
- [Contribution Guidelines](CONTRIBUTING.md) - How to contribute to this project
- [Change Log](CHANGELOG.md) - Version history and recent updates

### 🧠 Practical Tutorials

- [Creating a Simple FreeRTOS Project on STM32](docs/en/tutorials/Creating-Simple-FreeRTOS-Project-on-STM32.md)

---

## 🔍 Example Projects in Detail

### 🟢 [001] STM32 Project Template
A clean, ready-to-use STM32F103 template with standard peripheral library, providing the foundation for all other examples.

### 🟢 [002] FreeRTOS Basic Example
Your first steps with FreeRTOS - demonstrates basic task creation and simple functionality with LED blinking.

### 🟢 [003] Dynamic Task Creation
Learn how tasks are dynamically created and scheduled in FreeRTOS, with practical examples of task priorities and scheduling.

### 🟢 [004] Static Task Creation
Explore static memory allocation for task creation - crucial for memory-constrained embedded systems where dynamic allocation might be problematic.

### 🟢 [005] Project Enhancement
Take your project to the next level with UART communication, printf debugging, and optimized configurations - making development easier and more productive.

### 🟢 [006] Multi-Task Operations
Master task lifecycle management with dynamic creation and deletion, priority management, and state monitoring techniques.

### 🟢 [007] Task Parameters
Make your tasks flexible and reusable by learning how to pass parameters using void pointers - a fundamental skill for building modular RTOS applications.

### 🟢 [008] Queue Communication
Implement reliable inter-task communication using queues, with examples of both simple message passing and structured data transmission.

### 🟢 [009] Advanced Queue Operations
Explore advanced techniques for efficient data transfer between tasks, including pointer-based methods and solutions for common pitfalls.

### 🟢 [010] Binary Semaphores
Master the use of binary semaphores for task synchronization and mutual exclusion, with detailed API analysis and typical application scenarios.

### 🟢 [011] Counting Semaphores
Learn to use counting semaphores for resource pool management and event counting, with practical examples for advanced synchronization scenarios.

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

































   
  

---

