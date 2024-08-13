#include <LiteEmu/Cpu/Executor.h>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using Def::WordType;

void Cpu::Executor::Execute(Cpu::Register &registers, Memory &memory)
{
    auto inst = Fetch(registers, memory);
    Decode(inst);
    ExecDispatch(registers, memory);
}

void Cpu::Executor::Decode(Def::WordType inst)
{
    Inst.BitVal.FullInst = inst;
}

void Cpu::Executor::ExecDispatch(Register &registers, Memory &memory) {}

bool Cpu::Executor::PatternMatch(std::string_view pat, Def::WordType inst)
{
    for (int idx = 0; const auto c : pat)
    {
        if (idx >= 32)
        {
            SPDLOG_ERROR("Pattern {} overflowed", pat);
            assert(false);
        }

        switch (c)
        {
        case ' ':
            continue;
        case '?':
        {
            idx++;
            inst >>= 1;
            continue;
        }
        default:
        {
            SPDLOG_ERROR("Pattern {} error", pat);
            assert(false);
        }
        }
    }
    return true;
}

Def::WordType Cpu::Executor::Instruction::S::GetImm0_11()
{
    auto imm0_4 = ThisInst.BitVal.S.Imm0_4;
    auto imm5_11_shifted = ThisInst.BitVal.S.Imm5_11 << 5;
    return imm0_4 & 0b11111 | imm5_11_shifted & 0b1111111'00000;
}

Def::WordType Cpu::Executor::Instruction::B::GetImm1_12()
{
    auto inst = ThisInst.BitVal.FullInst;
    Def::WordType imm1_4_shifted =
        inst & 0b0000000'00000'00000'000'11110'0000000 >> 7;
    Def::WordType imm5_10_shifted =
        inst & 0b0111111'00000'00000'000'00000'0000000 >> (25 - 5);
    Def::WordType imm11_shifted = inst & 0b0000000'00000'00000'000'00001'0000000
                                             << (11 - 7);
    Def::WordType imm12_shifted =
        inst & 0b1000000'00000'00000'000'00000'0000000 >> (31 - 12);
    return imm1_4_shifted | imm5_10_shifted | imm11_shifted | imm12_shifted;
}

Def::WordType Cpu::Executor::Instruction::J::GetImm1_20()
{
    auto inst = ThisInst.BitVal.FullInst;
    Def::WordType imm1_10_shifted =
        inst & 0b0111111'11110'00000'000'00000'0000000 >> 20;
    Def::WordType imm11_shifted =
        inst & 0b0000000'00001'00000'000'00000'0000000 >> (20 - 11);
    Def::WordType imm12_19_shifted =
        inst & 0b0000000'00000'11111'111'00000'0000000;
    Def::WordType imm20_shifted =
        inst & 0b1000000'00000'00000'000'00000'0000000 >> (31 - 20);
    return imm1_10_shifted | imm11_shifted | imm12_19_shifted | imm20_shifted;
}

} // namespace LiteEmu