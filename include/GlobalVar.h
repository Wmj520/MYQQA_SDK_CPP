#pragma once
#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__
#include <MQAconfig.h>
#include <detail/ThreadPool.hpp>
#include <MQAcore/MQAType.h>

extern std::atomic<bool> PluginLoad;
extern std::atomic<bool> EventContInit;
extern ThreadPool::TPool p;
extern HMODULE MQAHModule;
extern HMODULE DllHModule;

#ifdef USE_TIMER
#include <Timer.hpp>
extern Timer::Looper::IOEventLoop Looper;
extern std::atomic<bool> LooperInit;
#endif // USE_TIMER

#ifdef USE_JSONCPP
#include <json/json.h>
extern Str MQInfoStr;
extern Json::Value MQInfoJson;
#endif
#endif // !__GLOBALVAR_H__
