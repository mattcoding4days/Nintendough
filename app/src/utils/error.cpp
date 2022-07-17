#include <nintendough/utils/error.hpp>

namespace nintendough::utils {
FileSystemOperationError::FileSystemOperationError(std::string_view const &msg,
                                                   error::SourceLocation &&slc)
    : error::INintendoughAbstractError(msg, std::move(slc)) {}

auto FileSystemOperationError::AssertFileExists(
    std::filesystem::path const &path, error::SourceLocation &&slc) -> void {
  if (!std::filesystem::exists(path)) {
    throw FileSystemOperationError("Config file not found", std::move(slc));
  }
}

auto FileSystemOperationError::AssertFileStreamFailed(
    bool didfail, error::SourceLocation &&slc) -> void {
  if (didfail) {
    throw FileSystemOperationError("ifstream fail bit was set", std::move(slc));
  }
}

};  // namespace nintendough::utils
