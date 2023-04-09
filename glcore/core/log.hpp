//
// Created by shepherd on 20.3.23.
//

#ifndef GLCORE_LOG_HPP
#define GLCORE_LOG_HPP

#include <spdlog/spdlog.h>

namespace glcore {

class Log {
public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetCoreLogger();

    static std::shared_ptr<spdlog::logger>& GetAppLogger();

private:
    static std::shared_ptr<spdlog::logger> core_logger_;
    static std::shared_ptr<spdlog::logger> app_logger_;
};

} // glcore

#define INIT_LOG() glcore::Log::Init()

#define LOG_CORE_TRACE(...) glcore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) glcore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) glcore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) glcore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) glcore::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_APP_TRACE(...) glcore::Log::GetAppLogger()->trace(__VA_ARGS__)
#define LOG_APP_INFO(...) glcore::Log::GetAppLogger()->info(__VA_ARGS__)
#define LOG_APP_WARN(...) glcore::Log::GetAppLogger()->warn(__VA_ARGS__)
#define LOG_APP_ERROR(...) glcore::Log::GetAppLogger()->error(__VA_ARGS__)
#define LOG_APP_CRITICAL(...) glcore::Log::GetAppLogger()->critical(__VA_ARGS__)

#endif //GLCORE_LOG_HPP
