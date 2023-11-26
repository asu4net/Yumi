#include "Texture2D.h"
#include "Core/Engine.h"
#include "Rendering/Renderer.h"
#include "RendererTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include <GLAD/glad.h>

namespace Yumi
{
    bool Texture2D::Load()
    {
        const String absolutePath = m_AssetData.AbsolutePath;
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

        Texture2DSettings settings;
        settings.Width = width;
        settings.Height = height;
        settings.Channels = channels;

        m_RendererTextureId = GetRenderer().CreateTexture2D(settings, m_Data);

        return true;
    }

    void Texture2D::Unload()
    {
        stbi_image_free(m_Data);
        m_Data = nullptr;
        GetRenderer().DestroyTexture2D(m_RendererTextureId);
    }
}