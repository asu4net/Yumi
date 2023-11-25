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
        Animation(AssetRef* target);

        void SetTarget(AssetRef* target);

        bool Load() override { return true; }
        void Unload() override {}
        
        AssetData GetAssetData() const override { return m_AssetData; };
        
        void SetTime(float time) { m_Time = time; }
        float GetTime() const { return m_Time; }

        float GetCurrentTime() const { return m_CurrentTime; }

        void SetLoopEnabled(bool loopEnabled) { m_LoopEnabled = loopEnabled; }
        bool IsLoopEnabled() const { return m_LoopEnabled; }

        void Play();
        void Pause();
        void Stop();
        void Reset();
        bool IsPlaying() const { return m_IsPlaying; }
        
        void PushKey(const Key& key);
        void PopKey(uint32_t index);
        Key& GetKey(uint32_t index);
        void AdjustTime();
        void Clear();

        void Update();

    private:
        AssetData m_AssetData;
        AssetRef* m_Target = nullptr;
        DynamicArray<Key> m_Keys;
        uint32_t m_CurrentIndex = 0;
        float m_Time = 0.f;
        float m_CurrentTime = 0.f;
        bool m_LoopEnabled = true;
        bool m_IsPlaying = false;

        virtual void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; };
        void SortKeys();

        friend class AssetManager;
    };
}