#include "AssetManager.h"

namespace Yumi
{
    static constexpr char* s_EmptyPathString = "NO_PATH";

    AssetRef AssetManager::CreateSpriteAsset(const String& textureAssetName)
    {
        return CreateSpriteAsset(AssetData{ textureAssetName + " [Sprite]" }, GetAssetByName(textureAssetName));
    }

    AssetManager::AssetManager(const String& workingDirectory, GraphicsAPI api)
        : m_WorkingDirectory(workingDirectory)
        , m_AssetDirectory(m_WorkingDirectory + "\\" + GetAssetsFolderName())
        , m_GraphicsApi(api)
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
        YCHECK(m_AssetNameIdMap.count(name), "Wrong asset name!");
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
                TryLoadAsset(CreateTextureAsset(AssetData{ fileName, localPath }));
            }
            else if (dirPath.extension() == ".glsl")
            {
                TryLoadAsset(CreateShaderAsset(AssetData{ fileName, localPath }));
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

    void AssetManager::EnsureAssetDataConsistency(AssetData& assetData, const String& assetType)
    {
        YCHECK(!assetData.Name.empty(), "Asset must have a name!");
        YCHECK(!m_AssetNameIdMap.count(assetData.Name), "An asset with the same Name already exists!");
        YCHECK(!m_IdAssetMap.count(assetData.AssetId), "An asset with the same AssetId already exists!");
        YCHECK(!assetType.empty(), "Asset must have a type")
        assetData.AssetType = assetType;

        if (assetData.Path.empty())
        {
            assetData.Path = s_EmptyPathString;
            assetData.AbsolutePath = s_EmptyPathString;
        }
        else
        {
            assetData.AbsolutePath = m_WorkingDirectory + "\\" + assetData.Path;
        }
    }

    void AssetManager::TryLoadAsset(AssetRef assetRef)
    {
        SharedPtr<Asset> asset = assetRef.GetPtr().lock();
        const AssetData assetData = asset->GetAssetData();
        const char* fileName = assetData.Name.c_str();
        const char* assetType = assetData.AssetType.c_str();

        if (asset->Load())
        {
            YLOG_TRACE("%s loaded: %s\n", assetType, fileName);
        }
        else
        {
            YLOG_WARN("Failed to load %s: %s", assetType, fileName);
            m_IdAssetMap.erase(assetData.AssetId);
        }
    }

    void AssetManager::GetAssetDirectoryLocalPath(const String& path, String& localPath)
    {
        DynamicArray<String> splitPath;
        String subString;
        std::stringstream ss(path);
        bool bProceed = false;
        while (std::getline(ss, subString, '\\'))
        {
            if (subString.find(GetAssetsFolderName()) != String::npos) 
                bProceed = true;
            if (bProceed) 
                splitPath.push_back("/" + subString);
        }
        for (int i = 0; i < splitPath.size(); i++)
            localPath += splitPath[i];
    }
}