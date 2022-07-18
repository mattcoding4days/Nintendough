#ifndef NINTENDOUGH_CPU_6502_HPP
#define NINTENDOUGH_CPU_6502_HPP

#include <nintendough/common.hpp>
#include <nintendough/cpu/types.hpp>

namespace nintendough::cpu {
class Bus;

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
  //! time an instruction or data is fetched from program memory
  u16 program_counter{0x0000};

  // The 8-bit processor status register contains seven status
  // flags. Some of the flags are controlled by the program, others
  // may be controlled both by the program and the CPU.
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
   * \brief Instruction completion indicator
   *
   * \details This will be used for step-by-step
   *  debugging
   * */
  [[nodiscard]] auto complete() noexcept -> bool;

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
   *  I = Disable I
   *  D = Decimal mode (Nes does not use this)
   *  B = Break
   *  U = Unused
   *  V = Overflow
   *  N = Negative
   * */
  enum StatusRegisterFlgs {
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
  /**
   * \brief connection to the bus
   * */
  std::unique_ptr<Bus> mBus;
};

};  // namespace nintendough::cpu

#endif
