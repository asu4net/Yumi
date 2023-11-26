#pragma once

#include "Asset.h"
#include "AssetRef.h"
#include "Rendering/Texture2D.h"
#include "Rendering/SubTexture2D.h"
#include "Rendering/Shader.h"
#include "Rendering/Sprite.h"
#include "Scene/Scene.h"
#include "Animation/Animation.h"

namespace Yumi
{
    class AssetManager
    {
    public:
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

        template<typename... Args>
        AssetRef CreateShaderAsset(AssetData&& assetData, Args&&... args)
        {
            EnsureAssetDataConsistency(assetData);

            SharedPtr<Shader> shader = Shader::Create(GraphicsAPI::OpenGL, std::forward<Args>(args)...);
            shader->SetAssetData(assetData);
            
            m_IdAssetMap[assetData.AssetId] = shader;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;
 
            return AssetRef(assetData.AssetId);
        }

        template<typename T, typename... TArgs>
        AssetRef CreateAsset(AssetData&& assetData, TArgs&&... args)
        {
            EnsureAssetDataConsistency(assetData);
            SharedPtr<T> asset = CreateSharedPtr<T>(std::forward<TArgs>(args)...);
            asset->SetAssetData(assetData);
            m_IdAssetMap[assetData.AssetId] = asset;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;
            return AssetRef(assetData.AssetId);
        }

        template<typename T, typename... TArgs>
        AssetRef CreateAsset(const String& assetName, TArgs&&... args)
        {
            return CreateAsset<T>(AssetData{ assetName }, std::forward<TArgs>(args)...);
        }

    private:
        void UnloadAssets();
        void EnsureAssetDataConsistency(AssetData& assetData);

        void TryLoadAsset(AssetRef assetLink);

        static void GetAssetDirectoryLocalPath(const String& filePath, String& localPath);

        const String m_WorkingDirectory;
        const String m_AssetDirectory;
        
        Map<Id, SharedPtr<Asset>> m_IdAssetMap;
        Map<String, Id> m_AssetNameIdMap;
    };
}