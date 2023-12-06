#pragma once

namespace Yumi
{
    struct AssetData
    {
        inline static const char* s_EmptyPathString = "NO_PATH";

        String Name;
        String Path;
        String AbsolutePath;
        Id AssetId;
        String AssetType;
    };
    
    YFORCE_LINK(AssetData)

    class Asset
    {
    public:
        Asset() = default;
        virtual ~Asset() {};

        virtual bool Load() { return false; };
        virtual void Unload() {};

        AssetData GetAssetData() const { return m_AssetData; };
        void SetAssetData(const AssetData& assetData) { m_AssetData = assetData; };
        
    private:
        AssetData m_AssetData;

        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
    };

    YFORCE_LINK(Asset)
}