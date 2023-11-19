#include "Input.h"
#include <GLFW/glfw3.h>
#include "Window/Window.h"

namespace Yumi
{
    static GLFWwindow* g_WindowHandler = nullptr;

    Input::Input(const UniquePtr<Window>& window)
    {
        g_WindowHandler = static_cast<GLFWwindow*>(window->GetHandler());
        YLOG_TRACE("Input created!\n");
    }

    Input::~Input() 
    {
        YLOG_TRACE("Input destroyed!\n");
    };

    bool Input::IsKeyPressed(const int key)
    {
        if (m_bConsumedByEditor) return false;
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
        if (m_bConsumedByEditor) return false;
        const auto state = glfwGetMouseButton(g_WindowHandler, button);
        return state == GLFW_PRESS;
    }

    Vector2 Input::MousePosition()
    {
        double xPos, yPos;
        glfwGetCursorPos(g_WindowHandler, &xPos, &yPos);
        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    Input& GetInput()
    {
        return Input::GetInstance();
    }
}