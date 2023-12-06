#include "Asset.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(AssetData);
    YFORCE_LINK_IMPL(Asset);
}

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<AssetData>("AssetData")
        .constructor<>()
        .property("Name", &AssetData::Name)
        .property("Path", &AssetData::Path)
        .property("AbsolutePath", &AssetData::AbsolutePath)
        .property("AssetId", &AssetData::AssetId)
        .property("AssetType", &AssetData::AssetType);

    rttr::registration::class_<Asset>("Asset")
        .constructor<>()
        .property("AssetData", &Asset::m_AssetData);
}