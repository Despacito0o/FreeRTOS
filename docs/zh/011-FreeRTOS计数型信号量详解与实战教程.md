# 深入理解操作系统：计数型信号量的原理与应用

> 📚 **作者推荐**：想系统学习FreeRTOS嵌入式开发？请访问我的[FreeRTOS开源学习库](https://github.com/Despacito0o/FreeRTOS)，内含从入门到精通的完整教程和实例代码！

信号量是操作系统中一种重要的同步机制，除了之前介绍的二值信号量（表示空或非空的状态）外，还有一种更为强大的变体——计数型信号量。顾名思义，计数型信号量内部维护一个计数值，而不仅仅是简单的二值状态。

## 计数型信号量的底层实现

从实现角度看，计数型信号量底层也是一个特殊的队列，但与二值信号量不同，计数型信号量的队列长度不是固定为1，而是等于设定的最大计数值。队列中的每个项目大小为0（仅用于标记该位置是否被占用），计数值实际上就是队列中非空项目的数量。

## 应用场景

### 1. 事件计数

当特定事件发生时，信号量计数值加1；当处理程序处理一个事件时，获取一个信号量，计数值减1。这就像不断增加和减少的工作队列：
- 新事件发生 → 待处理工作量+1
- 处理完一个事件 → 待处理工作量-1

### 2. 资源管理

以停车场为例，现代停车场入口通常有显示屏显示"剩余车位数"。假设停车场共有100个车位，显示剩余10个，这个"10"就是计数值：
- 一辆车进入 → 计数值减1（剩余9个）
- 一辆车驶出 → 计数值加1（剩余11个）

这种机制完美展示了计数型信号量如何用于资源管理——计数值直接表示可用资源数量。

## 计数型信号量的使用方法

使用非常简单，创建时调用create函数（包括动态和静态两种方式），此外还有获取计数值的专用函数。创建计数型信号量时需要指定两个参数：
- 最大计数值：信号量计数的上限
- 初始计数值：创建时的初始值

释放信号量时计数值加1（表示资源增加），获取信号量时计数值减1（表示资源减少）。

## 实验案例

为了演示计数型信号量的实际应用，我们设计了两个任务：
1. 任务1负责打印扫描：当打印task 1 running时，释放一个计数型信号量
2. 任务2每隔1秒获取一次计数型信号量，成功获取后打印当前计数值

### 1. 复制010二值信号量工程模板并重命名为011
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/153871b84b52443aac833286fcaf1e91.png)

### 2. 开启计数信号量的宏

在FreeRTOSConfig.h文件中，我们需要确保计数型信号量功能已启用：

```c
#define configUSE_COUNTING_SEMAPHORES           1  // 是否启用计数信号量
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7ed4d9a1be7946a0beb6cfc0e42c9a46.png)

### 3. 删除创建的二值信号量，创建计数信号量
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/054c514c12be494abac13f3462816f4d.png)

### 4. 深入理解计数型信号量的实现

查看源码，我们可以发现计数型信号量的创建函数定义如下：

```c
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
    #define xSemaphoreCreateCounting( uxMaxCount, uxInitialCount )    xQueueCreateCountingSemaphore( ( uxMaxCount ), ( uxInitialCount ) )
#endif
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e930c54caa1b40fc9ac254822de06f0a.png)

注意到该函数需要两个参数：
- `uxMaxCount`：最大计数值，对应于创建的队列长度
- `uxInitialCount`：初始计数值，表示初始时队列中的项目数

仔细观察底层实现函数 `xQueueCreateCountingSemaphore()`：

```c
#if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

    QueueHandle_t xQueueCreateCountingSemaphore( const UBaseType_t uxMaxCount,
                                                 const UBaseType_t uxInitialCount )
    {
        QueueHandle_t xHandle = NULL;

        if( ( uxMaxCount != 0 ) &&
            ( uxInitialCount <= uxMaxCount ) )
        {
            xHandle = xQueueGenericCreate( uxMaxCount, queueSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_COUNTING_SEMAPHORE );

            if( xHandle != NULL )
            {
                ( ( Queue_t * ) xHandle )->uxMessagesWaiting = uxInitialCount;

                traceCREATE_COUNTING_SEMAPHORE();
            }
            else
            {
                traceCREATE_COUNTING_SEMAPHORE_FAILED();
            }
        }
        else
        {
            configASSERT( xHandle );
            mtCOVERAGE_TEST_MARKER();
        }

        return xHandle;
    }

#endif /* ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
```

关键在于，底层创建了一个长度为`uxMaxCount`的队列，但每个队列项的大小为0（`queueSEMAPHORE_QUEUE_ITEM_LENGTH`宏定义值为0）。这些队列项仅用来标记位置是否被占用，而`uxMessagesWaiting`成员则用来跟踪队列中非空项的数量，即计数型信号量的计数值。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ef6cdbf965024c2e8ae69411e48e0509.png)

### 5. 创建并初始化计数型信号量

在main.c中，我们需要声明计数型信号量的句柄并创建信号量：

```c
UBaseType_t count = 0;
	
sem_count_Handler = xSemaphoreCreateCounting(100,0);  //创建计数型信号量
	
if(sem_count_Handler == NULL)
{
    printf("Semaphore creation failed\r\n");
}
else
{
    count = uxSemaphoreGetCount(sem_count_Handler);
    printf("The creation of a counting semaphore is successful, and the initial count value is =%lu\r\n",count);
}	
```

我们使用`uxSemaphoreGetCount`函数获取计数型信号量的当前计数值。查看源码可知，它实际上是调用了`uxQueueMessagesWaiting`函数：

```c
// semphr.h
#define uxSemaphoreGetCount( xSemaphore )           uxQueueMessagesWaiting( ( QueueHandle_t ) ( xSemaphore ) )

// queue.c
UBaseType_t uxQueueMessagesWaiting( const QueueHandle_t xQueue )
{
    UBaseType_t uxReturn;

    configASSERT( xQueue );

    taskENTER_CRITICAL();
    {
        uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;
    }
    taskEXIT_CRITICAL();

    return uxReturn;
} /*lint !e818 Pointer cannot be declared const as xQueue is a typedef not pointer. */
```

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5187d7e89c7843b3b4425e0ec26c116e.png)

### 6. 信号量的释放与获取

计数型信号量的操作机制：
- 释放信号量（`xSemaphoreGive`）：计数值加1，表示资源数增加
- 获取信号量（`xSemaphoreTake`）：计数值减1，表示资源数减少

按照我们的实验设计，任务1在按键中断中释放信号量：

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5857a3ae765f4f7ca5e61dc3701084bc.png)

任务2每秒获取一次信号量并打印当前计数值：

```c
void myTask2(void *arg)
{
    UBaseType_t currnet_count = 0;
    BaseType_t res = 0;
    while (1)
    {
        /* 获取计数型信号量 */
        res = xSemaphoreTake(sem_count_Handler,portMAX_DELAY);
        if(res == pdPASS)
        {
            printf("Task2 release successful\r\n"); 
        }
        else 
        {
            printf("Task2 release failed\r\n");   
        }
				
        currnet_count = uxSemaphoreGetCount(sem_count_Handler);
        printf("Current Count Value =%lu\r\n", currnet_count);
        
        vTaskDelay(1000);
    }
}
```

在这个任务中，我们:
1. 尝试获取信号量（如果队列为空，将阻塞等待）
2. 获取成功后，打印成功信息
3. 使用`uxSemaphoreGetCount`获取并打印当前的计数值
4. 延时1秒后继续下一次循环

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ecd3e05b97904e40b727401aafef0606.png)

### 7. 调试运行结果

编译并下载程序，运行后可以看到如下结果：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5e36d0f3f93c4c8a8400ce3b3a876846.png)

## 计数型信号量的进阶应用

除了基本的资源管理和事件计数，计数型信号量还有一些高级应用场景：

### 1. 多生产者-多消费者模型

在多个任务可能产生事件，多个任务需要处理这些事件的场景中，计数型信号量可以优雅地实现任务间的协调。

### 2. 令牌桶算法实现

用于流量控制的令牌桶算法可以使用计数型信号量来实现，其中计数值代表可用的令牌数量。

### 3. 资源池管理

当需要管理一组相同类型的资源（如内存块、连接句柄等）时，计数型信号量可以用来跟踪可用资源的数量。

## 信号量使用注意事项

1. **优先级反转**：在使用信号量时要注意可能出现的优先级反转问题，可以考虑使用优先级继承（FreeRTOS提供的互斥量支持此特性）。

2. **递归获取**：标准信号量不支持递归获取，如果需要这个特性，应使用递归互斥量。

3. **中断中使用**：在中断服务例程中应使用专门的FromISR版本函数，如`xSemaphoreGiveFromISR()`。

4. **计数上限**：注意设置合理的最大计数值，既要满足需求，又不要浪费过多RAM。

## 总结

计数型信号量是FreeRTOS中一个非常强大的同步原语，适用于多种场景，尤其是资源管理和事件计数。通过本文的实验，我们深入理解了其实现原理和使用方法。希望这个示例对你理解计数型信号量的工作原理和应用场景有所帮助。

如果你想深入学习FreeRTOS，欢迎访问我的GitHub项目库：[FreeRTOS学习资源](https://github.com/Despacito0o/FreeRTOS)，里面有从入门到精通的完整教程和示例代码，包括详细的文档和实践项目。该资源库涵盖了FreeRTOS的各种核心功能，从任务管理到各类同步原语，适合初学者和有一定经验的开发者学习和参考。 