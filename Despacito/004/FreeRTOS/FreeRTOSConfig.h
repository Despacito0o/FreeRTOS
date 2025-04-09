/**
 * @file FreeRTOSConfig.h
 * @author Despacito (https://github.com/Despacito0o/FreeRTOS)
 * @brief FreeRTOS�����ļ�
 */
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


// ����������
#define configUSE_PREEMPTION		1  // ������ռʽ����
#define configIDLE_SHOULD_YIELD		1  // ��������Ӧ�ó�CPU

// ʱ������
#define configCPU_CLOCK_HZ			( ( unsigned long ) 72000000 )  // CPUʱ��Ƶ�ʣ���λHz
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )  // ʱ�ӽ���Ƶ�ʣ���λHz
#define configUSE_16_BIT_TICKS		0  // ʹ��32λʱ�ӽ���

// ��������
#define configMAX_PRIORITIES		( 5 )  // ����������ȼ���
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )  // ��С�����ջ��С
#define configMAX_TASK_NAME_LEN		( 16 )  // ����������󳤶�

// �ڴ�����
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 17 * 1024 ) )  // �ܶѴ�С

// ���Ӻ�������
#define configUSE_IDLE_HOOK			0  // ���ÿ���������
#define configUSE_TICK_HOOK			0  // ����ʱ�ӽ��Ĺ���

// API��������
#define INCLUDE_vTaskPrioritySet		1  // �����������ȼ����ú���
#define INCLUDE_uxTaskPriorityGet		1  // ������ȡ�������ȼ�����
#define INCLUDE_vTaskDelete				1  // ����ɾ��������
#define INCLUDE_vTaskCleanUpResources	0  // ����������������Դ����
#define INCLUDE_vTaskSuspend			1  // ��������������
#define INCLUDE_vTaskDelayUntil			1  // �����ӳٵ�ָ��ʱ�亯��
#define INCLUDE_vTaskDelay				1  // �����ӳٺ���

// �ж����ȼ�����
#define configKERNEL_INTERRUPT_PRIORITY 		255  // �ں��ж����ȼ�
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191  // �൱��0xb0�������ȼ�11
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15  // ���ں��ж����ȼ�

// �жϴ���������
#define xPortPendSVHandler 	PendSV_Handler  // ����PendSV�жϴ�����
#define vPortSVCHandler 	SVC_Handler  // ����SVC�жϴ�����
#define xPortSysTickHandler SysTick_Handler  // ����SysTick�жϴ�����

#endif /* FREERTOS_CONFIG_H */


