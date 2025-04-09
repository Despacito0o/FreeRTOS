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

## 📁 目录结构

```
FreeRTOS/
├── docs/                     # 文档
│   ├── en/                  # 英文文档
│   │   ├── FreeRTOS-Port-Guide.md
│   │   ├── STM32-Dev-Environment-Setup.md
│   │   └── Creating-Simple-FreeRTOS-Project-on-STM32.md
│   └── zh/                  # 中文文档
│       ├── FreeRTOS移植详解.md
│       ├── STM32标准库开发环境搭建教程.md
│       └── FreeRTOS移植详解-003.md
├── Despacito/               # STM32F103示例项目
│   ├── 001/                # STM32项目模板
│   ├── 002/                # FreeRTOS基础示例
│   ├── 003/                # FreeRTOS LED闪烁示例
│   └── 004/                # FreeRTOS静态内存分配示例
├── ScoreJudgment/           # FreeRTOS教程资料
│   └── STM32上创建简单FreeRTOS程序详解.md
└── README.md                # 项目文档
```

---

## 🚀 快速开始

1. 克隆仓库
```bash
git clone https://github.com/Despacito0o/FreeRTOS.git
```

2. 阅读文档
- 查看 [STM32开发环境搭建指南](docs/zh/STM32标准库开发环境搭建教程.md)
- 学习 [FreeRTOS移植详解](docs/zh/FreeRTOS移植详解.md)
- 跟随 [创建简单FreeRTOS程序详解](docs/zh/FreeRTOS移植详解-003.md)

3. 运行示例
- 进入 [Despacito基础示例](Despacito/002)
- 进入 [Despacito FreeRTOS LED闪烁示例](Despacito/003)
- 进入 [Despacito FreeRTOS静态内存分配示例](Despacito/004)
- 按照每个项目的README.md指南进行编译和运行

---

## 📖 文档导航

### 开发环境搭建
- [STM32开发环境搭建指南](docs/zh/STM32标准库开发环境搭建教程.md)
  - Keil MDK安装与配置
  - STM32标准外设库配置
  - 项目创建与配置
  - 常见问题解决方案

### FreeRTOS移植
- [FreeRTOS移植详解](docs/zh/FreeRTOS移植详解.md)
  - 源码获取与配置
  - 项目文件组织
  - 移植步骤
  - 编译与调试

### FreeRTOS示例
- [STM32上创建简单FreeRTOS程序详解](docs/zh/FreeRTOS移植详解-003.md)
  - FreeRTOS配置
  - 任务创建
  - LED闪烁实现
  - 调试与仿真

### STM32 FreeRTOS教程
- [STM32上创建简单FreeRTOS程序详解](ScoreJudgment/STM32上创建简单FreeRTOS程序详解.md)
  - FreeRTOS核心原理
  - 任务调度与上下文切换
  - 资源管理与同步机制
  - 中断处理与低功耗管理

---

## 🤝 贡献

欢迎提交Issue和Pull Request来帮助改进这个项目。在提交之前，请确保：

1. 代码符合项目的编码标准
2. 添加了必要的注释和文档
3. 测试通过，没有引入新的问题

---

## 📄 许可证

本项目基于MIT许可证 - 详情请见 [LICENSE](LICENSE) 文件

---

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者！

---

## 👨‍💻 作者

- [Despacito0o](https://github.com/Despacito0o) - FreeRTOS开发者和教程创作者
- 访问我的 [CSDN博客](https://blog.csdn.net/supershmily) 获取更多嵌入式开发内容

---

## 项目列表

### Despacito
STM32F103系列嵌入式开发项目，使用标准外设库(StdPeriph)进行开发。

#### Despacito/001
基础STM32F103项目模板，包含标准外设库。

#### Despacito/002
FreeRTOS基础示例。

#### Despacito/003
FreeRTOS LED闪烁示例 - 演示任务创建和调度，实现简单的LED闪烁模式。

#### Despacito/004
FreeRTOS静态内存分配示例 - 演示如何使用静态内存分配方式创建任务，适用于资源受限的系统。

---

## STM32标准库开发环境搭建指南

### 准备工作
1. 安装Keil MDK开发环境
2. 下载STM32标准外设库

### 详细步骤
1. 打开Keil，新建项目
   ![创建项目](https://i-blog.csdnimg.cn/direct/456e7f1370cd4f5d90b204dcbd37ff2a.png)

2. 选择存放项目的文件夹并命名，然后点击保存
   ![项目命名](https://i-blog.csdnimg.cn/direct/59e3493295b94cdaaa53beb27745c2e7.png)

3. 选择芯片型号（本例中为STM32F103C8），然后点击确定
   ![选择芯片](https://i-blog.csdnimg.cn/direct/95742a07675b467a9846eacbaf9e001c.png)

4. 关闭弹出窗口
   ![关闭窗口](https://i-blog.csdnimg.cn/direct/3fa8e6d04a2b43a59f3e0c102107a86c.png)

5. 在项目文件夹中添加三个子文件夹：Start、Library和User
   ![添加文件夹](https://i-blog.csdnimg.cn/direct/315e2eb94b954e86a950d86e0363cb3c.png)

### 下载和配置标准外设库
1. 前往ST官网下载最新的标准外设库：[点击官方下载](https://www.st.com.cn/zh/embedded-software/stsw-stm32054.html)
   ![下载库](https://i-blog.csdnimg.cn/direct/1868afb0b36246ab98824aaa4835d206.png)

2. 点击"获取最新版本"并接受许可协议
   ![接受协议](https://i-blog.csdnimg.cn/direct/4f31f48d21184a6488a683fb3600ff1f.png)

3. 使用您的ST账户登录
   ![登录](https://i-blog.csdnimg.cn/direct/d993c74d66424daba63851da6545deb3.png)

4. 点击"下载最新"下载最新版本
   ![下载最新版本](https://i-blog.csdnimg.cn/direct/658af4d3aaa04453906969c731e94c8a.png)

5. 解压下载的文件
   ![解压文件](https://i-blog.csdnimg.cn/direct/82860324304248a9bad5e8959c45db79.png)

### 文件配置
1. 找到启动文件路径：`Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm`，将所有文件复制到Start文件夹
   ![复制启动文件](https://i-blog.csdnimg.cn/direct/8f5c0ca058b9489f91cb8b49b408f1fd.png)

2. 导航到路径：`Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x`，将相关文件复制到Start文件夹
   ![复制设备支持文件](https://i-blog.csdnimg.cn/direct/734a5886f8684d41879e48f89226fd66.png)

3. 导航到路径：`Libraries\CMSIS\CM3\CoreSupport`，将核心支持文件复制到Start文件夹
   ![复制核心支持文件](https://i-blog.csdnimg.cn/direct/24f5a0388cf040ee84d68230113a7fdf.png)

4. 导航到路径：`Libraries\STM32F10x_StdPeriph_Driver\src`，将文件夹内容复制到Library文件夹
   ![复制标准外设驱动文件](https://i-blog.csdnimg.cn/direct/48399df386f64596a552435c93296bd6.png)

5. 打开inc文件夹（路径：`Libraries\STM32F10x_StdPeriph_Driver\inc`），将文件夹内容复制到Library文件夹
   ![复制头文件](https://i-blog.csdnimg.cn/direct/d7537287252a4dcaa0d95aa38caf5fb7.png)

6. 导航到路径：`Project\STM32F10x_StdPeriph_Template`，将模板文件复制到User文件夹
   ![复制模板文件](https://i-blog.csdnimg.cn/direct/b61aa4c1fdf04ea48ec8ff18f9d7e90f.png)

### 项目配置
1. 返回Keil，点击项目文件管理按钮
   ![项目管理](https://i-blog.csdnimg.cn/direct/d38bef47b03345f2bad77ece96d4c707.png)

2. 点击"新建组"按钮创建3个组（Start、Library、User）
   ![创建组](https://i-blog.csdnimg.cn/direct/2fc57debf42142e0853f06ea0cd5e6f3.png)

3. 向每个组添加文件
   - Start组：添加启动文件和相关支持文件
   - Library组：添加标准外设库文件
   - User组：添加用户代码文件

4. 配置包含路径和宏定义
   - 添加包含路径：Start、Library、User
   - 添加宏定义：USE_STDPERIPH_DRIVER, STM32F10X_MD

5. 配置调试器设置
   - 选择ST-Link调试器
   - 勾选"复位并运行"选项

### 解决常见问题
如果由于过时的core_cm3.c和core_cm3.h文件出现错误：
1. 下载STM32Cube_FW软件包：[ST官方链接](https://www.st.com.cn/zh/embedded-software/stm32cubef1.html)
2. 从`Drivers\CMSIS\Include`目录复制新版本头文件
3. 禁用旧版本core_cm3.c，使用CMSIS标准接口

### 示例代码
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

## 项目编译与下载
编译项目并确保0错误和0警告，然后使用ST-Link将程序下载到开发板。

![编译成功](https://i-blog.csdnimg.cn/direct/f91d31ff6e034111af569b5981f41213.png)
![运行结果](https://i-blog.csdnimg.cn/direct/1fb27fecd8fd4214a76819224b295a4a.jpeg) 