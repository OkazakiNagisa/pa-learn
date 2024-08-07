#include <LiteEmu/Memory.h>

namespace LiteEmu
{
using namespace Guest;

WordType Memory::Read(PhyAddrType addr, int len) {}

void Memory::Write(Guest::PhyAddrType addr, Guest::WordType data, int len) {}

constexpr bool Memory::IsValidAddress(Guest::PhyAddrType addr)
{
    return addr >= MEMORY_BASE && addr - MEMORY_BASE < MEMORY_SIZE;
}

Ptr Memory::ToHostAddress(Guest::PhyAddrType addr)
{
    return &PhysicalMemory[addr];
}

} // namespace LiteEmu