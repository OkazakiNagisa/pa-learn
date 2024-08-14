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
    Inst.BitVal.FullVal = inst;
}

void Cpu::Executor::ExecDispatch(Register &registers, Memory &memory)
{
    auto patternMatcher = [&, this](const std::string_view pat,
                                    const std::string_view opName,
                                    InstType type, auto func) {
        if (PatternMatch(pat, this->Inst.BitVal.FullVal))
        {
            switch (type)
            {
            case InstType::R:
                break;
            case InstType::I:
                Inst.Imm = Util::SignExtend(Inst.BitVal.I.Imm, 12);
                break;
            case InstType::S:
                Inst.Imm = Util::SignExtend(Inst.S.GetImm0_11(), 12);
                break;
            case InstType::B:

            case InstType::U:
            case InstType::J:
            default:
                LogErr("InstType not set");
                assert(false);
            }
            func();
        };
    };
    patternMatcher("??????? ????? ????? ??? ????? 01101 11", "lui", InstType::U,
                   [&]() {});
}

bool Cpu::Executor::PatternMatch(const std::string_view pat, Def::WordType inst)
{
    int idx = 0;
    for (auto it = pat.rbegin(); it != pat.rend(); it++)
    {
        auto c = *it;
        if (idx >= 32)
        {
            LogErr("Pattern {} overflowed", pat);
            assert(false);
        }

        switch (c)
        {
        case ' ':
            continue;
        case '1':
            if ((inst & 1) == 0)
                return false;
            inst >>= 1;
            idx++;
            continue;
        case '0':
            if ((inst & 1) == 1)
                return false;
            inst >>= 1;
            idx++;
            continue;
        case '?':
            inst >>= 1;
            idx++;
            continue;
        default:
            LogErr("Pattern {} error", pat);
            assert(false);
        }
    }
    return true;
}

Def::WordType Cpu::Executor::Instruction::GetImmS_0_11()
{
    auto imm0_4 = BitVal.S.Imm0_4;
    auto imm5_11_shifted = BitVal.S.Imm5_11 << 5;
    return imm0_4 & 0b11111 | imm5_11_shifted & 0b1111111'00000;
}

Def::WordType Cpu::Executor::Instruction::GetImmB_1_12()
{
    auto inst = BitVal.FullVal;
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

Def::WordType Cpu::Executor::Instruction::GetImmJ_1_20()
{
    auto inst = BitVal.FullVal;
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