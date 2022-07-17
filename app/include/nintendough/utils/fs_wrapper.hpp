#ifndef NINTENDOUGH_UTILS_FS_WRAPPER_HPP
#define NINTENDOUGH_UTILS_FS_WRAPPER_HPP

/**
 * \file nintendough/utils/fs_wrapper.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief Performs contrained directory creation and file loading/serialization
 */

#include <nintendough/common.hpp>

namespace nintendough::utils {
/**
 * \brief A Wrapper around std::filesystem
 *
 * \details Performs safe filesystem operations, uses std::error_code
 *  and custom exceptions to report errors accurately
 * */
class FileSystem {
 public:
  /**
   * /brief Wrapper around std::filesystem::create_directories
   *
   * /throws utils::FileSytemOperationError
   * */
  static auto create_directory(std::filesystem::path const& path) -> void;

  /**
   * /brief Attempts to open the path as an infile stream, serializes said
   *  file to a string and returns it, if the file is not found on disk,
   *  an appropriate error will be thrown
   *
   * \param file: absolute path to a config file to load
   *
   * \returns the serialized file contents
   *
   * \throws utils::FileSystemOperationError if the file was not found,
   *  or if ifstream fail bit was set when opening the file
   * */
  [[nodiscard]] static auto load_config(std::filesystem::path const& file)
      -> std::string;
};
};  // namespace nintendough::utils

#endif
