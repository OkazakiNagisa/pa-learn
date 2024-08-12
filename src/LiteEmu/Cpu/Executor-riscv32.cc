#include <LiteEmu/Cpu/Executor.h>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using Def::WordType;

void Cpu::Executor::Execute(Def::WordType inst, Cpu::Register &registers,
                            Memory &memory)
{
    Inst.Inst = inst;
    FetchAndDecode(registers, memory);
    ExecDispatch(registers, memory);
}

void Cpu::Executor::FetchAndDecode(Register &registers, Memory &memory)
{
    auto inst = Inst.Inst;

}

void Cpu::Executor::ExecDispatch(Register &registers, Memory &memory) {}

} // namespace LiteEmu