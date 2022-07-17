#include <nintendough/utils/system_defaults.hpp>

namespace nintendough::utils {
auto SystemDefault::config_dir() noexcept -> std::filesystem::path {
  if (SystemDefault::TestDataDir != nullptr) {
    return {SystemDefault::TestDataDir};
  } else if (const auto *xdg = std::getenv("XDG_CONFIG_HOME")) {
    return std::filesystem::path(xdg).append(SystemDefault::ProgName);
  } else {
    return SystemDefault::home_().append(".config").append(
        SystemDefault::ProgName);
  }
}

auto SystemDefault::cache_dir() noexcept -> std::filesystem::path {
  return SystemDefault::home_().append(".cache").append(
      SystemDefault::ProgName);
}

auto SystemDefault::logging_dir() noexcept -> std::filesystem::path {
  return SystemDefault::config_dir().append("log");
}

auto SystemDefault::get_config_file_path_for(ConfigFile type) noexcept
    -> std::filesystem::path {
  std::string cfile{};
  switch (type) {
    case ConfigFile::System: {
      cfile = SystemDefault::SysConfigFile;
    } break;
    case ConfigFile::Controller: {
      cfile = SystemDefault::ControllerConfigFile;
    } break;
  }
  return SystemDefault::config_dir().append(cfile);
}

auto SystemDefault::home_() noexcept -> std::filesystem::path {
  if (const auto *home = std::getenv("HOME")) {
    return {home};
  }
  return std::filesystem::current_path();
}
};  // namespace nintendough::utils
