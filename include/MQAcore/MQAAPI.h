#pragma once
#ifndef __MQAAPI_DEFINE__
#define __MQAAPI_DEFINE__
///////////////////////
///////////////////////
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <vector>
#include <functional>
#include <GlobalVar.h>
#include "MQAType.h"
#include "MQAException.hpp"

#ifndef StrToText
template<class _Ty>
typename std::enable_if<std::is_same<_Ty, Str>::value, Text>::type
isStr(_Ty& _Data)
{
	return _Data.c_str();
}
template<class _Ty>
typename std::enable_if<!std::is_same<_Ty, Str>::value, _Ty>::type
isStr(_Ty& _Data)
{
	return _Data;
}
#define StrToText(__Var) isStr((__Var))
#define _TextVaild(__Var) (__Var)  ? (__Var) : ""
#define _PtrVaild(__Var)  (__Var)  ? (__Var) : nullptr
#endif
namespace MQA::Detail
{
	extern std::vector<std::function<void(HMODULE)>> apiFuncInitializers;
	static bool addFuncInit(const std::function<void(HMODULE)>& initializer) {
		apiFuncInitializers.push_back(initializer);
		return true;
	}
#define MQAAPI(Name, ReturnType, ...) using Name##_FUNC = std::function<ReturnType (__stdcall)(__VA_ARGS__)>; \
	extern Name##_FUNC _##Name; \
	template <typename... Args> \
	ReturnType Name (Args&&... args) \
	{ \
		return p.push([&args...](int iThread){ return _##Name(std::forward<Args>(args)...); }).get(); \
	} 
#include "MyQQAAPI.inc"
#undef MQAAPI
}
static void initFuncs(const HMODULE& hModule)
{
	for (const auto& initializer : MQA::Detail::apiFuncInitializers) {
		initializer(hModule);
	}
	MQA::Detail::apiFuncInitializers.clear();
}

namespace MQA::文本代码
{
	constexpr auto __str_replace_once = [](Str& str, const Str& replace) {
		str.replace(str.find_first_of("%s"), 2, replace);
	};
	constexpr Text _MQACodeStr[] =
	{
		"[@%s]", "[@all]", "[bigFace,Id=%s,name=%s,hash=%s,flag=%s]", "[pic,hash=%s]", "[pic,hash=%s,guid=%s]",
		"[Audio,hash=%s,token=%s,url=%s]", "[AudioFile,path=%s]", "[picFile,path=%s]", "[bq%s]", "[litleVideo,linkParam=%s,hash1=%s,hash2=%s]",
		"[newFace,name=%s,Id=%s]", "[bigFace,Id=%s,name=%s,hash=%s,flag=%s]",
		"[Reply,Card=%s,Content=%s,SendQQID=%s,RequestID=%s,SendTime=%s]"
	};
	inline Str 艾特个人(LLInteger _atQQ)
	{
		if (!_atQQ)return "";
		Str _str(_MQACodeStr[0]);
		__str_replace_once(_str, std::to_string(_atQQ));
		return _str;
	}
	inline Str 艾特全体(void) { return _MQACodeStr[1]; }
	inline Str 表情包(Str id, Str name, Str hash, Str flag)
	{
		if (id.empty() || name.empty() || hash.empty() || flag.empty())return "";
		Str _str(_MQACodeStr[2]);
		__str_replace_once(_str, id);
		__str_replace_once(_str, name);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, flag);
		return _str;
	}
	inline Str 群聊图片(Str hash)
	{
		if (hash.empty())return "";
		Str _str(_MQACodeStr[3]);
		__str_replace_once(_str, hash);
		return _str;
	}
	inline Str 私聊图片(Str hash, Str guid)
	{
		if (hash.empty() || guid.empty())return "";
		Str _str(_MQACodeStr[4]);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, guid);
		return _str;
	}
	inline Str 语音(Str hash, Str token, Str url)
	{
		if (hash.empty() || token.empty() || url.empty())return "";
		Str _str(_MQACodeStr[5]);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, token);
		__str_replace_once(_str, url);
		return _str;
	}
	inline Str 语音_本地(Str path)
	{
		if (path.empty())return "";
		Str _str(_MQACodeStr[6]);
		__str_replace_once(_str, path);
		return _str;
	}
	inline Str 图片_本地(Str path)
	{
		if (path.empty())return "";
		Str _str(_MQACodeStr[7]);
		__str_replace_once(_str, path);
		return _str;
	}
	inline Str 小黄豆表情(Integer id)
	{
		Str _str(_MQACodeStr[8]);
		__str_replace_once(_str, std::to_string(id));
		return _str;
	}
	inline Str 小视频(Str link, Str hash1, Str hash2)
	{
		Str _str(_MQACodeStr[9]);
		__str_replace_once(_str, link);
		__str_replace_once(_str, hash1);
		__str_replace_once(_str, hash2);
		return _str;
	}
	inline Str 新黄豆(Str name, Integer id)
	{
		Str _str(_MQACodeStr[10]);
		__str_replace_once(_str, name);
		__str_replace_once(_str, std::to_string(id));
		return _str;
	}
	inline Str 大表情(Integer id, Str name, Str hash, Str flag)
	{
		Str _str(_MQACodeStr[11]);
		__str_replace_once(_str, std::to_string(id));
		__str_replace_once(_str, name);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, flag);
		return _str;
	}
	inline Str 回复消息(Str Card, Str Content, LLInteger SendQQID, Str RequestID, Str SendTime)
	{
		Str _str(_MQACodeStr[12]);
		__str_replace_once(_str, Card);
		__str_replace_once(_str, Content);
		__str_replace_once(_str, std::to_string(SendQQID));
		__str_replace_once(_str, RequestID);
		__str_replace_once(_str, SendTime);
		return _str;
	}
}
namespace MQA::Api
{
	namespace FrameAPI
	{
		inline void OutPut(Str content)
		{
			return MQA::Detail::Output(StrToText(content));
		}
		//取在线QQ，#换行符的，一行一个
		inline Text GetOnlineQQ()
		{
			return MQA::Detail::GetOnlineQQ();
		}
		//取所有QQ，#换行符的，一行一个
		inline Text GetAllQQ()
		{
			return MQA::Detail::GetAllQQ();
		}
		//添加QQ，添加QQ到框架里
		inline bool AddQQ(Text QQ, Str pwd, Integer type, bool savePwd)
		{
			return MQA::Detail::AddQQ(StrToText(QQ), StrToText(pwd), StrToText(type), StrToText(savePwd));
		}
		//获取登录二维码，例如：{"qrcode_path":"C:\Users\13301\Desktop\MyQQA\data\cache\363751070.jpg","qrcode_sign":"33DBDB7583E601FFBBF0BF38FD1DE8C41293F821F74D2E40"}
		inline Text GetQrcode(Text QQ)
		{
			return MQA::Detail::GetQrcode(QQ);
		}
		inline Text GetOffQQ(void)
		{
			return MQA::Detail::GetOffQQ();
		}
		//检查登录二维码状态，具体返回值请看文档, 
		inline Text CationQrcode(LLInteger QQ)
		{
			return MQA::Detail::CationQrcode(QQ);
		}
		//登录指定QQ，应确保QQ号码在列表中已存在
		inline void Login(LLInteger botQQ)
		{
			return MQA::Detail::Login(StrToText(botQQ));
		}
		//下线指定QQ，应确保QQ号码已在列表中且在线
		inline void Logout(LLInteger botQQ)
		{
			return MQA::Detail::Logout(StrToText(botQQ));
		}
		//删除指定QQ下线，应确保QQ号码在列表中已存在
		inline void Delete(LLInteger botQQ)
		{
			return MQA::Detail::Delete(StrToText(botQQ));
		}
		//取框架版本号
		inline Text GetVer()
		{
			return MQA::Detail::GetVer();
		}
		//取机器人状态 0未登录，1连接成功，2登录成功，3上线成功，4注册成功，5登录完毕，6登录失败，7心跳异常，8账号冻结，9密码错误
		inline Integer GetBotStatus(Str botQQ)
		{
			return MQA::Detail::GetBotStatus(StrToText(botQQ));
		}
	}
	namespace MessageAPI
	{
		inline Integer SendFriendMsg(LLInteger botQQ, LLInteger objQQ, Str msgContent, Integer req, LLInteger random)
		{
			return MQA::Detail::SendFriendMsg(StrToText(botQQ), StrToText(objQQ), StrToText(msgContent), StrToText(req), StrToText(random));
		}
		inline Integer SendFriendXMLMsg(LLInteger botQQ, LLInteger objQQ, Str msgContent, Integer req, LLInteger random)
		{
			return MQA::Detail::SendFriendXMLMsg(StrToText(botQQ), StrToText(objQQ), StrToText(msgContent), StrToText(req), StrToText(random));
		}
		inline Integer SendGroupMsg(LLInteger botQQ, LLInteger groupId, Str msgContent, bool anonymous)
		{
			return MQA::Detail::SendGroupMsg(StrToText(botQQ), StrToText(groupId), StrToText(msgContent), StrToText(anonymous));
		}
		inline Integer SendGroupXMLMsg(LLInteger botQQ, LLInteger groupId, Str msgContent, bool anonymous)
		{
			return MQA::Detail::SendGroupXMLMsg(StrToText(botQQ), StrToText(groupId), StrToText(msgContent), StrToText(anonymous));
		}
		inline Integer SendGroupMemberMsg(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Str msgContent, Integer req, LLInteger random)
		{
			return MQA::Detail::SendGroupMemberMsg(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(msgContent), StrToText(req), StrToText(random));
		}
		inline Integer SendGuildMsg(LLInteger botQQ, LLInteger guildId, LLInteger subGuildId, Str msgContent)
		{
			return MQA::Detail::SendGuildMsg(StrToText(botQQ), StrToText(guildId), StrToText(subGuildId), StrToText(msgContent));
		}
		inline Integer GetMsgReq(void)
		{
			return MQA::Detail::GetMsgReq();
		}
		inline LLInteger GetMsgRandom(void)
		{
			return MQA::Detail::GetMsgRandom();
		}
		inline bool PbMsgWithDraw_Friend(LLInteger botQQ, LLInteger objQQ, Integer req, LLInteger random, Integer recvTime)
		{
			return MQA::Detail::PbMsgWithDraw_Friend(StrToText(botQQ), StrToText(objQQ), StrToText(req), StrToText(random), StrToText(recvTime));
		}
		inline bool PbMsgWithDraw_Group(LLInteger botQQ, LLInteger groupId, Integer req, LLInteger random)
		{
			return MQA::Detail::PbMsgWithDraw_Group(StrToText(botQQ), StrToText(groupId), StrToText(req), StrToText(random));
		}
		inline Text GetFriendMsg(LLInteger botQQ, Integer fromReq, Integer fromSendTime, LLInteger fromSeq)
		{
			return MQA::Detail::GetFriendMsg(StrToText(botQQ), StrToText(fromReq), StrToText(fromSendTime), StrToText(fromSeq));
		}
		inline Text GetGroupMsg(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer fromReq, Integer fromRecvTime, LLInteger fromMsgRandom)
		{
			return MQA::Detail::GetGroupMsg(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(fromReq), StrToText(fromRecvTime), StrToText(fromMsgRandom));
		}
		//发送群json消息
		inline Integer SendGroupJson(LLInteger botQQ, LLInteger groupId, Str json, bool anony)
		{
			return MQA::Detail::SendGroupJson(StrToText(botQQ), StrToText(groupId), StrToText(json), StrToText(anony));
		}
	}
	namespace FriendAPI
	{

		//访问对象QQ空间
		inline bool BrowseQzone(LLInteger botQQ, LLInteger objQQ, Str log)
		{
			return MQA::Detail::BrowseQzone(StrToText(botQQ), StrToText(objQQ), StrToText(log));
		}
		//删除好友
		inline bool DelFriend(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::DelFriend(StrToText(botQQ), StrToText(objQQ));
		}
		//设置特别关心
		inline void SetSpecialCare(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::SetSpecialCare(StrToText(botQQ), StrToText(objQQ));
		}
		//置屏蔽用户 类型1 = 屏蔽 2 = 解除
		inline void SetShieldedFriend(LLInteger botQQ, LLInteger objQQ, Integer type)
		{
			return MQA::Detail::SetShieldedFriend(StrToText(botQQ), StrToText(objQQ), StrToText(type));
		}
		/// <summary>
		/// 取好友文件下载链接
		/// </summary>
		/// <param name="botQQ"></param>
		/// <param name="FileId"></param>
		/// <param name="fileName"></param>
		/// <returns></returns>
		inline Text GetFriendFileDownUrl(LLInteger botQQ, Str FileId, Str fileName)
		{
			return MQA::Detail::GetFriendFileDownUrl(StrToText(botQQ), StrToText(FileId), StrToText(fileName));
		}
		//查询好友名片，返回json
		inline Text GetFriendCard(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::GetFriendCard(StrToText(botQQ), StrToText(objQQ));
		}
		inline Text GetNickCache(LLInteger objQQ)
		{
			return MQA::Detail::GetNickCache(objQQ);
		}
		inline Text GetNick_Acquisition(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::GetNick_Acquisition(StrToText(botQQ), StrToText(objQQ));
		}
		//取好友列表，返回json
		inline Text GetFriends(LLInteger botQQ)
		{
			return MQA::Detail::GetFriends(StrToText(botQQ));
		}
		//拍一拍_好友头像
		inline bool TakeFriendsPic(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::TakeFriendsPic(StrToText(botQQ), StrToText(objQQ));
		}
		//取好友图片上传信息
		inline Text GetUploadInfo(LLInteger botQQ, LLInteger objQQ, Str pic_md5, LLInteger pic_size)
		{
			return MQA::Detail::GetUploadInfo(StrToText(botQQ), StrToText(objQQ), StrToText(pic_md5), StrToText(pic_size));
		}
		//取个性签名
		inline Text GetSign(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::GetSign(StrToText(botQQ), StrToText(objQQ));
		}

		//点赞
		inline Text Like(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::Like(StrToText(botQQ), StrToText(objQQ));
		}
		//取好友在线状态：“在线”“离开”...
		inline Text GetFriendOnlineStatus(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::GetFriendOnlineStatus(StrToText(botQQ), StrToText(objQQ));
		}

		inline Text AddFriend(LLInteger botQQ, LLInteger objQQ, Str Anwser)
		{
			return MQA::Detail::AddFriend(StrToText(botQQ), StrToText(objQQ), StrToText(Anwser));
		}
		inline Text UploadFriendPic(LLInteger botQQ, LLInteger objQQ, Str img_path)
		{
			return MQA::Detail::UploadFriendPic(StrToText(botQQ), StrToText(objQQ), StrToText(img_path));
		}
		inline Text UploadFriendAudio(LLInteger botQQ, LLInteger objQQ, Str file_path)
		{
			return MQA::Detail::UploadFriendAudio(StrToText(botQQ), StrToText(objQQ), StrToText(file_path));
		}
		inline Text UploadFriendPicEx(LLInteger botQQ, LLInteger objQQ, Integer ptr, Integer len)
		{
			return MQA::Detail::UploadFriendPicEx(StrToText(botQQ), StrToText(objQQ), StrToText(ptr), StrToText(len));
		}

		//处理好友验证，#好友事件_好友请求
		inline void ApplyFriendEvent(LLInteger botQQ, LLInteger objQQ, LLInteger fromSeq, Integer op)
		{
			return MQA::Detail::ApplyFriendEvent(StrToText(botQQ), StrToText(objQQ), StrToText(fromSeq), StrToText(op));
		}
		inline Text UploadFriendAudioEx(LLInteger botQQ, LLInteger objQQ, Integer ptr, Integer len)
		{
			return MQA::Detail::UploadFriendAudioEx(StrToText(botQQ), StrToText(objQQ), StrToText(ptr), StrToText(len));
		}

	}
	namespace GroupAPI
	{

		//群聊打卡，返回如：今日已成功打卡！
		inline Str Groupclock(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::Groupclock(StrToText(botQQ), StrToText(groupId));
		}
		//创建群聊，成功返回groupId等信息{ "ec":0,"errcode" : 0,"em" : "","gu" : 914856344,"gc" : 914856344 }，http模式创建群聊，请注意调用频率
		inline Str CreateGroup(LLInteger botQQ, Str groupName, Str groupClass)
		{
			return MQA::Detail::CreateGroup(StrToText(botQQ), StrToText(groupName), StrToText(groupClass));
		}
		/// <summary>
		/// 处理群验证
		/// </summary>
		/// <param name="botQQ"></param>
		/// <param name="groupId"></param>
		/// <param name="objQQ"></param>
		/// <param name="fromSeq"></param>
		/// <param name="op">11同意 12拒绝 14忽略</param>
		/// <param name="fromType">群事件_我被邀请加入群、群事件_某人申请加群</param>
		/// <param name="reason">拒绝理由</param>
		/// <returns></returns>
		inline Text ApplyGroupEventEx(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType, Str reason)
		{
			return MQA::Detail::ApplyGroupEventEx(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(fromSeq), StrToText(op), StrToText(fromType), StrToText(reason));
		}
		/// <summary>
		/// 邀请别人群成员
		/// </summary>
		/// <param name="botQQ"></param>
		/// <param name="fromGroupId">来自群号</param>
		/// <param name="objQQ"></param>
		/// <param name="toGroupId">邀请至群号</param>
		/// <returns></returns>
		inline void InviteGroup_other(LLInteger botQQ, LLInteger fromGroupId, LLInteger objQQ, LLInteger toGroupId)
		{
			return MQA::Detail::InviteGroup_other(StrToText(botQQ), StrToText(fromGroupId), StrToText(objQQ), StrToText(toGroupId));
		}
		//群礼物_抽取，群聊等级抽礼物8000-么有抽到，7779-等级不够
		inline Integer draw_lucky_gift(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::draw_lucky_gift(StrToText(botQQ), StrToText(groupId));
		}
		//置群名片
		inline bool SetGroupCard(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Str card)
		{
			return MQA::Detail::SetGroupCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(card));
		}
		//机器人是否被禁言，若被禁言返回剩余禁言时长
		inline LLInteger BotIsShutUp(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::BotIsShutUp(StrToText(botQQ), StrToText(groupId));
		}
		//允许anony聊天
		inline bool SetGroupAnonOpen(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::SetGroupAnonOpen(StrToText(botQQ), StrToText(groupId));
		}
		//禁止anony聊天
		inline bool SetGroupAnonClose(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::SetGroupAnonClose(StrToText(botQQ), StrToText(groupId));
		}
		//获取加群链接，获取指定群的加群链接
		inline Text GetGroupUrl(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupUrl(StrToText(botQQ), StrToText(groupId));
		}
		//发起群投票_单选，返回投票fid
		inline Text PublishVote_A(LLInteger botQQ, LLInteger groupId, Str title, Str option1, Str option2, Str option3, Str deadline, Str anony)
		{
			return MQA::Detail::PublishVote_A(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(option1), StrToText(option2), StrToText(option3), StrToText(deadline), StrToText(anony));
		}
		//发起群投票_多选，返回投票fid
		inline Text PublishVote_B(LLInteger botQQ, LLInteger groupId, Str title, Str option1, Str option2, Str option3, Str much, Str deadline, Str anony)
		{
			return MQA::Detail::PublishVote_B(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(option1), StrToText(option2), StrToText(option3), StrToText(much), StrToText(deadline), StrToText(anony));
		}
		//取群成员头衔，返回json，如果medalList[0]['medal_desc']=私人订制，无上荣耀，那么medalList[0].name就是专属头衔，如果medalList[0]['medal_desc']=活跃等级，那么medalList[0].name就是活跃头衔
		inline Text GetGroupMerRank(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::GetGroupMerRank(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//取群设置信息，包含了常用的群设置信息、全群禁言、自己被禁言、被禁言列表等信息，返回json
		inline Text GetGroupSetInfo(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupSetInfo(StrToText(botQQ), StrToText(groupId));
		}
		//获取自己在某个群里是否被禁言，0=没有被禁言，否则为剩余禁言秒数，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得全群禁言信息
		inline Integer getMeIsShutup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::getMeIsShutup(StrToText(botQQ), StrToText(groupId));
		}
		//获取群里否开启了全体禁言，真=开启了，假=未开启，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得自己被禁言信息
		inline bool getAllIsShutup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::getAllIsShutup(StrToText(botQQ), StrToText(groupId));
		}
		//获取其他人在某个群里是否被禁言，0=没有被禁言，否则为剩余禁言秒数
		inline Integer getOthIsShutup(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::getOthIsShutup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//取是否允许群成员发起临时会话，稳定版，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得是否允许群成员发起群聊等其他群设置信息
		inline bool GetGroupTempSessionEx(LLInteger botQQ, LLInteger sourceId)
		{
			return MQA::Detail::GetGroupTempSessionEx(StrToText(botQQ), StrToText(sourceId));
		}
		//取是否允许群成员发起群聊，稳定版，如需频繁使用，请调用取群设置信息(Api_GetGroupSetInfo)，可同时获得是否允许群成员发起临时会话等其他群设置信息
		inline bool GetGroupLaunchNewEx(LLInteger botQQ, LLInteger sourceId)
		{
			return MQA::Detail::GetGroupLaunchNewEx(StrToText(botQQ), StrToText(sourceId));
		}
		//上传小视频，成功返回消息时间戳
		inline Integer UploadLitleVideo(LLInteger botQQ, LLInteger groupId, Str filePath)
		{
			return MQA::Detail::UploadLitleVideo(StrToText(botQQ), StrToText(groupId), StrToText(filePath));
		}
		//上传群文件
		inline void UpFlieGroup(LLInteger botQQ, LLInteger groupId, Str file_path, Str to_folder)
		{
			return MQA::Detail::UpFlieGroup(StrToText(botQQ), StrToText(groupId), StrToText(file_path), StrToText(to_folder));
		}
		//强制取群匿名ID
		inline LLInteger GetAnonId(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetAnonId(StrToText(botQQ), StrToText(groupId));
		}
		//取群文件数量，和上限数量，返回json
		inline Text GetGroupFileNum(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupFileNum(StrToText(botQQ), StrToText(groupId));
		}
		//取群文件容量，和总容量，返回json
		inline Text GetGroupFileCapacity(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupFileCapacity(StrToText(botQQ), StrToText(groupId));
		}
		//发起群收钱，成功返回c_no，失败返回空
		inline Text CreateGroupPay(LLInteger botQQ, LLInteger groupId, Str title, Integer type, Str objQQ, Str money)
		{
			return MQA::Detail::CreateGroupPay(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(type), StrToText(objQQ), StrToText(money));
		}
		//关闭群收钱，成功返回真，失败返回假
		inline bool CloseGroupPay(LLInteger botQQ, Str c_no)
		{
			return MQA::Detail::CloseGroupPay(StrToText(botQQ), StrToText(c_no));
		}
		//查询群收钱账单详情，成功返回json，可调用Api_GetGroupPayIsOk（群收钱账单是否已支付）解析
		inline Text GetGroupPayDetail(LLInteger botQQ, Str c_no)
		{
			return MQA::Detail::GetGroupPayDetail(StrToText(botQQ), StrToText(c_no));
		}
		//群收钱账单是否已支付，已支付返回1，未支付返回0
		inline Integer GetGroupPayIsOk(LLInteger botQQ, Str payDetail)
		{
			return MQA::Detail::GetGroupPayIsOk(StrToText(botQQ), StrToText(payDetail));
		}
		//发送群收钱账单催收通知，成功返回1，失败返回0
		inline Integer SendGroupPayMsg(LLInteger botQQ, Str c_no)
		{
			return MQA::Detail::SendGroupPayMsg(StrToText(botQQ), StrToText(c_no));
		}
		//发布群公告（成功返回真，失败返回假），调用此API应保证botQQ为管理员
		inline bool PBGroupNotic(LLInteger botQQ, LLInteger groupId, Str title, Str content)
		{
			return MQA::Detail::PBGroupNotic(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(content));
		}
		//取群公告
		inline Text GetGroupNotice(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupNotice(StrToText(botQQ), StrToText(groupId));
		}
		//添加管家问答，返回json
		inline Text AddBotKeyWord(LLInteger botQQ, LLInteger groupId, Str question, Str msg_content)
		{
			return MQA::Detail::AddBotKeyWord(StrToText(botQQ), StrToText(groupId), StrToText(question), StrToText(msg_content));
		}
		//取群信息，返回json
		inline Text GetGroupInfo(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupInfo(StrToText(botQQ), StrToText(groupId));
		}
		//取群名片
		inline Text GetGroupMemberCard(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::GetGroupMemberCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//取群文件列表，返回json
		inline Text GetGroupFileList(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupFileList(StrToText(botQQ), StrToText(groupId));
		}
		//取群文件下载链接
		inline Text GetGroupFileDownUrl(LLInteger botQQ, LLInteger groupId, Str FlieID, Str FlieName)
		{
			return MQA::Detail::GetGroupFileDownUrl(StrToText(botQQ), StrToText(groupId), StrToText(FlieID), StrToText(FlieName));
		}
		//取艾特全体成员剩余次数，例如：剩余xx次
		inline Text GetGroupAtAllNum(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupAtAllNum(StrToText(botQQ), StrToText(groupId));
		}
		//开启群聊置顶
		inline void TopGroup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::TopGroup(StrToText(botQQ), StrToText(groupId));
		}
		//关闭群聊置顶
		inline void UnTopGroup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::UnTopGroup(StrToText(botQQ), StrToText(groupId));
		}
		//创建群文件夹，成功返回空，失败返回原因
		inline Text CreatGroupFloder(LLInteger botQQ, LLInteger groupId, Str folderName)
		{
			return MQA::Detail::CreatGroupFloder(StrToText(botQQ), StrToText(groupId), StrToText(folderName));
		}
		//置群名
		inline bool SetGroupName(LLInteger botQQ, LLInteger groupId, Str groupName)
		{
			return MQA::Detail::SetGroupName(StrToText(botQQ), StrToText(groupId), StrToText(groupName));
		}
		//取群名_从缓存
		inline Text GetGroupName(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupName(StrToText(botQQ), StrToText(groupId));
		}
		//置群消息接收
		inline void SetGroupRecType(LLInteger botQQ, LLInteger groupId, Integer type)
		{
			return MQA::Detail::SetGroupRecType(StrToText(botQQ), StrToText(groupId), StrToText(type));
		}
		//发送频道通行证到群
		inline bool GrantCheckToGroup(LLInteger botQQ, LLInteger guildId, LLInteger groupId, Integer num)
		{
			return MQA::Detail::GrantCheckToGroup(StrToText(botQQ), StrToText(guildId), StrToText(groupId), StrToText(num));
		}
		//取群文件信息
		inline Text GetGroupFileInfo(LLInteger botQQ, LLInteger groupId, Str FileId)
		{
			return MQA::Detail::GetGroupFileInfo(StrToText(botQQ), StrToText(groupId), StrToText(FileId));
		}
		inline Text UploadGroupAudioEx(LLInteger botQQ, LLInteger groupId, Integer ptr, Integer len)
		{
			return MQA::Detail::UploadGroupAudioEx(StrToText(botQQ), StrToText(groupId), StrToText(ptr), StrToText(len));
		}
		//设置专属头衔
		inline bool SetRank(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Str rank)
		{
			return MQA::Detail::SetRank(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(rank));
		}
		//拍一拍_群
		inline bool TakeGroup(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::TakeGroup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//拍一拍_好友在线状态
		inline bool TakeFriendsOnline(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::TakeFriendsOnline(StrToText(botQQ), StrToText(objQQ));
		}
		//禁言某人
		inline bool ShutUp(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer time)
		{
			return MQA::Detail::ShutUp(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(time));
		}
		//退群
		inline bool Quit(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::Quit(StrToText(botQQ), StrToText(groupId));
		}
		//解散群
		inline bool DelGroup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::DelGroup(StrToText(botQQ), StrToText(groupId));
		}
		//全员禁言
		inline bool ShutUpAll(LLInteger botQQ, LLInteger groupId, bool isOpen)
		{
			return MQA::Detail::ShutUpAll(StrToText(botQQ), StrToText(groupId), StrToText(isOpen));
		}
		//取群列表，返回json
		inline Text GetGroups(LLInteger botQQ)
		{
			return MQA::Detail::GetGroups(StrToText(botQQ));
		}
		//取群成员列表，返回json
		inline Text GetGroupMembers(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupMembers(StrToText(botQQ), StrToText(groupId));
		}
		//设置或取消管理
		inline bool SetManager(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer op)
		{
			return MQA::Detail::SetManager(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(op));
		}
		//取管理员列表，包括群主，返回json
		inline Text GetManager(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetManager(StrToText(botQQ), StrToText(groupId));
		}
		//踢出群成员
		inline bool RemoveMember(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, bool refuseJoin)
		{
			return MQA::Detail::RemoveMember(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(refuseJoin));
		}
		//处理群验证
		inline void ApplyGroupEvent(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType)
		{
			return MQA::Detail::ApplyGroupEvent(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(fromSeq), StrToText(op), StrToText(fromType));
		}
		inline Text UploadGroupPic(LLInteger botQQ, LLInteger groupId, Str img_path)
		{
			return MQA::Detail::UploadGroupPic(StrToText(botQQ), StrToText(groupId), StrToText(img_path));
		}
		inline Text UploadGroupAudio(LLInteger botQQ, LLInteger groupId, Str file_path)
		{
			return MQA::Detail::UploadGroupAudio(StrToText(botQQ), StrToText(groupId), StrToText(file_path));
		}
		inline Text UploadGroupPicEx(LLInteger botQQ, LLInteger groupId, Integer ptr, Integer len)
		{
			return MQA::Detail::UploadGroupPicEx(StrToText(botQQ), StrToText(groupId), StrToText(ptr), StrToText(len));
		}
		inline bool SetGroupMemberCard(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Str card)
		{
			return MQA::Detail::SetGroupMemberCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(card));
		}
	}
	namespace KeyAPI
	{

		//取指定域名Pskey
		inline Text GetDomainPskey(LLInteger botQQ, Text address, Text appid, Text daid)
		{
			return MQA::Detail::GetDomainPskey(StrToText(botQQ), StrToText(address), StrToText(appid), StrToText(daid));
		}
		//获取Sessionkey
		inline Text GetSessionkey(LLInteger botQQ)
		{
			return MQA::Detail::GetSessionkey(StrToText(botQQ));
		}
		//取cookies
		inline Text GetCookies(LLInteger botQQ)
		{
			return MQA::Detail::GetCookies(StrToText(botQQ));
		}
		//取Skey
		inline Text GetSkey(LLInteger botQQ)
		{
			return MQA::Detail::GetSkey(StrToText(botQQ));
		}
		//取Pskey
		inline Text GetPskey(LLInteger botQQ, Str domain)
		{
			return MQA::Detail::GetPskey(StrToText(botQQ), StrToText(domain));
		}
		//取Clientkey
		inline Text GetClientkey(LLInteger botQQ)
		{
			return MQA::Detail::GetClientkey(StrToText(botQQ));
		}
	}
	namespace BotQQAPI
	{
		//上传照片墙，成功返回filekey，可用来删除照片墙，失败返回空
		inline Text UpPhotoWall(LLInteger botQQ, Str imgPath)
		{
			return MQA::Detail::UpPhotoWall(StrToText(botQQ), StrToText(imgPath));
		}
		//获取照片墙，成功返回json，失败返回空
		inline Text GetPhotoWall(LLInteger botQQ, Str objQQ)
		{
			return MQA::Detail::GetPhotoWall(StrToText(botQQ), StrToText(objQQ));
		}
		//删除照片墙，成功返回真，失败返回假
		inline bool DelPhotoWall(LLInteger botQQ, Str filekey)
		{
			return MQA::Detail::DelPhotoWall(StrToText(botQQ), StrToText(filekey));
		}
		inline Integer UploadHead(LLInteger botQQ, Str img_path)
		{
			return MQA::Detail::UploadHead(StrToText(botQQ), StrToText(img_path));
		}
		inline Integer UploadHeadEx(LLInteger botQQ, Integer ptr, Integer len)
		{
			return MQA::Detail::UploadHeadEx(StrToText(botQQ), StrToText(ptr), StrToText(len));
		}
		//修改签名
		inline bool SetSign(LLInteger botQQ, Str newSign)
		{
			return MQA::Detail::SetSign(StrToText(botQQ), StrToText(newSign));
		}
		//修改昵称
		inline bool SetNick(LLInteger botQQ, Str newNick)
		{
			return MQA::Detail::SetNick(StrToText(botQQ), StrToText(newNick));
		}
	}
	namespace AnotherAPI
	{

		//查询网址安全性，安全返回空，否则返回一个链接
		inline Text GetUrlIsSafe(LLInteger botQQ, Str url)
		{
			return MQA::Detail::GetUrlIsSafe(StrToText(botQQ), StrToText(url));
		}
		//发送封包，结果十六进制到字节集
		inline Text SendPacket(LLInteger botQQ, Str cmd, Str pack, Integer time_out)
		{
			return MQA::Detail::SendPacket(StrToText(botQQ), StrToText(cmd), StrToText(pack), StrToText(time_out));
		}
		//取语音下载地址
		inline Text GetAudioUrl(LLInteger botQQ, Str token, Str MD5)
		{
			return MQA::Detail::GetAudioUrl(StrToText(botQQ), StrToText(token), StrToText(MD5));
		}
		//公众号会员签到
		inline bool vip_pub_subbutton_qiandao(LLInteger botQQ)
		{
			return MQA::Detail::vip_pub_subbutton_qiandao(StrToText(botQQ));
		}
		//手机会员网页签到
		inline bool vip_qiandao_web(LLInteger botQQ)
		{
			return MQA::Detail::vip_qiandao_web(StrToText(botQQ));
		}
		//搜索音乐
		inline Text QueryMusicInfo_fcg_music_search(LLInteger botQQ, Str keyword)
		{
			return MQA::Detail::QueryMusicInfo_fcg_music_search(StrToText(botQQ), StrToText(keyword));
		}
		//查看音乐详情
		inline Text QueryMusicInfo_fcg_music_get_song_info_batch(LLInteger botQQ, Str songId)
		{
			return MQA::Detail::QueryMusicInfo_fcg_music_get_song_info_batch(StrToText(botQQ), StrToText(songId));
		}
		//查看转发聊天记录内容
		inline Text MultiMsg_ApplyDown_Group(LLInteger botQQ, Str resId, Integer type)
		{
			return MQA::Detail::MultiMsg_ApplyDown_Group(StrToText(botQQ), StrToText(resId), StrToText(type));
		}
		//取频道用户所在地
		inline Text GetGuildUserHome(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetGuildUserHome(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//取频道用户昵称
		inline Text GetGuildUserName(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetGuildUserName(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//取加入频道时间
		inline Text GetJoinGuildTime(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetJoinGuildTime(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//取频道用户头像下载链接
		inline Text GetGuildHead(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetGuildHead(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//取子频道列表，返回json
		inline Text GetGuildChannelList(LLInteger botQQ, LLInteger guildId)
		{
			return MQA::Detail::GetGuildChannelList(StrToText(botQQ), StrToText(guildId));
		}
		//撤回子频道消息
		inline bool PbMsgWithDraw_ChannelGuild(LLInteger botQQ, LLInteger guildId, LLInteger subGuildId, Integer MsgReq)
		{
			return MQA::Detail::PbMsgWithDraw_ChannelGuild(StrToText(botQQ), StrToText(guildId), StrToText(subGuildId), StrToText(MsgReq));
		}
		//频道设置_全员禁言
		inline bool ChannelSet_totalSilence(LLInteger botQQ, LLInteger guildId, LLInteger time)
		{
			return MQA::Detail::ChannelSet_totalSilence(StrToText(botQQ), StrToText(guildId), StrToText(time));
		}

		//设置机器人频道名称
		inline bool SetRobotGuildNick(LLInteger botQQ, LLInteger GuildId, Str Nick)
		{
			return MQA::Detail::SetRobotGuildNick(StrToText(botQQ), StrToText(GuildId), StrToText(Nick));
		}
		//退出频道
		inline bool QuitGuild(LLInteger botQQ, LLInteger GuildId)
		{
			return MQA::Detail::QuitGuild(StrToText(botQQ), StrToText(GuildId));
		}
		//取公众号昵称
		inline Text GetPublicNick(LLInteger botQQ, LLInteger PublicQQ)
		{
			return MQA::Detail::GetPublicNick(StrToText(botQQ), StrToText(PublicQQ));
		}
		//取自身guildId_从缓存
		inline Text GetGuildSelfId_cache(LLInteger botQQ)
		{
			return MQA::Detail::GetGuildSelfId_cache(StrToText(botQQ));
		}
		//取图片下载连接
		inline Text GetPicLink(LLInteger botQQ, Integer type, LLInteger sourceId, Str imgId)
		{
			return MQA::Detail::GetPicLink(StrToText(botQQ), StrToText(type), StrToText(sourceId), StrToText(imgId));
		}
		//请确保bin目录有ffmpeg转码库(框架不自带)，成功返回amr文件完整路径，可直接调用上传语音api，失败返回空
		inline Text Mp3ToAmr(Text mp3, Str amr)
		{
			return MQA::Detail::Mp3ToAmr(mp3, StrToText(amr));
		}
		//请确保bin目录有ffmpeg转码库(框架不自带)，成功返回amr文件完整路径，可直接调用上传语音api，失败返回空
		inline Text WavToAmr(Text wav, Str amr)
		{
			return MQA::Detail::WavToAmr(StrToText(wav), StrToText(amr));
		}
	}
	namespace HBAPI
	{

		//获取红包msgno
		inline Text GetRedPackMsgNo(LLInteger botQQ)
		{
			return MQA::Detail::GetRedPackMsgNo(StrToText(botQQ));
		}
		//获取红包vskey
		inline Text GetRedPackVskey(LLInteger botQQ, LLInteger groupId, Text listid, Text authkey)
		{
			return MQA::Detail::GetRedPackVskey(StrToText(botQQ), StrToText(groupId), StrToText(listid), StrToText(authkey));
		}
		//红包数据加密
		inline Text EncryptRedPackData(LLInteger botQQ, Text data, Integer random)
		{
			return MQA::Detail::EncryptRedPackData(StrToText(botQQ), StrToText(data), StrToText(random));
		}
		//红包数据解密
		inline Text DecryptRedPackData(LLInteger botQQ, Text data, Integer random)
		{
			return MQA::Detail::DecryptRedPackData(StrToText(botQQ), StrToText(data), StrToText(random));
		}
		//查询红包领取详情，返回json
		inline Text GetRedPackDetail(LLInteger botQQ, LLInteger groupId, Str listid, Str authkey)
		{
			return MQA::Detail::GetRedPackDetail(StrToText(botQQ), StrToText(groupId), StrToText(listid), StrToText(authkey));
		}

		//普通红包，成功success，否则为失败原因
		inline Text RedPack_Ordinary(LLInteger botQQ, Str payPwd, Str sourceId, Str num, Str money, Str greeting, Integer type)
		{
			return MQA::Detail::RedPack_Ordinary(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(num), StrToText(money), StrToText(greeting), StrToText(type));
		}
		//拼手气红包，成功success，否则为失败原因
		inline Text RedPack_Luck(LLInteger botQQ, Str payPwd, Str sourceId, Str num, Str money, Str greeting)
		{
			return MQA::Detail::RedPack_Luck(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(num), StrToText(money), StrToText(greeting));
		}
		//（已废弃）专属红包，成功success，否则为失败原因
		inline Text RedPack_Exclusive(LLInteger botQQ, Str payPwd, Str sourceId, Str objQQ, Str num, Str money, Str greeting)
		{
			return MQA::Detail::RedPack_Exclusive(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(objQQ), StrToText(num), StrToText(money), StrToText(greeting));
		}
		//口令红包，成功success，否则为失败原因
		inline Text RedPack_KeyWord(LLInteger botQQ, Str payPwd, Str sourceId, Str num, Str money, Str discourse, Integer type)
		{
			return MQA::Detail::RedPack_KeyWord(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(num), StrToText(money), StrToText(discourse), StrToText(type));
		}
		//转账，成功success，否则为失败原因
		inline Text TransferAccounts(LLInteger botQQ, Str payPwd, Str objQQ, Str objNick, Str money, Str msg, Integer type)
		{
			return MQA::Detail::TransferAccounts(StrToText(botQQ), StrToText(payPwd), StrToText(objQQ), StrToText(objNick), StrToText(money), StrToText(msg), StrToText(type));
		}
		//查询钱包余额，成功返回余额数值，否则返回失败原因
		inline Text QueryBalance(LLInteger botQQ, Str payPwd)
		{
			return MQA::Detail::QueryBalance(StrToText(botQQ), StrToText(payPwd));
		}
		//查询红包记录，成功返回余额数值，否则返回失败原因
		inline Text RedPack_Log(LLInteger botQQ, Str payPwd, Str year, Integer typ, Integer page)
		{
			return MQA::Detail::RedPack_Log(StrToText(botQQ), StrToText(payPwd), StrToText(year), StrToText(typ), StrToText(page));
		}
	}
}
#endif // !__MQAAPI_DEFINE__