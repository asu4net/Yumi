#pragma once

namespace Yumi
{
    class Window;

    class File
    {
        static void Start(const Unique<Window>& window);

        String OpenFile(const String& filter);
        String SaveFile(const String& filter);

    private:
        static bool m_bInitialized;
    };
}