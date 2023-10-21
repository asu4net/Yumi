#pragma once
#include "Window/Window.h"

namespace Yumi
{
    class Renderer : public Singleton<Renderer>
    {
        YSINGLETON_FRIEND(Renderer)
    public:
    private:
        Renderer(const UniquePtr<Window>& window);
        ~Renderer();
    
        GraphicsAPI m_GraphicsApi;
    };
}