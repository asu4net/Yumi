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
        , m_CircleShader(RendererShader::Create(api))
        , m_CircleRenderer(CreateUniquePtr<CircleBatchRenderer>(m_RendererAPI, m_CommandQueue))
    {
        YLOG_TRACE("Renderer created!\n");
        
        // Default settings
        SetBlendingModeEnabled(true);
        SetBlendingMode(BlendingMode::Alpha);
        SetClearColor(Color::DarkGrey);

        m_SpriteShader->Compile(g_SpriteVertexShaderSource, g_SpriteFragmentShaderSource);
        m_CircleShader->Compile(g_CircleVertexShaderSource, g_CircleFragmentShaderSource);
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

    void Renderer::SubmitSprite(const SpritePrimitive& sprite)
    {
        m_SpritePrimitivesDrawList.emplace_back(sprite);
    }

    void Renderer::SubmitLine2D(const Vector2& start, const Vector2& end, const Vector2& normal, 
        const Color& color, float thickness)
    {
        Array<Color, 4> vertexColors;
        for (Color& vertexColor : vertexColors) vertexColor = color;
        
        Array<Vector3, 4> vertexPositions;
        const float halfThickness = thickness / 2;
        vertexPositions[0] = start + normal *  halfThickness;
        vertexPositions[1] = end   + normal *  halfThickness;
        vertexPositions[2] = end   + normal * -halfThickness;
        vertexPositions[3] = start + normal * -halfThickness;

        SpritePrimitive spritePrimitive{
            vertexPositions,
            vertexColors,
            Sprite::GetDefaultSpriteUVs(),
            nullptr
        };

        SubmitSprite(spritePrimitive);
    }

    void Renderer::SubmitCircle(const CirclePrimitive& circle)
    {
        m_CirclePrimitivesDrawList.push_back(circle);
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
            m_SpriteRenderer->SubmitSpritePrimitive(sprite);
        }

        m_SpritePrimitivesDrawList.clear();
        m_SpriteRenderer->End();

        // Circle Rendering

        CircleBatchRenderer::RenderData circleRenderData{
            m_CurrentRenderTarget,
            m_ProjectionViewMatrix,
            m_CircleShader
        };

        m_CircleRenderer->Begin(circleRenderData);

        for (const CirclePrimitive& circle : m_CirclePrimitivesDrawList)
        {
            m_CircleRenderer->SubmitCirclePrimitive(circle);
        }

        m_CirclePrimitivesDrawList.clear();
        m_CircleRenderer->End();
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