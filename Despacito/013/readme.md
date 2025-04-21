# FreeRTOS互斥信号量解决优先级翻转实战教程

大家好！今天我们来深入探讨FreeRTOS中的优先级翻转问题，并通过互斥信号量来解决这个问题。上一篇文章我们已经了解了优先级翻转的现象，今天我们将动手实践，通过代码对比来直观感受互斥信号量的作用。

> 🚀 本文是FreeRTOS学习系列的一部分。完整教程请访问我的GitHub仓库：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)，从入门到精通的全面指南！

## 一、互斥信号量解决优先级翻转

了解完互斥信号量可以解决优先级翻转的问题，我们来实际体验一下。我们将使用前面优先级翻转的案例，把它改造成使用互斥信号量的版本，然后观察效果。

首先，我们直接拷贝之前的012工程，重命名为013：

![工程复制](https://i-blog.csdnimg.cn/direct/bc29c57ff3584ff8bfd0795a1cfd31d8.png)

## 二、从二值信号量切换到互斥信号量

我们有三个任务，三个任务的逻辑不需要修改，只需要将创建的信号量类型从二值信号量换成互斥信号量。

要使用互斥信号量，必须先在FreeRTOSConfig.h中开启相关配置：

```c
#define configUSE_MUTEXES                       1  // 是否启用互斥信号量
```

![启用互斥信号量](https://i-blog.csdnimg.cn/direct/9beb94dc079540798c3e5171d54b2760.png)

## 三、创建互斥信号量

接下来，我们将二值信号量的创建函数替换为互斥信号量的创建函数：

```c
xSemaphoreCreateMutex();
```

![创建互斥信号量](https://i-blog.csdnimg.cn/direct/b194ec01636643ada225a69f76887c88.png)

让我们深入看看这个函数的实现：

```c
#if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_MUTEXES == 1 ) )
    #define xSemaphoreCreateMutex()    xQueueCreateMutex( queueQUEUE_TYPE_MUTEX )
#endif
```

进一步查看`xQueueCreateMutex`函数的实现：

```c
#if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

    QueueHandle_t xQueueCreateMutex( const uint8_t ucQueueType )
    {
        QueueHandle_t xNewQueue;
        const UBaseType_t uxMutexLength = ( UBaseType_t ) 1, uxMutexSize = ( UBaseType_t ) 0;

        xNewQueue = xQueueGenericCreate( uxMutexLength, uxMutexSize, ucQueueType );
        prvInitialiseMutex( ( Queue_t * ) xNewQueue );

        return xNewQueue;
    }

#endif /* configUSE_MUTEXES */
```

最后看看`prvInitialiseMutex`函数：

```c
static void prvInitialiseMutex( Queue_t * pxNewQueue )
{
    if( pxNewQueue != NULL )
    {
        /* 队列创建函数会为通用队列正确设置所有队列结构成员，
         * 但这个函数是创建互斥量。覆盖那些需要不同设置的成员 - 
         * 特别是优先级继承所需的信息。 */
        pxNewQueue->u.xSemaphore.xMutexHolder = NULL;
        pxNewQueue->uxQueueType = queueQUEUE_IS_MUTEX;

        /* 为递归互斥量做准备 */
        pxNewQueue->u.xSemaphore.uxRecursiveCallCount = 0;

        traceCREATE_MUTEX( pxNewQueue );

        /* 以预期状态开始信号量 */
        ( void ) xQueueGenericSend( pxNewQueue, NULL, ( TickType_t ) 0U, queueSEND_TO_BACK );
    }
    else
    {
        traceCREATE_MUTEX_FAILED();
    }
}
```

可以看到，创建完互斥信号量后，会自动调用一次`xQueueGenericSend`，相当于主动释放了一次资源，这与我们之前介绍的"互斥信号量默认创建完会自动释放一次资源"一致。

因此，我们只需要简单地替换创建函数即可：

```c
myPrintfQueueHandler = xSemaphoreCreateMutex(); // 创建互斥信号量，创建成功会自动释放一次信号量
```

![替换信号量创建函数](https://i-blog.csdnimg.cn/direct/2336f9af4efc4d609a25ceb5c44afd0b.png)

## 四、编译调试，观察现象

我们编译、调试、运行代码：

![编译运行](https://i-blog.csdnimg.cn/direct/c0e64489b04747f99e2182837a57b84c.png)

现在，我们通过串口输出分析互斥信号量的效果。

在没有使用互斥信号量的情况下，当高优先级任务3尝试获取已被低优先级任务1占用的信号量时，任务3会阻塞；此时中优先级任务2可以抢占任务1执行，导致任务1无法快速释放信号量，任务3长时间等待，出现优先级翻转。

而使用互斥信号量后，我们可以看到：当任务3（高优先级）尝试获取被任务1（低优先级）持有的互斥信号量时，任务1的优先级会被临时提升到与任务3相同的级别，这样任务2（中优先级）就无法抢断任务1的执行了。

通过串口输出，我们可以发现：

1. 任务1获取互斥信号量后开始执行
2. 当任务3尝试获取同一个互斥信号量时，任务1的优先级被提升
3. 此时任务2无法抢占任务1，任务1可以继续执行并最终释放互斥信号量
4. 任务1释放互斥信号量后，其优先级被恢复为原来的值
5. 任务3获取互斥信号量并执行

这就验证了互斥信号量通过优先级继承机制解决优先级翻转的工作原理。

## 五、代码分析

让我们详细分析一下任务执行的完整过程：

1. 首先，高优先级的任务3先完整执行一轮，然后进入延时状态（vTaskDelay(1000)）
2. 接着，中优先级的任务2开始执行，它需要执行1.5秒
3. 但在任务2执行1秒后，任务3的延时结束，抢占执行权，获取互斥信号量，执行自己的逻辑，然后释放互斥信号量并再次进入延时状态
4. 任务2继续执行剩余的0.5秒，然后也进入延时状态
5. 这时轮到低优先级的任务1执行，它获取互斥信号量并开始执行
6. 0.5秒后，任务3的延时结束，尝试获取互斥信号量，但发现信号量被任务1占用
7. **关键点**：此时任务1的优先级被临时提升到与任务3相同的级别
8. 由于任务1现在具有与任务3相同的高优先级，任务2无法抢断其执行
9. 任务1可以继续执行直到释放互斥信号量
10. 任务1释放互斥信号量后，其优先级恢复原值，任务3获取信号量并开始执行
11. 任务3执行完毕后，再次轮到任务2执行，而不是任务1，这证明任务1的优先级已被恢复

这整个过程清晰地展示了互斥信号量如何通过优先级继承机制解决优先级翻转问题。

## 六、完整代码

下面是完整的示例代码，使用互斥信号量解决优先级翻转：

```c
#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "semphr.h"
#include "delay.h"

TaskHandle_t myTaskHandler1;
TaskHandle_t myTaskHandler2;
TaskHandle_t myTaskHandler3;
TaskHandle_t startTaskHandler;

QueueHandle_t myPrintfQueueHandler;

void myTask1(void *arg)
{
    BaseType_t res = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        /* 获取信号量 */
        printf("The low-priority Task1 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task1 failed to get semaphore\r\n");
        }

        /* 执行其他逻辑 */
        printf("A low-priority Task1 is being executed\r\n");
        
        Delay_ms(3000);

        /* 释放信号量 */
        printf("Low-priority Task1 releases semaphores\r\n");
        res = xSemaphoreGive(myPrintfQueueHandler);
        if (res != pdPASS)
        {
            printf("Task1 failed to release semaphore\r\n");
        }

        taskEXIT_CRITICAL();
        
        vTaskDelay(1000);
    }
}

void myTask2(void *arg)
{
    while (1)
    {
        taskENTER_CRITICAL();
        printf("Task 2 of medium priority is being executed\r\n");
        Delay_ms(1500);
        printf("task2 is executed once\r\n");
        taskEXIT_CRITICAL();
        vTaskDelay(1000);
    }
}

void myTask3(void *arg)
{
    BaseType_t res = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        
        /* 获取信号量 */
        printf("The high priority Task3 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task3 failed to get semaphore\r\n");
        }

        /* 执行其他逻辑 */
        printf("High Priority Task3 is executing...\r\n");
        Delay_ms(1000);

        /* 释放信号量 */
        printf("A high-priority Task3 releases a semaphore\r\n");
        res = xSemaphoreGive(myPrintfQueueHandler);
        if (res != pdPASS)
        {
            printf("Failed to release semaphore in Task3\r\n");
        }

        taskEXIT_CRITICAL();
        
        vTaskDelay(1000);
    }
}

void startTask(void *arg)
{
    taskENTER_CRITICAL();
    printf("startTask runnig\n");
    taskEXIT_CRITICAL();
    xTaskCreate(myTask1,"myTask1",128,NULL,2,&myTaskHandler1);
    xTaskCreate(myTask2,"myTask2",128,NULL,3,&myTaskHandler2);  // 注意这里的优先级设置
    xTaskCreate(myTask3,"myTask3",128,NULL,4,&myTaskHandler3);  // 任务名应为myTask3
    vTaskDelete(NULL);
}

int main(void)
{
    USART_Config();
    
    myPrintfQueueHandler = xSemaphoreCreateMutex(); // 创建互斥信号量
    
    if(myPrintfQueueHandler == NULL)
    {
        printf("The semaphore is created failed\r\n");
    }
    else 
    {
        printf("The semaphore is created successfully\r\n");
    }
    
    xTaskCreate(startTask,"startTask",128,NULL,2,&startTaskHandler);
    
    vTaskStartScheduler();
    
    while (1)
    {
        
    }
}

StaticTask_t        IdleTaskTCB;
StackType_t         IdleTaskStack[configMINIMAL_STACK_SIZE];
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                   StackType_t ** ppxIdleTaskStackBuffer,
                                   uint32_t * pulIdleTaskStackSize )
{
    * ppxIdleTaskTCBBuffer = &IdleTaskTCB;
    * ppxIdleTaskStackBuffer = IdleTaskStack;
    * pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
```

> 注意：在startTask函数中，我修正了三个任务的优先级设置，分别为2、3、4，确保优先级递增，且修正了第三个任务的名称应为"myTask3"。

## 七、总结与拓展

通过本文的实践，我们清晰地看到了互斥信号量是如何通过优先级继承机制解决优先级翻转问题的。当高优先级任务等待低优先级任务持有的资源时，低优先级任务的优先级被临时提升，以防止中优先级任务抢占执行权。

### 互斥信号量与二值信号量的区别

1. **优先级继承**：互斥信号量支持优先级继承，二值信号量不支持
2. **用途**：互斥信号量专门用于互斥访问共享资源，二值信号量更适合任务同步
3. **所有权**：互斥信号量有所有权概念，只有获取者才能释放；二值信号量没有所有权概念
4. **递归性**：FreeRTOS还提供递归互斥信号量，允许同一任务多次获取同一互斥量

### 优先级继承的局限性

优先级继承机制虽然能解决优先级翻转问题，但仍有一些局限性：

1. 只能解决单个互斥量的情况，对于多个互斥量形成的死锁，无能为力
2. 增加了系统开销，尤其是频繁的优先级调整
3. 在某些极端情况下可能导致系统行为不可预测

### 优先级天花板协议

除了优先级继承，还有一种解决优先级翻转的方法是"优先级天花板协议"(Priority Ceiling Protocol)。该协议为每个互斥信号量指定一个优先级天花板，任何获取该互斥量的任务都会临时提升到这个优先级。虽然FreeRTOS没有直接实现这一协议，但我们可以通过适当的设计来模拟它。

> 🔥 完整的FreeRTOS学习项目请访问：[https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS)，从入门到精通的全面指南！

这个开源项目提供了从入门到精通的FreeRTOS学习资源，包括详细的移植教程、丰富的示例代码和深入浅出的文档说明，欢迎大家star和fork！

---

如果你对FreeRTOS有更多疑问或建议，欢迎在评论区留言，也欢迎关注我获取更多嵌入式开发内容！ 