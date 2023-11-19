#include "Core/Engine.h"
#include "Window/Window.h"
#include "Asset/AssetManager.h"
#include "Scene/World.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"

namespace Yumi
{
    Engine::Engine()  { YLOG_TRACE("Engine created!");   };
    Engine::~Engine() { YLOG_TRACE("Engine destroyed!"); };

    void Engine::Init()
    {
        YLOG_TRACE("Initializing Engine...\n");
        YCHECK(!m_IsInitialized, "Engine already initialized!");

        m_Window       = Window::Create();
        m_Time         = new Time();
        m_Input        = new Input(m_Window);
        m_AssetManager = new AssetManager(GetWorkingDirectory(), m_GraphicsApi);
        
        m_AssetManager->ImportAndLoadAssets();
        
        // TODO: Move this to engine modules
        static constexpr char* s_SpriteShaderName = "Sprite.glsl";
        SharedPtr<Shader> spriteShader = m_AssetManager->GetAssetByName(s_SpriteShaderName).GetPtrAs<Shader>().lock();
        m_Renderer     = new Renderer(m_GraphicsApi, spriteShader);
        m_World        = new World();
        
        m_World->Prepare();

        // Viewport resizing for renderer
        m_Window->Events().ResizeEvent.Add([&](int width, int height) { 
            m_Renderer->SetViewport(0, 0, width, height);
        });

        m_IsInitialized = true;
        YLOG_TRACE("Engine initialized!\n");
    }

    void Engine::Run()
    {  
        YCHECK(m_IsInitialized, "Engine needs to be initialized, call InitEngine() before RunEngine()!");
        YCHECK(!m_IsRunning, "Engine already running!");

        m_World->Start();

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP STARTED ******\n");
        YLOG_TRACE("******************************\n");

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Time->CalculateTimeStep();
            m_World->Update();

            uint32_t fixedUpdateCalls = m_Time->FixedUpdateCalls();

            while (fixedUpdateCalls--)
            {
                m_World->FixedUpdate();
            }
            
            m_Renderer->DrawPrimitives();
            
            //TODO: Move this to ImGui
            String windowTitle = "Yumi Window";

            windowTitle.append(" | MousePos: "         + m_Input->MousePosition().ToString());
            windowTitle.append(" | FPS: "              + std::to_string(m_Time->FrameRate()));
            windowTitle.append(" | AppTime: "          + std::to_string(m_Time->ApplicationTime()));
            windowTitle.append(" | AppFrames: "        + std::to_string(m_Time->ApplicationFrames()));
            windowTitle.append(" | DeltaTime: "        + std::to_string(m_Time->DeltaTime()));
            windowTitle.append(" | FixedUpdateCalls: " + std::to_string(m_Time->FixedUpdateCalls()));
            
            m_Window->SetTitle(windowTitle);
            m_Window->Update();
        }

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP FINISHED *****\n");
        YLOG_TRACE("******************************\n");

        Finish();
    }
    
    void Engine::Shutdown()
    {
        m_Window->Close();
        Finish();
    }

    void Engine::Finish()
    {
        YLOG_TRACE("Finishing engine...\n");
        
        delete m_World;
        delete m_AssetManager;
        delete m_Input;
        delete m_Time;
        
        m_Window.reset();

        m_IsRunning     = false;
        m_IsInitialized = false;

        YLOG_TRACE("Engine finished!\n");
    }
}