#pragma once
#include <array>
#include <string_view>
#include <LiteEmu/common.h>

namespace LiteEmu
{
namespace Cpu
{
class Register
{
public:
    static const std::array<std::string_view, 32> RegNames;
    enum class Regs : int
    {
        zero = 0,
        ra = 1,
        sp = 2,
        gp = 3,
        tp = 4,
        t0 = 5,
        t1 = 6,
        t2 = 7,
        s0 = 8,
        s1 = 9,
        a0 = 10,
        a1 = 11,
        a2 = 12,
        a3 = 13,
        a4 = 14,
        a5 = 15,
        a6 = 16,
        a7 = 17,
        s2 = 18,
        s3 = 19,
        s4 = 20,
        s5 = 21,
        s6 = 22,
        s7 = 23,
        s8 = 24,
        s9 = 25,
        s10 = 26,
        s11 = 27,
        t3 = 28,
        t4 = 29,
        t5 = 30,
        t6 = 31
    };

    Def::WordType GetPc();
    void SetPc(Def::WordType pc);
    Def::WordType GetReg(Regs reg);
    Def::WordType GetReg(std::string_view regName);
    void SetReg(Regs reg, Def::WordType data);
    void SetReg(std::string_view regName, Def::WordType data);
    Regs RegNameToEnum(std::string_view regName);
    int RegNameToIndex(std::string_view regName);

private:
    std::array<Def::WordType, 32> Registers = {0};
    Def::WordType Pc = 0;
};
}; // namespace Cpu
} // namespace LiteEmu