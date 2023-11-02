#pragma once
#include "Rendering/RendererAPI.h"

namespace Yumi
{
    class VertexArray;

    class OpenGLRenderAPI : public RendererAPI
    {
    public:
        OpenGLRenderAPI() = default;
        ~OpenGLRenderAPI() override = default;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
        void SetClearColor(const Color& clearColor) const override;
        void Clear() const override;
        void SetBlendingEnabled(bool bEnabled) const override;
        void SetBlendingMode(const BlendingMode blendingMode) const override;
        void DrawElements(const SharedPtr<VertexArray>& vertexArray, uint32_t elementCount) const override;
        void SetDepthTestEnabled(bool bEnabled) const override;
        GraphicsAPI GetGraphicsAPI() const override { return GraphicsAPI::OpenGL; }
    };
}
