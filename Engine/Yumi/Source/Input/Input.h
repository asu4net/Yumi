#pragma once

namespace Yumi
{
    class Window;

    class Input
    {
    public:
        static bool IsKeyPressed(int key);

        static void SetConsumed(bool bConsumedByEditor);
        static bool IsConsumed();

        static void Start(const Unique<Window>& window);
        static bool IsMouseButtonPressed(int button);
        static Vector2 MousePosition();

    private:
        static bool m_bConsumedByEditor;
        static bool m_bInitialized;
    };
}
