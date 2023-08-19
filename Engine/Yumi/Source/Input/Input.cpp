#include "Input.h"
#include <GLFW/glfw3.h>
#include "Window/Window.h"

namespace Yumi
{
    static GLFWwindow* g_WindowHandler = nullptr;
    
    bool Input::m_bInitialized = false;
    bool Input::m_bConsumedByEditor = false;

    void Input::Start(const Unique<Window>& window)
    {
        g_WindowHandler = static_cast<GLFWwindow*>(window->GetHandler());
        m_bInitialized = true;
    }

    bool Input::IsKeyPressed(const int key)
    {
        if (!m_bInitialized || m_bConsumedByEditor) return false;
        const auto state = glfwGetKey(g_WindowHandler, key);
        return state == GLFW_PRESS;
    }

    void Input::SetConsumed(const bool bConsumedByEditor)
    {
        m_bConsumedByEditor = bConsumedByEditor;
    }

    bool Input::IsConsumed()
    {
        return m_bConsumedByEditor;
    }

    bool Input::IsMouseButtonPressed(const int button)
    {
        if (!m_bInitialized || m_bConsumedByEditor) return false;
        const auto state = glfwGetMouseButton(g_WindowHandler, button);
        return state == GLFW_PRESS;
    }

    Vector2 Input::MousePosition()
    {
        if (!m_bInitialized) return {};

        double xPos, yPos;
        glfwGetCursorPos(g_WindowHandler, &xPos, &yPos);
        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }
}