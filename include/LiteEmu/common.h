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
} // namespace LiteEmu