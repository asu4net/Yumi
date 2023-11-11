#include "Engine.h"
#include "Time.h"
#include "Window/Window.h"
#include "Input/KeyCodes.h"
#include "Input/Input.h"
#include "Asset/AssetManager.h"
#include "Rendering/SpriteBatchRenderer.h"
#include "Rendering/Sprite.h"
#include "Rendering/Shader.h"
#include "Rendering/RendererAPI.h"
#include "Rendering/RenderCommandQueue.h"
#include "Rendering/Renderer.h"
#include "Scene/World.h"
#include "Scene/Scene.h"
#include "Scene/Actor.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scripting/Script.h"
#include "Scene/Components/ScriptComponent.h"
#include "Scripting/Scripts/FreeLookCameraScript.h"

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
        , m_Time(Time::CreateInstance())
        , m_Input(Input::CreateInstance(m_Window))
        , m_AssetManager(AssetManager::CreateInstance(GetWorkingDirectory(), GraphicsAPI::OpenGL))
        , m_Renderer(Renderer::CreateInstance(GraphicsAPI::OpenGL))
        , m_World(World::CreateInstance())
    {
        YLOG_TRACE("Yumi Engine created!\n");
        
        // Viewport resizing for renderer
        m_Window->Events().ResizeEvent.Add([&](int width, int height) { 
            m_Renderer.SetViewport(0, 0, width, height); 
        });

        m_Renderer.SetBlendingModeEnabled(true);
        m_Renderer.SetBlendingMode(BlendingMode::Alpha);
        m_Renderer.SetClearColor(Color::DarkGrey);
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

    class TestScript : public Script
    {
        void OnUpdate() override
        {
            GetActor().GetTransform().Position += Vector3::Right * 0.3f * GetDeltaTime();
        }
    };

    void Engine::StartMainLoop()
    {  
        AssetManager& assetManager = AssetManager::GetInstance();
        AssetLink<Scene> testScene = assetManager.CreateSceneAsset(AssetData{ "Test Scene" });
        testScene->SetStartScene(true);
        testScene->SetRuntimeEnabled(false);
        
        m_World.Start();

        Actor catActor = testScene->CreateActor({"Cat"});

        catActor.Add<SpriteComponent>(assetManager.CreateSpriteFromTexture("Bola.jpg"));
        ScriptStatics::Attach<TestScript>(catActor);

        Actor secondActor = testScene->CreateActor({"Cpp", Vector3(1, 0, 0)});
        secondActor.Add<SpriteComponent>(assetManager.CreateSpriteFromTexture("cpp.png"));

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP STARTED ******\n");
        YLOG_TRACE("******************************\n");

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Time.CalculateTimeStep();
            
            static bool runtimeEnabled = false;
            if (Input::GetInstance().IsKeyPressed(KEY_LEFT_CONTROL) && Input::GetInstance().IsKeyPressed(KEY_P))
            {
                World::GetInstance().GetActiveScene()->SetRuntimeEnabled(runtimeEnabled);
                runtimeEnabled = !runtimeEnabled;
            }

            m_World.Update();
            m_Renderer.DrawPrimitives();

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

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP FINISHED *****\n");
        YLOG_TRACE("******************************\n");
    }
}
