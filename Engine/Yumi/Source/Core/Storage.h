#pragma once
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

namespace Yumi
{
    template<typename T, size_t N>
    using Array = std::array<T, N>;

    template<typename T>
    using DynamicArray = std::vector<T>;

    template<typename K, typename V>
    using OrderedMap = std::map<K, V>;

    template<typename K, typename V>
    using Map = std::unordered_map<K, V>;
}