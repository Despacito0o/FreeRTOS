#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

#define KEY1_Pin         GPIO_Pin_11
#define KEY1_GPIO_Port   GPIOB
#define KEY2_Pin         GPIO_Pin_1
#define KEY2_GPIO_Port   GPIOB
#define KEY3_Pin         GPIO_Pin_10
#define KEY3_GPIO_Port   GPIOB
#define KEY4_Pin         GPIO_Pin_7
#define KEY4_GPIO_Port   GPIOF

#define KEY1        GPIO_ReadInputDataBit(KEY1_GPIO_Port, KEY1_Pin)   /* ��ȡKEY1����״̬��SW3�� */
#define KEY2        GPIO_ReadInputDataBit(KEY2_GPIO_Port, KEY2_Pin)   /* ��ȡKEY2����״̬��SW4�� */
#define KEY3        GPIO_ReadInputDataBit(KEY3_GPIO_Port, KEY3_Pin)   /* ��ȡKEY3����״̬��SW5�� */
#define KEY4        GPIO_ReadInputDataBit(KEY4_GPIO_Port, KEY4_Pin)   /* ��ȡKEY4����״̬��SW6�� */


#define KEY1_PRESS    1              
#define KEY2_PRESS    2              
#define KEY3_PRESS    3              
#define KEY4_PRESS    4              


uint8_t Key_Detect(void);


#endif
