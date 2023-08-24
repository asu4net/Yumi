#include "Engine.h"
#include "Window/Window.h"
#include "Time.h"
#include "Input/KeyCodes.h"
#include "Input/Input.h"

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
    {
        YLOG_TRACE("Yumi Engine created!\n");
    }

    Engine::~Engine()
    {
        YLOG_TRACE("Yumi Engine destroyed!\n");
    }

    void Engine::Start()
    {
        YLOG_TRACE("Yumi Engine started!\n");

        Time::Start();
        Input::Start(m_Window);

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            Time::CalculateTimeStep();

            //render stuff

            String windowTitle = "Yumi Window";
            windowTitle.append(" | MousePos: " + Input::MousePosition().ToString());
            windowTitle.append(" | FPS: " + std::to_string(Time::FrameRate()));
            windowTitle.append(" | AppTime: " + std::to_string(Time::ApplicationTime()));
            windowTitle.append(" | AppFrames: " + std::to_string(Time::ApplicationFrames()));
            windowTitle.append(" | DeltaTime: " + std::to_string(Time::DeltaTime()));
            windowTitle.append(" | FixedUpdateCalls: " + std::to_string(Time::FixedUpdateCalls()));

            m_Window->SetTitle(windowTitle);
            m_Window->Update();
        }
    }
}
