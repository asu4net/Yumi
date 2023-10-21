#pragma once

namespace Yumi
{
    struct AssetData
    {
        Id AssetId = 0;
        String Name;
        String Path;
        String AbsolutePath;
        String AssetType;
    };

    class Asset
    {
    public:
        virtual ~Asset() {};

        virtual bool Load() = 0;
        virtual void Unload() = 0;

        virtual AssetData GetAssetData() const = 0;

    private:
        virtual void SetAssetData(const AssetData& assetData) = 0;
        friend class AssetManager;
    };
}