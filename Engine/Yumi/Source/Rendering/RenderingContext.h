#pragma once

namespace Yumi
{
    class RenderingContext
    {
    public:
        virtual void SwapBuffers() const = 0;

        static Unique<RenderingContext> Create(void* windowHandler);
    };
}