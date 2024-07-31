#pragma once

namespace Interfaces
{
template <class T>
class Initializable
{
public:
    void Initialize();
    void Finalize();
};
} // namespace Interfaces