/**
  ******************************************************************************
  * @file    main.c
  * @author  Despacito
  * @version V1.0
  * @date    2023-xx-xx
  * @brief   FreeRTOS多任务创建与删除示例
  ******************************************************************************
  * @attention
  *
  * 实验平台:STM32 F103 开发板 
  *
  ******************************************************************************
  */

#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"

/* 任务句柄 */
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;
TaskHandle_t Task3_Handle;

/* 空闲任务任务堆栈 */
StaticTask_t IdleTaskTCB;
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];

/* 任务函数 */
static void Task1_Entry(void *parameter);
static void Task2_Entry(void *parameter);
static void Task3_Entry(void *parameter);

/* 延时函数 */
void Delay(uint32_t count)
{
	for(; count!=0; count--);
}

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//开启GPIOC的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//GPIO引脚，赋值为第13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为高电平
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为低电平
	
	USART_Config();
	
	printf("\r\n======== FreeRTOS多任务创建与删除示例 ========\r\n");
	
	/* 创建任务1 */
	xTaskCreate((TaskFunction_t)Task1_Entry,          /* 任务入口函数 */
				(const char *)"Task1",                /* 任务名称 */
				(uint16_t)512,                        /* 任务堆栈大小 */
				(void *)NULL,                         /* 任务入口函数参数 */
				(UBaseType_t)1,                       /* 任务优先级 */
				(TaskHandle_t *)&Task1_Handle);       /* 任务句柄 */
	
	/* 启动任务调度器 */
	vTaskStartScheduler();
	
	/* 正常情况下不会执行到这里 */
	while (1)
	{
		
	}
}

/**
  * @brief  任务1入口函数
  * @param  parameter 入口参数
  * @retval 无
  */
static void Task1_Entry(void *parameter)
{
	uint32_t count = 0;
	
	printf("任务1创建成功!\r\n");
	
	/* 创建任务2 */
	xTaskCreate((TaskFunction_t)Task2_Entry,          /* 任务入口函数 */
				(const char *)"Task2",                /* 任务名称 */
				(uint16_t)512,                        /* 任务堆栈大小 */
				(void *)NULL,                         /* 任务入口函数参数 */
				(UBaseType_t)2,                       /* 任务优先级 */
				(TaskHandle_t *)&Task2_Handle);       /* 任务句柄 */
	
	while(1)
	{
		printf("任务1运行中，计数值:%d\r\n", count++);
		
		/* 任务运行5次后创建任务3 */
		if(count == 5)
		{
			printf("任务1即将创建任务3...\r\n");
			
			/* 创建任务3 */
			xTaskCreate((TaskFunction_t)Task3_Entry,          /* 任务入口函数 */
						(const char *)"Task3",                /* 任务名称 */
						(uint16_t)512,                        /* 任务堆栈大小 */
						(void *)NULL,                         /* 任务入口函数参数 */
						(UBaseType_t)3,                       /* 任务优先级 */
						(TaskHandle_t *)&Task3_Handle);       /* 任务句柄 */
		}
		
		/* 延时500个tick */
		vTaskDelay(500);
	}
}

/**
  * @brief  任务2入口函数
  * @param  parameter 入口参数
  * @retval 无
  */
static void Task2_Entry(void *parameter)
{
	uint32_t count = 0;
	
	printf("任务2创建成功!\r\n");
	
	while(1)
	{
		printf("任务2运行中，计数值:%d\r\n", count++);
		
		/* 任务运行10次后删除自己 */
		if(count == 10)
		{
			printf("任务2即将删除自己...\r\n");
			vTaskDelete(NULL);
		}
		
		/* 延时500个tick */
		vTaskDelay(500);
	}
}

/**
  * @brief  任务3入口函数
  * @param  parameter 入口参数
  * @retval 无
  */
static void Task3_Entry(void *parameter)
{
	uint32_t count = 0;
	
	printf("任务3创建成功!\r\n");
	
	while(1)
	{
		printf("任务3运行中，计数值:%d\r\n", count++);
		
		/* 任务运行5次后删除任务1 */
		if(count == 5)
		{
			printf("任务3即将删除任务1...\r\n");
			vTaskDelete(Task1_Handle);
		}
		
		/* 延时500个tick */
		vTaskDelay(500);
	}
}

/**
  * @brief  空闲任务堆栈指针获取函数
  * @param  ppxIdleTaskTCBBuffer 任务控制块
  * @param  ppxIdleTaskStackBuffer 任务堆栈
  * @param  pulIdleTaskStackSize 任务堆栈大小
  * @retval 无
  */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
									StackType_t ** ppxIdleTaskStackBuffer,
									uint32_t * pulIdleTaskStackSize )
{
	* ppxIdleTaskTCBBuffer = &IdleTaskTCB;
	* ppxIdleTaskStackBuffer = IdleTaskStack;
	* pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
