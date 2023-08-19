#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YUMI_SINGLETON(Engine)
    
    public:
        void Start();

    private:
        Engine();
        ~Engine();

        Unique<class Window> m_Window;
    };
}