#include "WindowsWindow.h"
#include <tchar.h>

namespace Yumi
{
    static const TCHAR WindowClassName[] = TEXT("YumiWindowClass");

    static bool AssertWindowCreated(Window* window)
    {
        if (!window->IsCreated())
        {
            assert(false && "Window needs to have been created first!\n");
            return false;
        }

        return true;
    }

    // Function executed when processing messages
    LRESULT CALLBACK WindowProcedure(HWND windowHandler, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CLOSE:
            DestroyWindow(windowHandler);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(windowHandler, msg, wParam, lParam);
        }
        return 0;
    }

    WindowsWindow::WindowsWindow(const Configuration& config)
        : m_Config(config)
        , m_HandlerInstance(GetModuleHandle(nullptr))
        , m_WindowHandler(nullptr)
        , m_IsCreated(false)
        , m_IsOpened(false)
    {
        printf("Windows window begin create...\n");

        //Window class registration
        WNDCLASSEX wc;

        wc.cbSize = sizeof(WNDCLASSEX);                  // The size, in bytes, of the structure
        wc.style = 0;                                    // The window class styles.
        wc.lpfnWndProc = WindowProcedure;                // It stores the address of the window procedure.
        wc.cbClsExtra = 0;                               // The number of extra bytes to allocate for the window class.
        wc.cbWndExtra = 0;                               // The number of extra bytes to allocate for each individual window.
        wc.hInstance = m_HandlerInstance;                // The instance of the application handle.
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);   // The icon handle for the window class.
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);     // The cursor handle for the window class.
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);   // A handle to the background brush.
        wc.lpszMenuName = nullptr;                       // The resource name of the menu bar to use.
        wc.lpszClassName = WindowClassName;                    // The class name that identifies this window class structure.
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); // A handle to the small class icon.

        if (!RegisterClassEx(&wc)) 
        {
            assert(false && "Could not register window class");
            return;
        }

        std::wstring wideStringTitle = std::wstring(m_Config.Title.begin(), m_Config.Title.end());
        LPCWSTR windowTitle = wideStringTitle.c_str();

        m_WindowHandler = CreateWindowEx
        (
            WS_EX_LEFT,           // The extended window styles. The default value is WS_EX_LEFT.
            WindowClassName,      // The class name
            windowTitle,          // The window title, or caption. In this case, it is the caption that is displayed in a window's title bar.
            WS_OVERLAPPEDWINDOW,  // The window styles. If you want to create a top-level (parent) window like this one, the flag to pass in is WS_OVERLAPPEDWINDOW.
            CW_USEDEFAULT,        // The x-coordinate of the upper-left corner of the window.
            CW_USEDEFAULT,        // The y-coordinate of the upper-left corner of the window
            m_Config.Width,       // The width of the window
            m_Config.Height,      // The height of the window
            nullptr,              // The handle to the parent window. Since this window is in itself a parent window, this argument is nullptr.
            nullptr,              // If the window being created is a parent window, then this argument is a handle to the window menu.
            m_HandlerInstance,    // The handle to the instance of the application.
            nullptr               // The extra information that is passed to the window's window procedure.
        );

        if (!m_WindowHandler)
        {
            assert(false && "Could not create window");
            return;
        }

        m_IsCreated = true;
        printf("Windows window created!\n");
    }

    WindowsWindow::~WindowsWindow()
    {
        UnregisterClass(WindowClassName, m_HandlerInstance);
        printf("Windows window destroyed!\n");
    }

    //TODO: Finish
    void WindowsWindow::SetTitle(const String title)
    {
        if (!AssertWindowCreated(this)) return;
        m_Config.Title = title;
    }

    //TODO: Finish
    void WindowsWindow::SetVSync(bool enabled)
    {
        if (!AssertWindowCreated(this)) return;
        m_Config.VSync = enabled;
    }

    //TODO: Finish
    void WindowsWindow::SetCursorMode(const CursorMode mode)
    {
        if (!AssertWindowCreated(this)) return;
        m_Config.CursorMode = mode;
    }

    void WindowsWindow::Open()
    {
        if (!AssertWindowCreated(this)) return;
        if (m_IsOpened)
        {
            assert(false && "Window is already opened!");
            return;
        }
        ShowWindow(m_WindowHandler, SW_SHOW);
        m_IsOpened = true;
        printf("Windows window opened!\n");
    }

    void WindowsWindow::Close()
    {
        if (!AssertWindowCreated(this)) return;

        if (!m_IsOpened)
        {
            assert(false && "Window is already closed!");
            return;
        }

        m_IsOpened = false;
        printf("Windows window closed!\n");
    }

    void WindowsWindow::ProcessMessages()
    {
        if (!AssertWindowCreated(this)) return;

        MSG msg = {};

        while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) 
        {
            if (msg.message == WM_QUIT)
            {
                Close();
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}