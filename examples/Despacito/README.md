# Despacito - STM32F103 FreeRTOS示例项目

## 项目简介
这是一个基于STM32F103系列单片机的FreeRTOS示例项目，展示了FreeRTOS在STM32平台上的基本应用。

## 硬件要求
- STM32F103C8T6开发板
- ST-Link调试器
- LED指示灯（PC13）

## 软件要求
- Keil MDK 5.x
- STM32标准外设库
- FreeRTOS v202212.01

## 项目结构
```
Despacito/
├── FreeRTOS/                 # FreeRTOS相关文件
│   ├── freertos include/     # FreeRTOS头文件
│   └── freertos portable/    # 移植相关文件
├── User/                     # 用户代码
├── Library/                  # STM32标准外设库
└── Start/                    # 启动文件
```

## 功能特性
- FreeRTOS任务创建与管理
- LED控制示例
- 串口通信示例
- 中断处理示例

## 使用说明
1. 打开工程文件 `Despacito001.uvprojx`
2. 编译项目
3. 使用ST-Link下载程序到开发板
4. 观察LED指示灯的变化

## 示例代码
```c
// 创建LED控制任务
void LED_Task(void *pvParameters)
{
    while(1)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // LED亮
        vTaskDelay(pdMS_TO_TICKS(500));      // 延时500ms
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // LED灭
        vTaskDelay(pdMS_TO_TICKS(500));      // 延时500ms
    }
}
```

## 注意事项
1. 确保正确配置了STM32标准外设库
2. 检查FreeRTOS配置文件是否正确
3. 注意中断优先级的设置

## 常见问题
1. 编译错误
   - 检查包含路径是否正确
   - 确认所有依赖文件都已添加

2. 运行异常
   - 检查时钟配置
   - 验证中断向量表设置

## 贡献指南
欢迎提交Issue和Pull Request来帮助改进这个项目。

## 许可证
本项目采用 MIT 许可证 