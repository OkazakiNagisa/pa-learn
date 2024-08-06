#pragma once

class Singleton
{
public:
    template <class T, class... ArgsType>
    static T &Get(ArgsType &&...args)
    {
        static auto singleton = T();
        return singleton;
    }

    Singleton() = delete;
};