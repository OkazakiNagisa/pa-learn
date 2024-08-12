#include <LiteEmu/Memory.h>
#include <cassert>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using namespace Def;

WordType Memory::Read(PhyAddrType addr, int len)
{
    if (len != 1 && len != 2 && len != 4)
    {
        if (std::is_same_v<WordType, uint32_t> ||
            std::is_same_v<WordType, uint64_t> && len != 8)
        {
            spdlog::SPDLOG_ERROR("invalid read length: {}", len);
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
    if (len != 1 && len != 2 && len != 4)
    {
        if (std::is_same_v<WordType, uint32_t> ||
            std::is_same_v<WordType, uint64_t> && len != 8)
        {
            spdlog::SPDLOG_ERROR("invalid write length: {}", len);
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
        SPDLOG_ERROR("guest memory out of range {}", addr);
        assert(false);
    }
    return &PhysicalMemory[addr];
}

PhyAddrType Memory::ToGuestAddress(Ptr addr)
{
    PhyAddrType guestAddr = addr - MEMORY_BASE;
    if (!IsValidAddress(guestAddr))
    {
        SPDLOG_ERROR("host memory out of guest range {}", addr);
        assert(false);
    }
    return guestAddr;
}

} // namespace LiteEmu