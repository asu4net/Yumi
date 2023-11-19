#pragma once

namespace Yumi
{
    class Window;
    YDECLARE_EVENT(class Engine, EngineRunEvent);

    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        const UniquePtr<Window>& GetWindow() const { return m_Window; }
        EngineRunEvent& OnRun() { return m_EngineRunEvent; }
        void Run();
        
    private:
        EngineRunEvent m_EngineRunEvent;
        UniquePtr<Window> m_Window;

        Engine();
        ~Engine();
    };

    // Shortcuts
    Engine& CreateEngine();
    void DestroyEngine();
    Engine& GetEngine();
    Window& GetWindow();
}