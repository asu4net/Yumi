#pragma once
#include "GraphicsAPI.h"

namespace Yumi
{
    class VertexArray;

    enum class BlendingMode
    {
        Alpha,
        Solid,
        Add,
        Multiply
    };
    
    class RendererAPI
    {
    public:
        static Shared<RendererAPI> Create(GraphicsAPI api);
        
        virtual ~RendererAPI() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const Vector4& clearColor) = 0;
        virtual void Clear() = 0;
        virtual void SetBlendingEnabled(bool bEnabled) = 0;
        virtual void SetBlendingMode(const BlendingMode blendingMode) = 0;
        virtual void DrawElements(const Shared<VertexArray>& vertexArray, uint32_t elementCount) = 0;
        virtual void SetDepthTestEnabled(bool bEnabled) = 0;
    };
}
