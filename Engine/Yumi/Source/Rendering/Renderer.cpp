#include "Renderer.h"
#include "RendererShader.h"
#include "RendererTexture2D.h"
#include "RawShaderStrings.h"
#include "SpriteBatchRenderer.h"
#include "SpritePrimitive.h"
#include "Texture2D.h"

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

    void Renderer::SubmitSpritePrimitive(const SpritePrimitive& sprite)
    {
        m_SpritePrimitivesDrawList.emplace_back(sprite);
    }

    void Renderer::DrawPrimitives()
    {
        // Sprite Rendering

        SpriteBatchRenderer::RenderData spriteRenderData{
            m_CurrentRenderTarget,
            m_ProjectionViewMatrix,
            m_SpriteShader
        };

        m_SpriteRenderer->Begin(spriteRenderData);

        for (const SpritePrimitive& sprite : m_SpritePrimitivesDrawList)
        {
            SharedPtr<RendererTexture2D> texture = nullptr;

            if (sprite.SpriteSource)
            {
                AssetRef textureRef = sprite.SpriteSource->GetTextureRef();
                YCHECK(textureRef.IsValid(), "Texture ref should be valid!");
                const Id textureId = textureRef.GetAs<Texture2D>().GetRendererId();
                texture = GetTexture2D(textureId);
            }

            m_SpriteRenderer->SubmitSpriteVertexData(
                sprite.GetVertexPositions(),
                sprite.GetVertexColors(),
                sprite.GetVertexUV(),
                texture,
                (uint32_t) sprite.Shape,
                sprite.GetLocalVertexPositions(),
                sprite.Thickness,
                sprite.Fade,
                sprite.Bounds
            );
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

    SharedPtr<RendererTexture2D> Renderer::GetTexture2D(Id id)
    {
        YCHECK(m_Textures.count(id), "Invalid id!");
        return m_Textures[id];
    }

    void Renderer::DestroyTexture2D(Id id)
    {
        YCHECK(m_Textures.count(id), "Invalid id!");
        SharedPtr<RendererTexture2D> texture = m_Textures[id];
        m_Textures.erase(id);
    }
    
    Id Renderer::CreateShader(const char* vertexSource, const char* fragmentSource)
    {
        Id id;
        SharedPtr<RendererShader> shader = RendererShader::Create(m_RendererAPI->GetGraphicsAPI());
        shader->Compile(vertexSource, fragmentSource);
        m_Shaders[id] = shader;
        return id;
    }

    SharedPtr<RendererShader> Renderer::GetShader(Id id)
    {
        YCHECK(m_Shaders.count(id), "Invalid id!");
        return m_Shaders[id];
    }

    void Renderer::DestroyShader(Id id)
    {
        YCHECK(m_Shaders.count(id), "Invalid id!");
        SharedPtr<RendererShader> texture = m_Shaders[id];
        m_Shaders.erase(id);
    }
}