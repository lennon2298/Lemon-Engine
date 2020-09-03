#pragma once
#include "debugbreak.h"

#ifdef LM_PLATFORM_WINDOWS
    #ifdef LM_BUILD_DLL
        #define LEMON_API __declspec(dllexport)
    #else
        #define LEMON_API __declspec(dllimport)
    #endif
#elif LM_PLATFORM_LINUX
    #ifdef LM_BUILD_DLL
        #define LEMON_API __attribute__((visibility("default")))
    #else
        #define LEMON_API
    #endif
#endif

#define BIT(x) (1 << x)

#ifdef LM_ENABLE_ASSERTS
	#define LM_ASSERT(x, ...) { if(!(x)) { LM_ERROR("Assertion Failed: {0}", __VA_ARGS__); debug_break(); } }
	#define LM_CORE_ASSERT(x, ...) { if(!(x)) { LM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); debug_break(); } }
#else
	#define LM_ASSERT(x, ...)
	#define LM_CORE_ASSERT(x, ...)
#endif
