#pragma once
#include <Glx/Interfaces/Singleton.h>
#include <Glx/Interfaces/Initializable.h>

namespace Glx {
class TickEngine : public Interfaces::Singleton<TickEngine>,
               public Interfaces::Initializable<TickEngine>
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

private:
    bool Initialized = false;
    bool ShouldQuit = false;

    void Initialize()
    {
        Initialized = true;
    }
    void Finalize() {}
};
}