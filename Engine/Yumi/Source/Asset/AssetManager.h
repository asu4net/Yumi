#pragma once

#include "Asset.h"
#include "AssetRef.h"

namespace Yumi
{
    class AssetManager
    {
    public: 
        static void SerializeAsset(const SharedPtr<Asset>& asset);
        static SharedPtr<Asset> DeserializeAsset(const std::filesystem::path& assetPath);

        AssetManager(const String& workingDirectory);
        ~AssetManager();

        void ImportAndLoadAssets();

        // Temporal
        template<typename T>
        void GetAssetsOfType(DynamicArray<AssetRef>& assets)
        {
            for (auto& [id, asset] : m_IdAssetMap)
            {
                SharedPtr<T> desiredAsset = std::dynamic_pointer_cast<T>(asset);
                if (!desiredAsset)
                    continue;
                assets.emplace_back(AssetRef(desiredAsset->GetAssetData().AssetId));
            }
        }

        WeakPtr<Asset> GetAssetById(Id id);

        AssetRef GetAssetByName(const String& name);

        template<typename T, typename... TArgs>
        AssetRef CreateAsset(AssetData&& assetData, TArgs&&... args)
        {
            return RegistryAsset(CreateSharedPtr<T>(std::forward<TArgs>(args)...), assetData);
        }

        template<typename T, typename... TArgs>
        AssetRef CreateAsset(const String& assetName, TArgs&&... args)
        {
            return CreateAsset<T>(AssetData{ assetName }, std::forward<TArgs>(args)...);
        }

    private:
        void UnloadAssets();
        void EnsureAssetDataConsistency(AssetData& assetData);
        AssetRef RegistryAsset(const SharedPtr<Asset>& asset, AssetData& assetData);
        void TryLoadAsset(AssetRef assetLink);

        const String m_WorkingDirectory;
        const String m_AssetDirectory;
        
        Map<Id, SharedPtr<Asset>> m_IdAssetMap;
        Map<String, Id> m_AssetNameIdMap;
    };
}