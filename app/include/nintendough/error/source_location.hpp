#ifndef NINTENDOUGH_ERROR_SOURCE_LOCATION_HPP
#define NINTENDOUGH_ERROR_SOURCE_LOCATION_HPP

/**
 * \file nintendough/error/source_location.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief source location for runtime information
 */

namespace nintendough::error {
/**
 * \brief structure that holds run time location information
 */
struct SourceLocation {
  SourceLocation(std::string_view const &file, std::uint32_t line,
                 std::string_view const &func) noexcept;

  const std::string mFile{};
  const std::uint32_t mLine{};
  const std::string mFunc{};
};

/**
 * \brief Wrapper macro which will gaurentee that the accurate file, function
 *  name, and line number will be reported
 */
#define RUNTIME_INFO                 \
  SourceLocation(__FILE__, __LINE__, \
                 static_cast<const char *>(__PRETTY_FUNCTION__))
};  // namespace nintendough::error

#endif
