#include "AssetManager.h"

namespace Yumi
{
    AssetManager::AssetManager(const String& workingDirectory, GraphicsAPI api)
        : m_WorkingDirectory(workingDirectory)
        , m_AssetDirectory(m_WorkingDirectory + "\\" + GetAssetsFolderName())
        , m_GraphicsApi(api)
    {
        ImportAndLoadAssets();
    }

    AssetManager::~AssetManager()
    {
        UnloadAssets();
    }

    void AssetManager::ImportAndLoadAssets()
    {
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
                YCHECK(CreateAsset<Texture2D>(fileName, localPath)->Load(), "Failed loading: %s", fileName.c_str());
                YLOG_TRACE("Texture2D loaded: %s\n", fileName.c_str());
            }
            else if (dirPath.extension() == ".glsl")
            {
                YCHECK(CreateAsset<Shader>(fileName, localPath)->Load(), "Failed loading: %s", fileName.c_str());
                YLOG_TRACE("Shader loaded: %s\n", fileName.c_str());
            }
        }
    }

    void AssetManager::UnloadAssets()
    {
        for (auto [id, asset] : m_IdAssetMap)
        {
            asset->Unload();
        }

        m_IdAssetMap.clear();
    }

    void AssetManager::GetAssetDirectoryLocalPath(const String& path, String& localPath)
    {
        DynamicArray<String> splitPath;
        String subString;
        std::stringstream ss(path);
        bool bProceed{ false };
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