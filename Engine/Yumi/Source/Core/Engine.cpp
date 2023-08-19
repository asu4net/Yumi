#include "Engine.h"
#include "Window/Window.h"
#include "Time.h"

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
        , m_Time(CreateUnique<Time>())
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

        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Window->Update();
            m_Time->CalculateTimeStep();
        }
    }
}