#include "RendererShader.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Yumi
{
    SharedPtr<RendererShader> RendererShader::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateSharedPtr<OpenGLShader>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}