#include "RenderingContext.h"
#include "Platform/OpenGL/OpenGLRenderingContext.h"

namespace Yumi
{
    Unique<RenderingContext> RenderingContext::Create(void* windowHandler)
    {
        return CreateUnique<OpenGLRenderingContext>(windowHandler);
    }
}