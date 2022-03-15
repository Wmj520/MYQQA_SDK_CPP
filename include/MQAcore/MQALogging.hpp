#pragma once
#ifndef __MQLOGGER_H__
#define __MQLOGGER_H__
#include "MQAType.h"
#include "MQAAPI.h"
#include <detail/Logger.hpp>

namespace MQA
{
	namespace Detail
	{
		class MQAlogger : public logger::Logger, public singleton<MQAlogger>
		{
			void __LOG(const char* _logMsg)final
			{
				FrameAPI::OutPut(_logMsg);
			}
		};
	}
	namespace logging
	{
#define Logger(__Level) static inline void __Level(Text _msg)\
		{\
			Detail::MQAlogger::instance()->__Level(_msg);\
		}
		Logger(debug)
		Logger(info)
		Logger(warning)
		Logger(error)
		Logger(fatal)
#undef Logger
	}
}
#endif // !__MQLOGGER_H__
