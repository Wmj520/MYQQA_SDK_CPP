#include <MQACore/MQAAPI.h>

namespace MQA::Detail
{
    std::vector<std::function<void(HMODULE)>> apiFuncInitializers;
#define MQAAPI(Name, ReturnType, ...) Name##_FUNC _##Name; \
	using Name##_TYPE = ReturnType (__stdcall*)(__VA_ARGS__); \
    bool _init_##Name = addFuncInit( [] (const auto& hModule) { \
        _##Name = reinterpret_cast<Name##_TYPE>(GetProcAddress(hModule, "Api_" #Name)); \
        if (!_##Name)MQAExceptionCode(MQAException::MQAExceptionEnum::MQADllFuncError, "Unable to initialize API Function " #Name); \
    });
#include <MQAcore/MyQQAAPI.inc>
#undef MQAPI
}