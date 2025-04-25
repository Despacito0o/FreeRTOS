#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "semphr.h"
#include "delay.h"
#include "key.h"
#include "queue.h"

TaskHandle_t myTaskHandler1;
TaskHandle_t myTaskHandler2;
TaskHandle_t myTaskHandler3;
TaskHandle_t startTaskHandler;
QueueHandle_t queue1;
QueueHandle_t queue2;
QueueSetHandle_t myPrintfQueueHandler;

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



void startTask(void *arg)
{
	taskENTER_CRITICAL();
	xTaskCreate(myTask1,"myTask1",128,NULL,2,&myTaskHandler1);
	xTaskCreate(myTask2,"myTask2",128,NULL,2,&myTaskHandler2);
	vTaskDelete(NULL);
	taskEXIT_CRITICAL();
}

int main(void)
{
	
	BaseType_t res = 0;
	
	USART_Config();
	
		queue1 = xQueueCreate(2,sizeof(uint8_t));
	if (queue1 != NULL)
    {
        printf("queue1创建成功\r\n");
    }
    else
    {
        printf("queue1创建失败\r\n");
    }	

		queue2 = xSemaphoreCreateBinary();
    if (queue2 != NULL)
    {
        printf("二值信号量创建成功\r\n");
    }
    else
    {
        printf("二值信号量创建失败\r\n");
    }
		
		
		myPrintfQueueHandler = xQueueCreateSet(2);
	
    if (myPrintfQueueHandler != NULL)
    {
        printf("创建队列集成功\r\n");
    }

    /* 将队列、信号量添加到队列集中：添加时，队列/信号量 需要为空 */
    res = xQueueAddToSet(queue1, myPrintfQueueHandler);
    if (res == pdPASS)
    {
        printf("queue1添加到队列集成功\r\n");
    }
    res = xQueueAddToSet(queue2, myPrintfQueueHandler);
    if (res == pdPASS)
    {
        printf("二值信号量添加到队列集成功\r\n");
    }

	
	xTaskCreate(startTask,"startTask",128,NULL,2,&startTaskHandler);
	
	vTaskStartScheduler();
	
	while (1)
	{
		
	}
}

StaticTask_t        IdleTaskTCB;
StackType_t					IdleTaskStack[configMINIMAL_STACK_SIZE];
 void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                     StackType_t ** ppxIdleTaskStackBuffer,
                                     uint32_t * pulIdleTaskStackSize )
 {
		* ppxIdleTaskTCBBuffer = &IdleTaskTCB;
		* ppxIdleTaskStackBuffer = IdleTaskStack;
	  * pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
 }
