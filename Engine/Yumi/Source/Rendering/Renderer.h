#pragma once
#include "SpriteBatchRenderer.h"

namespace Yumi
{
    class Shader;
    
    class Renderer : public Singleton<Renderer>
    {
        YSINGLETON_FRIEND(Renderer)
    public:
        void SetProjectionViewMatrix(const Matrix4& matrix) { m_ProjectionViewMatrix = matrix; }
        void SetRenderTarget(RenderTarget renderTarget) { m_CurrentRenderTarget = renderTarget; }
        void SetBlendingModeEnabled(bool enabled);
        void SetBlendingMode(BlendingMode blendingMode);
        void SetDepthTestEnabled(bool enabled);
        void SetClearColor(const Color& clearColor);
        void Clear();
        void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
        void SubmitSpritePrimitive(const SpritePrimitive& sprite);
        void DrawPrimitives();

    private:
        Renderer(GraphicsAPI api);
        ~Renderer();
        
        Matrix4 m_ProjectionViewMatrix;
        RenderTarget m_CurrentRenderTarget = RenderTarget::Default;

        SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;

        // Sprite Rendering
        SharedPtr<Shader> m_SpriteShader;
        UniquePtr<SpriteBatchRenderer> m_SpriteRenderer;
        DynamicArray<SpritePrimitive> m_SpritePrimitivesDrawList;
    };

    Renderer& GetRenderer();
}