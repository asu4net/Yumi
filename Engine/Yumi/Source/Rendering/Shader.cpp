#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Yumi
{    
    SharedPtr<Shader> Shader::Create(GraphicsAPI api)
    {
        switch (api)
        {
        case GraphicsAPI::OpenGL:
            return CreateShared<OpenGLShader>();
        case GraphicsAPI::None:
        default:
            YCHECK(false, "Invalid API");
            return nullptr;
        }
    }
}