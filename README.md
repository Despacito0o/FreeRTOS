# FreeRTOS 嵌入式开发学习库

## 项目概述
本仓库包含FreeRTOS嵌入式系统开发的学习资料和示例项目，帮助初学者快速入门STM32开发。

## 项目列表

### Despacito
STM32F103系列的嵌入式开发项目，使用标准外设库(StdPeriph)进行开发。

## STM32标准库开发环境搭建教程

### 准备工作
1. 安装Keil MDK开发环境
2. 下载STM32标准外设库

### 详细步骤
1. 打开Keil，新建一个project
   ![新建工程](https://i-blog.csdnimg.cn/direct/456e7f1370cd4f5d90b204dcbd37ff2a.png)

2. 选择一个存放工程的文件夹，并给工程命名后点击保存
   ![命名工程](https://i-blog.csdnimg.cn/direct/59e3493295b94cdaaa53beb27745c2e7.png)

3. 选择您的芯片型号（本例中使用STM32F103C8），然后点击OK
   ![选择芯片](https://i-blog.csdnimg.cn/direct/95742a07675b467a9846eacbaf9e001c.png)

4. 关闭弹出的窗口
   ![关闭窗口](https://i-blog.csdnimg.cn/direct/3fa8e6d04a2b43a59f3e0c102107a86c.png)

5. 在刚创建的工程文件夹中添加三个子文件夹：Start、Library和User
   ![添加文件夹](https://i-blog.csdnimg.cn/direct/315e2eb94b954e86a950d86e0363cb3c.png)

### 下载并配置标准外设库
1. 前往ST官网下载最新标准外设库：[点击前往官方下载](https://www.st.com.cn/zh/embedded-software/stsw-stm32054.html)
   ![下载库](https://i-blog.csdnimg.cn/direct/1868afb0b36246ab98824aaa4835d206.png)

2. 点击"获取最新版本"，并接受许可协议
   ![接受协议](https://i-blog.csdnimg.cn/direct/4f31f48d21184a6488a683fb3600ff1f.png)

3. 使用您的ST账号登录
   ![登录](https://i-blog.csdnimg.cn/direct/d993c74d66424daba63851da6545deb3.png)

4. 点击"Download latest"下载最新版本
   ![下载最新版本](https://i-blog.csdnimg.cn/direct/658af4d3aaa04453906969c731e94c8a.png)

5. 解压下载的文件
   ![解压文件](https://i-blog.csdnimg.cn/direct/82860324304248a9bad5e8959c45db79.png)

### 文件配置
1. 找到启动文件路径：`Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm`，将其中所有文件复制到Start文件夹
   ![复制启动文件](https://i-blog.csdnimg.cn/direct/8f5c0ca058b9489f91cb8b49b408f1fd.png)

2. 导航至路径：`Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x`，将相关文件复制到Start文件夹
   ![复制设备支持文件](https://i-blog.csdnimg.cn/direct/734a5886f8684d41879e48f89226fd66.png)

3. 导航至路径：`Libraries\CMSIS\CM3\CoreSupport`，将核心支持文件复制到Start文件夹
   ![复制核心支持文件](https://i-blog.csdnimg.cn/direct/24f5a0388cf040ee84d68230113a7fdf.png)

4. 导航至路径：`Libraries\STM32F10x_StdPeriph_Driver\src`，将文件夹内容复制到Library文件夹
   ![复制标准外设驱动文件](https://i-blog.csdnimg.cn/direct/48399df386f64596a552435c93296bd6.png)

5. 打开inc文件夹（路径：`Libraries\STM32F10x_StdPeriph_Driver\inc`），将文件夹内容复制到Library文件夹
   ![复制头文件](https://i-blog.csdnimg.cn/direct/d7537287252a4dcaa0d95aa38caf5fb7.png)

6. 导航至路径：`Project\STM32F10x_StdPeriph_Template`，将模板文件复制到User文件夹
   ![复制模板文件](https://i-blog.csdnimg.cn/direct/b61aa4c1fdf04ea48ec8ff18f9d7e90f.png)

### 工程配置
1. 返回Keil，点击工程文件管理按钮
   ![工程管理](https://i-blog.csdnimg.cn/direct/d38bef47b03345f2bad77ece96d4c707.png)

2. 点击"New Group"按钮新建3个分组（Start、Library、User）
   ![新建分组](https://i-blog.csdnimg.cn/direct/2fc57debf42142e0853f06ea0cd5e6f3.png)

3. 添加各分组的文件
   - Start分组: 添加启动文件和相关支持文件
   - Library分组: 添加标准外设库文件
   - User分组: 添加用户代码文件

4. 配置包含路径和宏定义
   - 添加Include Paths: Start、Library、User
   - 添加宏定义: USE_STDPERIPH_DRIVER, STM32F10X_MD

5. 配置调试器设置
   - 选择ST-Link Debugger
   - 勾选"Reset and Run"选项

### 解决常见问题
如果遇到core_cm3.c和core_cm3.h文件版本过旧导致的错误：
1. 下载STM32Cube_FW软件包: [ST官网链接](https://www.st.com.cn/zh/embedded-software/stm32cubef1.html)
2. 从`Drivers\CMSIS\Include`目录下拷贝新版头文件
3. 停用旧版core_cm3.c，改用CMSIS标准接口

### 示例代码
```cpp
#include "stm32f10x.h"
int main(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    while(1) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  
    }
}
```

## 项目编译与下载
编译工程并确保0错误、0警告，然后使用ST-Link下载程序到开发板。

![编译成功](https://i-blog.csdnimg.cn/direct/f91d31ff6e034111af569b5981f41213.png)
![运行结果](https://i-blog.csdnimg.cn/direct/1fb27fecd8fd4214a76819224b295a4a.jpeg)

































   
  

---

