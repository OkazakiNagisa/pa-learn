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
    void Execute(Register &registers, Memory &memory);

private:
    enum class InstType : int
    {
        N = 0,
        R,
        I,
        S,
        B,
        U,
        J,
    };
    class Instruction
    {
    public:
        InstType Type = InstType::N;

        union
        {
            Def::WordType FullVal;
            struct
            {
                Def::WordType Opcode : 7;
                union
                {
                    struct
                    {
                        Def::WordType Rd     : 5;
                        Def::WordType Funct3 : 3;
                        Def::WordType Rs1    : 5;
                        Def::WordType Rs2    : 5;
                        Def::WordType Funct7 : 7;
                    } R;
                    struct
                    {
                        Def::WordType Rd     : 5;
                        Def::WordType Funct3 : 3;
                        Def::WordType Rs1    : 5;
                        Def::WordType Imm    : 12;
                        ;
                    } I;
                    struct
                    {
                        Def::WordType Imm0_4  : 5;
                        Def::WordType Funct3  : 3;
                        Def::WordType Rs1     : 5;
                        Def::WordType Rs2     : 5;
                        Def::WordType Imm5_11 : 7;
                    } S;
                    struct
                    {
                        Def::WordType Imm11__1_4  : 5;
                        Def::WordType Funct3      : 3;
                        Def::WordType Rs1         : 5;
                        Def::WordType Rs2         : 5;
                        Def::WordType Imm5_10__12 : 7;
                    } B;
                    struct
                    {
                        Def::WordType Rd       : 5;
                        Def::WordType Imm12_31 : 20;
                    } U;
                    struct
                    {
                        Def::WordType Rd                     : 5;
                        Def::WordType Imm12_19__11__1_10__20 : 20;
                    } J;
                };
            };
        } BitVal = {.FullVal = 0};
        static_assert(sizeof(BitVal) == 4, "");

        Def::WordType Imm;

        Def::WordType GetImmS_0_11();
        Def::WordType GetImmB_1_12();
        Def::WordType GetImmJ_1_20();
    } Inst;

    Def::WordType Fetch(Cpu::Register &registers, Memory &memory);
    void Decode(Def::WordType inst);
    void ExecDispatch(Register &registers, Memory &memory);

    bool PatternMatch(std::string_view pat, Def::WordType inst);
};
}; // namespace Cpu
} // namespace LiteEmu