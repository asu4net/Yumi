#include "WindowsWindow.h"
#include "Rendering/RenderingContext.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Yumi
{
    WindowsWindow::WindowsWindow(const Configuration& config)
        : m_Config(config)
        , m_WindowHandler(nullptr)
        , m_RenderingContext(nullptr)
        , m_IsOpened(false)
    {
        printf("Windows window begin create...\n");

        if (!glfwInit())
        {
            assert(false && "GLFW Window initialisation failed!");
            return;
        }

        m_WindowHandler = glfwCreateWindow(m_Config.Width, m_Config.Height, m_Config.Title.c_str(), nullptr, nullptr);
        
        if (!m_WindowHandler)
        {
            assert(false && "GLFW Window creation failed!");
            return;
        }
        
        glfwMakeContextCurrent(m_WindowHandler);

        m_RenderingContext = RenderingContext::Create(m_WindowHandler);
        printf("Windows window created!\n");

        m_IsOpened = true;
        
        SetVSync(config.VSync);
        SetTitle(config.Title);
        SetCursorMode(config.CursorMode);
    }

    WindowsWindow::~WindowsWindow()
    {
        if (IsOpened())
            Close();

        if (!m_WindowHandler)
        {
            assert(false && "GLFW Window handler empty!");
            return;
        }

        glfwDestroyWindow(m_WindowHandler);
        m_WindowHandler = nullptr;
        printf("Windows window destroyed!\n");
    }

    //TODO: Finish
    void WindowsWindow::SetTitle(const String title)
    {
        m_Config.Title = title;
        glfwSetWindowTitle(m_WindowHandler, title.c_str());
    }

    //TODO: Finish
    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        m_Config.VSync = enabled;
    }

    //TODO: Finish
    void WindowsWindow::SetCursorMode(const CursorMode mode)
    {
        m_Config.CursorMode = mode;

        switch (m_Config.CursorMode)
        {
        case CursorMode::Normal:
            glfwSetInputMode(m_WindowHandler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            return;
        case CursorMode::Disabled:
            glfwSetInputMode(m_WindowHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            return;
        case CursorMode::Hidden:
            glfwSetInputMode(m_WindowHandler, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            return;
        case CursorMode::Captured:
            glfwSetInputMode(m_WindowHandler, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
        }
    }

    bool WindowsWindow::IsOpened() const
    {
        return !glfwWindowShouldClose(m_WindowHandler);
    }

    void WindowsWindow::Close()
    {
        if (!m_IsOpened)
        {
            assert(false && "Window is already closed!");
            return;
        }

        m_IsOpened = false;
        printf("Windows window closed!\n");
    }

    void WindowsWindow::Update()
    {
        glfwPollEvents();
        m_RenderingContext->SwapBuffers();
    }
}