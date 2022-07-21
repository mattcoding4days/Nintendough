#ifndef NINTENDOUGH_COMPONENT_INSTRUCTION_HPP
#define NINTENDOUGH_COMPONENT_INSTRUCTION_HPP

#include <nintendough/types.hpp>

namespace nintendough::component {
/**
 * \brief A structure holding all relevent 6502 Instruction information
 *
 * \details Most Nes emulators use a abnormally large
 * switch and case statement structure to figure out which
 * instruction the cpu needs to execute, its pretty ugly.
 * Instead of that, a 16x16 table of instructions will be built
 * that can be indexed into with function pointers. The table
 * will be built to the specifications that the Rockwell R650x data sheet
 * outlines.
 *
 * Each table entry will hold the following:
 *    Mneumonic: The name or text representation of the opcode to be executed.
 *    Opcode Function: A function pointer to implementation of the opcode.
 *    Opcode Addressing Mode: A function pointer to the implementation of the
 *                            addressing mode.
 *    Clock Cycle Count: An integer that represents the base number of clock
 * cycles the CPU requires to execute the instruction. \size 56 bytes
 * */
struct Instruction {
  std::string mneumonic;
  u8 (*opcode)() = nullptr;
  u8 (*address_mode)() = nullptr;
  u8 cycle_count{};
};
};  // namespace nintendough::component

#endif
