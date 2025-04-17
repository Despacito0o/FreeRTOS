#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "semphr.h"

TaskHandle_t myTaskHandler1;
TaskHandle_t myTaskHandler2;
TaskHandle_t startTaskHandler;

QueueHandle_t myPrintfQueueHandler;

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

void startTask(void *arg)
{
	taskENTER_CRITICAL();
	printf("startTask runnig\n");
	taskEXIT_CRITICAL();
	xTaskCreate(myTask1,"myTask1",128,NULL,2,&myTaskHandler1);
	xTaskCreate(myTask2,"myTask2",128,NULL,2,&myTaskHandler2);
	vTaskDelete(NULL);
}

int main(void)
{
	
	USART_Config();
	
  //xSemaphoreCreateBinary(myPrintfQueueHandler,0);//x开头的，不会主动释放信号量
  vSemaphoreCreateBinary(myPrintfQueueHandler); //v开头的，创建完会主动释放一次信号量
	if(myPrintfQueueHandler == NULL)
	{
			printf("Semaphore creation failed\r\n");
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
