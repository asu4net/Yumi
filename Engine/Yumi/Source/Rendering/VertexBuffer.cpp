#include "VertexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Yumi
{
    Shared<VertexBuffer> VertexBuffer::Create(GraphicsAPI api, const void* vertices, const uint32_t size)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLVertexBuffer>(vertices, size);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }

    Shared<VertexBuffer> VertexBuffer::Create(GraphicsAPI api, const uint32_t size)
    {
        return CreateShared<OpenGLVertexBuffer>(size);
    }
}