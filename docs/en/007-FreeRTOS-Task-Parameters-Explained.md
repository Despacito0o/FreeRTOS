# FreeRTOS Task Parameters Explained

## Introduction

Hello everyone! Today we're going to explore a very useful but often overlooked feature in FreeRTOS — task parameters. In my previous FreeRTOS tutorial series, when creating tasks, we always set the parameters to NULL. Today, we'll dive deep into how to use task parameters to make our task designs more flexible.

If you're interested in FreeRTOS, please check out my GitHub repository: [https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS), which contains comprehensive FreeRTOS learning resources and example code from beginner to advanced levels!

## Task Parameter Basics

First, let's look at the task creation function prototype:

```c
BaseType_t xTaskCreate(
    TaskFunction_t pvTaskCode,        /* Task function pointer */
    const char * const pcName,        /* Task name */
    const uint16_t usStackDepth,      /* Task stack size */
    void *pvParameters,               /* Task parameters */
    UBaseType_t uxPriority,           /* Task priority */
    TaskHandle_t * const pxCreatedTask /* Task handle */
```

The `pvParameters` is a `void` pointer type, which means it can pass any type of data as task parameters. This design is very flexible, allowing us to:

- Pass basic data types (cast to `void*`)
- Pass addresses of structures or arrays
- Pass string constants
- Even pass function pointers

## Practical Case: One Function, Multiple Tasks

Today we'll implement a common scenario: **multiple tasks using the same task function but printing different content through different parameters**.

We'll use the project from the previous article as our foundation, copy 006, paste and rename it to 007:

![Project Copy](https://i-blog.csdnimg.cn/direct/a20a09392c3f45c183e1f2999d60661a.png)

### 1. Clean Up Existing Code

First, let's remove some redundant code:

```c
/*Enable clock*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//Enable GPIOC clock
	/*GPIO initialization*/
	GPIO_InitTypeDef GPIO_InitStructure;					//Define structure variable
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO mode, set to push-pull output mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//GPIO pin, set to pin 13
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO speed, set to 50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//Pass the configured structure to GPIO_Init function
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);						//Set PC13 pin to high level
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//Set PC13 pin to low level	
```

![Removing GPIO Code](https://i-blog.csdnimg.cn/direct/0fe2edf96cdd4f61a21a4f16e1600875.png)

Also delete the original task functions:

```c
void myTask1(void *arg)
{
	  uint8_t i = 0;
		while(1)
		{
			taskENTER_CRITICAL();
		  printf("myTask1 runnig\n");
			taskEXIT_CRITICAL();
			
			i++;
			if(i ==1)
			{
					vTaskDelete(myTaskHandler3);
			}
			if(i == 2)
			{
					vTaskDelete(NULL);
			}
			
					vTaskDelay(500);
		}
}

void myTask2(void *arg)
{
		while(1)
		{
			taskENTER_CRITICAL();
		  printf("myTask2 runnig\n");
			taskEXIT_CRITICAL();
			vTaskDelay(500);
		}
}

void myTask3(void *arg)
{
		while(1)
		{
			taskENTER_CRITICAL();
		  printf("myTask3 runnig\n");
			taskEXIT_CRITICAL();
			vTaskDelay(500);
		}
}
```

### 2. Create a Generic Print Task Function

First, create a generic print task function framework:

![Create Print Function](https://i-blog.csdnimg.cn/direct/18985212dfee41d29198d07b20d955c6.png)

```c
void myPrintf(void*arg)
{
		while(1)
		{
			
			
		}
}
```

### 3. Modify Task Creation Code

Modify the task creation code to make all tasks use the same task function:

![Update Task Creation](https://i-blog.csdnimg.cn/direct/e65334ade30e46799c7e960650e220ea.png)

```c
	xTaskCreate(myPrintf,"myTask1",128,NULL,2,&myTaskHandler1);
	xTaskCreate(myPrintf,"myTask2",128,NULL,2,&myTaskHandler2);
	xTaskCreate(myPrintf,"myTask3",128,NULL,2,&myTaskHandler3);
```

### 4. Complete the Task Function

Now implement the functionality of the print function. Before using the task parameter, we need to convert the `void*` type parameter to the type we need:

![Implement Function](https://i-blog.csdnimg.cn/direct/1081f45e31234949ae4f8ff627c8a11e.png)

```c
void myPrintf(void*arg)
{
		char *str = arg;
		while(1)
		{
			taskENTER_CRITICAL();
			printf("%s\n",str);
			taskEXIT_CRITICAL();

		}
}
```

### 5. Define Task Parameters

Define different string parameters for each task:

![Define Parameters](https://i-blog.csdnimg.cn/direct/84ae0c72e8ee4b52a1094985551b0279.png)

```c
char str1[20] = "myTask1 running!";
char str2[20] = "myTask2 running!";
char str3[20] = "myTask3 running!";
```

### 6. Add Delay and Pass Parameters to Tasks

Add delay in the task function and pass parameters to the task creation function:

![Add Delay](https://i-blog.csdnimg.cn/direct/47e70ed1e92548b29f8c4565958053e9.png)

```c
vTaskDelay(500);
```

```c
	xTaskCreate(myPrintf,"myTask1",128,str1,2,&myTaskHandler1);
	xTaskCreate(myPrintf,"myTask2",128,str2,2,&myTaskHandler2);
	xTaskCreate(myPrintf,"myTask3",128,str3,2,&myTaskHandler3);
```

### 7. Compile and Run

After compiling, enter debug mode, click run, and you can see the normal print results, successfully implementing different operations by passing different parameters:

![Running Result](https://i-blog.csdnimg.cn/direct/2b436f27c16046a281ea583add310179.png)

## Important Considerations

There's something important to note in this operation: the print function ultimately calls UART to send data, which is a relatively time-consuming operation. The operating system switches tasks every millisecond, and without protection, it might suddenly switch from task one to task two while task one is sending half of its data, causing data corruption or even program crashes.

This is why we used `taskENTER_CRITICAL()` and `taskEXIT_CRITICAL()` for critical section protection. **When multiple tasks use the same limited resource, conflicts from simultaneous access must be avoided**.

## More Uses of Task Parameters

In addition to the string parameters shown above, task parameters have many powerful uses:

1. **Passing Structures**: You can pass structures containing multiple parameters, for example:

```c
typedef struct {
    uint8_t led_pin;
    uint16_t delay_ms;
    char* message;
} TaskParams_t;

// Usage example
TaskParams_t task1_params = {LED_PIN_1, 500, "LED1 Toggle"};
xTaskCreate(ledToggleTask, "LED1Task", 128, &task1_params, 2, NULL);
```

2. **Passing Arrays**: You can pass array addresses as parameters

3. **Passing Values**: You can directly pass simple values (type conversion required)

```c
// Passing a simple integer (type conversion required)
xTaskCreate(countTask, "Count", 128, (void*)10, 2, NULL);

// In the task function
void countTask(void* arg) {
    int count = (int)arg;  // Convert void* back to integer
    // Use count...
}
```

4. **Passing Function Pointers**: You can pass callback functions

## Complete Code Example

You can find the complete example code in my GitHub repository: [https://github.com/Despacito0o/FreeRTOS/tree/main/Despacito/007](https://github.com/Despacito0o/FreeRTOS/tree/main/Despacito/007)

## Summary and Outlook

Today we learned the basic usage of FreeRTOS task parameters, demonstrating through an example how to use a single task function to create multiple tasks and implement different functions through different parameters.

Flexible use of task parameters can:
- Reduce code redundancy and improve code reusability
- Make task functions more generic and flexible
- Simplify data passing between tasks

In the next article, we'll explore FreeRTOS task notification mechanism, which is a lighter and more efficient way of inter-task communication than semaphores.

If you're interested in FreeRTOS development, please check out my GitHub repository: [https://github.com/Despacito0o/FreeRTOS](https://github.com/Despacito0o/FreeRTOS), which has complete tutorials and example code from beginner to master level!

Thank you for reading, and if you have any questions, please leave a comment in the discussion section!

---
**Author Introduction**: Embedded development enthusiast, focused on FreeRTOS and STM32 development, sharing embedded development technologies and experiences. 