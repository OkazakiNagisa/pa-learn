#include <LiteEmu/Memory.h>
#include <cassert>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using namespace Def;

WordType Memory::Read(PhyAddrType addr, int len)
{
    SPDLOG_TRACE("Memory read {} bytes at {}", len, addr);
    if (len != 1 && len != 2 && len != 4)
    {
        if (std::is_same_v<WordType, uint32_t> ||
            std::is_same_v<WordType, uint64_t> && len != 8)
        {
            LogErr("Invalid read length: {}", len);
            assert(false);
        }
    }

    WordType ret = 0;
    Ptr hostAddr = ToHostAddress(addr);
    for (int i = 0; i < len; i++)
    {
        ret |= hostAddr[i] << (8 * i);
    }

    return ret;
}

void Memory::Write(PhyAddrType addr, WordType data, int len)
{
    SPDLOG_TRACE("Memory write {} bytes at {}, data {}", len, addr, data);
    if (len != 1 && len != 2 && len != 4)
    {
        if (std::is_same_v<WordType, uint32_t> ||
            std::is_same_v<WordType, uint64_t> && len != 8)
        {
            LogErr("Invalid write length: {}", len);
            assert(false);
        }
    }

    Ptr hostAddr = ToHostAddress(addr);
    for (int i = 0; i < len; i++)
    {
        hostAddr[i] = (data & (0b1111'1111 << 8 * i)) >> (8 * i);
    }
}

constexpr bool Memory::IsValidAddress(PhyAddrType addr)
{
    return addr >= MEMORY_BASE && addr - MEMORY_BASE < MEMORY_SIZE;
}

Ptr Memory::ToHostAddress(PhyAddrType addr)
{
    if (!IsValidAddress(addr))
    {
        LogErr("Guest memory out of range {:x}", addr);
        assert(false);
    }
    return &PhysicalMemory[addr];
}

PhyAddrType Memory::ToGuestAddress(Ptr addr)
{
    PhyAddrType guestAddr = addr - MEMORY_BASE;
    if (!IsValidAddress(guestAddr))
    {
        LogErr("Host memory out of guest range {:x}", (size_t)addr);
        assert(false);
    }
    return guestAddr;
}

} // namespace LiteEmu