#pragma once
#ifndef __MQA_EXCEPTION_H__
#define __MQA_EXCEPTION_H__
#include <exception>
#include <ctime>
#include <sstream>
#include <Windows.h>
#include <functional>
#include <detail/Logger.hpp>
#include <MQACore/MQAType.h>
#ifndef __MYEXCEPTION_H__
#define __MYEXCEPTION_H__
struct MyException : public std::exception
{
protected:
	char* str;
public:
	UINT code;
	std::string ExcepetionName;
	const char* ExcepetionDesc;

	MyException(int code, const char* desc = "") :code(code), ExcepetionDesc(desc), str(new char[512])
	{}
	~MyException() { _DELETE_Arr(str); }
	virtual const char* what() const throw()
	{
		return ("MyException");
	}
	virtual void log(const char* LogPath) const throw()
	{
	}
};
#endif // !__MYEXCEPTION_H__

extern Text LogFile;
namespace MQA
{
	class MQAException : public MyException
	{
	public:
		MQAException(Integer code, Text desc = "") : MyException(code, desc)
		{
			this->ExcepetionName = "MQAException";
		}
		enum MQAExceptionEnum
		{
			MQAOK, MQAInitOutTime = 1, MQADllInitFailed = 2, MQADllFuncError = 3
		};
		inline Text what()const throw() override
		{
			memset(str, 0, 512);
			sprintf(str, "��%s[%s %s]:Error Code 0X%.4X", ExcepetionName.c_str(), __DATE__, __TIME__, code);
			switch (code)
			{
			case MQAExceptionEnum::MQAInitOutTime: sprintf(str, "%s, %s\n", str, "�����ʼ��ʧ�ܣ�");
				break;
			case MQAExceptionEnum::MQADllInitFailed: sprintf(str, "%s, %s\n", str, "api����ʧ�ܣ���ȷ��·�����Ƿ���ڶ�ӦDll�ļ����߲���Ƿ�ʹ���˴���ĺ�������");
				break;
			case MQAExceptionEnum::MQADllFuncError: sprintf(str, "%s, %s\n", str, "api��������ʧ�ܣ���ȷ��dll�Ƿ���ڶ�Ӧ������");
				break;
			case MQAOK:
			default: sprintf(str, "%s, %s\n", str, "����������У�");
				break;
			}
			if (this->ExcepetionDesc != "")
			{
				sprintf(str, "%s%s\n", str, this->ExcepetionDesc);
			}
			return str;
		}
		inline void log(Text logfile = LogFile) const throw() override
		{
			using namespace logger;
			auto* _logger = fileLogger::instance();
			if (_logger)
			{
				_logger->set(logfile);
				_logger->info(what());
			}
		}
	};

}
#define MQAExceptionCode(code, desc) \
	try\
	{\
		throw(MQAException(code, desc));\
	}\
	catch (const MQA::MQAException& e)\
	{\
		e.log();\
	}\


template <typename T, typename... Args>
std::function<T(Args...)> __stdcall MQAExceptionWrapper(T(__stdcall* func)(Args...))
{
	return std::function<T(Args...)>([func](Args&&... args) -> T
		{
			try
			{
				return func(std::forward<Args>(args)...);
			}
			catch (const MQA::MQAException& e)
			{
				e.log();
			}
			return T(0);
		});
}
#endif // !__MQA_EXCEPTION_H__
