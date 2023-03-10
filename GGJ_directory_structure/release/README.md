
# Route

===========================

## 环境依赖

- Visual studio 2022
- C++

***

## 部署步骤

- **Route_Game/GGJ_directory_structure/release目录下为游戏的Release版本，包含可执行文件**
- **Route_Game/GGJ_directory_structure/src目录下为游戏的源码**

1. **确保当前电脑安装了Visual Studio，版本为2017及以上。**
2. 运行Script文件夹下的**Build.bat**文件，该脚本会自动生成电脑对应版本的Visual Studio解决方案文件。
3. 打开Collection文件夹下生成的**Project.sln**文件。
4. 在上方解决方案配置中选择Debug/Release/Dist，按**Ctrl+Shift+B**生成解决方案。
5. 当下方输出栏出现“**已完成生成项目“Game.vcxproj”的操作**”字样时，说明项目已经生成完毕。
6. 运行Script文件夹下的**Publish.bat**文件，当脚本询问“**目标 Publish\assets 是文件名还是目录名**”时，选择**目录名**。该脚本会自动生成游戏的可执行文件已经相关依赖文件。
7. Collection文件夹下会自动生成**Publish目录**，这就是游戏的本体。你可以将这个 publich 文件夹， 复制到任何位置，都不会影响文件夹内*可执行文件*的运行。可执行文件需要的一切资源，都被集成在了 publish 目录内。
8. 如果需要重新部署，运行Script文件夹下的**Clear.bat**文件，该脚本会自动清理所有生成的文件，只留下源码。

***

## 怎么玩这款游戏

键盘按键布置

- 开始界面：按键 左右箭头：控制按钮选项，按键 Enter：确认键
- 游戏内：按键 WASD/上下左右：控制角色移动，按键 E：互动键

**请注意，当系统输入法为中文模式时，游戏将无法识别键盘按键。请务必切换到英文输入法模式。**

