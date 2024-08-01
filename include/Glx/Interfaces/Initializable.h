#pragma once
#include <concepts>

namespace Interfaces
{
namespace Virtual
{
class Initializable
{
public:
    virtual void Initialize() = 0;
    virtual void Finalize() = 0;

    const int InitOrder = -1;

protected:
    bool Initialized = false;
};
} // namespace Virtual

namespace Crtp
{
template <class T>
class Initializable
{
public:
    void Initialize();
    void Finalize();
};
} // namespace Crtp

namespace Concept
{
template <typename T>
concept Initializable = requires(T t) {
    { t.Initialize() } -> std::same_as<void>;
    { t.Finalize() } -> std::same_as<void>;
};
} // namespace Concept

} // namespace Interfaces