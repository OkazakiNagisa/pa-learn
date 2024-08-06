#pragma once
#include <array>
#include <string>
#include <string_view>
#include <LiteEmu/common-riscv32.h>

namespace LiteEmu
{
class Cpu
{
public:
    class Register
    {
    public:
        static const std::string RegNames[32];

        word_t GetPc()
        {
            return Pc;
        }

        void SetPc(word_t pc)
        {
            Pc = pc;
        }

        word_t GetReg(int reg)
        {
            return Registers[reg];
        }

        word_t GetReg(std::string_view regName)
        {
            return GetReg(RegNameToIndex(regName));
        }

        void SetReg(int reg, word_t data)
        {
            Registers[reg] = data;
        }

        int RegNameToIndex(std::string_view regName)
        {
            return 0;
        }

    private:
        std::array<word_t, 32> Registers;
        word_t Pc;
    };
};
} // namespace LiteEmu