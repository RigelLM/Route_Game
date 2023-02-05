MyProject
===========================
#### 环境依赖
- Visual studio 2022
- C++14
***
#### 第三方库
##### OpenGL库
- 渲染运算: OpenGL数学库: glm
- 窗口管理: OpenGL窗口库: GLFW
- 函数管理: OpenGL函数库: glad
##### stb库
- 图片读取,写入
##### freetype库
- 文本渲染
##### irrKlang库
- 游戏音频
##### Assimp库
- 模型导入
***
#### 部署步骤
>具体步骤图片详解请看Docs文件夹下Pics/SetUp文件夹之中的图片
1. 双击打开***Solution.sln***
2. 右侧***解决方案资源管理器中***,找到***MyProject项目***,*右键*打开***属性页***
>千万!!!千万!!!!千万!!!!!  
>要注意顶部的配置和平台选项!!!!!  
>一定要选择所有配置和所有平台!!!!!  

3. 在属性页点击***常规***,设置***输出目录***和***中间目录*** 
>输出目录: $(ProjectDir)Temp\Link\$(Platform)\$(Configuration)\  
>中间目录: $(ProjectDir)Temp\Compile\$(Platform)\$(Configuration)\

4. 点击***调试***,设置***工作目录***
>工作目录: $(ProjectDir)Bin\$(Platform)\$(Configuration)\  

5. 点击***VC++目录***,设置***包含目录***和***库目录*** 
>包含目录: $(ProjectDir)Include;$(IncludePath)  
>库目录: $(ProjectDir)Lib;$(LibraryPath)

6. 点击***C/C++***,设置***附加包含目录***
>附加包含目录: $(ProjectDir)Src\Headers;%(AdditionalIncludeDirectories)  

7. 点击*链接器*下的***输入***,设置***附加依赖项***
>附加依赖项: 一定要将Lib文件夹下的所有文件名称加进去  
>如:  
>opengl32.lib  
>glfw3.lib  
>assimp-vc140-mt.lib  
>freetype.lib  
>irrKlang.lib

8. 点击***生成事件***下的***生成后事件***,设置***命令行*** 
>命令行: xcopy $(TargetPath) $(ProjectDir)Bin\$(Platform)\$(ConfigurationName)\ /y  
>xcopy $(ProjectDir)Resource $(ProjectDir)Bin\$(Platform)\$(ConfigurationName)\Resource /e/y

9. 之后点击*确认*,在顶部的选项中,选择**Release或者Debug模式**,***一定要选择x64!!!!***.
10. *右键* ***MyProject项目***,点击***重新生成***,即可在Bin/x64/Release(或者Debug)文件夹下找到新生成的exe文件,运行查看是否成功
***
#### 错误排查
1. 如果#Include指令显示"无法打开xxx.h文件",记得去MyProject属性页查看是否将Headers和Include文件夹加入包含目录和附加包含目录
2. 如果生成时报错,显示"无法打开xxx.lib文件",记得去Lib文件夹查看xxx.lib文件是否在内
3. 如果生成时报错,显示有"无法解析的外部符号",记得查看每个文件开头的预编译指令,在引入第三方库的时候是否按照要求预定义宏
4. 如果生成时报错,显示有"无法解析的外部符号",记得在顶部查看生成选项是否为x64
5. 如果生成时报错,显示"命令行xxxxxxx", 记得去Bin文件夹下的Release和Debug文件夹下查看Resource文件夹是否存在,并且确认项目文件夹下的Resource文件夹是否存在
6. 如果运行时报错,记得去Release和Debug文件夹下查看所用的第三方库的dll静态链接库是否在内
7. 如果你的问题不属于上述任何一个类型,请将Temp/Compile文件夹下的x64或者Win32文件夹下Debug或者Release文件夹内的MyProject.log文件内容于报错处的代码截图一并发送给作者
***
#### 目录结构
```
.
└─MyProject
    ├─Bin                        //编译生成的文件
    │  └─x64                     //平台
    │      ├─Debug               //编译类型
    │      │  └─Resource         //资源
    │      │      ├─Fonts
    │      │      ├─Levels
    │      │      ├─Models
    │      │      ├─Shaders
    │      │      └─Textures
    │      └─Release
    │          └─Resource
    │              ├─Fonts
    │              ├─Levels
    │              ├─Models
    │              ├─Shaders
    │              └─Textures
    ├─Docs                       //文档
    │  
    ├─Include                    //第三方库头文件
    │  ├─assimp
    │  ├─dlg
    │  ├─freetype
    │  ├─glad
    │  ├─GLFW
    │  ├─glm
    │  ├─irrKlang
    │  ├─KHR
    │  └─stb
    ├─Lib                        //第三方静态库
    ├─Resource
    │  ├─Fonts
    │  ├─Levels
    │  ├─Models
    │  ├─Shaders
    │  └─Textures
    ├─Src                        //源码
    │  ├─Headers                 //源码头文件
    │  └─Sources                 //源码源文件
    └─Temp                       //中间文件
        ├─Compile                //编译中间文件
        │  └─x64
        │      ├─Debug
        │      └─Release
        └─Link                   //链接中间文件
            └─x64
                ├─Debug
                └─Release

```
***
#### 当前版本内容
##### Game类
- 工具类
- 游戏循环主体
- 包含游戏状态等参数
- 包含渲染函数
##### ResourceManager类
- 工具类
- 实现从文件读取数据
- 支持shader读取
- 支持纹理贴图读取
- 支持关卡数据读取
##### Shader类
- 工具类
- 实现shaderProgram
- 支持关卡渲染,物体渲染,光照渲染,文本渲染
##### Renderer类
- 工具类
- 实现立方体渲染
##### Texture类
- 工具类
- 实现2D纹理贴图
- 实现3D纹理贴图
##### Camera类
- 基础类
- 实现3D移动
##### GameLevel类
- 基础类
- 实现关卡渲染
##### GameObject类
- 基础类
- 实现物体渲染
##### Light类
- 基础类
- 实现文本渲染
##### TextRenderer类
- 基础类
- 实现文本渲染
##### PostProcessor类
- 基础类
- 实现特效渲染
- 实现阴影渲染
