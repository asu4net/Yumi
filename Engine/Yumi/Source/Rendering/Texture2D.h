#pragma once

#include "Asset/Asset.h"

namespace Yumi
{
    enum class MinFilter { Linear, Nearest };
    enum class MagFilter { Linear, Nearest };
    enum class WrapMode { Repeat, ClampToEdge };
    enum class TextureCoordinate { U, V };
    enum class InternalFormat { None, RGB8, RGBA8 };
    enum class DataFormat { None, RGB, RGBA };
    
    struct Texture2DSettings
    {
        bool CreateFromFile = true;
        uint32_t Width = 0;
        uint32_t Height = 0;
        MagFilter MagFilter{MagFilter::Linear};
        MinFilter MinFilter{MinFilter::Linear};
        WrapMode WrapModeU{WrapMode::Repeat};
        WrapMode WrapModeV{WrapMode::Repeat};
    };
    
    class Texture2D : public Asset
    {
    public:
        static SharedPtr<Texture2D> Create(GraphicsAPI api);

        virtual void UploadToGPU() = 0;
        
        virtual void Configure(const Texture2DSettings& settings) = 0;
        virtual void SetData(const void* data, uint32_t size) = 0;
        
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetTextureID() const = 0;
        
        virtual void Bind(uint32_t slot = 0) const = 0;
    };
}