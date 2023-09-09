#pragma once

namespace Yumi
{
    class Input : public Singleton<Input>
    {
        YSINGLETON_FRIEND(Input)
    public:
        bool IsKeyPressed(int key);

        void SetConsumed(bool bConsumedByEditor);
        bool IsConsumed();

        bool IsMouseButtonPressed(int button);
        Vector2 MousePosition();

    private:
        Input(const Unique<class Window>& window);
        ~Input();

        bool m_bConsumedByEditor = false;
    };
}