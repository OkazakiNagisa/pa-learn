#pragma once
#include <cassert>
#include "common-riscv32.h"

#define LogErr SPDLOG_ERROR

namespace LiteEmu
{
union ptr_t
{
    size_t as_int;
    void *as_ptr;
};
using ptr_t = union ptr_t;

class Ptr
{
public:
    Ptr() = default;
    Ptr(size_t value) : Value(value) {}
    Ptr(uint8_t *value) : Value(reinterpret_cast<size_t>(value)) {}
    Ptr(void *value) : Value(reinterpret_cast<size_t>(value)) {}

    operator size_t &()
    {
        return Value;
    }

    operator uint8_t *&()
    {
        return reinterpret_cast<uint8_t *&>(Value);
    }

    operator void *&()
    {
        return reinterpret_cast<void *&>(Value);
    }

private:
    size_t Value = 0;
};

namespace Util
{
constexpr Def::WordType ExtractBits(Def::WordType data, int start, int end)
{
    assert(end > start && end <= 31 && start >= 0);
    return (data >> start) & ((1 << (end - start + 1)) - 1);
}

constexpr Def::WordType SignExtend(Def::WordType data, int size)
{
    if (!ExtractBits(data, size - 1, size - 1))
        return data;

    int wordBitSize = sizeof(Def::WordType) * 8;
    // for (int i = size; size < wordBitSize; i++) {
    //     data |= 1 << i;
    // }
    return data | ~((1ull << size) - 1);
}
} // namespace Util
} // namespace LiteEmu