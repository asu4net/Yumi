#pragma once

namespace Yumi
{
    template <typename T>
    class AssetRef
    {
    public:
        AssetRef() = default;
        
        AssetRef(const AssetRef<T>& other) = default;
        
        AssetRef(const AssetRef<T>&& other)
            : m_Asset(std::move(other.m_Asset))
            , m_AssetData(other.m_AssetData)
        {}

        AssetRef<T>& operator = (const AssetRef<T>& other) = default;

        AssetRef<T>& operator = (const AssetRef<T>&& other)
        {
            m_Asset = std::move(other.m_Asset);
            m_AssetData = other.m_AssetData;
        }
        
        SharedPtr<T> operator -> () { return m_Asset.expired() ? nullptr : m_Asset.lock(); }

        ~AssetRef() { Clear(); }

        bool IsValid() const { return m_Asset.expired(); }

        AssetData GetAssetData() const { return m_AssetData; }

        void Clear()
        {
            m_AssetData = AssetData();
            m_Asset.reset();
        }
        
    private:
        AssetRef(const SharedPtr<T>& asset)
            : m_Asset(asset)
            , m_AssetData(asset ? asset->GetAssetData() : AssetData())
        {
            YCHECK(!m_Asset.expired(), "asset can not be nullptr")
        }

        AssetData m_AssetData;
        WeakPtr<T> m_Asset;

        friend class AssetManager;
    };
}