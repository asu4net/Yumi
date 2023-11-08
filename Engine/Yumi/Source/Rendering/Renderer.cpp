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

    void Renderer::Begin()
    {
        SpriteBatchRenderer::RenderData spriteRenderData{
            m_CurrentRenderTarget,
            m_ProjectionViewMatrix,
            m_SpriteShader
        };

        m_SpriteRenderer->Begin(spriteRenderData);
    }

    void Renderer::SubmitSpriteData(const Array<Vector3, 4>& vertexPositions, const Array<Color, 4>& vertexColors, const SharedPtr<Texture2D>& texture, const Array<Vector2, 4>& vertexUV)
    {
        m_SpriteRenderer->SubmitSpriteData(vertexPositions, vertexColors, texture, vertexUV);
    }

    void Renderer::End()
    {
        m_SpriteRenderer->End();
    }

}