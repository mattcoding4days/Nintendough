#ifndef NINTENDOUGH_ERROR_BASE_ERROR_HPP
#define NINTENDOUGH_ERROR_BASE_ERROR_HPP

/**
 * \file nintendough/error/base_error.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief base error class for all other custom errors
 */

#include <nintendough/error/source_location.hpp>

namespace nintendough::error {
/**
 * \brief Base Error that should be inherited from
 */
class INintendoughAbstractError : public std::exception {
 public:
  INintendoughAbstractError(std::string_view const &msg,
                            SourceLocation &&slc) noexcept
      : mMsg(msg), mFile(slc.mFile), mFunc(slc.mFunc), mLine(slc.mLine) {
    mFormattedInfo.append("Error: ")
        .append(msg)
        .append("\nFunction: ")
        .append(mFunc)
        .append("\nFile: ")
        .append(mFile)
        .append(":")
        .append(std::to_string(mLine));
  }

  ~INintendoughAbstractError() override = default;
  INintendoughAbstractError(INintendoughAbstractError const &) = default;
  INintendoughAbstractError(INintendoughAbstractError &&) = default;
  INintendoughAbstractError &operator=(INintendoughAbstractError const &) =
      default;
  INintendoughAbstractError &operator=(INintendoughAbstractError &&) noexcept =
      default;

  [[nodiscard]] inline const char *what() const noexcept override {
    return mMsg.data();
  };

  [[nodiscard]] virtual inline auto file() const noexcept -> std::string_view {
    return mFile;
  };

  [[nodiscard]] virtual inline auto func() const noexcept -> std::string_view {
    return mFunc;
  };

  [[nodiscard]] virtual inline auto line() const noexcept -> std::uint32_t {
    return mLine;
  };

  [[nodiscard]] virtual inline auto formatted_info() const noexcept
      -> std::string_view {
    return mFormattedInfo;
  };

 protected:
  std::string mMsg{};
  std::string mFile{};
  std::string mFunc{};
  std::uint32_t mLine{};
  std::string mFormattedInfo{};
};

/**
 * \brief A basic error class
 */
class NintendoughError : public INintendoughAbstractError {
 public:
  NintendoughError(std::string_view const &msg, SourceLocation &&slc) noexcept
      : INintendoughAbstractError(msg, std::move(slc)) {}
};

};  // namespace nintendough::error

#endif
