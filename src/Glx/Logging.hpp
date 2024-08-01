#pragma once
#include <Glx/Interfaces/Initializable.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Glx
{
class Logging : public virtual Interfaces::Virtual::Initializable
{
public:
    auto GetLogger()
    {
        return Logger;
    }

    const int InitOrder = 0;

    void Initialize() override
    {
        if (Initialized)
            return;
        spdlog::set_pattern("[%H:%M:%S.%e %^%L%$] %v");
        spdlog::set_level(spdlog::level::info);

        Logger = spdlog::stdout_color_mt("Logger");
        Logger->set_pattern("[%H:%M:%S.%e %^%L%$] [%n] %v");
        Initialized = true;
    }
    void Finalize() override {}

private:
    std::shared_ptr<spdlog::logger> Logger;
};
static_assert(Interfaces::Concept::Initializable<class Logging>, "???");
} // namespace Glx