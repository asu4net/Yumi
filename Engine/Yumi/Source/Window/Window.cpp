#include "Window.h"
#include "Platform\WindowsWindow.h"

namespace Yumi
{
    UniquePtr<Window> Window::Create(const Configuration& config)
    {
        return CreateUnique<WindowsWindow>(config);
    }
}