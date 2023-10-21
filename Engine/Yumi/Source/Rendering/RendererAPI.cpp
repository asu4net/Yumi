#include "RendererAPI.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Yumi
{
    SharedPtr<RendererAPI> RendererAPI::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLRenderAPI>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}