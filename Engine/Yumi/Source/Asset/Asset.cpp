#include "Asset.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(AssetData);
    YFORCE_LINK_IMPL(Asset);

    Type Asset::GetAssetTypeFromExtension(const String& extension)
    {
        YCHECK(s_ExtensionAssetTypeMap.count(extension), "Extension not registered!");
        Type assetClass = Type::get_by_name(s_ExtensionAssetTypeMap[extension]);
        return assetClass;
    }

    ExtensionData::ExtensionData(const String& assetType, const String& extension)
    {
        Type assetClass = Type::get_by_name(assetType);
        YCHECK(assetClass.is_valid() && assetClass.is_derived_from(Type::get<Asset>()), "Type should be derived from asset!");
        Asset::s_ExtensionAssetTypeMap[extension] = assetType;
    }

}

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<AssetData>("AssetData")
        .constructor<>()
        .property("Name", &AssetData::Name)
        .property("Path", &AssetData::Path)
        .property("AssetId", &AssetData::AssetId)
        .property("AssetType", &AssetData::AssetType);

    rttr::registration::class_<Asset>("Asset")
        .constructor<>()
        .property("AssetData", &Asset::m_AssetData);
}