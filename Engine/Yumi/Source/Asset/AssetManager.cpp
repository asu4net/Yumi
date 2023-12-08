#include "AssetManager.h"
#include "Rendering\Shader.h"

namespace Yumi
{
    static constexpr char* AssetExtension = ".yumiAsset";

    //TODO: Separar la deserialización de la llamada al load
    //TODO: Al deserializar un AssetRef siempre tienen que estar cargados todos los assets porque
    // se ha de resolver el retarget para el id del asset

    void AssetManager::SerializeAsset(const SharedPtr<Asset>& asset, const String& path)
    {
        const String jsonYumiAsset = Serialization::ToJson(asset);
        const AssetData assetData = asset->GetAssetData();
        
        std::ofstream fileYumiAssetProject("../" + path + "/" + assetData.Name + AssetExtension);
        std::ofstream fileYumiAssetBinaries(GetWorkingDirectory() + "/" + path + "/" + assetData.Name + AssetExtension);
        
        fileYumiAssetProject << jsonYumiAsset;
        fileYumiAssetBinaries << jsonYumiAsset;
    }

    SharedPtr<Asset> AssetManager::DeserializeAsset(const std::filesystem::path& assetPath)
    {
        if (assetPath.extension() != AssetExtension)
        {
            return nullptr;
        }

        const std::ifstream fileStream(assetPath);

        if (fileStream.fail())
        {
            return nullptr;
        }

        StringStream assetDataStream;
        assetDataStream << fileStream.rdbuf();

        Asset assetData;
        Serialization::FromJson(assetDataStream.str(), assetData);

        Type assetType = rttr::type::get_by_name(assetData.GetAssetData().AssetType);

        if (!assetType.is_valid())
            return nullptr;

        Variant variant = assetType.create();
        
        if (!variant.is_valid())
            return nullptr;
        
        Instance instance = variant;
        Serialization::FromJson(assetDataStream.str(), instance);
        SharedPtr<Asset> asset = variant.get_value<SharedPtr<Asset>>();
        return asset;
    }

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

            SharedPtr<Asset> asset = DeserializeAsset(dirPath);
            
            if (!asset)
                continue;

            AssetRef assetRef = RegistryAsset(asset, asset->GetAssetData());
            TryLoadAsset(assetRef);
        }

        for (auto [id, asset] : m_IdAssetMap)
        {
            asset->PostLoad();
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
        assetData.AssetType = asset->get_type().get_name().to_string();
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