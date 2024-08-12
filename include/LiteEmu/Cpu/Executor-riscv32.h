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
    class Instruction
    {
    public:
        enum class Type : int
        {
            N = 0,
            R,
            I,
            S,
            B,
            U,
            J,
        } Type = Type::N;

        Def::WordType Inst = 0, DestRegIdx = 0, Src1RegIdx = 0, Src2RedIdx = 0,
                      Imm = 0;
    } Inst;

    void FetchAndDecode(Register &registers, Memory &memory);
    void ExecDispatch(Register &registers, Memory &memory);
};
}; // namespace Cpu
} // namespace LiteEmu