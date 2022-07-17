#ifndef NINTENDOUGH_UTILS_ERROR_HPP
#define NINTENDOUGH_UTILS_ERROR_HPP

/**
 * \file nintendough/utils/error.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief custom errors for the utils module
 */

#include <nintendough/error/module.hpp>

namespace nintendough::utils {
class FileSystemOperationError : public error::INintendoughAbstractError {
 public:
  FileSystemOperationError(std::string_view const &msg,
                           error::SourceLocation &&slc);

  /**
   * \brief assert if the path in question exists
   *
   * \details can be used for directories or files
   * */
  static auto AssertFileExists(std::filesystem::path const &path,
                               error::SourceLocation &&slc) -> void;

  /**
   * \brief assert if the fail bit was set
   *
   * \details expects the value of std::ifstream.bad(), which checks if the
   *  operating system set the file fail bit. if the fail bit is set (true) the
   *  exception will be thrown. If this happens it is a vague unkown and is
   *  likely an operating system issue.
   * */
  static auto AssertFileStreamFailed(bool didfail, error::SourceLocation &&slc)
      -> void;
};
};  // namespace nintendough::utils

#endif
