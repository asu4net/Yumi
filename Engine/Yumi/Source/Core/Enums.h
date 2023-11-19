#pragma once

namespace Yumi
{
    enum class GraphicsAPI
    {
        None, OpenGL
    };

    enum class RenderTarget
    {
        Default, FrameBuffer
    };

    enum class Flip
    {
        None, X, Y, Both
    };
}