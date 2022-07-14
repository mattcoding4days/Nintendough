#include <iostream>
#include <nintendough/version.hpp>

int main() {
  std::cout << "Nintendough version: " << nintendough::get_version() << '\n';

  return 0;
}
