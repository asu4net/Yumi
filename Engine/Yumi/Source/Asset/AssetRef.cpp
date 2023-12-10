#include "Asset/AssetRef.h"
#include "Asset/AssetManager.h"
#include "Core/Engine.h"

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<AssetRef>("AssetRef")
        .constructor<>()(rttr::policy::ctor::as_object)
        .constructor<Id>()
        .property("AssetId", &AssetRef::m_AssetId);
}

namespace Yumi
{
    AssetRef::AssetRef()
    {
        Retarget();
    }
    
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

    bool AssetRef::operator==(const AssetRef& other) const
    {
        return m_AssetId == other.m_AssetId;
    }

    bool AssetRef::operator!=(const AssetRef& other) const
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
        if (Engine::HasInstance() && id != 0)
            m_Asset = GetAssetManager().GetAssetById(id);
    }

    void AssetRef::Clear()
    {
        m_AssetId = 0;
        m_Asset.reset();
    }
}
