#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace Lemon {

    class LEMON_API Log {
        public:
        Log();
        ~Log();

        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

        private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

#define LM_CORE_WARN(...) ::Lemon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LM_CORE_ERROR(...) ::Lemon::Log::GetCoreLogger()->error(__VA_ARGS__)

#define LM_WARN(...) ::Lemon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LM_ERROR(...) ::Lemon::Log::GetClientLogger()->error(__VA_ARGS__)


#ifdef LM_DEBUG
    #define LM_CORE_TRACE(...) ::Lemon::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define LM_CORE_INFO(...) ::Lemon::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define LM_TRACE(...) ::Lemon::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define LM_INFO(...) ::Lemon::Log::GetClientLogger()->info(__VA_ARGS__) 
#endif
