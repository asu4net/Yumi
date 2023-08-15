#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YUMI_SINGLETON(Engine)
    
    private:
        Engine();
        ~Engine();

        Unique<class Window> m_Window;
        Unique<class Time> m_Time;

    public:
        void Start();
    };
}