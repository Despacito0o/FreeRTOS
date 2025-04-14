# FreeRTOS 任务参数详解与实践

## 前言

大家好，今天我们来探讨一下 FreeRTOS 中非常有用但经常被忽视的特性——任务参数。在我之前的 FreeRTOS 系列文章中，创建任务时参数都填写的是 NULL，今天我们将深入了解如何利用任务参数实现更灵活的任务设计。

如果您对 FreeRTOS 有兴趣，欢迎关注我的 GitHub 仓库：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)，里面包含了从入门到进阶的全套 FreeRTOS 学习资源和示例代码！

## 任务参数基础

首先，我们看一下创建任务函数的原型：

```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,        /* 任务函数指针 */
    const char * const pcName,        /* 任务名称 */
    const uint16_t usStackDepth,      /* 任务堆栈大小 */
    void *pvParameters,               /* 任务参数 */
    UBaseType_t uxPriority,           /* 任务优先级 */
    TaskHandle_t * const pxCreatedTask /* 任务句柄 */
```

其中，`pvParameters` 是 `void` 指针类型，这意味着可以传递任何类型的数据作为任务参数。这种设计非常灵活，可以让我们：

- 传递基本数据类型（强制类型转换为 `void*`）
- 传递结构体或数组的地址
- 传递字符串常量
- 甚至可以传递函数指针

## 实战案例：一个函数，多个任务

今天我们就实现一个常见的场景：**多个任务使用同一个任务函数，但通过不同参数打印不同内容**。

我们以上一篇文章的工程为基础，复制 006，粘贴并重命名为 007：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a20a09392c3f45c183e1f2999d60661a.png)

### 1. 清理原有代码

先删除一些多余的代码：

```c
/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//开启GPIOC的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//GPIO引脚，赋值为第13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为高电平
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为低电平	
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0fe2edf96cdd4f61a21a4f16e1600875.png)

也删除原来的任务函数：

```c
void myTask1(void *arg)
{
	  uint8_t i = 0;
		while(1)
		{
			taskENTER_CRITICAL();
		  printf("myTask1 runnig\n");
			taskEXIT_CRITICAL();
			
			i++;
			if(i ==1)
			{
					vTaskDelete(myTaskHandler3);
			}
			if(i == 2)
			{
					vTaskDelete(NULL);
			}
			
					vTaskDelay(500);
		}
}

void myTask2(void *arg)
{
		while(1)
		{
			taskENTER_CRITICAL();
		  printf("myTask2 runnig\n");
			taskEXIT_CRITICAL();
			vTaskDelay(500);
		}
}

void myTask3(void *arg)
{
		while(1)
		{
			taskENTER_CRITICAL();
		  printf("myTask3 runnig\n");
			taskEXIT_CRITICAL();
			vTaskDelay(500);
		}
}
```

### 2. 创建通用打印任务函数

先创建一个通用的打印任务函数框架：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/18985212dfee41d29198d07b20d955c6.png)

```c
void myPrintf(void*arg)
{
		while(1)
		{
			
			
		}
}
```

### 3. 修改任务创建代码

修改任务创建代码，让所有任务都使用同一个任务函数：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e65334ade30e46799c7e960650e220ea.png)

```c
	xTaskCreate(myPrintf,"myTask1",128,NULL,2,&myTaskHandler1);
	xTaskCreate(myPrintf,"myTask2",128,NULL,2,&myTaskHandler2);
	xTaskCreate(myPrintf,"myTask3",128,NULL,2,&myTaskHandler3);
```

### 4. 完善任务函数

现在实现打印函数的功能。在使用任务参数前，需要将 `void*` 类型的参数转换为我们需要的类型：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1081f45e31234949ae4f8ff627c8a11e.png)

```c
void myPrintf(void*arg)
{
		char *str = arg;
		while(1)
		{
			taskENTER_CRITICAL();
			printf("%s\n",str);
			taskEXIT_CRITICAL();

		}
}
```

### 5. 定义任务参数

为每个任务定义不同的字符串参数：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/84ae0c72e8ee4b52a1094985551b0279.png)

```c
char str1[20] = "myTask1 running!";
char str2[20] = "myTask2 running!";
char str3[20] = "myTask3 running!";
```

### 6. 添加延时并将参数传入任务

在任务函数中添加延时，并将参数传入任务创建函数：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/47e70ed1e92548b29f8c4565958053e9.png)

```c
vTaskDelay(500);
```

```c
	xTaskCreate(myPrintf,"myTask1",128,str1,2,&myTaskHandler1);
	xTaskCreate(myPrintf,"myTask2",128,str2,2,&myTaskHandler2);
	xTaskCreate(myPrintf,"myTask3",128,str3,2,&myTaskHandler3);
```

### 7. 编译运行

编译后进入调试模式，点击运行，可以看到正常打印结果，成功实现了传入不同参数执行不同操作：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2b436f27c16046a281ea583add310179.png)

## 注意事项

这种操作需要注意的地方：打印函数最终是调用串口发送数据，这是一个相对耗时的操作。操作系统每毫秒切换一次任务，如果不进行保护，可能在任务一发送一半数据时突然切换到任务二，导致数据错乱甚至程序崩溃。

这就是为什么我们使用了 `taskENTER_CRITICAL()` 和 `taskEXIT_CRITICAL()` 临界区保护。**在多个任务使用同一个有限资源时，必须避免同时访问造成的冲突**。

## 任务参数的更多用法

除了上面展示的字符串参数，任务参数还有很多强大的用法：

1. **传递结构体**：可以传递包含多个参数的结构体，例如：

```c
typedef struct {
    uint8_t led_pin;
    uint16_t delay_ms;
    char* message;
} TaskParams_t;

// 使用示例
TaskParams_t task1_params = {LED_PIN_1, 500, "LED1 Toggle"};
xTaskCreate(ledToggleTask, "LED1Task", 128, &task1_params, 2, NULL);
```

2. **传递数组**：可以传递数组地址作为参数

3. **传递数值**：可以直接传递简单数值（需要类型转换）

```c
// 传递简单整数（需要类型转换）
xTaskCreate(countTask, "Count", 128, (void*)10, 2, NULL);

// 任务函数中
void countTask(void* arg) {
    int count = (int)arg;  // 将void*转回整数
    // 使用count...
}
```

4. **传递函数指针**：可以传递回调函数

## 完整代码示例

完整的示例代码可以在我的 GitHub 仓库找到：[https://github.com/Despacito0o/FreeRTOS/tree/main/Despacito/007](https://github.com/Despacito0o/FreeRTOS/tree/main/Despacito/007)

## 总结与展望

今天我们学习了 FreeRTOS 任务参数的基本使用方法，通过一个实例展示了如何使用同一个任务函数创建多个任务，并通过不同参数实现不同功能。

任务参数的灵活使用可以：
- 减少代码冗余，提高代码复用性
- 使任务函数更加通用和灵活
- 简化任务间数据传递

在下一篇文章中，我们将探讨 FreeRTOS 的任务通知机制，它是一种比信号量更轻量级、更高效的任务间通信方式。

如果你对 FreeRTOS 开发感兴趣，欢迎关注我的 GitHub 仓库：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)，里面有完整的从入门到精通的教程和示例代码！

感谢阅读，如有问题欢迎在评论区留言讨论！

---
**作者简介**：嵌入式开发爱好者，专注于 FreeRTOS 和 STM32 开发，分享嵌入式开发技术和经验。 