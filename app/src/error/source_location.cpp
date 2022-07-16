#include <nintendough/error/source_location.hpp>

namespace nintendough::error {
SourceLocation::SourceLocation(std::string_view const &file, std::uint32_t line,
                               std::string_view const &func) noexcept
    : mFile(file), mLine(line), mFunc(func) {}
};  // namespace nintendough::error
