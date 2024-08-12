#pragma once
#include <stdint.h>
#include <array>
#include <type_traits>

namespace LiteEmu::Def
{
constexpr uint64_t MEMORY_SIZE = 0x80000000;
constexpr uint64_t MEMORY_BASE = 0x80000000;
constexpr uint64_t RESET_VECTOR = 0;

using word_t = uint32_t;
using WordType = word_t;
using paddr_t = std::conditional_t<MEMORY_SIZE + MEMORY_BASE <= 0x100000000ul,
                                   uint32_t, uint64_t>;
using PhyAddrType = paddr_t;

const std::array<word_t, 5> built_in_img = {
    0x00000297, // auipc t0,0
    0x00028823, // sb  zero,16(t0)
    0x0102c503, // lbu a0,16(t0)
    0x00100073, // ebreak (used as nemu_trap)
    0xdeadbeef, // some data
};
} // namespace LiteEmu