#ifndef NINTENDOUGH_ERROR_HPP
#define NINTENDOUGH_ERROR_HPP

/**
 * \file nintendough/error.hpp
 * \author Matt Williams (matt.k.williams@protonmail.com)
 * \brief error module
 */

#include <nintendough/common.hpp>

namespace nintendough::error {
/**
 * \brief structure that holds run time location information
 */
struct SourceLocation {
  SourceLocation(std::string_view const &file, std::uint32_t line,
                 std::string_view const &func) noexcept
      : mFile(file), mLine(line), mFunc(func) {}

  const std::string mFile{};
  const std::uint32_t mLine{};
  const std::string mFunc{};
};

/**
 * \brief Wrapper macro which will gaurentee that the accurate file, function
 *  name, and line number will be reported
 */
#define RUNTIME_INFO                 \
  SourceLocation(__FILE__, __LINE__, \
                 static_cast<const char *>(__PRETTY_FUNCTION__))

/**
 * \brief Base Error that should be inherited from
 */
class INintendoughAbstractError : public std::exception {
 public:
  INintendoughAbstractError(std::string_view const &msg,
                            SourceLocation &&slc) noexcept
      : mMsg(msg), mFile(slc.mFile), mFunc(slc.mFunc), mLine(slc.mLine) {}

  ~INintendoughAbstractError() override = default;
  INintendoughAbstractError(INintendoughAbstractError const &) = default;
  INintendoughAbstractError(INintendoughAbstractError &&) = default;
  INintendoughAbstractError &operator=(INintendoughAbstractError const &) =
      default;
  INintendoughAbstractError &operator=(INintendoughAbstractError &&) noexcept =
      default;

  [[nodiscard]] const char *what() const noexcept override {
    return mMsg.data();
  };

  [[nodiscard]] virtual auto file() const noexcept -> std::string_view {
    return mFile;
  };

  [[nodiscard]] virtual auto func() const noexcept -> std::string_view {
    return mFunc;
  };

  [[nodiscard]] virtual auto line() const noexcept -> std::uint32_t {
    return mLine;
  };

 protected:
  std::string mMsg;
  std::string mFile;
  std::string mFunc;
  std::uint32_t mLine;
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
