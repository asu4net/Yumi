#include "AssetManager.h"
#include "Rendering\Texture2D.h"
#include "Rendering\Shader.h"

namespace Yumi
{
    AssetManager::AssetManager(const String& workingDirectory)
        : m_WorkingDirectory(workingDirectory)
        , m_AssetDirectory(m_WorkingDirectory + "\\" + GetAssetsFolderName())
    {
        YLOG_TRACE("AssetManager created!\n");
    }

    AssetManager::~AssetManager()
    {
        UnloadAssets();
        YLOG_TRACE("AssetManager destroyed!\n");
    }

    WeakPtr<Asset> AssetManager::GetAssetById(Id id)
    {
        if (!m_IdAssetMap.count(id))
            return WeakPtr<Asset>();

        return m_IdAssetMap[id];
    }

    AssetRef AssetManager::GetAssetByName(const String& name)
    {
        if (!m_AssetNameIdMap.count(name))
            return {};

        const Id assetId = m_AssetNameIdMap[name];
        YCHECK(m_IdAssetMap.count(assetId), "Internal error");
        return AssetRef(assetId);
    }

    void AssetManager::ImportAndLoadAssets()
    {
        YLOG_TRACE("Loading assets...\n");
        for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(m_AssetDirectory))
        {
            const std::filesystem::path& dirPath = dirEntry.path();
            
            if (dirEntry.is_directory()) 
                continue;

            const String fileName = dirPath.filename().string();
            
            String localPath;
            GetAssetDirectoryLocalPath(dirPath.string(), localPath);

            if (dirPath.extension() == ".png" || dirPath.extension() == ".jpg")
            {
                TryLoadAsset(CreateAsset<Texture2D>({ fileName, localPath }));
            }
            else if (dirPath.extension() == ".glsl")
            {
                TryLoadAsset(CreateAsset<Shader>({ fileName, localPath }));
            }
        }
    }

    void AssetManager::UnloadAssets()
    {
        YLOG_TRACE("Unloading assets...\n");
        for (auto [id, asset] : m_IdAssetMap)
        {
            asset->Unload();
        }

        m_IdAssetMap.clear();
        m_AssetNameIdMap.clear();
        YLOG_TRACE("Assets unloaded!\n");
    }

    void AssetManager::EnsureAssetDataConsistency(AssetData& assetData)
    {
        YCHECK(!assetData.Name.empty(), "Asset must have a name!");
        YCHECK(!m_AssetNameIdMap.count(assetData.Name), "An asset with the same Name already exists!");
        YCHECK(!m_IdAssetMap.count(assetData.AssetId), "An asset with the same AssetId already exists!");

        if (assetData.Path.empty())
        {
            assetData.Path = AssetData::s_EmptyPathString;
            assetData.AbsolutePath = AssetData::s_EmptyPathString;
        }
        else
        {
            assetData.AbsolutePath = m_WorkingDirectory + "\\" + assetData.Path;
        }
    }

    AssetRef AssetManager::RegistryAsset(const SharedPtr<Asset>& asset, AssetData& assetData)
    {
        EnsureAssetDataConsistency(assetData);
        asset->SetAssetData(assetData);
        m_IdAssetMap[assetData.AssetId] = asset;
        m_AssetNameIdMap[assetData.Name] = assetData.AssetId;
        return AssetRef(assetData.AssetId);
    }

    void AssetManager::TryLoadAsset(AssetRef assetRef)
    {
        SharedPtr<Asset> asset = assetRef.GetPtr().lock();
        const AssetData assetData = asset->GetAssetData();
        const char* fileName = assetData.Name.c_str();

        if (asset->Load())
        {
            YLOG_TRACE("loaded: %s\n", fileName);
        }
        else
        {
            YLOG_WARN("Failed to load: %s", fileName);
            m_IdAssetMap.erase(assetData.AssetId);
        }
    }
}