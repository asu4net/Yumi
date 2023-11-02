#pragma once
#include "RenderCommandQueue.h"
#include "RendererAPI.h"

namespace Yumi
{
    class FrameBuffer;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class Texture2D;
    class Sprite;

    class Renderer2D
    {
    public:
        struct SpriteVertex
        {
            Vector3 Position;
            Color TintColor;
            Vector2 UV;
            Vector2 UVScale;
            uint32_t TextureSlot;
        };

        enum class RenderTarget
        {
            Default, FrameBuffer
        };

        struct RenderData
        {
            RenderTarget CurrentRenderTarget;
            Matrix4 ProjectionViewMat4;
            SharedPtr<Shader> SpriteShader;
        };

        Renderer2D(const SharedPtr<RendererAPI> API, 
            SharedPtr<RenderCommandQueue> commandQueue, 
            const SharedPtr<FrameBuffer> frameBuffer = nullptr,
            uint32_t maxSprites = 3000,
            uint32_t maxTextureSlots = 32);

        ~Renderer2D();

        void Begin(RenderData& renderData);
        void SubmitSprite(const SharedPtr<Sprite>& sprite);
        void End();

    private:
        void CreateWhiteTexture();
        void CreateTextureSlots();
        void CreateRenderObjects();
        int CalculateTextureSlot(const SharedPtr<Texture2D>& texture);
        void StartBatch();
        void Flush();
        
        const SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;
        SharedPtr<FrameBuffer> m_FrameBuffer;

        SharedPtr<VertexArray> m_VertexArray;
        SharedPtr<VertexBuffer> m_VertexBuffer;
        SharedPtr<IndexBuffer> m_IndexBuffer;
        SharedPtr<Texture2D> m_WhiteTexture;

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
        DynamicArray<SharedPtr<Texture2D>> m_Textures;
    };
}