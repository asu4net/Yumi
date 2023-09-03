#pragma once
#include "GraphicsAPI.h"

namespace Yumi
{
    class RenderingContext
    {
    public:
        static Unique<RenderingContext> Create(GraphicsAPI api, void* windowHandler);
        
        virtual void SwapBuffers() const = 0;
    };
}