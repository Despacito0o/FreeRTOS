
# FreeRTOS移植详解

> 本文详细介绍了如何在STM32平台上移植FreeRTOS操作系统，包括源码获取、工程配置、文件修改等完整步骤。通过本文的学习，您将掌握FreeRTOS移植的关键技术点。

## 一、准备工作

### 1.1 打开工程文件夹

首先打开之前创建的keil6文件夹，准备进行FreeRTOS的移植工作。

[点击打开keil6创建新文件夹教程（含工程文件夹）](https://blog.csdn.net/supershmily/article/details/146780134?spm=1001.2014.3001.5501)

![打开keil6文件夹](https://i-blog.csdnimg.cn/direct/953f51d2cfe047b3a7963093f9647e5f.png)

### 1.2 下载FreeRTOS源码

访问FreeRTOS官网下载最新版本源码：

![下载FreeRTOS源码](https://i-blog.csdnimg.cn/direct/1b330855776f4a688cf8ce1e15a993b1.png)

### 1.3 获取内核文档

在官网找到关于FreeRTOS内核的文档：

![获取内核文档](https://i-blog.csdnimg.cn/direct/77acc0a6f0b9453896b7c1419819609a.png)

### 1.4 选择下载版本

点击下载FreeRTOS，选择最新版本FreeRTOS 202212.01（有条件也可以下载两个版本进行对比）：

![选择下载版本](https://i-blog.csdnimg.cn/direct/ce5830134bd7473f83f10734946861f7.png)

### 1.5 解压文件

将下载好的文件解压到创建的FreeRTOS目录下：

![解压文件](https://i-blog.csdnimg.cn/direct/d632ebe55ec245e096146ea1df2ae3c1.png)

## 二、工程配置

### 2.1 创建新工程

1. 新建一个002工程文件
2. 将上节课的工程文件模板复制进来
3. 添加FreeRTOS src和FreeRTOS portable文件夹

![创建新工程](https://i-blog.csdnimg.cn/direct/3ba0bf8841ac4939bc6fd8235cf4c17a.png)

### 2.2 复制源文件

导航到`...\FreeRTOSv202212.01\FreeRTOS\Source`，将所有.c文件复制到002的freertos src文件夹中：

![复制源文件1](https://i-blog.csdnimg.cn/direct/b556b5c9559142bab694f00b775dc854.png)
![复制源文件2](https://i-blog.csdnimg.cn/direct/ab9e3acc65a74930bb36c6c6d15e0478.png)

### 2.3 复制移植文件

导航到`...\FreeRTOSv202212.01\FreeRTOS\Source\portable`，将"MemMang"文件夹与"RVDS"文件夹拷贝到新建的freertos port文件夹中：

![复制移植文件1](https://i-blog.csdnimg.cn/direct/eb30108c2e424bd8acf22f3c0ec91c98.png)
![复制移植文件2](https://i-blog.csdnimg.cn/direct/6c5a764f67004e009e721712530b724e.png)

### 2.4 复制头文件

导航到`...\FreeRTOSv202212.01\FreeRTOS\Source`，将include直接复制到工程文件夹并改名为freertos include：

![复制头文件1](https://i-blog.csdnimg.cn/direct/386d0fa8afba4d9fbe3a0ea3aea87e6c.png)
![复制头文件2](https://i-blog.csdnimg.cn/direct/12673f270b124a46aaf98d140e407af9.png)

### 2.5 整理文件结构

为了更好的文件组织，可以在002目录下新建一个FreeRTOS文件夹，并将刚才创建的三个文件夹放入其中：

![整理文件结构](https://i-blog.csdnimg.cn/direct/88c40549c293436095b2fc6a53eb0c5f.png)

### 2.6 配置FreeRTOSConfig.h

导航到`...\FreeRTOSv202212.01\FreeRTOS\Demo\CORTEX_STM32F103_Keil`找到freertosconfig.h，将其复制到user文件夹下：

![配置FreeRTOSConfig.h](https://i-blog.csdnimg.cn/direct/3bef10073b364903a0b3097a5e4e1f84.png)

## 三、Keil工程配置

### 3.1 添加文件组

1. 打开Keil，点击魔法棒右边的三个小箱子
2. 添加freertos port组，添加以下文件：
   - `...\Despacito\002\FreeRTOS\freertos portable\RVDS\ARM_CM3\port.c`
   - `...\Despacito\002\FreeRTOS\freertos portable\MemMang\heap_4.c`

![添加文件组1](https://i-blog.csdnimg.cn/direct/d6fa53a8c2074a89944ba443f6b1815f.png)

3. 添加freertos src组，添加所有.c文件：

![添加文件组2](https://i-blog.csdnimg.cn/direct/8759c58afa1e475f823e5b3bc8924a5a.png)

4. 在user分组中添加FreeRTOSConfig.h文件：

![添加文件组3](https://i-blog.csdnimg.cn/direct/d71638dd9cee4df588e2d9838f76cc88.png)

### 3.2 配置头文件路径

点击魔法棒-->c/c++(AC6)-->include path，添加以下路径：

![配置头文件路径](https://i-blog.csdnimg.cn/direct/43f73e6f19f04411a400a5e07ce9f0c3.png)

## 四、文件修改

### 4.1 修改FreeRTOSConfig.h

FreeRTOSConfig.h文件需要修改的内容不多，主要是：
1. 修改开发板对应的头文件（如STM32F1系列使用`#include "stm32f10x.h"`）
2. 添加串口头文件`#include "stm32f10x_usart.h"`（用于断言操作打印信息）

![修改FreeRTOSConfig.h](https://i-blog.csdnimg.cn/direct/3464377815724a94b1230a67c5d75001.png)

### 4.2 修改stm32f10x_it.c

SysTick中断服务函数是FreeRTOS的心跳时钟，驱动着FreeRTOS的运行。FreeRTOS已经帮我们实现了：
1. 在port.c中实现了`vPortSetupTimerInterrupt()`函数
2. 实现了通用的`xPortSysTickHandler()`函数

我们只需要在stm32f10x_it.c中实现STM32平台上的`SysTick_Handler()`函数即可。

同时，需要注释掉`PendSV_Handler()`与`SVC_Handler()`这两个函数，因为FreeRTOS已经在port.c中实现了`xPortPendSVHandler()`与`vPortSVCHandler()`函数。

```c
/* 修改后的stm32f10x_it.c文件 */
#include "stm32f10x_it.h"
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h" 

/* 其他代码保持不变 */

// 注释掉SVC_Handler
//void SVC_Handler(void)
//{
//}

// 注释掉PendSV_Handler
//void PendSV_Handler(void)
//{
//}

// 实现SysTick_Handler
void SysTick_Handler(void)
{
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) //系统已经运行
    {
        xPortSysTickHandler();	
    }
}
```

### 4.3 修改main.c

修改main.c文件，添加FreeRTOS相关头文件和初始化代码：

```c
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

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

## 五、编译问题解决

### 5.1 常见编译错误

FreeRTOS移植编译错误主要由以下原因引起：

1. **编译器版本与移植文件不兼容**
   - `__forceinline`关键字未识别：RVDS移植文件中的`__forceinline`是ARM Compiler 5（AC5）特有的内联语法
   - 汇编语法错误：RVDS移植文件中的汇编指令语法与AC6不兼容

2. **关键配置缺失**
   - 中断服务函数重命名问题
   - 数据类型未定义

3. **其他可能原因**
   - 中断优先级冲突
   - 内存分配问题

### 5.2 解决方案

1. **替换移植文件**
   - 删除portable/RVDS/ARM_CM3目录
   - 复制FreeRTOS/portable/GCC/ARM_CM3中的文件到工程
   - 更新Keil工程文件引用路径

2. **修改编译器设置**
   - 在Keil的Options for Target → C/C++选项卡中：
     - 使用AC5编译器
     - 或启用AC6的GNU兼容模式

3. **验证关键配置**
```c
// FreeRTOSConfig.h 关键配置示例
#define configUSE_TIMERS 1
#define configTIMER_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define configTIMER_QUEUE_LENGTH 10
#define configKERNEL_INTERRUPT_PRIORITY 255
```

### 5.3 切换到GCC编译器

在Keil中切换到GCC编译器：

![切换到GCC编译器1](https://i-blog.csdnimg.cn/direct/ab4d0ab1a18e4f3c8728279f7c2ec04b.png)
![切换到GCC编译器2](https://i-blog.csdnimg.cn/direct/6cbc7465a2854ee88ae59b4a3ca57a16.png)
![切换到GCC编译器3](https://i-blog.csdnimg.cn/direct/0ae79ce28d264311bd42c2d3a54deed1.png)

### 5.4 编译结果

编译后没有报错和警告，移植成功：

![编译结果](https://i-blog.csdnimg.cn/direct/2d99480e286647f78b09ef4867bfbd51.png)

## 六、总结

通过以上步骤，我们成功完成了FreeRTOS在STM32平台上的移植。主要步骤包括：
1. 获取并配置FreeRTOS源码
2. 创建工程并添加必要文件
3. 修改相关配置文件
4. 解决编译问题

移植完成后，您就可以开始使用FreeRTOS进行开发了。FreeRTOS作为一个轻量级的实时操作系统，在嵌入式系统开发中有着广泛的应用。











