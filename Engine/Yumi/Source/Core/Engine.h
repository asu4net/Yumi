#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        void Start();

    private:
        Engine();
        ~Engine();

        Unique<class Window> m_Window;
    };
}