#pragma once
#include <Glx/Interfaces/Singleton.h>
#include <Glx/Interfaces/Initializable.h>

namespace Glx
{
class TickEngine : public Interfaces::Crtp::Singleton<TickEngine>
{
public:
    void DoMainLoop()
    {
        Initialize();
        while (ShouldQuit)
        {
            Tick();
        }
        Finalize();
    }
    void Tick() {}

    void Initialize()
    {
        Initialized = true;
    }
    void Finalize() {}

private:
    bool Initialized = false;
    bool ShouldQuit = false;
};
static_assert(Interfaces::Concept::Initializable<TickEngine>, "???");
} // namespace Glx