#include <MQAconfig.h>
#include <MQAcore//MQAHeader.h>
#include <GlobalVar.h>
#include <json/myJson.hpp>
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DllHModule = hModule;
        break;
    }

    return TRUE;
}

template<class _FunContTy, class _ArgTy>
inline void CallAllFun(const _FunContTy& _FunCont, _ArgTy const& _Args)
{
    if (!EventContInit || _FunCont.empty())return;
    for (const auto& _Fun : _FunCont)
    {
        if (_Fun)_Fun(_Args);
    }
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
namespace MQA
{
#define __MQAEVENT(__Event, __EventData)                                                        \
        std::vector<std::function<void(__EventData)>>& __Event##CallbackCont(void)              \
        {                                                                                       \
            static std::vector<std::function<void(__EventData)>> __Event##_Callback;            \
            return __Event##_Callback;                                                          \
        }                                                                                       \
        void clr_##__Event(void){__Event##CallbackCont().clear();}                              \
		void reg_##__Event(const std::function<void(__EventData)>& _Callback)                   \
        {__Event##CallbackCont().push_back(_Callback);}
    __MQAEVENT(Setting, SettingEvent const&)
    __MQAEVENT(End, EndEvent const&)
    __MQAEVENT(Load, LoadEvent const&)
	__MQAEVENT(Enable, EnableEvent const&)
	__MQAEVENT(Disable, DisableEvent const&)
	__MQAEVENT(PrivateMsg, PrivateEvent const&)
	__MQAEVENT(GroupMsg, GroupEvent const&)
	__MQAEVENT(GulidMsg, GulidEvent const&)
	__MQAEVENT(Event, NormalEvent const&)
#undef __MQAEVENT
}
using namespace MQA;
/*
* 插件信息
*/
EVENT(Text, MQA_Info, 0)(void)
{
#ifdef USE_JSONCPP
    MQInfoJson["name"] = PluginId;
    MQInfoJson["author"] = PluginAuthor;
    MQInfoJson["description"] = PluginDesc;
    MQInfoJson["version"] = PluginVer;
    MQInfoJson["skey"] = PluginSkey;
    MQInfoJson["sdk"] = PluginSdk;
    MQInfoStr = MQInfoJson.toStyledString();
    return StrToText(MQInfoStr);
#else
    return "";
#endif
}
/*
* 右键点击插件（如果未设置窗口可删除此函数）
*/
EVENT(void, MQA_Set, 0)(void)
{
    SettingEvent _event;
    CallAllFun(SettingCallbackCont(), _event);
}
/*
* 当插件被卸载时将会调用
* 插件销毁，需要在此子程序下结束线程和关闭组件释放内存资源，否则可能引起程序异常(如果未加载任何对象内存资源可以删掉此函数)
*/
EVENT(EventRet, MQA_End, 0)(void)
{
    EndEvent _event;
    CallAllFun(EndCallbackCont(), _event);
    MQAExceptionWrapper(__UnInit)();
    return _event.operation;
}
/*
* 当插件被载入完成时将会调用
*/
EVENT(EventRet, MQA_Load, 0)(void)
{
    LoadEvent _event;
    if (!APIInitSuccess)
        p.push([](int) {MQAExceptionWrapper(__Init)(); });
    CallAllFun(LoadCallbackCont(), _event);
    return _event.operation;
}
/*
* 当插件被启用时将会调用,返回空代表允许启用，否则返回拒绝原因
*/
EVENT(Text, MQA_Enable, 0)(void)
{
    static EnableEvent _event;
    auto InitTime = clock();
    while (!APIInitSuccess)
    {
        OutTime(3)
        {
            MQAExceptionCode(MQAException::MQAExceptionEnum::MQAInitOutTime, "");
            return "Api初始化失败!";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    _event = std::move(EnableEvent());
    CallAllFun(EnableCallbackCont(), _event);
    return StrToText(_event.operation);
}
/*
* 当插件被禁用时将会调用，无权拒绝
*/
EVENT(void, MQA_Disable, 0)(void)
{
    DisableEvent _event;
    CallAllFun(DisableCallbackCont(), _event);
}
/*
* 此子程序会分发框架机器人QQ接收到的QQ事件
*/
EVENT(EventRet, MQA_Event, 4)(Text jsonStr)
{
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    NormalEvent _event;
    parseJson(fromMyUin);
    parseJson(fromGroupUin);
    parseJson(fromGroupName);
    parseJson(fromOpUin);
    parseJson(fromOpNick);
    parseJson(fromUin);
    parseJson(fromNick);
    parseJson(fromSeq);
    parseJson(fromReq);
    parseJson(fromTime);
    parseJson(fromRandom);
    parseJson(fromContent);
    parseJson(type);
    parseJson(subType);
    CallAllFun(EventCallbackCont(), _event);
    return _event.operation;
}
/*
* 收到私聊消息
*/
EVENT(EventRet, MQA_PrivateMsg, 4)(Text jsonStr)
{
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    PrivateEvent _event;
    parseJson(fromUin);
    parseJson(myUin);
    parseJson(toUin);
    parseJson(fromReq);
    parseJson(fromRecvTime);
    parseJson(fromGroup);
    parseJson(fromSendTime);
    parseJson(fromRandom);
    parseJson(pieceIndex);
    parseJson(pieceCount);
    parseJson(pieceFlag);
    parseJson(message_content);
    parseJson(buddleId);
    parseJson(msgType);
    parseJson(subType);
    parseJson(subTempMsgType);
    parseJson(red_packet_type);
    parseJson(chatToken);
    parseJson(fromEventUin);
    parseJson(fromEventNick);
    parseJson(fileId);
    parseJson(fileMd5);
    parseJson(fileName);
    parseJson(fileSize);
    CallAllFun(PrivateMsgCallbackCont(), _event);
    return _event.operation;
}
/*
* 收到群聊消息
*/
EVENT(EventRet, MQA_Group消息, 4)(Text jsonStr)
{
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    GroupEvent _event;
    parseJson(fromUin);
    parseJson(myUin);
    parseJson(fromReq);
    parseJson(fromRecvTime);
    parseJson(fromGroup);
    parseJson(groupName);
    parseJson(fromCard);
    parseJson(fromSendTime);
    parseJson(fromRandom);
    parseJson(pieceIndex);
    parseJson(pieceCount);
    parseJson(pieceFlag);
    parseJson(subType);
    parseJson(title);
    parseJson(message_content);
    parseJson(reply_info);
    parseJson(buddleId);
    parseJson(lon);
    parseJson(lat);
    CallAllFun(GroupMsgCallbackCont(), _event);
    return _event.operation;
}
/*
* 收到频道消息
*/
EVENT(EventRet, MQA_GulidMsg, 4)(Text jsonStr)
{
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    GulidEvent _event;
    parseJson(senderId);
    parseJson(senderNick);
    parseJson(myUin);
    parseJson(fromReq);
    parseJson(fromRecvTime);
    parseJson(guildId);
    parseJson(guildChannelId);
    parseJson(guildName);
    parseJson(guildChannelName);
    parseJson(fromSendTime);
    parseJson(fromRandom);
    parseJson(pieceIndex);
    parseJson(pieceCount);
    parseJson(pieceFlag);
    parseJson(subType);
    parseJson(title);
    parseJson(message_content);
    parseJson(reply_info);
    parseJson(buddleId);
    parseJson(lon);
    parseJson(lat);
    CallAllFun(GulidMsgCallbackCont(), _event);
    return _event.operation;
}

/*
* 插件初始化函数
*/
void CallingConvention __Init()
{
    if (!PluginEnable)
    {
        MQHModule = LoadLibraryA(APIDLLNAME);
        if (MQHModule)
        {
            initFuncs(MQHModule);
            APIInitSuccess = true;
            MQAExceptionCode(MQAException::MQAExceptionEnum::MQAOK, "插件载入成功！");
            FrameAPI::OutPut("插件Api初始化完毕...");
            init();
            PluginEnable = true;
        }
        else
        {
            throw(MQAException(MQAException::MQAExceptionEnum::MQADllInitFailed));
        }
    }
}
/*
* 插件释放函数
*/
void CallingConvention __UnInit()
{
    if (PluginEnable)
    {
        FrameAPI::OutPut("即将卸载插件...");
        if (MQHModule != nullptr)
        {
            FreeLibrary(MQHModule);
            MQHModule = nullptr;
        }
        p.stop();
        MQAExceptionCode(MQAException::MQAExceptionEnum::MQAOK, "插件正在卸载！");
        PluginEnable = false;
    }
}