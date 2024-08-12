#include <LiteEmu/Memory.h>
#include <cassert>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using namespace Def;

WordType Memory::Read(PhyAddrType addr, int len) {}

void Memory::Write(PhyAddrType addr, WordType data, int len) {}

constexpr bool Memory::IsValidAddress(PhyAddrType addr)
{
    return addr >= MEMORY_BASE && addr - MEMORY_BASE < MEMORY_SIZE;
}

Ptr Memory::ToHostAddress(PhyAddrType addr)
{
    if (IsValidAddress(addr))
        return &PhysicalMemory[addr];
    else
    {
        SPDLOG_ERROR("guest memory out of range {}", addr);
        assert(false);
    }
}

} // namespace LiteEmu