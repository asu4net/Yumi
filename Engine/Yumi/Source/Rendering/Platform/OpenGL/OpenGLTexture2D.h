#pragma once
#include "Rendering/Texture2D.h"

namespace Yumi
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const String& name, const String& path, const Id& id);
        ~OpenGLTexture2D() override = default;

        bool Load() override;
        void Initialize() override;
        void UploadToGPU() override;
        bool Unload() override;

        void Configure(const Texture2DSettings& settings) override;
        void SetData(const void* data, uint32_t size) override;

        uint32_t GetWidth() const override;
        uint32_t GetHeight() const override;
        uint32_t GetTextureID() const override;

        void Bind(uint32_t slot = 0) const override;

    private:
        Texture2DSettings m_Settings;
        uint32_t m_TextureID{ 0 };
        uint32_t m_Width{ 0 };
        uint32_t m_Height{ 0 };
        uint32_t m_Channels{ 0 };
        InternalFormat m_InternalFormat{ InternalFormat::None };
        DataFormat m_DataFormat{ DataFormat::None };
        unsigned char* m_Data{ nullptr };
        bool m_bUploaded{ false };
    };
}