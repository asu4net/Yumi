#include "VertexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Yumi
{
    SharedPtr<VertexBuffer> VertexBuffer::Create(GraphicsAPI api, const void* vertices, const uint32_t size)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateSharedPtr<OpenGLVertexBuffer>(vertices, size);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }

    SharedPtr<VertexBuffer> VertexBuffer::Create(GraphicsAPI api, const uint32_t size)
    {
        return CreateSharedPtr<OpenGLVertexBuffer>(size);
    }
}