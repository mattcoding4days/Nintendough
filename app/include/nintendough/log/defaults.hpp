#ifndef NINTENDOUGH_LOG_DEFAULTS_HPP
#define NINTENDOUGH_LOG_DEFAULTS_HPP

/**
 * \file nintendough/log/defaults.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief Constant defaults for logger configuration
 */

namespace nintendough::log {
/**
 * \brief These will be used for primary development,
 *  but will be used as fallbacks once a json config
 *  file is implemented and read from disk
 * */
struct Defaults {
  static constexpr auto console_logger_name = "Nintendough Console";
  static constexpr auto file_logger_name = "Nintendough";
  static constexpr auto max_file_size = 1048576 * 5; // 5mb size
  static constexpr auto max_files = 3;
};
}  // namespace nintendough::log

#endif
