#include <cstdlib>
#include <iostream>
#include <nintendough/log/module.hpp>
#include <nintendough/version.hpp>

using namespace nintendough;

auto main() -> int {
  try {
    log::Logger::instance().init();
    log::info("Nintedough version: {}", get_version());
  } catch (log::LoggerInitFailure const &e) {
    std::cerr << "Error: " << e.what() << "\nFile: " << e.file()
              << "\nFunc: " << e.func() << ":" << e.line() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
