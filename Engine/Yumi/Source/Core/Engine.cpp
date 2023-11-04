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

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
        , m_Time(Time::CreateInstance())
        , m_Input(Input::CreateInstance(m_Window))
        , m_AssetManager(AssetManager::CreateInstance(GetWorkingDirectory(), GraphicsAPI::OpenGL))
        , m_Renderer(Renderer::CreateInstance(GraphicsAPI::OpenGL))
    {
        YLOG_TRACE("Yumi Engine created!\n");
    }

    Engine::~Engine()
    {
        YLOG_TRACE("Yumi Engine begin destroy...\n");
        AssetManager::DestroyInstance();
        Input::DestroyInstance();
        Time::DestroyInstance();
        m_Window.reset();
        YLOG_TRACE("Yumi Engine destroyed!\n");
    }

    void Engine::StartMainLoop()
    {
        //render test stuff

        // Camera
        static Vector3 cameraPosition;
        float Size = 1.f;
        float NearPlane = 0.1f;
        float FarPlane = 1000.f;
        const float aspect = static_cast<float>(m_Window->GetWidth()) / static_cast<float>(m_Window->GetHeight());
        const float right = aspect * Size; //update aspect ratio
        const float left = -right;

        //Sprite
        Id spriteId = m_Renderer.CreateSprite(m_AssetManager.GetAssetByName<Texture2D>("Bola.jpg").Get());
        static Vector3 spritePosition;
        static Vector3 spriteRotation;
        static Vector3 spriteScale = Vector3::One;

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP STARTED ******\n");
        YLOG_TRACE("******************************\n");

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Time.CalculateTimeStep();

            //render test stuff
            if (Input::GetInstance().IsKeyPressed(KEY_W))
                cameraPosition += Vector3::Up * 0.5f * m_Time.DeltaTime();
            if (Input::GetInstance().IsKeyPressed(KEY_S))
                cameraPosition += Vector3::Down * 0.5f * m_Time.DeltaTime();
            if (Input::GetInstance().IsKeyPressed(KEY_D))
                cameraPosition += Vector3::Right * 0.5f * m_Time.DeltaTime();
            if (Input::GetInstance().IsKeyPressed(KEY_A))
                cameraPosition += Vector3::Left * 0.5f * m_Time.DeltaTime();
            
            m_Renderer.GetSprite(spriteId).SetTransform(Matrix4::CreateTransform(spritePosition, spriteRotation, spriteScale));
            m_Renderer.SetProjectionViewMatrix(Matrix4::OrthoProjection(left, right, -Size, Size,
                NearPlane, FarPlane) * Matrix4::ViewProjection(cameraPosition, Vector3::Zero));

            String windowTitle = "Yumi Window";
            windowTitle.append(" | MousePos: " + m_Input.MousePosition().ToString());
            windowTitle.append(" | FPS: " + std::to_string(m_Time.FrameRate()));
            windowTitle.append(" | AppTime: " + std::to_string(m_Time.ApplicationTime()));
            windowTitle.append(" | AppFrames: " + std::to_string(m_Time.ApplicationFrames()));
            windowTitle.append(" | DeltaTime: " + std::to_string(m_Time.DeltaTime()));
            windowTitle.append(" | FixedUpdateCalls: " + std::to_string(m_Time.FixedUpdateCalls()));
            m_Window->SetTitle(windowTitle);
            
            m_Renderer.Update();
            m_Window->Update();
        }

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP FINISHED *****\n");
        YLOG_TRACE("******************************\n");
    }
}
