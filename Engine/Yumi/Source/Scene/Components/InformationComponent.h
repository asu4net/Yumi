#pragma once

namespace Yumi
{
    struct InformationComponent
    {
        String Name;
        const Id ID;
        const bool IsSerializable;

        InformationComponent()
            : Name("Uninitialized")
            , ID(0)
            , IsSerializable(false)
        {}

        InformationComponent(const String& name, Id id, bool isSerializable)
            : Name(name)
            , ID(id)
            , IsSerializable(isSerializable)
        {}
    };
}