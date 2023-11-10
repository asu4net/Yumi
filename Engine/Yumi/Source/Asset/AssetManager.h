#pragma once

#include "Asset.h"
#include "AssetLink.h"
#include "Rendering/Texture2D.h"
#include "Rendering/SubTexture2D.h"
#include "Rendering/Shader.h"
#include "Rendering/Sprite.h"
#include "Scene/Scene.h"

namespace Yumi
{
    class AssetManager : public Singleton<AssetManager>
    {
        YSINGLETON_FRIEND(AssetManager)
    public:

        // Temporal
        template<typename T>
        void GetAssetsOfType(DynamicArray<AssetLink<T>>& assets)
        {
            for (auto& [id, asset] : m_IdAssetMap)
            {
                SharedPtr<T> desiredAsset = std::dynamic_pointer_cast<T>(asset);
                if (!desiredAsset)
                    continue;
                assets.emplace_back(AssetLink(desiredAsset));
            }
        }

        template<typename T>
        AssetLink<T> GetAssetByName(const String& name)
        {
            if (!m_AssetNameIdMap.count(name))
                return AssetLink<T>();
            const Id assetId = m_AssetNameIdMap[name];
            YCHECK(m_IdAssetMap.count(assetId), "Turbo bug");
            AssetLink<T> assetLink = AssetLink<T>(std::dynamic_pointer_cast<T>(m_IdAssetMap[assetId]));
            YCHECK(assetLink.IsValid(), "Turbo bug");
            return assetLink;
        }

        template<typename... Args>
        AssetLink<Shader> CreateShaderAsset(AssetData& assetData, Args&&... args)
        {
            EnsureAssetDataConsistency(assetData);

            SharedPtr<Shader> shader = Shader::Create(m_GraphicsApi, std::forward<Args>(args)...);
            shader->SetAssetData(assetData);
            
            m_IdAssetMap[assetData.AssetId] = shader;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;
 
            return AssetLink(shader);
        }

        template<typename... Args>
        AssetLink<Texture2D> CreateTextureAsset(AssetData& assetData, Args&&... args)
        {
            EnsureAssetDataConsistency(assetData);

            SharedPtr<Texture2D> texture = Texture2D::Create(m_GraphicsApi, std::forward<Args>(args)...);
            texture->SetAssetData(assetData);

            m_IdAssetMap[assetData.AssetId] = texture;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;

            return AssetLink(texture);
        }

        template<typename... Args>
        AssetLink<SubTexture2D> CreateSubTextureAsset(AssetData& assetData, Args&&... args)
        {
            EnsureAssetDataConsistency(assetData);

            SharedPtr<SubTexture2D> subTexture = SubTexture2D::Create(std::forward<Args>(args)...);
            subTexture->SetAssetData(assetData);

            m_IdAssetMap[assetData.AssetId] = subTexture;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;

            return AssetLink(subTexture);
        }

        template<typename... Args>
        AssetLink<Sprite> CreateSpriteAsset(AssetData& assetData, Args&&... args)
        {
            EnsureAssetDataConsistency(assetData);

            SharedPtr<Sprite> sprite = CreateSharedPtr<Sprite>(std::forward<Args>(args)...);
            sprite->SetAssetData(assetData);

            m_IdAssetMap[assetData.AssetId] = sprite;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;

            return AssetLink(sprite);
        }

        template<typename... Args>
        AssetLink<Scene> CreateSceneAsset(AssetData& assetData, Args&&... args)
        {
            EnsureAssetDataConsistency(assetData);

            SharedPtr<Scene> scene = CreateSharedPtr<Scene>(std::forward<Args>(args)...);
            scene->SetAssetData(assetData);
            scene->SetScenePtr(scene);

            m_IdAssetMap[assetData.AssetId] = scene;
            m_AssetNameIdMap[assetData.Name] = assetData.AssetId;

            return AssetLink(scene);
        }

        AssetLink<Sprite> CreateSpriteFromTexture(const String& textureAssetName);
        AssetLink<Sprite> CreateSpriteFromSubTexture(const String& textureAssetName);

    private:
        AssetManager(const String& workingDirectory, GraphicsAPI api);
        ~AssetManager();

        void ImportAndLoadAssets();
        void UnloadAssets();
        void EnsureAssetDataConsistency(AssetData& assetData);

        template<typename T>
        void TryLoadAsset(AssetLink<T> assetLink)
        {
            const AssetData assetData = assetLink->GetAssetData();
            const char* fileName = assetData.Name.c_str();
            const char* assetType = assetData.AssetType.c_str();

            if (assetLink->Load())
            {
                YLOG_TRACE("%s loaded: %s\n", assetType, fileName);
            }
            else
            {
                YLOG_WARN("Failed to load %s: %s", assetType, fileName);
                m_IdAssetMap.erase(assetData.AssetId);
            }
        }

        static void GetAssetDirectoryLocalPath(const String& filePath, String& localPath);

        const String m_WorkingDirectory;
        const String m_AssetDirectory;
        const GraphicsAPI m_GraphicsApi;
        
        Map<Id, SharedPtr<Asset>> m_IdAssetMap;
        Map<String, Id> m_AssetNameIdMap;
    };
}