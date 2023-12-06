﻿#pragma once

#include "Asset/Asset.h"

namespace Yumi
{
    enum class TextureMinFilter { Linear, Nearest };
    enum class TextureMagFilter { Linear, Nearest };
    enum class TextureWrapMode { Repeat, ClampToEdge };
    enum class TextureCoordinate { U, V };
    
    struct Texture2DSettings
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
        uint32_t Channels = 0;
        TextureMagFilter MagFilter{TextureMagFilter::Linear};
        TextureMinFilter MinFilter{TextureMinFilter::Linear};
        TextureWrapMode WrapModeU{TextureWrapMode::Repeat};
        TextureWrapMode WrapModeV{TextureWrapMode::Repeat};
    };

    YFORCE_LINK(Texture2DSettings)
        
    class RendererTexture2D    
    {
    public:
        static SharedPtr<RendererTexture2D> Create(GraphicsAPI api);
        virtual void UploadToGPU(const Texture2DSettings& settings, const void* data) = 0;
        virtual uint32_t GetTextureID() const = 0;
        virtual void Bind(uint32_t slot = 0) const = 0;
    };
}