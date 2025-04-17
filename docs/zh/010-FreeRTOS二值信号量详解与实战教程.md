# FreeRTOS二值信号量详解与实战教程

> 📚 **作者推荐**：想系统学习FreeRTOS嵌入式开发？请访问我的[FreeRTOS开源学习库](https://github.com/Despacito0o/FreeRTOS)，内含从入门到精通的完整教程和实例代码！

## 1. 二值信号量核心概念解析

二值信号量(Binary Semaphore)是FreeRTOS提供的一种简单而强大的同步工具，它只有两个可能值：0或1。这种简单特性使它成为嵌入式系统中极其实用的同步原语。

💡 **形象理解**：二值信号量就像公共卫生间的占用指示灯：
- 绿灯(值为1)：资源可用，任务可以获取
- 红灯(值为0)：资源被占用，需要等待

## 2. 二值信号量三大应用场景

### 2.1 资源互斥访问

当多个任务需要访问共享资源（如全局变量、外设）时，二值信号量能确保任一时刻只有一个任务能访问该资源：

```c
// 任务想要访问共享资源时
xSemaphoreTake(xMutexSemaphore, portMAX_DELAY);  // 获取访问权
// 访问共享资源
xSemaphoreGive(xMutexSemaphore);  // 释放访问权
```

### 2.2 任务同步控制

实现"任务A必须在任务B之前完成"的先后依赖关系：

```c
// 任务A完成工作后
xSemaphoreGive(xSyncSemaphore);  // 发出"我完成了"的信号

// 任务B开始前
xSemaphoreTake(xSyncSemaphore, portMAX_DELAY);  // 等待任务A完成
// 开始任务B的工作
```

### 2.3 任务阻塞与唤醒机制

FreeRTOS使用优先级管理等待同一信号量的多个任务：
- 不同优先级：高优先级任务优先获得信号量
- 相同优先级：先等待的任务先获得信号量

## 3. 二值信号量的底层实现揭秘

> 🔍 **底层原理**：二值信号量实质上是一个**队列长度为1的特殊队列**！

在FreeRTOS内核中：
- 队列为空 → 信号量值为0（不可用）
- 队列有元素 → 信号量值为1（可用）

这种实现使二值信号量具有队列的所有优势，包括任务阻塞和优先级继承等特性。

## 4. 二值信号量核心API详解

| 函数 | 描述 | 使用场景 |
|------|------|---------|
| `vSemaphoreCreateBinary()` | 创建二值信号量（创建后自动释放一次） | 需要初始状态为"可用"的场景 |
| `xSemaphoreCreateBinary()` | 创建二值信号量（不会自动释放） | 需要初始状态为"不可用"的场景 |
| `xSemaphoreTake()` | 获取信号量（将信号量由1变为0） | 任务中获取信号量 |
| `xSemaphoreGive()` | 释放信号量（将信号量由0变为1） | 任务中释放信号量 |
| `xSemaphoreTakeFromISR()` | 中断中获取信号量 | 中断服务程序中获取信号量 |
| `xSemaphoreGiveFromISR()` | 中断中释放信号量 | 中断服务程序中释放信号量 |

## 5. 二值信号量实战示例教程

下面通过一个完整示例展示二值信号量的使用方法。我们创建两个任务：
- 任务1：定期释放信号量
- 任务2：等待并获取信号量，成功后打印提示

### 5.1 代码实现步骤

1. **准备工程**：复制006多任务创建模板，并重命名为010
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2445a95694804bbba59bcc1616005254.png)

2. **删除不必要的代码**：

```cpp
#include "queue.h"
```

```cpp
TaskHandle_t myTaskHandler3;
```

```cpp
struct print{
	int cnt;
	char data[20];
};
```

```cpp
		struct print data = {
			.data = "myTask1 runnig"
			};
```

```cpp
			data.cnt++;
			xQueueSend(myPrintfQueueHandler, &data, 0);
```

```cpp
struct print data = {
			.data = "myTask2 runnig"
		};
```

```cpp
			data.cnt++;
			xQueueSend(myPrintfQueueHandler, &data, 0);
```

```cpp
void myTask3(void *arg)
{
		struct print data;
		BaseType_t xStatus;
		while(1)
		{
			xStatus = xQueueReceive(myPrintfQueueHandler, &data, portMAX_DELAY);
			if(xStatus == pdPASS)
			{
			taskENTER_CRITICAL();
				printf("%s:%d\n", data.data,data.cnt);
			taskEXIT_CRITICAL();
			}
//			vTaskDelay(500);
		}
}
```

```cpp
	xTaskCreate(myTask3,"myTask3",128,NULL,2,&myTaskHandler3);
```

```cpp
	myPrintfQueueHandler = xQueueCreate(2,sizeof(struct print));
```

3. **导入信号量头文件**：
```cpp
#include "semphr.h" //信号量相关的头文件
```

4. **创建二值信号量**：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d14c82cb481943ebbc78876bcb876068.png)

> **深入理解**：为什么选择v开头的创建函数？

查看`vSemaphoreCreateBinary`定义，理解其内部实现：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e4fb63890a7f486aae9065820658a347.png)

```cpp
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define vSemaphoreCreateBinary( xSemaphore )                                                                                     \
    {                                                                                                                                \
        ( xSemaphore ) = xQueueGenericCreate( ( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_BINARY_SEMAPHORE ); \
        if( ( xSemaphore ) != NULL )                                                                                                 \
        {                                                                                                                            \
            ( void ) xSemaphoreGive( ( xSemaphore ) );                                                                               \
        }                                                                                                                            \
    }
#endif
```

从源码可以看出：
- 它首先创建一个长度为1的队列
- 创建成功后，立即执行`xSemaphoreGive`释放信号量，使其初始值为1（可用状态）
- 这正是我们需要的初始状态！

对比另一个创建函数：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/573f12740d4c4a9b85cb675eea647fc8.png)

```c
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define xSemaphoreCreateBinary()    xQueueGenericCreate( ( UBaseType_t ) 1, semSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_BINARY_SEMAPHORE )
#endif
```

`xSemaphoreCreateBinary`仅创建队列，不自动释放，初始值为0（不可用状态）。

5. **声明信号量句柄**：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6400ed2a2483423ba97ae7b28d41c1eb.png)

6. **创建失败检测**：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7a8bdb5a6b654ed894c3d843b7efef0b.png)

7. **编写Task1（释放信号量）**：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7890f1264e2f4d5ba63dd272761516ca.png)

```c
void myTask1(void *arg)
{
		BaseType_t res = 0;

		while(1)
		{
			taskENTER_CRITICAL();
			  	printf("myTask1 runnig\n");
		
            /* 释放二值信号量 */
            res = xSemaphoreGive(myPrintfQueueHandler);
            if(res == pdPASS)
            {
                printf("Task1 release successful\r\n");
            }
            else 
            {
                printf("Task1 release failed\r\n");
            }
						taskEXIT_CRITICAL();
        vTaskDelay(500);
		}
}
```

> 📝 **说明**：这里使用临界区保护打印操作，防止多任务打印导致的输出混乱。

查看`xSemaphoreGive`定义：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8bea4eac9e04446391b6113090a54fdf.png)

```c
#define xSemaphoreGive( xSemaphore )    xQueueGenericSend( ( QueueHandle_t ) ( xSemaphore ), NULL, semGIVE_BLOCK_TIME, queueSEND_TO_BACK )
```

本质上是向队列发送一个空数据！

8. **编写Task2（获取信号量）**：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/77eaa0f9eaf743c39d20ec0a97c24531.png)

```c
void myTask2(void *arg)
{
 BaseType_t res = 0;
    while (1)
    {
        /* 获取二值信号量 */
        res = xSemaphoreTake(myPrintfQueueHandler,portMAX_DELAY);
        if(res == pdPASS)
        {
            printf("Task2 release successful\r\n"); 
        }
        else 
        {
            printf("Task2 release failed\r\n");   
        }

    }
}
```

查看`xSemaphoreTake`定义：
```c
#define xSemaphoreTake( xSemaphore, xBlockTime )    xQueueSemaphoreTake( ( xSemaphore ), ( xBlockTime ) )
```

9. **编译、调试、运行**：输出如下内容表示成功
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7f59fc9dd436440ab4147a077078c468.png)

### 5.2 实例代码深度解析

1. **创建信号量**：使用`vSemaphoreCreateBinary()`创建二值信号量，初始值为1（可用）。

2. **Task1工作流程**：
   - 进入临界区（防止打印混乱）
   - 打印运行状态信息
   - 释放信号量（使值为1）
   - 打印释放结果
   - 退出临界区
   - 延时500ms

3. **Task2工作流程**：
   - 尝试获取信号量（将值从1变为0）
   - 若成功（返回pdPASS），打印成功信息
   - 若失败，打印失败信息
   - 循环执行（无延时）

4. **portMAX_DELAY参数**：表示无限等待，直到获取到信号量才继续执行。

### 5.3 运行结果分析

执行程序后，我们观察到典型的执行顺序：

1. 系统启动，Task2立即获取到信号量（因初始值为1）并打印成功信息。
2. 信号量值变为0，Task2再次尝试获取时进入阻塞状态。
3. Task1执行，释放信号量，值变为1。
4. Task2被唤醒，获取信号量，打印成功信息。
5. 周而复始，形成Task1释放→Task2获取的循环。

> 🔍 **现象解释**：为什么有时Task1的释放成功信息会出现在Task2的获取成功信息之后？
> 
> 这是因为任务调度的时机。当Task1释放信号量后，如果Task2优先级高于Task1，系统会立即切换到Task2执行，导致Task2的打印先于Task1的释放成功信息。

## 6. 二值信号量高级特性与注意事项

1. **跨任务操作**：信号量的获取和释放可以在不同任务间进行，这是实现任务同步的基础。

2. **初始状态选择**：
   - 使用`vSemaphoreCreateBinary()`：初始状态为"可用"（值为1）
   - 使用`xSemaphoreCreateBinary()`：初始状态为"不可用"（值为0）

3. **超时参数**：
   - `portMAX_DELAY`：永久等待
   - `0`：不等待，立即返回
   - 其他值：等待指定时间（单位为tick）

4. **中断中使用**：中断服务程序中必须使用`FromISR`结尾的函数版本。

## 7. 总结与实践建议

二值信号量是FreeRTOS中极为强大且使用简单的同步工具，适用于互斥访问和任务同步场景。通过本教程的学习，你应该已经掌握了：

✅ 二值信号量的基本概念与原理  
✅ 信号量的创建、获取与释放操作  
✅ 常见应用场景与实现方法  
✅ 底层实现机制与高级特性  

### 应用建议

1. **选择合适的场景**：二值信号量适合简单的同步场景，复杂场景考虑计数信号量或事件组。

2. **避免优先级反转**：在互斥访问场景中，考虑使用互斥量(Mutex)代替二值信号量，因为互斥量支持优先级继承机制。

3. **防止死锁**：确保获取信号量的任务最终会释放它，避免系统陷入死锁。

---

> 📚 **想深入学习FreeRTOS？**  
> 我整理了一套完整的[FreeRTOS开发学习资源](https://github.com/Despacito0o/FreeRTOS)，从环境搭建到高级特性应用，包含大量实例代码和详细教程。欢迎star和fork！

**扩展思考**：在什么情况下，你会选择使用二值信号量而非互斥量(Mutex)或计数信号量？欢迎在评论区讨论！ 