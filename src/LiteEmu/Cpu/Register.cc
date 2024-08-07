#include <LiteEmu/Cpu/Register.h>

namespace LiteEmu
{
word_t Cpu::Register::GetPc()
{
    return Pc;
}

void Cpu::Register::SetPc(word_t pc)
{
    Pc = pc;
}

word_t Cpu::Register::GetReg(int reg)
{
    return Registers[reg];
}

word_t Cpu::Register::GetReg(std::string_view regName)
{
    return GetReg(RegNameToIndex(regName));
}

void Cpu::Register::SetReg(int reg, word_t data)
{
    Registers[reg] = data;
}

int Cpu::Register::RegNameToIndex(std::string_view regName)
{
    return 0;
}
} // namespace LiteEmu