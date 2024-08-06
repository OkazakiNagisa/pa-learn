#include <Singleton.hh>
#include "Glx/TickEngine.hpp"

int main(int argc, char *argv[])
{
    class A
    {
    public:
        A() = default;
        A(int) {}
    };
    Singleton::Get<A>();
    Singleton::Get<A>(1);
    Glx::TickEngine::Run();
    return 0;
}