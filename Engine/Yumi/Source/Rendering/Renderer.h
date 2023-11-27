#pragma once

namespace Yumi
{
    struct SpritePrimitive;
    struct Texture2DSettings;
    class RendererShader;
    class RendererTexture2D;
    class RendererAPI;
    class RenderCommandQueue;
    class SpriteBatchRenderer;

    class Renderer
    {
    public:
        Renderer(GraphicsAPI api);
        ~Renderer();
        
        void SetSpriteShader(const SharedPtr<RendererShader> spriteShader) { m_SpriteShader = spriteShader; }
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

        Id CreateTexture2D(const Texture2DSettings& settings, const void* data);
        SharedPtr<RendererTexture2D> GetTexture2D(Id id);
        void DestroyTexture2D(Id id);

        Id CreateShader(const char* vertexSource, const char* fragmentSource);
        SharedPtr<RendererShader> GetShader(Id id);
        void DestroyShader(Id id);

    private:
        Matrix4 m_ProjectionViewMatrix;
        RenderTarget m_CurrentRenderTarget = RenderTarget::Default;

        SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;

        Map<Id, SharedPtr<RendererTexture2D>> m_Textures;
        Map<Id, SharedPtr<RendererShader>> m_Shaders;

        // Sprite Rendering
        SharedPtr<RendererShader> m_SpriteShader;
        UniquePtr<SpriteBatchRenderer> m_SpriteRenderer;
        DynamicArray<SpritePrimitive> m_SpritePrimitivesDrawList;
    };
}