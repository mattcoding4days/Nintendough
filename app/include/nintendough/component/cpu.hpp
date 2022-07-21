#ifndef NINTENDOUGH_COMPONENT_CPU_HPP
#define NINTENDOUGH_COMPONENT_CPU_HPP

#include <nintendough/common.hpp>
#include <nintendough/component/bus.hpp>
#include <nintendough/component/instruction.hpp>
#include <nintendough/types.hpp>

namespace nintendough::component {

/**
 * \brief 6502 emulation class
 *
 * \details This is an emulation of the popular 8 bit Mos technology
 *  micro processor which was invented in 1975. The Nintentdo
 *  used this chip with some variations that they added, most notably
 *  the Audio unit. This variation is known as the 6502/2A03.
 *  In a nutshell, the 6502 is a little-endian 8-bit processor with a 16-bit
 *  address bus.
 * */
class Cpu6502 {
 public:
  /**
   * /brief Since there are many versions of the 6502,
   *  which can have different bus implementations,
   *  we will rely on depency injection, so any arbitrary
   *  bus can be passed in.
   * */
  explicit Cpu6502(std::unique_ptr<Bus> &&bus);
  virtual ~Cpu6502() = default;
  Cpu6502(Cpu6502 const &) = delete;
  Cpu6502 &operator=(Cpu6502 const &) = delete;
  Cpu6502(Cpu6502 &&) = default;
  Cpu6502 &operator=(Cpu6502 &&) = default;

  /**
   * \brief Cpu registers, we will leave these public
   *  for now, for testing purposes.
   *
   *  TODO: wrap all regiserts in an std::variant<Registers, u8> Regiser;
   * */

  //! A general purpose 8-bit register that stores
  //! the results of most arithmetic and logic operations,
  //! and in addition usually contains one of the two data
  //! words used in these operations
  u8 accumulator_register{0x00};

  //! There are two 8-bit registers (x and y), which may be used
  //! to count program steps or to provide and index value
  //! to be used in generating an effective address.
  //!
  //! When executing an instruction which specifies indexed
  //! addressing, the CPU fetches the op code and the base address,
  //! and modifies the address by adding the index register to
  //! it prior to performing the desired operation. Pre or post
  //! indexing of indirect addresses is possible.
  u8 x_register{0x00};
  u8 y_register{0x00};

  //! The stack pointer is an 8-bit register used to control
  //! the addressing of the variable-length on page one. The
  //! stack pointer is automatically incremented and decremented
  //! under control of the micro-processor to perform stack
  //! manipulations under direction of either the program
  //! or interupts (NMI and IRQ). The stack allows simple
  //! implementation of nested subroutines and multiple level
  //! interrupts. The stack pointer should be initialized before
  //! any interrupts or stack operations occur.
  u8 stack_pointer{0x00};

  //! The 16-bit program counter provides the addresses which
  //! step the microprocessor through sequential instructions
  //! in a program.
  //!
  //! Each the the microprocessor fetches an instruction from
  //! program memory, the lower byte of the program counter (PCL)
  //! is placed on the low-order bits of the address bus and
  //! the high-order 8 bits. The counter is incremented each
  //! time an instruction or data is fetched from program memory.
  u16 program_counter{0x0000};

  //! The 8-bit processor status register contains seven status
  //! flags. Some of the flags are controlled by the program, others
  //! may be controlled both by the program and the CPU.
  u8 statis_register{0x00};

  /**
   * \brief Event function, reset interrupt forces the CPU
   *  into an unknown state.
   * */
  auto reset() noexcept -> void;

  /**
   * \brief Interrupt Request
   *
   * \details Executes an instruction at a specific location
   * */
  auto irq() noexcept -> void;

  /**
   * \brief Non maskable interrupt request
   *
   * \details Executes an instruction at a specific location,
   *  but cannot be disabled
   * */
  auto nmi() noexcept -> void;

  /**
   * \brief Execute code which is = 1 clock cycle
   * */
  auto clock() noexcept -> void;

  /**
   * \brief since the status register stores 8 individual
   *  flags, we can enumurate them for nice access and manipulation.
   *  Each bit can have a different meaning depending on the type
   *  of instruction being executed
   *
   *  TODO: Should be moved into a Register class
   *  that encapsulates all this functionality
   *
   * \details
   *  C = Carry bit
   *  Z = Zero
   *  I = Disable Interrupts
   *  D = Decimal mode (Nes does not use this)
   *  B = Break
   *  U = Unused
   *  V = Overflow
   *  N = Negative
   * */
  enum class StatusRegisterFlags : u8 {
    C = (StatusRegisterMask << static_cast<u8>(0)),
    Z = (StatusRegisterMask << static_cast<u8>(1)),
    I = (StatusRegisterMask << static_cast<u8>(2)),
    D = (StatusRegisterMask << static_cast<u8>(3)),
    B = (StatusRegisterMask << static_cast<u8>(4)),
    U = (StatusRegisterMask << static_cast<u8>(5)),
    V = (StatusRegisterMask << static_cast<u8>(6)),
    N = (StatusRegisterMask << static_cast<u8>(7)),
  };

 private:
  using BusConn = std::unique_ptr<Bus>;
  using InstructionSet = std::vector<Instruction>;

  /**
   * \brief Getter/Setter functions to access the status register
   * */

  [[nodiscard]] auto get_flag_(StatusRegisterFlags flag) noexcept -> u8;
  auto set_flag_(StatusRegisterFlags flag, bool additional) noexcept -> void;

  /**
   * \brief Assistive variables to facilitate emulation
   *
   * \details
   * fetched      = Represents the working input value to the ALU
   * opcode       = The instruction byte
   * cycles       = Counts how many cycles the instruction has remaining
   * temp         = A convenience variable used everywhere
   * addr_abs     = All used memory addresses end up in here
   * addr_rel     = Represents absolute address following a branch
   * clock_count  = A global accumulation of the number of clocks
   * */
  u8 m_fetched{0x00};
  u8 m_opcode{0x00};
  u8 m_cycles{0};
  u16 m_temp{0x0000};
  u16 m_addr_abs{0x000};
  u16 m_addr_rel{0x0000};
  u32 m_clock_count{0};

  /**
   * \brief connection to the bus
   * */
  BusConn m_bus{};

  /**
   * \brief read data from the bus
   * */
  [[nodiscard]] auto read_(u16 data) noexcept -> u8;

  /**
   * \brief write data to the bus
   * */
  auto write_(u16 data, u16 data2) noexcept -> void;

  /**
   * \brief fetch data from two sources
   *
   * \details the location of data can come from two different sources,
   *  a memory address, or its immediately available as part of the instruction.
   *  This function decides depdending on the addressing mode of the instruction
   *
   *  \returns the data from an instruction itself or memory
   * */
  [[nodiscard]] auto fetch_() noexcept -> u8;

  /**
   * \brief intruction look
   * */
  InstructionSet m_lookup{};

  /**
   * \brief Addressing modes
   * */
  auto imp_() noexcept -> u8;
  auto imm_() noexcept -> u8;
  auto zp0_() noexcept -> u8;
  auto zpx_() noexcept -> u8;
  auto zpy_() noexcept -> u8;
  auto rel_() noexcept -> u8;
  auto abs_() noexcept -> u8;
  auto abx_() noexcept -> u8;
  auto aby_() noexcept -> u8;
  auto ind_() noexcept -> u8;
  auto izx_() noexcept -> u8;
  auto izy_() noexcept -> u8;

  /**
   * \brief Opcodes
   * */
  auto adc_() noexcept -> u8;
  auto and_() noexcept -> u8;
  auto asl_() noexcept -> u8;
  auto bcc_() noexcept -> u8;
  auto bcs_() noexcept -> u8;
  auto beq_() noexcept -> u8;
  auto bit_() noexcept -> u8;
  auto bmi_() noexcept -> u8;
  auto bne_() noexcept -> u8;
  auto bpl_() noexcept -> u8;
  auto brk_() noexcept -> u8;
  auto bvc_() noexcept -> u8;
  auto bvs_() noexcept -> u8;
  auto clc_() noexcept -> u8;
  auto cld_() noexcept -> u8;
  auto cli_() noexcept -> u8;
  auto clv_() noexcept -> u8;
  auto cmp_() noexcept -> u8;
  auto cpx_() noexcept -> u8;
  auto cpy_() noexcept -> u8;
  auto dec_() noexcept -> u8;
  auto dex_() noexcept -> u8;
  auto dey_() noexcept -> u8;
  auto eor_() noexcept -> u8;
  auto inc_() noexcept -> u8;
  auto inx_() noexcept -> u8;
  auto iny_() noexcept -> u8;
  auto jmp_() noexcept -> u8;
  auto jsr_() noexcept -> u8;
  auto lda_() noexcept -> u8;
  auto ldx_() noexcept -> u8;
  auto ldy_() noexcept -> u8;
  auto lsr_() noexcept -> u8;
  auto nop_() noexcept -> u8;
  auto ora_() noexcept -> u8;
  auto pha_() noexcept -> u8;
  auto php_() noexcept -> u8;
  auto pla_() noexcept -> u8;
  auto plp_() noexcept -> u8;
  auto rol_() noexcept -> u8;
  auto ror_() noexcept -> u8;
  auto rti_() noexcept -> u8;
  auto rts_() noexcept -> u8;
  auto sbc_() noexcept -> u8;
  auto sec_() noexcept -> u8;
  auto sed_() noexcept -> u8;
  auto sei_() noexcept -> u8;
  auto sta_() noexcept -> u8;
  auto stx_() noexcept -> u8;
  auto sty_() noexcept -> u8;
  auto tax_() noexcept -> u8;
  auto tay_() noexcept -> u8;
  auto tsx_() noexcept -> u8;
  auto txa_() noexcept -> u8;
  auto txs_() noexcept -> u8;
  auto tya_() noexcept -> u8;
  auto xxx_() noexcept -> u8;
};

};  // namespace nintendough::component

#endif
