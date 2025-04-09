#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"

//TaskHandle_t myTaskHandler;
StackType_t myTaskStack[128];
StaticTask_t myTaskTCB;

void myTask(void *arg)
{
		while(1)
		{
		  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			vTaskDelay(500);
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			vTaskDelay(500);
		}
}

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
//	GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为低电平
	
//	xTaskCreate(myTask,"myTask",128,NULL,2,&myTaskHandler);
	xTaskCreateStatic(myTask,"myTask",128,NULL,2,myTaskStack,&myTaskTCB);
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
