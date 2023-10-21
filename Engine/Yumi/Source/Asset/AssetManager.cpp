#include "AssetManager.h"

namespace Yumi
{
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
                TryLoadAsset(CreateAsset<Texture2D>(fileName, localPath));
            }
            else if (dirPath.extension() == ".glsl")
            {
                TryLoadAsset(CreateAsset<Shader>(fileName, localPath));
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
        YLOG_TRACE("Assets unloaded!\n");
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