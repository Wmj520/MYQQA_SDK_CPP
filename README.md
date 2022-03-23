# MYQQA_SDK_CPP_Ver1.0.3

MYQQA_SDK_CPP封装了提供给MQA的DLL接口相关的底层逻辑，为插件编程者提供更现代的C++接口。

### 目录

[TOC]



### Demo

```c++
#include <MQAconfig.h>
#include <MQAcore/MQAHeader.h>
#include <GlobalVar.h>
using namespace MQA;
//MQA::Api		MQA 提供的api函数接口
//MQA::Enum		MQA 事件常量
//MQA::Event	MQA 注册事件回调函数
//MQA::Logging	MQA 日志
//MQA::文本代码	MQA 文本代码


void processPrivatMsg(const Event::PrivateEvent& e)
{
	if (e.myUin == e.fromUin)return;
	//日志输出 fun
	Api::FrameAPI::OutPut("fun");
	//日志输出[info]fun
	Logging::info("fun");
	//复读
	Api::MessageAPI::SendFriendMsg(std::stoll(e.myUin), std::stoll(e.fromUin), e.message_content, 0, 0);
}
/*
* 插件入口
* 请在该宏(MQA_REGISTER_EVENT)的作用域内注册回调函数
* 在静态成员初始化、插件系统载入事件之后，插件用户载入事件发生之前被执行,用于配置SDK和注册事件回调
*/
MQA_REGISTER_EVENT
{
	if (EventContInit)return;
	//注册事件回调函数1,优先级20000
	Event::reg_PrivateMsg(processPrivatMsg, 20000);
	//注册事件回调函数2,优先级15000
	Event::reg_PrivateMsg([](const Event::PrivateEvent& e) {
		if (e.myUin == e.fromUin)return;
		Api::FrameAPI::OutPut("lambda expression");
		Api::MessageAPI::SendFriendMsg(std::stoll(e.myUin), std::stoll(e.fromUin), MQA::文本代码::小黄豆表情(1) + e.message_content, 0, 0);
		//阻止后续该事件回调函数执行,低优先级回调函数无权拒绝
		e.eventBlock();
	}, 15000);
	//注册事件回调函数3,优先级10000
	Event::reg_Load([](const Event::LoadEvent& e) {
		//设置事件返回值为忽略,若高优先级回调函数已阻塞则无法修改阻塞状态
		e.retIgnore();
	}, 10000);
	//注册设置窗口,优先级为默认30000
	Event::reg_Setting([](const auto& e) {
		MessageBoxA(nullptr, "Text", "Caption", 0);
		});
	EventContInit = true;
}
```

### 介绍

- `MQA::Api` 命名空间封装了MQA提供的大部分api接口，现更新到MyQQA `1.0.3` 版本
- `MQA::文本代码` 命名空间提供了快速构造MQA文本代码的接口
- `MQA::Enum`命名空间封装了MQA相关常量 `MQAEventEnum` 、事件返回值 `EventRet`...
- `MQA::Event` 命名空间提供了注册MQA各事件回调函数接口，如` reg_PrivateMsg`，并且封装了MQA各事件的数据类，如 `PrivateEvent` 等，将在事件回调函数中传入
- ......

### 预备

本项目使用 [Visual Studio](https://visualstudio.microsoft.com/zh-hans/) 构建，请确保安装了 **Visual Studio 2019** ，并勾选「使用 C++ 的桌面开发」，安装了 **MSVC v142**、**Windows 10 SDK** 组件。

若已安装 **Visual Studio 2019**，请直接打开目录下的 **[MYQQA_SDK_CPP.sln](MYQQA_SDK_CPP.sln)** 文件。

### 修改插件信息

请在 [`MQAHeader.h`](include/MQcore/MQHeader.h) 文件修改插件相关的 `PluginId` 、`PluginAuthor`、`PluginDesc` 、`PluginVersion` 信息，并将项目重命名为你的插件名，并且项目名需要与 `PluginId` 宏一致，否则插件可能会载入失败。

### 编写插件

移除 [`main/MQAdemo.cpp`](main/MQdemo.cpp) 或在其基础上修改，实现自己的功能。

具体API函数和事件函数请在命名空间 `MQA` 内查找。

若有未添加的MQA api函数请自行添加，`MyQQAApi.dll` 载入句柄为`MQAHModule` 。

### 生成项目

在 **Visual Studio** 使用快捷键 **Ctrl + Alt + F7** 生成项目，生成的 **dll文件** 将放在文件夹 **[out](out) **下。

然后只需要将生成的 **dll文件** 拷贝到 **MyQQA\plugin** 文件夹下，然后打开 **MyQQA.exe** ，在 **插件管理** 启用插件即可。

### 注意事项

- 该SDK运行需安装 Visual C++ 可再发行软件包，请提醒用户安装，下载地址见 [最新支持的 Visual C++ 下载](https://support.microsoft.com/zh-cn/help/2977003/the-latest-supported-visual-c-downloads)。

### 问题反馈

如果使用该sdk过程中遇到任何问题、Bug，或有其它意见或建议，欢迎提 [issue](https://github.com/Wmj520/MYQQA_SDK_CPP/issues) ，或者加 **QQ2216193879** 交流讨论。
