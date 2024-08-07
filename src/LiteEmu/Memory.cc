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

ptr_t Memory::ToHostAddress(Guest::PhyAddrType addr)
{
    ptr_t ret;
    ret.as_ptr = &PhysicalMemory[addr];
    return ret;
}

} // namespace LiteEmu