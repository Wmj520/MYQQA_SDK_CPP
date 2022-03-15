#pragma once
#ifndef __MQATYPE__
#define __MQATYPE__
#include <cstdint>
#include <string>
typedef const char* Text;
typedef std::string Str;
typedef std::stringstream StrBuffer;
typedef int32_t Integer;
typedef uint32_t UInteger;
typedef int64_t LLInteger;
typedef uint64_t ULLInteger;
typedef int8_t SInteger;
typedef uint8_t SUInteger;

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
#endif