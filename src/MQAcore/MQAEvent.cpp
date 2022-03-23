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

class Priority
{
public:
    Priority(const uint16_t& priority) : __priority(priority) {}
    void setPriority(const uint16_t& priority) { __priority = priority; }
    uint16_t priority(void)const { return this->__priority; }
protected:
    uint16_t __priority;
};
template<class _FunTy>
class functionCont : public Priority
{
public:
    std::function<void(_FunTy)> _Fun;
    functionCont(const std::function<void(_FunTy)>& _fun, const uint16_t& priortiy = 30000) : _Fun(_fun), Priority(priortiy)
    {}
};
bool operator<(const Priority& a, const Priority& b)
{
    return a.priority() < b.priority();
}
template<class _FunContTy, class _ArgTy>
inline void CallAllFun(const _FunContTy& _FunCont, _ArgTy const& _Args)
{
    if (!EventContInit || _FunCont.empty())return;
    for (const auto& _Fun : _FunCont)
    {
        if (!_Args.eventContinue())break;
        if (_Fun._Fun)_Fun._Fun(_Args);
    }
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
namespace MQA::Event
{
#define __MQAEVENT(__Event, __EventData)                                                         \
        std::set<functionCont<__EventData>>& __Event##CallbackCont(void)                        \
        {                                                                                       \
            static std::set<functionCont<__EventData>> __Event##_Callback;                      \
            return __Event##_Callback;                                                          \
        }                                                                                       \
        void clr_##__Event(void){__Event##CallbackCont().clear();}                              \
		void reg_##__Event(const std::function<void(__EventData)>& _Callback, const uint16_t& priority)\
        {__Event##CallbackCont().insert({_Callback, priority});}
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
    Event::SettingEvent _event;
    CallAllFun(Event::SettingCallbackCont(), _event);
}
/*
* 当插件被卸载时将会调用
* 插件销毁，需要在此子程序下结束线程和关闭组件释放内存资源，否则可能引起程序异常(如果未加载任何对象内存资源可以删掉此函数)
*/
EVENT(Enum::EventRet, MQA_End, 0)(void)
{
    Event::EndEvent _event;
    CallAllFun(Event::EndCallbackCont(), _event);
    MQAExceptionWrapper(__UnInit)();
    return _event.operation;
}
/*
* 当插件被载入完成时将会调用
*/
EVENT(Enum::EventRet, MQA_Load, 0)(void)
{
    Event::LoadEvent _event;
    if (!PluginLoad)
        p.push([](int) {MQAExceptionWrapper(__Init)(); });
    CallAllFun(Event::LoadCallbackCont(), _event);
    return _event.operation;
}
/*
* 当插件被启用时将会调用,返回空代表允许启用，否则返回拒绝原因
*/
EVENT(Text, MQA_Enable, 0)(void)
{
    auto InitTime = clock();
    while (!PluginLoad)
    {
        OutTime(1)
        {
            MQAExceptionCode(MQAException::MQAExceptionEnum::MQAInitOutTime, "");
            return "Api初始化失败!";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    Event::EnableEvent _event;
    CallAllFun(Event::EnableCallbackCont(), _event);
    return StrToText(_event.operation);
}
/*
* 当插件被禁用时将会调用，无权拒绝
*/
EVENT(void, MQA_Disable, 0)(void)
{
    Event::DisableEvent _event;
    CallAllFun(Event::DisableCallbackCont(), _event);
}
/*
* 此子程序会分发框架机器人QQ接收到的QQ事件
*/
EVENT(Enum::EventRet, MQA_Event, 4)(Text jsonStr)
{
    if (!PluginLoad)return Enum::EventRet::消息处理_忽略;
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    Event::NormalEvent _event;
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
    CallAllFun(Event::EventCallbackCont(), _event);
    return _event.operation;
}
/*
* 收到私聊消息
*/
EVENT(Enum::EventRet, MQA_PrivateMsg, 4)(Text jsonStr)
{
    if (!PluginLoad)return Enum::EventRet::消息处理_忽略;
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    Event::PrivateEvent _event;
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
    CallAllFun(Event::PrivateMsgCallbackCont(), _event);
    return _event.operation;
}
/*
* 收到群聊消息
*/
EVENT(Enum::EventRet, MQA_Group消息, 4)(Text jsonStr)
{
    if (!PluginLoad)return Enum::EventRet::消息处理_忽略;
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    Event::GroupEvent _event;
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
    CallAllFun(Event::GroupMsgCallbackCont(), _event);
    return _event.operation;
}
/*
* 收到频道消息
*/
EVENT(Enum::EventRet, MQA_GulidMsg, 4)(Text jsonStr)
{
    if (!PluginLoad)return Enum::EventRet::消息处理_忽略;
    Json::Value _json;
    JsonParser::parseStr(&_json, jsonStr);
    Event::GulidEvent _event;
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
    CallAllFun(Event::GulidMsgCallbackCont(), _event);
    return _event.operation;
}

/*
* 插件初始化函数
*/
void CallingConvention __Init()
{
    if (!PluginLoad)
    {
        MQAHModule = LoadLibraryA(APIDLLNAME);
        if (MQAHModule)
        {
            initFuncs(MQAHModule);
            PluginLoad = true;
            Logging::info("插件Api初始化完毕...");
            init();
            MQAExceptionCode(MQAException::MQAExceptionEnum::MQAOK, "插件载入成功！");
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
    if (PluginLoad)
    {
        Logging::info("即将卸载插件...");
        if (MQAHModule != nullptr)
        {
            FreeLibrary(MQAHModule);
            MQAHModule = nullptr;
        }
        p.stop();
        MQAExceptionCode(MQAException::MQAExceptionEnum::MQAOK, "插件正在卸载！");
        PluginLoad = false;
    }
}