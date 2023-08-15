#pragma once
#include "Window/Window.h"

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YUMI_SINGLETON(Engine)
    
    private:
        Engine();
        ~Engine();

        Unique<class Window> m_Window;

    public:
        void Start();
    };
}