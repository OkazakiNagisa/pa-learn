#pragma once

namespace LiteEmu
{
class Monitor
{
public:
    Memory &mem;
    ISA_Wrapper &isa;

    Monitor(const Monitor &) = delete;
    Monitor &operator=(const Monitor &) = delete;
    Monitor(Monitor &&) = delete;
    Monitor &operator=(Monitor &&) = delete;

    ~Monitor();

    static Monitor &getMonitor();
    void execute(uint64_t n);

    void invalid_inst_handler(word_t pc);
    void ebreak_handler(word_t pc);

    bool is_bad_status();

private:
    enum State
    {
        RUNNING,
        STOP,
        END,
        ABORT,
        QUIT
    } state;
    word_t halt_pc;
    word_t halt_ret;
    std::chrono::nanoseconds timer;
    uint64_t inst_count;

    Monitor();

    void statistics();
    void trap_handler(State s, word_t pc, word_t ret);
    void stop();
    void quit();

    friend class Debugger;
};
} // namespace LiteEmu