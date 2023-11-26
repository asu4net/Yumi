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
    };

    class Asset
    {
    public:
        virtual ~Asset() {};

        virtual bool Load() = 0;
        virtual void Unload() = 0;

        virtual AssetData GetAssetData() const = 0;
        virtual void SetAssetData(const AssetData& assetData) = 0;
    };
}