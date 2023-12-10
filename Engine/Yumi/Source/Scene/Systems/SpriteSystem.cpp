#include "SpriteSystem.h"
#include "Rendering\Renderer.h"
#include "Scene\Components\SpriteComponent.h"
#include "Scene\Components\TransformComponent.h"
#include "Core\Engine.h"
#include "Rendering\SpritePrimitive.h"

namespace Yumi
{
    SpriteSystem::SpriteSystem(Scene* scene)
        : System(scene)
    {
        GetRegistry().on_construct<SpriteComponent>().connect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }

    void SpriteSystem::OnSpriteComponentAdded(entt::registry&, const entt::entity entity)
    {
        Actor spriteActor = GetActorFromEntity(entity);
        SpriteComponent& spriteComponent = spriteActor.Get<SpriteComponent>();
        spriteComponent.SpriteAssetRef.Retarget();
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
            
            if (!sprite.IsVisible)
                return;

            SpritePrimitive primitive;
            primitive.FlipMode = sprite.FlipMode;
            primitive.TransformMatrix = transformComponent.GetMatrix();
            primitive.TintColor = sprite.TintColor;
            primitive.UVScale = sprite.UVScale;
            primitive.Size = sprite.Size;

            primitive.SpriteRef = sprite.SpriteAssetRef.IsValid() ? 
                sprite.SpriteAssetRef.GetPtrAs<Sprite>().lock() : nullptr;
            primitive.Source = sprite.Source;
            primitive.SubSpriteName = sprite.SubSpriteName;

            primitive.GenerateVertexData();
            renderer.SubmitSpritePrimitive(primitive);
        });
    }
}