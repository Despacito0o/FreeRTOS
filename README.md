# FreeRTOS Embedded Development Learning Library

<div align="center">

[![GitHub stars](https://img.shields.io/github/stars/Despacito0o/FreeRTOS.svg?style=social&label=Stars)](https://github.com/Despacito0o/FreeRTOS)
[![GitHub forks](https://img.shields.io/github/forks/Despacito0o/FreeRTOS.svg?style=social&label=Forks)](https://github.com/Despacito0o/FreeRTOS)
[![GitHub watchers](https://img.shields.io/github/watchers/Despacito0o/FreeRTOS.svg?style=social&label=Watchers)](https://github.com/Despacito0o/FreeRTOS)

[English](README.md) | [中文](README_zh.md)

</div>

---

## 📚 Project Overview

This is a learning resource library focused on FreeRTOS embedded system development, designed to help developers quickly get started with STM32 development. The repository provides detailed tutorials, example code, and development environment configuration guides to help you easily begin your FreeRTOS development journey.

### 🌟 Key Features

- 📖 Detailed FreeRTOS porting tutorial
- 🔧 Complete STM32 development environment setup guide
- 💡 Practical example projects
- 📝 Clear documentation
- 🔍 Common problem solutions

---

## 📋 Project Structure

```
FreeRTOS/
├── docs/                     # Documentation
│   ├── README.md             # Documentation index
│   ├── en/                   # English documentation
│   │   ├── FreeRTOS-Port-Guide.md
│   │   ├── STM32-Dev-Environment-Setup.md
│   │   ├── Creating-Simple-FreeRTOS-Project-on-STM32.md
│   │   └── tutorials/        # English tutorials
│   └── zh/                   # Chinese documentation
│       ├── FreeRTOS移植详解.md
│       ├── STM32标准库开发环境搭建教程.md
│       ├── FreeRTOS移植详解-003.md
│       └── tutorials/        # Chinese tutorials
├── Despacito/                # STM32F103 example projects
│   ├── 001/                  # STM32 project template
│   ├── 002/                  # FreeRTOS basic example
│   ├── 003/                  # FreeRTOS LED blink example
│   ├── 004/                  # FreeRTOS static allocation example
│   └── 005/                  # FreeRTOS project improvement (UART+config optimization)
├── templates/                # Project templates
│   └── README_template.md    # README template for examples
├── CONTRIBUTING.md           # Contribution guidelines
├── CHANGELOG.md              # Version history
├── LICENSE                   # MIT License
└── README.md/README_zh.md    # Project documentation
```

---

## 🚀 Quick Start

1. **Clone the repository**
   ```bash
   git clone https://github.com/Despacito0o/FreeRTOS.git
   ```

2. **Read the documentation**
   - View [STM32 Development Environment Setup Guide](docs/en/STM32-Dev-Environment-Setup.md)
   - Learn [FreeRTOS Porting Guide](docs/en/FreeRTOS-Port-Guide.md)
   - Follow [Creating a Simple FreeRTOS Project](docs/en/Creating-Simple-FreeRTOS-Project-on-STM32.md)
   - Read [FreeRTOS Project Improvement Guide](docs/en/FreeRTOS-Project-Improvement-Guide.md)
   - Browse all documents in the [documentation index](docs/README.md)

3. **Run examples**
   - Go to [STM32 Project Template](Despacito/001)
   - Go to [FreeRTOS Basic Example](Despacito/002)
   - Go to [FreeRTOS LED Blink Example](Despacito/003)
   - Go to [FreeRTOS Static Allocation Example](Despacito/004)
   - Go to [FreeRTOS Project Improvement Example](Despacito/005)
   - Follow each project's README for compilation and running instructions

---

## 📖 Documentation Navigation

### 📁 Core Documentation

- [STM32 Development Environment Setup Guide](docs/en/STM32-Dev-Environment-Setup.md)
- [FreeRTOS Porting Guide](docs/en/FreeRTOS-Port-Guide.md)
- [Creating a Simple FreeRTOS Project on STM32](docs/en/Creating-Simple-FreeRTOS-Project-on-STM32.md)
- [FreeRTOS Project Improvement Guide](docs/en/FreeRTOS-Project-Improvement-Guide.md)

### 📝 Project-related

- [Documentation Index](docs/README.md) - Navigate all available documentation
- [Contribution Guidelines](CONTRIBUTING.md) - How to contribute to this project
- [Change Log](CHANGELOG.md) - Version history and changes

### 🧠 Tutorials

- [STM32上创建简单FreeRTOS程序详解](docs/zh/tutorials/STM32上创建简单FreeRTOS程序详解.md) - Creating a simple FreeRTOS program

---

## 🔍 Example Projects

### 🟢 Despacito/001
Basic STM32F103 project template with standard peripheral library.

### 🟢 Despacito/002
FreeRTOS basic example with task creation and simple functionality.

### 🟢 Despacito/003
FreeRTOS LED blink example - demonstrates task creation and scheduling with a simple LED blinking pattern.

### 🟢 Despacito/004
FreeRTOS static memory allocation example - demonstrates how to create tasks using static memory allocation method, suitable for resource-constrained systems.

### 🟢 Despacito/005
FreeRTOS project improvement example - adds UART communication, printf debugging output, and optimized FreeRTOS configuration, making the project more robust and practical for developing complex applications.

---

## 🤝 Contributing

Contributions are welcome to help improve this project. Please read our [Contribution Guidelines](CONTRIBUTING.md) before submitting any pull requests or issues.

Key points:
- Fork the repository and create a feature branch
- Follow code style and documentation standards
- Test your changes thoroughly
- Submit a pull request with a clear description

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

- [Despacito0o](https://github.com/Despacito0o) - FreeRTOS developer and tutorial creator
- Visit my [CSDN Blog](https://blog.csdn.net/supershmily) for more embedded development content

---

## 🙏 Acknowledgments

Thanks to all developers who have contributed to this project!

---

## Project List

### Despacito
STM32F103 series embedded development projects, using standard peripheral library (StdPeriph) for development.

#### Despacito/001
Basic STM32F103 project template with standard peripheral library.

#### Despacito/002
FreeRTOS basic example.

#### Despacito/003
FreeRTOS LED blink example - demonstrates task creation and scheduling with a simple LED blinking pattern.

#### Despacito/004
FreeRTOS static memory allocation example - demonstrates how to create tasks using static memory allocation method, suitable for resource-constrained systems.

#### Despacito/005
FreeRTOS project improvement example - adds UART communication, printf debugging output, and optimized FreeRTOS configuration, making the project more robust and practical for developing complex applications.

---

## STM32 Standard Library Development Environment Setup Guide

### Preparation
1. Install Keil MDK development environment
2. Download STM32 standard peripheral library

### Detailed Steps
1. Open Keil, create a new project
   ![Create Project](https://i-blog.csdnimg.cn/direct/456e7f1370cd4f5d90b204dcbd37ff2a.png)

2. Select a folder to store the project and name it, then click Save
   ![Name Project](https://i-blog.csdnimg.cn/direct/59e3493295b94cdaaa53beb27745c2e7.png)

3. Select your chip model (in this example, STM32F103C8), then click OK
   ![Select Chip](https://i-blog.csdnimg.cn/direct/95742a07675b467a9846eacbaf9e001c.png)

4. Close the pop-up window
   ![Close Window](https://i-blog.csdnimg.cn/direct/3fa8e6d04a2b43a59f3e0c102107a86c.png)

5. Add three subfolders to the project folder: Start, Library, and User
   ![Add Folder](https://i-blog.csdnimg.cn/direct/315e2eb94b954e86a950d86e0363cb3c.png)

### Download and Configure Standard Peripheral Library
1. Go to ST official website to download the latest standard peripheral library: [Click to Official Download](https://www.st.com.cn/zh/embedded-software/stsw-stm32054.html)
   ![Download Library](https://i-blog.csdnimg.cn/direct/1868afb0b36246ab98824aaa4835d206.png)

2. Click "Get Latest Version" and accept the license agreement
   ![Accept Agreement](https://i-blog.csdnimg.cn/direct/4f31f48d21184a6488a683fb3600ff1f.png)

3. Use your ST account to log in
   ![Login](https://i-blog.csdnimg.cn/direct/d993c74d66424daba63851da6545deb3.png)

4. Click "Download Latest" to download the latest version
   ![Download Latest Version](https://i-blog.csdnimg.cn/direct/658af4d3aaa04453906969c731e94c8a.png)

5. Unzip the downloaded file
   ![Unzip File](https://i-blog.csdnimg.cn/direct/82860324304248a9bad5e8959c45db79.png)

### File Configuration
1. Find the startup file path: `Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm`, and copy all files to the Start folder
   ![Copy Startup File](https://i-blog.csdnimg.cn/direct/8f5c0ca058b9489f91cb8b49b408f1fd.png)

2. Navigate to the path: `Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x`, and copy related files to the Start folder
   ![Copy Device Support Files](https://i-blog.csdnimg.cn/direct/734a5886f8684d41879e48f89226fd66.png)

3. Navigate to the path: `Libraries\CMSIS\CM3\CoreSupport`, and copy the core support files to the Start folder
   ![Copy Core Support Files](https://i-blog.csdnimg.cn/direct/24f5a0388cf040ee84d68230113a7fdf.png)

4. Navigate to the path: `Libraries\STM32F10x_StdPeriph_Driver\src`, and copy the folder content to the Library folder
   ![Copy Standard Peripheral Driver Files](https://i-blog.csdnimg.cn/direct/48399df386f64596a552435c93296bd6.png)

5. Open the inc folder (path: `Libraries\STM32F10x_StdPeriph_Driver\inc`), and copy the folder content to the Library folder
   ![Copy Header Files](https://i-blog.csdnimg.cn/direct/d7537287252a4dcaa0d95aa38caf5fb7.png)

6. Navigate to the path: `Project\STM32F10x_StdPeriph_Template`, and copy the template files to the User folder
   ![Copy Template Files](https://i-blog.csdnimg.cn/direct/b61aa4c1fdf04ea48ec8ff18f9d7e90f.png)

### Project Configuration
1. Return to Keil, click the project file management button
   ![Project Management](https://i-blog.csdnimg.cn/direct/d38bef47b03345f2bad77ece96d4c707.png)

2. Click the "New Group" button to create 3 groups (Start, Library, User)
   ![Create Groups](https://i-blog.csdnimg.cn/direct/2fc57debf42142e0853f06ea0cd5e6f3.png)

3. Add files to each group
   - Start group: Add startup files and related support files
   - Library group: Add standard peripheral library files
   - User group: Add user code files

4. Configure Include Paths and Macro Definitions
   - Add Include Paths: Start, Library, User
   - Add Macro Definitions: USE_STDPERIPH_DRIVER, STM32F10X_MD

5. Configure Debugger Settings
   - Select ST-Link Debugger
   - Check "Reset and Run" option

### Solve Common Problems
If you encounter errors due to outdated core_cm3.c and core_cm3.h files:
1. Download STM32Cube_FW software package: [ST Official Link](https://www.st.com.cn/zh/embedded-software/stm32cubef1.html)
2. Copy new version header files from `Drivers\CMSIS\Include` directory
3. Disable old version core_cm3.c and use CMSIS standard interface

### Example Code
```cpp
#include "stm32f10x.h"
int main(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    while(1) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  
    }
}
```

## Project Compilation and Download
Compile the project and ensure 0 errors and 0 warnings, then use ST-Link to download the program to the development board.

![Compile Success](https://i-blog.csdnimg.cn/direct/f91d31ff6e034111af569b5981f41213.png)
![Run Result](https://i-blog.csdnimg.cn/direct/1fb27fecd8fd4214a76819224b295a4a.jpeg)

































   
  

---

