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
        /* ��ȡ�ź��� */
        printf("The low-priority Task1 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task1 failed to get semaphore\r\n");
        }

        /* ִ�������߼� */
        printf("A low-priority Task1 is being executed\r\n");
				
        Delay_ms(3000);

        /* �ͷ��ź��� */
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
			
        /* ��ȡ�ź��� */
        printf("The high priority Task3 gets the semaphore\r\n");
        res = xSemaphoreTake(myPrintfQueueHandler, portMAX_DELAY);
        if (res != pdPASS)
        {
            printf("Task3 failed to get semaphore\r\n");
        }

        /* ִ�������߼� */
        printf("High Priority Task3 is executing...\r\n");
        Delay_ms(1000);

        /* �ͷ��ź��� */
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
	xTaskCreate(myTask2,"myTask2",128,NULL,2,&myTaskHandler2);
	xTaskCreate(myTask3,"myTask2",128,NULL,2,&myTaskHandler3);
	vTaskDelete(NULL);
}

int main(void)
{
	
	USART_Config();
	
  //xSemaphoreCreateBinary(myPrintfQueueHandler,0);//x��ͷ�ģ����������ͷ��ź���
  vSemaphoreCreateBinary(myPrintfQueueHandler); //v��ͷ�ģ�������������ͷ�һ���ź���
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
StackType_t					IdleTaskStack[configMINIMAL_STACK_SIZE];
 void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                     StackType_t ** ppxIdleTaskStackBuffer,
                                     uint32_t * pulIdleTaskStackSize )
 {
		* ppxIdleTaskTCBBuffer = &IdleTaskTCB;
		* ppxIdleTaskStackBuffer = IdleTaskStack;
	  * pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
 }
