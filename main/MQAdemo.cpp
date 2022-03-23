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