#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <nintendough/log/defaults.hpp>
#include <nintendough/log/logger.hpp>

namespace nintendough::log {

auto Logger::instance() -> Logger& {
  static Logger instance;
  return instance;
}

auto Logger::get_console_logger() -> std::shared_ptr<spdlog::logger> const& {
  LoggerInitFailure::AssertLoggerInitialized(mInitialized, error::RUNTIME_INFO);
  return mConsoleLogger;
}

auto Logger::get_file_logger() -> std::shared_ptr<spdlog::logger> const& {
  LoggerInitFailure::AssertLoggerInitialized(mInitialized, error::RUNTIME_INFO);
  return mFileLogger;
}

auto Logger::init() -> void {
  LoggerInitFailure::AssertLoggerInitialized(mInitialized, error::RUNTIME_INFO);
  try {
    spdlog::set_pattern("%^[%c]::[%n]::[%l]  %v%$");
    mConsoleLogger = spdlog::stdout_color_mt(Defaults::console_logger_name);
    mConsoleLogger->set_level(spdlog::level::trace);
    mFileLogger = spdlog::rotating_logger_mt(
        Defaults::file_logger_name, "nintendough.log", Defaults::max_file_size,
        Defaults::max_files);
    mFileLogger->set_level(spdlog::level::trace);
  } catch (std::exception const& e) {
    throw LoggerInitFailure(e.what(), error::RUNTIME_INFO);
  }
  mInitialized = true;
}
};  // namespace nintendough::log
