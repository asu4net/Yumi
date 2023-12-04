#pragma once

namespace Yumi::Serialization
{
    bool FromJson(const std::string& json, const rttr::instance& object);
    std::string ToJson(const rttr::instance& object);
}