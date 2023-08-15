#pragma once
#include "Window/Window.h"

namespace Yumi
{
    class WindowsWindow : public Window
    {

    public:
        WindowsWindow(const Configuration& config);
        WindowsWindow(const Window&) = delete;
        WindowsWindow& operator = (const WindowsWindow&) = delete;

        ~WindowsWindow() override;

        void SetTitle(const String title) override;
        const String& GetTitle() const override { return m_Config.Title; }
        
        uint32_t GetWidth() const override { return m_Config.Width; };

        uint32_t GetHeight() const override { return m_Config.Height; };
        
        void SetVSync(bool enabled) override;
        bool IsVSync() const override { return m_Config.VSync; };
        
        void SetCursorMode(const CursorMode mode) override;
        CursorMode GetCursorMode() const override { return m_Config.CursorMode; };
    
        bool IsCreated() const override { return m_IsCreated; }

        bool IsOpened() const override { return m_IsOpened; };

        void Open() override;

        void Close() override;

        void ProcessMessages();

    private:
        Configuration m_Config;
        HINSTANCE m_HandlerInstance;
        HWND m_WindowHandler;
        bool m_IsCreated;
        bool m_IsOpened;
    };
}