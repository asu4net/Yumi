#include "SpriteSystem.h"
#include "Rendering\Renderer.h"
#include "Scene\Components\SpriteComponent.h"
#include "Scene\Components\TransformComponent.h"
#include "Rendering\RendererTexture2D.h"
#include "Core\Engine.h"
#include "Rendering\Texture2D.h"

namespace Yumi
{
    static void UpdateVertexPositions(SpriteComponent& spriteComponent)
    {
        const Array<Vector3, 4>& localVertexPositions = spriteComponent.SpriteAssetRef.IsValid() ?
            spriteComponent.SpriteAssetRef.GetAs<Sprite>().GetVertexPositions() : Sprite::GetDefaultSpriteVertexPositions();

        for (uint32_t i = 0; i < 4; i++)
        {
            spriteComponent.VertexPositions[i] = Vector4(localVertexPositions[i], 1.f) * spriteComponent.TransformMatrix;
            spriteComponent.VertexPositions[i].x *= spriteComponent.Size.x;
            spriteComponent.VertexPositions[i].y *= spriteComponent.Size.y;
        }
    }

    static void UpdateVertexUVs(SpriteComponent& spriteComponent)
    {
        spriteComponent.VertexUVs = spriteComponent.SpriteAssetRef.IsValid() ?
            spriteComponent.SpriteAssetRef.GetAs<Sprite>().GetVertexUVs() : Sprite::GetDefaultSpriteUVs();

        for (Vector2& vertexUV : spriteComponent.VertexUVs)
        {
            vertexUV.x *= spriteComponent.UVScale.x;
            vertexUV.y *= spriteComponent.UVScale.y;
        }

        Sprite::FlipVertexUVs(spriteComponent.FlipMode, spriteComponent.VertexUVs);
    }
    
    static void UpdateVertexColors(SpriteComponent& spriteComponent)
    {
        for (Color& vertexColor : spriteComponent.VertexColors)
            vertexColor = spriteComponent.TintColor;
    }

    static void UpdateSpriteVertexData(const Matrix4& transformMatrix, SpriteComponent& spriteComponent)
    {
        spriteComponent.TransformMatrix = transformMatrix;
        UpdateVertexPositions(spriteComponent);
        UpdateVertexUVs(spriteComponent);
        UpdateVertexColors(spriteComponent);
    }

    SpriteSystem::SpriteSystem(const SharedPtr<Scene>& scene)
        : System(scene)
    {
        GetRegistry().on_construct<SpriteComponent>().connect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }
    
    void SpriteSystem::OnSpriteComponentAdded(entt::registry&, const entt::entity entity)
    {
        Actor actor = GetActorFromEntity(entity);
        UpdateSpriteVertexData(actor.GetTransform().GetMatrix(), actor.Get<SpriteComponent>());
    }

    void SpriteSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<TransformComponent, SpriteComponent>();

        GetRegistry().sort<SpriteComponent>([](const SpriteComponent& a, const SpriteComponent& b)
        {
            return a.OrderInLayer < b.OrderInLayer;
        });

        Renderer& renderer = GetRenderer();
        
        renderer.Clear();

        view.each([&](entt::entity entity, const TransformComponent& transformComponent, const SpriteComponent& sprite) {
            
            Actor spriteActor = GetActorFromEntity(entity);
            SpriteComponent& spriteComponent = spriteActor.Get<SpriteComponent>();
            
            if (!spriteComponent.IsVisible)
                return;

            Actor actor = GetActorFromEntity(entity);
            UpdateSpriteVertexData(transformComponent.GetMatrix(), spriteComponent);
            
            const SharedPtr<Texture2D> texture = sprite.SpriteAssetRef.IsValid() ? 
                sprite.SpriteAssetRef.GetAs<Sprite>().GetTextureRef().GetPtrAs<Texture2D>().lock() : nullptr;

            const Id id = texture ? texture->GetRendererId() : 0;

            SpritePrimitive spritePrimitive{
                sprite.VertexPositions,
                sprite.VertexColors,
                sprite.VertexUVs,
                id != 0 ? renderer.GetTexture2D(id) : nullptr
            };

            renderer.SubmitSprite(spritePrimitive);
        });
    }

    void SpriteSystem::OnFinish()
    {
        GetRegistry().on_construct<SpriteSystem>().disconnect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }
}