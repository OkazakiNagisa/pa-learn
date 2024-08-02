#pragma once

namespace Interfaces
{
namespace Crtp
{
template <class T>
class Singleton
{
public:
    static T &GetInstance()
    {
        static auto singleton = T();
        return singleton;
    }

protected:
    Singleton() = default;

private:
    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};
} // namespace Crtp
} // namespace Interfaces