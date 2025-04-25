#include "Key.h"
#include "delay.h"

/**
 * @description: 检测按键
 * @return {*} 按下的按键值
 */
uint8_t Key_Detect(void)
{
    uint8_t res = 0;
    if (KEY1 == RESET || KEY2 == RESET || KEY3 == SET || KEY4 == SET )  
    {
        Delay_ms(10);           /* 去抖动 */
        /* 按这个顺序，如果多个按键同时按，优先级：KEY4>KEY3>KEY2>KEY1 */
        if (KEY1 == RESET)  res = KEY1_PRESS;
        if (KEY2 == RESET)  res = KEY2_PRESS;
        if (KEY3 == SET)  res = KEY3_PRESS;
        if (KEY4 == SET)  res = KEY4_PRESS;
    }
    return res;
}


