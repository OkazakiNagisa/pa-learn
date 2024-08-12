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
} // namespace LiteEmu