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

#ifdef RY_DEBUG
#define RY_ENABLE_ASSERTS
#endif 


#ifdef RY_ENABLE_ASSERTS
#define RY_ASSERT(x,...)if(!(x)){RY_ERROR("Assertion Faild {0}",__VA_ARGS__);__debugbreak();}
#define RY_CORE_ASSERT(x,...)if(!(x)){RY_CORE_ERROR("Assertion Faild {0}",__VA_ARGS__);__debugbreak();}
#else
#define RY_ASSERT(x,...)
#define RY_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)
#define RY_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)