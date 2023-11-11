#pragma once

namespace Yumi
{
    YDECLARE_EVENT(class Engine, EngineRunEvent);

    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        const UniquePtr<class Window>& GetWindow() const { return m_Window; }
        EngineRunEvent& OnRun() { return m_EngineRunEvent; }
        void Run();
        
    private:
        EngineRunEvent m_EngineRunEvent;
        UniquePtr<Window> m_Window;

        Engine();
        ~Engine();
    };
}