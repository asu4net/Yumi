#pragma once

namespace Yumi
{
    class Asset
    {
    public:
        Asset() = default;
        Asset(const String& name, const String& path, const Id& id);
        virtual ~Asset() = default;

        virtual bool Load() { return false; }
        virtual void Initialize() {}
        virtual bool Unload() { return false; }

        const String& GetTypeName() const { return m_TypeName; }
        const String& GetName() const { return m_Name; }
        const String& GetPath() const { return m_Path; }
        const String& GetAbsolutePath() const { return m_AbsolutePath; }

        Id GetId() const { return m_Id; }

    private:
        String m_Name;
        String m_Path;
        String m_AbsolutePath;
        String m_TypeName;
        Id m_Id{ 0 };

        void SetTypeName(const String& typeName) { m_TypeName = typeName; }

        friend class AssetManager;
    };
}