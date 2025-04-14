#include "stm32f10x.h"                  
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"

TaskHandle_t myTaskHandler1;
TaskHandle_t myTaskHandler2;
TaskHandle_t myTaskHandler3;
TaskHandle_t startTaskHandler;

char str1[20] = "myTask1 running!";
char str2[20] = "myTask2 running!";
char str3[20] = "myTask3 running!";


void myPrintf(void*arg)
{
		char *str =arg;
		while(1)
		{
			taskENTER_CRITICAL();
			printf("%s\n",str);
			taskEXIT_CRITICAL();
			vTaskDelay(500);
		}
}

void startTask(void *arg)
{
	taskENTER_CRITICAL();
	printf("startTask runnig\n");
	taskEXIT_CRITICAL();
	xTaskCreate(myPrintf,"myTask1",128,str1,2,&myTaskHandler1);
	xTaskCreate(myPrintf,"myTask2",128,str2,2,&myTaskHandler2);
	xTaskCreate(myPrintf,"myTask3",128,str3,2,&myTaskHandler3);
	vTaskDelete(NULL);
}

int main(void)
{
	
	USART_Config();
	
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
