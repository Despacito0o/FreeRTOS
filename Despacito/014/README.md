# FreeRTOS队列集（Queue Set）实战教程：多源数据同步处理

## 前言

在实际的嵌入式系统开发中，我们常常需要处理来自多个队列或信号量的数据。如果分别监听多个队列，不仅代码复杂度增加，还可能导致某些实时性问题。而FreeRTOS的队列集（Queue Sets）正是解决这一问题的利器。本文将通过实例详解队列集的工作原理及使用方法。

> 🔗 更多FreeRTOS学习资源，请访问我的完整学习库：[FreeRTOS从入门到精通](https://github.com/Despacito0o/FreeRTOS)，里面包含从基础到高级的全面教程！

## 什么是队列集（Queue Sets）？

队列集（英文名为Queue Set）是FreeRTOS提供的一种数据结构，用于统一管理多个队列和信号量。它允许任务同时等待多个队列或信号量，只要其中任何一个有数据可用，任务就能被唤醒并处理相应数据。

### 为什么需要队列集？

想象这样一个场景：一个任务需要同时监听两个不同的数据源（一个温度队列和一个湿度队列）。传统方法中，我们会这样编写代码：

```c
// 先读取温度队列
if(xQueueReceive(tempQueue, &tempData, portMAX_DELAY) == pdTRUE) {
    // 处理温度数据
}

// 再读取湿度队列
if(xQueueReceive(humidQueue, &humidData, portMAX_DELAY) == pdTRUE) {
    // 处理湿度数据
}
```

这种方法存在严重问题：如果温度队列一直没有数据，那么任务会一直阻塞在第一个`xQueueReceive`，即使湿度队列中已经有数据也无法处理！

队列集完美解决了这个问题。它允许任务等待多个队列，只要其中任何一个队列有数据，任务就能被唤醒处理。

## 队列集实战演示

我们通过一个实例来演示队列集的使用。这个例子中，我们会创建：
- 一个普通的消息队列（用于接收按键信息）
- 一个二值信号量（用于同步）
- 一个队列集（用于统一管理上述两个对象）

然后通过两个任务来演示队列集的工作方式：
- 任务1：扫描按键，向队列发送数据或释放信号量
- 任务2：从队列集读取消息，并根据源头打印对应信息

### 1. 拷贝工程模板

首先，我们基于之前的消息队列示例创建新工程：

```
复制013并重命名为014
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4af6919a522249be9ac338e8137385c6.png)

### 2. 导入按键驱动

导入key.c和key.h并在main函数添加`#include "key.h"`

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9744140db16744268f00c974a98f41a6.png)

key.h文件内容：

```c
#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

#define KEY1_Pin         GPIO_Pin_1
#define KEY1_GPIO_Port   GPIOB
#define KEY2_Pin         GPIO_Pin_11
#define KEY2_GPIO_Port   GPIOB
#define KEY3_Pin         GPIO_Pin_10
#define KEY3_GPIO_Port   GPIOB
#define KEY4_Pin         GPIO_Pin_11
#define KEY4_GPIO_Port   GPIOF

#define KEY1        GPIO_ReadInputDataBit(KEY1_GPIO_Port, KEY1_Pin)   /* 读取KEY1引脚状态（SW3） */
#define KEY2        GPIO_ReadInputDataBit(KEY2_GPIO_Port, KEY2_Pin)   /* 读取KEY2引脚状态（SW4） */
#define KEY3        GPIO_ReadInputDataBit(KEY3_GPIO_Port, KEY3_Pin)   /* 读取KEY3引脚状态（SW5） */
#define KEY4        GPIO_ReadInputDataBit(KEY4_GPIO_Port, KEY4_Pin)   /* 读取KEY4引脚状态（SW6） */


#define KEY1_PRESS    1              
#define KEY2_PRESS    2              
#define KEY3_PRESS    3              
#define KEY4_PRESS    4              


uint8_t Key_Detect(void);


#endif
```

key.c文件内容：

```c
#include "Key.h"
#include "delay.h"

/**
 * @description: 检测按键
 * @return {*} 按下的按键值
 */
uint8_t Key_Detect(void)
{
    uint8_t res = 0;
    if (KEY1 == RESET || KEY2 == RESET || KEY3 == SET || KEY4 == SET )  
    {
        Delay_ms(10);           /* 去抖动 */
        /* 按这个顺序，如果多个按键同时按，优先级：KEY4>KEY3>KEY2>KEY1 */
        if (KEY1 == RESET)  res = KEY1_PRESS;
        if (KEY2 == RESET)  res = KEY2_PRESS;
        if (KEY3 == SET)  res = KEY3_PRESS;
        if (KEY4 == SET)  res = KEY4_PRESS;
    }
    return res;
}
```

### 3. 添加FreeRTOS相关头文件

要使用队列集，我们需要引入队列和信号量的头文件：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cfd55e3b93464293aada55857d9fb1a1.png)

### 4. 创建队列和二值信号量

首先，我们声明一个普通队列：

```c
QueueHandle_t queue1;
```

然后创建这个队列：

```c
queue1 = xQueueCreate(2,sizeof(uint8_t));
if (queue1 != NULL)
{
    printf("queue1创建成功\r\n");
}
else
{
    printf("queue1创建失败\r\n");
}	
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6aa2927b6a0f419fbc16891dbb0e91d1.png)

接着创建一个二值信号量（它在底层也是通过队列实现的）：

```c
QueueHandle_t queue2;
```

```c
queue2 = xSemaphoreCreateBinary();
if (queue2 != NULL)
{
    printf("二值信号量创建成功\r\n");
}
else
{
    printf("二值信号量创建失败\r\n");
}
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/40cbeff8cad842eab034ce2df84e89d7.png)

### 5. 创建队列集

要使用队列集功能，首先要确保在FreeRTOSConfig.h中开启了相关宏定义：

```c
#define configUSE_QUEUE_SETS 1  // 启用队列集合
```

然后声明队列集句柄：

```c
QueueSetHandle_t myPrintfQueueHandler;
```

创建队列集：

```c
myPrintfQueueHandler = xQueueCreateSet(2);
	
if (myPrintfQueueHandler != NULL)
{
    printf("创建队列集成功\r\n");
}
```

### 6. 将队列和信号量添加到队列集

声明用于存储操作结果的变量：

```c
BaseType_t res = 0;
```

将普通队列添加到队列集：

```c
res = xQueueAddToSet(queue1, myPrintfQueueHandler);
if (res == pdPASS)
{
    printf("queue1添加到队列集成功\r\n");
}
```

将二值信号量添加到队列集：

```c
res = xQueueAddToSet(queue2, myPrintfQueueHandler);
if (res == pdPASS)
{
    printf("二值信号量添加到队列集成功\r\n");
}
```

> **重要提示**：队列或信号量只有在为空时才能被添加到队列集，否则添加会失败！

### 7. 实现任务1：发送数据和释放信号量

任务1负责检测按键，并根据按键执行不同操作：
- 按键1按下：向queue1发送按键值
- 按键2按下：释放二值信号量

```c
void myTask1(void *arg)
{
    uint8_t key = 0;
    uint8_t res = 0;
    while (1)
    {
        key = Key_Detect();
        if (key == KEY1_PRESS)
        {
            /* 将key的编号写入queue1 */
            res = xQueueSend(queue1, &key, portMAX_DELAY);
            if (res == pdPASS)
            {
                printf("往queue1发送数据[%d]成功\r\n", key);
            }
            else
            {
                printf("往queue1发送数据失败\r\n");
            }
        }
        else if (key == KEY2_PRESS)
        {
            /* 释放信号量 */
            res = xSemaphoreGive(queue2);
            if (res == pdPASS)
            {
                printf("释放信号量成功\r\n");
            }
            else
            {
                printf("释放信号量失败\r\n");
            }
        }

        vTaskDelay(500);
    }
}
```

### 8. 实现任务2：从队列集读取消息

任务2使用队列集监听所有消息源，并根据消息来源执行不同处理：

```c
void myTask2(void *arg)
{
    QueueSetMemberHandle_t member_handle;
    uint8_t receive = 0;
    uint8_t res = 0;
    while (1)
    {
        /* 查看哪个队列有数据来了 */
        member_handle = xQueueSelectFromSet(myPrintfQueueHandler, portMAX_DELAY);
        /* 根据对应的队列，去获取数据 */
        if (member_handle == queue1)
        {
            res = xQueueReceive(queue1, &receive, portMAX_DELAY);
            if (res == pdPASS)
            {
                printf("task2从queue1成功读取数据[%d]\r\n", receive);
            }
            else
            {
                printf("task2从queue1读取数据失败\r\n");
            }
        }
        else if (member_handle == queue2)
        {
            res = xSemaphoreTake(queue2,portMAX_DELAY);
            if(res == pdPASS)
            {
                printf("获取信号量成功\r\n");
            }
        }
        else 
        {
            printf("从队列集获取信息失败\r\n");
        }
    }
}
```

### 9. 编译和测试

编译并烧录程序到开发板，通过串口观察运行结果：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/882a4f3a15ed4066b8f30d330acf2e7c.png)

## 队列集的高级应用

### 1. 队列集容量计算

创建队列集时，需要指定其容量，这个容量至少应该等于所有添加到队列集中的队列和信号量的总容量：

```c
// 例如：
// queue1容量为2，queue2容量为1（二值信号量）
// 则队列集容量至少为2+1=3
QueueSetHandle_t queueSet = xQueueCreateSet(3);
```

### 2. 多种信号量的混合使用

队列集不仅可以管理普通队列和二值信号量，还可以同时管理：
- 计数信号量
- 互斥量
- 递归互斥量（注意：在某些FreeRTOS版本中可能不支持）

例如：

```c
QueueHandle_t normalQueue = xQueueCreate(5, sizeof(uint32_t));
SemaphoreHandle_t binarySem = xSemaphoreCreateBinary();
SemaphoreHandle_t countingSem = xSemaphoreCreateCounting(10, 0);
SemaphoreHandle_t mutex = xSemaphoreCreateMutex();

QueueSetHandle_t mixedSet = xQueueCreateSet(5 + 1 + 10 + 1);
xQueueAddToSet(normalQueue, mixedSet);
xQueueAddToSet(binarySem, mixedSet);
xQueueAddToSet(countingSem, mixedSet);
xQueueAddToSet(mutex, mixedSet);
```

### 3. 在中断中使用队列集

FreeRTOS也提供了在中断服务例程（ISR）中使用队列集的API：

```c
QueueSetMemberHandle_t xQueueSelectFromSetFromISR(QueueSetHandle_t xQueueSet);
```

使用示例：

```c
void EXTI0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        QueueSetMemberHandle_t activeMember = xQueueSelectFromSetFromISR(myQueueSet);
        if(activeMember == myQueue)
        {
            uint32_t data;
            xQueueReceiveFromISR(myQueue, &data, &xHigherPriorityTaskWoken);
            // 处理数据...
        }
        
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
    
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
```

## 队列集注意事项

1. **添加条件**：队列或信号量只有在为空时才能被添加到队列集中
2. **删除问题**：如果删除了队列集中的某个队列，记得先用`xQueueRemoveFromSet()`将其从队列集中移除
3. **容量计算**：队列集容量必须大于等于所有成员队列和信号量的总容量
4. **操作顺序**：从队列集获取到活动队列后，仍需调用对应的`xQueueReceive`或`xSemaphoreTake`获取实际数据
5. **性能影响**：队列集虽然方便，但会带来一定性能开销，在资源非常受限的系统中需谨慎使用

## 总结

队列集是FreeRTOS提供的一个强大功能，通过统一管理多个队列和信号量，让任务能够同时等待多个事件源的消息，极大简化了多事件源处理的编程复杂度。对于需要处理多种不同类型数据的复杂实时系统，队列集是一个不可多得的利器。

如果你想深入学习FreeRTOS的更多高级特性，欢迎访问我的GitHub仓库：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)，那里有从入门到精通的全面FreeRTOS学习资源，包括详细的示例项目、移植教程和中英双语文档，适合初学者和专业开发者！

---

觉得本文有帮助？点赞、收藏、关注一键三连支持一下吧！如有疑问欢迎在评论区留言交流！

## 调试工具下载

串口调试助手和烧入器通过网盘分享：
链接: [https://pan.baidu.com/s/1DiC2NMzd6zYbYmaaE4mVtQ?pwd=uarg](https://pan.baidu.com/s/1DiC2NMzd6zYbYmaaE4mVtQ?pwd=uarg) 
提取码: uarg 