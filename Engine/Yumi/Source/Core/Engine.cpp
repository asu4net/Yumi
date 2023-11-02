#include "Engine.h"
#include "Time.h"
#include "Window/Window.h"
#include "Input/KeyCodes.h"
#include "Input/Input.h"
#include "Asset/AssetManager.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/Sprite.h"
#include "Rendering/Shader.h"
#include "Rendering/RendererAPI.h"
#include "Rendering/RenderCommandQueue.h"

namespace Yumi
{
    Engine::Engine()
        : m_Window(Window::Create())
        , m_Time(Time::CreateInstance())
        , m_Input(Input::CreateInstance(m_Window))
        , m_AssetManager(AssetManager::CreateInstance(GetWorkingDirectory(), GraphicsAPI::OpenGL))
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
        SharedPtr<Sprite> sprite = CreateSharedPtr<Sprite>();
        SharedPtr<Texture2D> texture = m_AssetManager.GetAssetByName<Texture2D>("Bola.jpg").Get();
        sprite->SetTexture(texture);
        
        SharedPtr<Shader> shader = m_AssetManager.GetAssetByName<Shader>("Texture.glsl").Get();
        SharedPtr<RendererAPI> api = RendererAPI::Create(GraphicsAPI::OpenGL);

        SharedPtr<RenderCommandQueue> commandQueue = CreateSharedPtr<RenderCommandQueue>();
        commandQueue->Submit<SetClearColorCommand>(api, Color::DarkGray);
        commandQueue->Submit<SetBlendingEnabledCommand>(api, true);
        commandQueue->Submit<SetBlendingModeCommand>(api, BlendingMode::Alpha);

        Renderer2D renderer(api, commandQueue);
        
        Renderer2D::RenderData data = { Renderer2D::RenderTarget::Default, Matrix4(), shader };
        
        float Size = 1.f;
        float NearPlane = 0.1f;
        float FarPlane = 1000.f;
        const float aspect = static_cast<float>(m_Window->GetWidth()) / static_cast<float>(m_Window->GetHeight());
        const float right = aspect * Size; //update aspect ratio
        const float left = -right;
        data.ProjectionViewMat4 = Matrix4::GetOrthoProjection(left, right, -Size, Size,
            NearPlane, FarPlane);

        YLOG_TRACE("******************************\n");
        YLOG_TRACE("***** MAIN LOOP STARTED ******\n");
        YLOG_TRACE("******************************\n");

        //TODO: Frame by frame mode
        // MAIN LOOP
        while (m_Window->IsOpened())
        {
            m_Time.CalculateTimeStep();

            static Vector3 spriteLocation;

            if (Input::GetInstance().IsKeyPressed(KEY_W))
                spriteLocation += Vector3::Up * 0.5f * m_Time.DeltaTime();
            if (Input::GetInstance().IsKeyPressed(KEY_S))
                spriteLocation += Vector3::Down * 0.5f * m_Time.DeltaTime();
            if (Input::GetInstance().IsKeyPressed(KEY_D))
                spriteLocation += Vector3::Right * 0.5f * m_Time.DeltaTime();
            if (Input::GetInstance().IsKeyPressed(KEY_A))
                spriteLocation += Vector3::Left * 0.5f * m_Time.DeltaTime();

            Matrix4 spriteTransform;
            spriteTransform.SetTranslation(spriteLocation);
            sprite->SetTransform(spriteTransform);

            commandQueue->Submit<ClearCommand>(api);
            
            //render test stuff
            renderer.Begin(data);
            renderer.SubmitSprite(sprite);
            renderer.End();

            //YLOG_WARN("location: %s \n", sprite->GetVertexPositions()[0].ToString().c_str());

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
