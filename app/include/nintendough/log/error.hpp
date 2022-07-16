#ifndef NINTENDOUGH_LOG_ERROR_HPP
#define NINTENDOUGH_LOG_ERROR_HPP

#include <nintendough/error.hpp>

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
                    error::SourceLocation const &slc) noexcept
      : error::INintendoughAbstractError(msg, slc) {}

  /**
   * \brief convenience method to verify the loggers have been initialized
   * */
  static auto LoggerInitialized(bool initialized,
                                error::SourceLocation const &slc) -> void {
    if (!initialized) {
      throw LoggerInitFailure("Loggers were not initialized", slc);
    }
  }
};

}  // namespace nintendough::log

#endif
