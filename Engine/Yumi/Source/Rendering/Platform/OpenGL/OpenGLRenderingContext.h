#pragma once
#include "Rendering/RenderingContext.h"

struct GLFWwindow;

namespace Yumi
{
    class OpenGLRenderingContext : public RenderingContext
    {
    public:
#ifdef YUMI_DEBUG
        inline static bool EnableDebugMessages = true;
        inline static std::function<void(const std::string& message)> OnDebugMessage = [](const std::string& message)
        {
           YLOG("%s \n", message.c_str());
        };
#endif
        OpenGLRenderingContext(void* windowHandler);

        void SwapBuffers() const override;

    private:
        GLFWwindow* m_WindowHandler;
    };
}