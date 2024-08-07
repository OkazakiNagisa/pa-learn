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

        Guest::WordType GetPc();
        void SetPc(Guest::WordType pc);
        Guest::WordType GetReg(int reg);
        Guest::WordType GetReg(std::string_view regName);
        void SetReg(int reg, Guest::WordType data);
        int RegNameToIndex(std::string_view regName);

    private:
        std::array<Guest::WordType, 32> Registers;
        Guest::WordType Pc;
    };
};
} // namespace LiteEmu