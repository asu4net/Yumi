#include "RenderingContext.h"
#include "Platform/OpenGL/OpenGLRenderingContext.h"

namespace Yumi
{
    UniquePtr<RenderingContext> RenderingContext::Create(GraphicsAPI api, void* windowHandler)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateUniquePtr<OpenGLRenderingContext>(windowHandler);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}