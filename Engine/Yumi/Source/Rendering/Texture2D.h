#pragma once
#include "Asset\Asset.h"
#include "RendererTexture2D.h"

namespace Yumi
{
    class Texture2D : public Asset
    {
    public:
        Texture2D() = default;
        
        void SetSettings(const Texture2DSettings& settings) { m_Settings = settings; }
        Texture2DSettings GetSettings() const { return m_Settings; }

        Id GetRendererId() const { return m_RendererTextureId; }
        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }
        Vector2 GetSize() const { return m_Size; }

        bool Load() override;
        void Unload() override;

    private:
        Texture2DSettings m_Settings;
        Id m_RendererTextureId = 0;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        uint32_t m_Channels = 0;
        Vector2 m_Size;
        void* m_Data = nullptr;

        RTTR_ENABLE(Asset)
        RTTR_REGISTRATION_FRIEND
    };
    
    YFORCE_LINK(Texture2D)
    YDECLARE_ASSET_EXTENSION(Texture2D, png)
    YDECLARE_ASSET_EXTENSION(Texture2D, jpg)
}