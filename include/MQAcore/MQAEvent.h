#pragma once

#ifndef __MQA_EVENT__
#define __MQA_EVENT__
#include <MQACore/MQAType.h>

#define EVENT(ReturnType, Name, Size) __pragma(comment(linker, "/EXPORT:" #Name "=_" #Name "@" #Size))\
 extern "C" ReturnType __stdcall Name
#define __MQAEVENT(__Event, __EventData)\
		void reg_##__Event(const std::function<void(__EventData)>& _Callback, const uint16_t& priority = 30000);\
		void clr_##__Event(void);

namespace MQA
{
	namespace Enum
	{
		enum class MQAEventEnum : Integer
		{
			群事件_我被邀请加入群 = 1,
			群事件_某人加入了群 = 2,
			群事件_某人申请加群 = 3,
			群事件_群被解散 = 4,
			群事件_某人退出了群 = 5,
			群事件_某人被踢出群 = 6,
			群事件_某人被禁言 = 7,
			群事件_某人被解除禁言 = 26,
			群事件_某人撤回事件 = 8,
			群事件_某人被取消管理 = 9,
			群事件_某人被赋予管理 = 10,
			群事件_开启全员禁言 = 11,
			群事件_关闭全员禁言 = 12,
			群事件_开启匿名聊天 = 13,
			群事件_关闭匿名聊天 = 14,
			群事件_某人获得专属头衔 = 25,
			好友事件_被好友删除 = 15,
			好友事件_签名变更 = 16,
			好友事件_昵称改变 = 17,
			好友事件_某人撤回事件 = 18,
			好友事件_有新好友 = 19,
			好友事件_好友请求 = 20,
			好友事件_对方同意了您的好友请求 = 21,
			好友事件_对方拒绝了您的好友请求 = 22,
			群事件_某人入场 = 27,
			系统事件_帐号登录完毕 = 24
		};
		enum class MQAMsgType : Integer
		{
			消息类型_临时会话 = 141,
			消息类型_好友通常消息 = 166,
			消息类型_讨论组消息 = 83

		};
		enum class MQAMsgSubType : Integer
		{
			消息类型_临时会话_群临时 = 0,
			消息类型_临时会话_讨论组临时 = 1,
			消息类型_临时会话_公众号 = 129,
			消息类型_临时会话_网页QQ咨询 = 201,
			消息类型_临时会话_好友申请验证消息 = 134

		};
		enum class EventRet : Integer
		{
			消息处理_忽略 = 0,
			消息处理_继续 = 1,
			消息处理_拦截 = 2,
			事件处理_同意 = 10,
			事件处理_拒绝 = 20
		};
	}
	namespace Event
	{
		class Event
		{
		public:
			void eventBlock()const { EventContinue = false; }
			bool eventContinue(void)const { return this->EventContinue; }
		protected:
			std::time_t EventTime;
			mutable std::atomic_bool EventContinue = true;
			Event() : EventTime(std::time(0)) {}
		};
		class UserEvent : public Event
		{
		public:
			mutable Enum::EventRet operation;
			UserEvent() : Event(), operation(Enum::EventRet::消息处理_忽略) {}
			virtual ~UserEvent() {}
			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_忽略;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_继续;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::消息处理_拦截;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::消息处理_拦截;
			}
		};
		template<class _OpTy = Enum::EventRet>
		class SysEvent : public Event
		{
		public:
			mutable _OpTy operation;
			SysEvent() : Event() {}
			virtual ~SysEvent() {}
			void block(const _OpTy& _str)const
			{
				operation = _str;
			}
		};
		struct SettingEvent : public SysEvent<Enum::EventRet> {
			SettingEvent() : SysEvent<Enum::EventRet>() {
				this->operation = Enum::EventRet::消息处理_忽略;
			}

			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_忽略;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_继续;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::消息处理_拦截;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::消息处理_拦截;
			}
		};
		struct EndEvent : public SysEvent<Enum::EventRet> {
			EndEvent() {
				this->operation = Enum::EventRet::消息处理_忽略;
			}

			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_忽略;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_继续;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::消息处理_拦截;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::消息处理_拦截;
			}
		};
		struct LoadEvent : public SysEvent<Enum::EventRet>
		{
			LoadEvent() {
				this->operation = Enum::EventRet::消息处理_忽略;
			}

			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_忽略;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::消息处理_继续;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::消息处理_拦截;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::消息处理_拦截;
			}
		};
		struct EnableEvent : public SysEvent<Str>
		{
			EnableEvent() {
				this->operation.clear();
			}
		};
		struct DisableEvent : public SysEvent<Enum::EventRet> {
			DisableEvent() {
				this->operation = Enum::EventRet::消息处理_忽略;
			}
		};
		struct PrivateEvent : public UserEvent
		{
			Str fromUin;
			Str myUin;
			Str toUin;
			Str fromReq;
			Str fromRecvTime;
			Str fromGroup;
			Str fromSendTime;
			Str fromRandom;
			Integer pieceIndex;
			Integer pieceCount;
			Integer pieceFlag;
			Str message_content;
			Integer buddleId;
			Integer msgType;
			Integer subType;
			Integer subTempMsgType;
			Integer red_packet_type;
			Str chatToken;
			Str fromEventUin;
			Str fromEventNick;
			Str fileId;
			Str fileMd5;
			Str fileName;
			UInteger fileSize;
		};
		struct GulidEvent : public UserEvent
		{
			Str senderId;
			Str senderNick;
			Str myUin;
			Str fromReq;
			Str fromRecvTime;
			Str guildId;
			Str guildChannelId;
			Str guildName;
			Str guildChannelName;
			Str fromSendTime;
			Str fromRandom;
			Integer pieceIndex;
			Integer pieceCount;
			Integer pieceFlag;
			Integer subType;
			Str title;
			Str message_content;
			Str reply_info;
			Integer buddleId;
			Integer lon;
			Integer lat;
		};
		struct GroupEvent : public UserEvent
		{
			Str fromUin;
			Str myUin;
			Str fromReq;
			Str fromRecvTime;
			Str fromGroup;
			Str groupName;
			Str fromCard;
			Str fromSendTime;
			Str fromRandom;
			Integer pieceIndex;
			Integer pieceCount;
			Integer pieceFlag;
			Integer subType;
			Str title;
			Str message_content;
			Str reply_info;
			Integer buddleId;
			Integer lon;
			Integer lat;

		};
		struct NormalEvent : public UserEvent
		{
			Str fromMyUin;
			Str fromGroupUin;
			Str fromGroupName;
			Str fromOpUin;
			Str fromOpNick;
			Str fromUin;
			Str fromNick;
			Str fromSeq;
			Str fromReq;
			Str fromTime;
			Str fromRandom;
			Str fromContent;
			Integer type;
			Integer subType;
		};

		__MQAEVENT(Load, LoadEvent const&)
		__MQAEVENT(Enable, EnableEvent const&)
		__MQAEVENT(Disable, DisableEvent const&)
		__MQAEVENT(PrivateMsg, PrivateEvent const&)
		__MQAEVENT(GroupMsg, GroupEvent const&)
		__MQAEVENT(GulidMsg, GulidEvent const&)
		__MQAEVENT(Event, NormalEvent const&)
		__MQAEVENT(Setting, SettingEvent const&)
		__MQAEVENT(End, EndEvent const&)
	}
}

void CallingConvention __Init(void);
void CallingConvention __UnInit(void);
#define OutTime(num) if (num < (InitTime - clock()) / CLK_TCK) 
void init();
#define MQA_REGISTER_EVENT						\
	void init()
#undef __MQAEVENT
#endif // !__MQA_EVENT__

