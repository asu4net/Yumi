#include "AssetManager.h"
#include "AssetManager.h"

namespace Yumi
{
    static constexpr char* s_EmptyPathString = "NO_PATH";

    AssetManager::AssetManager(const String& workingDirectory, GraphicsAPI api)
        : m_WorkingDirectory(workingDirectory)
        , m_AssetDirectory(m_WorkingDirectory + "\\" + GetAssetsFolderName())
        , m_GraphicsApi(api)
    {
        YLOG_TRACE("AssetManager begin create...\n");
        ImportAndLoadAssets();
        YLOG_TRACE("AssetManager created!\n");
    }

    AssetManager::~AssetManager()
    {
        UnloadAssets();
        YLOG_TRACE("AssetManager destroyed!\n");
    }

    AssetLink<Sprite> AssetManager::CreateSpriteFromTexture(const String& textureAssetName)
    {
        const String spriteName = textureAssetName + "[Sprite]";
        return CreateSpriteAsset(AssetData{spriteName}, GetAssetByName<Texture2D>(textureAssetName));
    }

    AssetLink<Sprite> AssetManager::CreateSpriteFromSubTexture(const String& textureAssetName)
    {
        const String spriteName = textureAssetName + "[Sprite]";
        return CreateSpriteAsset(AssetData{spriteName}, GetAssetByName<SubTexture2D>(textureAssetName));
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

    void AssetManager::EnsureAssetDataConsistency(AssetData& assetData)
    {
        YCHECK(!assetData.Name.empty(), "Asset must have a name!");
        YCHECK(!m_AssetNameIdMap.count(assetData.Name), "An asset with the same Name already exists!");
        YCHECK(!m_IdAssetMap.count(assetData.AssetId), "An asset with the same AssetId already exists!");

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