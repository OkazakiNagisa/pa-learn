#include <LiteEmu/Cpu/Executor.h>
#include <spdlog/spdlog.h>

namespace LiteEmu
{
using Def::WordType;

void Cpu::Executor::Execute(Cpu::Register &registers,
                            Memory &memory)
{
    auto inst = Fetch(registers, memory);
    Decode(inst);
    ExecDispatch(registers, memory);
}

void Cpu::Executor::Decode(Def::WordType inst)
{
    Inst.FullInst = inst;
}

void Cpu::Executor::ExecDispatch(Register &registers, Memory &memory) {}

} // namespace LiteEmu