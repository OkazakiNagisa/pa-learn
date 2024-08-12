#pragma once
#include <LiteEmu/common.h>
#include <LiteEmu/Memory.h>
#include <LiteEmu/Cpu/Register.h>

namespace LiteEmu
{
namespace Cpu
{
class Executor
{
public:
    void Execute(Def::WordType inst, Register &registers, Memory &memory);

private:
    enum class InstType
    {
        I,
        U,
        S,
        R,
        J,
        B,
        N
    } InstType;

    Def::WordType DestRegIdx = 0, Src1RegIdx = 0, Src2RedIdx = 0, Imm = 0;

    void FetchAndDecode();
    void ExecDispatch();
};
}; // namespace Cpu
} // namespace LiteEmu