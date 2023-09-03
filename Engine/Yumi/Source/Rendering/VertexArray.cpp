#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Yumi
{
    Shared<VertexArray> VertexArray::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLVertexArray>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}