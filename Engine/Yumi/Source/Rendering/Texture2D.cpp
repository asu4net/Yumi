#include "Texture2D.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Yumi
{
    SharedPtr<Texture2D> Texture2D::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLTexture2D>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}