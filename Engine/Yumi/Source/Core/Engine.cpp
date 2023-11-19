#include "Engine.h"
#include "Time.h"
#include "Window/Window.h"
#include "Input/KeyCodes.h"
#include "Input/Input.h"
#include "Asset/AssetManager.h"
#include "Rendering/Renderer.h"
#include "Scene/World.h"

namespace Yumi
{
    Engine::Engine()
    {
        YLOG_TRACE("Yumi Engine begin create...\n");
        
        m_Window = Window::Create();
        Time::CreateInstance();
        Input::CreateInstance(m_Window);
        AssetManager::CreateInstance(GetWorkingDirectory(), GraphicsAPI::OpenGL);
        GetAssetManager().ImportAndLoadAssets();
        Renderer::CreateInstance(GraphicsAPI::OpenGL);
        World::CreateInstance();

        YLOG_TRACE("Yumi Engine created!\n");
        
        // Viewport resizing for renderer
        m_Window->Events().ResizeEvent.Add([](int width, int height) { 
            GetRenderer().SetViewport(0, 0, width, height);
        });
    }

    Engine::~Engine()
    {
        YLOG_TRACE("Yumi Engine begin destroy...\n");
        World::DestroyInstance();
        AssetManager::DestroyInstance();
        Input::DestroyInstance();
        Time::DestroyInstance();
        m_Window.reset();
        YLOG_TRACE("Yumi Engine destroyed!\n");
    }

    void Engine::Run()
    {  
        GetWorld().Prepare();
        m_EngineRunEvent.Broadcast();
        GetWorld().Start();

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP STARTED ******\n");
        YLOG_TRACE("******************************\n");

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            GetTime().CalculateTimeStep();
            GetWorld().Update();

            uint32_t fixedUpdateCalls = GetTime().FixedUpdateCalls();
            while (fixedUpdateCalls--)
            {
                GetWorld().FixedUpdate();
            }
            
            GetRenderer().DrawPrimitives();
            
            //TODO: Move this to ImGui
            String windowTitle = "Yumi Window";
            windowTitle.append(" | MousePos: " + GetInput().MousePosition().ToString());
            windowTitle.append(" | FPS: " + std::to_string(GetTime().FrameRate()));
            windowTitle.append(" | AppTime: " + std::to_string(GetTime().ApplicationTime()));
            windowTitle.append(" | AppFrames: " + std::to_string(GetTime().ApplicationFrames()));
            windowTitle.append(" | DeltaTime: " + std::to_string(GetTime().DeltaTime()));
            windowTitle.append(" | FixedUpdateCalls: " + std::to_string(GetTime().FixedUpdateCalls()));
            m_Window->SetTitle(windowTitle);
            
            m_Window->Update();
        }

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP FINISHED *****\n");
        YLOG_TRACE("******************************\n");
    }

    // Shortcuts
    Engine& CreateEngine()
    {
        return Engine::CreateInstance();
    }

    void DestroyEngine()
    {
        Engine::DestroyInstance();
    }

    Engine& GetEngine()
    {
        return Engine::GetInstance();
    }

    Window& GetWindow()
    {
        return *GetEngine().GetWindow().get();
    }
}
