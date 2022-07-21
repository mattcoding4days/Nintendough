#ifndef NINTENDOUGH_TYPES_HPP
#define NINTENDOUGH_TYPES_HPP

#include <cstdint>

namespace nintendough {
/**
 * \brief bit masks and custom types
 * */
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;

constexpr auto StatusRegisterMask = static_cast<u8>(1);
};  // namespace nintendough

#endif
