#pragma once
#include "Asset\AssetRef.h"
#include "Asset\Asset.h"

namespace Yumi
{
    class Animation : public Asset
    {
    public:
        struct Key
        {
            AssetRef KeyAssetRef;
            float KeyTime;
        };

        static void PushKeysFromAtlas(const AssetRef& animationRef, const AssetRef& spriteAtlasRef,
            const Vector2& atlasTileSize, const DynamicArray<Vector2>& atlasLocations, const DynamicArray<float>& keyTimes);

        static void PushKeysFromAtlas(const AssetRef& animationRef, const AssetRef& spriteAtlasRef,
            const Vector2& atlasTileSize, uint32_t numOfTiles, float keyTime = .1f, bool atlasIsHorizontal = true);

        static void PushKeysFromAtlas(const String& animationName, const String& atlasName,
            const Vector2& atlasTileSize, uint32_t numOfTiles, float keyTime = .1f, bool atlasIsHorizontal = true);

        Animation() = default;

        bool Load() override { return true; }
        void Unload() override {}
        
        AssetData GetAssetData() const override { return m_AssetData; };
        
        void SetTime(float time) { m_Time = time; }
        float GetTime() const { return m_Time; }
        
        void PushKey(const Key& key);
        void PopKey(uint32_t index);
        const Key& GetKey(uint32_t index) const;
        size_t GetSize() const;
        void AdjustTime();
        void Clear();

    private:
        AssetData m_AssetData;
        DynamicArray<Key> m_Keys;
        float m_Time = 0.f;

        virtual void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; };
        void SortKeys();

        friend class AssetManager;
    };
}