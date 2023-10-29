#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Yumi
{
    SharedPtr<FrameBuffer> FrameBuffer::Create(GraphicsAPI api, const Configuration& configuration)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateSharedPtr<OpenGLFrameBuffer>(configuration);
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}
