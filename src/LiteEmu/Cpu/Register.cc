#include <LiteEmu/Cpu/Register.h>

namespace LiteEmu
{
using Guest::WordType;
WordType Cpu::Register::GetPc()
{
    return Pc;
}

void Cpu::Register::SetPc(WordType pc)
{
    Pc = pc;
}

WordType Cpu::Register::GetReg(int reg)
{
    return Registers[reg];
}

WordType Cpu::Register::GetReg(std::string_view regName)
{
    return GetReg(RegNameToIndex(regName));
}

void Cpu::Register::SetReg(int reg, WordType data)
{
    Registers[reg] = data;
}

int Cpu::Register::RegNameToIndex(std::string_view regName)
{
    return 0;
}
} // namespace LiteEmu