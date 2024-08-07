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

class Ptr
{
public:
    Ptr() = default;
    Ptr(size_t value) : Value(value) {}
    Ptr(void *value) : Value(reinterpret_cast<size_t>(value)) {}

    operator size_t()
    {
        return Value;
    }

    operator void *()
    {
        return reinterpret_cast<void *>(Value);
    }

private:
    size_t Value = 0;
};

template <typename T>
class MultipleCaster
{
public:
    MultipleCaster() = default;
    MultipleCaster(T value) : Value(value) {}

    template <typename U>
    MultipleCaster(void *value) : Value(reinterpret_cast<size_t>(value))
    {
    }

    operator T()
    {
        return Value;
    }

    template <typename U>
    operator U()
    {
        return reinterpret_cast<U>(Value);
    }

private:
    T Value = 0;
};
} // namespace LiteEmu