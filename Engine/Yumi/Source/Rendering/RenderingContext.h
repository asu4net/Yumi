#pragma once


namespace Yumi
{
    class RenderingContext
    {
    public:
        static UniquePtr<RenderingContext> Create(GraphicsAPI api, void* windowHandler);
        
        virtual void SwapBuffers() const = 0;
    };
}