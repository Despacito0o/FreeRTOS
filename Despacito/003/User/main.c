#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t myTaskHandler;

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
															//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//GPIO引脚，赋值为第13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
															//函数内部会自动根据结构体的参数配置相应寄存器
															//实现GPIOC的初始化
	
	/*设置GPIO引脚的高低电平*/
	/*若不设置GPIO引脚的电平，则在GPIO初始化为推挽输出后，指定引脚默认输出低电平*/
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为高电平
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为低电平
	
	xTaskCreate(myTask,"myTask",128,NULL,2,&myTaskHandler);
	vTaskStartScheduler();
	while (1)
	{
		
	}
}
