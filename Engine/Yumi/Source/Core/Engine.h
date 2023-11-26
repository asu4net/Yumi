#pragma once

namespace Yumi
{
    class Engine : public Singleton<Engine>
    {
        YSINGLETON_FRIEND(Engine)
    
    public:
        bool                IsInitialized()   const { return m_IsInitialized; }
        bool                IsRunning()       const { return m_IsRunning;     }
        GraphicsAPI         GetGraphicsApi()  const { return m_GraphicsApi;     }
        class Window&       GetWindow()       const { return *m_Window;       }
        class Time&         GetTime()         const { return *m_Time;         }
        class Input&        GetInput()        const { return *m_Input;        }
        class AssetManager& GetAssetManager() const { return *m_AssetManager; }
        class Renderer&     GetRenderer()     const { return *m_Renderer;     }
        class World&        GetWorld()        const { return *m_World;        }

        void Init();
        void Run();
        void Shutdown();

    private:
        Engine();
        ~Engine();

        void Finish();

        bool                    m_IsInitialized = false;
        bool                    m_IsRunning     = false;
        GraphicsAPI             m_GraphicsApi   = GraphicsAPI::OpenGL;
        UniquePtr<Window>       m_Window        = nullptr;
        Time*                   m_Time          = nullptr;
        Input*                  m_Input         = nullptr;
        AssetManager*           m_AssetManager  = nullptr;
        Renderer*               m_Renderer      = nullptr;
        World*                  m_World         = nullptr;
    };

    // Shortcuts

    inline Engine&        CreateEngine()    { return Engine::CreateInstance();      }
    inline Engine&        GetEngine()       { return Engine::GetInstance();         }
    inline void           DestroyEngine()   {        Engine::DestroyInstance();     }

    inline void           InitEngine()      {        Engine::GetInstance().Init();  }
    inline void           RunEngine()       {        Engine::GetInstance().Run();   }

    inline Window&        GetWindow()       { return GetEngine().GetWindow();       }
    inline Time&          GetTime()         { return GetEngine().GetTime();         }
    inline Input&         GetInput()        { return GetEngine().GetInput();        }
    inline AssetManager&  GetAssetManager() { return GetEngine().GetAssetManager(); }
    inline Renderer&      GetRenderer()     { return GetEngine().GetRenderer();     }
    inline World&         GetWorld()        { return GetEngine().GetWorld();        }

    inline float          GetDeltaTime()    { return GetTime().DeltaTime();         }
}