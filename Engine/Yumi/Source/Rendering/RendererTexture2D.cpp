#include "RendererTexture2D.h"
#include "Platform\OpenGL\OpenGLTexture2D.h"

RTTR_REGISTRATION
{
    using namespace Yumi;
    using namespace rttr;

    registration::enumeration<TextureMinFilter>("TextureMinFilter")
    (
        value("Linear", TextureMinFilter::Linear),
        value("Nearest", TextureMinFilter::Nearest)
    );
    registration::enumeration<TextureMagFilter>("TextureMagFilter")
    (
        value("Linear", TextureMagFilter::Linear),
        value("Nearest", TextureMagFilter::Nearest)
    );
    registration::enumeration<TextureWrapMode>("TextureWrapMode")
    (
        value("Repeat", TextureWrapMode::Repeat),
        value("ClampToEdge", TextureWrapMode::ClampToEdge)
    );

    rttr::registration::class_<Texture2DSettings>("Texture2DSettings")
        .constructor<>()
        .property("MagFilter", &Texture2DSettings::MagFilter)
        .property("MinFilter", &Texture2DSettings::MinFilter)
        .property("WrapModeU", &Texture2DSettings::WrapModeU)
        .property("WrapModeV", &Texture2DSettings::WrapModeV);
}

namespace Yumi
{
    YFORCE_LINK_IMPL(Texture2DSettings)

    SharedPtr<RendererTexture2D> RendererTexture2D::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateSharedPtr<OpenGLTexture2D>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}