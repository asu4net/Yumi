#include "Renderer.h"
#include "Shader.h"
#include "Asset\AssetManager.h"

namespace Yumi
{
    Renderer::Renderer(GraphicsAPI api)
        : m_RendererAPI(RendererAPI::Create(api))
        , m_CommandQueue(CreateSharedPtr<RenderCommandQueue>())
        , m_SpriteShader(AssetManager::GetInstance().GetAssetByName<Shader>(Graphics::GetSpriteShaderName()).Get())
        , m_SpriteRenderer(CreateUniquePtr<SpriteBatchRenderer>(m_RendererAPI, m_CommandQueue))
    {
        m_CommandQueue->Submit<SetBlendingEnabledCommand>(m_RendererAPI, true);
        m_CommandQueue->Submit<SetClearColorCommand>(m_RendererAPI, Color::DarkGrey);
    }

    void Renderer::SetBlendingMode(BlendingMode blendingMode)
    {
        m_CommandQueue->Submit<SetBlendingModeCommand>(m_RendererAPI, blendingMode);
    }

    void Renderer::SetClearColor(const Color& clearColor)
    {
        m_CommandQueue->Submit<SetClearColorCommand>(m_RendererAPI, clearColor);
    }

    void Renderer::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
    {
        m_CommandQueue->Submit<SetViewPortCommand>(m_RendererAPI, x, y, width, height);
    }

    void Renderer::Update()
    {
        SpriteBatchRenderer::RenderData data;
        data.CurrentRenderTarget = m_CurrentRenderTarget;
        data.ProjectionViewMat4 = m_ProjectionViewMatrix;
        data.SpriteShader = m_SpriteShader;

        m_CommandQueue->Submit<ClearCommand>(m_RendererAPI);

        m_SpriteRenderer->Begin(data);

        for (const auto& [id, sprite] : m_IdSpriteMap)
        {
            m_SpriteRenderer->SubmitSpriteData(sprite.GetVertexPositions(), sprite.GetVertexColors(), sprite.GetTexture(), sprite.GetVertexUVs());
        }
        
        m_SpriteRenderer->End();
    }
}