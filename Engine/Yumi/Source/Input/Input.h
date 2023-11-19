#pragma once

namespace Yumi
{
    class Input
    {
    public:
        Input(const UniquePtr<class Window>& window);
        ~Input();

        bool IsKeyPressed(int key);

        void SetConsumed(bool bConsumedByEditor);
        bool IsConsumed();

        bool IsMouseButtonPressed(int button);
        Vector2 MousePosition();

    private:

        bool m_bConsumedByEditor = false;
    };
}