#ifndef NINTENDOUGH_VERSION_HPP
#define NINTENDOUGH_VERSION_HPP

/**
 * \file nintendough/version.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief Adds version support for project, used by Cmake
 */

#include <string>

#define VMAJOR 0
#define VMINOR 1
#define VPATCH 0

namespace nintendough {
/**
 * \brief version (major.minor.patch) in string format
 *
 * \returns std::string
 * */
[[maybe_unused]] inline static auto get_version() -> std::string {
  std::string version_string{std::to_string(VMAJOR)};
  return version_string.append(".")
      .append(std::to_string(VMINOR))
      .append(".")
      .append(std::to_string(VPATCH));
}
}  // namespace nintendough

#endif
