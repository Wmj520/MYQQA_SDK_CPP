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
			Ⱥ�¼�_�ұ��������Ⱥ = 1,
			Ⱥ�¼�_ĳ�˼�����Ⱥ = 2,
			Ⱥ�¼�_ĳ�������Ⱥ = 3,
			Ⱥ�¼�_Ⱥ����ɢ = 4,
			Ⱥ�¼�_ĳ���˳���Ⱥ = 5,
			Ⱥ�¼�_ĳ�˱��߳�Ⱥ = 6,
			Ⱥ�¼�_ĳ�˱����� = 7,
			Ⱥ�¼�_ĳ�˱�������� = 26,
			Ⱥ�¼�_ĳ�˳����¼� = 8,
			Ⱥ�¼�_ĳ�˱�ȡ������ = 9,
			Ⱥ�¼�_ĳ�˱�������� = 10,
			Ⱥ�¼�_����ȫԱ���� = 11,
			Ⱥ�¼�_�ر�ȫԱ���� = 12,
			Ⱥ�¼�_������������ = 13,
			Ⱥ�¼�_�ر��������� = 14,
			Ⱥ�¼�_ĳ�˻��ר��ͷ�� = 25,
			�����¼�_������ɾ�� = 15,
			�����¼�_ǩ����� = 16,
			�����¼�_�ǳƸı� = 17,
			�����¼�_ĳ�˳����¼� = 18,
			�����¼�_���º��� = 19,
			�����¼�_�������� = 20,
			�����¼�_�Է�ͬ�������ĺ������� = 21,
			�����¼�_�Է��ܾ������ĺ������� = 22,
			Ⱥ�¼�_ĳ���볡 = 27,
			ϵͳ�¼�_�ʺŵ�¼��� = 24
		};
		enum class MQAMsgType : Integer
		{
			��Ϣ����_��ʱ�Ự = 141,
			��Ϣ����_����ͨ����Ϣ = 166,
			��Ϣ����_��������Ϣ = 83

		};
		enum class MQAMsgSubType : Integer
		{
			��Ϣ����_��ʱ�Ự_Ⱥ��ʱ = 0,
			��Ϣ����_��ʱ�Ự_��������ʱ = 1,
			��Ϣ����_��ʱ�Ự_���ں� = 129,
			��Ϣ����_��ʱ�Ự_��ҳQQ��ѯ = 201,
			��Ϣ����_��ʱ�Ự_����������֤��Ϣ = 134

		};
		enum class EventRet : Integer
		{
			��Ϣ����_���� = 0,
			��Ϣ����_���� = 1,
			��Ϣ����_���� = 2,
			�¼�����_ͬ�� = 10,
			�¼�����_�ܾ� = 20
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
			UserEvent() : Event(), operation(Enum::EventRet::��Ϣ����_����) {}
			virtual ~UserEvent() {}
			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::��Ϣ����_����;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::��Ϣ����_����;
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
				this->operation = Enum::EventRet::��Ϣ����_����;
			}

			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::��Ϣ����_����;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::��Ϣ����_����;
			}
		};
		struct EndEvent : public SysEvent<Enum::EventRet> {
			EndEvent() {
				this->operation = Enum::EventRet::��Ϣ����_����;
			}

			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::��Ϣ����_����;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::��Ϣ����_����;
			}
		};
		struct LoadEvent : public SysEvent<Enum::EventRet>
		{
			LoadEvent() {
				this->operation = Enum::EventRet::��Ϣ����_����;
			}

			void retIgnore(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retContinue(void)const
			{
				if (!retBlocked())
					this->operation = Enum::EventRet::��Ϣ����_����;
			}
			void retBlock(void)const
			{
				this->operation = Enum::EventRet::��Ϣ����_����;
			}
			bool retBlocked(void)const
			{
				return this->operation == Enum::EventRet::��Ϣ����_����;
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
				this->operation = Enum::EventRet::��Ϣ����_����;
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

