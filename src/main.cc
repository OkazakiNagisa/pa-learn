#include <Singleton.hh>
#include "Glx/TickEngine.hpp"

int main(int argc, char *argv[])
{
    Singleton::Get<Glx::TickEngine>().Run();
    return 0;
}