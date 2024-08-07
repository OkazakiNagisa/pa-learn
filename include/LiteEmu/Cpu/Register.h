#pragma once
#include <array>
#include <string>
#include <string_view>
#include <LiteEmu/common.h>

namespace LiteEmu
{
class Cpu
{
public:
    class Register
    {
    public:
        static const std::string RegNames[32];

        word_t GetPc();
        void SetPc(word_t pc);
        word_t GetReg(int reg);
        word_t GetReg(std::string_view regName);
        void SetReg(int reg, word_t data);
        int RegNameToIndex(std::string_view regName);

    private:
        std::array<word_t, 32> Registers;
        word_t Pc;
    };
};
} // namespace LiteEmu