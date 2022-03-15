#include <MQAconfig.h>
#include <MQAcore/MQAHeader.h>
#include <GlobalVar.h>
using namespace MQA;
MQA_REGISTER_EVENT
{
	if (EventContInit)return;

	/// <summary>
	/// MYQQA 专属函数注册块
	/// </summary>
	reg_PrivateMsg([](const auto& e) {
		if (e.myUin == e.fromUin)return;
		FrameAPI::OutPut(e.message_content);
		MessageAPI::SendFriendMsg(std::stoll(e.myUin), std::stoll(e.fromUin), e.message_content, 0, 0);
	});
	/// <summary>
	/// 通用函数注册块
	/// </summary>
	reg_Setting([](const auto& e) {
		});
	EventContInit = true;
}