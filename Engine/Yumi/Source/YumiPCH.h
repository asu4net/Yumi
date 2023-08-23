#pragma once

/// -------- STUFF ----------

#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <thread>
#include <utility>
#include <cmath>
#include <random>
#include <filesystem>

/// -------- MEMORY ---------

#include <memory>

namespace Yumi
{
    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Unique<T> CreateUnique(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Shared = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Shared<T> CreateShared(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Weak = std::weak_ptr<T>;
}

/// -------- STRING ---------

#include <string>

namespace Yumi { using String = std::string; }

#include <sstream>
#include <fstream>

/// -------- STORAGE ---------

#include <array>
namespace Yumi
{
    template<typename T, size_t N>
    using Array = std::array<T, N>;
}

#include <vector>
namespace Yumi
{
    template<typename T>
    using DynamicArray = std::vector<T>;
}

#include <map>
namespace Yumi
{
    template<typename K, typename V>
    using OrderedMap = std::map<K, V>;
}

#include <unordered_map>
namespace Yumi
{
    template<typename K, typename V>
    using Map = std::unordered_map<K, V>;
}

/// -------- LOGGING --------

//TODO: Add date/time at the log beginning
//TODO: Add final config without logs and stats
//TODO: Set logging levels

#define YLOG(...) \
    printf("Yumi Engine: "); \
    printf(__VA_ARGS__)

#define YLOG_TRACE(...) \
    printf("\x1B[96m"); \
    YLOG(__VA_ARGS__); \
    printf("\033[0m")

#define YLOG_WARN(...) \
    printf("\x1B[93m"); \
    YLOG(__VA_ARGS__); \
    printf("\033[0m")

#define YLOG_ERR(...) \
    printf("\x1B[91m"); \
    YLOG(__VA_ARGS__); \
    printf("\033[0m")

#define YCHECK(_CONDITION, ...) \
    if (!_CONDITION) { YLOG_ERR(__VA_ARGS__); __debugbreak(); }

/// -------- INTERNAL --------

#include "Core/Singleton.h"
#include "Core/Delegate/Delegate.h"
#include "Core/Delegate/MulticastDelegate.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

/// --------------------------