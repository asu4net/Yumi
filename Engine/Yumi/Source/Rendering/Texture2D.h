#pragma once
#include "Asset\Asset.h"

namespace Yumi
{
    class Texture2D : public Asset
    {
    public:
        Texture2D() = default;

        AssetData GetAssetData() const override { return m_AssetData; }
        void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; }

        Id GetRendererId() const { return m_RendererTextureId; }
        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }
        Vector2 GetSize() const { return m_Size; }

        bool Load() override;
        void Unload() override;

    private:
        AssetData m_AssetData;
        Id m_RendererTextureId = 0;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;
        Vector2 m_Size;
        void* m_Data = nullptr;
    };
}