#pragma once

namespace Yumi
{
    class Asset
    {
    public:
        virtual ~Asset() = 0;

        virtual bool Load() = 0;
        virtual void Initialize() = 0;
        virtual bool Unload() = 0;

        virtual String GetTypeName() const = 0;
        virtual String GetName() const = 0;
        virtual String GetPath() const = 0;
        virtual String GetAbsolutePath() const = 0;
        virtual Id GetId() const = 0;
    };
}