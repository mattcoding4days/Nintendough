#ifndef NINTENDOUGH_UTILS_SYSTEM_DEFAULTS_HPP
#define NINTENDOUGH_UTILS_SYSTEM_DEFAULTS_HPP

#include <nintendough/common.hpp>

namespace nintendough::utils {
/**
 * \brief There are two different config files, one for the nintendough itself,
 *  and another for controller mappings
 * */
enum class ConfigFile { System, Controller };

/**
 * \brief Provides Nintendough specific default values and paths for
 *  configuration, logging, and common file manipulation utilities using the
 *  standard c++ 17 filesystem library
 * */
class SystemDefault {
 public:
  /**
   * \brief Returns the absolute path for the config directory
   *
   * \details /home/user/.config/log/nintendough
   *
   * \returns std::filesystem::path
   * */
  [[nodiscard]] static auto config_dir() noexcept -> std::filesystem::path;

  /**
   * \brief Returns the absolute path for the cache directory
   *
   * \details /home/user/.cache/nintendough
   *
   * \returns std::filesystem::path
   * */
  [[nodiscard]] static auto cache_dir() noexcept -> std::filesystem::path;

  /**
   * \brief Returns the absolute path for the log dump directory
   *
   * \details /home/user/.config/log/nintendough
   *
   * \returns std::filesystem::path
   * */
  [[nodiscard]] static auto logging_dir() noexcept -> std::filesystem::path;

  /**
   * \brief gets the absolute path for a configfile specified via the
   * ConfigFile type param
   *
   * \param ConfigFile::System, ConfigFile::Controller
   *
   * \returns std::filesystem::path
   * */
  [[nodiscard]] static auto get_config_file_path_for(ConfigFile type) noexcept
      -> std::filesystem::path;

 private:
  /**
   * \brief Returns the absolute path for the users home directory,
   *  if for some reason the HOME env variable is not defined (unlikely)
   *  the function will return the current_path
   *
   *  \return std::filesystem::path
   * */
  [[nodiscard]] static auto home_() noexcept -> std::filesystem::path;
    
  /**
   * \brief Hard coded constants to build directory paths and
   *  read/write files
   *
   * \details TestDataDir will point the the config direcory
   *  at the root level of this project, if tests are enabled
   *  the macro NINTENDOUGH_TEST_DATA_DIR will be populated
   * */
  static constexpr auto ProgName{"nintendough"};
  static constexpr auto SysConfigFile{"sys-config.json"};
  static constexpr auto ControllerConfigFile{"controller-config.json"};
  static const char* const TestDataDir;
};

#ifdef NINTENDOUGH_TEST_DATA_DIR
inline const char* const SystemDefault::TestDataDir{NINTENDOUGH_TEST_DATA_DIR};
#else
inline const char* const SystemDefault::TestDataDir{nullptr};
#endif

};  // namespace nintendough::utils

#endif
