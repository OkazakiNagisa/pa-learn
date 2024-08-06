#pragma once
#include <type_traits>
#include "../src/LiteEmu/Cpu.hh"
#include "../src/LiteEmu/Devices.hh"
#include "../src/LiteEmu/Memory.hh"
#include "../src/LiteEmu/Monitor.hh"

class Singleton
{
public:
    // template <class T>
    // static T &Get()
    // {
    //     static_assert(std::is_same_v<T, LiteEmu::Cpu> ||
    //                       std::is_same_v<T, LiteEmu::Devices> ||
    //                       std::is_same_v<T, LiteEmu::Memory> ||
    //                       std::is_same_v<T, LiteEmu::Monitor>,
    //                   "");
    //     static auto singleton = T();
    //     return singleton;
    // }

    template <class T, class... ArgsType>
    static T &Get(ArgsType &&...args)
    {
        // static_assert(std::is_same_v<T, LiteEmu::Cpu> ||
        //                   std::is_same_v<T, LiteEmu::Devices> ||
        //                   std::is_same_v<T, LiteEmu::Memory> ||
        //                   std::is_same_v<T, LiteEmu::Monitor>,
        //               "");
        static auto singleton = T();
        return singleton;
    }

    Singleton() = delete;
};