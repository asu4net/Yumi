#pragma once
#include "SpriteBatchRenderer.h"
#include "Sprite.h"

namespace Yumi
{
    class Shader;

    class Renderer : public Singleton<Renderer>
    {
        YSINGLETON_FRIEND(Renderer)
    public:
        void SetProjectionViewMatrix(const Matrix4& projectionViewMatrix) { m_ProjectionViewMatrix = projectionViewMatrix; }
        void SetRenderTarget(RenderTarget renderTarget) { m_CurrentRenderTarget = renderTarget; }
        void SetBlendingMode(BlendingMode blendingMode);
        void SetClearColor(const Color& clearColor);
        void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);

        template<typename ...TArgs>
        Id CreateSprite(TArgs&& ...args)
        {
            Id id;
            m_IdSpriteMap[(uint64_t)id] = Sprite(std::forward<TArgs>(args)...);
            return id;
        }

        Sprite& GetSprite(Id id)
        {
            YCHECK(m_IdSpriteMap.count((uint64_t)id), "Unregistered sprite id");
            return m_IdSpriteMap[(uint64_t)id];
        }

        void DestroySprite(Id id)
        {
            YCHECK(m_IdSpriteMap.count((uint64_t)id), "Unregistered sprite id");
            m_IdSpriteMap.erase((uint64_t)id);
        }

        void Update();

    private:
        Renderer(GraphicsAPI api);
        ~Renderer() = default;
        
        Matrix4 m_ProjectionViewMatrix;
        RenderTarget m_CurrentRenderTarget = RenderTarget::Default;

        SharedPtr<RendererAPI> m_RendererAPI;
        SharedPtr<RenderCommandQueue> m_CommandQueue;

        // Sprite Rendering
        SharedPtr<Shader> m_SpriteShader;
        UniquePtr<SpriteBatchRenderer> m_SpriteRenderer;
        OrderedMap<uint64_t, Sprite> m_IdSpriteMap;
    };
}