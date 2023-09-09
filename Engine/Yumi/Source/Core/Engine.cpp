#include "Engine.h"
#include "Time.h"
#include "Window/Window.h"
#include "Input/KeyCodes.h"
#include "Input/Input.h"
#include "Asset/AssetManager.h"

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
        , m_Time(Time::CreateInstance())
        , m_Input(Input::CreateInstance(m_Window))
        , m_AssetManager(AssetManager::CreateInstance(GetWorkingDirectory()))
    {
        YLOG_TRACE("Yumi Engine created!\n");
    }

    Engine::~Engine()
    {
        Time::DestroyInstance();
        Input::DestroyInstance();
        AssetManager::DestroyInstance();
        YLOG_TRACE("Yumi Engine destroyed!\n");
    }

    void Engine::StartMainLoop()
    {
        YLOG_TRACE("Yumi Engine main loop started!\n");

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Time.CalculateTimeStep();

            //render stuff

            String windowTitle = "Yumi Window";
            windowTitle.append(" | MousePos: " + m_Input.MousePosition().ToString());
            windowTitle.append(" | FPS: " + std::to_string(m_Time.FrameRate()));
            windowTitle.append(" | AppTime: " + std::to_string(m_Time.ApplicationTime()));
            windowTitle.append(" | AppFrames: " + std::to_string(m_Time.ApplicationFrames()));
            windowTitle.append(" | DeltaTime: " + std::to_string(m_Time.DeltaTime()));
            windowTitle.append(" | FixedUpdateCalls: " + std::to_string(m_Time.FixedUpdateCalls()));

            m_Window->SetTitle(windowTitle);
            m_Window->Update();
        }
    }
}
