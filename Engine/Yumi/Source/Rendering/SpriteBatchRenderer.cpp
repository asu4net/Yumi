#include "SpriteBatchRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "FrameBuffer.h"
#include "RendererTexture2D.h"

namespace Yumi
{
    static constexpr uint32_t s_VerticesPerSprite = 4;
    static constexpr uint32_t s_IndicesPerSprite = 6;

    SpriteBatchRenderer::SpriteBatchRenderer(const SharedPtr<RendererAPI> API, SharedPtr<RenderCommandQueue> commandQueue, const SharedPtr<FrameBuffer> frameBuffer, uint32_t maxSprites, uint32_t maxTextureSlots)
        : m_RendererAPI(API)
        , m_CommandQueue(commandQueue)
        , m_FrameBuffer(frameBuffer)
        , m_MaxSprites(maxSprites)
        , m_MaxTextureSlots(maxTextureSlots)
        , m_MaxVertices(maxSprites * s_VerticesPerSprite)
        , m_Vertices(new SpriteVertex[m_MaxVertices])
        , m_LastVertex(m_Vertices)
        , m_Textures(maxTextureSlots)
    {
        CreateWhiteTexture();
        CreateTextureSlots();
        CreateRenderObjects();
    }

    SpriteBatchRenderer::~SpriteBatchRenderer()
    {
        delete[] m_Vertices;
    }

    void SpriteBatchRenderer::Begin(RenderData& renderData)
    {
        m_CurrentRenderTarget = renderData.CurrentRenderTarget;
        renderData.SpriteShader->Bind();
        renderData.SpriteShader->SetUniformMat4("u_ProjectionViewMatrix", renderData.ProjectionViewMat4);
        renderData.SpriteShader->SetUniformIntArray("u_TextureSlots", &m_TextureSlots.front(), m_MaxTextureSlots);

        StartBatch();
    }

    void SpriteBatchRenderer::SubmitSpritePrimitive(const SpritePrimitive& sprite)
    {
        for (int i = 0; i < 4; i++)
        {
            m_LastVertex->Position = sprite.VertexPositions[i];
            m_LastVertex->TintColor = sprite.VertexColors[i];
            m_LastVertex->UV = sprite.VertexUV[i];
            m_LastVertex->TextureSlot = CalculateTextureSlot(sprite.Texture);

            m_LastVertex++;
        }

        m_IndexCount += 6;
        m_SpriteCount++;
    }

    void SpriteBatchRenderer::End()
    {
        Flush();
    }

    void SpriteBatchRenderer::StartBatch()
    {
        m_LastVertex = m_Vertices;
        m_SpriteCount = 0;
        m_IndexCount = 0;
        m_LastTextureSlot = 1;
    }

    void SpriteBatchRenderer::Flush()
    {
        if (const uint32_t vertexDataSize = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(m_LastVertex) -
            reinterpret_cast<uint8_t*>(m_Vertices)))
        {
            m_VertexBuffer->SetData(m_Vertices, vertexDataSize);

            for (uint32_t i = 0; i < m_LastTextureSlot; i++)
                m_Textures[i]->Bind(i);

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

    void SpriteBatchRenderer::CreateWhiteTexture()
    {
        Texture2DSettings settings;
        settings.Width = 1;
        settings.Height = 1;
        settings.Channels = 4;

        m_WhiteTexture = RendererTexture2D::Create(m_RendererAPI->GetGraphicsAPI());
        constexpr uint32_t whiteTextureData = 0xffffffff;
        m_WhiteTexture->UploadToGPU(settings, &whiteTextureData);
        m_Textures[0] = m_WhiteTexture;
    }

    void SpriteBatchRenderer::CreateTextureSlots()
    {
        DynamicArray<int32_t>* slots = const_cast<DynamicArray<int32_t>*>(&m_TextureSlots);
        slots->reserve(m_MaxTextureSlots);
        for (uint32_t i = 0; i < m_MaxTextureSlots; i++)
            slots->push_back(i);
    }

    void SpriteBatchRenderer::CreateRenderObjects()
    {
        const GraphicsAPI API = m_RendererAPI->GetGraphicsAPI();

        m_VertexArray = VertexArray::Create(API);
        m_VertexBuffer = VertexBuffer::Create(API, m_MaxVertices * sizeof(SpriteVertex));

        m_VertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"   },
            {ShaderDataType::Float4, "a_Color"      },
            {ShaderDataType::Float2, "a_UV"         },
            {ShaderDataType::Float , "a_TextureSlot"}
        });

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        const uint32_t maxIndices = m_MaxSprites * s_IndicesPerSprite;

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

    int SpriteBatchRenderer::CalculateTextureSlot(const SharedPtr<RendererTexture2D>& texture)
    {
        int textureSlot = 0;

        if (texture)
        {
            // Search existing texture
            for (uint32_t i = 1; i < m_LastTextureSlot; i++)
            {
                if (m_Textures[i]->GetTextureID() == texture->GetTextureID())
                {
                    textureSlot = i;
                    break;
                }
            }

            // If not exists save the new texture
            if (textureSlot == 0)
            {
                m_Textures[m_LastTextureSlot] = texture;
                textureSlot = m_LastTextureSlot;
                m_LastTextureSlot++;
            }
        }

        return textureSlot;
    }
}