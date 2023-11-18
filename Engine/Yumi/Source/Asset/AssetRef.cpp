#include "AssetRef.h"
#include "AssetManager.h"

namespace Yumi
{
    AssetRef::AssetRef() = default;
    
    AssetRef::AssetRef(Id assetId)
    {
        Retarget(assetId);
    }

    AssetRef::AssetRef(const AssetRef& other) = default;
    
    AssetRef::AssetRef(AssetRef&& other) noexcept
        : m_Asset(std::move(other.m_Asset))
        , m_AssetId(other.m_AssetId)
    {}

    AssetRef::~AssetRef()
    {
        Clear();
    }

    AssetRef& AssetRef::operator=(const AssetRef& other) = default;

    AssetRef& AssetRef::operator=(AssetRef&& other) noexcept
    {
        m_Asset = std::move(other.m_Asset);
        m_AssetId = other.m_AssetId;
        return *this;
    }

    bool AssetRef::operator==(const AssetRef& other)
    {
        return m_AssetId == other.m_AssetId;
    }

    bool AssetRef::operator!=(const AssetRef& other)
    {
        return !(operator==(other));
    }

    void AssetRef::Retarget()
    {
        Retarget(m_AssetId);
    }

    void AssetRef::Retarget(Id id)
    {
        m_AssetId = id;
        m_Asset = GetAssetManager().GetAssetById(id);
    }

    void AssetRef::Clear()
    {
        m_AssetId = 0;
        m_Asset.reset();
    }
}
