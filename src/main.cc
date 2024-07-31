#include <spdlog/spdlog.h>
#include "Glx/TickEngine.hpp"

int main(int argc, char *argv[])
{
    auto &engine = Glx::TickEngine::GetInstance();
    engine.DoMainLoop();
    return 0;
}