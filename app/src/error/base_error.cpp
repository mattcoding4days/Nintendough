#include <nintendough/error/base_error.hpp>

namespace nintendough::error {
INintendoughAbstractError::INintendoughAbstractError(
    std::string_view const &msg, SourceLocation &&slc) noexcept
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

const char *INintendoughAbstractError::what() const noexcept {
  return mMsg.data();
}

auto INintendoughAbstractError::file() const noexcept -> std::string_view {
  return mFile;
}

auto INintendoughAbstractError::func() const noexcept -> std::string_view {
  return mFunc;
}

auto INintendoughAbstractError::line() const noexcept -> std::uint32_t {
  return mLine;
}

auto INintendoughAbstractError::formatted_info() const noexcept
    -> std::string_view {
  return mFormattedInfo;
}

NintendoughError::NintendoughError(std::string_view const &msg,
                                   SourceLocation &&slc) noexcept
    : INintendoughAbstractError(msg, std::move(slc)) {}

}  // namespace nintendough::error
