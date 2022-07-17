#ifndef NINTENDOUGH_LOG_LOGGER_HPP
#define NINTENDOUGH_LOG_LOGGER_HPP

/**
 * \file nintendough/log/logger.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief logger implementation using spdlog
 */

#include <spdlog/spdlog.h>

#include <nintendough/common.hpp>
#include <nintendough/log/error.hpp>

namespace nintendough::log {
/**
 * \brief C++17 version of a Meyers singleton
 *
 * \code{.cpp}
 * #include <nintendough/log/module.hpp>
 *
 * try {
 *   log::Logger::instance().init();
 *   log::info("Nintedough version: {}", get_version());
 * } catch (log::LoggerInitFailure const &e) {
 *   std::cerr << e.formatted_info() << '\n';
 * }
 * \endcode
 * */
class Logger {
 public:
  /**
   * \brief explicitly delete the abillity to copy this object
   * */
  Logger(Logger const &) = delete;
  Logger &operator=(Logger const &) = delete;

  /**
   * \brief only move semantics are allowed
   * */
  Logger(Logger &&) = default;
  Logger &operator=(Logger &&) noexcept = default;

  /**
   * \brief get an instance to the logger
   *
   * \returns reference to Logger
   * */
  static auto instance() -> Logger &;

  /**
   * \brief Initialize spdlog
   *
   * \param std::filesystem::path logging directory path
   *
   * \details no filename should be appended, just the path,
   *  the logging file name is appended within this init method
   *
   * \throws LoggerInitFailure
   * */
  auto init(std::filesystem::path log_path) -> void;

  /**
   * \brief  Getter for the console logger
   *
   * \returns const reference to std::shared_ptr
   *
   * \throw LoggerInitFailure if init() method was never called
   * */
  [[nodiscard]] auto get_console_logger()
      -> std::shared_ptr<spdlog::logger> const &;

  /**
   * \brief Getter for the file logger
   *
   * \returns const reference std::shared_ptr
   *
   * \throw LoggerInitFailure if init() method was never called
   * */
  [[nodiscard]] auto get_file_logger()
      -> std::shared_ptr<spdlog::logger> const &;

 private:
  /**
   * /brief private ctor and dtor because Singleton
   * */
  Logger() = default;
  ~Logger() = default;

  bool mInitialized{};
  std::shared_ptr<spdlog::logger> mConsoleLogger{};
  std::shared_ptr<spdlog::logger> mFileLogger{};
};

/**
 * \brief Wrap both console and file loggers into templated variadic
 * functions for global convenience
 * */
template <typename... Args>
constexpr auto trace(Args... args) -> void {
  Logger::instance().get_console_logger()->trace(std::forward<Args>(args)...);
  Logger::instance().get_file_logger()->trace(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr auto debug(Args... args) -> void {
  Logger::instance().get_console_logger()->debug(std::forward<Args>(args)...);
  Logger::instance().get_file_logger()->debug(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr auto info(Args... args) -> void {
  Logger::instance().get_console_logger()->info(std::forward<Args>(args)...);
  Logger::instance().get_file_logger()->info(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr auto warn(Args... args) -> void {
  Logger::instance().get_console_logger()->warn(std::forward<Args>(args)...);
  Logger::instance().get_file_logger()->warn(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr auto error(Args... args) -> void {
  Logger::instance().get_console_logger()->error(std::forward<Args>(args)...);
  Logger::instance().get_file_logger()->error(std::forward<Args>(args)...);
}

template <typename... Args>
constexpr auto critical(Args... args) -> void {
  Logger::instance().get_console_logger()->critical(
      std::forward<Args>(args)...);
  Logger::instance().get_file_logger()->critical(std::forward<Args>(args)...);
}
};  // namespace nintendough::log

#endif
