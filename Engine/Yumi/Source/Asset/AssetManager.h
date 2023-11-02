#pragma once

#include "Asset.h"
#include "AssetRef.h"

#include "Rendering/Texture2D.h"
#include "Rendering/SubTexture2D.h"
#include "Rendering/Shader.h"

namespace Yumi
{
    class AssetManager : public Singleton<AssetManager>
    {
        YSINGLETON_FRIEND(AssetManager)
    public:
        inline static constexpr char* emptyPathString = "Pathless";

        template<typename T>
        AssetRef<T> GetAssetByName(const String& name)
        {
            if (!m_AssetNameIdMap.count(name))
                return AssetRef<T>();
            const Id assetId = m_AssetNameIdMap[name];
            YCHECK(m_IdAssetMap.count(assetId), "Turbo bug");
            AssetRef<T> assetRef = AssetRef<T>(std::dynamic_pointer_cast<T>(m_IdAssetMap[assetId]));
            YCHECK(assetRef.IsValid(), "Turbo bug");
            return assetRef;
        }

        template<typename T>
        AssetRef<T> CreateAsset(const String& name, const String& path, const Id assetId = Id())
        {
            YCHECK(false, "Invalid asset type");
            return AssetRef<T>();
        }

        template<>
        AssetRef<Shader> CreateAsset(const String& name, const String& path, const Id assetId)
        {
            YCHECK(!name.empty(), "Asset must have a name!");
            YCHECK(!m_IdAssetMap.count(assetId), "An asset with the same id already exists!");

            SharedPtr<Shader> shader = Shader::Create(m_GraphicsApi);
            m_IdAssetMap[assetId] = shader;
            m_AssetNameIdMap[name] = assetId;

            AssetData assetData;
            assetData.AssetId = assetId;
            assetData.Name = name;
            assetData.Path = path.empty() ? emptyPathString : path;
            assetData.AbsolutePath = path.empty() ? emptyPathString : m_WorkingDirectory + "\\" + path;
            assetData.AssetType = "Shader";
            shader->SetAssetData(assetData);
            AssetRef assetRef(shader);

            return assetRef;
        }

        template<>
        AssetRef<Texture2D> CreateAsset(const String& name, const String& path, const Id assetId)
        {
            YCHECK(!name.empty(), "Asset must have a name!");
            YCHECK(!m_IdAssetMap.count(assetId), "An asset with the same id already exists!");

            SharedPtr<Texture2D> texture = Texture2D::Create(m_GraphicsApi);
            m_IdAssetMap[assetId] = texture;
            m_AssetNameIdMap[name] = assetId;

            AssetData assetData;
            assetData.AssetId = assetId;
            assetData.Name = name;
            assetData.Path = path.empty() ? emptyPathString : path;
            assetData.AbsolutePath = path.empty() ? emptyPathString : m_WorkingDirectory + "\\" + path;
            assetData.AssetType = "Texture2D";
            texture->SetAssetData(assetData);
            AssetRef<Texture2D> assetRef(texture);

            return assetRef;
        }

        template<>
        AssetRef<SubTexture2D> CreateAsset(const String& name, const String& path, const Id assetId)
        {
            YCHECK(!name.empty(), "Asset must have a name!");
            YCHECK(!m_IdAssetMap.count(assetId), "An asset with the same id already exists!");

            SharedPtr<SubTexture2D> subTexture = CreateSharedPtr<SubTexture2D>();
            m_IdAssetMap[assetId] = subTexture;
            m_AssetNameIdMap[name] = assetId;

            AssetData assetData;
            assetData.AssetId = assetId;
            assetData.Name = name;
            assetData.Path = path.empty() ? emptyPathString : path;
            assetData.AbsolutePath = path.empty() ? emptyPathString : m_WorkingDirectory + "\\" + path;
            assetData.AssetType = "SubTexture2D";
            subTexture->SetAssetData(assetData);
            AssetRef<SubTexture2D> assetRef(subTexture);

            return assetRef;
        }

    private:
        AssetManager(const String& workingDirectory, GraphicsAPI api);
        ~AssetManager();

        void ImportAndLoadAssets();
        void UnloadAssets();

        template<typename T>
        void TryLoadAsset(AssetRef<T> assetRef)
        {
            const AssetData assetData = assetRef->GetAssetData();
            const char* fileName = assetData.Name.c_str();
            const char* assetType = assetData.AssetType.c_str();

            if (assetRef->Load())
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