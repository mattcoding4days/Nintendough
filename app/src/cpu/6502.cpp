#include <nintendough/cpu/6502.hpp>

namespace nintendough::cpu {
Cpu6502::Cpu6502(std::unique_ptr<Bus> &&bus) : mBus(std::move(bus)) {}
};  // namespace nintendough::cpu
