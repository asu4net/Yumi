#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Yumi
{
    SharedPtr<VertexArray> VertexArray::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateSharedPtr<OpenGLVertexArray>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}