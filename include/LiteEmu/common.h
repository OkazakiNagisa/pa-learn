#pragma once
#include "common-riscv32.h"

namespace LiteEmu
{
union ptr_t
{
    size_t as_int;
    void *as_ptr;
};
using ptr_t = union ptr_t;

template <typename T, typename U>
class MultipleCastable
{
public:
    MultipleCastable() = default;
    MultipleCastable(T value) : Value(value) {}

    MultipleCastable(U value) : Value(reinterpret_cast<T>(value))
    {
    }

    operator T()
    {
        return Value;
    }

    operator U()
    {
        return reinterpret_cast<U>(Value);
    }

private:
    T Value = 0;
};

using Ptr = MultipleCastable<size_t, void *>;
} // namespace LiteEmu