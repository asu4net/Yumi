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

        void Configure(const Texture2DSettings& settings) override { m_Settings = settings; }
        void SetData(const void* data, uint32_t size) override;

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }
        uint32_t GetTextureID() const override { return m_TextureID; }

        void Bind(uint32_t slot = 0) const override;

        String GetTypeName() const override { return m_TypeName; }
        String GetName() const override { return m_Name; }
        String GetPath() const override { return m_Path; }
        String GetAbsolutePath() const override { return m_AbsolutePath; }
        Id GetId() const override { return m_Id; }

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

        String m_Name;
        String m_Path;
        String m_AbsolutePath;
        String m_TypeName;
        Id m_Id{ 0 };
    };
}