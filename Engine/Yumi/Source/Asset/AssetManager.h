#pragma once

#include "Asset.h"
#include "AssetRef.h"

#include "Rendering/Texture2D.h"
#include "Rendering/Shader.h"

namespace Yumi
{
    class AssetManager : public Singleton<AssetManager>
    {
        YSINGLETON_FRIEND(AssetManager)
    public:
        inline static constexpr char* emptyPathString = "Pathless";

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

            AssetData assetData;
            assetData.AssetId = assetId;
            assetData.Name = name;
            assetData.Path = path.empty() ? emptyPathString : path;
            assetData.AbsolutePath = path.empty() ? emptyPathString : m_WorkingDirectory + "\\" + path;
            assetData.AssetType = "Unimplemented";
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

            AssetData assetData;
            assetData.AssetId = assetId;
            assetData.Name = name;
            assetData.Path = path.empty() ? emptyPathString : path;
            assetData.AbsolutePath = path.empty() ? emptyPathString : m_WorkingDirectory + "\\" + path;
            assetData.AssetType = "Unimplemented";
            texture->SetAssetData(assetData);
            AssetRef<Texture2D> assetRef(texture);

            return assetRef;
        }

    private:
        AssetManager(const String& workingDirectory, GraphicsAPI api);
        ~AssetManager();

        void ImportAndLoadAssets();
        void UnloadAssets();

        static void GetAssetDirectoryLocalPath(const String& filePath, String& localPath);

        const String m_WorkingDirectory;
        const String m_AssetDirectory;
        const GraphicsAPI m_GraphicsApi;
        
        Map<Id, SharedPtr<Asset>> m_IdAssetMap;
    };
}