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

        union
        {
            Def::WordType FullInst = 0;
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
        } BitVal;

        class S
        {
        public:
            S(Instruction &thisInst) : ThisInst(thisInst) {}
            Def::WordType GetImm0_11()
            {
                auto imm0_4 = ThisInst.BitVal.S.Imm0_4;
                auto imm5_11_shifted = ThisInst.BitVal.S.Imm5_11 << 5;
                return imm0_4 & 0b11111 | imm5_11_shifted & 0b1111111'00000;
            }

        private:
            const Instruction &ThisInst;
        } S = *this;

        class B
        {
        public:
            B(Instruction &thisInst) : ThisInst(thisInst) {}
            Def::WordType GetImm1_12()
            {
                auto inst = ThisInst.BitVal.FullInst;
                Def::WordType imm1_4_shifted =
                    inst & 0b0000000'00000'00000'000'11110'0000000 >> 7;
                Def::WordType imm5_10_shifted =
                    inst & 0b0111111'00000'00000'000'00000'0000000 >> (25 - 5);
                Def::WordType imm11_shifted =
                    inst & 0b0000000'00000'00000'000'00001'0000000 << (11 - 7);
                Def::WordType imm12_shifted =
                    inst & 0b1000000'00000'00000'000'00000'0000000 >> (31 - 12);
                return imm1_4_shifted | imm5_10_shifted | imm11_shifted |
                       imm12_shifted;
            }

        private:
            const Instruction &ThisInst;
        } B = *this;

        class J
        {
        public:
            J(Instruction &thisInst) : ThisInst(thisInst) {}
            Def::WordType GetImm1_20()
            {
                auto inst = ThisInst.BitVal.FullInst;
                Def::WordType imm1_10_shifted =
                    inst & 0b0111111'11110'00000'000'00000'0000000 >> 7;
                Def::WordType imm11_shifted =
                    inst & 0b0000000'00001'00000'000'00000'0000000 >> (25 - 5);
                Def::WordType imm12_19_shifted =
                    inst & 0b0000000'00000'00000'000'00001'0000000 << (11 - 7);
                Def::WordType imm20_shifted =
                    inst & 0b1000000'00000'00000'000'00000'0000000 >> (31 - 12);
                return imm1_10_shifted | imm11_shifted | imm12_19_shifted |
                       imm20_shifted;
            }

        private:
            const Instruction &ThisInst;
        } J = *this;
    } Inst;

    Def::WordType Fetch(Cpu::Register &registers, Memory &memory);
    void Decode(Def::WordType inst);
    void ExecDispatch(Register &registers, Memory &memory);
};
}; // namespace Cpu
} // namespace LiteEmu