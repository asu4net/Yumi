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
        
        Animation() = default;

        void SetTarget(const WeakPtr<AssetRef>& target) { m_Target = target; };

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
        void Clear();

        void Update();

    private:
        AssetData m_AssetData;
        WeakPtr<AssetRef> m_Target;
        DynamicArray<Key> m_Keys;
        uint32_t m_CurrentIndex = 0;
        float m_Time = 0.f;
        float m_CurrentTime = 0.f;
        bool m_LoopEnabled = false;
        bool m_IsPlaying = false;

        virtual void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; };
        void SortKeys();

        friend class AssetManager;
    };
}