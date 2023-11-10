#pragma once

#include "WindowEvents.h"

namespace Yumi
{
    class Window
    {
    public:
        enum class CursorMode { Normal, Disabled, Hidden, Captured };

        struct Configuration
        {
            String Title{"Yumi Window"};
            int Width{ 1280 }, Height{ 720 };
            float Aspect = (float) Width / (float) Height;
            GraphicsAPI API = GraphicsAPI::OpenGL;
            bool VSync{ true };
            CursorMode CursorMode{ CursorMode::Normal };
        };

        virtual ~Window() = default;

        virtual void* GetHandler() const = 0;

        virtual WindowEvents& Events() = 0;

        virtual void SetTitle(const String title) = 0;
        virtual const String& GetTitle() const = 0;

        virtual uint32_t GetWidth() const = 0;
        
        virtual uint32_t GetHeight() const = 0;

        virtual float GetAspect() const = 0;

        virtual Vector2 GetSize() const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void SetCursorMode(const CursorMode mode) = 0;
        virtual CursorMode GetCursorMode() const = 0;
        
        virtual bool IsOpened() const = 0;
                
        virtual void Close() = 0;

        virtual void Update() = 0;

        static UniquePtr<Window> Create(const Configuration& config = {});
    };
}