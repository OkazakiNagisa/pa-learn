#pragma once
#include <array>
#include <LiteEmu/common.h>

namespace LiteEmu
{
class Memory
{
public:
    Def::WordType Read(Def::PhyAddrType addr, int len);
    void Write(Def::PhyAddrType addr, Def::WordType data, int len);
    constexpr bool IsValidAddress(Def::PhyAddrType addr);
    Ptr ToHostAddress(Def::PhyAddrType addr);

private:
    std::array<uint8_t, Def::MEMORY_SIZE> PhysicalMemory;
};
} // namespace LiteEmu