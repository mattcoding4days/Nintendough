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
                            SourceLocation &&slc) noexcept;

  ~INintendoughAbstractError() override = default;
  INintendoughAbstractError(INintendoughAbstractError const &) = default;
  INintendoughAbstractError(INintendoughAbstractError &&) = default;
  INintendoughAbstractError &operator=(INintendoughAbstractError const &) =
      default;
  INintendoughAbstractError &operator=(INintendoughAbstractError &&) noexcept =
      default;

  [[nodiscard]] const char *what() const noexcept override;
  [[nodiscard]] virtual auto file() const noexcept -> std::string_view;
  [[nodiscard]] virtual auto func() const noexcept -> std::string_view;
  [[nodiscard]] virtual auto line() const noexcept -> std::uint32_t;
  [[nodiscard]] virtual auto formatted_info() const noexcept
      -> std::string_view;

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
  NintendoughError(std::string_view const &msg, SourceLocation &&slc) noexcept;
};

};  // namespace nintendough::error

#endif
