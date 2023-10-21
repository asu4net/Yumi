#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        void StartMainLoop();

    private:
        Engine();
        ~Engine();

        UniquePtr<class Window> m_Window;
        
        class Time& m_Time;
        class Input& m_Input;
        class AssetManager& m_AssetManager;
    };
}