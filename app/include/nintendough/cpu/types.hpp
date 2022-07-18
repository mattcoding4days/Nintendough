#ifndef NINTENDOUGH_CPU_MODULE_HPP
#define NINTENDOUGH_CPU_MODULE_HPP

namespace nintendough::cpu {
/**
 * \brief bit masks and custom types
 * */
using u8 = std::uint8_t;
using u16 = std::uint16_t;

constexpr auto StatusRegisterMask = static_cast<u8>(1);
};  // namespace nintendough::cpu

#endif
