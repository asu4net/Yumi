#pragma once

namespace Yumi
{
    struct InformationComponent
    {
        String Name;
        Id ID;
        bool IsSerializable;

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

        RTTR_ENABLE_NO_VIRTUAL
    };

    YFORCE_LINK(InformationComponent)
}