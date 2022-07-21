#include <nintendough/component/cpu.hpp>

namespace nintendough::component {
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

auto Cpu6502::imp_() noexcept -> u8 {}
auto Cpu6502::imm_() noexcept -> u8 {}
auto Cpu6502::zp0_() noexcept -> u8 {}
auto Cpu6502::zpx_() noexcept -> u8 {}
auto Cpu6502::zpy_() noexcept -> u8 {}
auto Cpu6502::rel_() noexcept -> u8 {}
auto Cpu6502::abs_() noexcept -> u8 {}
auto Cpu6502::abx_() noexcept -> u8 {}
auto Cpu6502::aby_() noexcept -> u8 {}
auto Cpu6502::ind_() noexcept -> u8 {}
auto Cpu6502::izx_() noexcept -> u8 {}
auto Cpu6502::izy_() noexcept -> u8 {}

auto Cpu6502::adc_() noexcept -> u8 {}
auto Cpu6502::and_() noexcept -> u8 {}
auto Cpu6502::asl_() noexcept -> u8 {}
auto Cpu6502::bcc_() noexcept -> u8 {}
auto Cpu6502::bcs_() noexcept -> u8 {}
auto Cpu6502::beq_() noexcept -> u8 {}
auto Cpu6502::bit_() noexcept -> u8 {}
auto Cpu6502::bmi_() noexcept -> u8 {}
auto Cpu6502::bne_() noexcept -> u8 {}
auto Cpu6502::bpl_() noexcept -> u8 {}
auto Cpu6502::brk_() noexcept -> u8 {}
auto Cpu6502::bvc_() noexcept -> u8 {}
auto Cpu6502::bvs_() noexcept -> u8 {}
auto Cpu6502::clc_() noexcept -> u8 {}
auto Cpu6502::cld_() noexcept -> u8 {}
auto Cpu6502::cli_() noexcept -> u8 {}
auto Cpu6502::clv_() noexcept -> u8 {}
auto Cpu6502::cmp_() noexcept -> u8 {}
auto Cpu6502::cpx_() noexcept -> u8 {}
auto Cpu6502::cpy_() noexcept -> u8 {}
auto Cpu6502::dec_() noexcept -> u8 {}
auto Cpu6502::dex_() noexcept -> u8 {}
auto Cpu6502::dey_() noexcept -> u8 {}
auto Cpu6502::eor_() noexcept -> u8 {}
auto Cpu6502::inc_() noexcept -> u8 {}
auto Cpu6502::inx_() noexcept -> u8 {}
auto Cpu6502::iny_() noexcept -> u8 {}
auto Cpu6502::jmp_() noexcept -> u8 {}
auto Cpu6502::jsr_() noexcept -> u8 {}
auto Cpu6502::lda_() noexcept -> u8 {}
auto Cpu6502::ldx_() noexcept -> u8 {}
auto Cpu6502::ldy_() noexcept -> u8 {}
auto Cpu6502::lsr_() noexcept -> u8 {}
auto Cpu6502::nop_() noexcept -> u8 {}
auto Cpu6502::ora_() noexcept -> u8 {}
auto Cpu6502::pha_() noexcept -> u8 {}
auto Cpu6502::php_() noexcept -> u8 {}
auto Cpu6502::pla_() noexcept -> u8 {}
auto Cpu6502::plp_() noexcept -> u8 {}
auto Cpu6502::rol_() noexcept -> u8 {}
auto Cpu6502::ror_() noexcept -> u8 {}
auto Cpu6502::rti_() noexcept -> u8 {}
auto Cpu6502::rts_() noexcept -> u8 {}
auto Cpu6502::sbc_() noexcept -> u8 {}
auto Cpu6502::sec_() noexcept -> u8 {}
auto Cpu6502::sed_() noexcept -> u8 {}
auto Cpu6502::sei_() noexcept -> u8 {}
auto Cpu6502::sta_() noexcept -> u8 {}
auto Cpu6502::stx_() noexcept -> u8 {}
auto Cpu6502::sty_() noexcept -> u8 {}
auto Cpu6502::tax_() noexcept -> u8 {}
auto Cpu6502::tay_() noexcept -> u8 {}
auto Cpu6502::tsx_() noexcept -> u8 {}
auto Cpu6502::txa_() noexcept -> u8 {}
auto Cpu6502::txs_() noexcept -> u8 {}
auto Cpu6502::tya_() noexcept -> u8 {}
auto Cpu6502::xxx_() noexcept -> u8 {}
};  // namespace nintendough::component
