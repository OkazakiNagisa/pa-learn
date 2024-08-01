#pragma once

namespace Interfaces
{
namespace Virtual
{
class Tickable
{
public:
    virtual void PreTick() = 0;
    virtual void Tick() = 0;
    virtual void PostTick() = 0;
};
} // namespace Virtual

namespace Crtp
{
template <class T>
class Tickable
{
public:
    void PreTick();
    void Tick();
    void PostTick();
};
} // namespace Crtp
} // namespace Interfaces