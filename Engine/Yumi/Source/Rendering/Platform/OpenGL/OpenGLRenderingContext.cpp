#include "OpenGLRenderingContext.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Yumi
{
#ifdef YUMI_DEBUG
    static void APIENTRY OnDebugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity,
        GLsizei length, const char* message, const void* userParam)
    {
        if (!OpenGLRenderingContext::EnableDebugMessages) return;
        OpenGLRenderingContext::OnDebugMessage(message);
    }
#endif

    namespace InternalOpenGLRenderingContext
    {
        static GLFWwindow* GetGlfWwindow(void* windowHandler)
        {
            static GLFWwindow* glfWwindowHandler = static_cast<GLFWwindow*>(windowHandler);
            return glfWwindowHandler;
        }
    }

    OpenGLRenderingContext::OpenGLRenderingContext(void* windowHandler)
        : m_WindowHandler(windowHandler)
    {
        assert(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) && "Failed to initialize glad!");

#ifdef YUMI_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OnDebugMessageCallback, nullptr);
#endif
    }

    void OpenGLRenderingContext::SwapBuffers() const
    {
        glfwSwapBuffers(InternalOpenGLRenderingContext::GetGlfWwindow(m_WindowHandler));
    }
}