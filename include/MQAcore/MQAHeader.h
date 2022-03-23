#pragma once
#ifndef __MQA_HEADER__
#define __MQA_HEADER__
#include <MQAconfig.h>
#if !defined MYQQA
#define MYQQA
#define MYQQAVER "1.0.3"
#endif
#if (!defined (MYQQ)) && (!defined MYQQA)
#error 请在"MQHeader.H"确定你使用的MYQQ版本！
#elif (defined MYQQ) && (defined MYQQA)
#error 请选择其中一个版本！
#endif

#define APIDLLNAME "MyQQAApi.dll"

#if !defined USE_CMAKE
#define PluginId "MYQQA_SDK_CPP"
#define PluginAuthor "you"
#define PluginDesc "plugin information"
#define PluginVer "1.0.0"
#define PluginSkey "SDG5D4Ys89h7DJ849d"
#define PluginSdk "S1"
#endif

#if !defined PluginId 
#error 请确定插件名字‘PluginId’！
#endif

#include "MQAType.h"
#include "MQAAPI.h"
#include "MQAEvent.h"
#include "MQAException.hpp"
#include "MQALogging.hpp"
#endif // !__MQA_HEADER__
