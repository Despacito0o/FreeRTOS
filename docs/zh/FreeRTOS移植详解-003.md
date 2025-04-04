# STM32上创建简单FreeRTOS程序详解

## 前言
本文将详细讲解如何在STM32平台上创建一个简单的FreeRTOS程序，并通过一个LED闪烁任务来验证程序的正确运行。整个过程将按照步骤一步一步展开，确保即使是初学者也能轻松上手。

> **源码获取**：本教程相关的工程文件已上传至GitHub，您可以通过以下链接获取完整代码：
> [https://github.com/Despacito0o/FreeRTOS.git](https://github.com/Despacito0o/FreeRTOS.git)

## 开发环境准备
- Keil MDK 5.x 或更高版本
- STM32F103系列开发板（本教程使用STM32F103C8）
- ST-Link调试器（如使用实际硬件）

## 具体步骤

### 1. 复制工程模板
首先，我们需要复制之前创建好的工程模板，并命名为003。这样做是为了保留原始工程，同时在新的工程上进行FreeRTOS程序的开发，避免对原有工程造成破坏。使用模板也能确保基础的STM32配置已经完成，省去了从零开始的繁琐步骤。

> **提示**：如果您直接从GitHub克隆了项目，可以在`Despacito/002`目录中找到基础工程模板。

![工程模板复制](https://i-blog.csdnimg.cn/direct/62e7f9855aba4f08be71028476798cec.png)

### 2. 清理不必要的头文件
打开工程文件，删除不需要的头文件。这一步是为了精简工程，删除与我们当前FreeRTOS程序开发无关的组件，减少可能的冲突和编译错误。同时，一个干净的工程结构也有助于我们更清晰地理解FreeRTOS的组成部分和我们的程序结构。

![删除不需要的头文件](https://i-blog.csdnimg.cn/direct/29216208fa0543dd86fa7c9338a5cc7d.png)

### 3. 修改FreeRTOS配置文件
接下来，我们需要修改`freertosconfig.h`文件，添加三个关键中断处理函数的定义。这是FreeRTOS程序开发中的重要一步。FreeRTOS需要使用系统的一些中断处理，包括：
- PendSV_Handler：用于任务切换
- SVC_Handler：用于系统服务调用
- SysTick_Handler：用于系统滴答计时，是FreeRTOS进行任务调度的时间基准

通过这样的定义，我们告诉编译器FreeRTOS的中断处理函数将使用系统默认的同名函数。

```cpp
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler
#define xPortSysTickHandler SysTick_Handler
```

![修改FreeRTOS配置](https://i-blog.csdnimg.cn/direct/7bb208bd7d6a4b0898697b89894f30eb.png)

### 4. 注释原有中断处理函数
由于上一步中我们已经将三个关键中断交给了FreeRTOS处理，所以需要在STM32的中断文件`stm32f10x_it.c`中注释掉原本的这三个中断处理函数。如果不注释，将会导致函数重定义错误，因为FreeRTOS和STM32标准库都定义了相同名称的函数。

![注释中断处理函数1](https://i-blog.csdnimg.cn/direct/685c23e1c58342d4b609b5a0db610e05.png)
![注释中断处理函数2](https://i-blog.csdnimg.cn/direct/85ca5f72949c435ead14443615f5d7f9.png)

### 5. 编写测试程序
完成基础配置后，我们需要编写一个测试程序来验证FreeRTOS是否正常工作。在嵌入式系统开发中，LED闪烁通常是最简单且直观的测试方式，也被称为"嵌入式世界的Hello World"。

#### 5.1 定义任务句柄
首先定义一个任务句柄，它是FreeRTOS中用于操作和管理任务的标识符。
```cpp
TaskHandle_t myTaskHandler;
```

#### 5.2 创建任务
使用`xTaskCreate`函数创建一个任务，这个函数有六个参数：
- 任务函数名称：`myTask`，指定任务的入口函数
- 任务名称：`"myTask"`，一个字符串，用于调试识别
- 堆栈大小：`128`，指定任务所需的堆栈空间大小
- 传入参数：`NULL`，可以传递给任务的参数
- 优先级：`2`，任务优先级，数字越大优先级越高
- 任务句柄：`&myTaskHandler`，用于返回任务的句柄

```cpp
xTaskCreate(myTask, "myTask", 128, NULL, 2, &myTaskHandler);
```

#### 5.3 启动任务调度器
创建任务后，需要启动FreeRTOS的任务调度器，使系统开始运行并根据任务优先级进行调度。
```cpp
vTaskStartScheduler();
```

#### 5.4 创建任务函数
定义任务函数，这是任务执行的入口。FreeRTOS任务函数通常是一个无限循环，因为任务终止会导致系统出错。
```cpp
void myTask(void *arg)
{
    while(1)
    {
        // 任务代码将在这里执行
    }
}
```

#### 5.5 实现LED闪烁功能
在任务函数中添加LED翻转操作，使LED以固定时间间隔闪烁，这样我们可以直观地观察任务是否正常执行。
```cpp
void myTask(void *arg)
{
    while(1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED亮
        vTaskDelay(500);                     // 延时500个时钟节拍，相当于500ms
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED灭
        vTaskDelay(500);                     // 再延时500ms
    }
}
```
这里的`vTaskDelay`函数是FreeRTOS提供的延时函数，它会使当前任务进入阻塞状态，并允许其他任务运行，实现了真正的多任务操作。

> **代码说明**：与传统的延时函数不同，`vTaskDelay`不会占用CPU资源。当任务调用此函数后，FreeRTOS会将该任务置于阻塞状态，并切换到其他就绪任务执行，直到指定的延时时间到达。

### 6. 配置调试环境
为了验证我们的程序，需要正确配置调试环境。点击IDE中的"魔法棒"（Debug按钮），选择"use Simulator"，并设置适合STM32F103C8芯片的调试参数：
- Dialog DLL：DARMSTM.DLL
- Parameter：-PSTM32F103C8

这些设置告诉调试器使用STM32设备模拟器，并指定了正确的芯片型号，确保仿真环境与实际硬件一致。

![配置调试环境](https://i-blog.csdnimg.cn/direct/b98362ff706f4be6a5af329ed011a8ad.png)

### 7. 开始调试
配置完成后，点击调试按钮开始调试过程。此时，调试器会加载程序到虚拟的STM32芯片中，并准备执行。

![启动调试](https://i-blog.csdnimg.cn/direct/744beaaf32194e77ad01d3ac7095beab.png)

### 8. 打开逻辑分析仪
为了直观地观察LED的状态变化，我们需要打开IDE中的逻辑分析仪工具。逻辑分析仪可以实时显示GPIO引脚状态的变化，帮助我们确认任务是否按预期执行。

![打开逻辑分析仪](https://i-blog.csdnimg.cn/direct/e26592b59cfe4ce79017144749d046be.png)

### 9. 配置逻辑分析仪
点击逻辑分析仪左上角的"Setup..."按钮，开始配置要监视的引脚。

![配置逻辑分析仪](https://i-blog.csdnimg.cn/direct/e8c109e28bcd49358c538f9e8ab61ad2.png)

### 10. 添加监视变量
在弹出的配置窗口中，添加要监视的GPIO引脚。在本例中，我们使用的是PC13引脚（GPIOC的第13号引脚），这通常是STM32F103C8板载LED的控制引脚。输入"portc.13"后点击空白处确认添加。

![添加监视变量](https://i-blog.csdnimg.cn/direct/07f99b3b7a9b400fa2373377e90414e0.png)

### 12. 设置显示类型
继续点击刚刚添加的变量（PC13），将显示类型（Display Type）改为"bit"，这样可以更清晰地看到引脚的高低电平变化。完成设置后点击"Close"关闭配置窗口。

![设置显示类型](https://i-blog.csdnimg.cn/direct/8a8657129a004159a7b5ff3a24f137ce.png)

### 13. 运行程序
配置完成后，点击"Run"按钮开始运行程序。此时，FreeRTOS调度器会启动，并开始执行我们创建的LED闪烁任务。

![运行程序](https://i-blog.csdnimg.cn/direct/bc4fc56263524915ac23d434c770e853.png)

### 14. 观察结果
如果一切正常，我们应该能在逻辑分析仪中观察到PC13引脚的电平状态按照500ms的间隔周期性变化，这表明我们的FreeRTOS任务已经成功创建并正常执行。这也证明了我们的简单FreeRTOS程序已经成功运行。

![观察结果](https://i-blog.csdnimg.cn/direct/4bf3362ad4a84d148d25f329296042e3.png)

## 常见问题与解决方案

### 1. 编译报错：函数重定义
**问题**：编译时出现PendSV_Handler、SVC_Handler或SysTick_Handler函数重定义错误。  
**解决方案**：检查是否正确注释了`stm32f10x_it.c`中的对应函数。

### 2. LED不闪烁
**问题**：程序运行后，LED没有按预期闪烁。  
**解决方案**：
- 检查GPIO配置是否正确
- 确认延时时间是否合适
- 检查任务是否成功创建（可以使用任务状态查看函数）

### 3. 堆栈溢出
**问题**：运行时出现堆栈溢出错误。  
**解决方案**：增加任务堆栈大小，修改`xTaskCreate`中的堆栈参数（第三个参数）。

## 进阶拓展

### 多任务示例
以下是一个创建两个任务的示例，一个控制LED闪烁，另一个在串口输出信息：

```cpp
TaskHandle_t ledTaskHandler;
TaskHandle_t uartTaskHandler;

void ledTask(void *arg)
{
    while(1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        vTaskDelay(500);
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        vTaskDelay(500);
    }
}

void uartTask(void *arg)
{
    while(1)
    {
        printf("FreeRTOS running...\r\n");
        vTaskDelay(1000);
    }
}

int main(void)
{
    // 初始化外设...
    
    // 创建任务
    xTaskCreate(ledTask, "LED", 128, NULL, 2, &ledTaskHandler);
    xTaskCreate(uartTask, "UART", 128, NULL, 1, &uartTaskHandler);
    
    // 启动调度器
    vTaskStartScheduler();
    
    // 正常情况下不会执行到这里
    while(1);
}
```

## 总结
通过以上步骤，我们成功地在STM32平台上创建了一个简单的FreeRTOS程序，并通过一个LED闪烁任务验证了程序的正确运行。FreeRTOS是一个功能强大的实时操作系统，它为嵌入式开发提供了多任务处理、任务间通信、资源管理等重要功能，能够极大地简化复杂嵌入式应用的开发。

在接下来的学习中，我们将进一步探索FreeRTOS的高级特性，如信号量、消息队列、任务通知等，以便开发更复杂、更强大的嵌入式应用。

## 更多资源

要深入学习FreeRTOS，可以参考以下资源：

1. [GitHub项目完整代码](https://github.com/Despacito0o/FreeRTOS.git)
2. [FreeRTOS官方文档](https://www.freertos.org/Documentation/RTOS_book.html)
3. [STM32参考手册](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

## 参考文献
1. FreeRTOS官方文档：[https://www.freertos.org/Documentation/RTOS_book.html](https://www.freertos.org/Documentation/RTOS_book.html)
2. STM32标准外设库用户手册
3. FreeRTOS源码解析

---
如有疑问，欢迎在评论区留言交流！您也可以在GitHub上提交Issue或Pull Request，共同改进这个项目。













