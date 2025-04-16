#include "stm32f10x.h"                  // Device header
#include "freertos.h"
#include "task.h"
#include "usart.h"
#include "queue.h"


TaskHandle_t myTaskHandler1;
TaskHandle_t myTaskHandler2;
TaskHandle_t myTaskHandler3;
TaskHandle_t startTaskHandler;

QueueHandle_t myPrintfQueueHandler;

struct print{
	int cnt;
	char data[20];
};


void myTask1( void * arg)
{
	struct print data = {
		.data = "myTask1 running"
	};
	while(1)
	{
//		taskENTER_CRITICAL();
//		printf("myTask1 running\n");
//		taskEXIT_CRITICAL();	
		data.cnt ++;
		xQueueSend(myPrintfQueueHandler, &data, 0);
		vTaskDelay(500);
	}
}

void myTask2( void * arg)
{
	struct print data = {
		.data = "myTask2 running"
	};
	while(1)
	{
//		taskENTER_CRITICAL();
//		printf("myTask2 running\n");
//		taskEXIT_CRITICAL();
		data.cnt ++;
		xQueueSend(myPrintfQueueHandler, &data, 0);
		vTaskDelay(500);
	}
}

void myTask3( void * arg)
{
	struct print data;
	BaseType_t xStatus;
	while(1)
	{
		xStatus = xQueueReceive(myPrintfQueueHandler, &data, portMAX_DELAY);
		if(xStatus == pdPASS)
		{
			taskENTER_CRITICAL();
			printf("%s:%d\n", data.data, data.cnt);
			taskEXIT_CRITICAL();
		}
//		vTaskDelay(500);
	}
}

void startTask(void * arg)
{
	taskENTER_CRITICAL();
	printf("startTask running\n");
	taskEXIT_CRITICAL();
	xTaskCreate(myTask1, "myTask1", 128, NULL, 2, &myTaskHandler1); 
	xTaskCreate(myTask2, "myTask2", 128, NULL, 2, &myTaskHandler2); 
	xTaskCreate(myTask3, "myTask3", 128, NULL, 2, &myTaskHandler3); 
	vTaskDelete(NULL);
}

int main(void)
{
	USART_Config();
	
	myPrintfQueueHandler = xQueueCreate(2, sizeof(struct print));
	
	xTaskCreate(startTask, "startTask", 128, NULL, 2, &startTaskHandler); 
	   
	vTaskStartScheduler();
	
	while(1)
	{
		
	
	}

}

StaticTask_t	IdleTaskTCB;
StackType_t		IdleTaskStack[configMINIMAL_STACK_SIZE];
void vApplicationGetIdleTaskMemory( StaticTask_t 	**ppxIdleTaskTCBBuffer, 
									StackType_t 	**ppxIdleTaskStackBuffer, 
									uint32_t 		*pulIdleTaskStackSize )
{
	*ppxIdleTaskTCBBuffer = &IdleTaskTCB;
	*ppxIdleTaskStackBuffer = IdleTaskStack;	
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;

}
