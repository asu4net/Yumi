#pragma once
#include "SpriteBatchRenderer.h"
#include "Sprite.h"

namespace Yumi
{
    class Shader;

    class Renderer : public Singleton<Renderer>
    {
        YSINGLETON_FRIEND(Renderer)
    public:

        void SetProjectionViewMatrix(const Matrix4& matrix) { m_ProjectionViewMatrix = matrix; }
        void SetRenderTarget(RenderTarget renderTarget) { m_CurrentRenderTarget = renderTarget; }
        void SetBlendingMode(BlendingMode blendingMode);
        void SetClearColor(const Color& clearColor);
        void Clear();
        void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
        void Begin();
        void SubmitSpriteData(const Array<Vector3, 4>& vertexPositions, const Array<Color, 4>& vertexColors, const SharedPtr<Texture2D>& texture, const Array<Vector2, 4>& vertexUV);
        void End();

    private:
        Renderer(GraphicsAPI api);
        ~Renderer() = default;
        
        Matrix4 m_ProjectionViewMatrix;
        RenderTarget m_CurrentRenderTarget = RenderTarget::Default;

        SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;

        // Sprite Rendering
        SharedPtr<Shader> m_SpriteShader;
        UniquePtr<SpriteBatchRenderer> m_SpriteRenderer;
    };
}