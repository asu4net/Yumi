#include "Engine.h"
#include "Window/Window.h"
#include "Time.h"

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

        Time::Start();

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            Time::CalculateTimeStep();

            //render stuff

            String windowTitle = "Yumi Window";
            windowTitle.append(" | FPS: " + std::to_string(Time::FrameRate()));
            windowTitle.append(" | AppTime: " + std::to_string(Time::ApplicationTime()));
            windowTitle.append(" | AppFrames: " + std::to_string(Time::ApplicationFrames()));
            windowTitle.append(" | DeltaTime: " + std::to_string(Time::DeltaTime()));
            windowTitle.append(" | FixedUpdateCalls: " + std::to_string(Time::FixedUpdateCalls()));

            std::cout << Time::FixedUpdateCalls() << std::endl;

            m_Window->SetTitle(windowTitle);
            m_Window->Update();
        }
    }
}