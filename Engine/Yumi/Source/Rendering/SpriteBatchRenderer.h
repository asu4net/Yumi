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

    struct SpritePrimitive
    {
        Array<Vector3, 4> VertexPositions;
        Array<Color, 4> VertexColors;
        Array<Vector2, 4> VertexUV = Sprite::GetDefaultSpriteUVs();
        SharedPtr<RendererTexture2D> Texture = nullptr;
    };

    class SpriteBatchRenderer
    {
    public:
        struct SpriteVertex
        {
            Vector3 Position;
            Color TintColor;
            Vector2 UV;
            uint32_t TextureSlot;
        };

        struct RenderData
        {
            RenderTarget CurrentRenderTarget;
            Matrix4 ProjectionViewMat4;
            SharedPtr<Shader> SpriteShader;
        };

        SpriteBatchRenderer(const SharedPtr<RendererAPI> API, 
            SharedPtr<RenderCommandQueue> commandQueue, 
            const SharedPtr<FrameBuffer> frameBuffer = nullptr,
            uint32_t maxSprites = 3000,
            uint32_t maxTextureSlots = 32);

        ~SpriteBatchRenderer();

        void Begin(RenderData& renderData);
        
        void SubmitSpritePrimitive(const SpritePrimitive& sprite);
        
        void End();

    private:
        void CreateWhiteTexture();
        void CreateTextureSlots();
        void CreateRenderObjects();
        int CalculateTextureSlot(const SharedPtr<RendererTexture2D>& texture);
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