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

    OpenGLRenderingContext::OpenGLRenderingContext(void* windowHandler)
        : m_WindowHandler(static_cast<GLFWwindow*>(windowHandler))
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            YCHECK(false, "Failed to initialize glad!");
            return;
        }
        
        YLOG_TRACE("OpenGL rendering context created!\n");

#ifdef YUMI_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OnDebugMessageCallback, nullptr);
#endif
    }

    void OpenGLRenderingContext::SwapBuffers() const
    {
        glfwSwapBuffers(m_WindowHandler);
    }
}