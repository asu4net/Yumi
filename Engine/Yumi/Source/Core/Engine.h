#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        class Window&       GetWindow()       const { return *m_Window;       }
        class Time&         GetTime()         const { return *m_Time;         }
        class Input&        GetInput()        const { return *m_Input;        }
        class AssetManager& GetAssetManager() const { return *m_AssetManager; }
        class Renderer&     GetRenderer()     const { return *m_Renderer;     }
        class World&        GetWorld()        const { return *m_World;        }

        void Init();
        void Run();

    private:
        void Finish();

        bool                    m_IsInitialized = false;
        bool                    m_IsRunning     = false;
        GraphicsAPI             m_GraphicsApi   = GraphicsAPI::OpenGL;
        UniquePtr<Window>       m_Window;
        UniquePtr<Time>         m_Time;
        UniquePtr<Input>        m_Input;
        UniquePtr<AssetManager> m_AssetManager;
        UniquePtr<Renderer>     m_Renderer;
        UniquePtr<World>        m_World;

        Engine();
        ~Engine();
    };

    // Shortcuts

    inline Engine&        CreateEngine()    { return Engine::CreateInstance();      }
    inline Engine&        GetEngine()       { return Engine::GetInstance();         }
    inline void           DestroyEngine()   {        Engine::DestroyInstance();     }

    inline void           InitEngine()      {        Engine::GetInstance().Init();  }
    inline void           RunEngine()       {        Engine::GetInstance().Run();  }

    inline Window&        GetWindow()       { return GetEngine().GetWindow();       }
    inline Time&          GetTime()         { return GetEngine().GetTime();         }
    inline Input&         GetInput()        { return GetEngine().GetInput();        }
    inline AssetManager&  GetAssetManager() { return GetEngine().GetAssetManager(); }
    inline Renderer&      GetRenderer()     { return GetEngine().GetRenderer();     }
    inline World&         GetWorld()        { return GetEngine().GetWorld();        }

    inline float          GetDeltaTime()    { return GetTime().DeltaTime();         }
}