#include "SpriteSystem.h"
#include "Rendering\Renderer.h"
#include "..\Components\SpriteComponent.h"
#include "..\Components\TransformComponent.h"
#include "Rendering\Texture2D.h"
#include "Core\Engine.h"

namespace Yumi
{
    SpriteSystem::SpriteSystem(const SharedPtr<Scene>& scene)
        : System(scene)
    {
        GetRegistry().on_construct<SpriteComponent>().connect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }
    
    void SpriteSystem::OnSpriteComponentAdded(entt::registry&, const entt::entity entity)
    {
        Actor actor = GetActorFromEntity(entity);
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.TransformMatrix = actor.GetTransform().GetMatrix();
        SpriteStatics::UpdateVertexPositions(actor);
        SpriteStatics::UpdateVertexUVs(actor);
        SpriteStatics::SetTintColor(actor, sprite.TintColor);
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

        view.each([&](entt::entity entity, const TransformComponent&, const SpriteComponent& sprite) {
            
            Actor spriteActor = GetActorFromEntity(entity);
            SpriteComponent& spriteComponent = spriteActor.Get<SpriteComponent>();
            
            if (!spriteComponent.IsVisible)
                return;

            SpriteStatics::UpdateTransformMatrix(spriteActor);
            
            const SharedPtr<Texture2D> texture = sprite.SpriteAssetRef.IsValid() ? 
                sprite.SpriteAssetRef.GetAs<Sprite>().GetTextureRef().GetPtrAs<Texture2D>().lock() : nullptr;

            SpritePrimitive spritePrimitive{
                sprite.VertexPositions,
                sprite.VertexColors,
                sprite.VertexUVs,
                texture
            };

            renderer.SubmitSpritePrimitive(spritePrimitive);
        });
    }

    void SpriteSystem::OnFinish()
    {
        GetRegistry().on_construct<SpriteSystem>().disconnect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }
}