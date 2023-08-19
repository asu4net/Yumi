#pragma once
#include "Rendering/RenderingContext.h"

namespace Yumi
{
    class OpenGLRenderingContext : public RenderingContext
    {
    public:
#ifdef YUMI_DEBUG
        inline static bool EnableDebugMessages = true;
        inline static std::function<void(const std::string& message)> OnDebugMessage = [](const std::string& message)
        {
            printf("%s \n", message.c_str());
        };
#endif
        OpenGLRenderingContext(void* windowHandler);

        void SwapBuffers() const override;

    private:
        void* m_WindowHandler = nullptr;
    };
}