#include "IndexBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Yumi
{
    SharedPtr<IndexBuffer> IndexBuffer::Create(GraphicsAPI api, const uint32_t* indices, const uint32_t count)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLIndexBuffer>(indices, count);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}