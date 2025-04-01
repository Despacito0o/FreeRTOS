# STM32 Standard Peripheral Library Development Environment Setup Guide

## Prerequisites
1. Install Keil MDK development environment
2. Download STM32 Standard Peripheral Library

## Detailed Steps

### 1. Create New Project
1. Open Keil and create a new project
   ![New Project](https://i-blog.csdnimg.cn/direct/456e7f1370cd4f5d90b204dcbd37ff2a.png)

2. Select a folder to store the project, name it and click Save
   ![Name Project](https://i-blog.csdnimg.cn/direct/59e3493295b94cdaaa53beb27745c2e7.png)

3. Select your chip model (STM32F103C8 in this example) and click OK
   ![Select Chip](https://i-blog.csdnimg.cn/direct/95742a07675b467a9846eacbaf9e001c.png)

4. Close the popup window
   ![Close Window](https://i-blog.csdnimg.cn/direct/3fa8e6d04a2b43a59f3e0c102107a86c.png)

5. Add three subfolders to the newly created project folder: Start, Library, and User
   ![Add Folders](https://i-blog.csdnimg.cn/direct/315e2eb94b954e86a950d86e0363cb3c.png)

### 2. Download and Configure Standard Peripheral Library
1. Visit ST's official website to download the latest standard peripheral library: [Click to Download](https://www.st.com.cn/zh/embedded-software/stsw-stm32054.html)
   ![Download Library](https://i-blog.csdnimg.cn/direct/1868afb0b36246ab98824aaa4835d206.png)

2. Click "Get Latest Version" and accept the license agreement
   ![Accept Agreement](https://i-blog.csdnimg.cn/direct/4f31f48d21184a6488a683fb3600ff1f.png)

3. Log in with your ST account
   ![Login](https://i-blog.csdnimg.cn/direct/d993c74d66424daba63851da6545deb3.png)

4. Click "Download latest" to download the latest version
   ![Download Latest](https://i-blog.csdnimg.cn/direct/658af4d3aaa04453906969c731e94c8a.png)

5. Extract the downloaded files
   ![Extract Files](https://i-blog.csdnimg.cn/direct/82860324304248a9bad5e8959c45db79.png)

### 3. File Configuration
1. Find the startup file path: `Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm`, copy all files to the Start folder
   ![Copy Startup Files](https://i-blog.csdnimg.cn/direct/8f5c0ca058b9489f91cb8b49b408f1fd.png)

2. Navigate to: `Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x`, copy related files to the Start folder
   ![Copy Device Support Files](https://i-blog.csdnimg.cn/direct/734a5886f8684d41879e48f89226fd66.png)

3. Navigate to: `Libraries\CMSIS\CM3\CoreSupport`, copy core support files to the Start folder
   ![Copy Core Support Files](https://i-blog.csdnimg.cn/direct/24f5a0388cf040ee84d68230113a7fdf.png)

4. Navigate to: `Libraries\STM32F10x_StdPeriph_Driver\src`, copy folder contents to the Library folder
   ![Copy Standard Peripheral Driver Files](https://i-blog.csdnimg.cn/direct/48399df386f64596a552435c93296bd6.png)

5. Open the inc folder (path: `Libraries\STM32F10x_StdPeriph_Driver\inc`), copy folder contents to the Library folder
   ![Copy Header Files](https://i-blog.csdnimg.cn/direct/d7537287252a4dcaa0d95aa38caf5fb7.png)

6. Navigate to: `Project\STM32F10x_StdPeriph_Template`, copy template files to the User folder
   ![Copy Template Files](https://i-blog.csdnimg.cn/direct/b61aa4c1fdf04ea48ec8ff18f9d7e90f.png)

### 4. Project Configuration
1. Return to Keil, click the project file management button
   ![Project Management](https://i-blog.csdnimg.cn/direct/d38bef47b03345f2bad77ece96d4c707.png)

2. Click "New Group" button to create 3 groups (Start, Library, User)
   ![Create Groups](https://i-blog.csdnimg.cn/direct/2fc57debf42142e0853f06ea0cd5e6f3.png)

3. Add files to each group
   - Start group: Add startup files and related support files
   - Library group: Add standard peripheral library files
   - User group: Add user code files

4. Configure include paths and macro definitions
   - Add Include Paths: Start, Library, User
   - Add macro definitions: USE_STDPERIPH_DRIVER, STM32F10X_MD

5. Configure debugger settings
   - Select ST-Link Debugger
   - Check "Reset and Run" option

### 5. Common Problem Solving
If you encounter errors due to outdated core_cm3.c and core_cm3.h files:
1. Download STM32Cube_FW software package: [ST Official Link](https://www.st.com.cn/zh/embedded-software/stm32cubef1.html)
2. Copy new header files from `Drivers\CMSIS\Include` directory
3. Disable old core_cm3.c and use CMSIS standard interface

### 6. Example Code
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

## Project Compilation and Download
Compile the project and ensure 0 errors, 0 warnings, then use ST-Link to download the program to the development board.

![Compilation Success](https://i-blog.csdnimg.cn/direct/f91d31ff6e034111af569b5981f41213.png)
![Running Result](https://i-blog.csdnimg.cn/direct/1fb27fecd8fd4214a76819224b295a4a.jpeg) 