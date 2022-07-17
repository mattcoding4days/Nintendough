#include <cstdlib>
#include <iostream>
#include <nintendough/log/module.hpp>
#include <nintendough/utils/module.hpp>
#include <nintendough/version.hpp>

using namespace nintendough;

auto main() -> int {
  try {
    log::Logger::instance().init();
    log::info("Nintendough version: {}", get_version());
    log::info("Test data dir: {}", utils::SystemDefault::config_dir().string());
  } catch (log::LoggerInitFailure const &e) {
    std::cerr << e.formatted_info() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
