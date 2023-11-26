#pragma once
#include "RenderCommandQueue.h"
#include "RendererAPI.h"

namespace Yumi
{
    class FrameBuffer;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;
    class RendererShader;

    struct CirclePrimitive
    {
        Matrix4 Transform;
        Color TintColor;
        float Thickness;
        float Fade;
    };

    class CircleBatchRenderer
    {
    public:
        struct CircleVertex
        {
            Vector3 Position;
            Vector3 LocalPosition;
            Color TintColor;
            float Thickness = 0;
            float Fade = 0;
        };
        
        struct RenderData
        {
            RenderTarget CurrentRenderTarget;
            Matrix4 ProjectionViewMat4;
            SharedPtr<RendererShader> CircleShader;
        };

        CircleBatchRenderer(const SharedPtr<RendererAPI> API,
            SharedPtr<RenderCommandQueue> commandQueue,
            const SharedPtr<FrameBuffer> frameBuffer = nullptr,
            uint32_t maxCircles = 3000);

        ~CircleBatchRenderer();

        void Begin(RenderData& renderData);
        void SubmitCirclePrimitive(const CirclePrimitive& circlePrimitive);
        void End();

    private:
        void CreateRenderObjects();
        void StartBatch();
        void Flush();

        const SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;
        SharedPtr<FrameBuffer> m_FrameBuffer;

        SharedPtr<VertexArray> m_VertexArray;
        SharedPtr<VertexBuffer> m_VertexBuffer;
        SharedPtr<IndexBuffer> m_IndexBuffer;
    
        // Per batch data
        const uint32_t m_MaxCircles;
        const uint32_t m_MaxVertices;

        RenderTarget m_CurrentRenderTarget = RenderTarget::Default;
        uint32_t m_CircleCount = 0;
        uint32_t m_IndexCount = 0;
        CircleVertex* m_Vertices;
        CircleVertex* m_LastVertex;
    };
}