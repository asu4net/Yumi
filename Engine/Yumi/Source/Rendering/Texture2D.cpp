#include "Texture2D.h"
#include "Core/Engine.h"
#include "Rendering/Renderer.h"
#include "RendererTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include <GLAD/glad.h>

RTTR_REGISTRATION
{
    using namespace Yumi;
    rttr::registration::class_<Texture2D>("Texture2D")
        .constructor<>()
        .property("Settings", &Texture2D::m_Settings);
}

namespace Yumi
{
    YFORCE_LINK_IMPL(Texture2D)

    bool Texture2D::Load()
    {
        const String absolutePath = GetAssetData().AbsolutePath;
        if (absolutePath == AssetData::s_EmptyPathString) return true;
        
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        m_Data = stbi_load(absolutePath.c_str(), &width, &height, &channels, 0);

        if (!m_Data)
            return false;

        m_Width = width;
        m_Height = height;

        m_Size = { (float) width, (float) height };
        m_Channels = channels;

        m_Settings.Width = width;
        m_Settings.Height = height;
        m_Settings.Channels = channels;

        m_RendererTextureId = GetRenderer().CreateTexture2D(m_Settings, m_Data);

        return true;
    }

    void Texture2D::Unload()
    {
        stbi_image_free(m_Data);
        m_Data = nullptr;
        GetRenderer().DestroyTexture2D(m_RendererTextureId);
    }
}