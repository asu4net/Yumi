#include "Engine.h"

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
    {
        printf("Yumi Engine created!\n");
    }

    Engine::~Engine()
    {
        printf("Yumi Engine destroyed!\n");
    }

    void Engine::Start()
    {
        printf("Yumi Engine started!\n");

        m_Window->Open();

        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Window->ProcessMessages();
        }
    }
}