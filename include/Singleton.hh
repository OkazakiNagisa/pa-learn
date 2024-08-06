#pragma once

class Singleton
{
public:
    template <class T, class... ArgsType>
    static T &Get(ArgsType &&...args)
    {
        static auto singleton = T(args...);
        return singleton;
    }

    Singleton() = delete;
};