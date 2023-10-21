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

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void SetClearColor(const Vector4& clearColor) override;
        void Clear() override;
        void SetBlendingEnabled(bool bEnabled) override;
        void SetBlendingMode(const BlendingMode blendingMode) override;
        void DrawElements(const SharedPtr<VertexArray>& vertexArray, uint32_t elementCount) override;
        void SetDepthTestEnabled(bool bEnabled) override;
    };
}
