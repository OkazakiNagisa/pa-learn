#pragma once
#include <array>
#include <LiteEmu/common.h>

namespace LiteEmu
{
class Memory
{
public:
    word_t Read(paddr_t addr, int len);
    void Write(paddr_t addr, word_t data, int len);
    constexpr bool IsValidAddress(paddr_t addr);
    constexpr ptr_t ToHostAddress(paddr_t addr);

private:
    std::array<uint8_t, MEMORY_SIZE> PhysicalMemory;
};
} // namespace LiteEmu