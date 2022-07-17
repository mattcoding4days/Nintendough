#include <nintendough/utils/error.hpp>
#include <nintendough/utils/fs_wrapper.hpp>

namespace nintendough::utils {
auto FileSystem::FileSystem::create_directory(std::filesystem::path const& path)
    -> void {
  if (!std::filesystem::exists(path)) {
    std::error_code ecode;
    std::filesystem::create_directories(path, ecode);
    if (ecode) {
      throw FileSystemOperationError(ecode.message(), error::RUNTIME_INFO);
    }
  }
}

auto FileSystem::load_config(std::filesystem::path const& file) -> std::string {
  FileSystemOperationError::AssertFileExists(file, error::RUNTIME_INFO);
  std::ifstream infile_stream(file);
  FileSystemOperationError::AssertFileStreamFailed(infile_stream.bad(),
                                                   error::RUNTIME_INFO);
  std::string serialized_config((std::istreambuf_iterator<char>(infile_stream)),
                                std::istreambuf_iterator<char>());
  infile_stream.close();
  return serialized_config;
}
};  // namespace nintendough::utils
