# FreeRTOS 队列通信示例

## 简介

本示例演示了如何在FreeRTOS中使用队列（Queue）进行任务间通信。队列是FreeRTOS提供的一种数据传输机制，可用于任务间数据传递，也可用于任务与中断间的数据传递。本示例展示了通过队列实现任务功能分离，使代码结构更加清晰。

## 功能特点

- 演示队列的基本创建和使用方法
- 展示任务间通过队列传递字符串消息
- 实现使用结构体通过队列传递多种类型数据
- 展示生产者-消费者模式的任务分离

## 工程概述

本项目基于STM32F103系列微控制器，使用标准外设库(StdPeriph)开发。工程通过队列实现了多个任务之间的通信，其中：

- `myTask1`和`myTask2`作为生产者任务，负责产生数据并将数据写入队列
- `myTask3`作为消费者任务，负责从队列读取数据并显示

这种结构使得任务逻辑层次更加清晰，各任务可专注于自己的功能，提高代码可维护性。

## 关键代码

### 1. 队列创建

```c
/* 创建一个队列，可存放2个消息，每个消息大小为20字节 */
myPrintfQueueHandler = xQueueCreate(2, 20);
```

### 2. 发送数据到队列

```c
/* 基本字符串发送 */
char data[20] = "myTask1 running";
xQueueSend(myPrintfQueueHandler, data, 0);

/* 结构体数据发送 */
struct print data = {
    .data = "myTask1 running"
};
data.cnt++;
xQueueSend(myPrintfQueueHandler, &data, 0);
```

### 3. 从队列接收数据

```c
/* 从队列接收数据并处理 */
BaseType_t xStatus;
xStatus = xQueueReceive(myPrintfQueueHandler, &data, portMAX_DELAY);
if(xStatus == pdPASS)
{
    taskENTER_CRITICAL();
    printf("%s:%d\n", data.data, data.cnt);
    taskEXIT_CRITICAL();
}
```

## 结构体传输

本示例也展示了如何通过队列传输结构体数据，这对于需要传递多种参数的场景非常有用：

```c
/* 定义结构体 */
struct print {
    char data[20];
    int cnt;
};

/* 修改队列创建，数据大小为结构体大小 */
myPrintfQueueHandler = xQueueCreate(2, sizeof(struct print));
```

## 运行现象

- 调试运行后，串口终端将显示来自任务1和任务2的数据
- 在结构体传输模式下，将显示任务名和计数值
- 任务3会按照FIFO顺序处理来自任务1和任务2的数据

## 注意事项

1. 队列满时，使用的阻塞时间参数决定了任务的行为：
   - 设为0时，无法写入立即返回
   - 设为portMAX_DELAY时，将一直阻塞到能够写入
   
2. 队列空时，接收数据的阻塞特性类似
   
3. 使用结构体时，队列中数据大小需与结构体大小一致

## 扩展思考

1. 如何处理队列满的情况？
2. 如何在中断中使用队列？
3. 如何使用队列实现更复杂的任务间通信模式？

## 相关函数API

- `xQueueCreate()`: 创建队列
- `xQueueSend()`: 发送数据到队列尾部
- `xQueueSendToFront()`: 发送数据到队列头部
- `xQueueReceive()`: 从队列读取数据
- `xQueuePeek()`: 查看队列数据但不移除
- `uxQueueMessagesWaiting()`: 获取队列中消息数量 