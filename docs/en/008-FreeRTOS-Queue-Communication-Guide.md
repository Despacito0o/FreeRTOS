# FreeRTOS Queue Communication Example

## Introduction

This example demonstrates how to use queues in FreeRTOS for inter-task communication. Queues are a data transfer mechanism provided by FreeRTOS, which can be used for data transmission between tasks, as well as between tasks and interrupts. This example shows how to implement task separation through queues, making the code structure clearer.

## Features

- Demonstrates the basic creation and usage of queues
- Shows how to pass string messages between tasks via queues
- Implements passing multiple data types using structures through queues
- Demonstrates the producer-consumer pattern for task separation

## Project Overview

This project is based on the STM32F103 series microcontroller, developed using the Standard Peripheral Library (StdPeriph). The project implements communication between multiple tasks through queues, where:

- `myTask1` and `myTask2` act as producer tasks, responsible for generating data and writing it to the queue
- `myTask3` acts as a consumer task, responsible for reading data from the queue and displaying it

This structure makes the task logic hierarchy clearer, allowing each task to focus on its own functionality, improving code maintainability.

## Key Code

### 1. Queue Creation

```c
/* Create a queue that can hold 2 messages, each 20 bytes in size */
myPrintfQueueHandler = xQueueCreate(2, 20);
```

### 2. Sending Data to Queue

```c
/* Basic string sending */
char data[20] = "myTask1 running";
xQueueSend(myPrintfQueueHandler, data, 0);

/* Structure data sending */
struct print data = {
    .data = "myTask1 running"
};
data.cnt++;
xQueueSend(myPrintfQueueHandler, &data, 0);
```

### 3. Receiving Data from Queue

```c
/* Receive and process data from queue */
BaseType_t xStatus;
xStatus = xQueueReceive(myPrintfQueueHandler, &data, portMAX_DELAY);
if(xStatus == pdPASS)
{
    taskENTER_CRITICAL();
    printf("%s:%d\n", data.data, data.cnt);
    taskEXIT_CRITICAL();
}
```

## Structure Transfer

This example also shows how to transfer structure data through a queue, which is very useful for scenarios requiring the transmission of multiple parameters:

```c
/* Define structure */
struct print {
    char data[20];
    int cnt;
};

/* Modify queue creation, data size is the structure size */
myPrintfQueueHandler = xQueueCreate(2, sizeof(struct print));
```

## Running Behavior

- After debugging and running, the serial terminal will display data from Task 1 and Task 2
- In structure transfer mode, it will display the task name and count value
- Task 3 will process data from Task 1 and Task 2 in FIFO order

## Notes

1. When a queue is full, the blocking time parameter determines the task's behavior:
   - Set to 0: returns immediately if unable to write
   - Set to portMAX_DELAY: will block until writing is possible
   
2. When a queue is empty, the blocking characteristics for receiving data are similar
   
3. When using structures, the data size in the queue needs to match the structure size

## Extended Considerations

1. How to handle situations when a queue is full?
2. How to use queues in interrupts?
3. How to implement more complex inter-task communication patterns using queues?

## Related API Functions

- `xQueueCreate()`: Create a queue
- `xQueueSend()`: Send data to the back of the queue
- `xQueueSendToFront()`: Send data to the front of the queue
- `xQueueReceive()`: Read data from the queue
- `xQueuePeek()`: View queue data without removing it
- `uxQueueMessagesWaiting()`: Get the number of messages in the queue 