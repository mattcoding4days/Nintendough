#ifndef NINTENDOUGH_LOG_ERROR_HPP
#define NINTENDOUGH_LOG_ERROR_HPP

#include <nintendough/error/module.hpp>

/**
 * \file nintendough/log/error.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief result errors for logging module
 */
namespace nintendough::log {
/**
 * \brief Logger module custom error
 */
class LoggerInitFailure : public error::INintendoughAbstractError {
 public:
  LoggerInitFailure(std::string_view const &msg,
                    error::SourceLocation &&slc) noexcept
      : error::INintendoughAbstractError(msg, std::move(slc)) {}

  /**
   * \brief convenience method to verify the loggers have been initialized
   * */
  static auto AssertLoggerInitialized(bool initialized,
                                      error::SourceLocation &&slc) -> void {
    if (!initialized) {
      throw LoggerInitFailure("Loggers were not initialized", std::move(slc));
    }
  }
};

}  // namespace nintendough::log

#endif
