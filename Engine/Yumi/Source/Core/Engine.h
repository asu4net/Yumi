#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        const UniquePtr<class Window>& GetWindow() const { return m_Window; }

        void StartMainLoop();

    private:
        Engine();
        ~Engine();

        UniquePtr<Window> m_Window;
        
        class Time& m_Time;
        class Input& m_Input;
        class AssetManager& m_AssetManager;
        class Renderer& m_Renderer;
        class World& m_World;
    };
}