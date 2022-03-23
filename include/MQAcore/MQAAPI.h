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

namespace MQA::�ı�����
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
	inline Str ���ظ���(LLInteger _atQQ)
	{
		if (!_atQQ)return "";
		Str _str(_MQACodeStr[0]);
		__str_replace_once(_str, std::to_string(_atQQ));
		return _str;
	}
	inline Str ����ȫ��(void) { return _MQACodeStr[1]; }
	inline Str �����(Str id, Str name, Str hash, Str flag)
	{
		if (id.empty() || name.empty() || hash.empty() || flag.empty())return "";
		Str _str(_MQACodeStr[2]);
		__str_replace_once(_str, id);
		__str_replace_once(_str, name);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, flag);
		return _str;
	}
	inline Str Ⱥ��ͼƬ(Str hash)
	{
		if (hash.empty())return "";
		Str _str(_MQACodeStr[3]);
		__str_replace_once(_str, hash);
		return _str;
	}
	inline Str ˽��ͼƬ(Str hash, Str guid)
	{
		if (hash.empty() || guid.empty())return "";
		Str _str(_MQACodeStr[4]);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, guid);
		return _str;
	}
	inline Str ����(Str hash, Str token, Str url)
	{
		if (hash.empty() || token.empty() || url.empty())return "";
		Str _str(_MQACodeStr[5]);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, token);
		__str_replace_once(_str, url);
		return _str;
	}
	inline Str ����_����(Str path)
	{
		if (path.empty())return "";
		Str _str(_MQACodeStr[6]);
		__str_replace_once(_str, path);
		return _str;
	}
	inline Str ͼƬ_����(Str path)
	{
		if (path.empty())return "";
		Str _str(_MQACodeStr[7]);
		__str_replace_once(_str, path);
		return _str;
	}
	inline Str С�ƶ�����(Integer id)
	{
		Str _str(_MQACodeStr[8]);
		__str_replace_once(_str, std::to_string(id));
		return _str;
	}
	inline Str С��Ƶ(Str link, Str hash1, Str hash2)
	{
		Str _str(_MQACodeStr[9]);
		__str_replace_once(_str, link);
		__str_replace_once(_str, hash1);
		__str_replace_once(_str, hash2);
		return _str;
	}
	inline Str �»ƶ�(Str name, Integer id)
	{
		Str _str(_MQACodeStr[10]);
		__str_replace_once(_str, name);
		__str_replace_once(_str, std::to_string(id));
		return _str;
	}
	inline Str �����(Integer id, Str name, Str hash, Str flag)
	{
		Str _str(_MQACodeStr[11]);
		__str_replace_once(_str, std::to_string(id));
		__str_replace_once(_str, name);
		__str_replace_once(_str, hash);
		__str_replace_once(_str, flag);
		return _str;
	}
	inline Str �ظ���Ϣ(Str Card, Str Content, LLInteger SendQQID, Str RequestID, Str SendTime)
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
		//ȡ����QQ��#���з��ģ�һ��һ��
		inline Text GetOnlineQQ()
		{
			return MQA::Detail::GetOnlineQQ();
		}
		//ȡ����QQ��#���з��ģ�һ��һ��
		inline Text GetAllQQ()
		{
			return MQA::Detail::GetAllQQ();
		}
		//���QQ�����QQ�������
		inline bool AddQQ(Text QQ, Str pwd, Integer type, bool savePwd)
		{
			return MQA::Detail::AddQQ(StrToText(QQ), StrToText(pwd), StrToText(type), StrToText(savePwd));
		}
		//��ȡ��¼��ά�룬���磺{"qrcode_path":"C:\Users\13301\Desktop\MyQQA\data\cache\363751070.jpg","qrcode_sign":"33DBDB7583E601FFBBF0BF38FD1DE8C41293F821F74D2E40"}
		inline Text GetQrcode(Text QQ)
		{
			return MQA::Detail::GetQrcode(QQ);
		}
		inline Text GetOffQQ(void)
		{
			return MQA::Detail::GetOffQQ();
		}
		//����¼��ά��״̬�����巵��ֵ�뿴�ĵ�, 
		inline Text CationQrcode(LLInteger QQ)
		{
			return MQA::Detail::CationQrcode(QQ);
		}
		//��¼ָ��QQ��Ӧȷ��QQ�������б����Ѵ���
		inline void Login(LLInteger botQQ)
		{
			return MQA::Detail::Login(StrToText(botQQ));
		}
		//����ָ��QQ��Ӧȷ��QQ���������б���������
		inline void Logout(LLInteger botQQ)
		{
			return MQA::Detail::Logout(StrToText(botQQ));
		}
		//ɾ��ָ��QQ���ߣ�Ӧȷ��QQ�������б����Ѵ���
		inline void Delete(LLInteger botQQ)
		{
			return MQA::Detail::Delete(StrToText(botQQ));
		}
		//ȡ��ܰ汾��
		inline Text GetVer()
		{
			return MQA::Detail::GetVer();
		}
		//ȡ������״̬ 0δ��¼��1���ӳɹ���2��¼�ɹ���3���߳ɹ���4ע��ɹ���5��¼��ϣ�6��¼ʧ�ܣ�7�����쳣��8�˺Ŷ��ᣬ9�������
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
		//����Ⱥjson��Ϣ
		inline Integer SendGroupJson(LLInteger botQQ, LLInteger groupId, Str json, bool anony)
		{
			return MQA::Detail::SendGroupJson(StrToText(botQQ), StrToText(groupId), StrToText(json), StrToText(anony));
		}
	}
	namespace FriendAPI
	{

		//���ʶ���QQ�ռ�
		inline bool BrowseQzone(LLInteger botQQ, LLInteger objQQ, Str log)
		{
			return MQA::Detail::BrowseQzone(StrToText(botQQ), StrToText(objQQ), StrToText(log));
		}
		//ɾ������
		inline bool DelFriend(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::DelFriend(StrToText(botQQ), StrToText(objQQ));
		}
		//�����ر����
		inline void SetSpecialCare(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::SetSpecialCare(StrToText(botQQ), StrToText(objQQ));
		}
		//�������û� ����1 = ���� 2 = ���
		inline void SetShieldedFriend(LLInteger botQQ, LLInteger objQQ, Integer type)
		{
			return MQA::Detail::SetShieldedFriend(StrToText(botQQ), StrToText(objQQ), StrToText(type));
		}
		/// <summary>
		/// ȡ�����ļ���������
		/// </summary>
		/// <param name="botQQ"></param>
		/// <param name="FileId"></param>
		/// <param name="fileName"></param>
		/// <returns></returns>
		inline Text GetFriendFileDownUrl(LLInteger botQQ, Str FileId, Str fileName)
		{
			return MQA::Detail::GetFriendFileDownUrl(StrToText(botQQ), StrToText(FileId), StrToText(fileName));
		}
		//��ѯ������Ƭ������json
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
		//ȡ�����б�����json
		inline Text GetFriends(LLInteger botQQ)
		{
			return MQA::Detail::GetFriends(StrToText(botQQ));
		}
		//��һ��_����ͷ��
		inline bool TakeFriendsPic(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::TakeFriendsPic(StrToText(botQQ), StrToText(objQQ));
		}
		//ȡ����ͼƬ�ϴ���Ϣ
		inline Text GetUploadInfo(LLInteger botQQ, LLInteger objQQ, Str pic_md5, LLInteger pic_size)
		{
			return MQA::Detail::GetUploadInfo(StrToText(botQQ), StrToText(objQQ), StrToText(pic_md5), StrToText(pic_size));
		}
		//ȡ����ǩ��
		inline Text GetSign(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::GetSign(StrToText(botQQ), StrToText(objQQ));
		}

		//����
		inline Text Like(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::Like(StrToText(botQQ), StrToText(objQQ));
		}
		//ȡ��������״̬�������ߡ����뿪��...
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

		//���������֤��#�����¼�_��������
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

		//Ⱥ�Ĵ򿨣������磺�����ѳɹ��򿨣�
		inline Str Groupclock(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::Groupclock(StrToText(botQQ), StrToText(groupId));
		}
		//����Ⱥ�ģ��ɹ�����groupId����Ϣ{ "ec":0,"errcode" : 0,"em" : "","gu" : 914856344,"gc" : 914856344 }��httpģʽ����Ⱥ�ģ���ע�����Ƶ��
		inline Str CreateGroup(LLInteger botQQ, Str groupName, Str groupClass)
		{
			return MQA::Detail::CreateGroup(StrToText(botQQ), StrToText(groupName), StrToText(groupClass));
		}
		/// <summary>
		/// ����Ⱥ��֤
		/// </summary>
		/// <param name="botQQ"></param>
		/// <param name="groupId"></param>
		/// <param name="objQQ"></param>
		/// <param name="fromSeq"></param>
		/// <param name="op">11ͬ�� 12�ܾ� 14����</param>
		/// <param name="fromType">Ⱥ�¼�_�ұ��������Ⱥ��Ⱥ�¼�_ĳ�������Ⱥ</param>
		/// <param name="reason">�ܾ�����</param>
		/// <returns></returns>
		inline Text ApplyGroupEventEx(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, LLInteger fromSeq, Integer op, Integer fromType, Str reason)
		{
			return MQA::Detail::ApplyGroupEventEx(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(fromSeq), StrToText(op), StrToText(fromType), StrToText(reason));
		}
		/// <summary>
		/// �������Ⱥ��Ա
		/// </summary>
		/// <param name="botQQ"></param>
		/// <param name="fromGroupId">����Ⱥ��</param>
		/// <param name="objQQ"></param>
		/// <param name="toGroupId">������Ⱥ��</param>
		/// <returns></returns>
		inline void InviteGroup_other(LLInteger botQQ, LLInteger fromGroupId, LLInteger objQQ, LLInteger toGroupId)
		{
			return MQA::Detail::InviteGroup_other(StrToText(botQQ), StrToText(fromGroupId), StrToText(objQQ), StrToText(toGroupId));
		}
		//Ⱥ����_��ȡ��Ⱥ�ĵȼ�������8000-ô�г鵽��7779-�ȼ�����
		inline Integer draw_lucky_gift(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::draw_lucky_gift(StrToText(botQQ), StrToText(groupId));
		}
		//��Ⱥ��Ƭ
		inline bool SetGroupCard(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Str card)
		{
			return MQA::Detail::SetGroupCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(card));
		}
		//�������Ƿ񱻽��ԣ��������Է���ʣ�����ʱ��
		inline LLInteger BotIsShutUp(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::BotIsShutUp(StrToText(botQQ), StrToText(groupId));
		}
		//����anony����
		inline bool SetGroupAnonOpen(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::SetGroupAnonOpen(StrToText(botQQ), StrToText(groupId));
		}
		//��ֹanony����
		inline bool SetGroupAnonClose(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::SetGroupAnonClose(StrToText(botQQ), StrToText(groupId));
		}
		//��ȡ��Ⱥ���ӣ���ȡָ��Ⱥ�ļ�Ⱥ����
		inline Text GetGroupUrl(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupUrl(StrToText(botQQ), StrToText(groupId));
		}
		//����ȺͶƱ_��ѡ������ͶƱfid
		inline Text PublishVote_A(LLInteger botQQ, LLInteger groupId, Str title, Str option1, Str option2, Str option3, Str deadline, Str anony)
		{
			return MQA::Detail::PublishVote_A(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(option1), StrToText(option2), StrToText(option3), StrToText(deadline), StrToText(anony));
		}
		//����ȺͶƱ_��ѡ������ͶƱfid
		inline Text PublishVote_B(LLInteger botQQ, LLInteger groupId, Str title, Str option1, Str option2, Str option3, Str much, Str deadline, Str anony)
		{
			return MQA::Detail::PublishVote_B(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(option1), StrToText(option2), StrToText(option3), StrToText(much), StrToText(deadline), StrToText(anony));
		}
		//ȡȺ��Աͷ�Σ�����json�����medalList[0]['medal_desc']=˽�˶��ƣ�������ҫ����ômedalList[0].name����ר��ͷ�Σ����medalList[0]['medal_desc']=��Ծ�ȼ�����ômedalList[0].name���ǻ�Ծͷ��
		inline Text GetGroupMerRank(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::GetGroupMerRank(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//ȡȺ������Ϣ�������˳��õ�Ⱥ������Ϣ��ȫȺ���ԡ��Լ������ԡ��������б����Ϣ������json
		inline Text GetGroupSetInfo(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupSetInfo(StrToText(botQQ), StrToText(groupId));
		}
		//��ȡ�Լ���ĳ��Ⱥ���Ƿ񱻽��ԣ�0=û�б����ԣ�����Ϊʣ���������������Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ���ȫȺ������Ϣ
		inline Integer getMeIsShutup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::getMeIsShutup(StrToText(botQQ), StrToText(groupId));
		}
		//��ȡȺ�������ȫ����ԣ���=�����ˣ���=δ����������Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ����Լ���������Ϣ
		inline bool getAllIsShutup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::getAllIsShutup(StrToText(botQQ), StrToText(groupId));
		}
		//��ȡ��������ĳ��Ⱥ���Ƿ񱻽��ԣ�0=û�б����ԣ�����Ϊʣ���������
		inline Integer getOthIsShutup(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::getOthIsShutup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//ȡ�Ƿ�����Ⱥ��Ա������ʱ�Ự���ȶ��棬����Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ����Ƿ�����Ⱥ��Ա����Ⱥ�ĵ�����Ⱥ������Ϣ
		inline bool GetGroupTempSessionEx(LLInteger botQQ, LLInteger sourceId)
		{
			return MQA::Detail::GetGroupTempSessionEx(StrToText(botQQ), StrToText(sourceId));
		}
		//ȡ�Ƿ�����Ⱥ��Ա����Ⱥ�ģ��ȶ��棬����Ƶ��ʹ�ã������ȡȺ������Ϣ(Api_GetGroupSetInfo)����ͬʱ����Ƿ�����Ⱥ��Ա������ʱ�Ự������Ⱥ������Ϣ
		inline bool GetGroupLaunchNewEx(LLInteger botQQ, LLInteger sourceId)
		{
			return MQA::Detail::GetGroupLaunchNewEx(StrToText(botQQ), StrToText(sourceId));
		}
		//�ϴ�С��Ƶ���ɹ�������Ϣʱ���
		inline Integer UploadLitleVideo(LLInteger botQQ, LLInteger groupId, Str filePath)
		{
			return MQA::Detail::UploadLitleVideo(StrToText(botQQ), StrToText(groupId), StrToText(filePath));
		}
		//�ϴ�Ⱥ�ļ�
		inline void UpFlieGroup(LLInteger botQQ, LLInteger groupId, Str file_path, Str to_folder)
		{
			return MQA::Detail::UpFlieGroup(StrToText(botQQ), StrToText(groupId), StrToText(file_path), StrToText(to_folder));
		}
		//ǿ��ȡȺ����ID
		inline LLInteger GetAnonId(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetAnonId(StrToText(botQQ), StrToText(groupId));
		}
		//ȡȺ�ļ�����������������������json
		inline Text GetGroupFileNum(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupFileNum(StrToText(botQQ), StrToText(groupId));
		}
		//ȡȺ�ļ���������������������json
		inline Text GetGroupFileCapacity(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupFileCapacity(StrToText(botQQ), StrToText(groupId));
		}
		//����Ⱥ��Ǯ���ɹ�����c_no��ʧ�ܷ��ؿ�
		inline Text CreateGroupPay(LLInteger botQQ, LLInteger groupId, Str title, Integer type, Str objQQ, Str money)
		{
			return MQA::Detail::CreateGroupPay(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(type), StrToText(objQQ), StrToText(money));
		}
		//�ر�Ⱥ��Ǯ���ɹ������棬ʧ�ܷ��ؼ�
		inline bool CloseGroupPay(LLInteger botQQ, Str c_no)
		{
			return MQA::Detail::CloseGroupPay(StrToText(botQQ), StrToText(c_no));
		}
		//��ѯȺ��Ǯ�˵����飬�ɹ�����json���ɵ���Api_GetGroupPayIsOk��Ⱥ��Ǯ�˵��Ƿ���֧��������
		inline Text GetGroupPayDetail(LLInteger botQQ, Str c_no)
		{
			return MQA::Detail::GetGroupPayDetail(StrToText(botQQ), StrToText(c_no));
		}
		//Ⱥ��Ǯ�˵��Ƿ���֧������֧������1��δ֧������0
		inline Integer GetGroupPayIsOk(LLInteger botQQ, Str payDetail)
		{
			return MQA::Detail::GetGroupPayIsOk(StrToText(botQQ), StrToText(payDetail));
		}
		//����Ⱥ��Ǯ�˵�����֪ͨ���ɹ�����1��ʧ�ܷ���0
		inline Integer SendGroupPayMsg(LLInteger botQQ, Str c_no)
		{
			return MQA::Detail::SendGroupPayMsg(StrToText(botQQ), StrToText(c_no));
		}
		//����Ⱥ���棨�ɹ������棬ʧ�ܷ��ؼ٣������ô�APIӦ��֤botQQΪ����Ա
		inline bool PBGroupNotic(LLInteger botQQ, LLInteger groupId, Str title, Str content)
		{
			return MQA::Detail::PBGroupNotic(StrToText(botQQ), StrToText(groupId), StrToText(title), StrToText(content));
		}
		//ȡȺ����
		inline Text GetGroupNotice(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupNotice(StrToText(botQQ), StrToText(groupId));
		}
		//��ӹܼ��ʴ𣬷���json
		inline Text AddBotKeyWord(LLInteger botQQ, LLInteger groupId, Str question, Str msg_content)
		{
			return MQA::Detail::AddBotKeyWord(StrToText(botQQ), StrToText(groupId), StrToText(question), StrToText(msg_content));
		}
		//ȡȺ��Ϣ������json
		inline Text GetGroupInfo(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupInfo(StrToText(botQQ), StrToText(groupId));
		}
		//ȡȺ��Ƭ
		inline Text GetGroupMemberCard(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::GetGroupMemberCard(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//ȡȺ�ļ��б�����json
		inline Text GetGroupFileList(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupFileList(StrToText(botQQ), StrToText(groupId));
		}
		//ȡȺ�ļ���������
		inline Text GetGroupFileDownUrl(LLInteger botQQ, LLInteger groupId, Str FlieID, Str FlieName)
		{
			return MQA::Detail::GetGroupFileDownUrl(StrToText(botQQ), StrToText(groupId), StrToText(FlieID), StrToText(FlieName));
		}
		//ȡ����ȫ���Աʣ����������磺ʣ��xx��
		inline Text GetGroupAtAllNum(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupAtAllNum(StrToText(botQQ), StrToText(groupId));
		}
		//����Ⱥ���ö�
		inline void TopGroup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::TopGroup(StrToText(botQQ), StrToText(groupId));
		}
		//�ر�Ⱥ���ö�
		inline void UnTopGroup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::UnTopGroup(StrToText(botQQ), StrToText(groupId));
		}
		//����Ⱥ�ļ��У��ɹ����ؿգ�ʧ�ܷ���ԭ��
		inline Text CreatGroupFloder(LLInteger botQQ, LLInteger groupId, Str folderName)
		{
			return MQA::Detail::CreatGroupFloder(StrToText(botQQ), StrToText(groupId), StrToText(folderName));
		}
		//��Ⱥ��
		inline bool SetGroupName(LLInteger botQQ, LLInteger groupId, Str groupName)
		{
			return MQA::Detail::SetGroupName(StrToText(botQQ), StrToText(groupId), StrToText(groupName));
		}
		//ȡȺ��_�ӻ���
		inline Text GetGroupName(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupName(StrToText(botQQ), StrToText(groupId));
		}
		//��Ⱥ��Ϣ����
		inline void SetGroupRecType(LLInteger botQQ, LLInteger groupId, Integer type)
		{
			return MQA::Detail::SetGroupRecType(StrToText(botQQ), StrToText(groupId), StrToText(type));
		}
		//����Ƶ��ͨ��֤��Ⱥ
		inline bool GrantCheckToGroup(LLInteger botQQ, LLInteger guildId, LLInteger groupId, Integer num)
		{
			return MQA::Detail::GrantCheckToGroup(StrToText(botQQ), StrToText(guildId), StrToText(groupId), StrToText(num));
		}
		//ȡȺ�ļ���Ϣ
		inline Text GetGroupFileInfo(LLInteger botQQ, LLInteger groupId, Str FileId)
		{
			return MQA::Detail::GetGroupFileInfo(StrToText(botQQ), StrToText(groupId), StrToText(FileId));
		}
		inline Text UploadGroupAudioEx(LLInteger botQQ, LLInteger groupId, Integer ptr, Integer len)
		{
			return MQA::Detail::UploadGroupAudioEx(StrToText(botQQ), StrToText(groupId), StrToText(ptr), StrToText(len));
		}
		//����ר��ͷ��
		inline bool SetRank(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Str rank)
		{
			return MQA::Detail::SetRank(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(rank));
		}
		//��һ��_Ⱥ
		inline bool TakeGroup(LLInteger botQQ, LLInteger groupId, LLInteger objQQ)
		{
			return MQA::Detail::TakeGroup(StrToText(botQQ), StrToText(groupId), StrToText(objQQ));
		}
		//��һ��_��������״̬
		inline bool TakeFriendsOnline(LLInteger botQQ, LLInteger objQQ)
		{
			return MQA::Detail::TakeFriendsOnline(StrToText(botQQ), StrToText(objQQ));
		}
		//����ĳ��
		inline bool ShutUp(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer time)
		{
			return MQA::Detail::ShutUp(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(time));
		}
		//��Ⱥ
		inline bool Quit(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::Quit(StrToText(botQQ), StrToText(groupId));
		}
		//��ɢȺ
		inline bool DelGroup(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::DelGroup(StrToText(botQQ), StrToText(groupId));
		}
		//ȫԱ����
		inline bool ShutUpAll(LLInteger botQQ, LLInteger groupId, bool isOpen)
		{
			return MQA::Detail::ShutUpAll(StrToText(botQQ), StrToText(groupId), StrToText(isOpen));
		}
		//ȡȺ�б�����json
		inline Text GetGroups(LLInteger botQQ)
		{
			return MQA::Detail::GetGroups(StrToText(botQQ));
		}
		//ȡȺ��Ա�б�����json
		inline Text GetGroupMembers(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetGroupMembers(StrToText(botQQ), StrToText(groupId));
		}
		//���û�ȡ������
		inline bool SetManager(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, Integer op)
		{
			return MQA::Detail::SetManager(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(op));
		}
		//ȡ����Ա�б�����Ⱥ��������json
		inline Text GetManager(LLInteger botQQ, LLInteger groupId)
		{
			return MQA::Detail::GetManager(StrToText(botQQ), StrToText(groupId));
		}
		//�߳�Ⱥ��Ա
		inline bool RemoveMember(LLInteger botQQ, LLInteger groupId, LLInteger objQQ, bool refuseJoin)
		{
			return MQA::Detail::RemoveMember(StrToText(botQQ), StrToText(groupId), StrToText(objQQ), StrToText(refuseJoin));
		}
		//����Ⱥ��֤
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

		//ȡָ������Pskey
		inline Text GetDomainPskey(LLInteger botQQ, Text address, Text appid, Text daid)
		{
			return MQA::Detail::GetDomainPskey(StrToText(botQQ), StrToText(address), StrToText(appid), StrToText(daid));
		}
		//��ȡSessionkey
		inline Text GetSessionkey(LLInteger botQQ)
		{
			return MQA::Detail::GetSessionkey(StrToText(botQQ));
		}
		//ȡcookies
		inline Text GetCookies(LLInteger botQQ)
		{
			return MQA::Detail::GetCookies(StrToText(botQQ));
		}
		//ȡSkey
		inline Text GetSkey(LLInteger botQQ)
		{
			return MQA::Detail::GetSkey(StrToText(botQQ));
		}
		//ȡPskey
		inline Text GetPskey(LLInteger botQQ, Str domain)
		{
			return MQA::Detail::GetPskey(StrToText(botQQ), StrToText(domain));
		}
		//ȡClientkey
		inline Text GetClientkey(LLInteger botQQ)
		{
			return MQA::Detail::GetClientkey(StrToText(botQQ));
		}
	}
	namespace BotQQAPI
	{
		//�ϴ���Ƭǽ���ɹ�����filekey��������ɾ����Ƭǽ��ʧ�ܷ��ؿ�
		inline Text UpPhotoWall(LLInteger botQQ, Str imgPath)
		{
			return MQA::Detail::UpPhotoWall(StrToText(botQQ), StrToText(imgPath));
		}
		//��ȡ��Ƭǽ���ɹ�����json��ʧ�ܷ��ؿ�
		inline Text GetPhotoWall(LLInteger botQQ, Str objQQ)
		{
			return MQA::Detail::GetPhotoWall(StrToText(botQQ), StrToText(objQQ));
		}
		//ɾ����Ƭǽ���ɹ������棬ʧ�ܷ��ؼ�
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
		//�޸�ǩ��
		inline bool SetSign(LLInteger botQQ, Str newSign)
		{
			return MQA::Detail::SetSign(StrToText(botQQ), StrToText(newSign));
		}
		//�޸��ǳ�
		inline bool SetNick(LLInteger botQQ, Str newNick)
		{
			return MQA::Detail::SetNick(StrToText(botQQ), StrToText(newNick));
		}
	}
	namespace AnotherAPI
	{

		//��ѯ��ַ��ȫ�ԣ���ȫ���ؿգ����򷵻�һ������
		inline Text GetUrlIsSafe(LLInteger botQQ, Str url)
		{
			return MQA::Detail::GetUrlIsSafe(StrToText(botQQ), StrToText(url));
		}
		//���ͷ�������ʮ�����Ƶ��ֽڼ�
		inline Text SendPacket(LLInteger botQQ, Str cmd, Str pack, Integer time_out)
		{
			return MQA::Detail::SendPacket(StrToText(botQQ), StrToText(cmd), StrToText(pack), StrToText(time_out));
		}
		//ȡ�������ص�ַ
		inline Text GetAudioUrl(LLInteger botQQ, Str token, Str MD5)
		{
			return MQA::Detail::GetAudioUrl(StrToText(botQQ), StrToText(token), StrToText(MD5));
		}
		//���ںŻ�Աǩ��
		inline bool vip_pub_subbutton_qiandao(LLInteger botQQ)
		{
			return MQA::Detail::vip_pub_subbutton_qiandao(StrToText(botQQ));
		}
		//�ֻ���Ա��ҳǩ��
		inline bool vip_qiandao_web(LLInteger botQQ)
		{
			return MQA::Detail::vip_qiandao_web(StrToText(botQQ));
		}
		//��������
		inline Text QueryMusicInfo_fcg_music_search(LLInteger botQQ, Str keyword)
		{
			return MQA::Detail::QueryMusicInfo_fcg_music_search(StrToText(botQQ), StrToText(keyword));
		}
		//�鿴��������
		inline Text QueryMusicInfo_fcg_music_get_song_info_batch(LLInteger botQQ, Str songId)
		{
			return MQA::Detail::QueryMusicInfo_fcg_music_get_song_info_batch(StrToText(botQQ), StrToText(songId));
		}
		//�鿴ת�������¼����
		inline Text MultiMsg_ApplyDown_Group(LLInteger botQQ, Str resId, Integer type)
		{
			return MQA::Detail::MultiMsg_ApplyDown_Group(StrToText(botQQ), StrToText(resId), StrToText(type));
		}
		//ȡƵ���û����ڵ�
		inline Text GetGuildUserHome(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetGuildUserHome(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//ȡƵ���û��ǳ�
		inline Text GetGuildUserName(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetGuildUserName(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//ȡ����Ƶ��ʱ��
		inline Text GetJoinGuildTime(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetJoinGuildTime(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//ȡƵ���û�ͷ����������
		inline Text GetGuildHead(LLInteger botQQ, LLInteger guildId, LLInteger userId)
		{
			return MQA::Detail::GetGuildHead(StrToText(botQQ), StrToText(guildId), StrToText(userId));
		}
		//ȡ��Ƶ���б�����json
		inline Text GetGuildChannelList(LLInteger botQQ, LLInteger guildId)
		{
			return MQA::Detail::GetGuildChannelList(StrToText(botQQ), StrToText(guildId));
		}
		//������Ƶ����Ϣ
		inline bool PbMsgWithDraw_ChannelGuild(LLInteger botQQ, LLInteger guildId, LLInteger subGuildId, Integer MsgReq)
		{
			return MQA::Detail::PbMsgWithDraw_ChannelGuild(StrToText(botQQ), StrToText(guildId), StrToText(subGuildId), StrToText(MsgReq));
		}
		//Ƶ������_ȫԱ����
		inline bool ChannelSet_totalSilence(LLInteger botQQ, LLInteger guildId, LLInteger time)
		{
			return MQA::Detail::ChannelSet_totalSilence(StrToText(botQQ), StrToText(guildId), StrToText(time));
		}

		//���û�����Ƶ������
		inline bool SetRobotGuildNick(LLInteger botQQ, LLInteger GuildId, Str Nick)
		{
			return MQA::Detail::SetRobotGuildNick(StrToText(botQQ), StrToText(GuildId), StrToText(Nick));
		}
		//�˳�Ƶ��
		inline bool QuitGuild(LLInteger botQQ, LLInteger GuildId)
		{
			return MQA::Detail::QuitGuild(StrToText(botQQ), StrToText(GuildId));
		}
		//ȡ���ں��ǳ�
		inline Text GetPublicNick(LLInteger botQQ, LLInteger PublicQQ)
		{
			return MQA::Detail::GetPublicNick(StrToText(botQQ), StrToText(PublicQQ));
		}
		//ȡ����guildId_�ӻ���
		inline Text GetGuildSelfId_cache(LLInteger botQQ)
		{
			return MQA::Detail::GetGuildSelfId_cache(StrToText(botQQ));
		}
		//ȡͼƬ��������
		inline Text GetPicLink(LLInteger botQQ, Integer type, LLInteger sourceId, Str imgId)
		{
			return MQA::Detail::GetPicLink(StrToText(botQQ), StrToText(type), StrToText(sourceId), StrToText(imgId));
		}
		//��ȷ��binĿ¼��ffmpegת���(��ܲ��Դ�)���ɹ�����amr�ļ�����·������ֱ�ӵ����ϴ�����api��ʧ�ܷ��ؿ�
		inline Text Mp3ToAmr(Text mp3, Str amr)
		{
			return MQA::Detail::Mp3ToAmr(mp3, StrToText(amr));
		}
		//��ȷ��binĿ¼��ffmpegת���(��ܲ��Դ�)���ɹ�����amr�ļ�����·������ֱ�ӵ����ϴ�����api��ʧ�ܷ��ؿ�
		inline Text WavToAmr(Text wav, Str amr)
		{
			return MQA::Detail::WavToAmr(StrToText(wav), StrToText(amr));
		}
	}
	namespace HBAPI
	{

		//��ȡ���msgno
		inline Text GetRedPackMsgNo(LLInteger botQQ)
		{
			return MQA::Detail::GetRedPackMsgNo(StrToText(botQQ));
		}
		//��ȡ���vskey
		inline Text GetRedPackVskey(LLInteger botQQ, LLInteger groupId, Text listid, Text authkey)
		{
			return MQA::Detail::GetRedPackVskey(StrToText(botQQ), StrToText(groupId), StrToText(listid), StrToText(authkey));
		}
		//������ݼ���
		inline Text EncryptRedPackData(LLInteger botQQ, Text data, Integer random)
		{
			return MQA::Detail::EncryptRedPackData(StrToText(botQQ), StrToText(data), StrToText(random));
		}
		//������ݽ���
		inline Text DecryptRedPackData(LLInteger botQQ, Text data, Integer random)
		{
			return MQA::Detail::DecryptRedPackData(StrToText(botQQ), StrToText(data), StrToText(random));
		}
		//��ѯ�����ȡ���飬����json
		inline Text GetRedPackDetail(LLInteger botQQ, LLInteger groupId, Str listid, Str authkey)
		{
			return MQA::Detail::GetRedPackDetail(StrToText(botQQ), StrToText(groupId), StrToText(listid), StrToText(authkey));
		}

		//��ͨ������ɹ�success������Ϊʧ��ԭ��
		inline Text RedPack_Ordinary(LLInteger botQQ, Str payPwd, Str sourceId, Str num, Str money, Str greeting, Integer type)
		{
			return MQA::Detail::RedPack_Ordinary(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(num), StrToText(money), StrToText(greeting), StrToText(type));
		}
		//ƴ����������ɹ�success������Ϊʧ��ԭ��
		inline Text RedPack_Luck(LLInteger botQQ, Str payPwd, Str sourceId, Str num, Str money, Str greeting)
		{
			return MQA::Detail::RedPack_Luck(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(num), StrToText(money), StrToText(greeting));
		}
		//���ѷ�����ר��������ɹ�success������Ϊʧ��ԭ��
		inline Text RedPack_Exclusive(LLInteger botQQ, Str payPwd, Str sourceId, Str objQQ, Str num, Str money, Str greeting)
		{
			return MQA::Detail::RedPack_Exclusive(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(objQQ), StrToText(num), StrToText(money), StrToText(greeting));
		}
		//���������ɹ�success������Ϊʧ��ԭ��
		inline Text RedPack_KeyWord(LLInteger botQQ, Str payPwd, Str sourceId, Str num, Str money, Str discourse, Integer type)
		{
			return MQA::Detail::RedPack_KeyWord(StrToText(botQQ), StrToText(payPwd), StrToText(sourceId), StrToText(num), StrToText(money), StrToText(discourse), StrToText(type));
		}
		//ת�ˣ��ɹ�success������Ϊʧ��ԭ��
		inline Text TransferAccounts(LLInteger botQQ, Str payPwd, Str objQQ, Str objNick, Str money, Str msg, Integer type)
		{
			return MQA::Detail::TransferAccounts(StrToText(botQQ), StrToText(payPwd), StrToText(objQQ), StrToText(objNick), StrToText(money), StrToText(msg), StrToText(type));
		}
		//��ѯǮ�����ɹ����������ֵ�����򷵻�ʧ��ԭ��
		inline Text QueryBalance(LLInteger botQQ, Str payPwd)
		{
			return MQA::Detail::QueryBalance(StrToText(botQQ), StrToText(payPwd));
		}
		//��ѯ�����¼���ɹ����������ֵ�����򷵻�ʧ��ԭ��
		inline Text RedPack_Log(LLInteger botQQ, Str payPwd, Str year, Integer typ, Integer page)
		{
			return MQA::Detail::RedPack_Log(StrToText(botQQ), StrToText(payPwd), StrToText(year), StrToText(typ), StrToText(page));
		}
	}
}
#endif // !__MQAAPI_DEFINE__