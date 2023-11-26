#include "Renderer.h"
#include "RendererShader.h"
#include "RendererTexture2D.h"
#include "RawShaderStrings.h"

namespace Yumi
{
    Renderer::Renderer(GraphicsAPI api)
        : m_RendererAPI(RendererAPI::Create(api))
        , m_CommandQueue(CreateSharedPtr<RenderCommandQueue>())
        , m_SpriteShader(RendererShader::Create(api))
        , m_SpriteRenderer(CreateUniquePtr<SpriteBatchRenderer>(m_RendererAPI, m_CommandQueue))
    {
        YLOG_TRACE("Renderer created!\n");
        
        // Default settings
        SetBlendingModeEnabled(true);
        SetBlendingMode(BlendingMode::Alpha);
        SetClearColor(Color::DarkGrey);

        m_SpriteShader->Compile(g_SpriteVertexShaderSource, g_SpriteFragmentShaderSource);
    }

    Renderer::~Renderer()
    {
        YLOG_TRACE("Renderer destroyed!\n");
    }

    void Renderer::SetBlendingModeEnabled(bool enabled)
    {
        m_CommandQueue->Submit<SetBlendingEnabledCommand>(m_RendererAPI, enabled);
    }

    void Renderer::SetBlendingMode(BlendingMode blendingMode)
    {
        m_CommandQueue->Submit<SetBlendingModeCommand>(m_RendererAPI, blendingMode);
    }

    void Renderer::SetDepthTestEnabled(bool enabled)
    {
        m_CommandQueue->Submit<SetDepthTestEnabledCommand>(m_RendererAPI, enabled);
    }

    void Renderer::SetClearColor(const Color& clearColor)
    {
        m_CommandQueue->Submit<SetClearColorCommand>(m_RendererAPI, clearColor);
    }

    void Renderer::Clear()
    {
        m_CommandQueue->Submit<ClearCommand>(m_RendererAPI);
    }

    void Renderer::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
    {
        m_CommandQueue->Submit<SetViewPortCommand>(m_RendererAPI, x, y, width, height);
    }

    void Renderer::SubmitSprite(const Array<Vector3, 4>& vertexPositions, const Array<Color, 4>& vertexColors,
        const Array<Vector2, 4>& vertexUV, Id rendererTextureId)
    {
        SharedPtr<RendererTexture2D> texture = rendererTextureId != 0 ? m_Textures[rendererTextureId] : nullptr;

        SpritePrimitive spritePrimitive{
            vertexPositions,
            vertexColors,
            vertexUV,
            texture
        };

        m_SpritePrimitivesDrawList.emplace_back(spritePrimitive);
    }

    void Renderer::DrawPrimitives()
    {
        SpriteBatchRenderer::RenderData spriteRenderData{
            m_CurrentRenderTarget,
            m_ProjectionViewMatrix,
            m_SpriteShader
        };

        m_SpriteRenderer->Begin(spriteRenderData);

        for (const SpritePrimitive& sprite : m_SpritePrimitivesDrawList)
        {
            m_SpriteRenderer->SubmitSpritePrimitive(sprite);
        }

        m_SpritePrimitivesDrawList.clear();
        m_SpriteRenderer->End();
    }

    Id Renderer::CreateTexture2D(const Texture2DSettings& settings, const void* data)
    {
        Id id;
        SharedPtr<RendererTexture2D> texture = RendererTexture2D::Create(m_RendererAPI->GetGraphicsAPI());
        texture->UploadToGPU(settings, data);
        m_Textures[id] = texture;
        return id;
    }

    RendererTexture2D& Renderer::GetTexture2D(Id id)
    {
        YCHECK(m_Textures.count(id), "Invalid id!");
        return *m_Textures[id];
    }

    void Renderer::DestroyTexture2D(Id id)
    {
        YCHECK(m_Textures.count(id), "Invalid id!");
        SharedPtr<RendererTexture2D> texture = m_Textures[id];
        m_Textures.erase(id);
    }
}