#include <nintendough/cpu/6502.hpp>

namespace nintendough::cpu {
Cpu6502::Cpu6502(std::unique_ptr<Bus> &&bus) : m_bus(std::move(bus)) {}

auto Cpu6502::reset() noexcept -> void {}

auto Cpu6502::irq() noexcept -> void {}

auto Cpu6502::nmi() noexcept -> void {}

auto Cpu6502::clock() noexcept -> void {}

auto Cpu6502::get_flag_(StatusRegisterFlags flag) noexcept -> u8 {}

auto Cpu6502::set_flag_(StatusRegisterFlags flag, bool additional) noexcept
    -> void {}

auto Cpu6502::read_(u16 data) noexcept -> u8 {}

auto Cpu6502::write_(u16 data, u16 data2) noexcept -> void {}
};  // namespace nintendough::cpu
