#pragma once


#ifdef RY_PLAYFROM_WINDOWS
#ifdef RY_BUILD_DLL
#define ROYU_API __declspec(dllexport)
#else
#define ROYU_API __declspec(dllimport)
#endif
#else
#error Royu only support Windows!
#endif 

#ifdef RY_ENABLE_ASSERTS
#define RY_ASSERT(x,...){if!(x)){RY_ERROE("Assertion Faild {0}",__VA_ARGS__);__debugbreak();}}
#define RY_CORE_ASSERT(x,...){if!(x)){RY_ERROE("Assertion Faild {0}",__VA_ARGS__);__debugbreak();}}
#else
#define RY_ASSERT(x,...)
#define RY_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)