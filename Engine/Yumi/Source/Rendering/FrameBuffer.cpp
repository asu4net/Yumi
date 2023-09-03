#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Yumi
{
    Shared<FrameBuffer> FrameBuffer::Create(GraphicsAPI api, const Configuration& configuration)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLFrameBuffer>(configuration);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}
