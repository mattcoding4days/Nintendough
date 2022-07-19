#include <nintendough/cpu/6502.hpp>

namespace nintendough::cpu {
Cpu6502::Cpu6502(std::unique_ptr<Bus> &&bus) : mBus(std::move(bus)) {}

auto Cpu6502::reset() noexcept -> void {}

auto Cpu6502::irq() noexcept -> void {}

auto Cpu6502::nmi() noexcept -> void {}

auto Cpu6502::clock() noexcept -> void {}

auto Cpu6502::complete() noexcept -> bool {}

};  // namespace nintendough::cpu
