#include "Window.h"
#include "Platform\WindowsWindow.h"

namespace Yumi
{
    Unique<Window> Window::Create(const Configuration& config)
    {
        return CreateUnique<WindowsWindow>(config);
    }
}