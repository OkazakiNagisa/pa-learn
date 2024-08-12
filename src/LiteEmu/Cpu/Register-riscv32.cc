#include <LiteEmu/Cpu/Register.h>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using Def::WordType;

const std::array<std::string_view, 32> Cpu::Register::RegNames = {
    "zero", "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
    "a1",   "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
    "s6",   "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

WordType Cpu::Register::GetPc()
{
    return Pc;
}

void Cpu::Register::SetPc(WordType pc)
{
    Pc = pc;
}

WordType Cpu::Register::GetReg(Regs reg)
{
    return Registers[static_cast<int>(reg)];
}

WordType Cpu::Register::GetReg(std::string_view regName)
{
    return GetReg(RegNameToEnum(regName));
}

void Cpu::Register::SetReg(Regs reg, WordType data)
{
    Registers[static_cast<int>(reg)] = data;
}

void Cpu::Register::SetReg(std::string_view regName, WordType data)
{
    Registers[RegNameToIndex(regName)] = data;
}

Cpu::Register::Regs Cpu::Register::RegNameToEnum(std::string_view regName)
{
    for (int i = 0, size = regName.size(); i < size; i++)
    {
        if (regName == RegNames[i])
            return static_cast<Regs>(i);
    }
    SPDLOG_ERROR("unknown regname {}", regName);
    assert(false);
}

int Cpu::Register::RegNameToIndex(std::string_view regName)
{
    for (int i = 0, size = regName.size(); i < size; i++)
    {
        if (regName == RegNames[i])
            return i;
    }
    SPDLOG_ERROR("unknown regname {}", regName);
    assert(false);
}
} // namespace LiteEmu