#pragma once


#ifdef RY_PLAYFROM_WINDOWS
#ifdef RY_BUILD_DLL
#define ROYUYU_API __declspec(dllexport)
#else
#define ROYUYU_API __declspec(dllimport)
#endif
#else
#error Royuyu only support Windows!
#endif // HZ_BUILE_DLL
