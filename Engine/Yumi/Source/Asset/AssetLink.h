#pragma once
#include "Asset.h"

namespace Yumi
{
    template <typename T>
    class AssetLink
    {
    public:
        AssetLink() = default;
        
        AssetLink(const AssetLink<T>& other) = default;
        
        AssetLink(const AssetLink<T>&& other)
            : m_Asset(std::move(other.m_Asset))
            , m_AssetData(other.m_AssetData)
        {}

        AssetLink<T>& operator = (const AssetLink<T>& other) = default;

        AssetLink<T>& operator = (const AssetLink<T>&& other)
        {
            m_Asset = std::move(other.m_Asset);
            m_AssetData = other.m_AssetData;
            return *this;
        }

        bool operator == (const AssetLink<T>& other)
        {
            if (IsValid() && other.IsValid())
                return m_AssetData.AssetId == m_AssetData.AssetId;
            return false;
        }

        bool operator != (const AssetLink<T>& other)
        {
            return !(operator==(other));
        }
        
        SharedPtr<T> operator -> () { return Get(); }
        const SharedPtr<T> operator -> () const { return Get(); }
        
        SharedPtr<T> Get() const { return m_Asset.expired() ? nullptr : m_Asset.lock(); }

        ~AssetLink() { Clear(); }

        bool IsValid() const { return !m_Asset.expired(); }

        AssetData GetAssetData() const { return m_AssetData; }

        void Clear()
        {
            m_AssetData = AssetData();
            m_Asset.reset();
        }
        
    private:
        AssetLink(const SharedPtr<T>& asset)
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