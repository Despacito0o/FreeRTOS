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
            /* ��key�ı��д��queue1 */
            res = xQueueSend(queue1, &key, portMAX_DELAY);
            if (res == pdPASS)
            {
                printf("��queue1��������[%d]�ɹ�\r\n", key);
            }
            else
            {
                printf("��queue1��������ʧ��\r\n");
            }
        }
        else if (key == KEY2_PRESS)
        {
            /* �ͷ��ź��� */
            res = xSemaphoreGive(queue2);
            if (res == pdPASS)
            {
                printf("�ͷ��ź����ɹ�\r\n");
            }
            else
            {
                printf("�ͷ��ź���ʧ��\r\n");
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
        /* �鿴�ĸ��������������� */
        member_handle = xQueueSelectFromSet(myPrintfQueueHandler, portMAX_DELAY);
        /* ���ݶ�Ӧ�Ķ��У�ȥ��ȡ���� */
        if (member_handle == queue1)
        {
            res = xQueueReceive(queue1, &receive, portMAX_DELAY);
            if (res == pdPASS)
            {
                printf("task2��queue1�ɹ���ȡ����[%d]\r\n", receive);
            }
            else
            {
                printf("task2��queue1��ȡ����ʧ��\r\n");
            }
        }
        else if (member_handle == queue2)
        {
            res = xSemaphoreTake(queue2,portMAX_DELAY);
            if(res == pdPASS)
            {
                printf("��ȡ�ź����ɹ�\r\n");
            }
        }
        else 
        {
            printf("�Ӷ��м���ȡ��Ϣʧ��\r\n");
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
        printf("queue1�����ɹ�\r\n");
    }
    else
    {
        printf("queue1����ʧ��\r\n");
    }	

		queue2 = xSemaphoreCreateBinary();
    if (queue2 != NULL)
    {
        printf("��ֵ�ź��������ɹ�\r\n");
    }
    else
    {
        printf("��ֵ�ź�������ʧ��\r\n");
    }
		
		
		myPrintfQueueHandler = xQueueCreateSet(2);
	
    if (myPrintfQueueHandler != NULL)
    {
        printf("�������м��ɹ�\r\n");
    }

    /* �����С��ź�����ӵ����м��У����ʱ������/�ź��� ��ҪΪ�� */
    res = xQueueAddToSet(queue1, myPrintfQueueHandler);
    if (res == pdPASS)
    {
        printf("queue1��ӵ����м��ɹ�\r\n");
    }
    res = xQueueAddToSet(queue2, myPrintfQueueHandler);
    if (res == pdPASS)
    {
        printf("��ֵ�ź�����ӵ����м��ɹ�\r\n");
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
