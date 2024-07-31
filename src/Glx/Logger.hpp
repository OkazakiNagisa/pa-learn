#pragma once
#include <Glx/Interfaces/Singleton.h>
#include <Glx/Interfaces/Initializable.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Glx
{
class Logger : public Interfaces::Singleton<Logger>,
               public Interfaces::Initializable<Logger>
{
public:
    auto GetLogger()
    {
        return Logger;
    }

private:
    std::shared_ptr<spdlog::logger> Logger;

    void Initialize()
    {
        spdlog::set_pattern("[%H:%M:%S.%e %^%L%$] %v");
        spdlog::set_level(spdlog::level::info);

        Logger = spdlog::stdout_color_mt("Logger");
        Logger->set_pattern("[%H:%M:%S.%e %^%L%$] [%n] %v");
    }
    void Finalize() {}
};
} // namespace Glx