#pragma once
#include <array>
#include <LiteEmu/common.h>

namespace LiteEmu
{
class Memory
{
public:
    Guest::WordType Read(Guest::PhyAddrType addr, int len);
    void Write(Guest::PhyAddrType addr, Guest::WordType data, int len);
    constexpr bool IsValidAddress(Guest::PhyAddrType addr);
    ptr_t ToHostAddress(Guest::PhyAddrType addr);

private:
    std::array<uint8_t, Guest::MEMORY_SIZE> PhysicalMemory;
};
} // namespace LiteEmu