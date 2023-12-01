#pragma once
#include "RenderCommandQueue.h"
#include "RendererAPI.h"
#include "Sprite.h"

namespace Yumi
{
    class FrameBuffer;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class RendererTexture2D;
    class RendererShader;

    struct SpriteVertex
    {
        Vector3  Position = Vector2::Zero;
        Color    TintColor = Color::White;
        Vector2  UV = Vector2::One;
        uint32_t TextureSlot = 0;
        uint32_t Shape = 0;
        Vector3  LocalPosition = Vector2::Zero;
        float    Thickness = .05f;
        float    Fade = .01f;
        Vector2  Bounds = Vector2::Zero;
        Color    RectColor = Color::Orange;
    };

    class SpriteBatchRenderer
    {
    public:
        struct RenderData
        {
            RenderTarget CurrentRenderTarget;
            Matrix4 ProjectionViewMat4;
            SharedPtr<RendererShader> SpriteShader;
        };

        SpriteBatchRenderer(const SharedPtr<RendererAPI> API, 
            SharedPtr<RenderCommandQueue> commandQueue, 
            const SharedPtr<FrameBuffer> frameBuffer = nullptr,
            uint32_t maxSprites = 3000,
            uint32_t maxTextureSlots = 32);

        ~SpriteBatchRenderer();

        int CalculateTextureSlot(const SharedPtr<RendererTexture2D>& texture);
        void Begin(RenderData& renderData);
        void SubmitSpriteVertexData(const Array<SpriteVertex, 4>& spriteVertices);
        void End();

    private:
        void CreateWhiteTexture();
        void CreateTextureSlots();
        void CreateRenderObjects();
        void StartBatch();
        void Flush();
        
        const SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;
        SharedPtr<FrameBuffer> m_FrameBuffer;

        SharedPtr<VertexArray> m_VertexArray;
        SharedPtr<VertexBuffer> m_VertexBuffer;
        SharedPtr<IndexBuffer> m_IndexBuffer;
        SharedPtr<RendererTexture2D> m_WhiteTexture;

        // Per batch data
        const uint32_t m_MaxSprites;
        const uint32_t m_MaxTextureSlots;
        const uint32_t m_MaxVertices;
        const DynamicArray<int32_t> m_TextureSlots;

        RenderTarget m_CurrentRenderTarget = RenderTarget::Default;
        uint32_t m_SpriteCount = 0;
        uint32_t m_IndexCount = 0;
        uint32_t m_LastTextureSlot = 1;
        SpriteVertex* m_Vertices;
        SpriteVertex* m_LastVertex;
        DynamicArray<SharedPtr<RendererTexture2D>> m_Textures;
    };
}