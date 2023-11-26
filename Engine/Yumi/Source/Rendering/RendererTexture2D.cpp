#include "RendererTexture2D.h"
#include "Platform\OpenGL\OpenGLTexture2D.h"

namespace Yumi
{
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