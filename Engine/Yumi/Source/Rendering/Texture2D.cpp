#include "Texture2D.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Yumi
{
    Shared<Texture2D> Texture2D::Create(GraphicsAPI api, const String& name, const String& path, const Id& id)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLTexture2D>(name, path, id);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}