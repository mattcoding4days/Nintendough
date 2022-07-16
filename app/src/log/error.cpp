#include <nintendough/log/error.hpp>

namespace nintendough::log {
LoggerInitFailure::LoggerInitFailure(std::string_view const &msg,
                                     error::SourceLocation &&slc) noexcept
    : error::INintendoughAbstractError(msg, std::move(slc)) {}

auto LoggerInitFailure::AssertLoggerInitialized(bool initialized,
                                                error::SourceLocation &&slc)
    -> void {
  if (!initialized) {
    throw LoggerInitFailure("Loggers were not initialized", std::move(slc));
  }
}

};  // namespace nintendough::log
