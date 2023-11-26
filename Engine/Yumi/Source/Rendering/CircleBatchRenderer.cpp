#include "CircleBatchRenderer.h"
#include "Sprite.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "FrameBuffer.h"
#include "RendererShader.h"

namespace Yumi
{
    static constexpr uint32_t s_VerticesPerCircle = 4;
    static constexpr uint32_t s_IndicesPerCircle = 6;

    CircleBatchRenderer::CircleBatchRenderer(const SharedPtr<RendererAPI> API, SharedPtr<RenderCommandQueue> commandQueue, const SharedPtr<FrameBuffer> frameBuffer, uint32_t maxCircles)
        : m_RendererAPI(API)
        , m_CommandQueue(commandQueue)
        , m_FrameBuffer(frameBuffer)
        , m_MaxCircles(maxCircles)
        , m_MaxVertices(maxCircles * s_VerticesPerCircle)
        , m_Vertices(new CircleVertex[m_MaxVertices])
        , m_LastVertex(m_Vertices)
    {
        CreateRenderObjects();
    }

    CircleBatchRenderer::~CircleBatchRenderer()
    {
        delete[] m_Vertices;
    }

    void CircleBatchRenderer::Begin(RenderData& renderData)
    {
        m_CurrentRenderTarget = renderData.CurrentRenderTarget;
        renderData.CircleShader->Bind();
        renderData.CircleShader->SetUniformMat4("u_ProjectionViewMatrix", renderData.ProjectionViewMat4);
        
        StartBatch();
    }

    void CircleBatchRenderer::SubmitCirclePrimitive(const CirclePrimitive& circlePrimitive)
    {
        Array<Vector3, 4> localVertexPositions = Sprite::GetDefaultSpriteVertexPositions();

        for (int i = 0; i < 4; i++)
        {
            m_LastVertex->Position = Vector4(localVertexPositions[i], 1.f) * circlePrimitive.Transform;
            m_LastVertex->LocalPosition = localVertexPositions[i];
            m_LastVertex->TintColor = circlePrimitive.TintColor;
            m_LastVertex->Thickness = circlePrimitive.Thickness;
            m_LastVertex->Fade = circlePrimitive.Fade;

            m_LastVertex++;
        }

        m_IndexCount += 6;
        m_CircleCount++;
    }

    void CircleBatchRenderer::End()
    {
        Flush();
    }
    
    void CircleBatchRenderer::StartBatch()
    {
        m_LastVertex = m_Vertices;
        m_CircleCount = 0;
        m_IndexCount = 0;
    }

    void CircleBatchRenderer::Flush()
    {
        if (const uint32_t vertexDataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(m_LastVertex) -
            reinterpret_cast<uint8_t*>(m_Vertices)))
        {
            m_VertexBuffer->SetData(m_Vertices, vertexDataSize);
            m_CommandQueue->Submit<DrawElementsCommand>(m_RendererAPI, m_VertexArray, m_IndexCount);
        }

        if (m_CurrentRenderTarget == RenderTarget::FrameBuffer)
        {
            YCHECK(m_FrameBuffer, "Frame buffer is required!");
            m_FrameBuffer->Bind();
        }

        while (!m_CommandQueue->IsEmpty())
            m_CommandQueue->ExecuteNext();

        if (m_CurrentRenderTarget == RenderTarget::FrameBuffer)
            m_FrameBuffer->Unbind();
    }

    void CircleBatchRenderer::CreateRenderObjects()
    {
        const GraphicsAPI API = m_RendererAPI->GetGraphicsAPI();

        m_VertexArray = VertexArray::Create(API);
        m_VertexBuffer = VertexBuffer::Create(API, m_MaxVertices * sizeof(CircleVertex));

        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"        },
            {ShaderDataType::Float3, "a_LocalPosition"   },
            {ShaderDataType::Float4, "a_Color"           },
            {ShaderDataType::Float , "a_Thickness"       },
            {ShaderDataType::Float , "a_Fade"            }
        });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        const uint32_t maxIndices = m_MaxCircles * s_IndicesPerCircle;

        uint32_t* indices = new uint32_t[maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        m_IndexBuffer = IndexBuffer::Create(API, indices, maxIndices);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        delete[] indices;
    }
}