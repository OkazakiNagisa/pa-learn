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

class Ptr : public MultipleCastable<size_t, uint8_t *>
{
public:
    uint8_t &operator[](Ptr ptr)
    {
        return *ptr;
    }
};
} // namespace LiteEmu