//
// Created by shepherd on 20.3.23.
//

#include <glcore/core/log.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace glcore {

std::shared_ptr<spdlog::logger> Log::core_logger_;
std::shared_ptr<spdlog::logger> Log::app_logger_;

void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    core_logger_ = spdlog::stdout_color_mt("CORE");
    core_logger_->set_level(spdlog::level::trace);

    app_logger_ = spdlog::stdout_color_mt("APP");
    app_logger_->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Log::GetCoreLogger() {
    return core_logger_;
}

std::shared_ptr<spdlog::logger>& Log::GetAppLogger() {
    return app_logger_;
}

} // glcore